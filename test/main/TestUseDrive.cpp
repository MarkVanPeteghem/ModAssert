//  Copyright (C) 2004-2009 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#endif

#include "ModAssertTest.h"

#if defined(RICHBOOL_WIN) && !defined(RICHBOOL_USE_WX)

#include <windows.h>
#include "modassert/Win32Handler.hpp"

namespace ModAssert
{
	struct IDriveIsRemote
	{
		virtual bool IsRemote(char drive) const = 0;
	};
}

struct MockDriveIsRemote: public ModAssert::IDriveIsRemote
{
	virtual bool IsRemote(char drive) const
	{
		return (drive=='r')||(drive=='s');
	}
};

MA_TEST(UseDrive_DefaultSettings)
{
	MockDriveIsRemote mockDriveIsRemote;
	ModAssert::DriveUsage driveUsage(mockDriveIsRemote);

	META_ASSERT(!driveUsage.UseDrive('a'));
	META_ASSERT(!driveUsage.UseDrive('b'));
	META_ASSERT( driveUsage.UseDrive('c'));
	META_ASSERT(!driveUsage.UseDrive('r'));
	META_ASSERT(!driveUsage.UseDrive('s'));
}

MA_TEST(UseDrive_UseDriveA)
{
	MockDriveIsRemote mockDriveIsRemote;
	ModAssert::DriveUsage driveUsage(mockDriveIsRemote);
	
	driveUsage.SetUseDrive('a', true);

	META_ASSERT( driveUsage.UseDrive('a'));
	META_ASSERT(!driveUsage.UseDrive('b'));
	META_ASSERT( driveUsage.UseDrive('c'));
	META_ASSERT(!driveUsage.UseDrive('r'));
	META_ASSERT(!driveUsage.UseDrive('s'));
}

MA_TEST(UseDrive_DontUseDriveC)
{
	MockDriveIsRemote mockDriveIsRemote;
	ModAssert::DriveUsage driveUsage(mockDriveIsRemote);
	
	driveUsage.SetUseDrive('c', false);

	META_ASSERT(!driveUsage.UseDrive('a'));
	META_ASSERT(!driveUsage.UseDrive('b'));
	META_ASSERT(!driveUsage.UseDrive('c'));
	META_ASSERT(!driveUsage.UseDrive('r'));
	META_ASSERT(!driveUsage.UseDrive('s'));
}

MA_TEST(UseDrive_UseDriveR)
{
	MockDriveIsRemote mockDriveIsRemote;
	ModAssert::DriveUsage driveUsage(mockDriveIsRemote);
	
	driveUsage.SetUseDrive('r', true);

	META_ASSERT(!driveUsage.UseDrive('a'));
	META_ASSERT(!driveUsage.UseDrive('b'));
	META_ASSERT( driveUsage.UseDrive('c'));
	META_ASSERT( driveUsage.UseDrive('r'));
	META_ASSERT(!driveUsage.UseDrive('s'));
}

MA_TEST(UseDrive_UseRemoteDrives)
{
	MockDriveIsRemote mockDriveIsRemote;
	ModAssert::DriveUsage driveUsage(mockDriveIsRemote);
	
	driveUsage.SetUseRemoteDrives(true);

	META_ASSERT(!driveUsage.UseDrive('a'));
	META_ASSERT(!driveUsage.UseDrive('b'));
	META_ASSERT( driveUsage.UseDrive('c'));
	META_ASSERT( driveUsage.UseDrive('r'));
	META_ASSERT( driveUsage.UseDrive('s'));
}

#endif
