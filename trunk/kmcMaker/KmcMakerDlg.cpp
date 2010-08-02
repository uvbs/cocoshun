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
	m_bUseDir=FALSE;
}

CKmcMakerDlg::~CKmcMakerDlg()
{
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
}

void CKmcMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKmcMakerDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKmcMakerDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CKmcMakerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_STEP1, OnCheckStep1)
	ON_BN_CLICKED(IDC_CHECK_STEP2, OnCheckStep2)
	ON_BN_CLICKED(IDC_CHECK_STEP3, OnCheckStep3)
	ON_WM_SIZE()

	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CKmcMakerDlg message handlers

BOOL CKmcMakerDlg::OnInitDialog()
{
	CResizingDialog::OnInitDialog();
	
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

	static ChkBtnIDAndDlg ChkBtnIDAndDlgs[] =
	{
		{IDC_CHECK_STEP1, m_ImportLyricDlg},
		{IDC_CHECK_STEP2, m_MakeLyricDlg},
		{IDC_CHECK_STEP3, m_SaveLyricDlg}
	};

	static CheckGroupInfo ChkGrpInfo = 
	{ 
		this,
		0, 
		IDC_DLG_AREA,
		ChkBtnIDAndDlgs
	};

	m_CheckGroup.Init(ChkGrpInfo);
	
	SetControlInfo(IDOK,ANCHORE_LEFT | ANCHORE_BOTTOM);
	SetControlInfo(IDCANCEL,ANCHORE_LEFT| ANCHORE_BOTTOM);
	SetControlInfo(IDC_DLG_AREA, RESIZE_BOTH);
	SetControlInfo(IDC_STATIC_TOPLINE, RESIZE_HOR);
	m_ImportLyricDlg->SetFocus();

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
	m_CheckGroup.SetCheck(0);
	m_ImportLyricDlg->SetFocus();
}

void CKmcMakerDlg::OnCheckStep2() 
{
	CString Lyric;
	m_ImportLyricDlg->m_LyricEditor.GetWindowText(Lyric);
	Lyric.TrimLeft();
	Lyric.TrimRight();
	if(Lyric.IsEmpty())
	{
// 		MessageBox(_T("请导入歌词^_^!"));
// 		return;
	}
	m_MakeLyricDlg->InitLyric(Lyric);
	m_MakeLyricDlg->SetFocusToLyricMaker();
	m_CheckGroup.SetCheck(1);
}

void CKmcMakerDlg::OnCheckStep3() 
{
	m_CheckGroup.SetCheck(2);
//	m_MakeLyricDlg->m_LyricLines
	m_SaveLyricDlg->SetLyricInfo(&m_MakeLyricDlg->m_LyricLines,m_ImportLyricDlg->m_LyricText.GetLyricHeader());	
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
	m_ImportLyricDlg->SendMessage(WM_CUSTOM_MSG_DROPFILE,wParam,lParam);
	return 1L;
}

