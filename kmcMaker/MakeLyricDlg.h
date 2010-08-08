//{{AFX_INCLUDES()
#include "wmpplayer4.h"
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
#include "UILib/BitmapSlider.h"
/////////////////////////////////////////////////////////////////////////////
// CMakeLyricDlg dialog

class CMakeLyricDlg : public CResizingDialog
{
// Construction
public:
	BOOL CheckLeaveToPrev();
	void FocusToLyricMaker();
	void InitLyric(CString Lyric);
	CMakeLyricDlg(CWnd* pParent = NULL);   // standard constructor
	vector <LyricLine> m_LyricLines;
	BOOL IsMarkedAll();
// Dialog Data
	//{{AFX_DATA(CMakeLyricDlg)
	enum { IDD = IDD_MAKELYRICDLG_DIALOG };
	CLyricMakerCtrl	m_LyricMaker;
	CWMPPlayer4	m_MediaPlayer;
	CBitmapSlider m_SliderMP;
	//}}AFX_DATA
	int		m_nMax;
	int		m_nMin;
	int		m_nPos;

	// 初子控件作为外部方法调用
	afx_msg void OnBtnPlayPause();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMakeLyricDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
// Implementation
protected:
	void InitPlaySlider();
	LRESULT OnAcceptDropFile(WPARAM wParam = 0, LPARAM lParam = 0 );
	// Generated message map functions
	//{{AFX_MSG(CMakeLyricDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnOpen();
	afx_msg void OnBtnPriview();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnStop();
	afx_msg void OnOpenStateChangeMediaplayer(long NewState);
	afx_msg void OnPlayStateChangeMediaplayer(long NewState);
	afx_msg void OnPositionChangeMediaplayer(double oldPosition, double newPosition);
	afx_msg void OnBtnPrevstep();
	afx_msg void OnBtnNextstep();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg LRESULT OnBitmapSliderMoved(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBitmapSliderMoving(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	BOOL IsMarkedFirst();
	BOOL m_IsSliderMoving;
	void InitMediaCtrls();
	
	void ShowPlayerTimeInfo();
	void GetEnWord(CString &Str, int &Pos, CString &StrWord);
	void GetSpace(CString &Str, int &Pos, CString &StrSpace);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAKELYRICDLG_H__BDCEA29D_FB44_4249_8AF8_05AC5A712424__INCLUDED_)
