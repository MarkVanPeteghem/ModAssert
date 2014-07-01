//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com


#ifndef WIN32_DISK_SPACE_H__QM
#define WIN32_DISK_SPACE_H__QM

#include "modassert/info.hpp"

namespace InfoProviders
{
	class Win32DiskInfoProvider: public InfoProvider
	{
	public:
		Win32DiskInfoProvider(const std::string &driveName_):
            InfoProvider(machine), driveName(driveName_), valid(true)
        {
			ConstructInfo();
		}

		virtual const std::string& GetType() const;
		virtual bool HasInfo() const;
		virtual std::string GetInfo() const;

		char GetDriveLetter() const
		{
			return driveName[0];
		}

	private:
		std::string driveName, info;
		bool valid;

		void ConstructInfo();
	};

	class Win32FreeDiskSpaceInfoProvider: public InfoProvider
	{
	public:
		Win32FreeDiskSpaceInfoProvider(const std::string &driveName_):
            InfoProvider(volatileInfo), driveName(driveName_)
        {}

		virtual const std::string& GetType() const;
		virtual std::string GetInfo() const;

		char GetDriveLetter() const
		{
			return driveName[0];
		}

	private:
		std::string driveName;
	};
}

#endif // #ifndef WIN32_DISK_SPACE_H__QM
