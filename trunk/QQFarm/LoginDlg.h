#if !defined(AFX_LOGINDLG_H__AB8B6F45_E8A3_4E56_9586_D718D92104CF__INCLUDED_)
#define AFX_LOGINDLG_H__AB8B6F45_E8A3_4E56_9586_D718D92104CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

class CLoginDlg : public CDialog
{
// Construction
public:

	CLoginDlg(CWnd* pParent = NULL);   // standard constructor
    ~CLoginDlg();
// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_LOGINDLG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    BOOL InitPic();
    
    IPicture* m_pPic;
    CSize m_Size;
    long m_nPicWidth;
    long m_nPicHeight;
	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	virtual void OnOK();
    afx_msg	BOOL Login();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__AB8B6F45_E8A3_4E56_9586_D718D92104CF__INCLUDED_)
