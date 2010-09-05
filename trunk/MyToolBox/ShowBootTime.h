#if !defined(AFX_SHOWBOOTTIME_H__34873D74_C016_4827_AC97_620F5B4D5A5A__INCLUDED_)
#define AFX_SHOWBOOTTIME_H__34873D74_C016_4827_AC97_620F5B4D5A5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowBootTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowBootTime dialog

class CShowBootTime : public CDialog
{
// Construction
public:
	CShowBootTime(CWnd* pParent = NULL);   // standard constructor
    ~CShowBootTime();

// Dialog Data
	//{{AFX_DATA(CShowBootTime)
	enum { IDD = IDD_SHOWBOOTTIME_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowBootTime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CFont m_Font;
	// Generated message map functions
	//{{AFX_MSG(CShowBootTime)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_strTip;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWBOOTTIME_H__34873D74_C016_4827_AC97_620F5B4D5A5A__INCLUDED_)
