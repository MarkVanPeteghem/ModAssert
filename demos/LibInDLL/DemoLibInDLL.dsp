# Microsoft Developer Studio Project File - Name="DemoLibInDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=DemoLibInDLL - Win32 DebugWxMTD
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DemoLibInDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DemoLibInDLL.mak" CFG="DemoLibInDLL - Win32 DebugWxMTD"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DemoLibInDLL - Win32 DebugST" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DemoLibInDLL - Win32 ReleaseST" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DemoLibInDLL - Win32 DebugMT" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DemoLibInDLL - Win32 ReleaseMT" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DemoLibInDLL - Win32 DebugMTD" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DemoLibInDLL - Win32 ReleaseMTD" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DemoLibInDLL - Win32 ReleaseWxMTD" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "DemoLibInDLL - Win32 DebugWxMTD" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DemoLibInDLL - Win32 DebugST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_ST"
# PROP BASE Intermediate_Dir "Debug_ST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "DebugST-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib shell32.lib ole32.lib richbool.lib modassert.lib /nologo /dll /machine:I386 /out:"DemoLibInDLL.dll" /libpath:"$(RICHBOOL)\DebugMTD" /libpath:"$(MODASSERT)\DebugMTD"
# ADD LINK32 user32.lib shell32.lib ole32.lib advapi32.lib kernel32.lib /nologo /entry:"" /dll /map:"$(OutDir)/DemoLibInDLL.map" /machine:I386 /out:"DemoLibInDLL-vc6-sgd.dll" /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)\lib"

!ELSEIF  "$(CFG)" == "DemoLibInDLL - Win32 ReleaseST"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_ST"
# PROP BASE Intermediate_Dir "Release_ST"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "ReleaseST-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib shell32.lib ole32.lib richbool.lib modassert.lib /nologo /dll /machine:I386 /out:"DemoLibInDLL.dll" /libpath:"$(RICHBOOL)\DebugMTD" /libpath:"$(MODASSERT)\DebugMTD"
# ADD LINK32 user32.lib shell32.lib ole32.lib advapi32.lib kernel32.lib /nologo /entry:"" /dll /map:"$(OutDir)/DemoLibInDLL.map" /machine:I386 /out:"DemoLibInDLL-vc6-s.dll" /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)\lib"

!ELSEIF  "$(CFG)" == "DemoLibInDLL - Win32 DebugMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_MT"
# PROP BASE Intermediate_Dir "Debug_MT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "DebugMT-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib shell32.lib ole32.lib richbool.lib modassert.lib /nologo /dll /machine:I386 /out:"DemoLibInDLL-vc6-mt-sgd.dll" /libpath:"$(RICHBOOL)\DebugMTD" /libpath:"$(MODASSERT)\DebugMTD"
# ADD LINK32 user32.lib shell32.lib ole32.lib advapi32.lib kernel32.lib /nologo /entry:"" /dll /map:"$(OutDir)/DemoLibInDLL.map" /machine:I386 /out:"DemoLibInDLL-vc6-mt-sgd.dll" /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)\lib"

!ELSEIF  "$(CFG)" == "DemoLibInDLL - Win32 ReleaseMT"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_MT"
# PROP BASE Intermediate_Dir "Release_MT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "ReleaseMT-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib shell32.lib ole32.lib richbool.lib modassert.lib /nologo /dll /machine:I386 /out:"DemoLibInDLL.dll" /libpath:"$(RICHBOOL)\DebugMTD" /libpath:"$(MODASSERT)\DebugMTD"
# ADD LINK32 user32.lib shell32.lib ole32.lib advapi32.lib kernel32.lib /nologo /entry:"" /dll /map:"$(OutDir)/DemoLibInDLL.map" /machine:I386 /out:"DemoLibInDLL-vc6-mt-s.dll" /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)\lib"

!ELSEIF  "$(CFG)" == "DemoLibInDLL - Win32 DebugMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_MTD"
# PROP BASE Intermediate_Dir "Debug_MTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "DebugMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /YX /FD /GZ /c
# SUBTRACT CPP /O<none>
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib shell32.lib ole32.lib richbool.lib modassert.lib /nologo /dll /machine:I386 /out:"DemoLibInDLL.dll" /libpath:"$(RICHBOOL)\DebugMTD" /libpath:"$(MODASSERT)\DebugMTD"
# ADD LINK32 user32.lib shell32.lib ole32.lib advapi32.lib kernel32.lib /nologo /entry:"" /dll /map:"$(OutDir)/DemoLibInDLL.map" /debug /machine:I386 /out:"DemoLibInDLL-vc6-mt-gd.dll" /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)\lib"

!ELSEIF  "$(CFG)" == "DemoLibInDLL - Win32 ReleaseMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_MTD"
# PROP BASE Intermediate_Dir "Release_MTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "ReleaseMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib shell32.lib ole32.lib richbool.lib modassert.lib /nologo /dll /machine:I386 /out:"DemoLibInDLL.dll" /libpath:"$(RICHBOOL)\DebugMTD" /libpath:"$(MODASSERT)\DebugMTD"
# ADD LINK32 user32.lib shell32.lib ole32.lib advapi32.lib kernel32.lib /nologo /entry:"" /dll /map:"$(OutDir)/DemoLibInDLL.map" /machine:I386 /out:"DemoLibInDLL-vc6-mt.dll" /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)\lib"

!ELSEIF  "$(CFG)" == "DemoLibInDLL - Win32 ReleaseWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_Wx_MTD"
# PROP BASE Intermediate_Dir "Release_Wx_MTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "ReleaseWxMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_USRDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /I "$(WXWIN)/include" /I "$(WXWIN)/lib/vc_lib/mswd" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_USRDLL" /D "RICHBOOL_USE_WX" /D "DLL_EXPORTS" /YX /FD /c
# ADD BASE RSC /l 0x813 /d "NDEBUG"
# ADD RSC /l 0x813 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib shell32.lib ole32.lib richbool.lib modassert.lib wxbase28d.lib /nologo /dll /machine:I386 /out:"DemoLibInDLL.dll" /libpath:"$(RICHBOOL)\DebugMTD" /libpath:"$(MODASSERT)\DebugMTD" /libpath:"$(WXWIN)\lib\vc_lib"
# ADD LINK32 wxbase28d.lib user32.lib shell32.lib ole32.lib advapi32.lib kernel32.lib /nologo /entry:"" /dll /map:"$(OutDir)/DemoLibInDLL.map" /machine:I386 /out:"DemoLibInDLL-vc6-mt-wx.dll" /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)\lib" /libpath:"$(WXWIN)\lib\vc_lib"

!ELSEIF  "$(CFG)" == "DemoLibInDLL - Win32 DebugWxMTD"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_Wx_MTD"
# PROP BASE Intermediate_Dir "Debug_Wx_MTD"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "DebugWxMTD-6.0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
LIB32=link.exe -lib
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(MODASSERT)/include" /I "$(RICHBOOL)/include" /I "$(WXWIN)/include" /I "$(WXWIN)/lib/vc_lib/mswd" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_USRDLL" /D "RICHBOOL_USE_WX" /D "DLL_EXPORTS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x813 /d "_DEBUG"
# ADD RSC /l 0x813 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 user32.lib shell32.lib ole32.lib richbool.lib modassert.lib wxbase28d.lib /nologo /dll /machine:I386 /out:"DemoLibInDLL.dll" /libpath:"$(RICHBOOL)\DebugMTD" /libpath:"$(MODASSERT)\DebugMTD" /libpath:"$(WXWIN)\lib\vc_lib"
# ADD LINK32 wxbase28d.lib user32.lib shell32.lib ole32.lib advapi32.lib kernel32.lib /nologo /entry:"" /dll /map:"$(OutDir)/DemoLibInDLL.map" /machine:I386 /out:"DemoLibInDLL-vc6-mt-gd-wx.dll" /libpath:"$(RICHBOOL)\lib" /libpath:"$(MODASSERT)\lib" /libpath:"$(WXWIN)\lib\vc_lib"

!ENDIF 

# Begin Target

# Name "DemoLibInDLL - Win32 DebugST"
# Name "DemoLibInDLL - Win32 ReleaseST"
# Name "DemoLibInDLL - Win32 DebugMT"
# Name "DemoLibInDLL - Win32 ReleaseMT"
# Name "DemoLibInDLL - Win32 DebugMTD"
# Name "DemoLibInDLL - Win32 ReleaseMTD"
# Name "DemoLibInDLL - Win32 ReleaseWxMTD"
# Name "DemoLibInDLL - Win32 DebugWxMTD"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DLLmain.cpp
# End Source File
# Begin Source File

SOURCE=.\export.hpp
# End Source File
# End Group
# End Target
# End Project
