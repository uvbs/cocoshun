// BodyWeight.h : main header file for the BODYWEIGHT application
//

#if !defined(AFX_BODYWEIGHT_H__564F3A4A_7074_4D93_A266_348BC9ABBCC7__INCLUDED_)
#define AFX_BODYWEIGHT_H__564F3A4A_7074_4D93_A266_348BC9ABBCC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBodyWeightApp:
// See BodyWeight.cpp for the implementation of this class
//

class CBodyWeightApp : public CWinApp
{
public:
	CBodyWeightApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBodyWeightApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBodyWeightApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BODYWEIGHT_H__564F3A4A_7074_4D93_A266_348BC9ABBCC7__INCLUDED_)
