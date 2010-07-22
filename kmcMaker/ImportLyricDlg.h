#if !defined(AFX_IMPORTLYRICDLG_H__9E4C4127_C6AC_4390_AAC0_06CD9CC65C75__INCLUDED_)
#define AFX_IMPORTLYRICDLG_H__9E4C4127_C6AC_4390_AAC0_06CD9CC65C75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportLyricDlg.h : header file
//
#include "UILib/ResizingDialog.h"
#include "UILib/BtnST.h"
#include "UILib/FileDialogEx.h"
//#include "UILib/AutoRichEditCtrl.h"
#include  "UILib/MyRichEdit.h"
#include "LyricText.h"	// Added by ClassView
#include "Util/StdioFileEx.h"
/////////////////////////////////////////////////////////////////////////////
// CImportLyricDlg dialog

class CImportLyricDlg : public CResizingDialog
{
// Construction
public:
	CLyricText m_LyricText;
	CImportLyricDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImportLyricDlg)
	enum { IDD = IDD_IMPORTLYRICDLG_DIALOG };
	CComboBox	m_ComboEncode;
	CButton m_BtnImport;
	CMyRichEdit m_LyricEditor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportLyricDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL LoadLyric(LPCTSTR pszFileName);

	// Generated message map functions
	//{{AFX_MSG(CImportLyricDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnImportLyric();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LRESULT OnAcceptDropFile(WPARAM wParam = 0, LPARAM lParam = 0 );
	void AddCodePage(IN const CString& sDesc,IN const UINT nCodePage,IN const UINT nCurrentCP);
	CMapStringToPtr	m_mapCodePageDescsToCodePages;
	CString				m_sCurrentCPDesc;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTLYRICDLG_H__9E4C4127_C6AC_4390_AAC0_06CD9CC65C75__INCLUDED_)
