// KmcMakerDlg.h : header file
//

#if !defined(AFX_KMCMAKERDLG_H__C9E4CED8_1B9E_48F3_90F7_7C111ED04579__INCLUDED_)
#define AFX_KMCMAKERDLG_H__C9E4CED8_1B9E_48F3_90F7_7C111ED04579__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CKmcMakerDlg dialog
#include "CheckBTGroup.h"
#include "./UILib/DynamicLayoutExport.h"

class CKmcMakerDlg : public CDialog
{
// Construction
public:
	CKmcMakerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKmcMakerDlg)
	enum { IDD = IDD_KMCMAKER_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKmcMakerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKmcMakerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckStep1();
	afx_msg void OnCheckStep2();
	afx_msg void OnCheckStep3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static UINT CheckBtnIDs[];
	CCheckBTGroup m_CheckGroup;
	DynamicLayout::CDynamicLayout m_DLayout;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KMCMAKERDLG_H__C9E4CED8_1B9E_48F3_90F7_7C111ED04579__INCLUDED_)
