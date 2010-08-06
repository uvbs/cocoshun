// MakeLyricDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KmcMaker.h"
#include "MakeLyricDlg.h"
#include "UILib/FileDialogEx.h"
#include "wmpmedia.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MEDIA_PLAYER_SLIDER_TIMER 0X10;
/////////////////////////////////////////////////////////////////////////////
// CMakeLyricDlg dialog


CMakeLyricDlg::CMakeLyricDlg(CWnd* pParent /*=NULL*/)
: CResizingDialog(CMakeLyricDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMakeLyricDlg)
	//}}AFX_DATA_INIT
}


void CMakeLyricDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMakeLyricDlg)
	DDX_Control(pDX, IDC_LYRIC_MAKER, m_LyricMaker);
	DDX_Control(pDX, IDC_MEDIAPLAYER, m_MediaPlayer);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_MAX, m_nMax);
	DDX_Text(pDX, IDC_MIN, m_nMin);
	DDX_Text(pDX, IDC_POS, m_nPos);
	DDX_Control(pDX, IDC_SLIDER_MP, m_sliderMP);
}


BEGIN_MESSAGE_MAP(CMakeLyricDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CMakeLyricDlg)
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_PRIVIEW, OnBtnPriview)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PLAY_PAUSE, OnBtnPlayPause)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_BITMAPSLIDER_MOVED, OnBitmapSliderMoved)
	ON_MESSAGE(WM_BITMAPSLIDER_MOVING, OnBitmapSliderMoving)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakeLyricDlg message handlers

BOOL CMakeLyricDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();

	// Slider 3 - Media Player
	m_sliderMP.SetBitmapChannel( IDB_MP_CHANNEL, IDB_MP_CHANNEL_ACTIVE );
	m_sliderMP.SetBitmapThumb( IDB_MP_THUMB, IDB_MP_THUMB_ACTIVE, TRUE );
	m_sliderMP.DrawFocusRect( FALSE );
	m_nMin = 0;
	m_nMax = 100;
	m_nPos = 30;

	
	m_sliderMP.SetRange( m_nMin, m_nMax );
	m_sliderMP.SetPos( m_nPos );
	m_sliderMP.SetMargin( 2, 3, 2, 0 );
	SetControlInfo(IDC_SLIDER_MP,ANCHORE_RIGHT);

	SetControlInfo(IDC_LYRIC_MAKER,RESIZE_BOTH);
	SetControlInfo(IDC_STATIC_MEDIA_TIMEINFO,ANCHORE_RIGHT);

	SetControlInfo(IDC_LYRIC_MAKER,RESIZE_BOTH);
	SetControlInfo(IDC_STATIC_TIP,ANCHORE_RIGHT);

	SetControlInfo(IDC_BTN_OPEN,ANCHORE_RIGHT);
	SetControlInfo(IDC_BTN_PLAY_PAUSE,ANCHORE_RIGHT);
	SetControlInfo(IDC_BTN_STOP,ANCHORE_RIGHT);


	SetControlInfo(IDC_STATIC_KEY_TIP,ANCHORE_RIGHT);
	SetControlInfo(IDC_BTN_NEXTSTEP,ANCHORE_RIGHT| ANCHORE_BOTTOM);
	SetControlInfo(IDC_BTN_PREVSTEP,ANCHORE_RIGHT| ANCHORE_BOTTOM);
	SetControlInfo(IDC_BTN_PRIVIEW,ANCHORE_LEFT | ANCHORE_BOTTOM);
	SetControlInfo(IDC_MEDIAPLAYER, ANCHORE_RIGHT | ANCHORE_TOP);

	m_MediaPlayer.SetUrl(_T(".\\Test\\十年.mp3"));
	m_MediaPlayer.GetControls().play();
	SetMediaTimeInfo();

	SetFocusToLyricMaker();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CMakeLyricDlg::OnBtnOpen() 
{
	TCHAR szFilter[] = _T("所有媒体文件 (*.mp3;*.wav;*.wmv;*.mpeg;*.mpg;*.asf)|*.mp3; *.wav; *.wmv; *.mpeg; *.mpg; *.asf|音频文件 (*.mp3;*.wav;*.wmv)|*.mp3; *.wav; *.wmv|视频频文件 (*.mpeg;*.mpg;*.asf)|*.mpeg; *.mpg; *.asf|All Files (*.*)|*.*||");
	CFileDialogEx FileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);;
	if( FileDlg.DoModal() == IDOK)
	{
		CString fname = FileDlg.GetPathName();
		m_MediaPlayer.SetUrl(fname);
	}
	SetFocusToLyricMaker();
}

void CMakeLyricDlg::InitLyric(CString Lyric)
{
	if(Lyric.IsEmpty()) 
	{
		m_LyricMaker.SetLyricLines( &m_LyricLines);
		return;
	}

	m_LyricLines.clear();
	CString Line;
	TCHAR lBracket = _T('(');
	TCHAR rBracket = _T(')');

	int nCount=0;
	while(AfxExtractSubString(Line, Lyric, nCount++, '\n'))
	{
		LyricLine LL;
		if(Line.IsEmpty()) continue;
		LL.Line = Line;

		int Pos = 0;
		int n = -1;
		int Len = Line.GetLength();
		while(Pos < Len)
		{
			n++;
			LyricWord LyWord;

			// check chinese
			TCHAR ch = Line.GetAt(Pos);

			if( n == 0)
			{
				// 设置括号中不为歌词的word
				if(ch==lBracket)
				{
					int rPos = Line.Find(rBracket);
					if( rPos != -1)
					{
						LyWord.IsLyric = FALSE;
						LyWord.Word = Line.Mid(0, rPos+1);
						Pos = LyWord.Word.GetLength();
					}
				}
			}

			if(ch & 0x80)
			{
				LyWord.IsChs = TRUE;
				LyWord.Word = Line.Mid(Pos,2);
				Pos+=2;
	
				// add space
				//int increment;
				CString StrSpace;
				GetSpace(Line, Pos, StrSpace);
				LyWord.Word += StrSpace;
			}else
			{
				LyWord.IsChs = FALSE;
				GetEnWord(Line, Pos, LyWord.Word);

				CString StrSpace;
				GetSpace(Line, Pos, StrSpace);
				LyWord.Word += StrSpace;
			}
			LL.LyricWords.push_back(LyWord);
		}
		m_LyricLines.push_back(LL);
	}
	m_LyricMaker.SetLyricLines( &m_LyricLines);
	m_LyricMaker.SetMediaPlayer( &m_MediaPlayer);
}

void CMakeLyricDlg::GetSpace(CString &Str, int &Pos,CString &StrSpace)
{
	int Len = Str.GetLength();
	while(Pos < Len)
	{
		TCHAR ch = Str.GetAt(Pos++);
		if(ch == 0x20)
		{
			StrSpace += ch;
		}else
		{
			break;
		}
	}
	if(Pos < Len)
		Pos--;
}

void CMakeLyricDlg::GetEnWord(CString &Str, int &Pos, CString &StrWord)
{
	int Len = Str.GetLength();
	while(Pos < Len)
	{
		TCHAR ch = Str.GetAt(Pos++);
		if( (!(ch & 0x80)) && ch!=0x20)
		{
			StrWord += ch;
		}else
		{
			break;
		}
	}

	if(Pos < Len)	
		Pos--;	
}

void CMakeLyricDlg::SetFocusToLyricMaker()
{
	m_LyricMaker.SetFocus();
}

void CMakeLyricDlg::OnBtnPriview() 
{
	m_LyricMaker.Preview();
}

LRESULT CMakeLyricDlg::OnAcceptDropFile( WPARAM wParam /*= 0*/, LPARAM lParam /*= 0 */ )
{
	TCHAR *DropFileName = (TCHAR *)wParam;
	m_MediaPlayer.SetUrl(DropFileName);

	return 0;
}


LRESULT CMakeLyricDlg::OnBitmapSliderMoved(WPARAM wParam, LPARAM lParam)
{
	CString sMsg;
	
// 	switch( wParam ) 
	{
		
// 	case IDC_SLIDER_VOL :
// 		m_sliderVol2.SetPos( m_sliderVol.GetPos() );
// 		break;
// 		
// 	case IDC_SLIDER_VOL2 :
// 		m_sliderVol.SetPos( m_sliderVol2.GetPos() );
// 		break;
// 		
// 	case IDC_SLIDER_BALLOON :
// 		
// 		sMsg.Format( "%d", lParam );
// 		AfxMessageBox( sMsg );
// 		break;
	}
	return 0;
}

LRESULT CMakeLyricDlg::OnBitmapSliderMoving(WPARAM wParam, LPARAM lParam)
{
	switch( wParam ) {

	case IDC_SLIDER_MP :
		m_nPos = m_sliderMP.GetPos();
		UpdateData( FALSE );
		break;
	}
	
	return 0;
}

void CMakeLyricDlg::OnTimer(UINT nIDEvent) 
{
	
	CResizingDialog::OnTimer(nIDEvent);
}

void CMakeLyricDlg::OnBtnPlayPause() 
{
	if(m_MediaPlayer.IsPlay())
	{
		m_MediaPlayer.GetControls().pause();
		GetDlgItem(IDC_BTN_PLAY_PAUSE)->SetWindowText(_T(">"));
		return;
	}
	
	if(m_MediaPlayer.IsStop() || m_MediaPlayer.IsPause())
	{
		m_MediaPlayer.GetControls().play();
		GetDlgItem(IDC_BTN_PLAY_PAUSE)->SetWindowText(_T("|"));
		return;
	}
	
}

void CMakeLyricDlg::OnBtnStop() 
{
	if(m_MediaPlayer.IsPlay())
	{
		m_MediaPlayer.GetControls().stop();
	}
	
}

void CMakeLyricDlg::SetMediaTimeInfo()
{
	CString Duration = m_MediaPlayer.GetCurrentMedia().GetDurationString();
	GetDlgItem(IDC_STATIC_MEDIA_TIMEINFO)->SetWindowText(Duration);
}

