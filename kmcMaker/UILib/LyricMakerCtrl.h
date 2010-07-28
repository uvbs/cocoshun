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
	class TextBoard
	{
		protected:
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

			double GetCurPlayTime()
			{
				
				return MediaPlayer->GetControls().GetCurrentPosition();
			}

			void LoadPicture(int nResourceID)
			{
				HDC hMemDC;
				HDC hDC = pDC->m_hDC;
				HDC hdcCompatible;
				HBITMAP hbmScreen;
				
				if (nResourceID != 0)
				{
					// if resourceid is given, load bitmap
					HBITMAP hPicture = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(nResourceID));
					
					BITMAP bm;
					GetObject(hPicture, sizeof (BITMAP), (LPSTR)&bm);
					
					hMemDC = CreateCompatibleDC(hDC);
					
					HBITMAP hOldBMP = (HBITMAP)SelectObject(hMemDC, hPicture);
					
					BmpWidth = bm.bmWidth;
					BmpHeight = bm.bmHeight;
					
					// Create the DC
					hdcCompatible = CreateCompatibleDC(hDC);    
					// Temporary memory bitmap
					hbmScreen = CreateCompatibleBitmap(hDC, BmpWidth, BmpHeight);
					
					// select bitmap into dc
					if (SelectObject(hdcCompatible, hbmScreen) == NULL)
					{
						// return null
						BitMap = NULL;                                        
					}
					else 
					{
						// return the DC
						BitMap = hdcCompatible;
					}
					
					if (BitMap)
						BitBlt(BitMap, 0, 0, BmpWidth, BmpHeight, hMemDC, 0, 0, SRCCOPY);
					
					SelectObject(hMemDC, hOldBMP);
					
					// Release temporary stuff
					DeleteDC(hMemDC);
					DeleteObject(hbmScreen);
					DeleteObject(hPicture);
				}
				else	// if no resourceid is given, create empty DC with specified width and height
				{
					// create the DC
					hdcCompatible = CreateCompatibleDC(hDC);			
					// temporary memory bitmap
					hbmScreen = CreateCompatibleBitmap(hDC, BmpWidth, BmpHeight);		
					// if the function fails
					if (SelectObject(hdcCompatible, hbmScreen) == NULL)
					{
						// return null
						BitMap = NULL;
					}
					else
					{
						// if it succeeds, return the DC
						BitMap = hdcCompatible;                                     
					}
					DeleteObject(hbmScreen);
				}
			}


			void CreateFont()
			{
				// create a bunch of fonts
				LyricFont = ::CreateFont(20, 0, 0, 0, 
					FW_BOLD, FALSE, FALSE, 0, 
					ANSI_CHARSET,
					OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS,
					PROOF_QUALITY,
					VARIABLE_PITCH | 0x04 | FF_DONTCARE,
					_T("ËÎÌו"));
				
				
				// select font
				SelectObject(pDC->m_hDC, LyricFont);
				
				// get font height
				TEXTMETRIC tm;  
				GetTextMetrics(pDC->m_hDC, &tm);
				FontHeight = tm.tmHeight + 8;

				pDC->SetBkMode(TRANSPARENT);
			}

			void InitGraph()
			{
				LoadPicture(IDB_BACKGROUND);
				CreateFont();
			}
		
		public:
			void MoveNextLine()
			{
				// check if all word has been marked in the line
				int i=0;
				
				for(i=0;i<LyricLines->at(LyricPosY).LyricWords.size();i++)
				{
					if(!LyricLines->at(LyricPosY).LyricWords.at(i).IsMarked)
						break;
				}
				
				if( i==LyricLines->at(LyricPosY).LyricWords.size() && LyricPosY < LineCount-1)
				{
					LyricPosY++;
					LyricPosX = 0;
					Draw(); 
				}
			}
			void MovePrevLine()
			{
				if(LyricPosY>0)
				{
					int i;
					// clear all marked flag of lyric word in current line  
					for(i=0;i<LyricLines->at(LyricPosY).LyricWords.size();i++)
					{
						LyricLines->at(LyricPosY).LyricWords.at(i).IsMarked = FALSE;
					}
					
					LyricPosY--;
					
					// clear all marked flag of lyric word in previos line  
					for(i=0;i<LyricLines->at(LyricPosY).LyricWords.size();i++)
					{
						LyricLines->at(LyricPosY).LyricWords.at(i).IsMarked = FALSE;
					}
					LyricPosX = 0;
					Draw(); 
				}
			}
			void UnMarkPrevWord()
			{
				if(LyricPosX > 0)
				{
					LyricPosX--;
					LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).IsMarked = FALSE;
					DrawLine(LyricPosY);
				}
			}
			void MarkNextWord()
			{
				int WordNum = LyricLines->at(LyricPosY).LyricWords.size();
				double curTime = GetCurPlayTime();
				if(LyricPosX < WordNum)
				{
					if(LyricPosX == 0)
					{
						LyricLines->at(LyricPosY).StartTime = curTime;
						LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).StartTime = curTime;
					}else
					{
						LyricLines->at(LyricPosY).LyricWords.at(LyricPosX - 1 ).EndTime = curTime;
						LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).StartTime = curTime;
					}	

					LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).IsMarked = TRUE;
					LyricPosX++;
					DrawLine(LyricPosY);
				}
				else if(LyricPosY < LineCount-1)
				{
					LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).EndTime = curTime;
					LyricLines->at(LyricPosY).EndTime = curTime;

					LyricPosY++;
					LyricPosX = 0;
					LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).IsMarked = TRUE;

					// warp line
					if(LyricPosY > MidLineNum-1)
						Draw();
					//DrawLine(LyricPosY);
				}
				
			}

			void DrawLine(int LyricPosY)
			{
				int BoardPosY = 0;
				
				if(LyricPosY < MidLineNum)
				{
					BoardPosY = LyricPosY;
				}else
				{
					BoardPosY = MidLineNum - 1;
				}
				DrawLine(BoardPosY, LyricPosY);
			}

			void DrawLine(int BoardPosY, int LyricPosY)
			{
				if( LyricLines == NULL) return;

				CRect FontRect(20, (BoardPosY) * FontHeight + 10, BoardWith, BoardHeight);
				COLORREF oldColor;
				
				CString UnMarkedWords;
				CString MarkedWords;
				LyricLine Ll = LyricLines->at(LyricPosY);
				MarkedWords = _T("");
				UnMarkedWords = _T("");
				for(int j=0;j<Ll.LyricWords.size();j++)
				{
					LyricWord Lw = Ll.LyricWords.at(j);
					if(Lw.IsMarked)
					{
						MarkedWords += Lw.Word;
					}else
					{
						UnMarkedWords += Lw.Word;
					}
				}
				oldColor = SetTextColor(pDC->m_hDC, RGB(16,140,231));
				pDC->DrawText(Ll.Line, FontRect, DT_TOP|DT_LEFT|DT_NOPREFIX | DT_SINGLELINE);

				SetTextColor(pDC->m_hDC, RGB(250,0,0));
				pDC->DrawText(MarkedWords, FontRect, DT_TOP|DT_LEFT|DT_NOPREFIX | DT_SINGLELINE);
				
				// set back old values
				pDC->SetTextColor(oldColor);
				
//				pWnd->ReleaseDC(pDC);
			}

			void Draw()
			{
				// draw background bitmap
 				BitBlt(pDC->m_hDC, 0, 0, BoardWith, BoardHeight, BitMap, 0, 0, SRCCOPY);
// 				//	StretchBlt(pDC->m_hDC,0, 0, m_ClientWith, m_ClientHeight, m_hBackgroundDC, 0, 0, 800,600, SRCCOPY);
 				if( LyricLines == NULL) return;
				
 				// Draw Line
				int LinePosY = FontHeight*MidLineNum + 5; //(DrawLineCount / 4) * FontHeight + 8;
				CPen pen3DDKShadow(PS_SOLID, 2, RGB(0,240,0)); // Black
				pDC->SelectObject(pen3DDKShadow);
				pDC->MoveTo(0, LinePosY);
				pDC->LineTo(800, LinePosY );
				
				// Draw all lyric
 				int DrewLineNum = 0;
				int i = (LyricPosY > MidLineNum-1) ? (LyricPosY - MidLineNum + 1) : 0;
				//TRACE("LyricPosY=%d,MidLineNum=%d,i=%d \n",LyricPosY,MidLineNum,i);

 				for(;i<LyricLines->size() 
 					&& DrewLineNum< BoardCY;i++,DrewLineNum++)
 				{
					DrawLine(DrewLineNum , i);
 				}

			}

			void SetBoardWidth(int Width)
			{
				BoardWith = Width;
			}
			void SetBoardHeight(int Height)
			{
				BoardHeight = Height;
				BoardCY = BoardHeight / FontHeight;
				MidLineNum = BoardCY / 2;
			}			
			
			TextBoard (vector <LyricLine> *LyricLines,CWnd *Wnd,CWMPPlayer4 *MediaPlayer)
			{
				this->LyricLines = LyricLines;
				this->pWnd = Wnd;
				this->MediaPlayer = MediaPlayer;

				this->pDC = this->pWnd->GetDC();
				this->LineCount = LyricLines->size();
				this->LyricPosX = 0;
				this->LyricPosY = 0;
				this->BitMap = NULL;
				this->LyricFont = NULL;

				InitGraph();
			}

			~TextBoard()
			{
				if(pDC != NULL)
				{
					::ReleaseDC(pWnd->m_hWnd,pDC->GetSafeHdc());
				}

				if(LyricFont != NULL)
				{
					DeleteObject(LyricFont);
				}

				if(BitMap != NULL)
				{
					DeleteObject(BitMap);
				}
			}
		
	};

	TextBoard *m_TextBoard;

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
