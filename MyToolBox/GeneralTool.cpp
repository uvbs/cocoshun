// GeneralTool.cpp : implementation file
//

#include "stdafx.h"
#include "MyToolBox.h"
#include "GeneralTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GeneralTool dialog


GeneralTool::GeneralTool(CWnd* pParent /*=NULL*/)
	: CResizingDialog(GeneralTool::IDD, pParent)
{
	//{{AFX_DATA_INIT(GeneralTool)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void GeneralTool::DoDataExchange(CDataExchange* pDX)
{
	CResizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GeneralTool)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GeneralTool, CResizingDialog)
	//{{AFX_MSG_MAP(GeneralTool)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GeneralTool message handlers

BOOL GeneralTool::OnInitDialog() 
{
	CResizingDialog::OnInitDialog();
	
	return TRUE; 
}

void GeneralTool::OnOK() 
{
//	CResizingDialog::OnOK();
}

void GeneralTool::OnCancel() 
{
//	CResizingDialog::OnCancel();
}
