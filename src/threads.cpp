//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/config.hpp"
#include "modassert/threads.hpp"

#if defined(MODASSERT_USE_PTHREADS)

	#include <pthread.h>

	namespace ModAssert
	{
		static pthread_mutex_t mutex;

		struct InitMutex
		{
			InitMutex()
			{
				pthread_mutexattr_t attr;
				pthread_mutexattr_init(&attr);
				pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
				pthread_mutex_init(&mutex, &attr);
				pthread_mutexattr_destroy(&attr);
			}
			~InitMutex()
			{
				pthread_mutex_destroy(&mutex);
			}
		} initMutex;

		void ScopedLock::Lock()
		{
			pthread_mutex_lock(&mutex);
			locked = true;
		}
		void ScopedLock::Unlock()
		{
			pthread_mutex_unlock(&mutex);
			locked = false;
		}

		static bool mainThreadDetermined = false;
		static pthread_t mainThreadId;

		void SetMainThread()
		{
			if (!mainThreadDetermined)
			{
				mainThreadDetermined = true;
				mainThreadId = pthread_self();
			}
		}

		bool IsGUIThread()
		{
			pthread_t tid = pthread_self();
			return pthread_equal(mainThreadId, tid)!=0;
		}
	}

#elif defined(RICHBOOL_USE_WX)

	#include "wx/thread.h"

	namespace ModAssert
	{
		static wxCriticalSection critSection;

		void ScopedLock::Lock()
		{
			critSection.Enter();
			locked = true;
		}
		void ScopedLock::Unlock()
		{
			critSection.Leave();
			locked = false;
		}

		void SetMainThread()
		{}

		bool IsGUIThread()
		{
			return wxIsMainThread();
		}
	}

#elif defined(RICHBOOL_WIN)

	#include "windows.h"

	namespace ModAssert
	{
		CRITICAL_SECTION critSection;

		struct InitCriticalSection
		{
			InitCriticalSection()
			{
				InitializeCriticalSection(&critSection);
			}
			~InitCriticalSection()
			{
				DeleteCriticalSection(&critSection);
			}
		} initCriticalSection;

		void ScopedLock::Lock()
		{
			EnterCriticalSection(&critSection);
			locked = true;
		}
		void ScopedLock::Unlock()
		{
			LeaveCriticalSection(&critSection);
			locked = false;
		}


		static bool mainThreadDetermined = false;
		static DWORD mainThreadId = 0;

		void SetMainThread()
		{
			if (!mainThreadDetermined)
			{
				mainThreadDetermined = true;
				mainThreadId = GetCurrentThreadId();
			}
		}

		bool IsGUIThread()
		{
			return mainThreadId==GetCurrentThreadId();
		}
	}

#else

	namespace ModAssert
	{
		void ScopedLock::Lock() {}
		void ScopedLock::Unlock() {}
	}

#endif

namespace ModAssert
{
	ScopedLock::ScopedLock(bool initialLock): locked(false)
	{
		if (initialLock)
			Lock();
	}
	ScopedLock::~ScopedLock()
	{
		if (locked)
			Unlock();
	}
}
