// CtrlAction.h: interface for the CCtrlAction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTRLACTION_H__FC08DAEF_29D6_4F4C_A69D_D13DE014CE14__INCLUDED_)
#define AFX_CTRLACTION_H__FC08DAEF_29D6_4F4C_A69D_D13DE014CE14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FuncDef.h"

class CCtrlAction  
{
public:
	void Process(UINT ID, BOOL bGetValue = FALSE);
	CCtrlAction();
	virtual ~CCtrlAction();
    
    void Initialize(CWnd *pWnd, CTRL_OPERATION *settingOper)
    {
        m_hWnd = pWnd;
        m_ctlOper = settingOper;
    };
private:
    CWnd *m_hWnd;
    CTRL_OPERATION *m_ctlOper;

    CTRL_OPERATION *GetCtrlOperationByID(UINT ID);
    
    void ProcessCheckbox(UINT ID, CTRL_OPERATION *co,BOOL bGetValue = FALSE);
};

#endif // !defined(AFX_CTRLACTION_H__FC08DAEF_29D6_4F4C_A69D_D13DE014CE14__INCLUDED_)
