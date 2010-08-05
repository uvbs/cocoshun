// XButtonXPTest.h : main header file for the XBUTTONXPTEST application
//

#ifndef XBUTTONXPTEST_H
#define XBUTTONXPTEST_H

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXButtonXPTestApp:
// See XButtonXPTest.cpp for the implementation of this class
//

class CXButtonXPTestApp : public CWinApp
{
public:
	CXButtonXPTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXButtonXPTestApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXButtonXPTestApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XBUTTONXPTEST_H
