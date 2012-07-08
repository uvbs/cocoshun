// ShellUtil.h: interface for the CShellUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHELLUTIL_H__132DB68B_CF44_49BC_9B67_C7FB01238B28__INCLUDED_)
#define AFX_SHELLUTIL_H__132DB68B_CF44_49BC_9B67_C7FB01238B28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

static TCHAR m_DefaultDir[MAX_PATH];
class CShellUtil  
{
public:
	CShellUtil();
	virtual ~CShellUtil();

public:
	static CString BrowseFolder(HWND hwnd, LPCTSTR defaultDir = NULL);
	static int CALLBACK BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData);
};

#endif // !defined(AFX_SHELLUTIL_H__132DB68B_CF44_49BC_9B67_C7FB01238B28__INCLUDED_)
