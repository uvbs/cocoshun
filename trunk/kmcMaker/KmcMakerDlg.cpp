// KmcMakerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KmcMaker.h"
#include "KmcMakerDlg.h"

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
UINT CKmcMakerDlg::CheckBtnIDs[] = 
{
	IDC_CHECK_STEP1,
	IDC_CHECK_STEP2,
	IDC_CHECK_STEP3,
};

CKmcMakerDlg::CKmcMakerDlg(CWnd* pParent /*=NULL*/)
: CResizingDialog(CKmcMakerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKmcMakerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	SetControlInfo(IDOK,				ANCHORE_RIGHT);
	SetControlInfo(IDCANCEL,			ANCHORE_RIGHT);
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
	m_CheckGroup.SubClassWindows(this,CheckBtnIDs,0);

	//////////////////////////////////////////////////////////////////////////
// 	m_DLayout.InitLayout( this );
// 	m_DLayout.SetDialogMaxSize( 800,600 );
// 	m_DLayout.SetDialogMinSize( 200,100 );
// 	
//  	m_DLayout.AddPanel("��","",1,1,1,1);
// 	m_DLayout.AddPanel("��","",0,1,1,1);
// 	
// 	m_DLayout.AddPanel("����","��",1,1,1,1);
// 	m_DLayout.AddControl(IDC_LIST_LIST,"����",1,1,1,1);
// 	m_DLayout.AddPanel("������","����",0,1,1,0);
// 	m_DLayout.AddControl(IDC_BTN_MODAL,"������",1,1,1,0);
// 	m_DLayout.AddControl(IDC_BTN_MODALNESS,"������",1,1,1,0);
// 	m_DLayout.AddControl(IDOK,"������",1,1,1,0);
// 	
// 	m_DLayout.AddPanel("����","��",1,1,1,0);
// 	m_DLayout.AddControl(IDC_TREE1,"����",1,1,1,1);
// 	
// 	m_DLayout.AddPanel("����","��",1,1,1,0);
// 	m_DLayout.AddControl(IDC_LIST2,"����",1,1,1,1);
// 	m_DLayout.AddPanel("����","��",1,1,1,1);	
// 	m_DLayout.AddControl(IDC_EDIT1,"����",1,1,1,1);
// 	m_DLayout.AddControl(IDC_STATIC_COMMAND,"����",1,0,1,0);
// 	m_DLayout.AddControl(IDC_EDIT2,"����",1,0,1,1);
	
// 	m_DLayout.SetBkColor( "��",    RGB(160,160,255));
// 	m_DLayout.SetBkColor( "����",  RGB(128,128,255));
// 	m_DLayout.SetBkColor("������", RGB(128,255,128));
// 	
// 	//m_DLayout.UpdateLayout();
// 	m_DLayout.ShowPanel("",TRUE);
// 	m_DLayout.SetSplit("");
// 	m_DLayout.SetSplit("��");
// 	m_DLayout.SetSplit("��" );
	
	//////////////////////////////////////////////////////////////////////////
	

	CRect rect;
	GetDlgItem(IDC_DLG_AREA)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	ImportLyricDlg.Create(IDD_IMPORTLYRICDLG_DIALOG,this);
	ImportLyricDlg.MoveWindow(rect.left, rect.top, rect.Width(), rect.Height());
	ImportLyricDlg.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKmcMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
}

void CKmcMakerDlg::OnCheckStep2() 
{
	m_CheckGroup.SetCheck(1);
	}

void CKmcMakerDlg::OnCheckStep3() 
{
	m_CheckGroup.SetCheck(2);		
}

// LRESULT CKmcMakerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
// {
// 	// TODO: Add your specialized code here and/or call the base class
// 	m_DLayout.FilterDynamicLayoutMessage(message,wParam,lParam);
// 	
// 	return CDialog::WindowProc(message, wParam, lParam); 
// }