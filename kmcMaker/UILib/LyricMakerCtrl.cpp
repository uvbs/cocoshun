
#include "stdafx.h"
#include "../resource.h"
#include "LyricMakerCtrl.h"
#include "../MakeLyricDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CLyricMakerCtrl::CLyricMakerCtrl()
{
	m_IsPreview = FALSE;
	m_TextBoard = NULL;
}


CLyricMakerCtrl::~CLyricMakerCtrl()
{
	if(m_TextBoard != NULL)
	{
		delete m_TextBoard;
	}
}


BEGIN_MESSAGE_MAP(CLyricMakerCtrl, CStatic)
	//{{AFX_MSG_MAP(CLyricMakerCtrl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_GETDLGCODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/********************************************************************/
/*																	*/
/* Function name : OnPaint											*/
/* Description   : Called when the application makes a request to	*/
/*				   repaint a portion of the window.					*/
/*																	*/
/********************************************************************/
void CLyricMakerCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	m_TextBoard->Draw();
}



/********************************************************************/
/*																	*/
/* Function name : PreSubclassWindow								*/
/* Description   : Called before the window is subclassed.			*/
/*																	*/
/********************************************************************/
void CLyricMakerCtrl::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();
}

void CLyricMakerCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	
	if(m_TextBoard != NULL)
	{
		m_TextBoard->SetBoardWidth(cx);
		m_TextBoard->SetBoardHeight(cy);
		m_TextBoard->RefreshBackground();
	}
	
}

UINT CLyricMakerCtrl::OnGetDlgCode()
{
	// 让歌词控件能接收KEY消息
	return DLGC_WANTALLKEYS | DLGC_WANTARROWS;
}


void CLyricMakerCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == VK_LEFT || nChar == VK_RIGHT 
		|| nChar == VK_UP|| nChar == VK_DOWN
		|| nChar == VK_SPACE)
	{
		if( m_LyricLines == NULL) return;

		if(nChar == VK_SPACE)
		{
			((CMakeLyricDlg *)GetParent())->OnBtnPlayPause();
			return;
		}
		
		// check if playing
		if(!((CMakeLyricDlg *)GetParent())->m_MediaPlayer.IsPlay())
 			return;

		TRACE("%d\n",nChar);
		
		switch(nChar)
		{
		case VK_LEFT:
			m_TextBoard->UnMarkPrevWord();
			break;
		case VK_RIGHT:
			m_TextBoard->MarkNextWord();
			break;
		case VK_UP:
			m_TextBoard->MovePrevLine();
			break;
		case VK_DOWN:
			m_TextBoard->MarkWordEnd();
			break;
		}
	}
	//	CStatic::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CLyricMakerCtrl::SetMediaPlayer(CWMPPlayer4 *MediaPlayer)
{
	m_MediaPlayer = MediaPlayer;
}

void CLyricMakerCtrl::SetLyricLines( vector <LyricLine> *Ll )
{
	m_LyricLines = Ll;

	if(m_TextBoard != NULL)
	{
		delete m_TextBoard;
		m_TextBoard = NULL;
	}
	
	m_TextBoard = new CTextBoard(Ll,this, m_MediaPlayer);
	CRect rect;
	GetClientRect(rect);
	if(m_TextBoard != NULL)
	{
		m_TextBoard->SetBoardWidth(rect.Width());
		m_TextBoard->SetBoardHeight(rect.Height());
		m_TextBoard->RefreshBackground();
	}

}

void CLyricMakerCtrl::CTextBoard::LoadPicture(int nResourceID)
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
			hBitMap = NULL;                                        
		}
		else 
		{
			// return the DC
			hBitMap = hdcCompatible;
		}
		
		if (hBitMap)
			BitBlt(hBitMap, 0, 0, BmpWidth, BmpHeight, hMemDC, 0, 0, SRCCOPY);
		
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
			hBitMap = NULL;
		}
		else
		{
			// if it succeeds, return the DC
			hBitMap = hdcCompatible;                                     
		}
		DeleteObject(hbmScreen);
	}
}


void CLyricMakerCtrl::CTextBoard::SetFont()
{
	// create a bunch of fonts
	LyricFont = ::CreateFont(20, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, 
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH,
		_T("黑体"));
	
	// select font
	SelectObject(pDC->m_hDC, LyricFont);
	
	// get font height
	TEXTMETRIC tm;  
	GetTextMetrics(pDC->m_hDC, &tm);
	FontHeight = tm.tmHeight + 5;
	
	pDC->SetBkMode(TRANSPARENT);
}

void CLyricMakerCtrl::CTextBoard::InitGraph()
{
	LoadPicture(IDB_BACKGROUND);
	SetFont();
}

void CLyricMakerCtrl::CTextBoard::MarkWordEnd()
{
	int WordNum = LyricLines->at(LyricPosY).LyricWords.size();
	HDC hDC = pDC->GetSafeHdc();
	double curTime = GetCurrentPosition();
	if(LyricPosX>0 )
	{
		GetLyricWord(LyricPosY,LyricPosX-1)->EndTime = curTime;
		GetLyricWord(LyricPosY,LyricPosX-1)->MarkedEnd = TRUE;

		DrawWord(hDC,LyricPosY,LyricPosX-1);
	}
}
void CLyricMakerCtrl::CTextBoard::MovePrevLine()
{
	HDC hDC = pDC->GetSafeHdc();
	int WordNum = LyricLines->at(LyricPosY).LyricWords.size();
	if(LyricPosY>0)
	{
		StopDrawIncrementWord();
		Draw();
		// clear all marked flag of lyric word in current line  
		for(int x=0;x<WordNum;x++)
		{
			GetLyricWord(LyricPosY,x)->UnMark();
			DrawWord(hDC, LyricPosY, x);
		}
		LyricPosY--;
		LyricPosX = LyricLines->at(LyricPosY).LyricWords.size();

		double EndTime = GetLyricWord(LyricPosY,LyricPosX-1)->EndTime;
		SetCurrentPosition(EndTime);
	}
}

void CLyricMakerCtrl::CTextBoard::SetPlayPosition()
{
	// set media player position
	double StartTime = LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).StartTime;
	SetCurrentPosition(StartTime);
}

void CLyricMakerCtrl::CTextBoard::MarkNextWord()
{
	int WordNum = LyricLines->at(LyricPosY).LyricWords.size();
	double curTime = GetCurrentPosition();
	HDC hDC = pDC->GetSafeHdc();
	if(LyricPosX < WordNum )
	{
		if(LyricPosX == 0)
		{
			// 标记行开始
			GetLyricLine(LyricPosY)->StartTime = curTime;

			// 标记Word开始
			GetLyricWord(LyricPosY,LyricPosX)->StartTime = curTime;
			GetLyricWord(LyricPosY,LyricPosX)->MarkedStart = TRUE;

			DrawWord(hDC, LyricPosY, 0);
			StartDrawIncrementWord();
		}else
		{
			// 标记前一个Word的结束
			GetLyricWord(LyricPosY,LyricPosX-1)->EndTime = curTime;
			GetLyricWord(LyricPosY,LyricPosX-1)->MarkedEnd = TRUE;
			DrawWord(hDC, LyricPosY, LyricPosX-1);

			// 标记当前Word的开始
			GetLyricWord(LyricPosY,LyricPosX)->StartTime = curTime;
			GetLyricWord(LyricPosY,LyricPosX)->MarkedStart = TRUE;
			DrawWord(hDC, LyricPosY, LyricPosX);
			StartDrawIncrementWord();
		}	
		
		LyricPosX++;
	}
	else if(LyricPosY < LyricLines->size() - 1)
	{
		// 标记上一行的最后一个word
		GetLyricWord(LyricPosY,LyricPosX-1)->EndTime = curTime;
		GetLyricWord(LyricPosY,LyricPosX-1)->MarkedEnd = TRUE;
		DrawWord(hDC, LyricPosY, LyricPosX-1);
		// 标记行结束
		LyricLines->at(LyricPosY).EndTime = curTime;

		
		// move to next line
		LyricPosY++;
		LyricPosX = 0;

		// 标记行开始
		GetLyricLine(LyricPosY)->StartTime = curTime;

		// 标记行中的Word
		GetLyricWord(LyricPosY,LyricPosX)->StartTime = curTime;
		GetLyricWord(LyricPosY,LyricPosX)->MarkedStart = TRUE;
		DrawWord(hDC, LyricPosY, LyricPosX);

		LyricPosX++;

		// warp line
		if(LyricPosY > MidLineNum-1)
		{
			Draw();
		}
	}
}

void CLyricMakerCtrl::CTextBoard::UnMarkPrevWord()
{
	int WordNum = LyricLines->at(LyricPosY).LyricWords.size();
	HDC hDC = pDC->GetSafeHdc();
	if(LyricPosX > 0)
	{
		Draw();
		if(LyricPosX>WordNum-1)
		{
			LyricPosX--;
			GetLyricWord(LyricPosY,LyricPosX)->UnMark();
			DrawWord(hDC,LyricPosY,LyricPosX);
			return;
		}

		GetLyricWord(LyricPosY,LyricPosX)->UnMark();
		DrawWord(hDC,LyricPosY,LyricPosX);

		LyricPosX--;

		GetLyricWord(LyricPosY,LyricPosX)->UnMark();
		DrawWord(hDC,LyricPosY,LyricPosX);

		double EndTime = GetLyricWord(LyricPosY,LyricPosX)->EndTime;
		SetCurrentPosition(EndTime);
	}
}

double CLyricMakerCtrl::CTextBoard::GetCurrentPosition()
{
	double CurPlayTime = ((CMakeLyricDlg *)(pWnd->GetParent()))->m_MediaPlayer.GetControls().GetCurrentPosition();
	return CurPlayTime;
}

void CLyricMakerCtrl::CTextBoard::SetCurrentPosition(double newPos)
{
	((CMakeLyricDlg *)(pWnd->GetParent()))->m_MediaPlayer.GetControls().SetCurrentPosition(newPos);
}

void CLyricMakerCtrl::CTextBoard::DrawLine(int y)
{
	int BoardPosY = 0;
	
	if(y < MidLineNum)
	{
		BoardPosY = y;
	}else
	{
		BoardPosY = MidLineNum - 1;
	}
	DrawLine(BoardPosY, y, TRUE);
}

void CLyricMakerCtrl::CTextBoard::DrawLine(int BoardPosY, int LyricPosY, BOOL bMarkDraw)
{
	if( LyricLines == NULL) return;
	
	CRect FontRect(20, (BoardPosY) * FontHeight + 10, BoardWith, BoardHeight);
	COLORREF oldColor;
	
	CString MarkedStart;
	CString MarkedWords;
	LyricLine Ll = LyricLines->at(LyricPosY);
	for(int j=0;j<Ll.LyricWords.size();j++)
	{
		LyricWord Lw = Ll.LyricWords.at(j);
		if(Lw.IsLyric)
		{
			if(Lw.IsMarkedAll())
			{
				MarkedWords += Lw.Word;
			}
			if(Lw.IsMarkedStart())
			{
				MarkedStart += Lw.Word;
			}
		}
	}

//	TRACE("MarkedWords(%s), MarkedStart(%s)\n",MarkedWords,MarkedStart );

	// draw line 
	oldColor = pDC->SetTextColor( COLOR_BLACK);
	CString lLine = Ll.Line;
	LyricWord *pLw = GetLyricWord(LyricPosY,0);
	if(!pLw->IsLyric)
	{
		lLine = lLine.Mid(pLw->Word.GetLength(),lLine.GetLength());
	}
	pDC->DrawText(lLine, FontRect, DT_TOP|DT_LEFT);
	
// 	if(MarkedStart.IsEmpty() || MarkedWords.IsEmpty())
// 		return;
	// draw marked font
	if(bMarkDraw)
	{
//		CString CurWord = MarkedStart; //LyricLines->at(LyricPosY).LyricWords.at(LyricPosX-1).Word;

		if(!MarkedWords.IsEmpty())
		{
			SetTextColor(pDC->m_hDC, COLOR_GREEN);
			pDC->DrawText(MarkedWords, FontRect, DT_TOP|DT_LEFT);
		}

		if(!MarkedStart.IsEmpty())
		{
			int MarkedWordsWidth = GetTextWidth(MarkedWords);

			FontRect.left = FontRect.left + MarkedWordsWidth;
			SetTextColor(pDC->m_hDC, COLOR_BLUE);
			pDC->DrawText(MarkedStart, FontRect, DT_TOP|DT_LEFT);

			// draw Increment
			//FontRect.left = FontRect.left + DrawWidth;
			int CurWordWidth = GetTextWidth(MarkedStart);
			FontRect.right = FontRect.left ;
			((CLyricMakerCtrl*)pWnd)->StartDrawIncrementWord(pDC,MarkedStart,FontRect,CurWordWidth);
		}
	}else
	{
		SetTextColor(pDC->m_hDC, COLOR_GREEN);
		pDC->DrawText(MarkedWords, FontRect, DT_TOP|DT_LEFT);
	}

	// set back old values
	pDC->SetTextColor(oldColor);
}

void CLyricMakerCtrl::CTextBoard::Draw()
{
	// draw background bitmap
	DrawBackground();
// 	BitBlt(pDC->m_hDC, 0, 0, BoardWith, BoardHeight, hBitMap, 0, 0, SRCCOPY);
//	StretchBlt(pDC->m_hDC,0, 0, m_ClientWith, m_ClientHeight, m_hBackgroundDC, 0, 0, 800,600, SRCCOPY);
//	if( LyricLines == NULL) return;
				
	// Draw Line
// 	int LinePosY = FontHeight*MidLineNum + 5; 
// 	CPen pen3DDKShadow(PS_SOLID, 2, COLOR_GREEN);
// 	pDC->SelectObject(pen3DDKShadow);
// 	pDC->MoveTo(0, LinePosY);
// 	pDC->LineTo(BoardWith-2, LinePosY );
// 	
// 	// Draw all lyric
// 	int DrewLineNum = 0;
// 	int i = (LyricPosY > MidLineNum-1) ? (LyricPosY - MidLineNum + 1) : 0;
// 	
// 	for(;i<LyricLines->size() 
// 		&& DrewLineNum< BoardCY;i++,DrewLineNum++)
// 	{
// 		DrawLine(DrewLineNum , i);
// 	}
	
}

void CLyricMakerCtrl::CTextBoard::SetBoardWidth(int Width)
{
	BoardWith = Width;
}
void CLyricMakerCtrl::CTextBoard::SetBoardHeight(int Height)
{
	BoardHeight = Height;
	BoardCY = BoardHeight / FontHeight;
	MidLineNum = BoardCY / 2;
}			

CLyricMakerCtrl::CTextBoard::CTextBoard (vector <LyricLine> *LyricLines,CWnd *Wnd,CWMPPlayer4 *MediaPlayer)
{
	this->LyricLines = LyricLines;
	this->pWnd = Wnd;
	this->MediaPlayer = MediaPlayer;
	
	this->pDC = this->pWnd->GetDC();
	this->LineCount = LyricLines->size();
	this->LyricPosX = 0;
	this->LyricPosY = 0;
	this->hBitMap = NULL;
	this->LyricFont = NULL;
	this->m_hBackGround = NULL;

	bDrawIncrementWord = FALSE;
	nDrawIncrementWordWidth = 0;	

	InitGraph();
}

CLyricMakerCtrl::CTextBoard::~CTextBoard()
{
	if(LyricFont != NULL)
	{
		DeleteObject(LyricFont);
	}
	
	if(hBitMap != NULL)
	{
		DeleteObject(hBitMap);
	}
	
	if(m_hBackGround != NULL)
	{
		DeleteObject(m_hBackGround);
	}

	if(pDC != NULL)
	{
		::ReleaseDC(pWnd->m_hWnd,pDC->GetSafeHdc());
	}
}

int CLyricMakerCtrl::CTextBoard::GetTextWidth(CString &Text)
{
	CSize size;
	size = pDC -> GetTextExtent(Text,Text.GetLength());
	return size.cx;
}
int CLyricMakerCtrl::CTextBoard::GetTextWidth(LPCTSTR pText)
{
	CSize size;
	size = pDC -> GetTextExtent(pText);
	return size.cx;
}
void CLyricMakerCtrl::StartDrawIncrementWord(CDC *pDC,CString Word, CRect FontRect, int WordWidth)
{
	m_TextBoardDC = pDC;
	m_IncrementWord = Word;
	m_IncrementWordRect = FontRect;
	m_IncrementWordWidth = WordWidth;
	SetTimer(1, 80, NULL);
}
void CLyricMakerCtrl::OnTimer( UINT nIDEvent )
{
	if(nIDEvent == 1)
	{
		m_TextBoard->DrawIncrementWord();
	}
	CStatic::OnTimer(nIDEvent);
}


void CLyricMakerCtrl::Preview()
{
//	SetTimer(2, 10, NULL);
	m_IsPreview = TRUE;
}

LyricWord* CLyricMakerCtrl::CTextBoard::GetLyricWord(int y, int x)
{
	return &(LyricLines->at(y).LyricWords.at(x));
}

void CLyricMakerCtrl::StopPrivew()
{
	KillTimer(2);
	m_IsPreview = FALSE;
}

void CLyricMakerCtrl::CTextBoard::RefreshBackground()
{
	if(m_hBackGround != NULL)
	{
		DeleteObject(m_hBackGround);
	}

	HDC hDC = pDC->m_hDC;
	HDC hdcCompatible;
	HBITMAP hbmScreen;
	int BackgroundHeight = (LyricLines->size() * FontHeight) + ((MidLineNum+1) * FontHeight);

	// Create the DC
	hdcCompatible = CreateCompatibleDC(hDC);			
	// Temporary bitmap
	hbmScreen = CreateCompatibleBitmap(hDC, BoardWith, BackgroundHeight);
	// if the function fails
	if (SelectObject(hdcCompatible, hbmScreen) == NULL)
	{
		// return null
		m_hBackGround = NULL;
	}
	else
	{
		// if it succeeds, return the DC
		m_hBackGround = hdcCompatible;
		RECT rc;

		rc.top = 0;
		rc.left = 0;
		rc.bottom = BackgroundHeight;
		rc.right = BoardWith;

//		BitBlt(m_hBackGround, 0, 0, rc.right, rc.bottom, hBitMap, 0, 0, SRCCOPY);
		FillRect(m_hBackGround, &rc, (HBRUSH)GetStockObject(RGB(255,255,255)));
		HFONT pOldFont = (HFONT)SelectObject(m_hBackGround, LyricFont);
		COLORREF oldColor = SetTextColor(m_hBackGround, COLOR_BLACK);

		if(LyricLines != NULL && !LyricLines->empty())
		{
			for(int y=0;y<LyricLines->size(); y++)
			{
				LyricLine *pLyricLine = GetLyricLine(y);
				if(pLyricLine != NULL)
				{
					for(int x=0;x<pLyricLine->LyricWords.size();x++)
					{
						DrawWord(m_hBackGround,y,x,FALSE);
					}
				}
			}
		}
//		RefreshMidLine();
		int LinePosY = 2 + FontHeight* (MidLineNum+GetLineOffset()) - 2; 
		CPen pen3DDKShadow(PS_SOLID, 2, COLOR_GREEN);
		SelectObject(m_hBackGround,pen3DDKShadow);
		MoveToEx(m_hBackGround, 0 , LinePosY,NULL);
		LineTo(m_hBackGround, BoardWith-2, LinePosY );

		SetTextColor(m_hBackGround, oldColor);
		SelectObject(m_hBackGround, pOldFont);
	}
	DeleteObject(hbmScreen);
}

LPCTSTR CLyricMakerCtrl::CTextBoard::GetLyricLineText(int y)
{
	LPCTSTR pLineText = _T("");
	if(y >= 0 && y< LyricLines->size())
	{
		pLineText = LyricLines->at(y).Line;
	}
	return pLineText;
}

LyricLine* CLyricMakerCtrl::CTextBoard::GetLyricLine(int y)
{
	LyricLine *pLyricLine = NULL;
	if(y >= 0 && y< LyricLines->size())
	{
		pLyricLine = &LyricLines->at(y);
	}
	return pLyricLine;
}

void CLyricMakerCtrl::CTextBoard::DrawBackground()
{
	int LineOffset = GetLineOffset();
	if(!LineOffset)
	{
		RefreshBackground();
		BitBlt(pDC->m_hDC, 0, 0, BoardWith, BoardHeight, m_hBackGround, 0, 0, SRCCOPY);
	}
	else
	{
		RefreshMidLine();
		RefreshBackground();
		BitBlt(pDC->m_hDC, 0, 0, BoardWith, BoardHeight, m_hBackGround, 0, LineOffset*FontHeight, SRCCOPY);
	}
}

void CLyricMakerCtrl::CTextBoard::DrawWord(HDC hDC, int y, int x, BOOL bOffset)
{
	LyricWord*  pWord = GetWord(y, x);

	if(pWord == NULL)
		return;

	if(pWord->IsMarkedStart())
		SetTextColor(hDC, COLOR_RED);
	else if(pWord->IsMarkedAll())
		SetTextColor(hDC, COLOR_GREEN);
	else if(!pWord->IsMarkedAll())
		SetTextColor(hDC, COLOR_BLACK);
	
	CString word = pWord->Word;
	int WordWidth = GetTextWidth(pWord->Word);

	int LineOffset = bOffset ? GetLineOffset() : 0;
	int nLine = y-LineOffset;

	RECT rect;
	rect.left   = 10 +  x*WordWidth;
	rect.top  =  5 + nLine * FontHeight;
	rect.right  = BoardWith;
	rect.bottom = rect.top + FontHeight;

	DrawText(hDC, pWord->Word, _tcslen(pWord->Word) , &rect, DT_TOP|DT_LEFT|DT_NOPREFIX | DT_SINGLELINE);
}

LyricWord* CLyricMakerCtrl::CTextBoard::GetWord(int y, int x)
{
	LyricWord *pWord = NULL;
	if(y >= 0 && y< LyricLines->size()
		&& x >= 0 && x < LyricLines->at(y).LyricWords.size())
	{
		pWord = &LyricLines->at(y).LyricWords.at(x);
	}
	return pWord;
}

int CLyricMakerCtrl::CTextBoard::GetLineOffset()
{
	int lineOffset;
	if(LyricPosY < MidLineNum - 1)
	{
		lineOffset = 0;
	}else
	{
		lineOffset = LyricPosY - ( MidLineNum - 1 );
	}
	return lineOffset;
}

void CLyricMakerCtrl::CTextBoard::RefreshMidLine()
{
	//擦除
	int LinePosY = FontHeight* (MidLineNum+GetLineOffset()-1) - 2; 
	CPen EraserPen(PS_SOLID, 2, RGB(255,255,255));
	SelectObject(m_hBackGround,EraserPen);
	MoveToEx(m_hBackGround, 0 , LinePosY,NULL);
	LineTo(m_hBackGround, BoardWith-2, LinePosY );

	//重画
	LinePosY = FontHeight* (MidLineNum+GetLineOffset()) - 2; 
	CPen pen3DDKShadow(PS_SOLID, 2, COLOR_GREEN);
	SelectObject(m_hBackGround,pen3DDKShadow);
	MoveToEx(m_hBackGround, 0 , LinePosY,NULL);
	LineTo(m_hBackGround, BoardWith-2, LinePosY );
}

void CLyricMakerCtrl::CTextBoard::DrawIncrementWord()
{
	HDC hDC = pDC->GetSafeHdc();
	nDrawIncrementWordWidth++;
	if(bDrawIncrementWord )
	{
		LyricWord*  pWord = GetWord(LyricPosY, LyricPosX-1);
		if(pWord == NULL)
			return;

		int WordWidth = GetTextWidth(pWord->Word);
		if(nDrawIncrementWordWidth< WordWidth)
		{
			SetTextColor(hDC, COLOR_GREEN);
			
			CString word = pWord->Word;
			
			int nLine = LyricPosY-GetLineOffset();
			
			RECT rect;
			rect.left   = 10 +  (LyricPosX-1)*WordWidth;
			rect.top  = 5 + nLine * FontHeight;
			rect.right  = rect.left + nDrawIncrementWordWidth;
			rect.bottom = rect.top + FontHeight;
			
			DrawText(hDC, pWord->Word, _tcslen(pWord->Word) , &rect, DT_TOP|DT_LEFT|DT_NOPREFIX | DT_SINGLELINE);		
		}else
			bDrawIncrementWord = FALSE;
	}
}

void CLyricMakerCtrl::CTextBoard::StartDrawIncrementWord()
{
	bDrawIncrementWord = TRUE;
	nDrawIncrementWordWidth = 0;
	((CLyricMakerCtrl *)pWnd)->SetTimer(1,50,NULL);
}

void CLyricMakerCtrl::CTextBoard::StopDrawIncrementWord()
{
	bDrawIncrementWord = FALSE;
	((CLyricMakerCtrl *)pWnd)->KillTimer(1);
}
