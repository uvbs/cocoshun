// BodyWeightDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BodyWeight.h"
#include "BodyWeightDlg.h"

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
// CBodyWeightDlg dialog

CBodyWeightDlg::CBodyWeightDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBodyWeightDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBodyWeightDlg)
	m_nSex = -1;
	m_stResult = _T("");
	m_etTail = 0;
	m_etWeight = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBodyWeightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBodyWeightDlg)
	DDX_CBIndex(pDX, IDC_COMBO_SEX, m_nSex);
	DDX_Text(pDX, IDC_STATIC_RESULT, m_stResult);
	DDX_Text(pDX, IDC_EDIT_TAIL, m_etTail);
	DDX_Text(pDX, IDC_EDIT_WEIGHT, m_etWeight);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBodyWeightDlg, CDialog)
	//{{AFX_MSG_MAP(CBodyWeightDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_CAL, OnCal)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBodyWeightDlg message handlers

BOOL CBodyWeightDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
    m_nSex=0;
    m_etTail = 173;
    m_etWeight = 70;
    UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBodyWeightDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBodyWeightDlg::OnPaint() 
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
HCURSOR CBodyWeightDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBodyWeightDlg::OnCal() 
{
    UpdateData(TRUE);

    //体重指数
    double hv = (float)m_etTail/100.0;
    double BMI = m_etWeight / (hv * hv);

    if(BMI<0)
    {
        MessageBox("请输入完整的参数","提示",MB_ICONINFORMATION);
        return;
    }

    int ideal_weight;

    if(m_nSex == 0){
        //男
        ideal_weight = (int) (50+(2.3*(m_etTail-152))/2.54);
    }else{
        //女
        ideal_weight = (int) (45.5+(2.3*(m_etTail-152))/2.54);
    }
    
    //中国标准
    if (BMI >= 40) {
        ShowResult(_T("Ⅲ度肥胖"),_T("非常严重增加"),BMI,ideal_weight);
    }
    else if (BMI >= 30 && BMI < 40) {
        ShowResult(_T("II度肥胖"),_T("严重增加"),BMI,ideal_weight);
    }
    else if (BMI >27 && BMI <= 29.9) {
        ShowResult(_T("I度肥胖"),_T("中度增加"),BMI,ideal_weight);
    }
    else if (BMI >= 24) {
        ShowResult(_T("肥胖前期"),_T("增加"),BMI,ideal_weight);
    }
    else if (BMI >= 18.5 && BMI <= 23.9) {
        ShowResult(_T("正常范围"),_T("平均水平"),BMI,ideal_weight);
    }
    else{
        ShowResult(_T("体重过低"),_T("低，但其它疾病危险性增加"),BMI,ideal_weight);
    }

}

void CBodyWeightDlg::ShowResult( CString c_level,CString c_stat,double c_bmi,double c_weight )
{
    CString result;
    result.Format(_T("BMI指数:%.1f\n\n%s,相关疾病发病的危险性处于:%s\n\n标准体重应为:%.1f"), c_bmi, c_level, c_stat,c_weight);
    m_stResult = result;
    UpdateData(FALSE);
}

HBRUSH CBodyWeightDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    if (nCtlColor==CTLCOLOR_STATIC) 
    { 
        if(pWnd-> GetDlgCtrlID()==IDC_STATIC_RESULT)
        {
            pDC-> SetTextColor(RGB(255,0,0));
        }
    } 
	return hbr;
}
