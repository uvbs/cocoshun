// ImportLyricDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KmcMaker.h"
#include "ImportLyricDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportLyricDlg dialog


CImportLyricDlg::CImportLyricDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CImportLyricDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportLyricDlg)
	//}}AFX_DATA_INIT
}


void CImportLyricDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportLyricDlg)
	DDX_Control(pDX, IDC_BTN_IMPORT, m_BtnImport);
	DDX_Control(pDX, IDC_LYRIC_EDITOR, m_LyricEditor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportLyricDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CImportLyricDlg)
	ON_BN_CLICKED(IDC_BTN_IMPORT, OnImportLyric)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportLyricDlg message handlers

void CImportLyricDlg::OnCancel() 
{
//	CResizingDialog::OnCancel();
}

BOOL CImportLyricDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	//set Controls
	SetControlInfo(IDC_LYRIC_EDITOR,RESIZE_BOTH);
	SetControlInfo(IDC_BTN_IMPORT,ANCHORE_LEFT | ANCHORE_BOTTOM);

	m_LyricEditor.SetFocus();
//	LoadLyric(_T("F:\\Lrc\\UTF-8-UINX.LRC"));
	LoadLyric(_T("E:\\Kelly Clarkson - Because Of You.lrc"));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CImportLyricDlg::OnImportLyric() 
{
 	TCHAR szFilter[] = _T("Lyric (*.lrc)|*.lrc|All Files (*.*)|*.*||");
 	CFileDialogEx ImportFileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);;
 	if( ImportFileDlg.DoModal() == IDOK)
	{
		LoadLyric(ImportFileDlg.GetFileName());
	}
}

void CImportLyricDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CResizingDialog::OnOK();
}

LRESULT CImportLyricDlg::OnAcceptDropFile(WPARAM wParam , LPARAM lParam  )
{
	TCHAR *DropFileName = (TCHAR *)wParam;

	LoadLyric(DropFileName);
	return 1L;
}


BOOL CImportLyricDlg::LoadLyric(LPCTSTR pszFileName)
{
	if(!m_LyricText.LoadLyric(pszFileName))
	{
		return FALSE;
	}

	m_LyricEditor.SetWindowText(m_LyricText.GetText());

	return TRUE;
}
