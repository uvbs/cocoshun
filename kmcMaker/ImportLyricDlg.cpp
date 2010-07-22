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
	DDX_Control(pDX, IDC_COMBO_ENCODE, m_ComboEncode);
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
	
	// Get current locale code page
	UINT nCurrentCodePage = CStdioFileEx::GetCurrentLocaleCodePage();

	// Fill the combo box with strings and our map with strings and code page IDs
// 	AddCodePage(_T("United States"), 437, nCurrentCodePage);
// 	AddCodePage(_T("Arabic"), 1256, nCurrentCodePage);
// 	AddCodePage(_T("Greek"), 737, nCurrentCodePage);
// 	AddCodePage(_T("Baltic"), 1257, nCurrentCodePage);
// 	AddCodePage(_T("Multilingual (Latin I)"), 850, nCurrentCodePage);
// 	AddCodePage(_T("Slavic (Latin II)"), 852, nCurrentCodePage);
// 	AddCodePage(_T("Thai"), 874, nCurrentCodePage);
// 	AddCodePage(_T("Japanese"), 932, nCurrentCodePage);
	AddCodePage(_T("Chinese (¼òÌå)"), 936, nCurrentCodePage);
// 	AddCodePage(_T("Korean"), 949, nCurrentCodePage);
	AddCodePage(_T("Chinese (·±Ìå)"), 950, nCurrentCodePage);
//	AddCodePage(_T("Hebrew"), 1255, nCurrentCodePage);
// 	AddCodePage(_T("Windows 3.1 US (ANSI)"), 1252, nCurrentCodePage);
// 	AddCodePage(_T("Windows 3.1 Greek"), 1253, nCurrentCodePage);
	AddCodePage(_T("UTF-8"), CP_UTF8, nCurrentCodePage);
	// Add current as "unknown" if we didn't find it
	if (m_sCurrentCPDesc.IsEmpty())
	{
		AddCodePage(_T("Unknown"), nCurrentCodePage, nCurrentCodePage);
	}
	
	// Select the current locale in the combo
	m_ComboEncode.SetCurSel(m_ComboEncode.FindString(-1, m_sCurrentCPDesc));

	//set Controls
	SetControlInfo(IDC_LYRIC_EDITOR,RESIZE_BOTH);
	SetControlInfo(IDC_BTN_IMPORT,ANCHORE_LEFT | ANCHORE_BOTTOM);
	SetControlInfo(IDC_STATIC_ENCODE,ANCHORE_LEFT | ANCHORE_BOTTOM);
	SetControlInfo(IDC_COMBO_ENCODE,ANCHORE_LEFT | ANCHORE_BOTTOM);


	m_LyricEditor.SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImportLyricDlg::AddCodePage(IN const CString& sDesc,IN const UINT nCodePage,IN const UINT nCurrentCP)
{
	CString	sCPDesc = sDesc;
	_TCHAR	szBuffer[64];
	
	_itot(nCodePage, szBuffer, 10);
	
	// Add code page to desc
	sCPDesc += (CString)_T(" - ") + (CString)szBuffer;
	
	// Add "(this locale)" if current locale code page
	if (nCodePage == nCurrentCP)
	{
		sCPDesc += _T(" (this locale)");
		
		// Store it so we know we found it
		m_sCurrentCPDesc = sCPDesc;
	}
	
	// Add to map
	m_mapCodePageDescsToCodePages.SetAt(sCPDesc, (void*)nCodePage);
	
	// Add to combo
	m_ComboEncode.AddString(sCPDesc);
}

void CImportLyricDlg::OnImportLyric() 
{
 	char BASED_CODE szFilter[] = "Lyric (*.lrc)|*.lrc|All Files (*.*)|*.*||";
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
