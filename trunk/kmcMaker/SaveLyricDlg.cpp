// SaveLyricDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KmcMaker.h"
#include "SaveLyricDlg.h"
#include "UILib/FileDialogEx.h"
#include "Util/textfile.h"

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
	m_editTi = _T("");
	m_editAl = _T("");
	m_editAr = _T("");
	m_editBy = _T("");
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
	DDX_Text(pDX, IDC_EDIT_TI, m_editTi);
	DDX_Text(pDX, IDC_EDIT_AL, m_editAl);
	DDX_Text(pDX, IDC_EDIT_AR, m_editAr);
	DDX_Text(pDX, IDC_EDIT_BY, m_editBy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveLyricDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CSaveLyricDlg)
	ON_BN_CLICKED(IDC_BTN_SAVELYRIC, OnBtnSavelyric)
	ON_BN_CLICKED(IDC_BTP_PRVIEW, OnBtpPrview)
	ON_EN_CHANGE(IDC_EDIT_TI, OnChangeEditTi)
	ON_EN_CHANGE(IDC_EDIT_BY, OnChangeEditBy)
	ON_EN_CHANGE(IDC_EDIT_AR, OnChangeEditAr)
	ON_EN_CHANGE(IDC_EDIT_AL, OnChangeEditAl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveLyricDlg message handlers

void CSaveLyricDlg::OnBtnSavelyric() 
{
	TCHAR szFilter[] = _T("Karaoke Media Lyric (*.kmc)|*.kmc|All Files (*.*)|*.*||");
	CFileDialogEx FileDlg(FALSE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);


	CString Kmc;
	m_KmcPreview.GetWindowText(Kmc);
	if( FileDlg.DoModal() == IDOK && !Kmc.IsEmpty())
	{
		CString kmcName = FileDlg.GetPathName();
		
		// set filename
		int pos = kmcName.ReverseFind('.');
		if(pos == -1)
		{
			kmcName+=".kmc";
		}

		CTextFileWrite fw(kmcName,CTextFileBase::UTF_8);
		if(! fw.IsOpen())
		{
			fw.Close();
			return;
		}
		fw.Write(Kmc);
	}
}

void CSaveLyricDlg::OnBtpPrview() 
{
	
}

void CSaveLyricDlg::SetLyricInfo( vector <LyricLine> *LyricLines ,CLyricText::LyricHeader *LyricHeader)
{
	m_LyricLines = LyricLines;
	m_LyricHeader = LyricHeader;

	if(m_KmcBuffer!=NULL)
		delete m_KmcBuffer;

	m_KmcBuffer = new CKmcBuffer(m_LyricLines);
	m_KmcBuffer->SetLyricHeader(m_LyricHeader);

	UpdatePreviewLyric();
	
	if(m_LyricHeader !=NULL)
	{
		m_editAl = m_LyricHeader->al;
		m_editAr = m_LyricHeader->ar;
		m_editBy = m_LyricHeader->by;
		m_editTi = m_LyricHeader->ti;
		UpdateData(FALSE);
	}
}


BOOL CSaveLyricDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	SetControlInfo(IDC_KMC_PRIVEW,RESIZE_BOTH);

	
	SetControlInfo(IDC_STATIC_TI, ANCHORE_RIGHT);
	SetControlInfo(IDC_STATIC_AR,ANCHORE_RIGHT);
	SetControlInfo(IDC_STATIC_AL,ANCHORE_RIGHT);
	SetControlInfo(IDC_STATIC_BY,ANCHORE_RIGHT);

	SetControlInfo(IDC_EDIT_TI,ANCHORE_RIGHT);
	SetControlInfo(IDC_EDIT_AR,ANCHORE_RIGHT);
	SetControlInfo(IDC_EDIT_AL,ANCHORE_RIGHT);
	SetControlInfo(IDC_EDIT_BY,ANCHORE_RIGHT);


	SetControlInfo(IDC_STATIC_SAVETIP, ANCHORE_RIGHT);
	SetControlInfo(IDC_STATIC_TIPEXT, ANCHORE_RIGHT);
	SetControlInfo(IDC_RADIO_KMC, ANCHORE_RIGHT);
	SetControlInfo(IDC_RADIO_XML, ANCHORE_RIGHT);
	SetControlInfo(IDC_BTN_SAVELYRIC,ANCHORE_RIGHT);

	SetControlInfo(IDC_BTN_SAVE_PREVSTEP, ANCHORE_RIGHT|ANCHORE_BOTTOM);
	SetControlInfo(IDC_BTN_EXIT, ANCHORE_RIGHT|ANCHORE_BOTTOM);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSaveLyricDlg::UpdatePreviewLyric()
{
	if(m_KmcBuffer !=NULL)
	{
		if(m_LyricHeader !=NULL)
		{
			UpdateData(TRUE);
			if(!m_editAl.IsEmpty())
				m_LyricHeader->al = m_editAl;

			if(!m_editAr.IsEmpty())
				m_LyricHeader->ar = m_editAr;

			if(!m_editBy.IsEmpty())
				m_LyricHeader->by = m_editBy;

			if(!m_editTi.IsEmpty())
				m_LyricHeader->ti = m_editTi;
		}
		UpdateData(FALSE);

		CString kmc;
		m_KmcBuffer->GetKmcLyric(kmc);
		m_KmcPreview.SetWindowText(kmc);
	}
}

void CSaveLyricDlg::OnChangeEditTi() 
{
	UpdatePreviewLyric();
}

void CSaveLyricDlg::OnChangeEditBy() 
{
	UpdatePreviewLyric();
}

void CSaveLyricDlg::OnChangeEditAr() 
{
	UpdatePreviewLyric();
}

void CSaveLyricDlg::OnChangeEditAl() 
{
	UpdatePreviewLyric();
}
