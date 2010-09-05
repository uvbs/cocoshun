#if !defined(AFX_GENERALTOOL_H__95451799_906C_464A_8690_E11BABFAF43B__INCLUDED_)
#define AFX_GENERALTOOL_H__95451799_906C_464A_8690_E11BABFAF43B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GeneralTool.h : header file
//
#include "UILib/ShadeButtonST.h"
/////////////////////////////////////////////////////////////////////////////
// GeneralTool dialog
#include "UILib/ResizingDialog.h"

class GeneralTool : public CResizingDialog
{
// Construction
public:
	GeneralTool(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GeneralTool)
	enum { IDD = IDD_GENERALTOOL_DIALOG };
	CShadeButtonST m_BtnRebulidIconCache;
	CShadeButtonST	m_BtnRestartExplorer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GeneralTool)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GeneralTool)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBtnRebulidIconCache();
	afx_msg void OnBtnRestartExplorer();
	afx_msg void OnCheckShowboottime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERALTOOL_H__95451799_906C_464A_8690_E11BABFAF43B__INCLUDED_)
