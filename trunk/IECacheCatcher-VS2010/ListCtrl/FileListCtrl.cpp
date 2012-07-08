// FileListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "..\IECacheCatcher.h"
#include "FileListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileListCtrl

CFileListCtrl::CFileListCtrl()
{
    m_nFileTypeColumn = -1;
	m_nIconIndex = -1;
    m_bSetImageList = FALSE;
	m_ImageList.Create(20, 20, ILC_COLOR16 | ILC_MASK, 1, 0);

}

CFileListCtrl::~CFileListCtrl()
{

}


BEGIN_MESSAGE_MAP(CFileListCtrl, CReportCtrl)
	//{{AFX_MSG_MAP(CFileListCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileListCtrl message handlers

int CFileListCtrl::AddFileItem(int nIndex, LPCTSTR pszText, ...)
{
	if(!m_bSetImageList)
	{
        m_bSetImageList = TRUE;
		SetImageList(&m_ImageList,LVSIL_SMALL);
	}

    TCHAR *pDot = (TCHAR *)_tcsrchr(pszText, '.');
    const TCHAR *pTypeName;
    int nImage = -1;
    if(pDot)
    {
        pDot += 1;
        CString Ext(pDot);
        Ext = Ext.MakeLower();

        map<CString, ITEMINFO>::const_iterator itr;
        itr = m_extIndexMap.find(Ext);
        int len = m_extIndexMap.size();
        if(itr == m_extIndexMap.end())
    	    AddImageByFileName(Ext);

        itr = m_extIndexMap.find(Ext);
        if(itr != m_extIndexMap.end())
        {
            nImage = itr->second.iIconIndex;
            pTypeName = itr->second.TypeName;
        }
    }
    
	const int iIndex = CReportCtrl::InsertItem(nIndex, pszText, nImage);
	
	if (!_IsValidIndex(iIndex))
		return iIndex;
	
	CStringArray arr;
	arr.Add(pszText);
	
	va_list list;
	va_start(list, pszText);
	
	for(int iColumn = 1; iColumn < GetColumnCount()+1; iColumn++)
	{
        if(m_nFileTypeColumn!=iColumn)
        {
		LPCTSTR lpsz = va_arg(list, LPCTSTR);
		CString str = (lpsz == NULL) ? _T("") : lpsz;
		arr.Add(str);
        CListCtrl::SetItemText(iIndex, iColumn, str);
        }
	}

    if(m_nFileTypeColumn != -1 && pTypeName)
    {
        CListCtrl::SetItemText(iIndex, m_nFileTypeColumn, pTypeName);
        arr.InsertAt(m_nFileTypeColumn, pTypeName);
    }
	
	va_end(list);
	
	_AssignNewItemData(iIndex, arr.GetData(), arr.GetSize());

	return iIndex;
}

void CFileListCtrl::AddImageByFileName( LPCTSTR pszText )
{
    if(!pszText)
        return;

    CString sDummyFileName(_T("foo."));
    sDummyFileName += pszText;

    // Call SHGetFileInfo to get the icon. Call with dummy filename and
    // SHGFI_USEFILEATTRIBUTES flag, so file doesn't actually have to
    // exist.
    SHFILEINFO shfi;
    memset(&shfi,0,sizeof(shfi));
    SHGetFileInfo(sDummyFileName,
        FILE_ATTRIBUTE_NORMAL,
        &shfi,
        sizeof(shfi),
        SHGFI_ICON|SHGFI_USEFILEATTRIBUTES|SHGFI_TYPENAME);

    m_nIconIndex++;
    ITEMINFO ItemInfo;
    ItemInfo.iIconIndex = m_nIconIndex;
    lstrcpy(ItemInfo.TypeName,shfi.szTypeName); 

    m_extIndexMap.insert(pair<CString, ITEMINFO>(pszText,ItemInfo));

    m_ImageList.Add(shfi.hIcon);
}

void CFileListCtrl::SetFileTypeColum( int nColumn )
{
    m_nFileTypeColumn = nColumn;
}
