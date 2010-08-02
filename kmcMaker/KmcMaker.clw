; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSaveLyricDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "KmcMaker.h"

ClassCount=7
Class1=CKmcMakerApp
Class2=CKmcMakerDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_MAKELYRICDLG_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_IMPORTLYRICDLG_DIALOG
Class4=CImportLyricDlg
Resource4=IDD_ABOUTBOX
Class5=CMakeLyricDlg
Resource5=IDD_KMCMAKER_DIALOG
Class6=CSaveLyricDlg
Class7=CPreviewCtrl
Resource6=IDD_SAVELYRICDLG_DIALOG

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
LastObject=IDC_RICHEDIT1
BaseClass=CResizingDialog
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
Control6=IDC_STATIC_TOPLINE,static,1342181383
Control7=IDC_DLG_AREA,button,1342177287

[DLG:IDD_IMPORTLYRICDLG_DIALOG]
Type=1
Class=CImportLyricDlg
ControlCount=2
Control1=IDC_LYRIC_EDITOR,RICHEDIT,1353781700
Control2=IDC_BTN_IMPORT,button,1342242816

[CLS:CImportLyricDlg]
Type=0
HeaderFile=ImportLyricDlg.h
ImplementationFile=ImportLyricDlg.cpp
BaseClass=CResizingDialog
Filter=D
LastObject=IDC_COMBO_ENCODE
VirtualFilter=dWC

[DLG:IDD_MAKELYRICDLG_DIALOG]
Type=1
Class=CMakeLyricDlg
ControlCount=5
Control1=IDC_BTN_OPEN,button,1342242816
Control2=IDC_LYRIC_MAKER,static,1342373889
Control3=IDC_MEDIAPLAYER,{6BF52A52-394A-11D3-B153-00C04F79FAA6},1476460544
Control4=IDC_STATIC_TIP,static,1342242816
Control5=IDC_BTN_PRIVIEW,button,1073807360

[CLS:CMakeLyricDlg]
Type=0
HeaderFile=MakeLyricDlg.h
ImplementationFile=MakeLyricDlg.cpp
BaseClass=CResizingDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_MEDIAPLAYER

[DLG:IDD_SAVELYRICDLG_DIALOG]
Type=1
Class=CSaveLyricDlg
ControlCount=10
Control1=IDC_EDIT_TI,edit,1350631552
Control2=IDC_EDIT_AR,edit,1350631552
Control3=IDC_EDIT_AL,edit,1350631552
Control4=IDC_EDIT_BY,edit,1350631552
Control5=IDC_BTN_SAVELYRIC,button,1342242816
Control6=IDC_KMC_PRIVEW,RICHEDIT,1353781700
Control7=IDC_STATIC_TI,static,1342308352
Control8=IDC_STATIC_AR,static,1342308352
Control9=IDC_STATIC_AL,static,1342308352
Control10=IDC_STATIC_BY,static,1342308352

[CLS:CSaveLyricDlg]
Type=0
HeaderFile=SaveLyricDlg.h
ImplementationFile=SaveLyricDlg.cpp
BaseClass=CResizingDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_AL

[CLS:CPreviewCtrl]
Type=0
HeaderFile=PreviewCtrl.h
ImplementationFile=PreviewCtrl.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CPreviewCtrl

