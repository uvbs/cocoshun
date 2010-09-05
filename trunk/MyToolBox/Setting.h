#if !defined(AFX_SETTING_H__)
#define AFX_SETTING_H__

struct HISTORY_SETTING
{
    BOOL bClearInternetTemp;
    BOOL bClearCookie;
    BOOL bClearBrowserAddress; //浏览器地址栏历史地址的清除
    BOOL bClearFormAutoComplete;
    BOOL bClearAutoPassword;
    BOOL bClearFavorite;
    BOOL bClearSysTempDir;
    BOOL bClearRecyclebin;
    BOOL bClearRun;
    BOOL bClearDocument;
    BOOL bClearLastLoginName;
    BOOL bClearFindFile;
    BOOL bClearFindComputer;
    BOOL bClearBrowseAddress; //清除浏览网址历史记录
    BOOL bClearTaskbarIconHistory;
};

struct WINDOW_SETTING
{
    int cx;
    int cy;
};

struct SETTING
{
    int nPageSelect ;
    HISTORY_SETTING HistorySetting;
    WINDOW_SETTING WindowSetting;
};

#endif