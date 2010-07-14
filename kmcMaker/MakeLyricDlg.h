#if !defined(AFX_MAKELYRICDLG_H__BDCEA29D_FB44_4249_8AF8_05AC5A712424__INCLUDED_)
#define AFX_MAKELYRICDLG_H__BDCEA29D_FB44_4249_8AF8_05AC5A712424__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MakeLyricDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMakeLyricDlg dialog

class CMakeLyricDlg : public CDialog
{
// Construction
public:
	CMakeLyricDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMakeLyricDlg)
	enum { IDD = IDD_MAKELYRICDLG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMakeLyricDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMakeLyricDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAKELYRICDLG_H__BDCEA29D_FB44_4249_8AF8_05AC5A712424__INCLUDED_)
