// IECacheCatcherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IECacheCatcher.h"
#include "IECacheCatcherDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define MAX_LOGLINE 100000
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
// CIECacheCatcherDlg dialog

CIECacheCatcherDlg::CIECacheCatcherDlg(CWnd* pParent /*=NULL*/)
:CDialog(CIECacheCatcherDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIECacheCatcherDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nLineNum = 0;
	m_bStart = TRUE;
}

void CIECacheCatcherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIECacheCatcherDlg)
	DDX_Control(pDX, IDC_BUTTON_OPEN_EXPORT_PATH, m_btnOpenExportPath);
	DDX_Control(pDX, IDC_EDIT_EXPORT_RECORD, m_editExportRecord);
	DDX_Control(pDX, IDC_BUTTON_OPENCACHEPATH, m_btnOpenCachePath);
	DDX_Control(pDX, IDC_BUTTON_EXPORT, m_btnExport);
	DDX_Control(pDX, IDC_BUTTON_CLEARCACHE, m_btnClearCache);
	DDX_Control(pDX, IDC_BUTTON_BROWSE, m_btnBrowse);
	DDX_Control(pDX, IDC_EDIT_URLPATH, m_editUrlPath);
	DDX_Control(pDX, IDC_EDIT_FILETYPE, m_editFileType);
	DDX_Control(pDX, IDC_EDIT_EXPORTPATH, m_editExportPath);
	DDX_Control(pDX, IDC_EDIT_CACHEPATH, m_editCachePath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIECacheCatcherDlg, CDialog)
	//{{AFX_MSG_MAP(CIECacheCatcherDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_CLEARCACHE, OnButtonClearcache)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, OnButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_EXPORT_PATH, OnButtonOpenExportPath)
	//}}AFX_MSG_MAP
	ON_MESSAGE(MSG_NOTIFY_STATUS, OnNotifyStatus)
	ON_MESSAGE(MSG_NOTIFY_EXPORT_RECORD, OnNotifyExportRecord)
	ON_MESSAGE(MSG_NOTIFY_CLEARCACHE_DONE,OnNotifyClearCacheDown)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIECacheCatcherDlg message handlers

void CIECacheCatcherDlg::InitCtrl() 
{
	m_btnBrowse.SetCaption(_T("浏览(&B)"));
	m_btnBrowse.SetStyleBorder(CGuiButton::STYLEXP);
	m_btnOpenCachePath.SetCaption(_T("打开(&O)"));
	m_btnOpenCachePath.SetStyleBorder(CGuiButton::STYLEXP);
	m_btnClearCache.SetCaption(_T("清空(&C)"));
	m_btnClearCache.SetStyleBorder(CGuiButton::STYLEXP);
	m_btnExport.SetCaption(_T("导出(&E)"));
	m_btnExport.SetStyleBorder(CGuiButton::STYLEXP);

	m_btnOpenExportPath.SetCaption(_T("打开导出目录(&X)"));
	m_btnOpenExportPath.SetStyleBorder(CGuiButton::STYLEXP);

// 	m_editFileType.SetWindowText(_T("*.mp3"));
// 	m_editUrlPath.SetWindowText(_T(""));
// 	m_editExportPath.SetWindowText(_T(""));
}
BOOL CIECacheCatcherDlg::OnInitDialog()
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
	
	InitCtrl();

	RetreveIECacheDirectory();

	if(!SysUtil::ReadSetting(&m_setting))
	{
		TCHAR szPath[MAX_PATH];
		LPITEMIDLIST ppidl = NULL; 
		if (SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &ppidl) == S_OK) // 获得系统特殊路径 
		{  
			BOOL flag = SHGetPathFromIDList(ppidl,      // 根指定一个文档或目录地点的一张项目标识符表的地址
				szPath);                                             // 接收文档系统路径的缓冲地址，大小至少是MAX_PATH
			if(flag)
				m_editExportPath.SetWindowText(szPath);
			CoTaskMemFree(ppidl);  
		}
		
		m_editFileType.SetWindowText(_T("*.mp3"));

// 		_tcscpy(m_setting.address, _T("61.128.128.68"));
// 		_tcscpy(m_setting.measure, _T("50"));
	}else
	{
		m_editUrlPath.SetWindowText(m_setting.WebSite);
		m_editExportPath.SetWindowText(m_setting.ExportPath);
		m_editFileType.SetWindowText(m_setting.Filter);
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIECacheCatcherDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIECacheCatcherDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIECacheCatcherDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIECacheCatcherDlg::RetreveIECacheDirectory()
{
	// //清internet临时文件
    TCHAR szPath[MAX_PATH];
    ::SHGetSpecialFolderPath(NULL, szPath, CSIDL_INTERNET_CACHE,FALSE);
	m_editCachePath.SetWindowText(szPath);
}

void CIECacheCatcherDlg::OnButtonOpen() 
{
	CString Path;
	m_editCachePath.GetWindowText(Path);
	Path = _T("cmd /k explorer.exe /e,\"") + Path + _T("\"");
	WinExec(Path,FALSE);
}

void CIECacheCatcherDlg::OnButtonBrowse() 
{
	CString defaultPath;
	m_editExportPath.GetWindowText(defaultPath);
	
	defaultPath = CShellUtil::BrowseFolder(GetSafeHwnd(), defaultPath);

	if(!defaultPath.IsEmpty())
		m_editExportPath.SetWindowText(defaultPath);
}

void CIECacheCatcherDlg::OnButtonClearcache() 
{
	SetDlgItemText(IDC_STATIC_STATUS, _T("清空IE缓存..."));
	m_IECacheThread.ClearCache();
	m_btnClearCache.EnableWindow(FALSE);
	
// 	CIECache cache;
// 	cache.ClearInternetTemp();
}

void CIECacheCatcherDlg::OnButtonExport() 
{
	if(m_bStart)
	{
		if(IsValidParam())
		{
			m_bStart = FALSE;
			m_editExportRecord.SetWindowText(_T(""));
			m_nExportCount = 0;
			FilterSpliter=";";
			m_editUrlPath.GetWindowText(WebSite);
			m_editFileType.GetWindowText(Filter);
			m_editExportPath.GetWindowText(tagPath);
			
			m_IECacheThread.Export(GetSafeHwnd(), tagPath, Filter,FilterSpliter,WebSite);

			m_btnExport.SetCaption(_T("停止(&S)"));
		}
	}else
	{
		m_btnExport.EnableWindow(FALSE);
		m_IECacheThread.Interrupt();
		m_btnExport.SetCaption(_T("导出(&E)"));
		m_btnExport.EnableWindow(TRUE);
	}

}

LRESULT CIECacheCatcherDlg::OnNotifyStatus( WPARAM wParam, LPARAM lParam )
{
	if(wParam)
	{
		TCHAR msg[MAX_PATH+1];
		LoadString(NULL,wParam,msg, MAX_PATH);
		SetDlgItemText(IDC_STATIC_STATUS, msg);
	}else
	{
		CString strCount;
		strCount.Format(_T("成功导出%d个文件."), m_nExportCount);
		SetDlgItemText(IDC_STATIC_STATUS, strCount);
		m_btnExport.SetCaption(_T("导出(&E)"));
		m_bStart = TRUE;
	}
	return 0;
}

LRESULT CIECacheCatcherDlg::OnNotifyExportRecord( WPARAM wParam, LPARAM lParam )
{
	if(lParam)
	{
		char *pString = (char *)lParam;
		AppendLineToMultilineEditCtrl(m_editExportRecord, pString);
//		m_lstExportRecord.AddString(pString);
		delete pString;
		m_nExportCount++;
	}
	return 0;
}

void CIECacheCatcherDlg::AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText)
{
	// get the initial text length
	int nLength = edit.GetWindowTextLength();
	// put the selection at the end of text
	edit.SetSel(nLength, nLength);
	// replace the selection
	edit.ReplaceSel(pszText);
}

void CIECacheCatcherDlg::AppendLineToMultilineEditCtrl(CEdit& edit, LPCTSTR pszText)
{
	if(m_nLineNum >= MAX_LOGLINE)
	{
		m_nLineNum = 0;
		edit.SetWindowText(_T(""));
	}
	
	CString strLine;
	// add CR/LF to text
	strLine.Format(_T("%s\r\n"),pszText);
	AppendTextToEditCtrl(edit, strLine);
	m_nLineNum++;
}



void CIECacheCatcherDlg::OnCancel() 
{
	UpdateData(FALSE);
	CString strValue;
	
	m_editUrlPath.GetWindowText(strValue);
	_tcscpy(m_setting.WebSite, strValue);
	
	m_editFileType.GetWindowText(strValue);
	_tcscpy(m_setting.Filter, strValue);

	m_editExportPath.GetWindowText(strValue);
	_tcscpy(m_setting.ExportPath, strValue);

	SysUtil::WriteSetting(&m_setting);

	m_IECacheThread.Interrupt();
	CDialog::OnCancel();
}

BOOL CIECacheCatcherDlg::IsValidParam()
{
	CString filter;
	CString path;
	CString WebSite;
	m_editUrlPath.GetWindowText(WebSite);
	m_editFileType.GetWindowText(filter);
	m_editExportPath.GetWindowText(path);


	if(WebSite.IsEmpty())
	{
		SetDlgItemText(IDC_STATIC_STATUS, _T("请填写正确的网址!"));
		return FALSE;
	}

	static CRegexpT <char> regexpFilter("([*][.]([\\w]+|[*])[;]*)+");
	
    MatchResult result = regexpFilter.MatchExact(filter);
	if(!result.IsMatched())
	{
		SetDlgItemText(IDC_STATIC_STATUS, _T("请填写正确的文件类型!"));
		//MessageBox(_T("请填写正确的文件类型!"), _T("提示"), MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}

	static CRegexpT <char> regexpPath("[a-zA-Z]:([\\\\][$]*[\\w]+)*");
    result = regexpPath.MatchExact(path);
	if(!result.IsMatched())
	{
		//MessageBox(_T("请填写正确的导出路径!"), _T("提示"), MB_OK|MB_ICONINFORMATION);
		SetDlgItemText(IDC_STATIC_STATUS, _T("请填写正确的导出路径!"));
		return FALSE;
	}

	return TRUE;
}

void CIECacheCatcherDlg::OnButtonOpenExportPath() 
{
	CString Path;
	m_editExportPath.GetWindowText(Path);
	if(Path.IsEmpty())
		return ;
	
	Path = _T("cmd /k explorer.exe /e,\"") + Path + _T("\"");
	WinExec(Path,FALSE);
}

LRESULT CIECacheCatcherDlg::OnNotifyClearCacheDown( WPARAM wParam, LPARAM lParam )
{
	SetDlgItemText(IDC_STATIC_STATUS, _T("清空缓存成功."));
	m_btnClearCache.EnableWindow(TRUE);
	return 0;
}