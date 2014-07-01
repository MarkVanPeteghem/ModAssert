# Microsoft Developer Studio Project File - Name="DemoMFC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DemoMFC - Win32 ReleaseMTD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DemoMFC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DemoMFC.mak" CFG="DemoMFC - Win32 ReleaseMTD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DemoMFC - Win32 ReleaseMTD" (based on "Win32 (x86) Application")
!MESSAGE "DemoMFC - Win32 DebugMTD" (based on "Win32 (x86) Application")
!MESSAGE "DemoMFC - Win32 DebugMT" (based on "Win32 (x86) Application")
!MESSAGE "DemoMFC - Win32 ReleaseMT" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DemoMFC - Win32 ReleaseMTD"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMTD"
# PROP BASE Intermediate_Dir "ReleaseMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMTD-6.0"
# PROP Intermediate_Dir "ReleaseMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x813 /i "$(MODASSERT)/Win32" /i "$(MODASSERT)/include" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"

!ELSEIF  "$(CFG)" == "DemoMFC - Win32 DebugMTD"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMTD"
# PROP BASE Intermediate_Dir "DebugMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMTD-6.0"
# PROP Intermediate_Dir "DebugMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x813 /i "$(MODASSERT)/Win32" /i "$(MODASSERT)/include" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"nafxcwd.lib" /pdbtype:sept /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"

!ELSEIF  "$(CFG)" == "DemoMFC - Win32 DebugMT"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMT"
# PROP BASE Intermediate_Dir "DebugMT"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMT-6.0"
# PROP Intermediate_Dir "DebugMT-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(MODASSERT)/MFC" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /i "$(MODASSERT)/MFC" /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x813 /i "$(MODASSERT)/Win32" /i "$(MODASSERT)/include" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 richbool.lib modassert.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)/DebugMTD" /libpath:"$(MODASSERT)/DebugMTD"
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"

!ELSEIF  "$(CFG)" == "DemoMFC - Win32 ReleaseMT"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMT"
# PROP BASE Intermediate_Dir "ReleaseMT"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMT-6.0"
# PROP Intermediate_Dir "ReleaseMT-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(MODASSERT)/MFC" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x813 /i "$(MODASSERT)/MFC" /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x813 /i "$(MODASSERT)/Win32" /i "$(MODASSERT)/include" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 richbool.lib modassert.lib /nologo /subsystem:windows /machine:I386 /libpath:"$(RICHBOOL)/ReleaseMTD" /libpath:"$(MODASSERT)/ReleaseMTD"
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"

!ENDIF 

# Begin Target

# Name "DemoMFC - Win32 ReleaseMTD"
# Name "DemoMFC - Win32 DebugMTD"
# Name "DemoMFC - Win32 DebugMT"
# Name "DemoMFC - Win32 ReleaseMT"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DemoMFC.cpp
# End Source File
# Begin Source File

SOURCE=.\DemoMFC.h
# End Source File
# Begin Source File

SOURCE=.\DemoMFC.rc
# End Source File
# Begin Source File

SOURCE=.\DemoMFCDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DemoMFCDlg.h
# End Source File
# Begin Source File

SOURCE=.\NoText.cpp
# End Source File
# Begin Source File

SOURCE=.\OtherFile.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DemoMFC.ico
# End Source File
# Begin Source File

SOURCE=.\res\DemoMFC.rc2
# End Source File
# End Group
# End Target
# End Project
