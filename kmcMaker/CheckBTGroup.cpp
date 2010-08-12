// CheckBTGroup.cpp: implementation of the CCheckBTGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KmcMaker.h"
#include "CheckBTGroup.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheckBTGroup::CCheckBTGroup()
{
	m_CheckBtns = NULL;
	m_IsCreated = FALSE;
}

CCheckBTGroup::~CCheckBTGroup()
{
	if(m_CheckBtns !=NULL)
	{
		delete [] m_CheckBtns;
		m_CheckBtns = NULL;
	}
}

void CCheckBTGroup::Init(CheckGroupInfo ChkGrpInfo, int nPages)
{
	m_ChkGrpInfo = ChkGrpInfo;

	// init check buttons
	m_PageNum = nPages ;

	m_CheckBtns = new CShadeButtonST[m_PageNum];
	for(int i=0; i<m_PageNum; i++)
	{
		// init check buttons
		m_CheckBtns[i].SubclassWindow(ChkGrpInfo.Parent->GetDlgItem(ChkGrpInfo.ChkBtnIDAndDlgs[i].CheckBtnID)->m_hWnd);
		m_CheckBtns[i].SetShade(CShadeButtonST::SHS_NOISE,8,20,5,::GetSysColor(COLOR_ACTIVEBORDER));
		
		//m_CheckBtns[i].SetShade(CShadeButtonST::SHS_VBUMP,8,20,5,RGB(55,55,255));
		m_CheckBtns[i].SetIcon(AfxGetApp()->LoadIcon(ChkGrpInfo.ChkBtnIDAndDlgs[i].IconID));
	}

	ReSizePages();

	SetCheck(ChkGrpInfo.nSelected);
	m_IsCreated = TRUE;
}

void CCheckBTGroup::SetCheck(int n)
{
	m_nSelected = n;
	for(int i=0; i<m_PageNum; i++)
	{
		if(i == n)
		{
			m_CheckBtns[i].SetCheck(TRUE);
			m_ChkGrpInfo.ChkBtnIDAndDlgs[i].Dlg->ShowWindow(SW_SHOW);
		}else
		{
			m_CheckBtns[i].SetCheck(FALSE);
			m_ChkGrpInfo.ChkBtnIDAndDlgs[i].Dlg->ShowWindow(SW_HIDE);
		}
	}
}

int CCheckBTGroup::GetCheck()
{
	return m_nSelected;
}

void CCheckBTGroup::ReSizePages()
{
	// get the rect of dialog page area
	CWnd *Parent = m_ChkGrpInfo.Parent;
	CRect rect;
	Parent->GetDlgItem(m_ChkGrpInfo.AreaCtrlID)->GetWindowRect(&rect);
	Parent->ScreenToClient(&rect);
	rect.left = rect.left + 5;
	rect.top  = rect.top + 10;
	rect.right= rect.right - 2;
	rect.bottom = rect.bottom - 5;
	
	for(int i=0; i<m_PageNum; i++)
	{
		// set size for dialog pages
		m_ChkGrpInfo.ChkBtnIDAndDlgs[i].Dlg->MoveWindow(rect.left, rect.top , rect.Width() , rect.Height());
	}
}

BOOL CCheckBTGroup::IsCreated()
{
	return m_IsCreated;
}
