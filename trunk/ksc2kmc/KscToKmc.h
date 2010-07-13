// KscToKmc.h: interface for the CKscToKmc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KSCTOKMC_H__3E3BE752_2512_4E2E_A64B_D364E2BBF6C1__INCLUDED_)
#define AFX_KSCTOKMC_H__3E3BE752_2512_4E2E_A64B_D364E2BBF6C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKscToKmc  
{
public:
	void convert(CString srcFile,CString tagFile);
	CKscToKmc();
	virtual ~CKscToKmc();
private:
	CString GetAddLine(CString &Line, BOOL bFirst);
	CString RgbToHex(CString &Line);
	Split(const CString	&s, CStringArray &sa, char chSplitter);
	BOOL StartWith(CString &string, CString &subString);
	CString GBToUTF8(const char* str);

	CString XMLHeader;
	CString KMCStart;
	CString XMLClose;
	CString KMCEnd;
	
	CString Karaoke_AnimateBorderColor;
	CString Karaoke_AnimateColor;
	CString Karaoke_NormalBorderColor;
	CString Karaoke_NormalColor;
	CString Karaoke_AnimateBorderThickness;
	CString Karaoke_NormalBorderThickness;
	CString Karaoke_TimeOffset;
	CString Karaoke_Font;
	CString Karaoke_Artist;
	CString Karaoke_Name;
	CString Karaoke_Add;

};

#endif // !defined(AFX_KSCTOKMC_H__3E3BE752_2512_4E2E_A64B_D364E2BBF6C1__INCLUDED_)
