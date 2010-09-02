// MyToolBoxDlg.h : header file
//

#if !defined(AFX_MYTOOLBOXDLG_H__C43FF463_8924_4AE4_B8CD_C0BA03EE95B3__INCLUDED_)
#define AFX_MYTOOLBOXDLG_H__C43FF463_8924_4AE4_B8CD_C0BA03EE95B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyToolBoxDlg dialog
#include "UILib/ResizingDialog.h"
#include "GeneralTool.h"
#include "Win7Setting.h"
#include "ClearHistoryDlg.h"
#include "UILib/CheckBTGroup.h"
#include "UILib/Btnst.h"

class CMyToolBoxDlg : public CResizingDialog
{
// Construction
public:
	CMyToolBoxDlg(CWnd* pParent = NULL);	// standard constructor
    ~CMyToolBoxDlg();
// Dialog Data
	//{{AFX_DATA(CMyToolBoxDlg)
	enum { IDD = IDD_MYTOOLBOX_DIALOG };
	CButtonST	m_BtnExit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyToolBoxDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CCheckBTGroup m_CheckGroup;
	GeneralTool *m_GeneralTool;
    CClearHistoryDlg *m_ClearTool;
	Win7Setting *m_Win7Setting;
	// Generated message map functions
	//{{AFX_MSG(CMyToolBoxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnWin7setting();
	afx_msg void OnBtnGeneraltool();
	afx_msg void OnBtnCleartool();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTOOLBOXDLG_H__C43FF463_8924_4AE4_B8CD_C0BA03EE95B3__INCLUDED_)
