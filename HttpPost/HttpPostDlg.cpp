// HttpPostDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HttpPost.h"
#include "HttpPostDlg.h"
#include <afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHttpPostDlg dialog

CHttpPostDlg::CHttpPostDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHttpPostDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHttpPostDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHttpPostDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHttpPostDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHttpPostDlg, CDialog)
	//{{AFX_MSG_MAP(CHttpPostDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SENDPOST, OnBtnSendpost)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHttpPostDlg message handlers

BOOL CHttpPostDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHttpPostDlg::OnPaint() 
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
HCURSOR CHttpPostDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHttpPostDlg::OnBtnSendpost() 
{
	CInternetSession m_InetSession(_T("session"),
		0,
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		INTERNET_FLAG_DONT_CACHE);     //设置不缓冲
	CHttpConnection* pServer = NULL;
	CHttpFile* pFile = NULL;
	CString strHtml = "";
	CString ActionServer = _T("www.cqjg.gov.cn");
	CString strRequest = _T("LicenseTxt=AG8091&VIN=LJDAAA21560205432"); //POST过去的数据
	CString strHeaders = "Accept: text*/*\r\nContent-Type: application/x-www-form-urlencoded\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; Maxthon;";
	int nRead = 0;
	try
	{
		INTERNET_PORT nPort = 80; //端口
		pServer = m_InetSession.GetHttpConnection(ActionServer, nPort);
		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST,"/netcar/FindOne.aspx");
		pFile->AddRequestHeaders(strHeaders);
		pFile->SendRequestEx(strRequest.GetLength());
		pFile->WriteString(strRequest); //重要-->m_Request 中有"name=aaa&name2=BBB&..."
		pFile->EndRequest();
		DWORD dwRet;
		pFile->QueryInfoStatusCode(dwRet);
		if (dwRet == HTTP_STATUS_OK)
		{
			CString strLine;
			while ((nRead = pFile->ReadString(strLine))>0)
			{
				strHtml += strLine + "\n";;
			}
		}

		int pos = strHtml.Find(_T("<li class=\"lithreeC\">"));
		if(pos != -1)
		{
			CString Value = strHtml.Mid(pos,500);
			CFile file("test.html",CFile::modeCreate|CFile::modeWrite);
			file.WriteHuge(Value.GetBuffer(0),Value.GetLength());
			file.Close();
			//MessageBox(Value);
		}
		delete pFile;
		delete pServer;
	}
	catch (CInternetException* e)
	{
		char strErrorBuf[255];
		e->GetErrorMessage(strErrorBuf,255,NULL);
		AfxMessageBox(strErrorBuf,MB_ICONINFORMATION);
	}
//	SendPost();
}


