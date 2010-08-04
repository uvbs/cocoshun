// LyricText.h: interface for the CLyricText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LYRICTEXT_H__7495BEF2_571B_47CE_9518_FFCF425E4A06__INCLUDED_)
#define AFX_LYRICTEXT_H__7495BEF2_571B_47CE_9518_FFCF425E4A06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TextBuffer.h"

class CLyricText : public CTextBuffer
{
public:
	struct LyricHeader
	{
		CString ti;
		CString ar;
		CString al;
		CString by;
	};

	struct FilterParam
	{
		BOOL bTrimSpace;
		BOOL bRemoveEmptyLine;
		BOOL bRemoveHTMLXML;
		BOOL bRemoveKsc;
		BOOL bRemoveLrc;
		BOOL bReplace;
		CString strReplaceSrc;
		CString strReplaceTag;
		
		public :
		FilterParam(BOOL bTrimSpace,
			BOOL bRemoveEmptyLine,
			BOOL bRemoveHTMLXML,
			BOOL bRemoveKsc,
			BOOL bRemoveLrc,
			BOOL bReplace,
			CString strReplaceSrc,
			CString strReplaceTag)
		{
			this->bTrimSpace=bTrimSpace;
			this->bRemoveEmptyLine=bRemoveEmptyLine;
			this->bRemoveHTMLXML=bRemoveHTMLXML;
			this->bRemoveKsc=bRemoveKsc;
			this->bRemoveLrc=bRemoveLrc;
			this->bReplace=bReplace;
			this->strReplaceSrc=strReplaceSrc;
			this->strReplaceTag=strReplaceTag;
		}

		BOOL IsReplaceAble()
		{
			return !strReplaceSrc.IsEmpty();
		}
	};
	
	CString GetFormat();
	void ProcessLine(CString &Line);
	BOOL LoadLyric(LPCTSTR pszFileName);
	void GetFilterText(CString &Text);

	CLyricText();
	virtual ~CLyricText();

	LyricHeader *GetLyricHeader(){return &m_LyricHeader;};
	void SetFilterParam(FilterParam *filterParam){m_FilterParam = filterParam;};
protected:

private:
	BOOL StartWith(CString &string, CString &subString);
	void ProcessKsc(CString &Text);
	LyricHeader m_LyricHeader;
	FilterParam *m_FilterParam;

	CString Karaoke_Artist;
	CString Karaoke_Name;
	CString Karaoke_Add;
	CString Karaoke_Flag;

	void GetAddLine(CString &Line);
};

#endif // !defined(AFX_LYRICTEXT_H__7495BEF2_571B_47CE_9518_FFCF425E4A06__INCLUDED_)
