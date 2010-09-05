// CheckBTGroup.h: interface for the CCheckBTGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKBTGROUP_H__A310CFC1_CA60_4E37_A545_D0A95070C8AC__INCLUDED_)
#define AFX_CHECKBTGROUP_H__A310CFC1_CA60_4E37_A545_D0A95070C8AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BtnST.h"
#include "ShadeButtonST.h"
#include "ResizingDialog.h"

class CCheckBTGroup  
{
public:
	struct ChkBtnIDAndDlg
	{
		UINT CheckBtnID;
		CDialog *Dlg;
		UINT IconID;
	};
	struct CheckGroupInfo
	{
		CWnd *Parent;
		int  nSelected;
		UINT AreaCtrlID;
		ChkBtnIDAndDlg *ChkBtnIDAndDlgs;
	} ;

	BOOL IsCreated();
	void ReSizePages();
    
    void GetPanelRect(CRect &rect);
    
    void SlideShowPage( int nOld,int nNew );
	void SetCheck(int n);
	int GetCheck();


	CCheckBTGroup();
    CCheckBTGroup(CheckGroupInfo ChkGrpInfo, int nPages);

	virtual ~CCheckBTGroup();
	void Init(CheckGroupInfo ChkGrpInfo, int nPages);

private:
	BOOL m_IsCreated;
	CShadeButtonST *m_CheckBtns;
	CheckGroupInfo m_ChkGrpInfo;
	int m_PageNum;
	int m_nSelected;
};	

#endif // !defined(AFX_CHECKBTGROUP_H__A310CFC1_CA60_4E37_A545_D0A95070C8AC__INCLUDED_)
