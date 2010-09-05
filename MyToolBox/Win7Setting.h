#if !defined(AFX_WIN7SETTING_H__A2CD23D3_1902_4EB7_8FDF_4808424AB110__INCLUDED_)
#define AFX_WIN7SETTING_H__A2CD23D3_1902_4EB7_8FDF_4808424AB110__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Win7Setting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Win7Setting dialog
#include "UILib/ResizingDialog.h"
#include "UILib/ShadeButtonST.h"
#include "FuncDef.h"
#include "CtrlAction.h"

class Win7Setting : public CResizingDialog
{
// Construction
public:
	Win7Setting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Win7Setting)
	enum { IDD = IDD_WIN7SETTING_DIALOG };
	CListCtrl	m_ListFolderType;
//	CShadeButtonST	m_BtnRestartExplorer;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Win7Setting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void GetToolbarItemCheckValue(int nIndex);
    void ClickToolbarItemCheckValue(int nIndex, BOOL bCheck);
	void InitToolBarList();

    BOOL GetCheck(UINT ID);
    void SetCheck(UINT ID,BOOL bCheck);
	static CTRL_OPERATION m_SettingOper[];
    CCtrlAction m_ctrlAction;

    EXP_TOOLBAR_LIST *m_ExpToolBarList;
    EXP_BUTTON *m_ExpToolBarCheckBtns;
    CString m_strItem;

	// Generated message map functions
	//{{AFX_MSG(Win7Setting)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
//	afx_msg void OnBtnRestartExplorer();
	afx_msg void OnCheckHideFavorites();
	afx_msg void OnCheckHideLibraries();
	afx_msg void OnCheckDisableWindowAutoArrangement();
	afx_msg void OnClickLISTFolderType(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioSelect();
	afx_msg void OnRadioUnselect();
	afx_msg void OnItemchangedLISTFolderType(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckDisableFullrowselect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ReadFullRowSelect();
	void ClearToolbarCheckBox();
	int m_nCheckboxArySize;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIN7SETTING_H__A2CD23D3_1902_4EB7_8FDF_4808424AB110__INCLUDED_)
