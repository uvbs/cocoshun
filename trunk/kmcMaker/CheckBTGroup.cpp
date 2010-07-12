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

}

CCheckBTGroup::~CCheckBTGroup()
{
	if(m_CheckBtns !=NULL)
	{
		delete []m_CheckBtns;
	}
}

void CCheckBTGroup::SubClassWindows(CWnd *parent,UINT CheckBtns[], int DefaultCheck)
{
	m_BtnNum = sizeof(CheckBtns) -1;
	m_CheckBtns = new CShadeButtonST[m_BtnNum];
	for(int i=0; i<m_BtnNum; i++)
	{
		m_CheckBtns[i].SubclassWindow(parent->GetDlgItem(CheckBtns[i])->m_hWnd);
		m_CheckBtns[i].SetShade(CShadeButtonST::SHS_SOFTBUMP,8,20,5,RGB(55,55,255));
		if(i == DefaultCheck)
		{
			m_CheckBtns[i].SetCheck(TRUE);
		}
	}
}

void CCheckBTGroup::SetCheck(int n)
{
	for(int i=0; i<m_BtnNum; i++)
	{
		if(i == n)
		{
			m_CheckBtns[i].SetCheck(TRUE);
		}else
		{
			m_CheckBtns[i].SetCheck(FALSE);
		}
	}
}
