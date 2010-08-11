// CheckBTGroup.h: interface for the CCheckBTGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKBTGROUP_H__A310CFC1_CA60_4E37_A545_D0A95070C8AC__INCLUDED_)
#define AFX_CHECKBTGROUP_H__A310CFC1_CA60_4E37_A545_D0A95070C8AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UILib/BtnST.h"
#include "UILib/ShadeButtonST.h"
#include "UILib/ResizingDialog.h"

typedef struct ChkBtnIDAndDlg_Tag
{
	UINT CheckBtnID;
	CDialog *Dlg;	
}ChkBtnIDAndDlg;

typedef struct CheckGroupInfo_Tag
{
	CWnd *Parent;
	int  nSelected;
	UINT AreaCtrlID;
	ChkBtnIDAndDlg *ChkBtnIDAndDlgs;
} CheckGroupInfo;

class CCheckBTGroup  
{
public:
	BOOL IsCreated();
	void ReSizePages();

	void SetCheck(int n);
	int GetCheck();
	CCheckBTGroup();
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
