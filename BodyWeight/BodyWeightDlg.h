// BodyWeightDlg.h : header file
//

#if !defined(AFX_BODYWEIGHTDLG_H__5147A434_8B63_4811_B5A6_CFC93CAB24A6__INCLUDED_)
#define AFX_BODYWEIGHTDLG_H__5147A434_8B63_4811_B5A6_CFC93CAB24A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBodyWeightDlg dialog

class CBodyWeightDlg : public CDialog
{
// Construction
public:
	CBodyWeightDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBodyWeightDlg)
	enum { IDD = IDD_BODYWEIGHT_DIALOG };
	int		m_nSex;
	CString	m_stResult;
	int		m_etTail;
	int		m_etWeight;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBodyWeightDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

    void ShowResult(CString c_level,CString c_stat,double c_bmi,double c_weight);
	// Generated message map functions
	//{{AFX_MSG(CBodyWeightDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCal();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BODYWEIGHTDLG_H__5147A434_8B63_4811_B5A6_CFC93CAB24A6__INCLUDED_)
