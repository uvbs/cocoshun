// MyToolBox.h : main header file for the MYTOOLBOX application
//

#if !defined(AFX_MYTOOLBOX_H__F531D489_F773_4BDB_A610_721E0431B8D8__INCLUDED_)
#define AFX_MYTOOLBOX_H__F531D489_F773_4BDB_A610_721E0431B8D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyToolBoxApp:
// See MyToolBox.cpp for the implementation of this class
//

class CMyToolBoxApp : public CWinApp
{
public:
	CMyToolBoxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyToolBoxApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyToolBoxApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL ExistParameter(CString param, CString cmdLine);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTOOLBOX_H__F531D489_F773_4BDB_A610_721E0431B8D8__INCLUDED_)
