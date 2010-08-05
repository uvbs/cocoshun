// XButtonXPTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XButtonXPTest.h"
#include "XButtonXPTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXButtonXPTestApp

BEGIN_MESSAGE_MAP(CXButtonXPTestApp, CWinApp)
	//{{AFX_MSG_MAP(CXButtonXPTestApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXButtonXPTestApp construction

CXButtonXPTestApp::CXButtonXPTestApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXButtonXPTestApp object

CXButtonXPTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXButtonXPTestApp initialization

BOOL CXButtonXPTestApp::InitInstance()
{
#if _MFC_VER < 0x700
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	CXButtonXPTestDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
