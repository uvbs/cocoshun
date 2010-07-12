// ShellUtil.h: interface for the CShellUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHELLUTIL_H__132DB68B_CF44_49BC_9B67_C7FB01238B28__INCLUDED_)
#define AFX_SHELLUTIL_H__132DB68B_CF44_49BC_9B67_C7FB01238B28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShellUtil  
{
public:
	CShellUtil();
	virtual ~CShellUtil();

public:
	static CString BrowseFolder(HWND hwnd);
};

#endif // !defined(AFX_SHELLUTIL_H__132DB68B_CF44_49BC_9B67_C7FB01238B28__INCLUDED_)
