#if !defined(AFX_SAVELYRICDLG_H__E01387A6_78F9_4DD9_9A39_908B0978EA4C__INCLUDED_)
#define AFX_SAVELYRICDLG_H__E01387A6_78F9_4DD9_9A39_908B0978EA4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveLyricDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaveLyricDlg dialog

class CSaveLyricDlg : public CDialog
{
// Construction
public:
	CSaveLyricDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSaveLyricDlg)
	enum { IDD = IDD_SAVELYRICDLG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveLyricDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaveLyricDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVELYRICDLG_H__E01387A6_78F9_4DD9_9A39_908B0978EA4C__INCLUDED_)
