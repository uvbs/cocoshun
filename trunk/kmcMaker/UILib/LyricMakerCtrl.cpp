
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
	
	m_TextBoard = new TextBoard(Ll,this, m_MediaPlayer);
	CRect rect;
	GetClientRect(rect);
	if(m_TextBoard != NULL)
	{
		m_TextBoard->SetBoardWidth(rect.Width());
		m_TextBoard->SetBoardHeight(rect.Height());
	}
	
	m_LyricLines = Ll;
}	

