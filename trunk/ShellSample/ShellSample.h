// ShellSample.h : main header file for the SHELLSAMPLE application
//

#if !defined(AFX_SHELLSAMPLE_H__87108B1A_AD37_42FA_93CA_E54030C3B447__INCLUDED_)
#define AFX_SHELLSAMPLE_H__87108B1A_AD37_42FA_93CA_E54030C3B447__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShellSampleApp:
// See ShellSample.cpp for the implementation of this class
//

class CShellSampleApp : public CWinApp
{
public:
	CShellSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShellSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShellSampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHELLSAMPLE_H__87108B1A_AD37_42FA_93CA_E54030C3B447__INCLUDED_)
