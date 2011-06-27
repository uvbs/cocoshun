#include "StdAfx.h"
#include "CustomBrowser.h"

CCustomBrowser::CCustomBrowser(void)
{
}

CCustomBrowser::~CCustomBrowser(void)
{
}

void CCustomBrowser::OnInitialUpdate()
{
	CLhpHtmlView::OnInitialUpdate();

	SetContextMenuMode(NoContextMenu);
}


void CCustomBrowser::OnNavigateComplete2( LPCTSTR strURL )
{

}

HRESULT CCustomBrowser::OnGetHostInfo( DOCHOSTUIINFO * pInfo )
{
	pInfo->cbSize = sizeof(DOCHOSTUIINFO);
	pInfo->dwFlags = DOCHOSTUIFLAG_DIALOG | 
		DOCHOSTUIFLAG_THEME  | 
		DOCHOSTUIFLAG_NO3DBORDER | 
		DOCHOSTUIFLAG_SCROLL_NO;
	pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT;

	return S_OK;

}