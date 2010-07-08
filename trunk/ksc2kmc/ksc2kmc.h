// ksc2kmc.h : main header file for the KSC2KMC application
//

#if !defined(AFX_KSC2KMC_H__0C9202EA_656F_4F36_8BF6_35C1859FFAF0__INCLUDED_)
#define AFX_KSC2KMC_H__0C9202EA_656F_4F36_8BF6_35C1859FFAF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKsc2kmcApp:
// See ksc2kmc.cpp for the implementation of this class
//

class CKsc2kmcApp : public CWinApp
{
public:
	CKsc2kmcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKsc2kmcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKsc2kmcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KSC2KMC_H__0C9202EA_656F_4F36_8BF6_35C1859FFAF0__INCLUDED_)
