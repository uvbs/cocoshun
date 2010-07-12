// KscToKmc.h: interface for the CKscToKmc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KSCTOKMC_H__3E3BE752_2512_4E2E_A64B_D364E2BBF6C1__INCLUDED_)
#define AFX_KSCTOKMC_H__3E3BE752_2512_4E2E_A64B_D364E2BBF6C1__INCLUDED_

#include "XString.H"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKscToKmc  
{
public:
//	CKscToKmc();
	CKscToKmc(CString Author) ;
	void convert(CString srcFile,CString tagFile);
	virtual ~CKscToKmc();
private:
	CString GetLyric(XString &Line);
	CString RgbToHex(XString &Line);
	CString GBToUTF8(const char* str);

	CString XMLHeader;
	CString KMCStart;
	CString KMCEnd;
	
// 	CString Karaoke_AnimateBorderColor;
// 	CString Karaoke_AnimateColor;
// 	CString Karaoke_NormalBorderColor;
// 	CString Karaoke_NormalColor;
// 	CString Karaoke_AnimateBorderThickness;
// 	CString Karaoke_NormalBorderThickness;
	XString Karaoke_TimeOffset;
/*	CString Karaoke_Font;*/
	XString Karaoke_Artist;
	XString Karaoke_Name;
	XString Karaoke_Add;
	CString m_Author;
	static byte UTF8_BOM[4];
	
	XString GetXStringElement(XString &xString, char Spliter, int index);
};

#endif // !defined(AFX_KSCTOKMC_H__3E3BE752_2512_4E2E_A64B_D364E2BBF6C1__INCLUDED_)
