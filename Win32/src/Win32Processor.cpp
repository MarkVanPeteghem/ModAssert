//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "modassert/Win32Processor.hpp"
#include <windows.h>

namespace InfoProviders
{
	const std::string& Win32ProcessorInfoProvider::GetType() const
	{
		static const std::string type = "processor";
		return type;
	}

	static std::string GetProcessorInfo(const SYSTEM_INFO &systemInfo)
	{
		std::string str;

		if (systemInfo.dwNumberOfProcessors!=1)
			str += RichBool::ToString(systemInfo.dwNumberOfProcessors)+"x ";

		switch (systemInfo.wProcessorArchitecture)
		{
		case 9: //PROCESSOR_ARCHITECTURE_AMD64
			str += "x64";
			break;
		case 10: //PROCESSOR_ARCHITECTURE_IA32_ON_WIN64
			str += "WOW64";
			break;
		case PROCESSOR_ARCHITECTURE_IA64:
			str += "Intel Itanium";
			break;
		case PROCESSOR_ARCHITECTURE_INTEL:
			switch (systemInfo.dwProcessorType)
			{
			case PROCESSOR_INTEL_386:
				str += "386";
				break;
			case PROCESSOR_INTEL_486:
				str += "486";
				break;
			case PROCESSOR_INTEL_PENTIUM:
				str += "Pentium";
				break;
			default:
				str += "unknown processor";
				break;
			}
			break;
		default:
			str += "unknown processor";
			break;
		}

		str += ", level "+RichBool::ToString(systemInfo.wProcessorLevel);

		std::string modelAndStepping;
		if ( (systemInfo.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL)
			&& ( (systemInfo.dwProcessorType==PROCESSOR_INTEL_386)
			|| (systemInfo.dwProcessorType==PROCESSOR_INTEL_486) ) )
		{
			int hi = HIBYTE(systemInfo.wProcessorRevision),
				lo = LOBYTE(systemInfo.wProcessorRevision);
			if (hi==0xff)
			{
				int model = (lo>>4) - 0xA, stepping = lo&0xf;
				modelAndStepping = "model "+RichBool::ToString(model)+
					", stepping "+RichBool::ToString(stepping);
			}
			else
			{
				modelAndStepping  = "stepping ";
				modelAndStepping += 'A'+(char)hi;
				modelAndStepping += '.';
				modelAndStepping += RichBool::ToString(lo);
			}
		}
		else
		{
			int model = HIBYTE(systemInfo.wProcessorRevision);
			int stepping = LOBYTE(systemInfo.wProcessorRevision);
			modelAndStepping = "model "+RichBool::ToString(model)+
					", stepping "+RichBool::ToString(stepping);
		}
		str += ", "+modelAndStepping;

		return str;
	}

	static std::string GetProcessorInfo()
	{
		SYSTEM_INFO systemInfo, nativeSystemInfo;
		bool useNativeSystemInfo=false;

		GetSystemInfo(&systemInfo);

		HMODULE hKernel32 = LoadLibrary("KERNEL32.DLL");
		if (hKernel32 != NULL)
		{
			VOID (WINAPI *GetNativeSystemInfo)(SYSTEM_INFO*);
			GetNativeSystemInfo = (VOID (WINAPI *)(SYSTEM_INFO*))GetProcAddress(hKernel32,"GetNativeSystemInfo");
			if (GetNativeSystemInfo)
			{
				// get native system info:
				GetNativeSystemInfo(&nativeSystemInfo);

				// but only use it if it is different from the other one:
				useNativeSystemInfo =
					(systemInfo.dwNumberOfProcessors!=nativeSystemInfo.dwNumberOfProcessors) ||
					(systemInfo.dwProcessorType!=nativeSystemInfo.dwProcessorType) ||
					(systemInfo.wProcessorArchitecture!=nativeSystemInfo.wProcessorArchitecture) ||
					(systemInfo.wProcessorLevel!=nativeSystemInfo.wProcessorLevel) ||
					(systemInfo.wProcessorRevision!=nativeSystemInfo.wProcessorRevision);
			}
			FreeLibrary(hKernel32);
		}

		std::string str;
		if (useNativeSystemInfo)
			str = GetProcessorInfo(nativeSystemInfo)+
				" (emulated as "+
				GetProcessorInfo(systemInfo)+")";
		else
			str = GetProcessorInfo(systemInfo);

		return str;
	}

	std::string Win32ProcessorInfoProvider::GetInfo() const
	{
		// build the string only once; the processor(s) will always be the
		// same during execution
		// note this is threadsafe, because the GetInfo in the infoproviders is
		// only called from inside a critical section

		static std::string str;
		if (str.empty())
			str = GetProcessorInfo();
		return str;
	}
}
