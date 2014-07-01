//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#include "modassert/handler.hpp"
#include "modassert/infostore.hpp"
#include "modassert/timeinfo.hpp"

#include "modassert/Win32Handler.hpp"
#include "modassert/Win32Displayer.hpp"
#include "modassert/Win32Trace.hpp"
#include "modassert/Win32LastError.hpp"
#include "modassert/Win32ThreadId.hpp"
#include "modassert/Win32ProcessId.hpp"
#include "modassert/Win32CurrentDirectory.hpp"
#include "modassert/Win32OSVersion.hpp"
#include "modassert/Win32Processor.hpp"
#include "modassert/Win32UserName.hpp"
#include "modassert/Win32ComputerName.hpp"
#include "modassert/Win32DiskSpace.hpp"
#include "modassert/Win32MemoryStatus.hpp"
#include "modassert/Win32TerminateMessage.hpp"
#include "modassert/Win32WarningMessage.hpp"

#include "richbool/analysis.hpp"

namespace ModAssert
{
	static Win32Displayer s_win32Displayer;
	static Win32TerminateMessage s_win32TerminateMessage;
	static Win32WarningMessage s_win32WarningMessage;
	static Win32Trace s_win32Trace;
	static InfoProviders::Win32ThreadIdInfoProvider s_threadIdInfoProvider;
	static InfoProviders::LastErrorInfoProvider s_lastErrorInfoProvider;
	static LastErrorHook s_lastErrorHook;
	static InfoProviders::TimeInfoProvider s_timeInfoProvider;
	static InfoProviders::Win32ProcessIdInfoProvider s_processIdInfoProvider;
	static InfoProviders::Win32OSVersionInfoProvider s_OSVersionInfoProvider;
	static InfoProviders::Win32CurrentDirectoryInfoProvider s_currentDirectoryInfoProvider;
	static InfoProviders::Win32ProcessorInfoProvider s_processorInfoProvider;
	static InfoProviders::Win32UserNameInfoProvider s_userNameInfoProvider;
	static InfoProviders::Win32ComputerNameInfoProvider s_computerNameInfoProvider;
	static InfoProviders::Win32TotalMemoryInfoProvider s_totalMemoryInfoProvider;
	static InfoProviders::Win32FreeMemoryInfoProvider s_freeMemoryInfoProvider;

	static std::vector<InfoProviders::Win32DiskInfoProvider>
		s_diskInfoProviders;
	static std::vector<InfoProviders::Win32FreeDiskSpaceInfoProvider>
		s_freeDiskSpaceInfoProviders;

	void CheckDrive(char drive)
	{
		int idx = drive-'a';

		DWORD drives = GetLogicalDrives();
		if (drives&(1<<idx))
		{
			char driveName[] = { drive, ':', '\\', '\0' };

			InfoProviders::Win32DiskInfoProvider ip(driveName);
			if (ip.HasInfo())
			{
				s_diskInfoProviders.push_back(ip);
				s_freeDiskSpaceInfoProviders.push_back(
					InfoProviders::Win32FreeDiskSpaceInfoProvider(driveName)
				);
			}
		}
	}

	struct IDriveIsRemote
	{
		virtual bool IsRemote(char drive) const = 0;
	};

	struct Win32DriveIsRemote: public IDriveIsRemote
	{
		virtual bool IsRemote(char drive) const
		{
			char driveName[] = { drive, ':', '\\', '\0' };
			UINT type = GetDriveType(driveName);
			return (type==DRIVE_REMOTE);
		}
	};

	DriveUsage::DriveUsage(const IDriveIsRemote &driveIsRemote_):
		driveIsRemote(driveIsRemote_), useRemoteDrives(false)
	{
		// by default drives A and B are not used:
		useDrive[0] = useDrive[1] = DontUseDrive;

		for (int i=2; i<26; ++i)
			useDrive[i] = UseDriveIfLocal;
	}

	void DriveUsage::SetUseRemoteDrives(bool b)
	{
		useRemoteDrives = b;
	}

	void DriveUsage::SetUseDrive(char drive, bool b)
	{
		useDrive[tolower(drive)-'a'] = b ? AlwaysUseDrive : DontUseDrive;
	}

	bool DriveUsage::UseDrive(char drive) const
	{
		const int idx = tolower(drive)-'a';
		if (!useRemoteDrives && (useDrive[idx]==UseDriveIfLocal))
		{
			if (driveIsRemote.IsRemote(drive))
				return false;
		}
		return useDrive[idx]!=DontUseDrive;
	}

	static Win32DriveIsRemote driveIsRemote;
	static DriveUsage s_driveUsage(driveIsRemote);

	void SetUseDrive(char drive, bool b)
	{
		s_driveUsage.SetUseDrive(drive, b);
	}

	void SetUseRemoteDrives(bool b)
	{
		s_driveUsage.SetUseRemoteDrives(b);
	}

	bool UseDrive(char drive)
	{
		return s_driveUsage.UseDrive(drive);
	}

	void SetupForWin32(HINSTANCE hInstance)
	{
		SetWin32Handler(hInstance);

		Setup(&s_win32Displayer);
	}

	void SetupForWin32(HINSTANCE hInstance, Mode mode)
	{
		SetWin32Handler(hInstance);

		Setup(mode, &s_win32Displayer, &s_win32WarningMessage, &s_win32TerminateMessage);
	}

	void SetWin32Handler(HINSTANCE hInstance)
	{
		static bool called = false;
		if (called)
			return;
		called = true;

		s_win32Displayer.SetInstance(hInstance);

		InfoProviders::Win32ThreadIdInfoProvider::SetMainThreadId(GetCurrentThreadId());

		AddInfoProvider(&s_lastErrorInfoProvider);
		AddHook(&s_lastErrorHook);
		AddInfoProvider(&s_threadIdInfoProvider);
		AddInfoProvider(&s_timeInfoProvider);
		AddInfoProvider(&s_processIdInfoProvider);
		AddInfoProvider(&s_OSVersionInfoProvider);
		AddInfoProvider(&s_processorInfoProvider);
		AddInfoProvider(&s_currentDirectoryInfoProvider);
		AddInfoProvider(&s_userNameInfoProvider);
		AddInfoProvider(&s_computerNameInfoProvider);
		AddInfoProvider(&s_totalMemoryInfoProvider);
		AddInfoProvider(&s_freeMemoryInfoProvider);

		// Add a Win32DiskInfoProvider and Win32FreeDiskSpaceInfoProvider
		// for every drive.
		for (char drive='a'; drive<='z'; ++drive)
		{
			if (UseDrive(drive))
				CheckDrive(drive);
		}

		// this loop supposes that the number of elements in
		// s_diskInfoProviders and s_freeDiskSpaceInfoProviders
		// are the same -  adjust if this would no longer be the case!
		for (size_t idx=0; idx<s_diskInfoProviders.size(); ++idx)
		{
			AddInfoProvider(&s_diskInfoProviders[idx]);
			AddInfoProvider(&s_freeDiskSpaceInfoProviders[idx]);
		}

		// add logger after infoproviders, so the information in them
		// is logged to it
		AddLogger(&s_win32Trace);
	}

	Responder& GetWin32Displayer()
	{
		return s_win32Displayer;
	}

	Logger& GetWin32Trace()
	{
		return s_win32Trace;
	}

	const InfoProviders::InfoProvider& GetWin32ThreadIdInfoProvider()
	{
		return s_threadIdInfoProvider;
	}

	const InfoProviders::InfoProvider& GetWin32LastErrorInfoProvider()
	{
		return s_lastErrorInfoProvider;
	}

	const InfoProviders::InfoProvider& GetWin32TimeInfoProvider()
	{
		return s_timeInfoProvider;
	}

	const InfoProviders::InfoProvider& GetWin32ProcessIdInfoProvider()
	{
		return s_processIdInfoProvider;
	}

	const InfoProviders::InfoProvider& GetWin32OSVersionInfoProvider()
	{
		return s_OSVersionInfoProvider;
	}

	const InfoProviders::InfoProvider& GetWin32CurrentDirectoryInfoProvider()
	{
		return s_currentDirectoryInfoProvider;
	}

	const InfoProviders::InfoProvider& GetWin32ProcessorInfoProvider()
	{
		return s_processorInfoProvider;
	}

	const InfoProviders::InfoProvider& GetWin32UserNameInfoProvider()
	{
		return s_userNameInfoProvider;
	}

	const InfoProviders::InfoProvider& GetWin32ComputerNameInfoProvider()
	{
		return s_computerNameInfoProvider;
	}

	const InfoProviders::InfoProvider& GetWin32TotalMemoryInfoProvider()
	{
		return s_totalMemoryInfoProvider;
	}

	const InfoProviders::InfoProvider& GetWin32FreeMemoryInfoProvider()
	{
		return s_freeMemoryInfoProvider;
	}

	size_t GetNrDetectedDrives()
	{
		return s_diskInfoProviders.size();
	}

	const InfoProviders::Win32DiskInfoProvider& GetDiskInfoProvider(size_t idx)
	{
		return s_diskInfoProviders[idx];
	}

	const InfoProviders::Win32FreeDiskSpaceInfoProvider& GetFreeDiskSpaceInfoProvider(size_t idx)
	{
		return s_freeDiskSpaceInfoProviders[idx];
	}

	bool charsEqualNoCase(char a, char b)
	{
		return (toupper(a)==b) || (tolower(a)==b);
	}

	const InfoProviders::Win32DiskInfoProvider* GetDiskInfoProvider(char drive)
	{
		for (size_t idx=0; idx<s_diskInfoProviders.size(); ++idx)
		{
			if (charsEqualNoCase(s_diskInfoProviders[idx].GetDriveLetter(), drive))
				return &s_diskInfoProviders[idx];
		}
		return NULL;
	}

	const InfoProviders::Win32FreeDiskSpaceInfoProvider* GetFreeDiskSpaceInfoProvider(char drive)
	{
		for (size_t idx=0; idx<s_freeDiskSpaceInfoProviders.size(); ++idx)
		{
			if (charsEqualNoCase(s_freeDiskSpaceInfoProviders[idx].GetDriveLetter(), drive))
				return &s_freeDiskSpaceInfoProviders[idx];
		}
		return NULL;
	}
}
