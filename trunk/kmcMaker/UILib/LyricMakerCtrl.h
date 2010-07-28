#if !defined(AFX_LYRICMAKERCTRL_H__B75B0B9E_367D_11D6_AB38_00D0B70C3D79__INCLUDED_)
#define AFX_LYRICMAKERCTRL_H__B75B0B9E_367D_11D6_AB38_00D0B70C3D79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "../Lyric.h"
#include "../wmpplayer4.h"
#include "../KmcBuffer.h"

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
			CKmcBuffer *m_kmcBuffer;
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

			HDC BitMap;
			int BmpWidth;
			int BmpHeight;


			void LoadPicture(int nResourceID);
			void CreateFont();
			void InitGraph();

		public:
			void MoveNextLine();
			void MovePrevLine();
			void UnMarkPrevWord();
			void MarkNextWord();
			long GetCurrentPosition();
			void SetCurrentPosition(double newPos);
			void DrawLine(int LyricPosY);
			void DrawLine(int BoardPosY, int LyricPosY);
			void Draw();
			void SetBoardWidth(int Width);
			void SetBoardHeight(int Height);
			CTextBoard (vector <LyricLine> *LyricLines,CWnd *Wnd,CWMPPlayer4 *MediaPlayer);
			~CTextBoard();
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
	void SetMediaPlayer(CWMPPlayer4 *MediaPlayer);
	virtual ~CLyricMakerCtrl();

	// Generated message map functions
protected:
	void Initialize();
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
