// SaveLyricDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KmcMaker.h"
#include "SaveLyricDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveLyricDlg dialog


CSaveLyricDlg::CSaveLyricDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CSaveLyricDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveLyricDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_KmcBuffer = NULL;
}
CSaveLyricDlg::~CSaveLyricDlg()
{
	if(m_KmcBuffer!=NULL)
		delete m_KmcBuffer;
}

void CSaveLyricDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveLyricDlg)
	DDX_Control(pDX, IDC_KMC_PRIVEW, m_KmcPreview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveLyricDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CSaveLyricDlg)
	ON_BN_CLICKED(IDC_BTN_SAVELYRIC, OnBtnSavelyric)
	ON_BN_CLICKED(IDC_BTP_PRVIEW, OnBtpPrview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveLyricDlg message handlers

void CSaveLyricDlg::OnBtnSavelyric() 
{
	
}

void CSaveLyricDlg::OnBtpPrview() 
{
	
}

void CSaveLyricDlg::SetLyricLine( vector <LyricLine> *LyricLines )
{
	m_LyricLines = LyricLines;

	if(m_KmcBuffer!=NULL)
		delete m_KmcBuffer;
	m_KmcBuffer = new CKmcBuffer(m_LyricLines);
	CString kmc;
	m_KmcBuffer->GetKmcLyric(kmc);
	m_KmcPreview.SetWindowText(kmc);
}


BOOL CSaveLyricDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	SetControlInfo(IDC_KMC_PRIVEW,RESIZE_BOTH);

		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
