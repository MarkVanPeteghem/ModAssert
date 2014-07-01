# Microsoft Developer Studio Project File - Name="DemoLibInExe" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=DemoLibInExe - Win32 DebugWxMTD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DemoLibInExe.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DemoLibInExe.mak" CFG="DemoLibInExe - Win32 DebugWxMTD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DemoLibInExe - Win32 ReleaseMTD" (based on "Win32 (x86) Console Application")
!MESSAGE "DemoLibInExe - Win32 DebugMTD" (based on "Win32 (x86) Console Application")
!MESSAGE "DemoLibInExe - Win32 ReleaseMT" (based on "Win32 (x86) Console Application")
!MESSAGE "DemoLibInExe - Win32 ReleaseST" (based on "Win32 (x86) Console Application")
!MESSAGE "DemoLibInExe - Win32 DebugMT" (based on "Win32 (x86) Console Application")
!MESSAGE "DemoLibInExe - Win32 DebugST" (based on "Win32 (x86) Console Application")
!MESSAGE "DemoLibInExe - Win32 DebugWxMTD" (based on "Win32 (x86) Console Application")
!MESSAGE "DemoLibInExe - Win32 ReleaseWxMTD" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DemoLibInExe - Win32 ReleaseMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMTD"
# PROP BASE Intermediate_Dir "ReleaseMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMTD-6.0"
# PROP Intermediate_Dir "ReleaseMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib DemoLibInExe_AssertionInDLL-vc6-mt.lib /nologo /subsystem:console /machine:I386 /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"

!ELSEIF  "$(CFG)" == "DemoLibInExe - Win32 DebugMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMTD"
# PROP BASE Intermediate_Dir "DebugMTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMTD-6.0"
# PROP Intermediate_Dir "DebugMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib DemoLibInExe_AssertionInDLL-vc6-mt-gd.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"

!ELSEIF  "$(CFG)" == "DemoLibInExe - Win32 ReleaseMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMT"
# PROP BASE Intermediate_Dir "ReleaseMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMT-6.0"
# PROP Intermediate_Dir "ReleaseMT-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(MODASSERT)/Console" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib richbool.lib modassert.lib /nologo /subsystem:console /machine:I386 /libpath:"$(RICHBOOL)\ReleaseMTD" /libpath:"$(MODASSERT)/ReleaseMTD"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib DemoLibInExe_AssertionInDLL-vc6-mt-s.lib /nologo /subsystem:console /machine:I386 /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"

!ELSEIF  "$(CFG)" == "DemoLibInExe - Win32 ReleaseST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseST"
# PROP BASE Intermediate_Dir "ReleaseST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseST-6.0"
# PROP Intermediate_Dir "ReleaseST-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(MODASSERT)/Console" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib richbool.lib modassert.lib /nologo /subsystem:console /machine:I386 /libpath:"$(RICHBOOL)\ReleaseMTD" /libpath:"$(MODASSERT)/ReleaseMTD"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib DemoLibInExe_AssertionInDLL-vc6-s.lib /nologo /subsystem:console /machine:I386 /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"

!ELSEIF  "$(CFG)" == "DemoLibInExe - Win32 DebugMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugMT"
# PROP BASE Intermediate_Dir "DebugMT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugMT-6.0"
# PROP Intermediate_Dir "DebugMT-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(MODASSERT)/Console" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib richbool.lib modassert.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)\DebugMTD" /libpath:"$(MODASSERT)/DebugMTD"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib DemoLibInExe_AssertionInDLL-vc6-mt-sgd.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"

!ELSEIF  "$(CFG)" == "DemoLibInExe - Win32 DebugST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugST"
# PROP BASE Intermediate_Dir "DebugST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugST-6.0"
# PROP Intermediate_Dir "DebugST-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(MODASSERT)/Console" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib richbool.lib modassert.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)\DebugMTD" /libpath:"$(MODASSERT)/DebugMTD"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib DemoLibInExe_AssertionInDLL-vc6-sgd.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"

!ELSEIF  "$(CFG)" == "DemoLibInExe - Win32 DebugWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DemoLibInExe___Win32_Debug_Wx_MTD"
# PROP BASE Intermediate_Dir "DemoLibInExe___Win32_Debug_Wx_MTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugWxMTD-6.0"
# PROP Intermediate_Dir "DebugWxMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(WXWIN)/lib/vc_lib/mswd" /I "$(WXWIN)/include" /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "RICHBOOL_USE_WX" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib DemoLibInExe_AssertionInDLL-vc6-mt-gd-wx.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(WXWIN)/lib/vc_lib" /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"

!ELSEIF  "$(CFG)" == "DemoLibInExe - Win32 ReleaseWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "DemoLibInExe___Win32_Release_Wx_MTD"
# PROP BASE Intermediate_Dir "DemoLibInExe___Win32_Release_Wx_MTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseWxMTD-6.0"
# PROP Intermediate_Dir "ReleaseWxMTD-6.0"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(WXWIN)/lib/vc_lib/msw" /I "$(WXWIN)/include" /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "RICHBOOL_USE_WX" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /machine:I386 /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib DemoLibInExe_AssertionInDLL-vc6-mt-wx.lib /nologo /subsystem:console /machine:I386 /libpath:"$(WXWIN)/lib/vc_lib" /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)/lib"

!ENDIF 

# Begin Target

# Name "DemoLibInExe - Win32 ReleaseMTD"
# Name "DemoLibInExe - Win32 DebugMTD"
# Name "DemoLibInExe - Win32 ReleaseMT"
# Name "DemoLibInExe - Win32 ReleaseST"
# Name "DemoLibInExe - Win32 DebugMT"
# Name "DemoLibInExe - Win32 DebugST"
# Name "DemoLibInExe - Win32 DebugWxMTD"
# Name "DemoLibInExe - Win32 ReleaseWxMTD"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# End Group
# End Target
# End Project
