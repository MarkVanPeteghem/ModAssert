//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif



// Define this symbol, so assertions are also reported when NDEBUG is defined.
// Usually NDEBUG is defined for optimized builds, and we need to know if
// thread synchronization works in that case as well.
#define MOD_ASSERT_REPORT_FILE

#include "ModAssertTest.h"
#include "CreateList.h"
#include "modassert/threads.hpp"
#include "richbool/richbool.hpp"
#include <stdio.h>

#if !defined(_MSC_VER) || defined(_MT)

#if defined(MODASSERT_USE_PTHREADS)

void* ThreadFunction(void*)
{
	for (int i=0; i<100; ++i)
		MOD_ASSERT(rbEQUAL(5, i));
	return (void*)0;
}

MA_TEST(TwentyThreads)
{
	ModAssertTestHandler::SetIgnoreAssertions(true);

	const int nrThreads=20;
	pthread_t threads[nrThreads];

	int i=0;
	for (i=0; i<nrThreads; ++i)
		pthread_create(&threads[i], NULL, ThreadFunction, NULL);

	void *status_ptr=(void*)0;
	for (i=0; i<nrThreads; ++i)
		pthread_join(threads[i], &status_ptr);

	ModAssertTestHandler::SetIgnoreAssertions(false);
}

MA_TEST(IsGUIThread)
{
	META_ASSERT(ModAssert::IsGUIThread());
}

void* CheckNotGUIThread(void*)
{
	META_ASSERT(!ModAssert::IsGUIThread());
	return (void*)0;
}

MA_TEST(IsNotGUIThread)
{
	pthread_t thread;
	pthread_create(&thread, NULL, CheckNotGUIThread, NULL);

	void *status_ptr=(void*)0;
	pthread_join(thread, &status_ptr);
}

#elif defined(RICHBOOL_USE_WX)

#include "wx/thread.h"

class TestThread: public wxThread
{
public:
	TestThread(): wxThread(wxTHREAD_JOINABLE)
	{}

	virtual ExitCode Entry()
	{
		for (int i=0; i<100; ++i)
		{
			MOD_ASSERT(rbEQUAL(5, i));
		}
		return 0;
	}
};

MA_TEST(TwoThreads)
{
	ModAssertTestHandler::SetIgnoreAssertions(true);

	TestThread thread1, thread2;

	thread1.Create();
	thread2.Create();

	thread1.Run();
	thread2.Run();

	wxThread::This()->Yield();

	thread1.Wait();
	thread2.Wait();

	ModAssertTestHandler::SetIgnoreAssertions(false);
}

MA_TEST(OneHundredThreads)
{
	ModAssertTestHandler::SetIgnoreAssertions(true);

	const int nrThreads=20;

	TestThread threads[nrThreads];

	int i=0;
	for (i=0; i<nrThreads; ++i)
	{
		threads[i].Create();
		threads[i].SetPriority(WXTHREAD_MIN_PRIORITY);
	}

	for (i=0; i<nrThreads; ++i)
		threads[i].Run();

	for (i=0; i<nrThreads; ++i)
		threads[i].Wait();

	ModAssertTestHandler::SetIgnoreAssertions(false);
}

MA_TEST(IsGUIThread)
{
	META_ASSERT(ModAssert::IsGUIThread());
}

class CheckNotGUIThread: public wxThread
{
public:
	CheckNotGUIThread(): wxThread(wxTHREAD_JOINABLE)
	{}

	virtual ExitCode Entry()
	{
		META_ASSERT(!ModAssert::IsGUIThread());
		return 0;
	}
};

MA_TEST(IsNotGUIThread)
{
	CheckNotGUIThread thread;

	thread.Create();
	thread.SetPriority(WXTHREAD_MIN_PRIORITY);
	thread.Run();
	thread.Wait();
}

#elif defined(RICHBOOL_WIN)

#include "Windows.h"

static DWORD WINAPI FailingFunction(LPVOID )
{
	for (int i=0; i<300; ++i)
	{
		MOD_ASSERT(rbEQUAL(5, i));
		if (i%10==0)
			Sleep(10);
	}
	return 0;
}

MA_TEST(TwoThreads)
{
	ModAssertTestHandler::SetIgnoreAssertions(true);

	HANDLE handle1, handle2;

	handle1 = CreateThread(0, 0, FailingFunction, 0, 0, 0);
	handle2 = CreateThread(0, 0, FailingFunction, 0, 0, 0);

	WaitForSingleObject(handle1, INFINITE);
	WaitForSingleObject(handle2, INFINITE);

	ModAssertTestHandler::SetIgnoreAssertions(false);
}

MA_TEST(MoreThreads)
{
	ModAssertTestHandler::SetIgnoreAssertions(true);

	const int nrThreads=30;
	HANDLE handles[nrThreads];
	for (int i=0; i<nrThreads; ++i)
		handles[i] = CreateThread(0, 0, FailingFunction, 0, 0, 0);
	WaitForMultipleObjects(nrThreads, handles, true, INFINITE);

	ModAssertTestHandler::SetIgnoreAssertions(false);
}

MA_TEST(IsGUIThread)
{
	META_ASSERT(ModAssert::IsGUIThread());
}

static DWORD WINAPI CheckNotGUIThread(LPVOID )
{
	META_ASSERT(!ModAssert::IsGUIThread());
	return 0;
}

MA_TEST(IsNotGUIThread)
{
	HANDLE handle = CreateThread(0, 0, CheckNotGUIThread, 0, 0, 0);
	WaitForMultipleObjects(1, &handle, true, INFINITE);
}

#else

#error "no thread model specified"

#endif

MA_TEST(AssertWhileLocked)
{
	ModAssert::ScopedLock lock;

	int a=2;

	EXPECT_ASSERT(false, "a==1", NULL, NULL, NULL);
	MOD_ASSERT(a==1);
}


#endif // #if !defined(_MSC_VER) || defined(_MT)
