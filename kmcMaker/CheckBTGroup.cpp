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

void CCheckBTGroup::Init(CheckGroupInfo ChkGrpInfo)
{
	m_ChkGrpInfo = ChkGrpInfo;

	// init check buttons
	m_PageNum = sizeof(ChkGrpInfo.ChkBtnIDAndDlgs->CheckBtnID) -1;

	m_CheckBtns = new CShadeButtonST[m_PageNum];
	for(int i=0; i<m_PageNum; i++)
	{
		// init check buttons
		m_CheckBtns[i].SubclassWindow(ChkGrpInfo.Parent->GetDlgItem(ChkGrpInfo.ChkBtnIDAndDlgs[i].CheckBtnID)->m_hWnd);
		m_CheckBtns[i].SetShade(CShadeButtonST::SHS_SOFTBUMP,8,20,5,RGB(55,55,255));
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

void CCheckBTGroup::ReSizePages()
{
	// get the rect of dialog page area
	CWnd *Parent = m_ChkGrpInfo.Parent;
	CRect rect;
	Parent->GetDlgItem(m_ChkGrpInfo.AreaCtrlID)->GetWindowRect(&rect);
	Parent->ScreenToClient(&rect);
	rect.left = rect.left + 10;
	rect.top  = rect.top + 10;
	rect.right= rect.right - 10;
	rect.bottom = rect.bottom - 10;
	
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
