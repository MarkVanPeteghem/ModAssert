//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/Win32OSVersion.hpp"
#include <windows.h>

#if (WINVER <= 0x0400) && !defined(__GNUC__)
#define SUITEMASK(info) (info.wReserved[0])
#define PRODUCTTYPE(info) (LOBYTE(info.wReserved[1]))
#define VER_NT_WORKSTATION 1
#define VER_NT_DOMAIN_CONTROLLER 2
#define VER_NT_SERVER 3
#define VER_SUITE_DATACENTER 0x0080
#define VER_SUITE_ENTERPRISE 0x0002
#define VER_SUITE_PERSONAL   0x0200
#define VER_SUITE_BLADE      0x0400
#else
#define SUITEMASK(info) info.wSuiteMask
#define PRODUCTTYPE(info) info.wProductType
#endif

namespace InfoProviders
{
	const std::string& Win32OSVersionInfoProvider::GetType() const
	{
		static const std::string type = "os version";
		return type;
	}

	static std::string GetVersionInfoAsString(const OSVERSIONINFO &osVersionInfo)
	{
		std::string str =
			RichBool::ToString(osVersionInfo.dwMajorVersion)+
			"."+RichBool::ToString(osVersionInfo.dwMinorVersion)
			+": ";

		std::string type;
		switch (osVersionInfo.dwPlatformId)
		{
		case 1:
			switch (osVersionInfo.dwMajorVersion)
			{
			case 4:
				switch (osVersionInfo.dwMinorVersion)
				{
				case 0:
					type = "95";
					if (osVersionInfo.dwBuildNumber>1080)
						type = " OSR2";
					break;
				case 10:
					type = "98";
					if (osVersionInfo.dwBuildNumber>=2183)
						type = " SE";
					break;
				case 90:
					type = "Me";
					break;
				}
				break;
			}
			break;
		case 2:
			switch (osVersionInfo.dwMajorVersion)
			{
			case 3:
				switch (osVersionInfo.dwMinorVersion)
				{
				case 51:
					type = "NT 3.51";
					break;
				}
				break;
			case 4:
				switch (osVersionInfo.dwMinorVersion)
				{
				case 0:
					type = "NT 4.0";
					break;
				}
				break;
			case 5:
				switch (osVersionInfo.dwMinorVersion)
				{
				case 0:
					type = "2000";
					break;
				case 1:
					type = "XP";
					break;
				case 2:
					type = "Server 2003 or Windows Server 2003 R2";
					break;
				}
				break;
			case 6:
				switch (osVersionInfo.dwMinorVersion)
				{
				case 0:
					type = "Vista or Windows Server Longhorn";
					break;
				}
				break;
			}
		case 3:
			type = "CE "+RichBool::ToString(osVersionInfo.dwMajorVersion)
				+"."+RichBool::ToString(osVersionInfo.dwMinorVersion);
			break;
		}
		if (!type.empty())
			str += "Windows "+type;
		else
			str += "unknown OS";

		str += ", build "+RichBool::ToString(osVersionInfo.dwBuildNumber)+", ";
		str += osVersionInfo.szCSDVersion;
		return str;
	}

	static std::string GetVersionInfoAsString(const OSVERSIONINFOEXA &osVersionInfo)
	{
		std::string str;

		std::string type;
		switch (osVersionInfo.dwPlatformId)
		{
		case 1:
			switch (osVersionInfo.dwMajorVersion)
			{
			case 4:
				switch (osVersionInfo.dwMinorVersion)
				{
				case 0:
					type = "95";
					if (osVersionInfo.dwBuildNumber>1080)
						type = " OSR2";
					break;
				case 10:
					type = "98";
					if (osVersionInfo.dwBuildNumber>=2183)
						type = " SE";
					break;
				case 90:
					type = "Me";
					break;
				}
				break;
			}
			break;
		case 2:
			switch (osVersionInfo.dwMajorVersion)
			{
			case 3:
				if (osVersionInfo.dwMinorVersion==51)
					type = "NT 3.51";
				break;
			case 4:
				switch (PRODUCTTYPE(osVersionInfo))
				{
				case VER_NT_WORKSTATION:
					type = "NT 4.0 Workstation";
					break;
				case VER_NT_SERVER:
					type = "NT 4.0 Server";
					break;
				}
				break;
			case 5:
				switch (osVersionInfo.dwMinorVersion)
				{
				case 0:
					switch (PRODUCTTYPE(osVersionInfo))
					{
					case VER_NT_WORKSTATION:
						type = "2000 Workstation";
						break;
					case VER_NT_SERVER:
						if ((SUITEMASK(osVersionInfo) &
							VER_SUITE_DATACENTER) == VER_SUITE_DATACENTER)
							type = "2000 Datacenter Server";
						else if ((SUITEMASK(osVersionInfo) &
							VER_SUITE_ENTERPRISE) == VER_SUITE_ENTERPRISE)
							type = "2000 Advanced Server";
						else
							type = "2000 Server";
						break;
					}
					break;
				case 1:
					if ((SUITEMASK(osVersionInfo)&VER_SUITE_PERSONAL) == VER_SUITE_PERSONAL)
						type = "XP Home Edition";
					else
						type = "XP Professional";
					break;
				case 2:
					if (PRODUCTTYPE(osVersionInfo)==VER_NT_WORKSTATION)
						type = "XP 64";
					else
					{
						if ((SUITEMASK(osVersionInfo) &
							VER_SUITE_DATACENTER) == VER_SUITE_DATACENTER)
							type = "Server 2003 Datacenter Edition";
						else if ((SUITEMASK(osVersionInfo) &
								VER_SUITE_ENTERPRISE) == VER_SUITE_ENTERPRISE)
							type = "Server 2003 Enterprise Edition";
						else if ((SUITEMASK(osVersionInfo) &
								VER_SUITE_BLADE) == VER_SUITE_BLADE)
							type = "Server 2003 Web Edition";
						else
							type = "Server 2003 Standard Edition";
					}
					break;
				}
				break;
			case 6:
				switch (osVersionInfo.dwMinorVersion)
				{
				case 0:
					switch (PRODUCTTYPE(osVersionInfo))
					{
					case VER_NT_WORKSTATION:
						type = "Vista";
						break;
					case VER_NT_SERVER:
						type = "Server Longhorn";
						break;
					case VER_NT_DOMAIN_CONTROLLER:
						type = "Server Longhorn (domain controller)";
						break;
					}
					break;
				}
				break;
			}
			break;
		case 3:
			type = "CE "+RichBool::ToString(osVersionInfo.dwMajorVersion)
				+"."+RichBool::ToString(osVersionInfo.dwMinorVersion);
			break;
		}
		if (!type.empty())
			str += "Windows "+type;
		else
			str += "unknown OS";

		str += "("+RichBool::ToString(osVersionInfo.dwMajorVersion)+
			"."+RichBool::ToString(osVersionInfo.dwMinorVersion)
			+")";
		str += ", build "+RichBool::ToString(osVersionInfo.dwBuildNumber)+", ";
		str += osVersionInfo.szCSDVersion;
		return str;
	}

	static std::string GetVersionInfoAsString()
	{
		// check if extended version info is available:
		HMODULE hKernel32 = LoadLibrary("KERNEL32.DLL");
		if (hKernel32 != NULL)
		{
			VOID (WINAPI *pGetVersionInfoEx)(OSVERSIONINFOEXA*);
			pGetVersionInfoEx = (VOID (WINAPI *)(OSVERSIONINFOEXA*))GetProcAddress(hKernel32,"GetVersionExA");
			if (pGetVersionInfoEx)
			{
				// yes it is:
				OSVERSIONINFOEXA osVersionInfo;
				osVersionInfo.dwOSVersionInfoSize = sizeof(osVersionInfo);
				pGetVersionInfoEx(&osVersionInfo);
				std::string str = GetVersionInfoAsString(osVersionInfo);
				FreeLibrary(hKernel32);
				return str;
			}
			FreeLibrary(hKernel32);
		}

		// no it isn't, use non-extended:
		OSVERSIONINFO osVersionInfo;
		osVersionInfo.dwOSVersionInfoSize = sizeof(osVersionInfo);
		GetVersionEx(&osVersionInfo);
		return GetVersionInfoAsString(osVersionInfo);
	}

	std::string Win32OSVersionInfoProvider::GetInfo() const
	{
		// build the string only once; the OS version will always be the
		// same during execution
		// note this is threadsafe, because GetInfo in the infoproviders is
		// only called from inside a critical section

		static std::string str;

		if (str.empty())
			str = GetVersionInfoAsString();

		return str;
	}
}
