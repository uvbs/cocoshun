#if !defined(AFX_LYRICMAKERCTRL_H__B75B0B9E_367D_11D6_AB38_00D0B70C3D79__INCLUDED_)
#define AFX_LYRICMAKERCTRL_H__B75B0B9E_367D_11D6_AB38_00D0B70C3D79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../Lyric.h"
#include "../wmpplayer4.h"
#include "../KmcBuffer.h"


#define COLOR_BLACK RGB(0,0,0)
#define COLOR_WHITE RGB(255,255,255)
#define COLOR_RED RGB(250,0,0)
#define COLOR_GREEN RGB(0,250,0)
#define COLOR_BLUE RGB(0,0,250)

class CLyricMakerCtrl : public CStatic
{
// Construction
public:
	CLyricMakerCtrl();

// Attributes
protected:
	class CTextBoard
	{
		protected:
			LyricWord *GetLyricWord(int y, int x);
			int GetTextWidth(CString &Text);
			int GetTextWidth(LPCTSTR pText);
			vector <LyricLine> *LyricLines;
			CWMPPlayer4 *MediaPlayer;
			CDC *pDC;
			CWnd *pWnd;
			int LineCount;
			int LyricPosX;
			int LyricPosY;
			HFONT LyricFont;
			int FontHeight;
			int BoardWith;
			int BoardHeight;

			int BoardCY;
			int MidLineNum;
			
			HDC m_hBackGround;

			HDC hBitMap;
			int BmpWidth;
			int BmpHeight;

			BOOL bDrawIncrementWord;
			int  nDrawIncrementWordWidth;

			void LoadPicture(int nResourceID);
			void SetFont();
			void InitGraph();
			void SetPlayPosition();
			double GetCurrentPosition();
			void SetCurrentPosition(double newPos);
			void DrawLine(int LyricPosY);
			void DrawLine(int BoardPosY, int LyricPosY, BOOL bMarkDraw = FALSE);
		
		public:
			void SetStartLine(int nModifiedStart);
			void DrawIncrementWord();
			CTextBoard (vector <LyricLine> *LyricLines,CWnd *Wnd,CWMPPlayer4 *MediaPlayer);
			~CTextBoard();

			void RefreshBackground();
			void Draw();

			void MarkWordEnd();
			void MovePrevLine();
			void UnMarkPrevWord();
			void MarkNextWord();

			void SetBoardWidth(int Width);
			void SetBoardHeight(int Height);

		private:
			void StopDrawIncrementWord();
			void StartDrawIncrementWord();
			void RefreshMidLine();
			int GetLineOffset();
			LyricWord* GetWord(int y,int x);
			void DrawWord(HDC hDC, int y, int x, BOOL bOffset = TRUE);
			LPCTSTR GetLyricLineText(int y);
			LyricLine* GetLyricLine(int y);
			void DrawBackground();
	};

	CTextBoard *m_TextBoard;

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
	void SetStartLine(int nModifiedStart);
	void StopPrivew();
	void SetMediaPlayer(CWMPPlayer4 *MediaPlayer);
	virtual ~CLyricMakerCtrl();

	void StartDrawIncrementWord(CDC *pDC,CString Word, CRect FontRect, int WordWidth);
	void Preview();

	// Generated message map functions
protected:
	BOOL m_IsPreview;
	//{{AFX_MSG(LyricMakerCtrl)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer( UINT nIDEvent );
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
	
private:
	CDC *m_TextBoardDC;
	int m_IncrementWordWidth;
	CRect m_IncrementWordRect;
	CString m_IncrementWord;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LYRICMAKERCTRL_H__B75B0B9E_367D_11D6_AB38_00D0B70C3D79__INCLUDED_)
