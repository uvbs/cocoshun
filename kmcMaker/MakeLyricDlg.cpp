// MakeLyricDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KmcMaker.h"
#include "MakeLyricDlg.h"
#include "UILib/FileDialogEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
}


BEGIN_MESSAGE_MAP(CMakeLyricDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CMakeLyricDlg)
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_PRIVIEW, OnBtnPriview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakeLyricDlg message handlers

BOOL CMakeLyricDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();

	SetControlInfo(IDC_LYRIC_MAKER,RESIZE_BOTH);
	SetControlInfo(IDC_STATIC_TIP,ANCHORE_RIGHT);
	SetControlInfo(IDC_BTN_OPEN,ANCHORE_LEFT | ANCHORE_BOTTOM);
	SetControlInfo(IDC_BTN_PRIVIEW,ANCHORE_LEFT | ANCHORE_BOTTOM);
	SetControlInfo(IDC_MEDIAPLAYER, ANCHORE_BOTTOM | ANCHORE_LEFT);

// 	m_MediaPlayer.SetUrl(_T(".\\Test\\十年.mp3"));
// 	m_MediaPlayer.GetControls().play();

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
// 	m_MediaPlayer.SetUrl(_T(".\\Test\\十年.mp3"));
// 	m_MediaPlayer.GetControls().play();
	SetFocusToLyricMaker();
}

void CMakeLyricDlg::InitLyric(CString Lyric)
{
//	Lyric = "一   个老虎 English \n二Chinese\n";
	if(Lyric.IsEmpty()) return;

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
		int Len = Line.GetLength();
		while(Pos < Len)
		{
			LyricWord LyWord;

			// check chinese
			TCHAR ch = Line.GetAt(Pos);

			if(LL.LyricWords.empty())
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
			}else
			{
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
