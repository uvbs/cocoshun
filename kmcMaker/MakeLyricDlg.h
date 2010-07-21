//{{AFX_INCLUDES()
#include "activemovie3.h"
//}}AFX_INCLUDES
#if !defined(AFX_MAKELYRICDLG_H__BDCEA29D_FB44_4249_8AF8_05AC5A712424__INCLUDED_)
#define AFX_MAKELYRICDLG_H__BDCEA29D_FB44_4249_8AF8_05AC5A712424__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MakeLyricDlg.h : header file
//

#include "UILib/ResizingDialog.h"
#include "UILib/LyricMakerCtrl.h"
#include "Lyric.h"
/////////////////////////////////////////////////////////////////////////////
// CMakeLyricDlg dialog

class CMakeLyricDlg : public CResizingDialog
{
// Construction
public:
	void InitLyric(CString Lyric);
	CMakeLyricDlg(CWnd* pParent = NULL);   // standard constructor
	CArray <LyricLine, LyricLine&> m_LyricLines;

// Dialog Data
	//{{AFX_DATA(CMakeLyricDlg)
	enum { IDD = IDD_MAKELYRICDLG_DIALOG };
	CLyricMakerCtrl	m_LyricMaker;
	CActiveMovie3	m_MediaPlayer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMakeLyricDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMakeLyricDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnOpen();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GetEnWord(CString &Str, int &Pos, CString &StrWord);
	void GetSpace(CString &Str, int &Pos, CString &StrSpace);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAKELYRICDLG_H__BDCEA29D_FB44_4249_8AF8_05AC5A712424__INCLUDED_)
