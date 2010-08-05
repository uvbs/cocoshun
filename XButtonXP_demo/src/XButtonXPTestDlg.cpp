// XButtonXPTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XButtonXPTest.h"
#include "XButtonXPTestDlg.h"
#include "about.h"
#include "ColorDlg.h"
#include "XTrace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//=============================================================================
BEGIN_MESSAGE_MAP(CXButtonXPTestDlg, CDialog)
//=============================================================================	
	//{{AFX_MSG_MAP(CXButtonXPTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_ICON_LEFT, OnIconLeft)
	ON_BN_CLICKED(IDC_ICON_NO, OnIconNo)
	ON_BN_CLICKED(IDC_ICON_RIGHT, OnIconRight)
	ON_BN_CLICKED(IDC_TOGGLE, OnToggle)
	ON_BN_CLICKED(IDC_TEXT_NO, OnTextNo)
	ON_BN_CLICKED(IDC_THEME, OnTheme)
	ON_BN_CLICKED(IDC_TOOLBAR, OnToolbar)
	ON_BN_CLICKED(IDC_DISABLED, OnDisabled)
	ON_BN_CLICKED(IDC_MULTILINE, OnMultiline)
	ON_BN_CLICKED(IDC_DEFAULT, OnDefault)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_PATTERN, OnPattern)
	ON_CBN_SELENDOK(IDC_ICON_COMBO, OnSelendokIconCombo)
	ON_BN_CLICKED(IDC_ONLINE_HELP, OnOnlineHelp)
	ON_BN_CLICKED(IDC_COLORS, OnColors)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//=============================================================================	
CXButtonXPTestDlg::CXButtonXPTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXButtonXPTestDlg::IDD, pParent)
//=============================================================================	
{
	//{{AFX_DATA_INIT(CXButtonXPTestDlg)
	m_nIcon = 0;
	m_bTheme = TRUE;
	m_bMultiLine = FALSE;
	m_bDisabled = FALSE;
	m_bDefault = FALSE;
	m_bMessageBox = FALSE;
	m_bPattern = FALSE;
	m_nIconIndex = -1;
	m_bToolbar = FALSE;
	m_bToggle = FALSE;
	//}}AFX_DATA_INIT
	m_strButton2Title = _T("Button 2");
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// create hatch brush for background
	m_brush.CreateHatchBrush(HS_CROSS, RGB(240,240,240));
	m_nIconId = IDI_MFC256;
}

//=============================================================================	
void CXButtonXPTestDlg::DoDataExchange(CDataExchange* pDX)
//=============================================================================	
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXButtonXPTestDlg)
	DDX_Control(pDX, IDC_ICON_COMBO, m_comboIcon);
	DDX_Control(pDX, IDC_TOOLBAR, m_chkToolbar);
	DDX_Control(pDX, IDC_THEME, m_chkTheme);
	DDX_Control(pDX, IDC_TOGGLE, m_chkToggle);
	DDX_Control(pDX, IDC_EDIT2, m_edtCount2);
	DDX_Control(pDX, IDC_EDIT1, m_edtCount1);
	DDX_Control(pDX, IDC_BUTTON2, m_XButtonXP);
	DDX_Radio(pDX, IDC_ICON_LEFT, m_nIcon);
	DDX_Check(pDX, IDC_THEME, m_bTheme);
	DDX_Check(pDX, IDC_MULTILINE, m_bMultiLine);
	DDX_Check(pDX, IDC_DISABLED, m_bDisabled);
	DDX_Check(pDX, IDC_DEFAULT, m_bDefault);
	DDX_Check(pDX, IDC_MESSAGEBOX, m_bMessageBox);
	DDX_Check(pDX, IDC_PATTERN, m_bPattern);
	DDX_CBIndex(pDX, IDC_ICON_COMBO, m_nIconIndex);
	DDX_Check(pDX, IDC_TOOLBAR, m_bToolbar);
	DDX_Check(pDX, IDC_TOGGLE, m_bToggle);
	//}}AFX_DATA_MAP
}

//=============================================================================	
BOOL CXButtonXPTestDlg::OnInitDialog()
//=============================================================================	
{
	CDialog::OnInitDialog();

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
	
	m_edtCount1.SetWindowText(_T("0"));
	m_edtCount2.SetWindowText(_T("0"));

	m_nIconIndex = GetIconIndex();
	m_comboIcon.SetCurSel(m_nIconIndex);

	m_XButtonXP.SetIcon(m_nIconId, CXButtonXP::LEFT)
			   .SetToggle(FALSE)
			   .EnableTheming(TRUE)
			   .SetDrawToolbar(FALSE);

	//m_XButtonXP.SetBackgroundColor(RGB(255, 0, 0));
	//m_XButtonXP.SetTextColor(RGB(255, 255, 255));

	m_bMultiLine = m_XButtonXP.GetButtonStyle() & BS_MULTILINE;
	m_strButton2Title = m_bMultiLine ? _T("Button 2\nLine 2") : _T("Button 2");
	m_XButtonXP.SetWindowText(m_strButton2Title);

	m_bDisabled = m_XButtonXP.GetStyle() & WS_DISABLED;

	m_bDefault = m_XButtonXP.IsDefault();

	// create tooltips
	m_ToolTips.Create(this, TTS_ALWAYSTIP);
	::SendMessage(m_ToolTips.m_hWnd, TTM_SETMAXTIPWIDTH, 0, SHRT_MAX);

	CString strHelp = _T("");
	VERIFY(strHelp.LoadString(IDS_ONLINE_HELP));

	m_ToolTips.AddTool(GetDlgItem(IDC_BUTTON1), _T("Standard Pushbutton"));
	m_ToolTips.AddTool(GetDlgItem(IDC_BUTTON2), _T("XButtonXP"));
	m_ToolTips.AddTool(GetDlgItem(IDC_ONLINE_HELP), strHelp);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

//=============================================================================	
int CXButtonXPTestDlg::GetIconIndex()
//=============================================================================	
{
	int index = 0;

	switch (m_nIconId)
	{
		default:			ASSERT(FALSE);
		case IDI_MFC16:		index = 0; break;
		case IDI_MFC256:	index = 1; break;
		case IDI_MFC24BPP:	index = 2; break;
		case IDI_MFC32BPP:	index = 3; break;
	}

	return index;
}

//=============================================================================	
HBRUSH CXButtonXPTestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
//=============================================================================	
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (m_bPattern)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(RGB(255,255,255));
		hbr = (HBRUSH) GetStockObject(WHITE_BRUSH);
	}

	return hbr;
}

//=============================================================================	
BOOL CXButtonXPTestDlg::OnEraseBkgnd(CDC* pDC) 
//=============================================================================	
{
	if (m_bPattern)
	{
		CRect rect;
		GetClientRect(&rect);
		pDC->FillRect(&rect, &m_brush);
		return TRUE;
	}
	else
	{
		return CDialog::OnEraseBkgnd(pDC);
	}
}

//=============================================================================	
void CXButtonXPTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
//=============================================================================	
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

//=============================================================================	
void CXButtonXPTestDlg::OnPaint() 
//=============================================================================	
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
		CDialog::OnPaint();
	}
}

//=============================================================================	
HCURSOR CXButtonXPTestDlg::OnQueryDragIcon()
//=============================================================================	
{
	return (HCURSOR) m_hIcon;
}

//=============================================================================
BOOL CXButtonXPTestDlg::PreTranslateMessage(MSG* pMsg) 
//=============================================================================
{
	if ((pMsg->hwnd == 0) || !IsWindow(pMsg->hwnd))
		return TRUE;

	m_ToolTips.RelayEvent(pMsg);

	if ((pMsg->hwnd == 0) || !IsWindow(pMsg->hwnd))
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

//=============================================================================	
void CXButtonXPTestDlg::OnButton1() 
//=============================================================================	
{
	TRACE(_T("in CXButtonXPTestDlg::OnButton1\n"));
	
	UpdateData(TRUE);

	CString str = _T("");
	m_edtCount1.GetWindowText(str);
	int nCount = _ttoi(str);
	if (nCount < 0)
		nCount = 0;
	nCount++;
	str.Format(_T("%d"), nCount);
	m_edtCount1.SetWindowText(str);

	if (m_bMessageBox)
		AfxMessageBox(_T("Button 1 pressed."), MB_OK|MB_ICONINFORMATION);
}

//=============================================================================	
void CXButtonXPTestDlg::OnButton2() 
//=============================================================================	
{
	TRACE(_T("in CXButtonXPTestDlg::OnButton2\n"));

	UpdateData(TRUE);

	CString str = _T("");
	m_edtCount2.GetWindowText(str);
	int nCount = _ttoi(str);
	if (nCount < 0)
		nCount = 0;
	nCount++;
	str.Format(_T("%d"), nCount);
	m_edtCount2.SetWindowText(str);

	BOOL bToggled = m_XButtonXP.GetToggleState();
	TRACE(_T("toggle state=%d\n"), bToggled);

	if (m_bMessageBox)
		AfxMessageBox(_T("Button 2 pressed."), MB_OK|MB_ICONINFORMATION);
}

//=============================================================================	
void CXButtonXPTestDlg::OnIconLeft() 
//=============================================================================	
{
	m_XButtonXP.SetWindowText(m_strButton2Title);
	m_XButtonXP.SetIcon(m_nIconId, CXButtonXP::LEFT);
}

//=============================================================================	
void CXButtonXPTestDlg::OnIconRight() 
//=============================================================================	
{
	m_XButtonXP.SetWindowText(m_strButton2Title);
	m_XButtonXP.SetIcon(m_nIconId, CXButtonXP::RIGHT);
}

//=============================================================================	
void CXButtonXPTestDlg::OnIconNo() 
//=============================================================================	
{
	m_XButtonXP.SetWindowText(m_strButton2Title);
	m_XButtonXP.SetIcon((HICON)NULL);
	OnMultiline();
}

//=============================================================================	
void CXButtonXPTestDlg::OnTextNo() 
//=============================================================================	
{
	m_XButtonXP.SetWindowText(_T(""));
	m_XButtonXP.SetIcon(m_nIconId, CXButtonXP::LEFT);
	OnMultiline();
}

//=============================================================================	
void CXButtonXPTestDlg::OnToggle() 
//=============================================================================	
{
	UpdateData(TRUE);
	m_XButtonXP.SetToggle(m_bToggle);
}

//=============================================================================	
void CXButtonXPTestDlg::OnTheme() 
//=============================================================================	
{
	UpdateData(TRUE);
	m_XButtonXP.EnableTheming(m_bTheme);
}

//=============================================================================	
void CXButtonXPTestDlg::OnToolbar() 
//=============================================================================	
{
	UpdateData(TRUE);
	m_XButtonXP.SetDrawToolbar(m_bToolbar);
}

//=============================================================================	
void CXButtonXPTestDlg::OnDisabled() 
//=============================================================================	
{
	UpdateData(TRUE);

	if (m_bDisabled)
		m_XButtonXP.ModifyStyle(0, WS_DISABLED);
	else
		m_XButtonXP.ModifyStyle(WS_DISABLED, 0);

	m_XButtonXP.RedrawWindow();
}

//=============================================================================	
void CXButtonXPTestDlg::OnMultiline() 
//=============================================================================	
{
	UpdateData(TRUE);

	if (m_bMultiLine)
	{
		m_XButtonXP.ModifyStyle(0, BS_MULTILINE);
		m_strButton2Title = _T("Button 2\nLine 2");
	}
	else
	{
		m_XButtonXP.ModifyStyle(BS_MULTILINE, 0);
		m_strButton2Title = _T("Button 2");
	}

	CString strTitle = _T("");
	m_XButtonXP.GetWindowText(strTitle);
	if (!strTitle.IsEmpty())
		m_XButtonXP.SetWindowText(m_strButton2Title);

	m_XButtonXP.RedrawWindow();
}

//=============================================================================	
void CXButtonXPTestDlg::OnDefault() 
//=============================================================================	
{
	UpdateData(TRUE);

	if (m_bDefault)
	{
		m_XButtonXP.SetDefID(this, IDC_BUTTON2);
	}
	else
	{
		m_XButtonXP.SetDefID(this, IDOK);
	}

	m_XButtonXP.RedrawWindow();
}

//=============================================================================	
void CXButtonXPTestDlg::OnPattern() 
//=============================================================================	
{
	UpdateData(TRUE);
	m_XButtonXP.SetDrawToolbar(m_bToolbar);
	RedrawWindow();
}

//=============================================================================	
void CXButtonXPTestDlg::OnSelendokIconCombo() 
//=============================================================================	
{
	UpdateData(TRUE);
	
	static UINT icons[] = { IDI_MFC16, IDI_MFC256, IDI_MFC24BPP, IDI_MFC32BPP };

	if ((m_nIconIndex < 0) || (m_nIconIndex > 3))
	{
		ASSERT(FALSE);
		m_nIconIndex = 0;
	}

	m_nIconId = icons[m_nIconIndex];

	m_XButtonXP.SetIcon(m_nIconId, CXButtonXP::LEFT);

	m_XButtonXP.RedrawWindow();
}

//=============================================================================	
void CXButtonXPTestDlg::OnOnlineHelp() 
//=============================================================================	
{
	CString strHelp = _T("");
	VERIFY(strHelp.LoadString(IDS_ONLINE_HELP));
	CXHyperLink::GotoURL(strHelp, SW_SHOW, TRUE);	
}

//=============================================================================	
void CXButtonXPTestDlg::OnColors() 
//=============================================================================	
{
	CColorDlg dlg;
	dlg.m_rgbText = m_XButtonXP.GetTextColor();
	dlg.m_rgbBackground = m_XButtonXP.GetBackgroundColor();
	if (dlg.DoModal() == IDOK)
	{
		m_XButtonXP.SetTextColor(dlg.m_rgbText)
				   .SetBackgroundColor(dlg.m_rgbBackground);
		m_XButtonXP.RedrawWindow();
	}
}
