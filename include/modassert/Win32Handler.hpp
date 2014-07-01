//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef MOD_ASSERT_HANDLER_WIN32_H__QM
#define MOD_ASSERT_HANDLER_WIN32_H__QM

#include <windows.h>

#include "modassert/linkcore.hpp"

#define BOOST_LIB_NAME modassertWin32
#include "modassert/version.hpp"
#include "richbool/auto_link.hpp"

#include "modassert/handler.hpp"

namespace InfoProviders
{
	class InfoProvider;
	class Win32DiskInfoProvider;
	class Win32FreeDiskSpaceInfoProvider;
}

namespace ModAssert
{
	void SetupForWin32(HINSTANCE hInstance);
	void SetupForWin32(HINSTANCE hInstance, Mode mode);

	// deprecated alternative for SetupForWin32:
	void SetWin32Handler(HINSTANCE hInstance);

	void SetUseRemoteDrives(bool b);
	void SetUseDrive(char drive, bool b);
	bool UseDrive(char drive);

	class Responder;
	class Logger;

	Responder& GetWin32Displayer();
	Logger& GetWin32Trace();
	const InfoProviders::InfoProvider& GetWin32ThreadIdInfoProvider();
	const InfoProviders::InfoProvider& GetWin32LastErrorInfoProvider();
	const InfoProviders::InfoProvider& GetWin32TimeInfoProvider();
	const InfoProviders::InfoProvider& GetWin32ProcessIdInfoProvider();
	const InfoProviders::InfoProvider& GetWin32OSVersionInfoProvider();
	const InfoProviders::InfoProvider& GetWin32CurrentDirectoryInfoProvider();
	const InfoProviders::InfoProvider& GetWin32ProcessorInfoProvider();
	const InfoProviders::InfoProvider& GetWin32UserNameInfoProvider();
	const InfoProviders::InfoProvider& GetWin32ComputerNameInfoProvider();
	const InfoProviders::InfoProvider& GetWin32TotalMemoryInfoProvider();
	const InfoProviders::InfoProvider& GetWin32FreeMemoryInfoProvider();

	size_t GetNrDetectedDrives();
	const InfoProviders::Win32DiskInfoProvider& GetDiskInfoProvider(size_t idx);
	const InfoProviders::Win32FreeDiskSpaceInfoProvider& GetFreeDiskSpaceInfoProvider(size_t idx);
	const InfoProviders::Win32DiskInfoProvider* GetDiskInfoProvider(char drive);
	const InfoProviders::Win32FreeDiskSpaceInfoProvider* GetFreeDiskSpaceInfoProvider(char drive);

	// for testing purposes:
	struct IDriveIsRemote;

	//undocumented class exposed for testing purposes:
	class DriveUsage
	{
		enum eDriveUsage { DontUseDrive, UseDriveIfLocal, AlwaysUseDrive };
		eDriveUsage useDrive[26];
		const IDriveIsRemote &driveIsRemote;
		bool useRemoteDrives;

		DriveUsage& operator=(const DriveUsage &)
		{
			return *this;
		}
	public:
		DriveUsage(const IDriveIsRemote &driveIsRemote_);

		void SetUseRemoteDrives(bool b);
		void SetUseDrive(char drive, bool b);
		bool UseDrive(char drive) const;
	};
}

#endif //#ifndef MOD_ASSERT_HANDLER_WIN32_H__QM
