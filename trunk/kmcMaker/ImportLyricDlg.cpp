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
	: CDialog(CImportLyricDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportLyricDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CImportLyricDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportLyricDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportLyricDlg, CDialog)
	//{{AFX_MSG_MAP(CImportLyricDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportLyricDlg message handlers
