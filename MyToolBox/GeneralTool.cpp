// GeneralTool.cpp : implementation file
//

#include "stdafx.h"
#include "MyToolBox.h"
#include "GeneralTool.h"
#include "Util/SysUtil.h"
#include "Util/Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GeneralTool dialog


GeneralTool::GeneralTool(CWnd* pParent /*=NULL*/)
	: CResizingDialog(GeneralTool::IDD, pParent)
{
	//{{AFX_DATA_INIT(GeneralTool)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void GeneralTool::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GeneralTool)
	DDX_Control(pDX, IDC_BTN_REBULID_ICON_CACHE, m_BtnRebulidIconCache);
	DDX_Control(pDX, IDC_BTN_RESTART_EXPLORER, m_BtnRestartExplorer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GeneralTool, CResizingDialog)
	//{{AFX_MSG_MAP(GeneralTool)
	ON_BN_CLICKED(IDC_BTN_REBULID_ICON_CACHE, OnBtnRebulidIconCache)
	ON_BN_CLICKED(IDC_BTN_RESTART_EXPLORER, OnBtnRestartExplorer)
	ON_BN_CLICKED(IDC_CHECK_SHOWBOOTTIME, OnCheckShowboottime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GeneralTool message handlers

BOOL GeneralTool::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
    m_BtnRestartExplorer.SetShade(CShadeButtonST::SHS_METAL);
    m_BtnRestartExplorer.SetIcon(SysUtil::GetSystemIcon(24));

    m_BtnRebulidIconCache.SetShade(CShadeButtonST::SHS_METAL);
    m_BtnRebulidIconCache.SetIcon(SysUtil::GetSystemIcon(238));

    CButton *pButton = (CButton *)GetDlgItem(IDC_CHECK_SHOWBOOTTIME);
    pButton->SetCheck(SysUtil::IsRegRun(_T("ShowBootTime")));
	return TRUE; 
}

void GeneralTool::OnOK() 
{
//	CResizingDialog::OnOK();
}

void GeneralTool::OnCancel() 
{
//	CResizingDialog::OnCancel();
}

void GeneralTool::OnBtnRebulidIconCache() 
{
    SysUtil::RebulidIconCache();
}

void GeneralTool::OnBtnRestartExplorer() 
{
    CRegistry reg;
    //HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{ED228FDF-9EA8-4870-83b1-96b02CFE0D52}
     reg.SetRootKey(HKEY_LOCAL_MACHINE);
//	reg.SetKey("SOFTWARE\\Classes\\CLSID\\{ED228FDF-9EA8-4870-83b1-96b02CFE0D52}\\test",TRUE);
//    reg.SetPermission("");
	reg.SetKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FolderTypes\\{5c4f28b5-f869-4e84-8e60-f11db97c5cc7}",FALSE);
//   CString explorerExe = _T("explorer.exe");
// 	SysUtil::KillProcess(explorerExe);
}

void GeneralTool::OnCheckShowboottime() 
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_CHECK_SHOWBOOTTIME);
    CString name = _T("ShowBootTime");

    CString strPath;
    CString strName;
    SysUtil::GetCurrentPathOrMoudle(strPath, strName);
    if(pButton->GetCheck())
    {
        CString strCmdline =  strPath += strName + _T(".exe /showBootTime");
        SysUtil::WriteRegRun(name,strCmdline);
    }else
    {
        SysUtil::RemoveRegRun(name);
    }	
}
