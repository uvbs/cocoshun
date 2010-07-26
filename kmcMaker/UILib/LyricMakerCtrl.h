#if !defined(AFX_LYRICMAKERCTRL_H__B75B0B9E_367D_11D6_AB38_00D0B70C3D79__INCLUDED_)
#define AFX_LYRICMAKERCTRL_H__B75B0B9E_367D_11D6_AB38_00D0B70C3D79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../Lyric.h"
#include "../wmpplayer4.h"

class CLyricMakerCtrl : public CStatic
{
// Construction
public:
	CLyricMakerCtrl();

// Attributes
protected:
	HDC m_hBackgroundDC; 
	HDC m_hLyricDC; 
	HFONT m_hLyricFont;

	int m_ClientWith;
	int m_ClientHeight;
	int m_LyricPosY;
	int m_LyricPosX;

	vector <LyricLine> *m_LyricLines;
	CWMPPlayer4 *m_MediaPlayer;
// Operations
public:
	void SetLyricLines( vector <LyricLine> *Ll );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LyricMakerCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetMediaPlayer(CWMPPlayer4 *MediaPlayer);
	int m_FontHeight;
	virtual ~CLyricMakerCtrl();

	// Generated message map functions
protected:
	void DrawLyricLine(int nLine);
	void DrawLyric();
	void Initialize();
	void LoadPicture(int nResourceID, HDC &hDestinationDC, int &nWidth, int &nHeight, HDC hDC);

	//{{AFX_MSG(LyricMakerCtrl)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer( UINT nIDEvent );
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LYRICMAKERCTRL_H__B75B0B9E_367D_11D6_AB38_00D0B70C3D79__INCLUDED_)
