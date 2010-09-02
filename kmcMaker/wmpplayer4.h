#if !defined(AFX_WMPPLAYER4_H__867733D7_79DF_4120_852E_F9F4BE0DF40C__INCLUDED_)
#define AFX_WMPPLAYER4_H__867733D7_79DF_4120_852E_F9F4BE0DF40C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.
#include "wmpcontrols.h"

//����״̬��1=ֹͣ��2=��ͣ��3=���ţ�6=���ڻ��壬9=�������ӣ�10=׼������
#define PLAYSTATE_READY 10
#define PLAYSTATE_STOP 1
#define PLAYSTATE_PAUSE 2
#define PLAYSTATE_PLAY  3
#define PLAYSTATE_BUFFERING 6 //���ڻ���
#define PLAYSTATE_FINISHED 8  //���

// Dispatch interfaces referenced by this interface
class CWMPControls;
class CWMPMedia;
class CWMPError;

/////////////////////////////////////////////////////////////////////////////
// CWMPPlayer4 wrapper class

class CWMPPlayer4 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CWMPPlayer4)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x6bf52a52, 0x394a, 0x11d3, { 0xb1, 0x53, 0x0, 0xc0, 0x4f, 0x79, 0xfa, 0xa6 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:

// Operations
public:
	BOOL IsReady();
	BOOL IsStop();
	BOOL IsPause();
	BOOL IsPlay();
	void close();
	CString GetUrl();
	void SetUrl(LPCTSTR lpszNewValue);
	long GetOpenState();
	long GetPlayState();
	CWMPControls GetControls();
	LPDISPATCH GetSettings();
	CWMPMedia GetCurrentMedia();
	void SetCurrentMedia(LPDISPATCH newValue);
	LPDISPATCH GetMediaCollection();
	LPDISPATCH GetPlaylistCollection();
	CString GetVersionInfo();
	void launchURL(LPCTSTR bstrURL);
	LPDISPATCH GetNetwork();
	LPDISPATCH GetCurrentPlaylist();
	void SetCurrentPlaylist(LPDISPATCH newValue);
	LPDISPATCH GetCdromCollection();
	LPDISPATCH GetClosedCaption();
	BOOL GetIsOnline();
	CWMPError GetError();
	CString GetStatus();
	LPDISPATCH GetDvd();
	LPDISPATCH newPlaylist(LPCTSTR bstrName, LPCTSTR bstrURL);
	LPDISPATCH newMedia(LPCTSTR bstrURL);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	BOOL GetFullScreen();
	void SetFullScreen(BOOL bNewValue);
	BOOL GetEnableContextMenu();
	void SetEnableContextMenu(BOOL bNewValue);
	void SetUiMode(LPCTSTR lpszNewValue);
	CString GetUiMode();
	BOOL GetStretchToFit();
	void SetStretchToFit(BOOL bNewValue);
	BOOL GetWindowlessVideo();
	void SetWindowlessVideo(BOOL bNewValue);
	BOOL GetIsRemote();
	LPDISPATCH GetPlayerApplication();
	void openPlayer(LPCTSTR bstrURL);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WMPPLAYER4_H__867733D7_79DF_4120_852E_F9F4BE0DF40C__INCLUDED_)