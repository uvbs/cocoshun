; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMakeLyricDlg
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
Resource3=IDD_ABOUTBOX
Class4=CImportLyricDlg
Resource4=IDD_IMPORTLYRICDLG_DIALOG
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
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_CHECK_STEP1,button,1342246915
Control4=IDC_CHECK_STEP2,button,1342246915
Control5=IDC_CHECK_STEP3,button,1342246915
Control6=IDC_STATIC_TOPLINE,static,1342181383
Control7=IDC_DLG_AREA,button,1342177287

[DLG:IDD_IMPORTLYRICDLG_DIALOG]
Type=1
Class=CImportLyricDlg
ControlCount=17
Control1=IDC_BTN_IMPORT,button,1342242816
Control2=IDC_CHECK_DEL_SPACE,button,1342242819
Control3=IDC_CHECK_DEL_EMPTYLINE,button,1342242819
Control4=IDC_CHECK_DEL_LRC,button,1342242819
Control5=IDC_CHECK_DEL_KSC,button,1342242819
Control6=IDC_EDIT_REPLACE_TXT,edit,1350631552
Control7=IDC_EDIT_TARGET_TXT,edit,1350631552
Control8=IDC_BTN_FILTER,button,1342242816
Control9=IDC_BTN_NEXTSTEP,button,1342242816
Control10=IDC_LYRIC_EDITOR,RICHEDIT,1353781700
Control11=IDC_STATIC_TIP,static,1342308352
Control12=IDC_CHECK_DEL_XML_HTML,button,1073807363
Control13=IDC_STATIC_FILTER_OPTION,button,1342178055
Control14=IDC_CHECK_REPLACE,button,1073807363
Control15=IDC_STATIC_FOR,static,1342308352
Control16=IDC_STATIC_HELP,button,1342178055
Control17=IDC_STATIC_FIND,static,1342308352

[CLS:CImportLyricDlg]
Type=0
HeaderFile=ImportLyricDlg.h
ImplementationFile=ImportLyricDlg.cpp
BaseClass=CResizingDialog
Filter=D
LastObject=IDC_EDIT_REPLACE_TXT
VirtualFilter=dWC

[DLG:IDD_MAKELYRICDLG_DIALOG]
Type=1
Class=CMakeLyricDlg
ControlCount=12
Control1=IDC_BTN_OPEN,button,1342242816
Control2=IDC_LYRIC_MAKER,static,1342373889
Control3=IDC_MEDIAPLAYER,{6BF52A52-394A-11D3-B153-00C04F79FAA6},1342242816
Control4=IDC_STATIC_TIP,static,1342242816
Control5=IDC_BTN_PRIVIEW,button,1073807360
Control6=IDC_BTN_NEXTSTEP,button,1342242816
Control7=IDC_BTN_PREVSTEP,button,1342242816
Control8=IDC_STATIC_KEY_TIP,button,1342178055
Control9=IDC_SLIDER_MP,static,1342245646
Control10=IDC_BTN_PLAY_PAUSE,button,1342242816
Control11=IDC_BTN_STOP,button,1342242816
Control12=IDC_STATIC_MEDIA_TIMEINFO,static,1342308354

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
ControlCount=16
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
Control11=IDC_RADIO_KMC,button,1342177289
Control12=IDC_RADIO_XML,button,1342177289
Control13=IDC_STATIC_SAVETIP,button,1342178055
Control14=IDC_BTN_EXIT,button,1342242816
Control15=IDC_BTN_SAVE_PREVSTEP,button,1342242816
Control16=IDC_STATIC_TIPEXT,static,1342308352

[CLS:CSaveLyricDlg]
Type=0
HeaderFile=SaveLyricDlg.h
ImplementationFile=SaveLyricDlg.cpp
BaseClass=CResizingDialog
Filter=D
VirtualFilter=dWC
LastObject=CSaveLyricDlg

[CLS:CPreviewCtrl]
Type=0
HeaderFile=PreviewCtrl.h
ImplementationFile=PreviewCtrl.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CPreviewCtrl

