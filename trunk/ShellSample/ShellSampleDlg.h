// ShellSampleDlg.h : header file
//

#if !defined(AFX_SHELLSAMPLEDLG_H__ED634D47_19AA_484C_BB7B_1B591E41DE68__INCLUDED_)
#define AFX_SHELLSAMPLEDLG_H__ED634D47_19AA_484C_BB7B_1B591E41DE68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShellSampleDlg dialog

class CShellSampleDlg : public CDialog
{
// Construction
public:
	CShellSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShellSampleDlg)
	enum { IDD = IDD_SHELLSAMPLE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShellSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShellSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSendmsg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLSAMPLEDLG_H__ED634D47_19AA_484C_BB7B_1B591E41DE68__INCLUDED_)
