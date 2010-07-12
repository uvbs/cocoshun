// KmcMaker.h : main header file for the KMCMAKER application
//

#if !defined(AFX_KMCMAKER_H__91C3A9DB_A420_4508_BD0C_6134FA754748__INCLUDED_)
#define AFX_KMCMAKER_H__91C3A9DB_A420_4508_BD0C_6134FA754748__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKmcMakerApp:
// See KmcMaker.cpp for the implementation of this class
//

class CKmcMakerApp : public CWinApp
{
public:
	CKmcMakerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKmcMakerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKmcMakerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KMCMAKER_H__91C3A9DB_A420_4508_BD0C_6134FA754748__INCLUDED_)
