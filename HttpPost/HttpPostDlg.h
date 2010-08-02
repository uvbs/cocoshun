// HttpPostDlg.h : header file
//

#if !defined(AFX_HTTPPOSTDLG_H__8BE1500A_2BAB_4B18_9CA4_D7545038CBBA__INCLUDED_)
#define AFX_HTTPPOSTDLG_H__8BE1500A_2BAB_4B18_9CA4_D7545038CBBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHttpPostDlg dialog

class CHttpPostDlg : public CDialog
{
// Construction
public:
	CHttpPostDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHttpPostDlg)
	enum { IDD = IDD_HTTPPOST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHttpPostDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHttpPostDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnSendpost();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTTPPOSTDLG_H__8BE1500A_2BAB_4B18_9CA4_D7545038CBBA__INCLUDED_)
