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
/////////////////////////////////////////////////////////////////////////////
// CSaveLyricDlg dialog

class CSaveLyricDlg : public CResizingDialog
{
// Construction
public:
	CSaveLyricDlg(CWnd* pParent = NULL);   // standard constructor
	~CSaveLyricDlg();
	void SetLyricLine(vector <LyricLine> *LyricLines);
// Dialog Data
	//{{AFX_DATA(CSaveLyricDlg)
	enum { IDD = IDD_SAVELYRICDLG_DIALOG };
	CRichEditCtrl	m_KmcPreview;
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
	CKmcBuffer *m_KmcBuffer;
	// Generated message map functions
	//{{AFX_MSG(CSaveLyricDlg)
	afx_msg void OnBtnSavelyric();
	afx_msg void OnBtpPrview();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVELYRICDLG_H__E01387A6_78F9_4DD9_9A39_908B0978EA4C__INCLUDED_)
