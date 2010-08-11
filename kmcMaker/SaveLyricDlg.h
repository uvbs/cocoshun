#if !defined(AFX_SAVELYRICDLG_H__E01387A6_78F9_4DD9_9A39_908B0978EA4C__INCLUDED_)
#define AFX_SAVELYRICDLG_H__E01387A6_78F9_4DD9_9A39_908B0978EA4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveLyricDlg.h : header file
//
#include "Lyric.h"
#include "./UILib/ResizingDialog.h"
#include "KMCBuffer.h"
#include "LyricText.h"
#include "UILib/BtnST.h"
/////////////////////////////////////////////////////////////////////////////
// CSaveLyricDlg dialog

class CSaveLyricDlg : public CResizingDialog
{
// Construction
public:
	BOOL CheckLeave();
	BOOL IsSaved();
	CSaveLyricDlg(CWnd* pParent = NULL);   // standard constructor
	~CSaveLyricDlg();
	void SetLyricInfo(vector <LyricLine> *LyricLines,CLyricText::LyricHeader *LyricHeader);
	
	void UpdatePreviewLyric();

// Dialog Data
	//{{AFX_DATA(CSaveLyricDlg)
	enum { IDD = IDD_SAVELYRICDLG_DIALOG };
	CButtonST	m_BtnSaveLyric;
	CButtonST	m_BtnPrevStep;
	CButtonST	m_BtnExit;
	CRichEditCtrl	m_KmcPreview;
	CString	m_editTi;
	CString	m_editAl;
	CString	m_editAr;
	CString	m_editBy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveLyricDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	vector <LyricLine> *m_LyricLines;
	CLyricText::LyricHeader *m_LyricHeader;

	CKmcBuffer *m_KmcBuffer;
	BOOL m_bSaved;
	// Generated message map functions
	//{{AFX_MSG(CSaveLyricDlg)
	afx_msg void OnBtnSavelyric();
	afx_msg void OnBtpPrview();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditTi();
	afx_msg void OnChangeEditBy();
	afx_msg void OnChangeEditAr();
	afx_msg void OnChangeEditAl();
	afx_msg void OnBtnSavePrevstep();
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVELYRICDLG_H__E01387A6_78F9_4DD9_9A39_908B0978EA4C__INCLUDED_)
