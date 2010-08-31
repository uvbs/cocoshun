// MyToolBoxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyToolBox.h"
#include "MyToolBoxDlg.h"
#include "Util/SysUtil.h"

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
// CMyToolBoxDlg dialog

CMyToolBoxDlg::CMyToolBoxDlg(CWnd* pParent /*=NULL*/)
	: CResizingDialog(CMyToolBoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyToolBoxDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_GeneralTool = NULL;
	m_Win7Setting = NULL;
}

void CMyToolBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyToolBoxDlg)
	DDX_Control(pDX, IDC_BTN_EXIT, m_BtnExit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyToolBoxDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CMyToolBoxDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_WIN7SETTING, OnBtnWin7setting)
	ON_BN_CLICKED(IDC_BTN_GENERALTOOL, OnBtnGeneraltool)
	ON_BN_CLICKED(IDC_BTN_CLEARTOOL, OnBtnCleartool)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyToolBoxDlg message handlers

BOOL CMyToolBoxDlg::OnInitDialog()
{
    // 右下角画上调整大小的角
	DrawGripper(TRUE);

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
	m_Win7Setting = new Win7Setting();
	m_Win7Setting->Create(IDD_WIN7SETTING_DIALOG,this);
	m_GeneralTool = new GeneralTool();
	m_GeneralTool->Create(IDD_GENERALTOOL_DIALOG,this);
    m_ClearTool = new CClearHistoryDlg();
    m_ClearTool->Create(IDD_CLEAR_HISTORY_DLG,this);
	
	static CCheckBTGroup::ChkBtnIDAndDlg ChkBtnIDAndDlgs[] =
	{
		{IDC_BTN_WIN7SETTING, m_Win7Setting, IDI_WIN7},
		{IDC_BTN_GENERALTOOL, m_GeneralTool, IDI_GENERAL},
        {IDC_BTN_CLEARTOOL, m_ClearTool, IDI_GENERAL},
	};
	
	static CCheckBTGroup::CheckGroupInfo ChkGrpInfo = 
	{ 
		this,
		0, 
		IDC_STATIC_DLGAREA,
		ChkBtnIDAndDlgs
	};
	m_CheckGroup.Init(ChkGrpInfo, 3);
    m_BtnExit.SetIcon(IDI_EXIT);

	SetControlInfo(IDC_STATIC_DLGAREA,RESIZE_BOTH);
	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CMyToolBoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
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

void CMyToolBoxDlg::OnPaint() 
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
HCURSOR CMyToolBoxDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyToolBoxDlg::OnCancel() 
{
	CResizingDialog::OnCancel();
}

void CMyToolBoxDlg::OnOK() 
{
	CResizingDialog::OnOK();
}

void CMyToolBoxDlg::OnBtnExit() 
{
	CResizingDialog::OnCancel();	
}

void CMyToolBoxDlg::OnBtnWin7setting() 
{
	m_CheckGroup.SetCheck(0);
}

void CMyToolBoxDlg::OnBtnGeneraltool() 
{
	m_CheckGroup.SetCheck(1);
}

void CMyToolBoxDlg::OnBtnCleartool() 
{
	m_CheckGroup.SetCheck(2);
}

BOOL CMyToolBoxDlg::DestroyWindow() 
{
	return CResizingDialog::DestroyWindow();
}
