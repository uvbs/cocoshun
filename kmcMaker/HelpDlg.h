//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_HELPDLG_H__B3B7F4BC_B18C_4535_BB9F_FB257B7D9588__INCLUDED_)
#define AFX_HELPDLG_H__B3B7F4BC_B18C_4535_BB9F_FB257B7D9588__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HelpDlg.h : header file
//
#include "UILib/ResizingDialog.h"
/////////////////////////////////////////////////////////////////////////////
// CHelpDlg dialog

class CHelpDlg : public CResizingDialog
{
// Construction
public:
	void OpenHelp();
	CHelpDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHelpDlg)
	enum { IDD = IDD_HELP };
	CWebBrowser2	m_WebBrowser;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHelpDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELPDLG_H__B3B7F4BC_B18C_4535_BB9F_FB257B7D9588__INCLUDED_)
