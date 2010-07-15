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
	m_DlgPages = NULL;
}

CCheckBTGroup::~CCheckBTGroup()
{
	if(m_CheckBtns !=NULL)
	{
		delete []m_CheckBtns;
	}
	if(m_DlgPages !=NULL)
	{
		delete []m_DlgPages;
	}
}

void CCheckBTGroup::Init(CWnd *parent,CheckGroupInfo ChkGrpInfo)
{
	m_Parent = parent;
	UINT *CheckBtns = ChkGrpInfo.CheckBtnIDs;
//	UINT *DlgPageIDs = ChkGrpInfo.DlgPageIDs;
	UINT AreaCtrlID = ChkGrpInfo.AreaCtrlID;
	int DefaultSelcted = ChkGrpInfo.nSelected;
	CDialog *Dlgs = ChkGrpInfo.Dlgs;
	
	// init check buttons
	m_BtnNum = sizeof(CheckBtns) -1;

	m_CheckBtns = new CShadeButtonST[m_BtnNum];
	for(int i=0; i<m_BtnNum; i++)
	{
		m_CheckBtns[i].SubclassWindow(parent->GetDlgItem(CheckBtns[i])->m_hWnd);
		m_CheckBtns[i].SetShade(CShadeButtonST::SHS_SOFTBUMP,8,20,5,RGB(55,55,255));
		if(i == DefaultSelcted)
		{
			m_CheckBtns[i].SetCheck(TRUE);
		}
	}

	// init dialog pages
	m_DlgPageNum = sizeof(Dlgs) -1;
	m_DlgPages = Dlgs;

	CRect rect;
	parent->GetDlgItem(AreaCtrlID)->GetWindowRect(&rect);
	parent->ScreenToClient(&rect);
	rect.left = rect.left + 10;
	rect.top  = rect.top + 10;
	rect.right= rect.right - 10;
	rect.bottom = rect.bottom - 10;

	for(int j=0; j<m_DlgPageNum; j++)
	{
//		m_DlgPages[j].Create(DlgPageIDs[j],parent);
		m_DlgPages[j].MoveWindow(rect.left, rect.top , rect.Width() , rect.Height());
	}

	SetCheck(DefaultSelcted);
}

void CCheckBTGroup::SetCheck(int n)
{
	for(int i=0; i<m_BtnNum; i++)
	{
		if(i == n)
		{
			m_CheckBtns[i].SetCheck(TRUE);
			m_DlgPages[i].ShowWindow(SW_SHOW);
		}else
		{
			m_CheckBtns[i].SetCheck(FALSE);
			m_DlgPages[i].ShowWindow(SW_HIDE);
		}
	}
}
