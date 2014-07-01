# Microsoft Developer Studio Project File - Name="ModAssertWin32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ModAssertWin32 - Win32 DebugST
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ModAssertWin32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ModAssertWin32.mak" CFG="ModAssertWin32 - Win32 DebugST"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ModAssertWin32 - Win32 DebugMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssertWin32 - Win32 ReleaseMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssertWin32 - Win32 DebugMT" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssertWin32 - Win32 ReleaseMT" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssertWin32 - Win32 DebugST" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssertWin32 - Win32 ReleaseST" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ModAssertWin32 - Win32 DebugMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMTD"
# PROP BASE Intermediate_Dir "DebugMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "DebugMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./" /I "../include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /i "$(MODASSERT)/include" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertWin32-vc6-mt-gd-2_0_5.lib"

!ELSEIF  "$(CFG)" == "ModAssertWin32 - Win32 ReleaseMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMTD"
# PROP BASE Intermediate_Dir "ReleaseMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "ReleaseMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include" /I "./" /I "../include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /i "$(MODASSERT)/include" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertWin32-vc6-mt-2_0_5.lib"

!ELSEIF  "$(CFG)" == "ModAssertWin32 - Win32 DebugMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMT"
# PROP BASE Intermediate_Dir "DebugMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "DebugMT-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /I "./" /I "../include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /i "$(MODASSERT)/include" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertWin32-vc6-mt-sgd-2_0_5.lib"

!ELSEIF  "$(CFG)" == "ModAssertWin32 - Win32 ReleaseMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMT"
# PROP BASE Intermediate_Dir "ReleaseMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "ReleaseMT-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "include" /I "./" /I "../include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /i "$(MODASSERT)/include" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertWin32-vc6-mt-s-2_0_5.lib"

!ELSEIF  "$(CFG)" == "ModAssertWin32 - Win32 DebugST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugST"
# PROP BASE Intermediate_Dir "DebugST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "DebugST-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./" /I "../include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "./" /I "../include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /i "$(MODASSERT)/include" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertWin32-vc6-sgd-2_0_5.lib"

!ELSEIF  "$(CFG)" == "ModAssertWin32 - Win32 ReleaseST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseST"
# PROP BASE Intermediate_Dir "ReleaseST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "ReleaseST-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "include" /I "./" /I "../include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /i "$(MODASSERT)/include" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertWin32-vc6-s-2_0_5.lib"

!ENDIF 

# Begin Target

# Name "ModAssertWin32 - Win32 DebugMTD"
# Name "ModAssertWin32 - Win32 ReleaseMTD"
# Name "ModAssertWin32 - Win32 DebugMT"
# Name "ModAssertWin32 - Win32 ReleaseMT"
# Name "ModAssertWin32 - Win32 DebugST"
# Name "ModAssertWin32 - Win32 ReleaseST"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\include\modassert\modassert.rc
# End Source File
# Begin Source File

SOURCE=..\include\modassert\resource.h
# End Source File
# Begin Source File

SOURCE=.\src\Win32ComputerName.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32ComputerName.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32CurrentDirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32CurrentDirectory.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32DiskSpace.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32DiskSpace.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32Displayer.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32Displayer.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32Dlg.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32Dlg.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32Handler.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32Handler.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32LastError.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32LastError.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32MemoryStatus.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32MemoryStatus.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32OSVersion.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32OSVersion.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32ProcessId.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32Processid.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32Processor.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32Processor.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32TerminateMessage.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32TerminateMessage.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32ThreadId.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32ThreadId.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32Trace.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32Trace.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32UserName.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32UserName.hpp
# End Source File
# Begin Source File

SOURCE=.\src\Win32WarningMessage.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\Win32WarningMessage.hpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\include\modassert\modassert\ModAssertF.ico
# End Source File
# Begin Source File

SOURCE=..\include\modassert\modassert\ModAssertS.ico
# End Source File
# End Target
# End Project
