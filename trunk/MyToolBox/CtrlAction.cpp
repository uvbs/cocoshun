// CtrlAction.cpp: implementation of the CCtrlAction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyToolBox.h"
#include "CtrlAction.h"
#include "util/Registry.h"
#include <malloc.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCtrlAction::CCtrlAction()
{

}

CCtrlAction::~CCtrlAction()
{

}

void CCtrlAction::Process(UINT ID,BOOL bGetValue)
{
    CTRL_OPERATION *co = GetCtrlOperationByID(ID);
    if(co == NULL) return;

    switch(co->CtrlType)
    {
        case CHECKBOX:
                ProcessCheckbox(ID,co,bGetValue);
                break;

    }
}
void CCtrlAction::ProcessCheckbox(UINT ID,CTRL_OPERATION *co,BOOL bGetValue)
{
    CButton *pCheckBox = (CButton *) m_hWnd->GetDlgItem(ID);
    
    REG_OPERATION regOper;
    if(bGetValue)
    {
        regOper = co->Query;
    }else
    {
        if(pCheckBox->GetCheck())
        {
            regOper = co->Action;
        }else
        {
            regOper = co->Revert;
        }
    }

    
    CRegistry regstry;
    regstry.SetRootKey(regOper.OperParam.Root);
    regstry.SetKey(regOper.OperParam.Path,TRUE);
    VALUE_TYPE valueType = regOper.OperParam.ValueType;
    switch(regOper.OperType)
    {
        case Write:
            if(valueType == DW)
            {
                regstry.WriteDword(regOper.OperParam.Key,regOper.OperParam.dwValue);
            }else if(valueType == STRING)
            {
                regstry.WriteString(regOper.OperParam.Key,regOper.OperParam.strValue);
            }
            break;
        case Remove:
            regstry.DeleteKey(regOper.OperParam.Key);
            break;
        case Query:
            REG_OPERATION regOperAction = co->Action;
            REG_OPERATION regOperRevert = co->Revert;
            if(valueType == DW)
            {
                DWORD actionValue = regOperAction.OperParam.dwValue;
                DWORD revertValue = regOperRevert.OperParam.dwValue;
                DWORD dw = regstry.ReadDword(regOper.OperParam.Key,regOperRevert.OperParam.dwValue);
                if(dw == actionValue)
                {
                    pCheckBox->SetCheck(TRUE);
                }else if(dw = revertValue)
                {
                    pCheckBox->SetCheck(FALSE);
                }

            }else if(valueType == STRING)
            {
                CString actionValue = regOperAction.OperParam.strValue;
                CString revertValue = regOperRevert.OperParam.strValue;
                CString str = regstry.ReadString(regOper.OperParam.Key,revertValue);
                if(str == actionValue)
                {
                    pCheckBox->SetCheck(TRUE);
                }else if(str = revertValue)
                {
                    pCheckBox->SetCheck(FALSE);
                }            
            }
            break;
    }
}
CTRL_OPERATION * CCtrlAction::GetCtrlOperationByID( UINT ID )
{
    for(int i=0;;i++)
    {
        CTRL_OPERATION *co = &m_ctlOper[i];
        
        if(co->Action.OperParam.Key == NULL)
        {
            break;
        }
        if(co->CtrlID == ID)
        {
            return co;
        }
    }
    return NULL;
}