#if !defined(AFX_FILELISTCTRL_H__5A7C7D5F_B157_4952_83A4_E367BD5B508A__INCLUDED_)
#define AFX_FILELISTCTRL_H__5A7C7D5F_B157_4952_83A4_E367BD5B508A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ReportCtrl.h"
#include <map>
using namespace std;
// FileListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileListCtrl window

class CFileListCtrl : public CReportCtrl
{
// Construction
public:
	CFileListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	int AddFileItem(int nIndex, LPCTSTR pszText, ...);
    void SetFileTypeColum(int nColumn);
	virtual ~CFileListCtrl();

    typedef struct
    {
        int iIconIndex;
        TCHAR TypeName[MAX_PATH];
    }ITEMINFO;
	// Generated message map functions
protected:
    int m_nFileTypeColumn;
    BOOL m_bSetImageList;
	CImageList m_ImageList;
	int m_nIconIndex;
	map<CString, ITEMINFO> m_extIndexMap;
	void AddImageByFileName( LPCTSTR pszText );
	//{{AFX_MSG(CFileListCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

   
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILELISTCTRL_H__5A7C7D5F_B157_4952_83A4_E367BD5B508A__INCLUDED_)
