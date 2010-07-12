// ksc2kmcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ksc2kmc.h"
#include "ksc2kmcDlg.h"
#include "ShellUtil.h"
#include "KscToKmc.h"
#include <direct.h>
#include <mmsystem.h>

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
// CKsc2kmcDlg dialog

CKsc2kmcDlg::CKsc2kmcDlg(CWnd* pParent /*=NULL*/)
: CDialog(CKsc2kmcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKsc2kmcDlg)
	m_srcPath = _T("");
	m_tagPath = _T("");
	m_StaticStatus = _T("");
	m_Author = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bProcess = FALSE;
	m_bClose   = FALSE;
}

void CKsc2kmcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKsc2kmcDlg)
	DDX_Control(pDX, IDC_EDIT_SOURCE, m_EditSrc);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, ID_BTN_STOP, m_BtnStop);
	DDX_Control(pDX, IDCANCEL, m_BtnCancel);
	DDX_Control(pDX, ID_BTN_SEARCH, m_BtnSearch);
	DDX_Text(pDX, IDC_EDIT_SOURCE, m_srcPath);
	DDX_Text(pDX, IDC_EDIT_TARGET, m_tagPath);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_StaticStatus);
	DDX_Text(pDX, IDC_EDIT_AUTHOR, m_Author);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKsc2kmcDlg, CDialog)
//{{AFX_MSG_MAP(CKsc2kmcDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON_BROWSE_SRC, OnButtonBrowseSrc)
ON_BN_CLICKED(IDC_BUTTON_BROWSE_TAG, OnButtonBrowseTag)
	ON_BN_CLICKED(ID_BTN_SEARCH, OnBtnSearch)
	ON_BN_CLICKED(ID_BTN_STOP, OnBtnStop)
	ON_REGISTERED_MESSAGE(WM_MYUPDATEDATA,OnUpdateMyData)
	ON_BN_CLICKED(IDC_STATIC_ICON, OnStaticIcon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKsc2kmcDlg message handlers

BOOL CKsc2kmcDlg::OnInitDialog()
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
	
	((CButton*)GetDlgItem(IDC_RADIO_KMC))->SetCheck(true);
	// TODO: Add extra initialization here
	
	m_BtnStop.EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKsc2kmcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKsc2kmcDlg::OnPaint() 
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
HCURSOR CKsc2kmcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKsc2kmcDlg::OnButtonBrowseSrc() 
{
	m_srcPath = CShellUtil::BrowseFolder(m_hWnd);
	if(!m_srcPath.IsEmpty())
	{
		if(m_srcPath.GetAt(m_srcPath.GetLength()-1) != '\\')
		{
			m_srcPath += '\\';
		}
		m_tagPath = m_srcPath + "kmc";
		UpdateData(FALSE);
	}
}

void CKsc2kmcDlg::OnButtonBrowseTag() 
{
	m_tagPath = CShellUtil::BrowseFolder(m_hWnd);
	if(!m_tagPath.IsEmpty())
		UpdateData(FALSE);
}

void CKsc2kmcDlg::OnBtnSearch() 
{
	UpdateData(TRUE);
	if(m_srcPath.IsEmpty() || m_tagPath.IsEmpty())
		return;

	m_bProcess = TRUE;
	m_bClose   = FALSE;
	m_BtnSearch.EnableWindow(FALSE);
	//m_BtnCancel.EnableWindow(FALSE);
	m_BtnStop.EnableWindow(TRUE);

	HANDLE handle =::CreateThread(NULL,0,ConvertProc,(LPVOID)this,0,NULL);
// 	WaitForSingleObject(handle,INFINITE);
// 	m_BtnSearch.EnableWindow(TRUE);
// 	m_BtnCancel.EnableWindow(TRUE);
// 	m_BtnStop.EnableWindow(FALSE);
// 	m_bProcess = FALSE;
	CloseHandle(handle);
}

DWORD WINAPI CKsc2kmcDlg::ConvertProc(LPVOID lpParameter)
{
	CKsc2kmcDlg *pDlg = (CKsc2kmcDlg *)lpParameter;
	BOOL bKmc = ((CButton*)pDlg->GetDlgItem(IDC_RADIO_KMC))->GetCheck();

	pDlg->m_fileFinder.StopSearch();
	pDlg->m_fileFinder.RemoveAll();
	
	CFileFinder::CFindOpts	opts;
	opts.sBaseFolder = pDlg->m_srcPath;
	opts.sFileMask.Format("*%s*", "*.ksc");
	opts.bSubfolders = TRUE;
	opts.FindAllFiles();
	
	pDlg->m_fileFinder.Find(opts);
	int FileCount = pDlg->m_fileFinder.GetFileCount();

	if(FileCount > 0)
		::mkdir(pDlg->m_tagPath);

	pDlg->m_Progress.SetRange(0,100);

	CKscToKmc converter(pDlg->m_Author);
	DWORD StartTime = timeGetTime();
	CString Percent;

	int i = 0;
	short pos = 0;
	for(i=0;i<FileCount && pDlg->m_bProcess && !pDlg->m_bClose;i++)
	{
		CPath path = pDlg->m_fileFinder.GetFilePath(i);

		if(path.IsLocalPath())
		{
			CString p = path.GetFileName();
		}

		CString srcFile = path.GetPath();
		CString tagFile = path.GetFileName();
		tagFile = tagFile.Mid(0,tagFile.GetLength()-3);
		if(bKmc)
		{
			tagFile = pDlg->m_tagPath + "\\" + tagFile + "kmc";
		}else
		{
			tagFile = pDlg->m_tagPath + "\\" + tagFile + "xml";
		}

		//start convert
		converter.convert(srcFile,tagFile);

		pos = (short)(( (i+1) /1.0 / FileCount) * 100);

		pDlg->m_Progress.SetPos(pos);
		Percent.Format("%d/%d  %d%% ", i+1, FileCount,pos);
		pDlg->m_Progress.SetWindowText(Percent);

		//set convert status
		DWORD UsedTime = timeGetTime() - StartTime;
		pDlg->m_StaticStatus.Format("%dºÁÃë", UsedTime);
		pDlg->SendMessage(WM_MYUPDATEDATA,FALSE);
	}

	if( i < FileCount)
	{
		Percent.Format("%d/%d  %d%% Í£Ö¹", i+1 , FileCount,pos);
		pDlg->m_Progress.SetWindowText(Percent);
	}else
	{
		Percent.Format("%d/%d  %d%% Íê³É", i, FileCount,pos);
		pDlg->m_Progress.SetWindowText(Percent);
	}

 	pDlg->m_BtnSearch.EnableWindow(TRUE);
 	pDlg->m_BtnStop.EnableWindow(FALSE);
 	pDlg->m_bProcess = FALSE;

	if( ((CButton*)pDlg->GetDlgItem(IDC_CHECK_OPENTAG))->GetCheck())
	{
		WinExec("explorer ,/e, " + pDlg->m_tagPath,SW_SHOW);
	}

	if(pDlg->m_bClose)
		pDlg->OnCancel();
	return 0;
}

void CKsc2kmcDlg::OnBtnStop() 
{
	m_bProcess = FALSE;	
}

void CKsc2kmcDlg::OnCancel() 
{
	m_bClose = TRUE;	

	if(m_BtnSearch.IsWindowEnabled())	
		CDialog::OnCancel();
}


void CKsc2kmcDlg::OnUpdateMyData(WPARAM wp,LPARAM lp)
{
    UpdateData(wp);
}

void CKsc2kmcDlg::OnStaticIcon() 
{
	MessageBox("x")	;
}
