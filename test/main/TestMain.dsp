# Microsoft Developer Studio Project File - Name="Test Main" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Test Main - Win32 DebugWxMTD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestMain.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestMain.mak" CFG="Test Main - Win32 DebugWxMTD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Test Main - Win32 ReleaseMTD" (based on "Win32 (x86) Console Application")
!MESSAGE "Test Main - Win32 DebugMTD" (based on "Win32 (x86) Console Application")
!MESSAGE "Test Main - Win32 DebugWxMTD" (based on "Win32 (x86) Console Application")
!MESSAGE "Test Main - Win32 ReleaseWxMTD" (based on "Win32 (x86) Console Application")
!MESSAGE "Test Main - Win32 DebugMT" (based on "Win32 (x86) Console Application")
!MESSAGE "Test Main - Win32 ReleaseMT" (based on "Win32 (x86) Console Application")
!MESSAGE "Test Main - Win32 DebugST" (based on "Win32 (x86) Console Application")
!MESSAGE "Test Main - Win32 ReleaseST" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Test Main - Win32 ReleaseMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMTD"
# PROP BASE Intermediate_Dir "ReleaseMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMTD-6.0"
# PROP Intermediate_Dir "ReleaseMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../include" /I "$(RICHBOOL)/include" /I "../Common" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FD /Zm200 /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /libpath:"$(RICHBOOL)/lib" /libpath:"../../lib"
# Begin Special Build Tool
TargetPath=.\ReleaseMTD-6.0\TestMain.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Test Main - Win32 DebugMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMTD"
# PROP BASE Intermediate_Dir "DebugMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMTD-6.0"
# PROP Intermediate_Dir "DebugMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../include" /I "$(RICHBOOL)/include" /I "../Common" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FD /GZ /Zm250 /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)/lib" /libpath:"../../lib"
# Begin Special Build Tool
TargetPath=.\DebugMTD-6.0\TestMain.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Test Main - Win32 DebugWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugWxMTD"
# PROP BASE Intermediate_Dir "DebugWxMTD"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugWxMTD-6.0"
# PROP Intermediate_Dir "DebugWxMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(WXWIN)/lib/vc_lib/mswd" /I "$(WXWIN)/include" /I "../../include" /I "$(RICHBOOL)/include" /I "../Common" /D "__WXDEBUG__" /D WXDEBUG=1 /D "_DEBUG" /D "RICHBOOL_USE_WX" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FD /GZ /Zm200 /Zm250 /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib richbool.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)\DebugMTD"
# ADD LINK32 comctl32.lib rpcrt4.lib wsock32.lib wxmsw28d_adv.lib wxmsw28d_core.lib wxbase28d.lib wxtiffd.lib wxjpegd.lib wxpngd.lib wxzlibd.lib wxregexd.lib wxexpatd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(WXWIN)/lib/vc_lib" /libpath:"$(RICHBOOL)/lib" /libpath:"../../lib"
# Begin Special Build Tool
TargetPath=.\DebugWxMTD-6.0\TestMain.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Test Main - Win32 ReleaseWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseWxMTD"
# PROP BASE Intermediate_Dir "ReleaseWxMTD"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseWxMTD-6.0"
# PROP Intermediate_Dir "ReleaseWxMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(WXWIN)/lib/vc_lib/msw" /I "$(WXWIN)/include" /I "../../include" /I "$(RICHBOOL)/include" /I "../Common" /D "NDEBUG" /D "RICHBOOL_USE_WX" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FD /Zm200 /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib richbool.lib /nologo /subsystem:console /machine:I386 /libpath:"$(RICHBOOL)\ReleaseMTD"
# ADD LINK32 comctl32.lib rpcrt4.lib wsock32.lib wxmsw28_adv.lib wxmsw28_core.lib wxbase28.lib wxtiff.lib wxjpeg.lib wxpng.lib wxzlib.lib wxregex.lib wxexpat.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /libpath:"$(WXWIN)/lib/vc_lib" /libpath:"$(RICHBOOL)/lib" /libpath:"../../lib"
# Begin Special Build Tool
TargetPath=.\ReleaseWxMTD-6.0\TestMain.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Test Main - Win32 DebugMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMT"
# PROP BASE Intermediate_Dir "DebugMT"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMT-6.0"
# PROP Intermediate_Dir "DebugMT-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../include" /I "$(RICHBOOL)/include" /I "../Common" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D MOD_ASSERT_LEVEL=1 /FD /GZ /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../include" /I "$(RICHBOOL)/include" /I "../Common" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FD /GZ /Zm200 /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib richbool.lib modassert.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)\DebugMT" /libpath:"../../DebugMT"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)/lib" /libpath:"../../lib"
# Begin Special Build Tool
TargetPath=.\DebugMT-6.0\TestMain.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Test Main - Win32 ReleaseMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMT"
# PROP BASE Intermediate_Dir "ReleaseMT"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMT-6.0"
# PROP Intermediate_Dir "ReleaseMT-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../../include" /I "$(RICHBOOL)/include" /I "../Common" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D MOD_ASSERT_LEVEL=1 /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../../include" /I "$(RICHBOOL)/include" /I "../Common" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "MOD_ASSERT_REPORT" /FD /Zm200 /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib richbool.lib modassert.lib /nologo /subsystem:console /machine:I386 /libpath:"$(RICHBOOL)\ReleaseMT" /libpath:"../../ReleaseMT"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /libpath:"$(RICHBOOL)/lib" /libpath:"../../lib"
# Begin Special Build Tool
TargetPath=.\ReleaseMT-6.0\TestMain.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Test Main - Win32 DebugST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugST"
# PROP BASE Intermediate_Dir "DebugST"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugST-6.0"
# PROP Intermediate_Dir "DebugST-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../include" /I "$(RICHBOOL)/include" /I "../Common" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D MOD_ASSERT_LEVEL=1 /FD /GZ /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../include" /I "$(RICHBOOL)/include" /I "../Common" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FD /GZ /Zm200 /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib richbool.lib modassert.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)\DebugMTD" /libpath:"../../DebugMTD"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)/lib" /libpath:"../../lib"
# Begin Special Build Tool
TargetPath=.\DebugST-6.0\TestMain.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Test Main - Win32 ReleaseST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseST"
# PROP BASE Intermediate_Dir "ReleaseST"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseST-6.0"
# PROP Intermediate_Dir "ReleaseST-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "../../include" /I "$(RICHBOOL)/include" /I "../Common" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D MOD_ASSERT_LEVEL=1 /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /W3 /GX /O2 /I "../../include" /I "$(RICHBOOL)/include" /I "../Common" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FD /Zm200 /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib richbool.lib modassert.lib /nologo /subsystem:console /machine:I386 /libpath:"$(RICHBOOL)\ReleaseMTD" /libpath:"../../ReleaseMTD"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /libpath:"$(RICHBOOL)/lib" /libpath:"../../lib"
# Begin Special Build Tool
TargetPath=.\ReleaseST-6.0\TestMain.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Testing...
PostBuild_Cmds=$(TARGETPATH)
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Test Main - Win32 ReleaseMTD"
# Name "Test Main - Win32 DebugMTD"
# Name "Test Main - Win32 DebugWxMTD"
# Name "Test Main - Win32 ReleaseWxMTD"
# Name "Test Main - Win32 DebugMT"
# Name "Test Main - Win32 ReleaseMT"
# Name "Test Main - Win32 DebugST"
# Name "Test Main - Win32 ReleaseST"
# Begin Group "Helper code"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Common\CreateList.h
# End Source File
# Begin Source File

SOURCE=..\Common\GetStreamString.h
# End Source File
# Begin Source File

SOURCE=..\Common\ScopedSetReturnValue.h
# End Source File
# Begin Source File

SOURCE=..\Common\StubHook.h
# End Source File
# Begin Source File

SOURCE=..\Common\StubLogger.h
# End Source File
# End Group
# Begin Group "Tests"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TestAllowResponses.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssert.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssert1DefaultParam.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssert2DefaultParams.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssertD.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssertDontReportFile.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssertInIf.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssertLevel1.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssertLevel3.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssertLevel3Check.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssertLogger.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssertOffCheckOff.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssertOffCheckOn.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssertOnCheckOff.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssertOnCheckOn.cpp
# End Source File
# Begin Source File

SOURCE=.\TestAssertReportFile.cpp
# End Source File
# Begin Source File

SOURCE=.\TestCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\TestCheck1DefaultParam.cpp
# End Source File
# Begin Source File

SOURCE=.\TestCheck2DefaultParams.cpp
# End Source File
# Begin Source File

SOURCE=.\TestCheckDontReportFile.cpp
# End Source File
# Begin Source File

SOURCE=.\TestCheckLevel1.cpp
# End Source File
# Begin Source File

SOURCE=.\TestCheckLevel3.cpp
# End Source File
# Begin Source File

SOURCE=.\TestCheckLevel3Assert.cpp
# End Source File
# Begin Source File

SOURCE=.\TestCheckReportFile.cpp
# End Source File
# Begin Source File

SOURCE=.\TestCombinedTypes.cpp
# End Source File
# Begin Source File

SOURCE=.\TestContext.cpp
# End Source File
# Begin Source File

SOURCE=.\TestDefaultGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\TestDefaultOptionalAction.cpp
# End Source File
# Begin Source File

SOURCE=.\TestDisabled.cpp
# End Source File
# Begin Source File

SOURCE=.\TestEnabled.cpp
# End Source File
# Begin Source File

SOURCE=.\TestExpressions.cpp
# End Source File
# Begin Source File

SOURCE=.\TestFilters.cpp
# End Source File
# Begin Source File

SOURCE=.\TestGetLevel.cpp
# End Source File
# Begin Source File

SOURCE=.\TestGroups.cpp
# End Source File
# Begin Source File

SOURCE=.\TestHook.cpp
# End Source File
# Begin Source File

SOURCE=.\TestIfSuccess.cpp
# End Source File
# Begin Source File

SOURCE=.\TestIfTypeReports.hpp
# End Source File
# Begin Source File

SOURCE=.\TestIgnore.cpp
# End Source File
# Begin Source File

SOURCE=.\TestLevelToString.cpp
# End Source File
# Begin Source File

SOURCE=.\TestLoggerId.cpp
# End Source File
# Begin Source File

SOURCE=.\TestLoggerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\TestNoText.cpp
# End Source File
# Begin Source File

SOURCE=.\TestOptionalAction.cpp
# End Source File
# Begin Source File

SOURCE=.\TestOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\TestParamList.cpp
# End Source File
# Begin Source File

SOURCE=.\TestParamListWithCommas.cpp
# End Source File
# Begin Source File

SOURCE=.\TestResponderSwitcher.cpp
# End Source File
# Begin Source File

SOURCE=.\TestSetOptionalAction.cpp
# End Source File
# Begin Source File

SOURCE=.\TestSetOptionalLogger.cpp
# End Source File
# Begin Source File

SOURCE=.\TestSideEffects.cpp
# End Source File
# Begin Source File

SOURCE=.\TestStreamLogger.cpp
# End Source File
# Begin Source File

SOURCE=.\TestStreamLogger_NoText.cpp
# End Source File
# Begin Source File

SOURCE=.\TestThreadSafety.cpp
# End Source File
# Begin Source File

SOURCE=.\TestUseBool.cpp
# End Source File
# Begin Source File

SOURCE=.\TestUseDrive.cpp
# End Source File
# Begin Source File

SOURCE=.\TestVerifyV.cpp
# End Source File
# Begin Source File

SOURCE=.\TestVersion.cpp
# End Source File
# Begin Source File

SOURCE=.\TestWxAssert.cpp
# End Source File
# End Group
# Begin Group "Test framework"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Common\main.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\ModAssertTest.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\ModAssertTest.h
# End Source File
# End Group
# End Target
# End Project
