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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CImportLyricDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportLyricDlg)
	DDX_Control(pDX, IDC_LYRIC_EDITOR, m_LyricEditor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportLyricDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CImportLyricDlg)
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
	
	SetControlInfo(IDC_LYRIC_EDITOR,RESIZE_BOTH);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
