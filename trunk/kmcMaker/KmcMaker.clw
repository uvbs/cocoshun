; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CImportLyricDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "KmcMaker.h"

ClassCount=4
Class1=CKmcMakerApp
Class2=CKmcMakerDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_KMCMAKER_DIALOG
Class4=CImportLyricDlg
Resource4=IDD_IMPORTLYRICDLG_DIALOG

[CLS:CKmcMakerApp]
Type=0
HeaderFile=KmcMaker.h
ImplementationFile=KmcMaker.cpp
Filter=N

[CLS:CKmcMakerDlg]
Type=0
HeaderFile=KmcMakerDlg.h
ImplementationFile=KmcMakerDlg.cpp
Filter=D
LastObject=IDC_CHECK_STEP1
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=KmcMakerDlg.h
ImplementationFile=KmcMakerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_KMCMAKER_DIALOG]
Type=1
Class=CKmcMakerDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK_STEP1,button,1342246915
Control4=IDC_CHECK_STEP2,button,1342246915
Control5=IDC_CHECK_STEP3,button,1342246915
Control6=IDC_STATIC,static,1342181383
Control7=IDC_DLG_AREA,button,1342177287

[DLG:IDD_IMPORTLYRICDLG_DIALOG]
Type=1
Class=CImportLyricDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CImportLyricDlg]
Type=0
HeaderFile=ImportLyricDlg.h
ImplementationFile=ImportLyricDlg.cpp
BaseClass=CDialog
Filter=D
