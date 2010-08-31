// ClearHistoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyToolBox.h"
#include "ClearHistoryDlg.h"
#include "Util/sysutil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClearHistoryDlg dialog

UINT CClearHistoryDlg::m_CtrlIDs[]=
{
    IDC_CHECK_CLEAR_INTERNAT_TEMP,IDC_CHECK_CLEAR_SYSTEMP
};

CClearHistoryDlg::CClearHistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClearHistoryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClearHistoryDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CClearHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClearHistoryDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClearHistoryDlg, CDialog)
	//{{AFX_MSG_MAP(CClearHistoryDlg)
	ON_BN_CLICKED(IDC_CHECK_CLEAR_INTERNAT_TEMP, OnCheckClearInternatTemp)
	ON_BN_CLICKED(IDC_CHECK_CLEAR_SYSTEMP, OnCheckClearSystemp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClearHistoryDlg message handlers

void CClearHistoryDlg::OnOK() 
{
    theSetting.HistorySetting.bClearRun = TRUE;
    SysUtil::WriteSetting(&theSetting);
//	CDialog::OnOK();
}

void CClearHistoryDlg::OnCancel() 
{
	SysUtil::ReadSetting(&theSetting);
//	CDialog::OnCancel();
}

BOOL CClearHistoryDlg::DestroyWindow() 
{
	return CDialog::DestroyWindow();
}

void CClearHistoryDlg::OnCheckClearInternatTemp() 
{
	theSetting.HistorySetting.bClearInternetTemp = GetCheck(IDC_CHECK_CLEAR_INTERNAT_TEMP);
}

void CClearHistoryDlg::OnCheckClearSystemp() 
{
	theSetting.HistorySetting.bClearSysTempDir = GetCheck(IDC_CHECK_CLEAR_SYSTEMP);
}

BOOL CClearHistoryDlg::GetCheck(UINT ID)
{
    CButton *pButton = (CButton *)GetDlgItem(ID);
    return pButton->GetCheck();
}

void CClearHistoryDlg::SetCheck(UINT ID,BOOL bCheck)
{
    CButton *pButton = (CButton *)GetDlgItem(ID);
    pButton->SetCheck(bCheck);
}

BOOL CClearHistoryDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ReadCheck();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CClearHistoryDlg::ReadCheck()
{
    SetCheck(IDC_CHECK_CLEAR_INTERNAT_TEMP,theSetting.HistorySetting.bClearInternetTemp);
    SetCheck(IDC_CHECK_CLEAR_SYSTEMP,theSetting.HistorySetting.bClearSysTempDir);
}
