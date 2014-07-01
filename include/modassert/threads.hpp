//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef THREADS_H__QM
#define THREADS_H__QM

namespace ModAssert
{
	class ScopedLock
	{
	public:
		ScopedLock(bool initialLock=true);
		~ScopedLock();

		void Lock();
		void Unlock();

		bool IsLocked() const { return locked; }

	private:
		bool locked;
	};

	bool IsGUIThread();
}

#endif // #ifndef THREADS_H__QM
