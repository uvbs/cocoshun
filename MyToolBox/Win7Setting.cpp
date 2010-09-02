// Win7Setting.cpp : implementation file
//

#include "stdafx.h"
#include "MyToolBox.h"
#include "Win7Setting.h"
#include "Util/SysUtil.h"
#include "Util/Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Win7Setting dialog
CTRL_OPERATION Win7Setting::m_SettingOper[]=
{
    IDC_CHECK_HIDE_FAVORITES,CHECKBOX,
    {Write,{HKEY_CLASSES_ROOT,_T("CLSID\\{323CA680-C24D-4099-B94D-446DD2D7249E}\\ShellFolder"),_T("Attributes"),DW,0xa9400100}},
    {Write,{HKEY_CLASSES_ROOT,_T("CLSID\\{323CA680-C24D-4099-B94D-446DD2D7249E}\\ShellFolder"),_T("Attributes"),DW,0xa9000100}},
    {Query,{HKEY_CLASSES_ROOT,_T("CLSID\\{323CA680-C24D-4099-B94D-446DD2D7249E}\\ShellFolder"),_T("Attributes"),DW}},   

    IDC_CHECK_HIDE_LIBRARIES,CHECKBOX,
    {Write,{HKEY_CLASSES_ROOT,_T("CLSID\\{031E4825-7B94-4dc3-B131-E946B44C8DD5}\\ShellFolder"),_T("Attributes"),DW,0xb090010d}},
    {Write,{HKEY_CLASSES_ROOT,_T("CLSID\\{031E4825-7B94-4dc3-B131-E946B44C8DD5}\\ShellFolder"),_T("Attributes"),DW,0xb080010d}},
    {Query,{HKEY_CLASSES_ROOT,_T("CLSID\\{031E4825-7B94-4dc3-B131-E946B44C8DD5}\\ShellFolder"),_T("Attributes"),DW}},   

    IDC_CHECK_DISABLE_WINDOW_AUTO_ARRANGEMENT,CHECKBOX,
    {Write,{HKEY_CURRENT_USER,_T("Control Panel\\Desktop"),_T("WindowArrangementActive"),STRING,0,_T("0")}},
    {Write,{HKEY_CURRENT_USER,_T("Control Panel\\Desktop"),_T("WindowArrangementActive"),STRING,0,_T("1")}},
    {Query,{HKEY_CURRENT_USER,_T("Control Panel\\Desktop"),_T("WindowArrangementActive"),STRING}},   
};

Win7Setting::Win7Setting(CWnd* pParent /*=NULL*/)
	: CResizingDialog(Win7Setting::IDD, pParent)
{
	//{{AFX_DATA_INIT(Win7Setting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void Win7Setting::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Win7Setting)
	DDX_Control(pDX, IDC_BTN_RESTART_EXPLORER, m_BtnRestartExplorer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Win7Setting, CResizingDialog)
	//{{AFX_MSG_MAP(Win7Setting)
	ON_BN_CLICKED(IDC_BTN_RESTART_EXPLORER, OnBtnRestartExplorer)
	ON_BN_CLICKED(IDC_CHECK_HIDE_FAVORITES, OnCheckHideFavorites)
	ON_BN_CLICKED(IDC_CHECK_HIDE_LIBRARIES, OnCheckHideLibraries)
	ON_BN_CLICKED(IDC_CHECK_DISABLE_WINDOW_AUTO_ARRANGEMENT, OnCheckDisableWindowAutoArrangement)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Win7Setting message handlers

BOOL Win7Setting::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();

    m_BtnRestartExplorer.SetShade(CShadeButtonST::SHS_METAL);
	m_BtnRestartExplorer.SetIcon(IDI_RESTART_EXPLORER);
	
    m_ctrlAction.Initialize(this,m_SettingOper);
    m_ctrlAction.Process(IDC_CHECK_HIDE_FAVORITES,TRUE);
    m_ctrlAction.Process(IDC_CHECK_HIDE_LIBRARIES,TRUE);
    m_ctrlAction.Process(IDC_CHECK_DISABLE_WINDOW_AUTO_ARRANGEMENT,TRUE);

	SetControlInfo(IDC_CHECK_HIDE_FAVORITES,ANCHORE_LEFT);
	return TRUE;  
}

void Win7Setting::OnOK() 
{
//	CResizingDialog::OnOK();
}

void Win7Setting::OnCancel() 
{
//	CResizingDialog::OnCancel();
}

void Win7Setting::OnBtnRestartExplorer() 
{
	CString explorerExe = _T("explorer.exe");
	SysUtil::KillProcess(explorerExe);
}

void Win7Setting::OnCheckHideFavorites() 
{
    m_ctrlAction.Process(IDC_CHECK_HIDE_FAVORITES);
}

void Win7Setting::OnCheckHideLibraries() 
{
    m_ctrlAction.Process(IDC_CHECK_HIDE_LIBRARIES); 	
}

void Win7Setting::OnCheckDisableWindowAutoArrangement() 
{
	m_ctrlAction.Process(IDC_CHECK_DISABLE_WINDOW_AUTO_ARRANGEMENT); 	
}
