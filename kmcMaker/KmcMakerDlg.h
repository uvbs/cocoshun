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
#include "./UILib/ResizingDialog.h"
#include "./UILib/BtnST.h"
#include "ImportLyricDlg.h"
#include "MakeLyricDlg.h"
#include "SaveLyricDlg.h"
#include "HelpDlg.h"

class CKmcMakerDlg : public CResizingDialog
{
// Construction
public:
	void CreateLyricFont( int FontSize );
	CFont& GetLyricFont();
	int m_nFontsize;
	CKmcMakerDlg(CWnd* pParent = NULL);	// standard constructor
	~CKmcMakerDlg();
	
	// 把消息映射函数拿出来，用于子页面调用 
	afx_msg void OnCheckStep1();
	afx_msg void OnCheckStep2();
	afx_msg void OnCheckStep3();
	virtual void OnCancel();
// Dialog Data
	//{{AFX_DATA(CKmcMakerDlg)
	enum { IDD = IDD_KMCMAKER_DIALOG };
	CButtonST	m_BtnCancel;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKmcMakerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	HICON m_hIcon;
	CFont m_LyricFont;
	// Generated message map functions
	//{{AFX_MSG(CKmcMakerDlg)
	virtual BOOL OnInitDialog();
 	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
 	afx_msg void OnPaint();
 	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCheckHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	LRESULT OnAcceptDropFile(WPARAM wParam , LPARAM lParam );

private:
	CCheckBTGroup m_CheckGroup;

	CImportLyricDlg *m_ImportLyricDlg;
	CMakeLyricDlg	*m_MakeLyricDlg;
	CSaveLyricDlg	*m_SaveLyricDlg;
	CHelpDlg		*m_HelpDlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KMCMAKERDLG_H__C9E4CED8_1B9E_48F3_90F7_7C111ED04579__INCLUDED_)
