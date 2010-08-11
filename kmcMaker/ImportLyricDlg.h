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
#include "UILib/BtnST.h"
/////////////////////////////////////////////////////////////////////////////
// CImportLyricDlg dialog

class CImportLyricDlg : public CResizingDialog
{
// Construction
public:
	void GetLyric(CString &Lyric);
	BOOL CheckLeave();
	CLyricText m_LyricText;
	CImportLyricDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImportLyricDlg)
	enum { IDD = IDD_IMPORTLYRICDLG_DIALOG };
	CButtonST	m_BtnNextStep;
	CButtonST	m_BtnFilter;
	CButtonST m_BtnImport;
	CMyRichEdit m_LyricEditor;
	CString	m_EditReplaceTxt;
	CString	m_EditTargetTxt;
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
	BOOL GetCheck(UINT ID);
	void SetCheck(UINT ID,BOOL bCheck = TRUE);
	
	int GetFileLenght( LPCTSTR pszFileName );
	// Generated message map functions
	//{{AFX_MSG(CImportLyricDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnImportLyric();
	virtual void OnOK();
	afx_msg void OnBtnFilter();
	afx_msg void OnBtnNextstep();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	LRESULT OnAcceptDropFile(WPARAM wParam = 0, LPARAM lParam = 0 );

private:
	CString m_OrgText;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTLYRICDLG_H__9E4C4127_C6AC_4390_AAC0_06CD9CC65C75__INCLUDED_)
