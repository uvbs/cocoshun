// IECacheCatcher.h : main header file for the IECACHECATCHER application
//

#if !defined(AFX_IECACHECATCHER_H__7846D745_71B3_49E1_A403_83259D0AF25A__INCLUDED_)
#define AFX_IECACHECATCHER_H__7846D745_71B3_49E1_A403_83259D0AF25A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIECacheCatcherApp:
// See IECacheCatcher.cpp for the implementation of this class
//

class CIECacheCatcherApp : public CWinApp
{
public:
	CIECacheCatcherApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIECacheCatcherApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIECacheCatcherApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IECACHECATCHER_H__7846D745_71B3_49E1_A403_83259D0AF25A__INCLUDED_)
