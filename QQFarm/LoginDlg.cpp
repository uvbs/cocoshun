// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QQFarm.h"
#include "LoginDlg.h"
#include <afxinet.h>
#include "Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define QQNC_IMAGE_URL "http://ptlogin2.qq.com/getimage?aid=353&0."
/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
: CDialog(CLoginDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CLoginDlg)
    // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    m_pPic = NULL;
}
CLoginDlg::~CLoginDlg()
{
	if(m_pPic) m_pPic->Release(); // 释放 IPicture 指针  
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CLoginDlg)
    // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
//{{AFX_MSG_MAP(CLoginDlg)
ON_BN_CLICKED(ID_Login, Login)
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_EDIT_QQNUMBER, OnKillfocusEditQQnumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnOK() 
{
    // TODO: Add extra validation here
    
    CDialog::OnOK();
}

BOOL CLoginDlg::Login()
{
    return FALSE;
}

BOOL CLoginDlg::InitPic() 
{
    IStream* pStm = NULL;  
    CString strTmp;
    CString strUrl = QQNC_IMAGE_URL;
    for(int i = 0 ; i < 16 ; i++)
    {
        strTmp.Format("%d",rand()%10);
        strUrl += strTmp;
    }
    
    DWORD dwLen = 0;
    
    CInternetSession m_InetSession(_T("session"),0,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,INTERNET_FLAG_DONT_CACHE); //设置不缓冲
    CHttpFile* pFile = NULL;
    try
    {
        pFile = (CHttpFile*)m_InetSession.OpenURL(strUrl);
        
        //获取图片大小
        pFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, dwLen); 
        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwLen);         
        LPVOID pvData = NULL;          
        if (hGlobal != NULL)         
        {             
            pvData = GlobalLock(hGlobal);             
            if (pvData != NULL)            
            {
                pFile->Read(pvData,dwLen);
                GlobalUnlock(hGlobal);
                
                if(pStm) pStm->Release(); // 释放 IStream 指针
                CreateStreamOnHGlobal(hGlobal, TRUE, &pStm);      
            }      
        }  
        if(pFile)  delete pFile;
    }
    catch(CInternetException* e)
    {
        e->m_dwContext;
        return FALSE;
    }
    
    //
    if(m_pPic) m_pPic->Release(); // 释放 IPicture 指针
    if(pStm && SUCCEEDED(OleLoadPicture(pStm, dwLen, TRUE,IID_IPicture, (LPVOID*)&m_pPic)))    
    {     
        m_pPic->get_Width(&m_nPicWidth);	// 宽  
        m_pPic->get_Height(&m_nPicHeight);	// 高  
        
        m_Size = CSize(m_nPicWidth, m_nPicHeight);  
        CDC* pDC = GetDC();
        pDC->HIMETRICtoDP(&m_Size);	 // 转换 MM_HIMETRIC 模式单位为 MM_TEXT 像素单位  
    }    
    
    return TRUE;	
}

void CLoginDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

    CRect rect;
    GetWindowRect(rect);
    int x =  rect.Width()/2 - m_Size.cx/2;
    int y =  rect.Height() - m_Size.cy - 70;
	
    if(m_pPic)
    {
       m_pPic->Render(dc.m_hDC, x , y, m_Size.cx, m_Size.cy, 0, m_nPicHeight, m_nPicWidth, -m_nPicHeight, NULL);
    }
}


BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CUtil util;
	//CString str = util.md5_3("1150403514!B5J");
	CString str = util.md5_3("123123");
	str = util.md5(str + "XMFXN");
	MessageBox(str);
	
    InitPic();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnKillfocusEditQQnumber() 
{
	CInternetSession m_InetSession(_T("session"),0,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,INTERNET_FLAG_DONT_CACHE); //设置不缓冲
    CHttpFile* pFile = NULL;
    IStream* pStm = NULL;  
	DWORD dwLen = 0;
	CString strUrlTemplate = _T("http://ptlogin2.qq.com/check?uin=%s&appid=15000101&r=0.5529257158294194");
	UpdateData(FALSE);
	CString qNum;
	GetDlgItem(IDC_EDIT_QQNUMBER)->GetWindowText(qNum);
	CString strUrl;
	strUrl.Format(strUrlTemplate,qNum);
    try
    {
        pFile = (CHttpFile*)m_InetSession.OpenURL(strUrl);
        
        pFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, dwLen); 
		CString content;
		pFile->ReadString(content);
		MessageBox(content);

        if(pFile)  delete pFile;
    }
    catch(CInternetException* e)
    {
        e->m_dwContext;
    }
}
