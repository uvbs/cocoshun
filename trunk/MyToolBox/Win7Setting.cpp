// Win7Setting.cpp : implementation file
//

#include "stdafx.h"
#include "MyToolBox.h"
#include "Win7Setting.h"
#include "Util/SysUtil.h"
#include "Util/Registry.h"
#include <shlwapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Win7Setting dialog
CTRL_OPERATION Win7Setting::m_SettingOper[]=
{
    IDC_CHECK_HIDE_FAVORITES,CHECKBOX,
    {Write,{HKEY_CLASSES_ROOT,_T("CLSID\\{323CA680-C24D-4099-B94D-446DD2D7249E}\\ShellFolder"),_T("Attributes"),DW,0xa9400100}},
    {Write,{HKEY_CLASSES_ROOT,_T("CLSID\\{323CA680-C24D-4099-B94D-446DD2D7249E}\\ShellFolder"),_T("Attributes"),DW,0xa9000100}},
    {Query,{HKEY_CLASSES_ROOT,_T("CLSID\\{323CA680-C24D-4099-B94D-446DD2D7249E}\\ShellFolder"),_T("Attributes"),DW}},   

    IDC_CHECK_HIDE_LIBRARIES,CHECKBOX,
    {Write,{HKEY_CLASSES_ROOT,_T("CLSID\\{031E4825-7B94-4dc3-B131-E946B44C8DD5}\\ShellFolder"),_T("Attributes"),DW,0xb090010d}},
    {Write,{HKEY_CLASSES_ROOT,_T("CLSID\\{031E4825-7B94-4dc3-B131-E946B44C8DD5}\\ShellFolder"),_T("Attributes"),DW,0xb080010d}},
    {Query,{HKEY_CLASSES_ROOT,_T("CLSID\\{031E4825-7B94-4dc3-B131-E946B44C8DD5}\\ShellFolder"),_T("Attributes"),DW}},   

    IDC_CHECK_DISABLE_WINDOW_AUTO_ARRANGEMENT,CHECKBOX,
    {Write,{HKEY_CURRENT_USER,_T("Control Panel\\Desktop"),_T("WindowArrangementActive"),STRING,0,_T("0")}},
    {Write,{HKEY_CURRENT_USER,_T("Control Panel\\Desktop"),_T("WindowArrangementActive"),STRING,0,_T("1")}},
    {Query,{HKEY_CURRENT_USER,_T("Control Panel\\Desktop"),_T("WindowArrangementActive"),STRING}},   
};

Win7Setting::Win7Setting(CWnd* pParent /*=NULL*/)
	: CResizingDialog(Win7Setting::IDD, pParent)
{
	//{{AFX_DATA_INIT(Win7Setting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void Win7Setting::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Win7Setting)
	DDX_Control(pDX, IDC_LIST_FolderType, m_ListFolderType);
//	DDX_Control(pDX, IDC_BTN_RESTART_EXPLORER, m_BtnRestartExplorer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Win7Setting, CResizingDialog)
	//{{AFX_MSG_MAP(Win7Setting)
//	ON_BN_CLICKED(IDC_BTN_RESTART_EXPLORER, OnBtnRestartExplorer)
	ON_BN_CLICKED(IDC_CHECK_HIDE_FAVORITES, OnCheckHideFavorites)
	ON_BN_CLICKED(IDC_CHECK_HIDE_LIBRARIES, OnCheckHideLibraries)
	ON_BN_CLICKED(IDC_CHECK_DISABLE_WINDOW_AUTO_ARRANGEMENT, OnCheckDisableWindowAutoArrangement)
	ON_NOTIFY(NM_CLICK, IDC_LIST_FolderType, OnClickLISTFolderType)
	ON_BN_CLICKED(IDC_RADIO_SELECT, OnRadioSelect)
	ON_BN_CLICKED(IDC_RADIO_UNSELECT, OnRadioUnselect)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FolderType, OnItemchangedLISTFolderType)
	ON_BN_CLICKED(IDC_CHECK_DISABLE_FULLROWSELECT, OnCheckDisableFullrowselect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Win7Setting message handlers

BOOL Win7Setting::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();

//     m_BtnRestartExplorer.SetShade(CShadeButtonST::SHS_METAL);
// 	m_BtnRestartExplorer.SetIcon(IDI_RESTART_EXPLORER);
	
    m_ctrlAction.Initialize(this,m_SettingOper);
    m_ctrlAction.Process(IDC_CHECK_HIDE_FAVORITES,TRUE);
    m_ctrlAction.Process(IDC_CHECK_HIDE_LIBRARIES,TRUE);
    m_ctrlAction.Process(IDC_CHECK_DISABLE_WINDOW_AUTO_ARRANGEMENT,TRUE);

    SetCheck(IDC_RADIO_SELECT,TRUE);
    m_strItem = _T("\\TasksItemsSelected");
    InitToolBarList();

    ReadFullRowSelect();

 //   GetToolbarItemCheckValue(0);
//	SetControlInfo(IDC_CHECK_HIDE_FAVORITES,ANCHORE_LEFT);

  //   m_ListFolderType.SetFocus();
 //    m_ListFolderType.SetSelectionMark(2);
//     TRACE("%d",m_ListFolderType.GetSelectionMark());
	return TRUE;  
}

void Win7Setting::OnOK() 
{
//	CResizingDialog::OnOK();
}

void Win7Setting::OnCancel() 
{
//	CResizingDialog::OnCancel();
}

// void Win7Setting::OnBtnRestartExplorer() 
// {
// 	CString explorerExe = _T("explorer.exe");
// 	SysUtil::KillProcess(explorerExe);
// }

void Win7Setting::OnCheckHideFavorites() 
{
    m_ctrlAction.Process(IDC_CHECK_HIDE_FAVORITES);
}

void Win7Setting::OnCheckHideLibraries() 
{
    m_ctrlAction.Process(IDC_CHECK_HIDE_LIBRARIES); 	
}

void Win7Setting::OnCheckDisableWindowAutoArrangement() 
{
	m_ctrlAction.Process(IDC_CHECK_DISABLE_WINDOW_AUTO_ARRANGEMENT); 	
}

void Win7Setting::OnClickLISTFolderType(NMHDR* pNMHDR, LRESULT* pResult) 
{
    int nSelect = m_ListFolderType.GetSelectionMark();
    GetToolbarItemCheckValue(nSelect);
	*pResult = 0;
}

void Win7Setting::InitToolBarList()
{
    // 初始化左侧的列表数据
    static EXP_TOOLBAR_LIST arrayList[] = 
    {
        {0,_T("{5c4f28b5-f869-4e84-8e60-f11db97c5cc7}"),_T("所有文件夹"),126},
        {1,_T("{7d49d726-3c21-4f05-99aa-fdc2c9474656}"),_T("文件"),70},
        {2,_T("{80213e82-bcfd-4c4f-8817-bb27601267a9}"),_T("压缩文件夹"),279},
        {3,_T("{b3690e58-e961-423b-b687-386ebfd83239}"),_T("图片"), 128},
        {4,_T("{94d6ddcc-4a68-4175-a374-bd584a510b78}"),_T("音乐"), 127},
        {5,_T("{5fa96407-7e77-483c-ac93-691d05850de8}"),_T("影片"),115},
        {6,_T("{5f4eab9a-6833-4f61-899d-31cf46979d49}"),_T("通用库"),19},
        {7,_T("{fbb3477e-c9e4-4b3b-a2ba-d3f5d3cd46f9}"),_T("文档库"),110},
        {8,_T("{0b2baaeb-0042-4dca-aa4d-3ee8648d03e5}"),_T("图片库"),127},
        {9,_T("{3f2a72a7-99fa-4ddb-a5a8-c604edf61d6b}"),_T("音乐库"),128},
        {10,_T("{631958a6-ad0f-4035-a745-28ac066dc6ed}"),_T("视频库"),129},
        {11,_T("{7fde1a1e-8b31-49a5-93b8-6be14cfa4943}"),_T("通用搜索"),22},
        {12,_T("{36011842-dccc-40fe-aa3d-6177ea401788}"),_T("文件搜索"),209},
        {13,_T("{71689ac1-cc88-45d0-8a22-2943c3e7dfb3}"),_T("音乐搜索"),55},
        {14,_T("{4dcafe13-e6a7-4c28-be02-ca8c2126280d}"),_T("图片搜索"),55},
        {15,_T("{ea25fbd7-3bf7-409e-b97f-3352240903f4}"),_T("影片搜索"),55},
    };
    m_ExpToolBarList = arrayList;
    int listSize = sizeof(arrayList) / sizeof(EXP_TOOLBAR_LIST);

    // create icons list from shell32.dll
    static CImageList ImageList;
    ImageList.Create(18,18,ILC_COLOR32,0,0); 

    // set list style
    m_ListFolderType.SetImageList(&ImageList,LVSIL_SMALL );
    m_ListFolderType.InsertColumn(0,_T(""));
    m_ListFolderType.SetColumnWidth(0,110);
    m_ListFolderType.SetExtendedStyle(LVS_EX_FULLROWSELECT);
    for(int i=0;i<listSize;i++)
    {
        HICON hIcon = SysUtil::GetSystemIcon(m_ExpToolBarList[i].nIconIndex);
        ImageList.Add(hIcon);
        
        m_ListFolderType.InsertItem(i,m_ExpToolBarList[i].szName,i);
    }
     
//     if(m_ListFolderType.GetSelectionMark()==-1)
//         MessageBox("xx");

    // 初始化右侧的CheckBox数据
    static EXP_BUTTON arrayCheckboxBtns[]=
    {
        {IDC_CHECK_COPY         ,_T("Windows.Copy;")},     
        {IDC_CHECK_PASTE        ,_T("Windows.Paste;")},    
        {IDC_CHECK_CUT          ,_T("Windows.Cut;")},      
        {IDC_CHECK_DELETE       ,_T("Windows.Delete;")},   
        {IDC_CHECK_UNDO         ,_T("Windows.Undo;")},     
        {IDC_CHECK_REDO         ,_T("Windows.Redo;")},     
        {IDC_CHECK_PRINT        ,_T("Windows.Print;")},    
        {IDC_CHECK_EMAIL        ,_T("Windows.Email;")},    
        {IDC_CHECK_BURN         ,_T("Windows.Burn;")},     
        {IDC_CHECK_SLIDESSHOW   ,_T("Windows.Slideshow;")},
    };
    m_nCheckboxArySize = sizeof(arrayCheckboxBtns) / sizeof(EXP_BUTTON);
    m_ExpToolBarCheckBtns = arrayCheckboxBtns;


    m_ListFolderType.SetItemState(0,LVIS_SELECTED,LVIS_SELECTED); 
    m_ListFolderType.SetFocus(); 
    m_ListFolderType.SetSelectionMark(0);
    GetToolbarItemCheckValue(0);

}

void Win7Setting::GetToolbarItemCheckValue(int nIndex)
{
    if(nIndex == -1)
        return;
    
    CString strGUID = m_ExpToolBarList[nIndex].szGUID;
    CString pathPrefix = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FolderTypes\\");
    CString path = pathPrefix + strGUID + m_strItem + _T("\\");

    CRegistry reg;
    reg.SetRootKey(HKEY_LOCAL_MACHINE);
    reg.SetKey(path,FALSE);
    if(!reg.PathIsValid())
    {
        ClearToolbarCheckBox();
        return;
    }
        
    CString regValue = reg.ReadString(_T(""), _T(""));

    for(int i=0;i<m_nCheckboxArySize;i++)
    {
        EXP_BUTTON expBtn = m_ExpToolBarCheckBtns[i];
        if(regValue.Find(expBtn.szButton) !=-1)
        {
            SetCheck(expBtn.CheckBoxID,TRUE);
        }else
        {
            SetCheck(expBtn.CheckBoxID,FALSE);
        }
    }
}
BOOL Win7Setting::GetCheck(UINT ID)
{
    CButton *pButton = (CButton *)GetDlgItem(ID);
    return pButton->GetCheck();
}

void Win7Setting::SetCheck(UINT ID,BOOL bCheck)
{
    CButton *pButton = (CButton *)GetDlgItem(ID);
    pButton->SetCheck(bCheck);
}

void Win7Setting::ClearToolbarCheckBox()
{
    for(int i=0;i<m_nCheckboxArySize;i++)
    {
        EXP_BUTTON expBtn = m_ExpToolBarCheckBtns[i];
        SetCheck(expBtn.CheckBoxID,FALSE);
    }
}

BOOL Win7Setting::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_LBUTTONDOWN)
    {
        int index = -1;
        for( int i=0;i<m_nCheckboxArySize;i++)
        {
            if(pMsg->hwnd == (GetDlgItem(m_ExpToolBarCheckBtns[i].CheckBoxID)->GetSafeHwnd()))
            {
                index = i;
                break;
            }
        }
        
        if(index != -1)
        {
             BOOL bCheck = !GetCheck(m_ExpToolBarCheckBtns[index].CheckBoxID);
             ClickToolbarItemCheckValue(index, bCheck);
        }
    }	
	return CResizingDialog::PreTranslateMessage(pMsg);
}

void Win7Setting::ClickToolbarItemCheckValue(int nIndex, BOOL bCheck)
{
    int nListIndex = m_ListFolderType.GetSelectionMark();
    if(nListIndex == -1) 
        return;

    CString strGUID = m_ExpToolBarList[nListIndex].szGUID;
    CString pathPrefix = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FolderTypes\\");
    CString path = pathPrefix + strGUID + m_strItem + _T("\\");

    CRegistry reg;
    reg.SetRootKey(HKEY_LOCAL_MACHINE);
    reg.SetKey(path,TRUE);

    CString strValue = reg.ReadString(_T(""),_T(""));
    CString str = m_ExpToolBarCheckBtns[nIndex].szButton;
    if(bCheck)
    {
        strValue+=str;
    }else
    {
        strValue.Replace(str,_T(""));
    }

//    for(int i=0;i<m_nCheckboxArySize;i++)
//    {
//         if(!GetCheck(m_ExpToolBarCheckBtns[i].CheckBoxID))
//         {
//             strValue+=m_ExpToolBarCheckBtns[i].szButton;
//         }
//    }
     if(strValue.IsEmpty())
         reg.DeleteValue(_T(""));
     else
         reg.WriteString(_T(""),strValue);
}

void Win7Setting::OnRadioSelect() 
{
	m_strItem = _T("\\TasksItemsSelected");
    int nSelect = m_ListFolderType.GetSelectionMark();
    GetToolbarItemCheckValue(nSelect);
}

void Win7Setting::OnRadioUnselect() 
{
	m_strItem = _T("\\TasksNoItemsSelected");
    int nSelect = m_ListFolderType.GetSelectionMark();
    GetToolbarItemCheckValue(nSelect);
}

void Win7Setting::OnItemchangedLISTFolderType(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    int nSelect = m_ListFolderType.GetSelectionMark();
    GetToolbarItemCheckValue(nSelect);	
	*pResult = 0;
}

void Win7Setting::OnCheckDisableFullrowselect() 
{
    CRegistry reg;
    reg.SetRootKey(HKEY_CURRENT_USER);
    CString pathBags = _T("Software\\Classes\\Local Settings\\Software\\Microsoft\\Windows\\Shell\\Bags");
    if(GetCheck(IDC_CHECK_DISABLE_FULLROWSELECT))
    {
        SHDeleteKey(HKEY_CURRENT_USER,pathBags);
        pathBags+=_T("\\AllFolders\\Shell");

        for(int i=0;i<m_ListFolderType.GetItemCount();i++)
        {
            CString guidPath = pathBags+ _T("\\") + m_ExpToolBarList[i].szGUID;
            reg.SetKey(guidPath,TRUE);
            reg.WriteDword(_T("FFlags"),0x43000001);
            reg.WriteDword(_T("Mode"),0x00000004);
        }
        reg.SetKey(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced"),TRUE);
        reg.WriteDword(_T("FullRowSelect"),0x00000000);
    }else
    {
        reg.SetKey(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced"),TRUE);
        reg.WriteDword(_T("FullRowSelect"),0x00000001);
    }
}

void Win7Setting::ReadFullRowSelect()
{
    CRegistry reg;
    reg.SetRootKey(HKEY_CURRENT_USER);
    reg.SetKey(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced"),FALSE);
    DWORD value = reg.ReadDword(_T("FullRowSelect"),0);

    if(value)
    {
        SetCheck(IDC_CHECK_DISABLE_FULLROWSELECT,FALSE);
    }else
    {
        SetCheck(IDC_CHECK_DISABLE_FULLROWSELECT,TRUE);
    }
}
