// MakeLyricDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KmcMaker.h"
#include "MakeLyricDlg.h"
#include "UILib/FileDialogEx.h"
#include "wmpmedia.h"
#include "wmperror.h"
#include "WMPErrorItem.h"
#include "KmcMakerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_MEDIAPLAYER_SLIDER 5000
/////////////////////////////////////////////////////////////////////////////
// CMakeLyricDlg dialog


CMakeLyricDlg::CMakeLyricDlg(CWnd* pParent /*=NULL*/)
: CResizingDialog(CMakeLyricDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMakeLyricDlg)
	//}}AFX_DATA_INIT
	m_IsSliderMoving = FALSE;
}


void CMakeLyricDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMakeLyricDlg)
	DDX_Control(pDX, IDC_BTN_NEXTSTEP, m_BtnNextStep);
	DDX_Control(pDX, IDC_BTN_PREVSTEP, m_BtnPrevStep);
	DDX_Control(pDX, IDC_BTN_STOP, m_BtnStop);
	DDX_Control(pDX, IDC_BTN_OPEN, m_BtnOpen);
	DDX_Control(pDX, IDC_BTN_PLAY_PAUSE, m_BtnPlayPause);
	DDX_Control(pDX, IDC_LYRIC_MAKER, m_LyricMaker);
	DDX_Control(pDX, IDC_MEDIAPLAYER, m_MediaPlayer);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_SLIDER_MP, m_SliderMP);
}


BEGIN_MESSAGE_MAP(CMakeLyricDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CMakeLyricDlg)
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_PRIVIEW, OnBtnPriview)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_BN_CLICKED(IDC_BTN_PREVSTEP, OnBtnPrevstep)
	ON_BN_CLICKED(IDC_BTN_NEXTSTEP, OnBtnNextstep)
	ON_BN_CLICKED(IDC_BTN_PLAY_PAUSE, OnBtnPlayPause)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_BITMAPSLIDER_MOVED, OnBitmapSliderMoved)
	ON_MESSAGE(WM_BITMAPSLIDER_MOVING, OnBitmapSliderMoving)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakeLyricDlg message handlers

BOOL CMakeLyricDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();

	//m_BtnNextStep
	m_BtnOpen.SetIcon(IDI_OPEN);
	m_BtnOpen.SetTooltipText(_T("打开媒体文件"));

	m_BtnPlayPause.SetIcon(IDI_PLAY);
	m_BtnPlayPause.SetTooltipText(_T("播放/暂停"));

	m_BtnStop.SetIcon(IDI_STOP);
	m_BtnStop.SetTooltipText(_T("停止播放"));

	m_BtnPrevStep.SetIcon(IDI_PREV);
	m_BtnNextStep.SetIcon(IDI_NEXT);

	// 设置滑杆外观
	m_SliderMP.SetBitmapChannel( IDB_MP_CHANNEL, IDB_MP_CHANNEL_ACTIVE );
	m_SliderMP.SetBitmapThumb( IDB_MP_THUMB, IDB_MP_THUMB_ACTIVE, TRUE );
	m_SliderMP.SetMargin( 2, 3, 2, 0 );
	m_SliderMP.DrawFocusRect( FALSE );
	
	SetControlInfo(IDC_SLIDER_MP,ANCHORE_RIGHT);
	
	SetControlInfo(IDC_LYRIC_MAKER,ANCHORE_LEFT);
	SetControlInfo(IDC_STATIC_MEDIA_TIMEINFO,ANCHORE_RIGHT);
	
	SetControlInfo(IDC_LYRIC_MAKER,RESIZE_BOTH);
	SetControlInfo(IDC_STATIC_TIP,ANCHORE_RIGHT);

	SetControlInfo(IDC_BTN_OPEN,ANCHORE_RIGHT);
	SetControlInfo(IDC_BTN_PLAY_PAUSE,ANCHORE_RIGHT);
	SetControlInfo(IDC_BTN_STOP,ANCHORE_RIGHT);

	SetControlInfo(IDC_STATIC_KEY_TIP,ANCHORE_RIGHT);
	SetControlInfo(IDC_BTN_NEXTSTEP,ANCHORE_RIGHT | ANCHORE_BOTTOM);
	SetControlInfo(IDC_BTN_PREVSTEP,ANCHORE_RIGHT | ANCHORE_BOTTOM);
	SetControlInfo(IDC_BTN_PRIVIEW,ANCHORE_LEFT | ANCHORE_BOTTOM);
	SetControlInfo(IDC_MEDIAPLAYER, ANCHORE_RIGHT | ANCHORE_TOP);

//   	m_MediaPlayer.SetUrl(_T(".\\Test\\十年1.mp3"));
//   	m_MediaPlayer.GetControls().play();

	FocusToLyricMaker();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CMakeLyricDlg::OnBtnOpen() 
{
	TCHAR szFilter[] = _T("所有媒体文件 (*.mp3;*.wav;*.wmv;*.mpeg;*.mpg;*.asf)\
							|*.mp3; *.wav; *.wmv; *.mpeg; *.mpg; *.asf\
							|音频文件 (*.mp3;*.wav;*.wmv)|*.mp3; *.wav; *.wmv|\
							视频频文件 (*.mpeg;*.mpg;*.asf)|*.mpeg; *.mpg; *.asf|All Files (*.*)|*.*||");
	CFileDialogEx FileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);;
	if( FileDlg.DoModal() == IDOK)
	{
		CString fname = FileDlg.GetPathName();
		m_MediaPlayer.SetUrl(fname);
		m_BtnPlayPause.SetIcon(IDI_PLAY);
		InitPlaySlider();
	}
	FocusToLyricMaker();
}

/************************************************************************/
/* 定位修改的歌词行,并删除多余的行                                      */
/* retrun 返回已经修改的行号											*/
/************************************************************************/
int CMakeLyricDlg::FixedModifiedLyric( CString Lyric, vector<LyricLine> &m_LyricLines ) 
{
	CString Line;
	vector<LyricLine> LyriceLinesCopy = m_LyricLines;

	//重新解析歌词
	m_LyricLines.clear();
	ParseTextToLyricLine(Lyric);

	//定位修改位置
	int nModifiedStart = 0;
	for(int i=0;i<m_LyricLines.size() && i<LyriceLinesCopy.size() ;i++)
	{
		LyricLine &l1 = m_LyricLines.at(i);
		LyricLine &l2 = LyriceLinesCopy.at(i);
		if(l1.Line.Compare(l2.Line) == 0 )
		{
			BOOL bMarkedAllLine = TRUE;
			for(int j=0;j<l2.LyricWords.size();j++)
			{
				LyricWord lw = l2.LyricWords.at(j);
				if(!lw.IsMarkedAll())
				{
					bMarkedAllLine = FALSE;
					break;
				}
			}

			if(bMarkedAllLine)
			{
				nModifiedStart++;
				l1 = l2;
			}
		}else
		{
			break;
		}
	}

	LyriceLinesCopy.clear();
	return nModifiedStart;
// 	vector<LyricLine>::iterator it;
// 	
// 	// 得到修改后的歌词行数
// 	int nLyricTextCount;
// 	for(nLyricTextCount=0, nCount=0; AfxExtractSubString(Line, Lyric, nCount++, '\n'); )
// 	{
// 		if(!Line.IsEmpty())
// 			nLyricTextCount++;
// 	}
// 
// 	// 删除文本后,也删除歌词结构中多余的行
// 	if(nLyricTextCount < m_LyricLines.size())
// 	{
// 		//从最后vector的最后一个元素开始删除
// 		while(m_LyricLines.size() > nLyricTextCount)
// 		{
// 			it=m_LyricLines.end() - 1 ;
// 			m_LyricLines.erase(it);
// 		}
// 	}
// 
// 	// 得到被修改后的开始位置
// 	int nModifiedStart = 0;
// 	it=m_LyricLines.begin();
// 	for(nCount=0;AfxExtractSubString(Line, Lyric, nCount++, '\n') && it!=m_LyricLines.end();)
// 	{
// 		if(Line.IsEmpty())
// 			continue;
// 
// 		while(Line.Compare(it->Line)!=0 && it!=m_LyricLines.end())
// 		{
// 			m_LyricLines.erase(it);
// 			continue;
// 		}
// 		it++;
// 		nModifiedStart++;
// 	}
// 
// 
// 	//解析添加后多出来的歌词文本
// 	ParseTextToLyricLine( Lyric, nModifiedStart+1);
}

void CMakeLyricDlg::InitLyric(CString Lyric)
{
	if(Lyric.IsEmpty()) 
	{
		m_LyricLines.clear();
		m_LyricMaker.SetLyricLines( &m_LyricLines);
		return;
	}

	int nModifiedStart = 0;
	if(m_LyricLines.empty())
	{
		//第一次解析
		ParseTextToLyricLine(Lyric);
	}else
	{
		// 如果歌词结构不为空,则为修改歌词之后返回制作页面
		nModifiedStart = FixedModifiedLyric(Lyric, m_LyricLines);
		
	}
	m_LyricMaker.SetLyricLines( &m_LyricLines);
	m_LyricMaker.SetStartLine(nModifiedStart);
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

void CMakeLyricDlg::FocusToLyricMaker()
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
	InitPlaySlider();
	return 0;
}


LRESULT CMakeLyricDlg::OnBitmapSliderMoved(WPARAM wParam, LPARAM lParam)
{
	switch( wParam ) 
	{
		case IDC_SLIDER_MP :
			m_IsSliderMoving = FALSE;
			m_MediaPlayer.GetControls().SetCurrentPosition(m_SliderMP.GetPos());
			break;
	}
	return 0;
}

LRESULT CMakeLyricDlg::OnBitmapSliderMoving(WPARAM wParam, LPARAM lParam)
{
	switch( wParam ) 
	{
		case IDC_SLIDER_MP :
			m_IsSliderMoving = TRUE;
			break;
	}
	
	return 0;
}

void CMakeLyricDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == TIMER_MEDIAPLAYER_SLIDER)
	{
		if(	!m_IsSliderMoving )
			ShowPlayerTimeInfo();
	}
}

void CMakeLyricDlg::OnBtnPlayPause() 
{
	CString url = m_MediaPlayer.GetUrl();
	if(url.IsEmpty())
		return;

	if(m_MediaPlayer.IsPlay())
	{
		m_MediaPlayer.GetControls().pause();
		return;
	}
	
	if(m_MediaPlayer.IsStop() || m_MediaPlayer.IsPause() || m_MediaPlayer.IsReady())
	{
		m_MediaPlayer.GetControls().play();
		return;
	}
}

void CMakeLyricDlg::OnBtnStop() 
{
	m_MediaPlayer.GetControls().stop();
	InitPlaySlider();
}

void CMakeLyricDlg::InitMediaCtrls()
{
	ShowPlayerTimeInfo();
	
	// 初始化滑杆
	InitPlaySlider();
}


BEGIN_EVENTSINK_MAP(CMakeLyricDlg, CResizingDialog)
    //{{AFX_EVENTSINK_MAP(CMakeLyricDlg)
	ON_EVENT(CMakeLyricDlg, IDC_MEDIAPLAYER, 5001 /* OpenStateChange */, OnOpenStateChangeMediaplayer, VTS_I4)
	ON_EVENT(CMakeLyricDlg, IDC_MEDIAPLAYER, 5101 /* PlayStateChange */, OnPlayStateChangeMediaplayer, VTS_I4)
	ON_EVENT(CMakeLyricDlg, IDC_MEDIAPLAYER, 5202 /* PositionChange */, OnPositionChangeMediaplayer, VTS_R8 VTS_R8)
	ON_EVENT(CMakeLyricDlg, IDC_MEDIAPLAYER, 5501 /* Error */, OnErrorMediaplayer, VTS_NONE)
	ON_EVENT(CMakeLyricDlg, IDC_MEDIAPLAYER, 5821 /* MediaError */, OnMediaErrorMediaplayer, VTS_DISPATCH)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CMakeLyricDlg::OnOpenStateChangeMediaplayer(long NewState) 
{
	// 为开始播放状态设置控件
	if(NewState == 13)
		InitMediaCtrls();
}

void CMakeLyricDlg::OnPlayStateChangeMediaplayer(long NewState) 
{
	if(NewState == PLAYSTATE_BUFFERING 
		|| NewState == PLAYSTATE_FINISHED 
		|| NewState == PLAYSTATE_READY
		|| NewState == PLAYSTATE_PAUSE
		|| NewState == PLAYSTATE_STOP)
	{
		KillTimer(TIMER_MEDIAPLAYER_SLIDER);
		m_BtnPlayPause.SetIcon(IDI_PLAY);
		
	}
	if(NewState == PLAYSTATE_PLAY)
	{
		SetTimer(TIMER_MEDIAPLAYER_SLIDER, 1000, NULL);
		m_BtnPlayPause.SetIcon(IDI_PAUSE);
	}

	FocusToLyricMaker();
}

void CMakeLyricDlg::OnPositionChangeMediaplayer(double oldPosition, double newPosition) 
{
	FocusToLyricMaker();
}

void CMakeLyricDlg::ShowPlayerTimeInfo()
{
	// 设置播放时间
	CString CurrentPosition =  m_MediaPlayer.GetControls().GetCurrentPositionString();
	if(CurrentPosition.IsEmpty())
		CurrentPosition = _T("00:00");
	CString Duration = m_MediaPlayer.GetCurrentMedia().GetDurationString();
	GetDlgItem(IDC_STATIC_MEDIA_TIMEINFO)->SetWindowText(CurrentPosition + _T("/") + Duration);

	double Postion = m_MediaPlayer.GetControls().GetCurrentPosition();
	m_SliderMP.SetPos(Postion);
}

void CMakeLyricDlg::InitPlaySlider()
{
	double Duration = m_MediaPlayer.GetCurrentMedia().GetDuration();

	m_SliderMP.SetRange(0, Duration );
	m_SliderMP.SetPos( 0 );
}

void CMakeLyricDlg::OnBtnPrevstep() 
{
	((CKmcMakerDlg *)GetParent())->OnCheckStep1();
}
void CMakeLyricDlg::OnBtnNextstep() 
{
	((CKmcMakerDlg *)GetParent())->OnCheckStep3();
}

BOOL CMakeLyricDlg::IsMarkedAll()
{
	int maxY = m_LyricLines.size() - 1;
	int maxX = m_LyricLines.at(maxY).LyricWords.size() - 1;
	return  m_LyricLines.at(maxY).LyricWords.at(maxX).IsMarkedAll();
}


BOOL CMakeLyricDlg::IsMarkedFirst()
{
	if(m_LyricLines.empty())
		return FALSE;
	return  m_LyricLines.at(0).LyricWords.at(0).MarkedStart;
}

BOOL CMakeLyricDlg::CheckLeaveToPrev()
{
	if(IsMarkedFirst())
	{
		m_MediaPlayer.GetControls().pause();
// 		int ret = MessageBox(_T("返回到上一步将丢失你已经标记的歌词信息，您确定要返回到上一步吗？"),
// 			_T("提示"),MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION);
		int ret = MessageBox(_T("您还没有标记完歌词,确定要退出吗？"),
			_T("提示"),MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION);		
		if( ret == IDNO)
		{
			m_MediaPlayer.GetControls().play();
			return FALSE;
		}
	}
	OnBtnStop();
	return TRUE;
}

BOOL CMakeLyricDlg::CheckLeaveToNext()
{
	if(IsMarkedFirst() && !IsMarkedAll())
	{
		m_MediaPlayer.GetControls().pause();
		MessageBox(_T("请标记完所有的歌词再进行下一步."),
			_T("提示"),MB_OK | MB_ICONINFORMATION);
		
		m_MediaPlayer.GetControls().play();
		return FALSE;
	}
	
	OnBtnStop();
	return TRUE;
}


void CMakeLyricDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CResizingDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}


CString CMakeLyricDlg::GetMediaDuration()
{
	return m_MediaPlayer.GetCurrentMedia().GetDurationString();
}

void CMakeLyricDlg::ParseTextToLyricLine( CString &Lyric , int nStartLine)
{
	CString Line;
	TCHAR lBracket = _T('(');
	TCHAR rBracket = _T(')');
	
	int nCount=0;
	for(int nLine = 0;AfxExtractSubString(Line, Lyric, nCount++, '\n');nLine++)
	{
		if(nLine < nStartLine)
			continue;
		LyricLine LL;
		if(Line.IsEmpty()) 
			continue;
		LL.Line = Line;
		
		int Pos = 0;
		int n = -1;
		int Len = Line.GetLength();
		while(Pos < Len)
		{
			n++;
			LyricWord LyWord;
			
			
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
						
						// 跳过带括号的开头
						continue;
					}
				}
			}
			
			// check Chinese
			if(ch & 0x80)
			{
				LyWord.IsChs = TRUE;
				LyWord.Word = Line.Mid(Pos,2);
				Pos+=2;
				
				// add space
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
}

void CMakeLyricDlg::OnErrorMediaplayer() 
{
	CWMPError   Error=m_MediaPlayer.GetError(); 
	CWMPErrorItem   ErrorItem=Error.GetItem(0); 
	CString ErrorMsg;
	ErrorMsg.Format(_T( "%s"), ErrorItem.GetErrorDescription()); 
	MessageBox(ErrorMsg,_T("错误"),MB_ICONSTOP);
	Error.clearErrorQueue();
}

void CMakeLyricDlg::OnMediaErrorMediaplayer(LPDISPATCH pMediaObject) 
{
	CWMPError   Error=m_MediaPlayer.GetError(); 
	CWMPErrorItem   ErrorItem=Error.GetItem(0); 
	CString ErrorMsg;
	ErrorMsg.Format(_T( "%s"), ErrorItem.GetErrorDescription()); 
	MessageBox(ErrorMsg,_T("错误"),MB_ICONSTOP);
	Error.clearErrorQueue();
}
