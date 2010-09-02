#if !defined(AFX_CLEARHISTORYDLG_H__75755C5E_33CF_4C4B_873A_792CAAC0F989__INCLUDED_)
#define AFX_CLEARHISTORYDLG_H__75755C5E_33CF_4C4B_873A_792CAAC0F989__INCLUDED_

#include "SysClearer.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClearHistoryDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClearHistoryDlg dialog

class CClearHistoryDlg : public CDialog
{
// Construction
public:
	CClearHistoryDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CClearHistoryDlg)
	enum { IDD = IDD_CLEAR_HISTORY_BOOT_DLG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClearHistoryDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CClearHistoryDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCheckClearInternatTemp();
	afx_msg void OnCheckClearSystemp();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void ReadCheckBoxValue();
    static CSysClearer m_SysClearer;

	void SetCheck(UINT ID,BOOL bCheck);
	BOOL GetCheck(UINT ID);

	typedef void (CSysClearer::*FUNC_PTR)();
    struct CTRLID_SETTING
    {
        UINT CtrlID;
        BOOL *bCheck;
		FUNC_PTR FuncPtr;
    };
	FUNC_PTR m_func;
    static CTRLID_SETTING m_CtrlAndSetting[];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLEARHISTORYDLG_H__75755C5E_33CF_4C4B_873A_792CAAC0F989__INCLUDED_)
