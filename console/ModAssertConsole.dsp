# Microsoft Developer Studio Project File - Name="ModAssertConsole" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ModAssertConsole - Win32 DebugWxMTD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ModAssertConsole.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ModAssertConsole.mak" CFG="ModAssertConsole - Win32 DebugWxMTD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ModAssertConsole - Win32 DebugST" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssertConsole - Win32 ReleaseST" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssertConsole - Win32 DebugMT" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssertConsole - Win32 ReleaseMT" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssertConsole - Win32 DebugMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssertConsole - Win32 ReleaseMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssertConsole - Win32 ReleaseWxMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssertConsole - Win32 DebugWxMTD" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ModAssertConsole - Win32 DebugST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_ST"
# PROP BASE Intermediate_Dir "Debug_ST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "DebugST-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertConsole-vc6-sgd-2_0_5.lib"

!ELSEIF  "$(CFG)" == "ModAssertConsole - Win32 ReleaseST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_ST"
# PROP BASE Intermediate_Dir "Release_ST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "ReleaseST-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertConsole-vc6-s-2_0_5.lib"

!ELSEIF  "$(CFG)" == "ModAssertConsole - Win32 DebugMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_MT"
# PROP BASE Intermediate_Dir "Debug_MT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "DebugMT-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertConsole-vc6-mt-sgd-2_0_5.lib"

!ELSEIF  "$(CFG)" == "ModAssertConsole - Win32 ReleaseMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_MT"
# PROP BASE Intermediate_Dir "Release_MT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "ReleaseMT-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertConsole-vc6-mt-s-2_0_5.lib"

!ELSEIF  "$(CFG)" == "ModAssertConsole - Win32 DebugMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_MTD"
# PROP BASE Intermediate_Dir "Debug_MTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "DebugMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertConsole-vc6-mt-gd-2_0_5.lib"

!ELSEIF  "$(CFG)" == "ModAssertConsole - Win32 ReleaseMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_MTD"
# PROP BASE Intermediate_Dir "Release_MTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "ReleaseMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertConsole-vc6-mt-2_0_5.lib"

!ELSEIF  "$(CFG)" == "ModAssertConsole - Win32 ReleaseWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_Wx_MTD"
# PROP BASE Intermediate_Dir "Release_Wx_MTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "ReleaseWxMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /I "$(WXWIN)/include" /I "$(WXWIN)/lib/vc_lib/mswd" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "RICHBOOL_USE_WX" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertConsole-vc6-mt-wx-2_0_5.lib"

!ELSEIF  "$(CFG)" == "ModAssertConsole - Win32 DebugWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_Wx_MTD"
# PROP BASE Intermediate_Dir "Debug_Wx_MTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "DebugWxMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /I "$(WXWIN)/include" /I "$(WXWIN)/lib/vc_lib/mswd" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "RICHBOOL_USE_WX" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertConsole-vc6-mt-gd-wx-2_0_5.lib"

!ENDIF 

# Begin Target

# Name "ModAssertConsole - Win32 DebugST"
# Name "ModAssertConsole - Win32 ReleaseST"
# Name "ModAssertConsole - Win32 DebugMT"
# Name "ModAssertConsole - Win32 ReleaseMT"
# Name "ModAssertConsole - Win32 DebugMTD"
# Name "ModAssertConsole - Win32 ReleaseMTD"
# Name "ModAssertConsole - Win32 ReleaseWxMTD"
# Name "ModAssertConsole - Win32 DebugWxMTD"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\consoledisplayer.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\consoledisplayer.hpp
# End Source File
# Begin Source File

SOURCE=.\src\consolehandler.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\consolehandler.hpp
# End Source File
# Begin Source File

SOURCE=.\src\consoleterminate.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\consoleterminate.hpp
# End Source File
# Begin Source File

SOURCE=.\src\consolewarning.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\consolewarning.hpp
# End Source File
# End Group
# End Target
# End Project
