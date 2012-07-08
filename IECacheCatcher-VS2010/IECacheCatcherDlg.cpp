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
:CResizingDialog(CIECacheCatcherDlg::IDD, pParent)
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
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIECacheCatcherDlg)
//	DDX_Control(pDX, IDC_COMBOBOX_FILETYPE, m_editFileType);
	DDX_Control(pDX, IDC_BUTTON_IEOPTION, m_btnIEOption);
	DDX_Control(pDX, IDC_LIST_RECORD, m_ListRecord);
	DDX_Control(pDX, IDC_BUTTON_OPEN_EXPORT_PATH, m_btnOpenExportPath);
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

BEGIN_MESSAGE_MAP(CIECacheCatcherDlg, CResizingDialog)
	//{{AFX_MSG_MAP(CIECacheCatcherDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_CLEARCACHE, OnButtonClearcache)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, OnButtonExport)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_EXPORT_PATH, OnButtonOpenExportPath)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RECORD, OnDblclkListRecord)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_RECORD, OnRclickListRecord)
	ON_BN_CLICKED(IDC_BUTTON_IEOPTION, OnButtonIeoption)
	//}}AFX_MSG_MAP
	ON_MESSAGE(MSG_NOTIFY_STATUS, OnNotifyStatus)
	ON_MESSAGE(MSG_NOTIFY_EXPORT_RECORD, OnNotifyExportRecord)
	ON_MESSAGE(MSG_NOTIFY_CLEARCACHE_DONE,OnNotifyClearCacheDown)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIECacheCatcherDlg message handlers

void CIECacheCatcherDlg::InitCtrl() 
{
// 	m_btnBrowse.SetCaption(_T("浏览(&B)"));
// 	m_btnBrowse.SetStyleBorder(CGuiButton::STYLEXP);
// 
// 	m_btnIEOption.SetCaption(_T("IE选项"));
// 	m_btnIEOption.SetStyleBorder(CGuiButton::STYLEXP);
// 
// 	m_btnOpenCachePath.SetCaption(_T("缓存目录"));
// 	m_btnOpenCachePath.SetStyleBorder(CGuiButton::STYLEXP);
// 
// 	m_btnClearCache.SetCaption(_T("清空缓存(&C)"));
// 	m_btnClearCache.SetStyleBorder(CGuiButton::STYLEXP);


// 	m_btnExport.SetCaption(_T("导出(&E)"));
// 	m_btnExport.SetStyleBorder(CGuiButton::STYLEXP);
// 
// 	m_btnOpenExportPath.SetCaption(_T("导出目录"));
// 	m_btnOpenExportPath.SetStyleBorder(CGuiButton::STYLEXP);

	m_ListRecord.SetHeadings(_T("文件名, 230;类型,150;网址, 220; 本地路径, 200"));
    m_ListRecord.SetFileTypeColum(1);

	SetControlInfo(IDC_STATIC_CTRL_AREA, RESIZE_HOR);

	SetControlInfo(IDC_EDIT_CACHEPATH, RESIZE_HOR);
	SetControlInfo(IDC_EDIT_URLPATH, RESIZE_HOR);
	SetControlInfo(IDC_EDIT_FILETYPE, RESIZE_HOR);
	SetControlInfo(IDC_EDIT_EXPORTPATH, RESIZE_HOR);
	SetControlInfo(IDC_STATIC_OPERCOMMENT, RESIZE_HOR);
	
	SetControlInfo(IDC_BUTTON_CLEARCACHE, ANCHORE_RIGHT);
	SetControlInfo(IDC_BUTTON_IEOPTION, ANCHORE_RIGHT);
	SetControlInfo(IDC_BUTTON_OPEN, ANCHORE_RIGHT);
	SetControlInfo(IDC_BUTTON_BROWSE, ANCHORE_RIGHT);
	SetControlInfo(IDC_BUTTON_EXPORT, ANCHORE_RIGHT);
	SetControlInfo(IDC_BUTTON_OPEN_EXPORT_PATH, ANCHORE_RIGHT);
	
	SetControlInfo(IDC_STATIC_COMMENT1, ANCHORE_RIGHT);
	SetControlInfo(IDC_STATIC_COMMENT2, ANCHORE_RIGHT);

	SetControlInfo(IDC_LIST_RECORD, RESIZE_BOTH);
	SetControlInfo(IDC_STATIC_STATUS, ANCHORE_BOTTOM | RESIZE_HOR);


	// 右下角画上调整大小的角
	DrawGripper(TRUE);
}
BOOL CIECacheCatcherDlg::OnInitDialog()
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
		
		m_editFileType.SetWindowText(_T("*.*"));
	}else
	{
		m_editUrlPath.SetWindowText(m_setting.WebSite);
		m_editExportPath.SetWindowText(m_setting.ExportPath);
		m_editFileType.SetWindowText(m_setting.Filter);
	}
	
	m_IECacheThread.SetHWnd(GetSafeHwnd());

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
		CResizingDialog::OnSysCommand(nID, lParam);
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
		CResizingDialog::OnPaint();
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
	ShellExecute(GetSafeHwnd(), NULL, Path, NULL ,NULL, SW_SHOWNORMAL );
// 	Path = _T("cmd /k explorer.exe /e,\"") + Path + _T("\"");
 //	WinExec(Path,FALSE);

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
//			m_editExportRecord.SetWindowText(_T(""));
//            m_ListRecord.clear();
			m_ListRecord.DeleteAllItems();
        

			m_nExportCount = 0;
			FilterSpliter=";";
			m_editUrlPath.GetWindowText(WebSite);
			m_editFileType.GetWindowText(Filter);
			m_editExportPath.GetWindowText(tagPath);
			

            if(WebSite.GetLength()==1 && WebSite.GetAt(0) !='*')
            {
                WebSite = '*' + WebSite + '*';
            }
            
            if(WebSite.GetLength() >1)
            {
                if(WebSite.GetAt(0) !='*')
                    WebSite = '*' + WebSite;
                if(WebSite.GetAt(WebSite.GetLength()-1) !='*')
                    WebSite = WebSite + '*';
            }
			m_IECacheThread.Export(tagPath, Filter,FilterSpliter,WebSite);

            m_btnExport.SetWindowText(_T("停止(&S)"));
			//m_btnExport.SetCaption(_T("停止(&S)"));
		}
	}else
	{
		m_btnExport.EnableWindow(FALSE);
		m_IECacheThread.Interrupt();
        m_btnExport.SetWindowText(_T("导出(&E)"));
		//m_btnExport.SetCaption(_T("导出(&E)"));
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
		if(m_nExportCount)
		{
			strCount.Format(_T("成功导出%d个文件."), m_nExportCount);
		}else
		{
			strCount = _T("没有导出任何文件.");
		}
		SetDlgItemText(IDC_STATIC_STATUS, strCount);

        m_btnExport.SetWindowText(_T("导出(&E)"));
		//m_btnExport.SetCaption(_T("导出(&E)"));
		m_bStart = TRUE;
	}
	return 0;
}

LRESULT CIECacheCatcherDlg::OnNotifyExportRecord( WPARAM wParam, LPARAM lParam )
{
	if(lParam)
	{
		CIECacheThread::LIST_DATA *pListData = (CIECacheThread::LIST_DATA *)lParam;
		m_ListRecord.AddFileItem(m_ListRecord.GetItemCount(), pListData->FileName, pListData->Website, pListData->LocalPath);
//		m_listRecord.SetColumnWidth(0,LVSCW_AUTOSIZE);
//		AppendLineToMultilineEditCtrl(m_editExportRecord, pString);
//		m_lstExportRecord.AddString(pString);
		

		if(pListData->bSuccess)
			m_nExportCount++;
		delete pListData->FileName;
		delete pListData->LocalPath;
		delete pListData->Website;
		delete pListData;
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

	m_ListRecord.clear();
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
        m_editUrlPath.SetFocus();;
        return FALSE;
    }

    static CRegexpT <TCHAR> regexpFilter(_T("([*][.]([\\w]+|[*])[;]*)+"));

    MatchResult result = regexpFilter.MatchExact(filter);

    if(!result.IsMatched())
    {
        SetDlgItemText(IDC_STATIC_STATUS, _T("请填写正确的文件类型!"));
        m_editFileType.SetFocus();
        return FALSE;
    }

    if(!path.IsEmpty())
    {
        if(path.GetAt(path.GetLength()-1) == '\\')
        {
            path = path.Mid(0,path.GetLength()-1);
        }
    }
    static CRegexpT <TCHAR> regexpPath(_T("[a-zA-Z]:([\\\\][$]*[\\w]+)*"));
    result = regexpPath.MatchExact(path);
    if(!result.IsMatched())
    {
        SetDlgItemText(IDC_STATIC_STATUS, _T("请填写正确的导出路径!"));
        m_editExportPath.SetFocus();
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
	ShellExecute(GetSafeHwnd(), NULL, Path, NULL ,NULL, SW_SHOWNORMAL );
// 	Path = _T("cmd /k explorer.exe /e,\"") + Path + _T("\"");
// 	WinExec(Path,FALSE);
}

LRESULT CIECacheCatcherDlg::OnNotifyClearCacheDown( WPARAM wParam, LPARAM lParam )
{
	SetDlgItemText(IDC_STATIC_STATUS, _T("清空缓存成功."));
	m_btnClearCache.EnableWindow(TRUE);
	return 0;
}

HBRUSH CIECacheCatcherDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CResizingDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    if (nCtlColor==CTLCOLOR_STATIC) 
    { 
		UINT CtrlID = pWnd-> GetDlgCtrlID();
        if(CtrlID==IDC_STATIC_STATUS)
        {
            pDC-> SetTextColor(RGB(250,0,0));
        }

		if(CtrlID==IDC_STATIC_OPERCOMMENT || CtrlID==IDC_STATIC_COMMENT1 || CtrlID==IDC_STATIC_COMMENT2)
        {
            pDC-> SetTextColor(RGB(100,100,200));
        }
    } 
	return hbr;
}



void CIECacheCatcherDlg::OnDblclkListRecord(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int iPos = m_ListRecord.GetNextItem( -1, LVNI_ALL | LVNI_SELECTED);
	if(iPos != -1)
	{
		CString filepath = m_ListRecord.GetItemText(iPos, 3);
		ShellExecute(GetSafeHwnd(), _T("open"), filepath, NULL ,NULL, SW_SHOW );
	}
	*pResult = 0;
}

void CIECacheCatcherDlg::OnRclickListRecord(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int iPos = m_ListRecord.GetNextItem( -1, LVNI_ALL | LVNI_SELECTED);
	if(iPos != -1)
	{
		CString name = m_ListRecord.GetItemText(iPos, 0);
		CString url = m_ListRecord.GetItemText(iPos, 2);
		CString successMark = "成功";
		CString format(_T("复制[%s]的网址到剪贴板%s."));
		CString tip;
		
		if(!SysUtil::SetClipBoardText(url, NULL))
		{
			successMark = _T("失败");
		}
		tip.Format(format, name, successMark);
		SetDlgItemText(IDC_STATIC_STATUS, tip);
	}
	
	*pResult = 0;
}

void CIECacheCatcherDlg::OnButtonIeoption() 
{
	//WinExec(_T("cmd /k \"%windir%\\System32\\rundll32.exe Shell32.dll,Control_RunDLL \"%windir%\\System32\\inetcpl.cpl\"\""), SW_HIDE);
	//WinExec(_T("%windir%\\System32\\rundll32.exe Shell32.dll,Control_RunDLL \"%windir%\\System32\\inetcpl.cpl\""), SW_SHOWNORMAL);
// 	CString filepath = _T("cmd /k rundll32.exe Shell32.dll,Control_RunDLL \"%windir%\\System32\\inetcpl.cpl\"");
// 	WinExec(filepath , SW_HIDE);

	TCHAR SysDir[MAX_PATH];
	GetSystemDirectory(SysDir, MAX_PATH);
	CString filepath = _T("%s\\rundll32.exe");

	CString parameter;
	SHELLEXECUTEINFO ShellInfo;
	CString cmdLine;

	cmdLine.Format(filepath, SysDir);
	parameter.Format(_T("Shell32.dll,Control_RunDLL \"%s\\inetcpl.cpl\""), SysDir);

	memset(&ShellInfo, 0, sizeof(ShellInfo));
	ShellInfo.cbSize = sizeof(ShellInfo);
	ShellInfo.hwnd = NULL;
	//ShellInfo.lpVerb = _T("open");
	ShellInfo.lpFile = cmdLine;
	ShellInfo.lpParameters = parameter;
	ShellInfo.nShow = SW_SHOWNORMAL;
    ShellInfo.fMask = SEE_MASK_NOCLOSEPROCESS;

	ShellExecuteEx(&ShellInfo);
}
