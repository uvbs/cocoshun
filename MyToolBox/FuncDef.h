// FuncDef.h: interface for the FuncDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCDEF_H__D2FC073C_F1DC_4F80_BA13_69C6FE53C859__INCLUDED_)
#define AFX_FUNCDEF_H__D2FC073C_F1DC_4F80_BA13_69C6FE53C859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/************************************************************************/
/*  注册表操作定义                                                      */
/************************************************************************/
//操作类型
enum OPERATION_TYPE
{
    Query,		//查询
    Write,		//写操作
    Remove		//删除操作
};

// 值类型
enum VALUE_TYPE
{
    DW,
    STRING
};

// 控件类型
enum CTRL_TYPE
{
    CHECKBOX,
    BUTTON
};

//操作参数
struct OPER_PARAM
{
    HKEY Root;
    LPCTSTR Path;
    LPCTSTR Key;
    VALUE_TYPE ValueType;
    DWORD dwValue;
    LPCTSTR strValue;
};

struct REG_OPERATION
{
    OPERATION_TYPE OperType;
    OPER_PARAM OperParam;
};

struct CTRL_OPERATION
{
    UINT CtrlID;
    CTRL_TYPE CtrlType;
    REG_OPERATION Action;	    //动作
    REG_OPERATION Revert;	    //恢复动作
    REG_OPERATION Query;	    //查询操作
};

enum CRUD
{
    ACTION,
    REVERT,
    GETVALUE
};

#endif // !defined(AFX_FUNCDEF_H__D2FC073C_F1DC_4F80_BA13_69C6FE53C859__INCLUDED_)
