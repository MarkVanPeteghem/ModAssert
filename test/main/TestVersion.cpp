//  Copyright (C) 2004-2011 Q-Mentum.
//  Use, modification and distribution are subject to the wxWindows licence
//  (see accompanying file COPYING.LIB, and LICENCE.txt for the
//  exception notice, or <http://opensource.org/licenses/wxwindows.php>)

//  For more information about Q-Mentum, visit http://www.q-mentum.com

#include "richbool/richbool.hpp"
#include "modassert/handler.hpp"
#include "ModAssertTest.h"

RichBool::detail::String GetDigits(const RichBool::detail::String &str)
{
	RichBool::detail::String rv;
	for (size_t i=0; i<str.size(); ++i)
		if ( (str[i]>='0') && (str[i]<='9') )
			rv += str[i];
	return rv;
}

// Only do this for MS VS 8.0 and higher, other compilers have relative paths in __FILE__
#if defined(_MSC_VER) && (_MSC_VER > 1400)

// If you install ModAssert in a non-standard directory,
// the following two tests may fail.
// In that case you can safely ignore these failures.

MA_TEST(Version_And_InstallDirectory)
{
	META_ASSERT(
		rbEQUAL(GetDigits(ModAssert::GetInstallDirectory()), GetDigits(MOD_ASSERT_VERSION))
	);
}

MA_TEST(Version_And_ThisDirectory)
{
	META_ASSERT(
		rbEQUAL(GetDigits(__FILE__), GetDigits(MOD_ASSERT_VERSION))
	);
}

#endif

#ifndef RICHBOOL_USE_WX

#include <fstream>

#if defined(TESTS_RUN_IN_TOPDIR)
#define DIR
#else
#define DIR "../../"
#endif

MA_TEST(Version_And_DocVersion)
{
	std::ifstream file(DIR "doc/modassert.xml");

	std::string version_in_documentation;
	while (file)
	{
		std::string line;
		std::getline(file, line);
		size_t idx = line.find("Version");
		if (idx!=std::string::npos)
		{
			version_in_documentation = line.substr(idx);
			break;
		}
	}

	META_ASSERT(
		rbEQUAL(GetDigits(version_in_documentation), GetDigits(MOD_ASSERT_VERSION))
	);
}

MA_TEST(Version_And_AutoConf_Version)
{
	std::ifstream file(DIR "configure.ac");

	std::string line;
	std::getline(file, line);

	META_ASSERT(
		rbEQUAL(GetDigits(line), GetDigits(MOD_ASSERT_VERSION))
	);
}

MA_TEST(Version_And_IncludeAutoConf_Version)
{
	std::ifstream file(DIR "include/configure.ac");

	std::string line;
	std::getline(file, line);

	META_ASSERT(
		rbEQUAL(GetDigits(line), GetDigits(MOD_ASSERT_VERSION))
	);
}

MA_TEST(Version_And_DemoConsoleAutoConf_Version)
{
	std::ifstream file(DIR "demos/Console/configure.ac");

	std::string line;
	std::getline(file, line);

	META_ASSERT(
		rbEQUAL(GetDigits(line), GetDigits(MOD_ASSERT_VERSION))
	);
}

MA_TEST(Version_And_DemoWxAutoConf_Version)
{
	std::ifstream file(DIR "demos/WxWidgets/configure.ac");

	std::string line;
	std::getline(file, line);

	META_ASSERT(
		rbEQUAL(GetDigits(line), GetDigits(MOD_ASSERT_VERSION))
	);
}


#endif
