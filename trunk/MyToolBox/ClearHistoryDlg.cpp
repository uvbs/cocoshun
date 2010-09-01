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

CClearHistoryDlg::CTRLID_SETTING CClearHistoryDlg::m_CtrlAndSetting[]=
{
    {IDC_CHECK_CLEAR_INTERNAT_TEMP,&(theSetting.HistorySetting.bClearInternetTemp)},
    {IDC_CHECK_CLEAR_SYSTEMP,&(theSetting.HistorySetting.bClearSysTempDir)},
    {IDC_CHECK_ClearBrowserAddress,&(theSetting.HistorySetting.bClearBrowserAddress)},
    {IDC_CHECK_ClearFormAutoComplete,&(theSetting.HistorySetting.bClearFormAutoComplete)},
    {IDC_CHECK_ClearAutoPassword,&(theSetting.HistorySetting.bClearAutoPassword)},
    {IDC_CHECK_ClearFavorite,&(theSetting.HistorySetting.bClearFavorite)},
    {IDC_CHECK_ClearRecyclebin,&(theSetting.HistorySetting.bClearRecyclebin)},
    {IDC_CHECK_ClearRun,&(theSetting.HistorySetting.bClearRun)},
    {IDC_CHECK_ClearDocument,&(theSetting.HistorySetting.bClearDocument)},
    {IDC_CHECK_ClearLastLoginName,&(theSetting.HistorySetting.bClearLastLoginName)},
    {IDC_CHECK_ClearFindFile,&(theSetting.HistorySetting.bClearFindFile)},
    {IDC_CHECK_ClearFindComputer,&(theSetting.HistorySetting.bClearFindComputer)},
    {IDC_CHECK_ClearBrowseAddress,&(theSetting.HistorySetting.bClearBrowseAddress)},
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
//    SysUtil::WriteSetting(&theSetting);
//	CDialog::OnOK();
}

void CClearHistoryDlg::OnCancel() 
{
//	SysUtil::ReadSetting(&theSetting);
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
    UpdateData(TRUE);
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

	ReadCheckBoxValue();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CClearHistoryDlg::ReadCheckBoxValue()
{
    int len = sizeof(m_CtrlAndSetting) / sizeof(CTRLID_SETTING);
    for( int i=0;i<len;i++)
    {
        UINT ID = m_CtrlAndSetting[i].CtrlID;
        BOOL bCheck = *m_CtrlAndSetting[i].bCheck;
        SetCheck(ID, bCheck);
    }
}

BOOL CClearHistoryDlg::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_LBUTTONDOWN)
    {
        int index = -1;

        int len = sizeof(m_CtrlAndSetting) / sizeof(CTRLID_SETTING);
        for( int i=0;i<len;i++)
        {
            if(pMsg->hwnd == (GetDlgItem(m_CtrlAndSetting[i].CtrlID)->GetSafeHwnd()))
            {
                index = i;
                break;
            }
        }

        if(index != -1)
        {
            TRACE("%d,%d\n",index,m_CtrlAndSetting[index].CtrlID);
            BOOL bCheck = !GetCheck(m_CtrlAndSetting[index].CtrlID);
            *m_CtrlAndSetting[index].bCheck = bCheck;
        }
    }
	
	return CDialog::PreTranslateMessage(pMsg);
}
