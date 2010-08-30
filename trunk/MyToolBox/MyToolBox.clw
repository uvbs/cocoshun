; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Win7Setting
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MyToolBox.h"

ClassCount=5
Class1=CMyToolBoxApp
Class2=CMyToolBoxDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_WIN7SETTING_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_MYTOOLBOX_DIALOG
Class4=Win7Setting
Resource4=IDD_ABOUTBOX
Class5=GeneralTool
Resource5=IDD_GENERALTOOL_DIALOG

[CLS:CMyToolBoxApp]
Type=0
HeaderFile=MyToolBox.h
ImplementationFile=MyToolBox.cpp
Filter=N

[CLS:CMyToolBoxDlg]
Type=0
HeaderFile=MyToolBoxDlg.h
ImplementationFile=MyToolBoxDlg.cpp
Filter=D
LastObject=IDC_BTN_EXIT
BaseClass=CResizingDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MyToolBoxDlg.h
ImplementationFile=MyToolBoxDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MYTOOLBOX_DIALOG]
Type=1
Class=CMyToolBoxDlg
ControlCount=4
Control1=IDC_STATIC_DLGAREA,button,1342177287
Control2=IDC_BTN_WIN7SETTING,button,1342246915
Control3=IDC_BTN_GENERALTOOL,button,1342246915
Control4=IDC_BTN_EXIT,button,1342246915

[DLG:IDD_WIN7SETTING_DIALOG]
Type=1
Class=Win7Setting
ControlCount=5
Control1=IDC_CHECK_HIDE_FAVORITES,button,1342242819
Control2=IDC_CHECK_HIDE_LIBRARIES,button,1342242819
Control3=IDC_BTN_RESTART_EXPLORER,button,1342242816
Control4=IDC_STATIC_EXPLORER,button,1342177287
Control5=IDC_CHECK_DISABLE_WINDOW_AUTO_ARRANGEMENT,button,1342242819

[CLS:Win7Setting]
Type=0
HeaderFile=Win7Setting.h
ImplementationFile=Win7Setting.cpp
BaseClass=CResizingDialog
Filter=D
LastObject=IDC_BTN_RESTART_EXPLORER
VirtualFilter=dWC

[DLG:IDD_GENERALTOOL_DIALOG]
Type=1
Class=GeneralTool
ControlCount=1
Control1=IDC_BTN_REBULID_ICON_CACHE,button,1342242816

[CLS:GeneralTool]
Type=0
HeaderFile=GeneralTool.h
ImplementationFile=GeneralTool.cpp
BaseClass=CResizingDialog
Filter=D
VirtualFilter=dWC
LastObject=GeneralTool

