
#include "stdafx.h"
#include "../resource.h"
#include "LyricMakerCtrl.h"
#include "../MakeLyricDlg.h"

#define PLAYSTATE_READY 0
#define PLAYSTATE_PLAY  3
#define PLAYSTATE_PAUSE 2
#define PLAYSTATE_STOP 1

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CLyricMakerCtrl::CLyricMakerCtrl()
{
	
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
void CLyricMakerCtrl::OnTimer( UINT nIDEvent )
{
	if(nIDEvent == 1)
	{
	}
	CStatic::OnTimer(nIDEvent);
}

void CLyricMakerCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == VK_LEFT || nChar == VK_RIGHT 
		|| nChar == VK_UP|| nChar == VK_DOWN)
	{
		if( m_LyricLines == NULL) return;
		
		// check if playing
		long PlayState = ((CMakeLyricDlg *)(GetParent()))->m_MediaPlayer.GetPlayState();
		if( PlayState !=PLAYSTATE_PLAY )
		{
			return;
		}
		
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
			m_TextBoard->MoveNextLine();
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


void CLyricMakerCtrl::CTextBoard::CreateFont()
{
	// create a bunch of fonts
	LyricFont = ::CreateFont(20, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, 
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		VARIABLE_PITCH | 0x04 | FF_DONTCARE,
		_T("宋体"));
	
	
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
	CreateFont();
}

void CLyricMakerCtrl::CTextBoard::MoveNextLine()
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
void CLyricMakerCtrl::CTextBoard::MovePrevLine()
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
void CLyricMakerCtrl::CTextBoard::UnMarkPrevWord()
{
	if(LyricPosX > 0)
	{
		LyricPosX--;
		LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).IsMarked = FALSE;
		DrawLine(LyricPosY);
	}
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
			LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).StartTime = curTime;
		}else
		{
			LyricLines->at(LyricPosY).LyricWords.at(LyricPosX - 1 ).EndTime = curTime;
			LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).StartTime = curTime;
		}	
		
		TRACE("%d,%d \n",LyricPosY,LyricPosX);
		LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).IsMarked = TRUE;
		LyricPosX++;
		DrawLine(LyricPosY);
	}
	else 
	{
		// 换行
		LyricLines->at(LyricPosY).LyricWords.at(LyricPosX-1).EndTime = curTime;
		LyricLines->at(LyricPosY).EndTime = curTime;

		//debug
// 		CString kmc;
// 		m_kmcBuffer->GetKmcLyric(kmc);
// 		pWnd->MessageBox(kmc);
		
		LyricPosY++;
		LyricPosX = 0;
		LyricLines->at(LyricPosY).LyricWords.at(LyricPosX).IsMarked = TRUE;
		LyricPosX++;
		TRACE("warp %d,%d \n",LyricPosY,LyricPosX);
		// warp line
		if(LyricPosY > MidLineNum-1)
			Draw();
		else
			DrawLine(LyricPosY);
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

void CLyricMakerCtrl::CTextBoard::DrawLine(int LyricPosY)
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

void CLyricMakerCtrl::CTextBoard::DrawLine(int BoardPosY, int LyricPosY)
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

void CLyricMakerCtrl::CTextBoard::Draw()
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
	m_kmcBuffer = new CKmcBuffer(LyricLines);
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

	delete m_kmcBuffer;
}

