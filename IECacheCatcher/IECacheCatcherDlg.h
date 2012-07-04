// IECacheCatcherDlg.h : header file
//

#if !defined(AFX_IECACHECATCHERDLG_H__41D1FAF5_2017_4A47_8327_528951B3316B__INCLUDED_)
#define AFX_IECACHECATCHERDLG_H__41D1FAF5_2017_4A47_8327_528951B3316B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <GuiButton.h>
#include <GuiEdit.h>
#include <GuiListEdit.h>
#include "IECacheThread.h"

#include "regex/deelx.h"

#include "ShellUtil.h"
#include "IECache.h"
#include "SysUtil.h"
/////////////////////////////////////////////////////////////////////////////
// CIECacheCatcherDlg dialog

class CIECacheCatcherDlg : public CDialog
{
// Construction
public:
	CIECacheCatcherDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIECacheCatcherDlg)
	enum { IDD = IDD_IECACHECATCHER_DIALOG };
	CGuiButton	m_btnOpenExportPath;
	CGuiEdit	m_editExportRecord;
	CGuiButton	m_btnOpenCachePath;
	CGuiButton	m_btnExport;
	CGuiButton	m_btnClearCache;
	CGuiButton	m_btnBrowse;
	CGuiEdit	m_editUrlPath;
	CGuiEdit	m_editFileType;
	CGuiEdit	m_editExportPath;
	CGuiEdit	m_editCachePath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIECacheCatcherDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	void InitCtrl();
	// Generated message map functions
	//{{AFX_MSG(CIECacheCatcherDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpen();
	afx_msg void OnButtonBrowse();
	afx_msg void OnButtonClearcache();
	afx_msg void OnButtonExport();
	virtual void OnCancel();
	afx_msg void OnButtonOpenExportPath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		void RetreveIECacheDirectory();

	LRESULT OnNotifyStatus(WPARAM wParam, LPARAM lParam);
	LRESULT OnNotifyExportRecord(WPARAM wParam, LPARAM lParam);
	LRESULT OnNotifyClearCacheDown(WPARAM wParam, LPARAM lParam);

	void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText);
	void AppendLineToMultilineEditCtrl(CEdit& edit, LPCTSTR pszText);
	BOOL IsValidParam();
	CString Filter;
	CString WebSite;
	CString tagPath;
	CString FilterSpliter;

	CIECacheThread m_IECacheThread;
	int m_nLineNum;
	int m_nExportCount;
	BOOL m_bStart;

	SETTING m_setting;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IECACHECATCHERDLG_H__41D1FAF5_2017_4A47_8327_528951B3316B__INCLUDED_)
