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
//	m_MediaPlayer.SetFileName("F:\\My Music\\ÖÜ½ÜÂ× - ÐÇÇç.mp3");

	m_LyricMaker.SetCredits("ÖÜ½ÜÂ× - ÐÇÇç");
	SetControlInfo(IDC_LYRIC_MAKER,RESIZE_BOTH);
	SetControlInfo(IDC_BTN_OPEN,ANCHORE_LEFT | ANCHORE_BOTTOM);
//	SetControlInfo(IDC_MEDIA_PLAYER, RESIZE_BOTH);
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
