//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/Win32DiskSpace.hpp"
#include <windows.h>

namespace InfoProviders
{
	/////////////////////////////////////////////////////////////////
	// class Win32DiskInfoProvider

	const std::string& Win32DiskInfoProvider::GetType() const
	{
		static const std::string type = "disk";
		return type;
	}

	void Win32DiskInfoProvider::ConstructInfo()
	{
		TCHAR VolumeNameBuffer[MAX_PATH+1];
		DWORD VolumeSerialNumber=0;
		DWORD MaximumComponentLength=0;
		DWORD FileSystemFlags=0;
		TCHAR FileSystemNameBuffer[MAX_PATH+1];
		BOOL b = GetVolumeInformation(driveName.c_str(), VolumeNameBuffer, MAX_PATH+1,
			&VolumeSerialNumber, &MaximumComponentLength, &FileSystemFlags,
			FileSystemNameBuffer, MAX_PATH+1);

		if (!b)
		{
			valid = false;
			info = "error";
			return;
		}

		ULARGE_INTEGER totalNrBytes;
		totalNrBytes.QuadPart = 0;
		GetDiskFreeSpaceEx(driveName.c_str(), NULL, &totalNrBytes, NULL);

		std::string strType;
		switch (GetDriveType(driveName.c_str()))
		{
		case DRIVE_UNKNOWN:
			strType += "unknown volume type";
			break;
		case DRIVE_NO_ROOT_DIR:
			strType += "invalid root dir";
			break;
		case DRIVE_REMOVABLE:
			strType += "removable volume";
			break;
		case DRIVE_FIXED:
			strType += "fixed volume";
			break;
		case DRIVE_REMOTE:
			strType += "remote volume";
			break;
		case DRIVE_CDROM:
			strType += "CD-ROM";
			break;
		case DRIVE_RAMDISK:
			strType += "RAM disk";
			break;
		}
		info = driveName+
			" type:<"+strType+
			">, name:<"+VolumeNameBuffer+
			">, system name:<"+FileSystemNameBuffer+
			">, "+RichBool::ToString(totalNrBytes)+" bytes";
	}

	bool Win32DiskInfoProvider::HasInfo() const
	{
		return valid;
	}

	std::string Win32DiskInfoProvider::GetInfo() const
	{
		return info;
	}


	/////////////////////////////////////////////////////////////////
	// class Win32FreeDiskSpaceInfoProvider

	const std::string& Win32FreeDiskSpaceInfoProvider::GetType() const
	{
		static const std::string type = "free disk space";
		return type;
	}

	std::string Win32FreeDiskSpaceInfoProvider::GetInfo() const
	{
		ULARGE_INTEGER freeNrBytes;
		freeNrBytes.QuadPart = 0;
		GetDiskFreeSpaceEx(driveName.c_str(), &freeNrBytes, NULL, NULL);
		return driveName+" "+RichBool::ToString(freeNrBytes)+" bytes";
	}
}
