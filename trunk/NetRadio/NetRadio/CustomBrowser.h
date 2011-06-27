#pragma once
#include "Common/HtmlView/LhpHtmlView.h"

class CCustomBrowser :
	public CLhpHtmlView
{
public:
	CCustomBrowser(void);
	~CCustomBrowser(void);

protected:
	virtual void OnInitialUpdate();


	virtual void OnNavigateComplete2(LPCTSTR strURL);

	virtual HRESULT OnGetHostInfo(DOCHOSTUIINFO * pInfo);
};
