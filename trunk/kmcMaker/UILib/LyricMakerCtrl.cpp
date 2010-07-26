
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
	m_hBackgroundDC = NULL;
	m_hLyricDC = NULL;
	m_LyricLines =NULL;
	m_hLyricFont = NULL;
	m_LyricPosY = 0;
	m_LyricPosX = 0;
}


CLyricMakerCtrl::~CLyricMakerCtrl()
{
	// clean up
	if (m_hLyricDC != NULL)
		DeleteDC(m_hLyricDC);
	if (m_hBackgroundDC != NULL)
		DeleteDC(m_hBackgroundDC);

	if(m_hLyricFont != NULL)
		DeleteObject(m_hLyricFont);
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
	DrawLyric();
}


/********************************************************************/
/*																	*/
/* Function name : Initialize										*/
/* Description   : Initialize some stuff							*/
/*																	*/
/********************************************************************/
void CLyricMakerCtrl::Initialize()
{
 	int cx, cy;
	CDC *pDC = GetDC();

	// load bitbmp
	LoadPicture(IDB_BACKGROUND, m_hBackgroundDC, cx, cy, pDC->m_hDC); 

	// create a bunch of fonts
	m_hLyricFont = CreateFont(20, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, 
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		VARIABLE_PITCH | 0x04 | FF_DONTCARE,
			_T("宋体"));


	// select font
	SelectObject(pDC->m_hDC, m_hLyricFont);

	// get font height
	TEXTMETRIC tm;  
	GetTextMetrics(pDC->m_hDC, &tm);
	m_FontHeight = tm.tmHeight + 5;

//	SetTimer(1,1000,NULL);

	ReleaseDC(pDC);
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


void CLyricMakerCtrl::DrawLyricLine(int nLine, BOOL bCallByDrallAll,int DrewLineNum )
{
	if( m_LyricLines == NULL) return;

	CDC *pDC = GetDC();
	SelectObject(pDC->m_hDC, m_hLyricFont);
	
	pDC->SetBkMode(TRANSPARENT);

	// Draw Lyric
 	int DrawLineCount = m_ClientHeight / m_FontHeight;
 	int MidLineNum = DrawLineCount / 2;
	int top;

	if(bCallByDrallAll )
	{
		top = (5+m_FontHeight* DrewLineNum);
	}else
	{
		top = (5+m_FontHeight * nLine);
	}

	CRect FontRect(20, top , m_ClientWith, m_ClientHeight);
	COLORREF oldColor;

	CString UnMarkedWords;
	CString MarkedWords;
	LyricLine Ll = m_LyricLines->at(nLine);
	MarkedWords = _T("");
	UnMarkedWords = _T("");

	for(int j=0;j<Ll.LyricWords.size();j++)
	{
		LyricWord Lw = Ll.LyricWords.at(j);
		//			TRACE("%d",Lw.IsMarked);
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
	//		DrawText(pDC->m_hDC, Line, Line.GetLength(), FontRect, DT_TOP|DT_LEFT|DT_NOPREFIX | DT_SINGLELINE);
	SetTextColor(pDC->m_hDC, RGB(250,0,0));
	pDC->DrawText(MarkedWords, FontRect, DT_TOP|DT_LEFT|DT_NOPREFIX | DT_SINGLELINE);
	// move position to next line
//	FontRect.top += m_FontHeight;
	
	// set back old values
	pDC->SetTextColor(oldColor);

	ReleaseDC(pDC);
}
void CLyricMakerCtrl::DrawLyric()
{
	CDC *pDC = GetDC();

	// Draw Background
	BitBlt(pDC->m_hDC, 0, 0, m_ClientWith, m_ClientHeight, m_hBackgroundDC, 0, 0, SRCCOPY);
//	StretchBlt(pDC->m_hDC,0, 0, m_ClientWith, m_ClientHeight, m_hBackgroundDC, 0, 0, 800,600, SRCCOPY);

	if( m_LyricLines == NULL) return;

	int StartDrawLine = 0;
	if(m_LyricPosY > m_MidLineNum)
	{
		StartDrawLine += (m_LyricPosY-m_MidLineNum) + 1;
	}

	TRACE("Start Line : %d\n",StartDrawLine);
	// Draw Line
	int LinePosY = m_FontHeight*m_MidLineNum + 3; //(DrawLineCount / 4) * FontHeight + 8;
	CPen pen3DDKShadow(PS_SOLID, 2, RGB(0,240,0)); // Black
	pDC->SelectObject(pen3DDKShadow);
	pDC->MoveTo(0, LinePosY);
	pDC->LineTo(800, LinePosY );

	int DrewLineNum = 0;
//	TRACE("%d\n",m_LyricLines->GetAt(m_LyricPosY).LyricWords[m_LyricPosX].IsMarked);
	for(int i=StartDrawLine;i<m_LyricLines->size() 
							&& DrewLineNum<m_DrawLineCount;i++,DrewLineNum++)
	{
		DrawLyricLine(i,TRUE, DrewLineNum);
	}

	ReleaseDC(pDC);
}

void CLyricMakerCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(rect);
	m_ClientWith = rect.Width();
	m_ClientHeight = rect.Height();

	// calculate line count for client font should be draw
	m_DrawLineCount = m_ClientHeight / m_FontHeight;
	m_MidLineNum = m_DrawLineCount / 2;
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

		double curTime = m_MediaPlayer->GetControls().GetCurrentPosition();
		
		int LineNum = m_LyricLines->size();
		int WordNum = m_LyricLines->at(m_LyricPosY).LyricWords.size();

		switch(nChar)
		{
			case VK_LEFT:
				if(m_LyricPosX > 0)
				{
					m_LyricPosX--;
					//TRACE("VK_LEFT, %d, %s\n",m_LyricPosX,m_LyricLines->at(m_LyricPosY).LyricWords.at(m_LyricPosX).Word);
					m_LyricLines->at(m_LyricPosY).LyricWords.at(m_LyricPosX).IsMarked = FALSE;
					DrawLyricLine(m_LyricPosY);
				}
				break;
			case VK_RIGHT:
				if(m_LyricPosX < WordNum)
				{
					if(m_LyricPosX == 0)
					{
						TRACE("行开始");
					}
					m_LyricLines->at(m_LyricPosY).LyricWords.at(m_LyricPosX).IsMarked = TRUE;
					m_LyricPosX++;
					DrawLyricLine(m_LyricPosY);
				}
				else //if( m_LyricPosY <= LineNum)
				{
					TRACE("行结束");
					m_LyricPosY++;
					m_LyricPosX = 0;
					m_LyricLines->at(m_LyricPosY).LyricWords.at(m_LyricPosX).IsMarked = TRUE;

					DrawLyricLine(m_LyricPosY);
					//DrawLyric();
				}
				break;
			case VK_UP:
				if(m_LyricPosY>0)
				{
					int i;
					// clear all marked flag of lyric word in current line  
					for(i=0;i<m_LyricLines->at(m_LyricPosY).LyricWords.size();i++)
					{
						m_LyricLines->at(m_LyricPosY).LyricWords.at(i).IsMarked = FALSE;
					}

					m_LyricPosY--;

					// clear all marked flag of lyric word in prev line  
					for(i=0;i<m_LyricLines->at(m_LyricPosY).LyricWords.size();i++)
					{
						m_LyricLines->at(m_LyricPosY).LyricWords.at(i).IsMarked = FALSE;
					}
					m_LyricPosX = 0;
					DrawLyric(); 
				}
				break;
			case VK_DOWN:
				// check if all word has been marked in the line
				int i=0;

				for(i=0;i<m_LyricLines->at(m_LyricPosY).LyricWords.size();i++)
				{
					if(!m_LyricLines->at(m_LyricPosY).LyricWords.at(i).IsMarked)
						break;
				}

				if( i==m_LyricLines->at(m_LyricPosY).LyricWords.size() && m_LyricPosY < LineNum-1)
				{
					m_LyricPosY++;
					m_LyricPosX = 0;
					DrawLyric(); 
				}
				break;
		}
	}
//	CStatic::OnKeyDown(nChar, nRepCnt, nFlags);
}

/********************************************************************/
/*																	*/
/* Function name : LoadPicture										*/
/* Description   : Load picture from resource into device context	*/
/*																	*/
/********************************************************************/
void CLyricMakerCtrl::LoadPicture(int nResourceID, HDC &hDestinationDC, int &nWidth, int &nHeight, HDC hDC)
{
	HDC hMemDC;
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
		
		nWidth = bm.bmWidth;
		nHeight = bm.bmHeight;
		
		// Create the DC
		hdcCompatible = CreateCompatibleDC(hDC);    
		// Temporary memory bitmap
		hbmScreen = CreateCompatibleBitmap(hDC, nWidth, nHeight);
		
		// select bitmap into dc
		if (SelectObject(hdcCompatible, hbmScreen) == NULL)
		{
			// return null
			hDestinationDC = NULL;                                        
		}
		else 
		{
			// return the DC
			hDestinationDC = hdcCompatible;
		}
		
		if (hDestinationDC)
			BitBlt(hDestinationDC, 0, 0, nWidth, nHeight, hMemDC, 0, 0, SRCCOPY);
		
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
		hbmScreen = CreateCompatibleBitmap(hDC, nWidth, nHeight);		
		// if the function fails
		if (SelectObject(hdcCompatible, hbmScreen) == NULL)
		{
			// return null
			hDestinationDC = NULL;
		}
		else
		{
			// if it succeeds, return the DC
			hDestinationDC = hdcCompatible;                                     
		}
		DeleteObject(hbmScreen);
	}
}

void CLyricMakerCtrl::SetLyricLines( vector <LyricLine> *Ll )
{
	m_LyricLines = Ll;
}	

void CLyricMakerCtrl::SetMediaPlayer(CWMPPlayer4 *MediaPlayer)
{
	m_MediaPlayer = MediaPlayer;
}
