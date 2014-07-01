# Microsoft Developer Studio Project File - Name="ModAssert" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ModAssert - Win32 DebugWxMTD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ModAssert.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ModAssert.mak" CFG="ModAssert - Win32 DebugWxMTD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ModAssert - Win32 ReleaseMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssert - Win32 DebugMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssert - Win32 ReleaseWxMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssert - Win32 DebugWxMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssert - Win32 DebugMT" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssert - Win32 ReleaseMT" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssert - Win32 DebugST" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssert - Win32 ReleaseST" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ModAssert - Win32 ReleaseMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMTD"
# PROP BASE Intermediate_Dir "ReleaseMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "ReleaseMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/libmodassert-vc6-mt-2_0_6.lib"

!ELSEIF  "$(CFG)" == "ModAssert - Win32 DebugMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMTD"
# PROP BASE Intermediate_Dir "DebugMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "DebugMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/libmodassert-vc6-mt-gd-2_0_6.lib"

!ELSEIF  "$(CFG)" == "ModAssert - Win32 ReleaseWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseWxMTD"
# PROP BASE Intermediate_Dir "ReleaseWxMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "ReleaseWxMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include" /I "$(RICHBOOL)/include" /I "$(WXWIN)/include" /I "$(WXWIN)/lib/vc_lib/msw" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "RICHBOOL_USE_WX" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/libmodassert-vc6-mt-wx-2_0_6.lib"

!ELSEIF  "$(CFG)" == "ModAssert - Win32 DebugWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugWxMTD"
# PROP BASE Intermediate_Dir "DebugWxMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "DebugWxMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /I "$(RICHBOOL)/include" /I "$(WXWIN)/include" /I "$(WXWIN)/lib/vc_lib/mswd" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "RICHBOOL_USE_WX" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/libmodassert-vc6-mt-gd-wx-2_0_6.lib"

!ELSEIF  "$(CFG)" == "ModAssert - Win32 DebugMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMT"
# PROP BASE Intermediate_Dir "DebugMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "DebugMT-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/libmodassert-vc6-mt-sgd-2_0_6.lib"

!ELSEIF  "$(CFG)" == "ModAssert - Win32 ReleaseMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMT"
# PROP BASE Intermediate_Dir "ReleaseMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "ReleaseMT-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/libmodassert-vc6-mt-s-2_0_6.lib"

!ELSEIF  "$(CFG)" == "ModAssert - Win32 DebugST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugST"
# PROP BASE Intermediate_Dir "DebugST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "DebugST-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/libmodassert-vc6-sgd-2_0_6.lib"

!ELSEIF  "$(CFG)" == "ModAssert - Win32 ReleaseST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseST"
# PROP BASE Intermediate_Dir "ReleaseST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "./lib"
# PROP Intermediate_Dir "ReleaseST-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib/libmodassert-vc6-s-2_0_6.lib"

!ENDIF 

# Begin Target

# Name "ModAssert - Win32 ReleaseMTD"
# Name "ModAssert - Win32 DebugMTD"
# Name "ModAssert - Win32 ReleaseWxMTD"
# Name "ModAssert - Win32 DebugWxMTD"
# Name "ModAssert - Win32 DebugMT"
# Name "ModAssert - Win32 ReleaseMT"
# Name "ModAssert - Win32 DebugST"
# Name "ModAssert - Win32 ReleaseST"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\appinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\appinfo.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\assert.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\autoresponder.hpp
# End Source File
# Begin Source File

SOURCE=.\src\categories.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\categories.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\category.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\categorybase.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\combine_groups.hpp
# End Source File
# Begin Source File

SOURCE=.\src\context.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\context.hpp
# End Source File
# Begin Source File

SOURCE=.\src\filters.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\filters.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\group.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\grouplst.hpp
# End Source File
# Begin Source File

SOURCE=.\src\handler.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\handler.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\hook.hpp
# End Source File
# Begin Source File

SOURCE=.\src\ifsuccess.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\ifsuccess.hpp
# End Source File
# Begin Source File

SOURCE=.\src\info.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\info.hpp
# End Source File
# Begin Source File

SOURCE=.\src\infostore.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\infostore.hpp
# End Source File
# Begin Source File

SOURCE=.\src\infouser.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\infouser.hpp
# End Source File
# Begin Source File

SOURCE=.\src\levels.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\levels.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\linkcore.hpp
# End Source File
# Begin Source File

SOURCE=.\src\logger.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\logger.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\logtype.hpp
# End Source File
# Begin Source File

SOURCE=.\src\parmlist.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\parmlist.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\properties.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\report_data.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\report_type.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\responder.hpp
# End Source File
# Begin Source File

SOURCE=.\src\responder_switcher.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\responder_switcher.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\response.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\result.hpp
# End Source File
# Begin Source File

SOURCE=.\src\strmlog.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\strmlog.hpp
# End Source File
# Begin Source File

SOURCE=.\src\terminate_message.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\terminate_message.hpp
# End Source File
# Begin Source File

SOURCE=.\src\threads.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\threads.hpp
# End Source File
# Begin Source File

SOURCE=.\src\timeinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\timeinfo.hpp
# End Source File
# Begin Source File

SOURCE=.\src\use_bool.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\use_bool.hpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\version.hpp
# End Source File
# Begin Source File

SOURCE=.\src\warning_message.cpp
# End Source File
# Begin Source File

SOURCE=.\include\modassert\warning_message.hpp
# End Source File
# End Group
# End Target
# End Project
