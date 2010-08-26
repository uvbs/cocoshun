// KmcMakerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KmcMaker.h"
#include "KmcMakerDlg.h"
#include "ImportLyricDlg.h"
#include "MakeLyricDlg.h"
#include "SaveLyricDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKmcMakerDlg dialog
CKmcMakerDlg::CKmcMakerDlg(CWnd* pParent /*=NULL*/)
: CResizingDialog(CKmcMakerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKmcMakerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_ImportLyricDlg = NULL;
	m_MakeLyricDlg = NULL;
	m_SaveLyricDlg = NULL;
	m_HelpDlg = NULL;

	m_bUseDir=FALSE;
	m_nFontsize = 18;
}

CKmcMakerDlg::~CKmcMakerDlg()
{
	m_LyricFont.DeleteObject();
	if(m_ImportLyricDlg!=NULL)
	{
		delete []m_ImportLyricDlg;
	}
	
	if(m_MakeLyricDlg!=NULL)
	{
		delete []m_MakeLyricDlg;
	}
	
	if(m_SaveLyricDlg!=NULL)
	{
		delete []m_SaveLyricDlg;
	}

	if(m_HelpDlg!=NULL)
	{
		delete []m_HelpDlg;
	}
}

void CKmcMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKmcMakerDlg)
	DDX_Control(pDX, IDCANCEL, m_BtnCancel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKmcMakerDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CKmcMakerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_CHECK_HELP, OnCheckHelp)
	ON_BN_CLICKED(IDC_CHECK_STEP1, OnCheckStep1)
	ON_BN_CLICKED(IDC_CHECK_STEP2, OnCheckStep2)
	ON_BN_CLICKED(IDC_CHECK_STEP3, OnCheckStep3)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CKmcMakerDlg message handlers

void CKmcMakerDlg::CreateLyricFont( int FontSize ) 
{
	m_LyricFont.DeleteObject();
	m_LyricFont.CreateFont(FontSize, 0, 0, 0, 
		FW_BLACK, FALSE, FALSE, 0, 
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH,
		_T("宋体"));
}

BOOL CKmcMakerDlg::OnInitDialog()
{
	CResizingDialog::OnInitDialog();

	CreateLyricFont(m_nFontsize);

	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	// Init dialog pages
	m_ImportLyricDlg = new CImportLyricDlg();
	m_ImportLyricDlg->Create(IDD_IMPORTLYRICDLG_DIALOG,this);
	m_MakeLyricDlg = new CMakeLyricDlg();
	m_MakeLyricDlg->Create(IDD_MAKELYRICDLG_DIALOG,this);
	m_SaveLyricDlg = new CSaveLyricDlg();
	m_SaveLyricDlg->Create(IDD_SAVELYRICDLG_DIALOG,this);
	m_HelpDlg = new CHelpDlg();
	m_HelpDlg->Create(IDD_HELP,this);

	static ChkBtnIDAndDlg ChkBtnIDAndDlgs[] =
	{
		{IDC_CHECK_STEP1, m_ImportLyricDlg, IDI_FOLDER},
		{IDC_CHECK_STEP2, m_MakeLyricDlg, IDI_STAR},
		{IDC_CHECK_STEP3, m_SaveLyricDlg,IDI_SAVE},
		{IDC_CHECK_HELP, m_HelpDlg,IDI_HELP}
	};

	static CheckGroupInfo ChkGrpInfo = 
	{ 
		this,
		0, 
		IDC_DLG_AREA,
		ChkBtnIDAndDlgs
	};

	m_CheckGroup.Init(ChkGrpInfo, 4);
	
// 	SetControlInfo(IDOK,ANCHORE_LEFT | ANCHORE_BOTTOM);
// 	SetControlInfo(IDCANCEL,ANCHORE_LEFT| ANCHORE_BOTTOM);
	SetControlInfo(IDC_DLG_AREA, RESIZE_BOTH);
	SetControlInfo(IDC_STATIC_TOPLINE, RESIZE_HOR);
	SetControlInfo(IDC_STATIC_LOGO, ANCHORE_RIGHT);
	
	m_ImportLyricDlg->SetFocus();

	m_BtnCancel.SetIcon(IDI_EXIT);

	// 右下角画上调整大小的角
	DrawGripper(TRUE);

	OnCheckStep1();
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CKmcMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ( (nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CResizingDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKmcMakerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CResizingDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKmcMakerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKmcMakerDlg::OnCheckStep1() 
{
	int nSelectPage = m_CheckGroup.GetCheck();
	BOOL bLeave = TRUE;


	if(!m_MakeLyricDlg->m_MediaPlayer.GetUrl().IsEmpty())
		m_MakeLyricDlg->m_MediaPlayer.GetControls().pause();

	if(bLeave)
		m_CheckGroup.SetCheck(0);
	else
		m_CheckGroup.SetCheck(nSelectPage);
}

void CKmcMakerDlg::OnCheckStep2() 
{
	int nSelectPage = m_CheckGroup.GetCheck();
	BOOL bLeave = TRUE;
	switch(nSelectPage)
	{
		case 0:
			CString Lyric;
			m_ImportLyricDlg->GetLyric(Lyric);
			m_MakeLyricDlg->InitLyric(Lyric);
			break;		
	}

	if(bLeave)
	{
		m_CheckGroup.SetCheck(1);
		m_MakeLyricDlg->SetFocus();
		m_MakeLyricDlg->FocusToLyricMaker();
	}
	else
		m_CheckGroup.SetCheck(nSelectPage);
}

void CKmcMakerDlg::OnCheckStep3() 
{
	int nSelectPage = m_CheckGroup.GetCheck();
	BOOL bLeave = TRUE;
	switch(nSelectPage)
	{

		case 1:
			//取得Duration
			m_ImportLyricDlg->m_LyricText.GetLyricHeader()->duration = m_MakeLyricDlg->GetMediaDuration();

			//设置歌词信息
			m_SaveLyricDlg->SetLyricInfo(&m_MakeLyricDlg->m_LyricLines,m_ImportLyricDlg->m_LyricText.GetLyricHeader());
			break;
	}

	m_MakeLyricDlg->m_MediaPlayer.GetControls().pause();
	if(bLeave)
		m_CheckGroup.SetCheck(2);
	else
		m_CheckGroup.SetCheck(nSelectPage);
}


void CKmcMakerDlg::OnCheckHelp() 
{
	m_MakeLyricDlg->m_MediaPlayer.GetControls().pause();
	m_CheckGroup.SetCheck(3);
	m_HelpDlg->OpenHelp();
}

// LRESULT CKmcMakerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
// {
// 	
// 	return CDialog::WindowProc(message, wParam, lParam); 
// }

void CKmcMakerDlg::OnSize(UINT nType, int cx, int cy) 
{
	CResizingDialog::OnSize(nType, cx, cy);
	if (nType == SIZE_MAXIMIZED || nType == SIZE_RESTORED )     //   这句 
	{ 
		if(m_CheckGroup.IsCreated())
		{
			m_CheckGroup.ReSizePages();
		}
	} 
}

LRESULT CKmcMakerDlg::OnAcceptDropFile(WPARAM wParam , LPARAM lParam  )
{
	if(m_CheckGroup.GetCheck() == 0)
	{
		m_ImportLyricDlg->SendMessage(WM_CUSTOM_MSG_DROPFILE,wParam,lParam);
	}

	if(m_CheckGroup.GetCheck() == 1)
	{
		m_MakeLyricDlg->SendMessage(WM_CUSTOM_MSG_DROPFILE,wParam,lParam);
	}
	
	return 1L;
}

void CKmcMakerDlg::OnCancel() 
{
	int nSelectPage = m_CheckGroup.GetCheck();
	BOOL bLeave = TRUE;
	switch(nSelectPage)
	{
		case 0:

		case 1:
			if(!m_MakeLyricDlg->CheckLeaveToPrev())
				return;
			break;
		case 2:
			if(!m_SaveLyricDlg->CheckLeave())
				return;
			break;
	}
	CResizingDialog::OnCancel();
}

CFont& CKmcMakerDlg::GetLyricFont()
{
	return m_LyricFont;
}
