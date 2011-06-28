// NetRadioDlg.h : 头文件
//

#pragma once
#include "custombrowser.h"


// CNetRadioDlg 对话框
class CNetRadioDlg : public CDialog
{
// 构造
public:
	CNetRadioDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NETRADIO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	typedef struct {

		//
		// dwAccessType - INTERNET_OPEN_TYPE_DIRECT, INTERNET_OPEN_TYPE_PROXY, or
		// INTERNET_OPEN_TYPE_PRECONFIG (set only)
		//

		DWORD dwAccessType;

		//
		// lpszProxy - proxy server list
		//

		LPCSTR Proxy;

		//
		// lpszProxyBypass - proxy bypass list
		//

		LPCSTR lpszProxyBypass;
	} INTERNET_PROXY_INFO_ANSI, * LPINTERNET_PROXY_INFO_ANSI;

	typedef struct	{
		CString Proxy;
		CString FM;
	}CONFIG;

	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	void TurnDouban();
	void TurnBaidu();
	void ReadConfigFromIni(CONFIG *Config);
	void SetProxy( LPCSTR strProxy );
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 自定义浏览器控件
	CCustomBrowser m_Browser;
	afx_msg void OnBnClickedTest();
	afx_msg void OnBnClickedBaidu();
	afx_msg void OnBnClickedDouban();
	
};
