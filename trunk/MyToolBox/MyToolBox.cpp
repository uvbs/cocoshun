// MyToolBox.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MyToolBox.h"
#include "MyToolBoxDlg.h"
#include "ClearHistoryDlg.h"
#include "setting.h"
#include "Util/SysUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyToolBoxApp

BEGIN_MESSAGE_MAP(CMyToolBoxApp, CWinApp)
	//{{AFX_MSG_MAP(CMyToolBoxApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyToolBoxApp construction

CMyToolBoxApp::CMyToolBoxApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMyToolBoxApp object

CMyToolBoxApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMyToolBoxApp initialization



BOOL CMyToolBoxApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

 //   LPCTSTR cmdLine = GetCommandLine();
 //   MessageBox(NULL,cmdLine,"OK",MB_OK);
//     CClearHistoryDlg clearDlg;
//     clearDlg.DoModal();
//   SysUtil::ReadSetting(&theSetting);
	if(ExistParameter(_T("/clear"),theApp.m_lpCmdLine))
	{
		CClearHistoryDlg clearDlg;

		if(ExistParameter(_T("/showUI"),theApp.m_lpCmdLine))
		{
			clearDlg.DoModal();
		}else
		{

		}
		
		return FALSE;
	}

	CMyToolBoxDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL CMyToolBoxApp::ExistParameter(CString param, CString cmdLine)
{
	return cmdLine.Find(param) != -1;
}
