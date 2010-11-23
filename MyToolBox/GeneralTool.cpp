// GeneralTool.cpp : implementation file
//

#include "stdafx.h"
#include "MyToolBox.h"
#include "GeneralTool.h"
#include "Util/SysUtil.h"
#include "Util/Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GeneralTool dialog

CString GeneralTool::m_maskADContent[]=
{
_T("\r\n#屏蔽优酷广告：\r\n\
0.0.0.0 vid.atm.youku.com\r\n\
0.0.0.0 valo.atm.youku.com\r\n\
0.0.0.0 valf.atm.youku.com\r\n\
0.0.0.0 walp.atm.youku.com\r\n\
0.0.0.0 static.atm.youku.com\r\n\
0.0.0.0 valb.atm.youku.com\r\n\r\n"),
_T("\r\n#屏蔽土豆广告：\r\n\
0.0.0.0 adcontorl.tudou.com\r\n\r\n"),
_T("\r\n#屏蔽迅雷看看广告：\r\n\
0.0.0.0 mcfg.sandai.net\r\n\
0.0.0.0 biz5.sandai.net\r\n\
0.0.0.0 server1.adpolestar.net\r\n\
0.0.0.0 advstat.xunlei.com\r\n\
0.0.0.0 mpv.sandai.net\r\n\r\n"),
_T("\r\n#屏蔽其他广告：\r\n\
0.0.0.0 googlesyndication.com\r\n\
0.0.0.0 pagead2.googlesyndication.com\r\n\
0.0.0.0 doubleclick.net\r\n\
0.0.0.0 union.baidu.com\r\n\
0.0.0.0 googleads.g.doubleclick.net\r\n\
0.0.0.0 cpro.baidu.com\r\n\
0.0.0.0 biz5.sandai.net\r\n\r\n"),
_T("\r\n#屏蔽酷6广告：\r\n\
0.0.0.0 ad-apac.doubleclick.net\r\n\
0.0.0.0 st.vq.ku6.cn\r\n\
0.0.0.0 ku6afp.allyes.com\r\n\r\n"),
};

GeneralTool::GeneralTool(CWnd* pParent /*=NULL*/)
	: CResizingDialog(GeneralTool::IDD, pParent)
{
	//{{AFX_DATA_INIT(GeneralTool)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void GeneralTool::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GeneralTool)
	DDX_Control(pDX, IDC_BTN_REBULID_ICON_CACHE, m_BtnRebulidIconCache);
	DDX_Control(pDX, IDC_BTN_RESTART_EXPLORER, m_BtnRestartExplorer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GeneralTool, CResizingDialog)
	//{{AFX_MSG_MAP(GeneralTool)
	ON_BN_CLICKED(IDC_BTN_REBULID_ICON_CACHE, OnBtnRebulidIconCache)
	ON_BN_CLICKED(IDC_BTN_RESTART_EXPLORER, OnBtnRestartExplorer)
	ON_BN_CLICKED(IDC_CHECK_SHOWBOOTTIME, OnCheckShowboottime)
	ON_BN_CLICKED(IDC_BUTTON_OPENHOSTS, OnButtonOpenhosts)
	ON_BN_CLICKED(IDC_CHECK_MASK_YOUKU, OnCheckMaskYouku)
	ON_BN_CLICKED(IDC_CHECK_MASK_TUDOU, OnCheckMaskTudou)
	ON_BN_CLICKED(IDC_CHECK_MASK_XUNLEI, OnCheckMaskXunlei)
	ON_BN_CLICKED(IDC_CHECK_MASK_OTHER, OnCheckMaskOther)
	ON_BN_CLICKED(IDC_CHECK_MASK_KU6, OnCheckMaskKu6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GeneralTool message handlers

BOOL GeneralTool::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
    m_BtnRestartExplorer.SetShade(CShadeButtonST::SHS_METAL);
    m_BtnRestartExplorer.SetIcon(SysUtil::GetSystemIcon(24));

    m_BtnRebulidIconCache.SetShade(CShadeButtonST::SHS_METAL);
    m_BtnRebulidIconCache.SetIcon(SysUtil::GetSystemIcon(238));

    CButton *pButton = (CButton *)GetDlgItem(IDC_CHECK_SHOWBOOTTIME);
    pButton->SetCheck(SysUtil::IsRegRun(_T("ShowBootTime")));

    ReadMaskAD();
	return TRUE; 
}

void GeneralTool::OnOK() 
{
//	CResizingDialog::OnOK();
}

void GeneralTool::OnCancel() 
{
//	CResizingDialog::OnCancel();
}

void GeneralTool::OnBtnRebulidIconCache() 
{
    SysUtil::RebulidIconCache();
}

void GeneralTool::OnBtnRestartExplorer() 
{
    CRegistry reg;
    //HKEY_LOCAL_MACHINE\SOFTWARE\Classes\CLSID\{ED228FDF-9EA8-4870-83b1-96b02CFE0D52}
//    reg.SetRootKey(HKEY_LOCAL_MACHINE);
//	reg.SetKey("SOFTWARE\\Classes\\CLSID\\{ED228FDF-9EA8-4870-83b1-96b02CFE0D52}\\test",TRUE);
//    reg.SetPermission("");
//	reg.SetKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FolderTypes\\{5c4f28b5-f869-4e84-8e60-f11db97c5cc7}",FALSE);
   CString explorerExe = _T("explorer.exe");
 	SysUtil::KillProcess(explorerExe);
}

void GeneralTool::OnCheckShowboottime() 
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_CHECK_SHOWBOOTTIME);
    CString name = _T("ShowBootTime");

    CString strPath;
    CString strName;
    SysUtil::GetCurrentPathOrMoudle(strPath, strName);
    if(pButton->GetCheck())
    {
        CString strCmdline =  strPath += strName + _T(".exe /showBootTime");
        SysUtil::WriteRegRun(name,strCmdline);
    }else
    {
        SysUtil::RemoveRegRun(name);
    }	
}

void GeneralTool::OnButtonOpenhosts() 
{

    CString CmdOpenHosts = "notepad " + GetHostsPath();

    WinExec(CmdOpenHosts,SW_SHOW);
}

CString GeneralTool::GetHostsPath()
{
    TCHAR SysPath[MAX_PATH];
    ::GetSystemDirectory(SysPath, MAX_PATH);
    CString HostsPath = SysPath;
    HostsPath +=  _T("\\drivers\\etc\\hosts");

    return HostsPath;
}

void GeneralTool::ReadMaskAD()
{
    CFile file;
    CString HostPath = GetHostsPath();
    if(!file.Open(HostPath,CFile::modeRead))
        MessageBox("不能打开hosts文件");

    int len = file.GetLength();
    TCHAR *buf = new TCHAR[len];
    file.Read(buf,file.GetLength());

    CButton *pButton = NULL;
    if(_tcsstr(buf,m_maskADContent[0]))
    {
        pButton = (CButton *)GetDlgItem(IDC_CHECK_MASK_YOUKU);
        pButton->SetCheck(TRUE);
    }
    if(_tcsstr(buf,m_maskADContent[1]))
    {
        pButton = (CButton *)GetDlgItem(IDC_CHECK_MASK_TUDOU);
        pButton->SetCheck(TRUE);
    }
    if(_tcsstr(buf,m_maskADContent[2]))
    {
        pButton = (CButton *)GetDlgItem(IDC_CHECK_MASK_XUNLEI);
        pButton->SetCheck(TRUE);
    }
    if(_tcsstr(buf,m_maskADContent[3]))
    {
        pButton = (CButton *)GetDlgItem(IDC_CHECK_MASK_OTHER);
        pButton->SetCheck(TRUE);
    }

	if(_tcsstr(buf,m_maskADContent[4]))
    {
        pButton = (CButton *)GetDlgItem(IDC_CHECK_MASK_KU6);
        pButton->SetCheck(TRUE);
    }
    if(buf)
    {
        delete[] buf;
        buf = NULL;
    }
    file.Close();
}

void GeneralTool::OnCheckMaskYouku() 
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_CHECK_MASK_YOUKU);
    CheckMaskItem(0,pButton->GetCheck());
}

void GeneralTool::OnCheckMaskTudou() 
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_CHECK_MASK_TUDOU);
    CheckMaskItem(1,pButton->GetCheck());
}

void GeneralTool::OnCheckMaskXunlei() 
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_CHECK_MASK_XUNLEI);
    CheckMaskItem(2,pButton->GetCheck());
}

void GeneralTool::OnCheckMaskOther() 
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_CHECK_MASK_OTHER);
    CheckMaskItem(3,pButton->GetCheck());
}
void GeneralTool::OnCheckMaskKu6() 
{
    CButton *pButton = (CButton *)GetDlgItem(IDC_CHECK_MASK_KU6);
    CheckMaskItem(4,pButton->GetCheck());
}

void GeneralTool::CheckMaskItem(int nItem, BOOL bCheck)
{
    CFile file;
    CString HostPath = GetHostsPath();
    if(!file.Open(HostPath,CFile::modeRead))
        MessageBox("不能打开hosts文件");
    
    int len = file.GetLength();
    int addLen = m_maskADContent[nItem].GetLength();
    TCHAR *buf = new TCHAR[len+addLen+1];
    file.Read(buf,len);
    buf[len] = 0;
    file.Close();
    if(bCheck)
    {
        if(!_tcsstr(buf,m_maskADContent[nItem]))
        {
            strcat(buf,m_maskADContent[nItem]);
			
            CFile file;
            CString HostPath = GetHostsPath();
            if(!file.Open(HostPath,CFile::modeCreate | CFile::modeWrite))
			{
                MessageBox("不能打开hosts文件");

			}
            file.Write(buf,strlen(buf));
            file.Close();
        }
    }else
    {
        TCHAR *pos = _tcsstr(buf,m_maskADContent[nItem]);
        if(pos)
        {
            if(!file.Open(HostPath,CFile::modeCreate | CFile::modeWrite))
                MessageBox("不能打开hosts文件");
            file.Write(buf,pos-buf);
            file.Write(pos + addLen, len - (pos-buf) - addLen);
            file.Close();
        }
    }

    if(buf)
    {
        delete []buf;
        buf = NULL;
    }
    
}

