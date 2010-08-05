# Microsoft Developer Studio Project File - Name="XButtonXPTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XButtonXPTest - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XButtonXPTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XButtonXPTest.mak" CFG="XButtonXPTest - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XButtonXPTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XButtonXPTest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XButtonXPTest - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "_VC60"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "XButtonXPTest - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL" /d "_VC60"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "XButtonXPTest - Win32 Release"
# Name "XButtonXPTest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\About.cpp
# End Source File
# Begin Source File

SOURCE=..\src\ColorDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\src\OddButton.cpp
# End Source File
# Begin Source File

SOURCE=..\src\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\src\XButtonXP.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XButtonXPTest.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XButtonXPTest.rc
# End Source File
# Begin Source File

SOURCE=..\src\XButtonXPTestDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XColourPicker.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XColourPopup.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XHyperLink.cpp
# End Source File
# Begin Source File

SOURCE=..\src\XNamedColors.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\src\XThemeHelper.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\About.h
# End Source File
# Begin Source File

SOURCE=..\src\ColorDlg.h
# End Source File
# Begin Source File

SOURCE=..\src\CreateGrayscaleIcon.h
# End Source File
# Begin Source File

SOURCE=..\src\OddButton.h
# End Source File
# Begin Source File

SOURCE=..\src\resource.h
# End Source File
# Begin Source File

SOURCE=..\src\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\src\XButtonXP.h
# End Source File
# Begin Source File

SOURCE=..\src\XButtonXPTest.h
# End Source File
# Begin Source File

SOURCE=..\src\XButtonXPTestDlg.h
# End Source File
# Begin Source File

SOURCE=..\src\XColourPicker.h
# End Source File
# Begin Source File

SOURCE=..\src\XColourPopup.h
# End Source File
# Begin Source File

SOURCE=..\src\XHyperLink.h
# End Source File
# Begin Source File

SOURCE=..\src\XNamedColors.h
# End Source File
# Begin Source File

SOURCE=..\src\XThemeHelper.h
# End Source File
# Begin Source File

SOURCE=..\src\XTrace.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\src\hans.ico
# End Source File
# Begin Source File

SOURCE=..\src\mfc16.ico
# End Source File
# Begin Source File

SOURCE=..\src\mfc24bpp.ico
# End Source File
# Begin Source File

SOURCE=..\src\mfc256.ico
# End Source File
# Begin Source File

SOURCE=..\src\mfc32bpp.ico
# End Source File
# End Group
# End Target
# End Project
