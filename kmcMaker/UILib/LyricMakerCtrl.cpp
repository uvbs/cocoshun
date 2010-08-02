
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
/* Function name : Initialize										*/
/* Description   : Initialize some stuff							*/
/*																	*/
/********************************************************************/
void CLyricMakerCtrl::Initialize()
{
}


/********************************************************************/
/*																	*/
/* Function name : PreSubclassWindow								*/
/* Description   : Called before the window is subclassed.			*/
/*																	*/
/********************************************************************/
void CLyricMakerCtrl::PreSubclassWindow() 
{
	// initialze dc's
	Initialize();
	CStatic::PreSubclassWindow();
}



void CLyricMakerCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	
	if(m_TextBoard != NULL)
	{
		m_TextBoard->SetBoardWidth(cx);
		m_TextBoard->SetBoardHeight(cy);
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
		|| nChar == VK_UP|| nChar == VK_DOWN)
	{
		if( m_LyricLines == NULL) return;
		
		// check if playing
		long PlayState = ((CMakeLyricDlg *)(GetParent()))->m_MediaPlayer.GetPlayState();
 		if( PlayState != PLAYSTATE_PLAY )
 			return;
		
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
	}
	
	m_LyricLines = Ll;
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
	FontHeight = tm.tmHeight + 8;
	
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
	double curTime = GetCurrentPosition();
	if(LyricPosX>0)
	{
		((CLyricMakerCtrl *)pWnd)->StopDrawIncrementWord();
		GetLyricWord(LyricPosY,LyricPosX-1)->EndTime = curTime;
		GetLyricWord(LyricPosY,LyricPosX-1)->MarkedEnd = TRUE;

		DrawLine(LyricPosY);
	}
}
void CLyricMakerCtrl::CTextBoard::MovePrevLine()
{
	if(LyricPosY>0)
	{
		((CLyricMakerCtrl *)pWnd)->StopDrawIncrementWord();

		// clear all marked flag of lyric word in current line  
		for(int x=0;x<LyricLines->at(LyricPosY).LyricWords.size();x++)
		{
			GetLyricWord(LyricPosY,x)->UnMark();
		}
//		if(LyricPosY>MidLineNum)
			Draw();
//		DrawLine(LyricPosY); 

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
	if(LyricPosX < WordNum )
	{
		if(LyricPosX == 0)
		{
			LyricLines->at(LyricPosY).StartTime = curTime;
			GetLyricWord(LyricPosY,LyricPosX)->StartTime = curTime;
			GetLyricWord(LyricPosY,LyricPosX)->MarkedStart = TRUE;
// 			LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).StartTime = curTime;
// 			LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).MarkedStart = TRUE;
		}else
		{
			GetLyricWord(LyricPosY,LyricPosX-1)->EndTime = curTime;
			GetLyricWord(LyricPosY,LyricPosX-1)->MarkedEnd = TRUE;
			GetLyricWord(LyricPosY,LyricPosX)->StartTime = curTime;
			GetLyricWord(LyricPosY,LyricPosX)->MarkedStart = TRUE;

// 			LyricLines->at(LyricPosY).LyricWords.at(LyricPosX - 1).EndTime = curTime;
// 			LyricLines->at(LyricPosY).LyricWords.at(LyricPosX - 1).MarkedEnd = TRUE;
// 			LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).StartTime = curTime;
// 			LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).MarkedStart = TRUE;
		}	
		
//		TRACE("%d,%d \n",LyricPosY,LyricPosX);
		LyricPosX++;
		DrawLine(LyricPosY);
	}
	else if(LyricPosY < LyricLines->size() - 1)
	{
		// set last word in current line
		GetLyricWord(LyricPosY,LyricPosX-1)->EndTime = curTime;
		GetLyricWord(LyricPosY,LyricPosX-1)->MarkedEnd = TRUE;

// 		LyricLines->at(LyricPosY).LyricWords.at(LyricPosX-1).EndTime = curTime;
// 		LyricLines->at(LyricPosY).LyricWords.at(LyricPosX-1).MarkedEnd = TRUE;
		LyricLines->at(LyricPosY).EndTime = curTime;

		//debug
// 		CString kmc;
// 		m_kmcBuffer->GetKmcLyric(kmc);
// 		pWnd->MessageBox(kmc);
		
		// move to next line
		LyricPosY++;
		LyricPosX = 0;

		// mark
		GetLyricWord(LyricPosY,LyricPosX)->StartTime = curTime;
		GetLyricWord(LyricPosY,LyricPosX)->MarkedStart = TRUE;
// 		LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).StartTime = curTime;
// 		LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).MarkedStart = TRUE;
		LyricPosX++;
//		TRACE("warp %d,%d \n",LyricPosY,LyricPosX);

		// warp line
		if(LyricPosY > MidLineNum-1)
		{
			Draw();
			DrawLine(LyricPosY);
		}
		else
		{
			if(LyricPosY>0)
				DrawLine(LyricPosY-1);
			DrawLine(LyricPosY);
		}
	}
}

void CLyricMakerCtrl::CTextBoard::UnMarkPrevWord()
{
	if(LyricPosX > 0)
	{
		((CLyricMakerCtrl *)pWnd)->StopDrawIncrementWord();
		
//		TRACE("%d,%d \n",LyricPosY,LyricPosX);
		LyricPosX--;

		double EndTime = GetLyricWord(LyricPosY,LyricPosX)->EndTime;
		SetCurrentPosition(EndTime);

		GetLyricWord(LyricPosY,LyricPosX)->UnMark();
//		LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).UnMark();
		//LyricLines->at(LyricPosY).LyricWords.at(LyricPosX-1).UnMark();
//		DrawLine(LyricPosY);
		Draw();
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
	BitBlt(pDC->m_hDC, 0, 0, BoardWith, BoardHeight, BitMap, 0, 0, SRCCOPY);
//	StretchBlt(pDC->m_hDC,0, 0, m_ClientWith, m_ClientHeight, m_hBackgroundDC, 0, 0, 800,600, SRCCOPY);
	if( LyricLines == NULL) return;
				
	// Draw Line
	int LinePosY = FontHeight*MidLineNum + 5; 
	CPen pen3DDKShadow(PS_SOLID, 2, COLOR_GREEN);
	pDC->SelectObject(pen3DDKShadow);
	pDC->MoveTo(0, LinePosY);
	pDC->LineTo(BoardWith-2, LinePosY );
	
	// Draw all lyric
	int DrewLineNum = 0;
	int i = (LyricPosY > MidLineNum-1) ? (LyricPosY - MidLineNum + 1) : 0;
	
	for(;i<LyricLines->size() 
		&& DrewLineNum< BoardCY;i++,DrewLineNum++)
	{
		DrawLine(DrewLineNum , i);
	}
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
	this->BitMap = NULL;
	this->LyricFont = NULL;
	
	InitGraph();
}

CLyricMakerCtrl::CTextBoard::~CTextBoard()
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


int CLyricMakerCtrl::CTextBoard::GetTextWidth(CString Text)
{
	CSize size;
	size = pDC -> GetTextExtent(Text,Text.GetLength());
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
		if(m_IncrementWordRect.right<m_IncrementWordRect.right + m_IncrementWordWidth)
		{
			m_IncrementWordRect.right ++;
			SetTextColor(m_TextBoardDC->m_hDC, COLOR_GREEN);
			m_TextBoardDC->DrawText(m_IncrementWord, m_IncrementWordRect, DT_TOP|DT_LEFT);
		}else
		{
			StopDrawIncrementWord();
		}
	}
	CStatic::OnTimer(nIDEvent);
}
void CLyricMakerCtrl::StopDrawIncrementWord()
{
	if(!m_IncrementWord.IsEmpty())
	{
		KillTimer(1);
// 		m_IncrementWordRect.right = m_IncrementWordRect.left + m_IncrementWordWidth;
// 		SetTextColor(m_TextBoardDC->m_hDC, COLOR_GREEN);
// 		m_TextBoardDC->DrawText(m_IncrementWord, m_IncrementWordRect, DT_TOP|DT_LEFT);
	}
}

void CLyricMakerCtrl::Preview()
{
	SetTimer(2, 10, NULL);
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
