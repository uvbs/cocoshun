#if !defined(AFX_IMPORTLYRICDLG_H__9E4C4127_C6AC_4390_AAC0_06CD9CC65C75__INCLUDED_)
#define AFX_IMPORTLYRICDLG_H__9E4C4127_C6AC_4390_AAC0_06CD9CC65C75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportLyricDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportLyricDlg dialog

class CImportLyricDlg : public CDialog
{
// Construction
public:
	CImportLyricDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImportLyricDlg)
	enum { IDD = IDD_IMPORTLYRICDLG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportLyricDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImportLyricDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTLYRICDLG_H__9E4C4127_C6AC_4390_AAC0_06CD9CC65C75__INCLUDED_)
