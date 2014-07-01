# Microsoft Developer Studio Project File - Name="ModAssertWxGui" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ModAssertWxGui - Win32 DebugWx MT
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ModAssertWxGui.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ModAssertWxGui.mak" CFG="ModAssertWxGui - Win32 DebugWx MT"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ModAssertWxGui - Win32 DebugWxMTD" (based on "Win32 (x86) Static Library")
!MESSAGE "ModAssertWxGui - Win32 ReleaseWxMTD" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ModAssertWxGui - Win32 DebugWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugWxMTD"
# PROP BASE Intermediate_Dir "DebugWxMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "DebugWxMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./" /I "../include" /I "$(RICHBOOL)/include" /I "$(WXWIN)/lib/vc_lib/mswd" /I "$(WXWIN)/include" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "RICHBOOL_USE_WX" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertGui-vc6-mt-gd-wx-2_0_5.lib"

!ELSEIF  "$(CFG)" == "ModAssertWxGui - Win32 ReleaseWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseWxMTD"
# PROP BASE Intermediate_Dir "ReleaseWxMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../lib"
# PROP Intermediate_Dir "ReleaseWxMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "./" /I "../include" /I "$(RICHBOOL)/include" /I "$(WXWIN)/lib/vc_lib/mswd" /I "$(WXWIN)/include" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "RICHBOOL_USE_WX" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../lib/libmodassertGui-vc6-mt-wx-2_0_5.lib"

!ENDIF 

# Begin Target

# Name "ModAssertWxGui - Win32 DebugWxMTD"
# Name "ModAssertWxGui - Win32 ReleaseWxMTD"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\wxcurrentdirectory.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\wxcurrentdirectory.hpp
# End Source File
# Begin Source File

SOURCE=.\wxdisplayer.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\wxdisplayer.hpp
# End Source File
# Begin Source File

SOURCE=.\wxdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\wxdlg.hpp
# End Source File
# Begin Source File

SOURCE=.\wxfreememory.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\wxfreememory.hpp
# End Source File
# Begin Source File

SOURCE=.\wxhandler.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\wxhandler.hpp
# End Source File
# Begin Source File

SOURCE=.\wxlog.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\wxlog.hpp
# End Source File
# Begin Source File

SOURCE=.\wxosversion.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\wxosversion.hpp
# End Source File
# Begin Source File

SOURCE=.\wxprocessid.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\wxprocessid.hpp
# End Source File
# Begin Source File

SOURCE=.\wxsyserror.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\wxsyserror.hpp
# End Source File
# Begin Source File

SOURCE=.\wxterminatemessage.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\wxterminatemessage.hpp
# End Source File
# Begin Source File

SOURCE=.\wxthreadid.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\wxthreadid.hpp
# End Source File
# Begin Source File

SOURCE=.\wxwarningmessage.cpp
# End Source File
# Begin Source File

SOURCE=..\include\modassert\wxwarningmessage.hpp
# End Source File
# End Group
# End Target
# End Project
