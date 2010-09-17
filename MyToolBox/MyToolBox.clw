; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=GeneralTool
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MyToolBox.h"

ClassCount=7
Class1=CMyToolBoxApp
Class2=CMyToolBoxDlg
Class3=CAboutDlg

ResourceCount=8
Resource1=IDD_CLEAR_HISTORY_BOOT_DLG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=Win7Setting
Resource4=IDD_MYTOOLBOX_DIALOG
Class5=GeneralTool
Resource5=IDD_CLEAR_HISTORY_DLG
Class6=CClearHistoryDlg
Resource6=IDD_WIN7SETTING_DIALOG
Resource7=IDD_GENERALTOOL_DIALOG
Class7=CShowBootTime
Resource8=IDD_SHOWBOOTTIME_DIALOG

[CLS:CMyToolBoxApp]
Type=0
HeaderFile=MyToolBox.h
ImplementationFile=MyToolBox.cpp
Filter=N
LastObject=CMyToolBoxApp

[CLS:CMyToolBoxDlg]
Type=0
HeaderFile=MyToolBoxDlg.h
ImplementationFile=MyToolBoxDlg.cpp
Filter=D
LastObject=CMyToolBoxDlg
BaseClass=CResizingDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MyToolBoxDlg.h
ImplementationFile=MyToolBoxDlg.cpp
Filter=D
LastObject=CAboutDlg

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
ControlCount=5
Control1=IDC_STATIC_DLGAREA,button,1073741831
Control2=IDC_BTN_WIN7SETTING,button,1342246915
Control3=IDC_BTN_GENERALTOOL,button,1342246915
Control4=IDC_BTN_EXIT,button,1342246915
Control5=IDC_BTN_CLEARTOOL,button,1342246915

[DLG:IDD_WIN7SETTING_DIALOG]
Type=1
Class=Win7Setting
ControlCount=23
Control1=IDC_CHECK_HIDE_FAVORITES,button,1342242819
Control2=IDC_CHECK_HIDE_LIBRARIES,button,1342242819
Control3=IDC_CHECK_DISABLE_WINDOW_AUTO_ARRANGEMENT,button,1342242819
Control4=IDC_CHECK_COPY,button,1342242819
Control5=IDC_CHECK_PASTE,button,1342242819
Control6=IDC_CHECK_CUT,button,1342242819
Control7=IDC_CHECK_UNDO,button,1342242819
Control8=IDC_CHECK_REDO,button,1342242819
Control9=IDC_CHECK_PRINT,button,1342242819
Control10=IDC_CHECK_EMAIL,button,1342242819
Control11=IDC_CHECK_BURN,button,1342242819
Control12=IDC_CHECK_SLIDESSHOW,button,1342242819
Control13=IDC_STATIC,button,1342177287
Control14=IDC_LIST_FolderType,SysListView32,1342259213
Control15=IDC_STATIC_EXPLORER2,button,1342177287
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_CHECK_DELETE,button,1342242819
Control19=IDC_RADIO_SELECT,button,1342177289
Control20=IDC_RADIO_UNSELECT,button,1342177289
Control21=IDC_CHECK_DISABLE_FULLROWSELECT,button,1342242819
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352

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
ControlCount=7
Control1=IDC_BTN_REBULID_ICON_CACHE,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,button,1342177287
Control4=IDC_LIST_FolderType,SysListView32,1342259213
Control5=IDC_BUTTON1,button,1342242816
Control6=IDC_BTN_RESTART_EXPLORER,button,1342242816
Control7=IDC_CHECK_SHOWBOOTTIME,button,1342242819

[CLS:GeneralTool]
Type=0
HeaderFile=GeneralTool.h
ImplementationFile=GeneralTool.cpp
BaseClass=CResizingDialog
Filter=D
VirtualFilter=dWC
LastObject=GeneralTool

[DLG:IDD_CLEAR_HISTORY_DLG]
Type=1
Class=CClearHistoryDlg
ControlCount=20
Control1=IDC_CHECK_CLEAR_INTERNAT_TEMP,button,1342242819
Control2=IDC_CHECK_CLEAR_SYSTEMP,button,1342242819
Control3=IDC_CHECK_ClearBrowserAddress,button,1342242819
Control4=IDC_CHECK_ClearBrowseAddress,button,1342242819
Control5=IDC_CHECK_ClearFormAutoComplete,button,1342242819
Control6=IDC_CHECK_ClearAutoPassword,button,1342242819
Control7=IDC_CHECK_ClearRecyclebin,button,1342242819
Control8=IDC_CHECK_ClearRun,button,1342242819
Control9=IDC_CHECK_ClearDocument,button,1342242819
Control10=IDC_CHECK_ClearLastLoginName,button,1342242819
Control11=IDC_CHECK_ClearFindFile,button,1342242819
Control12=IDC_CHECK_ClearFindComputer,button,1342242819
Control13=IDC_CHECK_ClearFavorite,button,1342242819
Control14=IDOK,button,1342242817
Control15=IDC_STATIC,button,1342177287
Control16=IDC_CHECK_CLEAR_AT_SYSSTART,button,1342242819
Control17=IDC_CHECK_DISPLAY_CLEARUI,button,1342242819
Control18=IDC_STATIC,static,1342181383
Control19=IDC_STATIC,static,1342308352
Control20=IDC_CHECK_ClearTaskbarIconHistory,button,1342242819

[CLS:CClearHistoryDlg]
Type=0
HeaderFile=ClearHistoryDlg.h
ImplementationFile=ClearHistoryDlg.cpp
BaseClass=CResizingDialog
Filter=D
VirtualFilter=dWC
LastObject=CClearHistoryDlg

[DLG:IDD_CLEAR_HISTORY_BOOT_DLG]
Type=1
Class=CClearHistoryDlg
ControlCount=20
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,button,1342177287
Control3=IDC_CHECK_CLEAR_AT_SYSSTART,button,1073807363
Control4=IDC_CHECK_DISPLAY_CLEARUI,button,1073807363
Control5=IDC_STATIC,static,1073872896
Control6=IDC_EDIT_LOG,edit,1350631556
Control7=IDC_CHECK_CLEAR_INTERNAT_TEMP,button,1342242819
Control8=IDC_CHECK_CLEAR_SYSTEMP,button,1342242819
Control9=IDC_CHECK_ClearBrowserAddress,button,1342242819
Control10=IDC_CHECK_ClearBrowseAddress,button,1342242819
Control11=IDC_CHECK_ClearFormAutoComplete,button,1342242819
Control12=IDC_CHECK_ClearAutoPassword,button,1342242819
Control13=IDC_CHECK_ClearRecyclebin,button,1342242819
Control14=IDC_CHECK_ClearRun,button,1342242819
Control15=IDC_CHECK_ClearDocument,button,1342242819
Control16=IDC_CHECK_ClearLastLoginName,button,1342242819
Control17=IDC_CHECK_ClearFindFile,button,1342242819
Control18=IDC_CHECK_ClearFindComputer,button,1342242819
Control19=IDC_CHECK_ClearFavorite,button,1342242819
Control20=IDC_CHECK_ClearTaskbarIconHistory,button,1342242819

[DLG:IDD_SHOWBOOTTIME_DIALOG]
Type=1
Class=CShowBootTime
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC_SHOWTIP,static,1342308353

[CLS:CShowBootTime]
Type=0
HeaderFile=ShowBootTime.h
ImplementationFile=ShowBootTime.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CShowBootTime

