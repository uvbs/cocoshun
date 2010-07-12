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

class CCheckBTGroup  
{
public:
	void SetCheck(int n);
	CCheckBTGroup();
	virtual ~CCheckBTGroup();
	void SubClassWindows(CWnd *parent,UINT CheckBtns[], int DefaultCheck);

private:
	CShadeButtonST *m_CheckBtns;
	int m_BtnNum;
};

#endif // !defined(AFX_CHECKBTGROUP_H__A310CFC1_CA60_4E37_A545_D0A95070C8AC__INCLUDED_)
