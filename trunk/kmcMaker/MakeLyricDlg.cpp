// MakeLyricDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KmcMaker.h"
#include "MakeLyricDlg.h"

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
	DDX_Control(pDX, IDC_MEDIA_PLAYER, m_MediaPlayer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMakeLyricDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CMakeLyricDlg)
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakeLyricDlg message handlers

BOOL CMakeLyricDlg::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
//	m_MediaPlayer.SetFileName("F:\\My Music\\周杰伦 - 星晴.mp3");

	SetControlInfo(IDC_LYRIC_MAKER,RESIZE_BOTH);
	SetControlInfo(IDC_BTN_OPEN,ANCHORE_LEFT | ANCHORE_BOTTOM);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CMakeLyricDlg, CResizingDialog)
    //{{AFX_EVENTSINK_MAP(CMakeLyricDlg)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



void CMakeLyricDlg::OnBtnOpen() 
{
	m_MediaPlayer.Run();
	CString str;
	str.Format("%f",m_MediaPlayer.GetDuration());
	MessageBox(str);
}

void CMakeLyricDlg::InitLyric(CString Lyric)
{
//	Lyric = "一   个老虎 English \n二Chinese\n";
	if(Lyric.IsEmpty()) return;

	m_LyricLines.RemoveAll();
	CString Line;
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
		m_LyricLines.Add(LL);
	}

//	m_LyricMaker.LoadLyric();
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
