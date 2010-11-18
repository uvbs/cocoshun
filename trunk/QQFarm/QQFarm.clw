; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLoginDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "QQFarm.h"

ClassCount=3
Class1=CQQFarmApp
Class2=CQQFarmDlg

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_QQFARM_DIALOG
Class3=CLoginDlg
Resource3=IDD_LOGINDLG_DIALOG

[CLS:CQQFarmApp]
Type=0
HeaderFile=QQFarm.h
ImplementationFile=QQFarm.cpp
Filter=N

[CLS:CQQFarmDlg]
Type=0
HeaderFile=QQFarmDlg.h
ImplementationFile=QQFarmDlg.cpp
Filter=D



[DLG:IDD_QQFARM_DIALOG]
Type=1
Class=CQQFarmDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_LOGINDLG_DIALOG]
Type=1
Class=CLoginDlg
ControlCount=9
Control1=IDC_EDIT_QQNUMBER,edit,1350631552
Control2=IDC_EDIT_PASSWORD,edit,1350631552
Control3=IDC_EDIT_VERIFYCODE,edit,1350631552
Control4=ID_Login,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_CHECK_SAVEPWD,button,1342242819

[CLS:CLoginDlg]
Type=0
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CLoginDlg

