# Microsoft Developer Studio Project File - Name="MyToolBox" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MyToolBox - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MyToolBox.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MyToolBox.mak" CFG="MyToolBox - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MyToolBox - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MyToolBox - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MyToolBox - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 shlwapi.lib Wininet.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "MyToolBox - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 shlwapi.lib Wininet.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MyToolBox - Win32 Release"
# Name "MyToolBox - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\UILib\BCMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\UILib\BitmapSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\UILib\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\UILib\CeXDib.cpp
# End Source File
# Begin Source File

SOURCE=.\UILib\CheckBTGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\ClearHistoryDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CtrlAction.cpp
# End Source File
# Begin Source File

SOURCE=.\UILib\FileDialogEx.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralTool.cpp
# End Source File
# Begin Source File

SOURCE=.\UILib\MyRichEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MyToolBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MyToolBox.rc
# End Source File
# Begin Source File

SOURCE=.\MyToolBoxDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Util\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\RegOperate.cpp
# End Source File
# Begin Source File

SOURCE=.\UILib\ResizingDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\UILib\ShadeButtonST.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SysClearer.cpp
# End Source File
# Begin Source File

SOURCE=.\Util\SysUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\Win7Setting.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\UILib\BCMenu.h
# End Source File
# Begin Source File

SOURCE=.\UILib\BitmapSlider.h
# End Source File
# Begin Source File

SOURCE=.\UILib\CeXDib.h
# End Source File
# Begin Source File

SOURCE=.\UILib\CheckBTGroup.h
# End Source File
# Begin Source File

SOURCE=.\ClearHistoryDlg.h
# End Source File
# Begin Source File

SOURCE=.\CtrlAction.h
# End Source File
# Begin Source File

SOURCE=.\UILib\FileDialogEx.h
# End Source File
# Begin Source File

SOURCE=.\GeneralTool.h
# End Source File
# Begin Source File

SOURCE=.\UILib\MyRichEdit.h
# End Source File
# Begin Source File

SOURCE=.\MyToolBox.h
# End Source File
# Begin Source File

SOURCE=.\MyToolBoxDlg.h
# End Source File
# Begin Source File

SOURCE=.\Util\Registry.h
# End Source File
# Begin Source File

SOURCE=.\RegOperate.h
# End Source File
# Begin Source File

SOURCE=.\UILib\ResizingDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\UILib\ShadeButtonST.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SysClearer.h
# End Source File
# Begin Source File

SOURCE=.\Util\SysUtil.h
# End Source File
# Begin Source File

SOURCE=.\Win7Setting.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ClearShell.ico
# End Source File
# Begin Source File

SOURCE=.\res\exit.ico
# End Source File
# Begin Source File

SOURCE=.\res\general.ico
# End Source File
# Begin Source File

SOURCE=.\res\MyToolBox.ico
# End Source File
# Begin Source File

SOURCE=.\res\MyToolBox.rc2
# End Source File
# Begin Source File

SOURCE=.\res\win7.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Master.manifest
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
