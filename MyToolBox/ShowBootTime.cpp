// ShowBootTime.cpp : implementation file
//

#include "stdafx.h"
#include "MyToolBox.h"
#include "ShowBootTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowBootTime dialog


CShowBootTime::CShowBootTime(CWnd* pParent /*=NULL*/)
	: CDialog(CShowBootTime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowBootTime)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_Font.CreateFont(25, 0, 0, 0, 
        FW_BLACK, FALSE, FALSE, 0, 
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        PROOF_QUALITY,
        DEFAULT_PITCH,
		_T("黑体"));
}


void CShowBootTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowBootTime)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowBootTime, CDialog)
	//{{AFX_MSG_MAP(CShowBootTime)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CShowBootTime::~CShowBootTime()
{
    m_Font.DeleteObject();
}
/////////////////////////////////////////////////////////////////////////////
// CShowBootTime message handlers

HBRUSH CShowBootTime::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    if (nCtlColor==CTLCOLOR_STATIC) 
    { 
        if(pWnd-> GetDlgCtrlID()==IDC_STATIC_SHOWTIP)
        {
            pDC-> SetTextColor(RGB(0,255,0));
        }
    } 	
	return hbr;
}

void CShowBootTime::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
    CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_SHOWTIP);
    pStatic->SetFont(&m_Font,FALSE);
    pStatic->SetWindowText(m_strTip);
}

BOOL CShowBootTime::OnInitDialog() 
{
	CDialog::OnInitDialog();

    //获取系统运行时间
    DWORD nCount=GetTickCount();
    CString str,str1;
//     str1.Format(_T("系统已运行 %d时"),nCount/3600000);
//     str=str1;
    nCount%=3600000;
    str1.Format(_T("本次开机时间:%2d分"),nCount/60000);
    str+=str1;
    nCount%=60000;
    str1.Format(_T("%2d秒"),nCount/1000);
    str+=str1;
    m_strTip = str;
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
