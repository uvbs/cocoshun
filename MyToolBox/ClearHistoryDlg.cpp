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
	DDX_Control(pDX, IDOK, m_BtnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CClearHistoryDlg, CDialog)
	//{{AFX_MSG_MAP(CClearHistoryDlg)
	ON_BN_CLICKED(IDC_CHECK_CLEAR_AT_SYSSTART, OnCheckClearAtSysStart)
	ON_BN_CLICKED(IDC_CHECK_DISPLAY_CLEARUI, OnCheckShowClearUI)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClearHistoryDlg message handlers

void CClearHistoryDlg::OnOK() 
{
    for( int i=0;i<m_arySize;i++)
    {
        if(*m_CtrlAndSetting[i].bCheck)
            (m_SysClearer.*m_CtrlAndSetting[i].FuncPtr)();
    }
}

void CClearHistoryDlg::OnCancel() 
{
    TRACE("OnCancel\n");
//	SysUtil::ReadSetting(&theSetting);
//	CDialog::OnCancel();
}

BOOL CClearHistoryDlg::DestroyWindow() 
{
	return CDialog::DestroyWindow();
}

void CClearHistoryDlg::OnCheckClearAtSysStart() 
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_CHECK_DISPLAY_CLEARUI);
    if(GetCheck(IDC_CHECK_CLEAR_AT_SYSSTART))
    {
        pButton->EnableWindow(TRUE);
        SysUtil::WriteRegRun(m_strModule,m_strPath);
    }else
    {
        pButton->EnableWindow(FALSE);
        SysUtil::RemoveRegRun(m_strModule);
    }
}

void CClearHistoryDlg::OnCheckShowClearUI() 
{
    if(!GetCheck(IDC_CHECK_CLEAR_AT_SYSSTART))
        return;
        
    SysUtil::GetCurrentPathOrMoudle(m_strPath, m_strModule);
    if(GetCheck(IDC_CHECK_DISPLAY_CLEARUI))
    {
        m_strPath += m_strModule + _T(".exe /clean /showUI");
        SysUtil::WriteRegRun(m_strModule, m_strPath);
    }else
    {
        m_strPath += m_strModule + _T(".exe /clean");
        SysUtil::WriteRegRun(m_strModule, m_strPath);
    }
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

    InitArray();
	ReadCheckBoxValue();

    SysUtil::GetCurrentPathOrMoudle(m_strPath, m_strModule);
    m_strPath += m_strModule + _T(".exe /clean");

    BOOL isRegRun = SysUtil::IsRegRun(m_strModule);
    SetCheck(IDC_CHECK_CLEAR_AT_SYSSTART,isRegRun);
    if(isRegRun)
    {
        CString strRegRun = SysUtil::GetRegRun(m_strModule);
        int pos = strRegRun.Find(_T("/showUI"), 0);

        SetCheck(IDC_CHECK_DISPLAY_CLEARUI, pos!=-1);
    }else
    {
         CButton *pButton = (CButton *)GetDlgItem(IDC_CHECK_DISPLAY_CLEARUI);
         pButton->EnableWindow(FALSE);
    }


    m_BtnOK.SetShade(CShadeButtonST::SHS_METAL);
    m_BtnOK.SetIcon(IDI_OK);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CClearHistoryDlg::ReadCheckBoxValue()
{
    for( int i=0;i<m_arySize;i++)
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

        for( int i=0;i<m_arySize;i++)
        {
            if(pMsg->hwnd == (GetDlgItem(m_CtrlAndSetting[i].CtrlID)->GetSafeHwnd()))
            {
                index = i;
                break;
            }
        }

        if(index != -1)
        {
            //TRACE("%d,%d\n",index,m_CtrlAndSetting[index].CtrlID);
            BOOL bCheck = !GetCheck(m_CtrlAndSetting[index].CtrlID);
            *m_CtrlAndSetting[index].bCheck = bCheck;
        }
    }
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CClearHistoryDlg::InitArray()
{
    static CTRLID_SETTING Array[]=
    {
        {IDC_CHECK_CLEAR_INTERNAT_TEMP, &(theSetting.HistorySetting.bClearInternetTemp),    m_SysClearer.ClearInternetTemp},
        {IDC_CHECK_CLEAR_SYSTEMP,       &(theSetting.HistorySetting.bClearSysTempDir),      m_SysClearer.ClearSysTempDir},
        {IDC_CHECK_ClearBrowserAddress, &(theSetting.HistorySetting.bClearBrowserAddress),  m_SysClearer.ClearBrowseAddress},
        {IDC_CHECK_ClearFormAutoComplete,&(theSetting.HistorySetting.bClearFormAutoComplete),m_SysClearer.ClearFormAutoComplete},
        {IDC_CHECK_ClearAutoPassword,   &(theSetting.HistorySetting.bClearAutoPassword),    m_SysClearer.ClearAutoPassword},
        {IDC_CHECK_ClearFavorite,       &(theSetting.HistorySetting.bClearFavorite),        m_SysClearer.ClearFavorite},
        {IDC_CHECK_ClearRecyclebin,     &(theSetting.HistorySetting.bClearRecyclebin),      m_SysClearer.ClearRecyclebin},
        {IDC_CHECK_ClearRun,            &(theSetting.HistorySetting.bClearRun),             m_SysClearer.ClearRun},
        {IDC_CHECK_ClearDocument,       &(theSetting.HistorySetting.bClearDocument),        m_SysClearer.ClearDocument},
        {IDC_CHECK_ClearLastLoginName,  &(theSetting.HistorySetting.bClearLastLoginName),   m_SysClearer.ClearLastLoginName},
        {IDC_CHECK_ClearFindFile,       &(theSetting.HistorySetting.bClearFindFile),        m_SysClearer.ClearFindFile},
        {IDC_CHECK_ClearFindComputer,   &(theSetting.HistorySetting.bClearFindComputer),    m_SysClearer.ClearFindComputer},
        {IDC_CHECK_ClearBrowseAddress,  &(theSetting.HistorySetting.bClearBrowseAddress),   m_SysClearer.ClearBrowserAddress},
    };

    m_arySize = sizeof(Array) / sizeof(CTRLID_SETTING);
    m_CtrlAndSetting = Array;
}
