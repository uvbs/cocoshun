// XButtonXPTestDlg.h : header file
//

#ifndef  XBUTTONXPTESTDLG_H 
#define  XBUTTONXPTESTDLG_H 

#include "XButtonXP.h"

/////////////////////////////////////////////////////////////////////////////
// CXButtonXPTestDlg dialog

class CXButtonXPTestDlg : public CDialog
{
// Construction
public:
	CXButtonXPTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXButtonXPTestDlg)
	enum { IDD = IDD_XBUTTONXPTEST_DIALOG };
	CComboBox	m_comboIcon;
	CButton		m_chkToolbar;
	CButton		m_chkTheme;
	CButton		m_chkToggle;
	CEdit		m_edtCount2;
	CEdit		m_edtCount1;
	CXButtonXP	m_XButtonXP;
	int			m_nIcon;
	BOOL		m_bTheme;
	BOOL		m_bMultiLine;
	BOOL		m_bDisabled;
	BOOL		m_bDefault;
	BOOL		m_bMessageBox;
	BOOL		m_bPattern;
	int			m_nIconIndex;
	BOOL		m_bToolbar;
	BOOL		m_bToggle;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXButtonXPTestDlg)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CBrush m_brush;
	CString m_strButton2Title;
	CToolTipCtrl m_ToolTips;
	UINT m_nIconId;

	int GetIconIndex();

	// Generated message map functions
	//{{AFX_MSG(CXButtonXPTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnIconLeft();
	afx_msg void OnIconNo();
	afx_msg void OnIconRight();
	afx_msg void OnToggle();
	afx_msg void OnTextNo();
	afx_msg void OnTheme();
	afx_msg void OnToolbar();
	afx_msg void OnDisabled();
	afx_msg void OnMultiline();
	afx_msg void OnDefault();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPattern();
	afx_msg void OnSelendokIconCombo();
	afx_msg void OnOnlineHelp();
	afx_msg void OnColors();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // XBUTTONXPTESTDLG_H 
