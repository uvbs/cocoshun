; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CIECacheCatcherDlg
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "IECacheCatcher.h"

ClassCount=4
Class1=CIECacheCatcherApp
Class2=CIECacheCatcherDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CFileListCtrl
Resource3=IDD_IECACHECATCHER_DIALOG

[CLS:CIECacheCatcherApp]
Type=0
HeaderFile=IECacheCatcher.h
ImplementationFile=IECacheCatcher.cpp
Filter=N

[CLS:CIECacheCatcherDlg]
Type=0
HeaderFile=IECacheCatcherDlg.h
ImplementationFile=IECacheCatcherDlg.cpp
Filter=D
BaseClass=CResizingDialog
VirtualFilter=dWC
LastObject=IDC_STATIC_TEST

[CLS:CAboutDlg]
Type=0
HeaderFile=IECacheCatcherDlg.h
ImplementationFile=IECacheCatcherDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_IECACHECATCHER_DIALOG]
Type=1
Class=CIECacheCatcherDlg
ControlCount=22
Control1=IDC_EDIT_URLPATH,edit,1350631552
Control2=IDC_EDIT_EXPORTPATH,edit,1350631552
Control3=IDC_BUTTON_EXPORT,button,1342242817
Control4=IDC_BUTTON_BROWSE,button,1342242816
Control5=IDC_STATIC,static,1342308353
Control6=IDC_STATIC,static,1342308353
Control7=IDC_STATIC,static,1342308353
Control8=IDC_STATIC,static,1342308353
Control9=IDC_EDIT_CACHEPATH,edit,1350633600
Control10=IDC_BUTTON_OPEN,button,1342242816
Control11=IDC_BUTTON_CLEARCACHE,button,1342242816
Control12=IDC_STATIC_CTRL_AREA,button,1342177287
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC_STATUS,static,1342312960
Control15=IDC_STATIC_COMMENT2,static,1342308352
Control16=IDC_STATIC_COMMENT1,static,1342308352
Control17=IDC_BUTTON_OPEN_EXPORT_PATH,button,1342242816
Control18=IDC_LIST_RECORD,SysListView32,1350631433
Control19=IDC_STATIC_OPERCOMMENT,static,1342312961
Control20=IDC_BUTTON_IEOPTION,button,1342242816
Control21=IDC_COMBOBOX_FILETYPE,combobox,1073807362
Control22=IDC_EDIT_FILETYPE,edit,1350631552

[CLS:CFileListCtrl]
Type=0
HeaderFile=ListCtrl\FileListCtrl.h
ImplementationFile=ListCtrl\FileListCtrl.cpp
BaseClass=CButton
Filter=W

