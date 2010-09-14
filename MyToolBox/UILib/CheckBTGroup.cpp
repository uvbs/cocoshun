// CheckBTGroup.cpp: implementation of the CCheckBTGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
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
    m_nSelected = -1;
}
CCheckBTGroup::CCheckBTGroup(CheckGroupInfo ChkGrpInfo, int nPages)
{
    CCheckBTGroup();
    Init(ChkGrpInfo,nPages);
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
    if(n <0 || n>=m_PageNum ) 
        return;
    if(n == m_nSelected)
    {
        m_CheckBtns[m_nSelected].SetCheck(TRUE);
        return;
    }

    for(int i=0;i<m_PageNum;i++)
    {
        if(i==n)
        {
            m_CheckBtns[n].SetCheck(TRUE);
        }else
        {
            m_CheckBtns[i].SetCheck(FALSE);
        }
    }

    m_ChkGrpInfo.ChkBtnIDAndDlgs[n].Dlg->ShowWindow(SW_SHOW);
	m_ChkGrpInfo.ChkBtnIDAndDlgs[n].Dlg->SetFocus();

    if(m_PageNum>1 && m_nSelected!=-1)
    {
        SlideShowPage(m_nSelected,n);
    }
    if(m_nSelected!=-1)
    {
        m_ChkGrpInfo.ChkBtnIDAndDlgs[m_nSelected].Dlg->ShowWindow(SW_HIDE);
    }
	m_nSelected = n;
}

int CCheckBTGroup::GetCheck()
{
	return m_nSelected;
}

void CCheckBTGroup::ReSizePages()
{
	// get the rect of dialog page area
    CRect rect;
	GetPanelRect(rect);
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

void CCheckBTGroup::SlideShowPage( int nOld,int nNew )
{
    CRect rect;
	GetPanelRect(rect);

    MSG				msg;

    m_ChkGrpInfo.ChkBtnIDAndDlgs[nNew].Dlg->ShowWindow(SW_SHOW);
    for(int x=0;x<rect.Width();x+=20)
    {
         m_ChkGrpInfo.ChkBtnIDAndDlgs[nOld].Dlg->MoveWindow(rect.left, rect.top , rect.Width()-x , rect.Height());
         m_ChkGrpInfo.ChkBtnIDAndDlgs[nNew].Dlg->MoveWindow(rect.Width()-x, rect.top , rect.Width() , rect.Height());
         // 处理消息，防止不响应
         while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
         {
             TranslateMessage(&msg);
             DispatchMessage(&msg);
         }
    }
}

void CCheckBTGroup::GetPanelRect( CRect &rect )
{
    CWnd *Parent = m_ChkGrpInfo.Parent;
    Parent->GetDlgItem(m_ChkGrpInfo.AreaCtrlID)->GetWindowRect(&rect);
    Parent->ScreenToClient(&rect);
    rect.left = rect.left + 5;
    rect.top  = rect.top + 10;
    rect.right= rect.right - 2;
    rect.bottom = rect.bottom - 5;
}