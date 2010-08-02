// HttpPost.h : main header file for the HTTPPOST application
//

#if !defined(AFX_HTTPPOST_H__7F7A482B_4AC7_4B21_807C_543671851635__INCLUDED_)
#define AFX_HTTPPOST_H__7F7A482B_4AC7_4B21_807C_543671851635__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHttpPostApp:
// See HttpPost.cpp for the implementation of this class
//

class CHttpPostApp : public CWinApp
{
public:
	CHttpPostApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHttpPostApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHttpPostApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTTPPOST_H__7F7A482B_4AC7_4B21_807C_543671851635__INCLUDED_)
