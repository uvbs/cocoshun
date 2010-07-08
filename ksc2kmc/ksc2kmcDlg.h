// ksc2kmcDlg.h : header file
//

#if !defined(AFX_KSC2KMCDLG_H__9056942F_AF69_441E_AD88_A727870A2912__INCLUDED_)
#define AFX_KSC2KMCDLG_H__9056942F_AF69_441E_AD88_A727870A2912__INCLUDED_

#include "FileFinder.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CKsc2kmcDlg dialog

const UINT WM_MYUPDATEDATA = ::RegisterWindowMessage(_T("MyUpdateData"));
class CKsc2kmcDlg : public CDialog
{
// Construction
public:
	CKsc2kmcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKsc2kmcDlg)
	enum { IDD = IDD_KSC2KMC_DIALOG };
	CProgressCtrl	m_Progress;
	CButton	m_BtnStop;
	CButton	m_BtnCancel;
	CButton	m_BtnSearch;
	CString	m_srcPath;
	CString	m_tagPath;
	CString	m_StaticStatus;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKsc2kmcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKsc2kmcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonBrowseSrc();
	afx_msg void OnButtonBrowseTag();
	afx_msg void OnBtnSearch();
	afx_msg void OnBtnStop();
	virtual void OnCancel();
	afx_msg void OnUpdateMyData(WPARAM wp, LPARAM lp); 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFileFinder m_fileFinder;

	static DWORD WINAPI ConvertProc(LPVOID lpParameter);

	BOOL m_bProcess;

	BOOL m_bClose;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KSC2KMCDLG_H__9056942F_AF69_441E_AD88_A727870A2912__INCLUDED_)
