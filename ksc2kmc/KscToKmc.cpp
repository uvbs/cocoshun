// KscToKmc.cpp: implementation of the CKscToKmc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ksc2kmc.h"
#include "KscToKmc.h"
#include <string>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
byte CKscToKmc::UTF8_BOM[]= {0xEF, 0xBB, 0xBF, 0};

CKscToKmc::CKscToKmc(CString Author)
{
	m_Author = Author;
	XMLHeader	= "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
	KMCStart	= "<kmc ";
	KMCEnd		= "</kmc>\n";
// 	Karaoke_AnimateBorderColor		=	"karaoke.AnimateBorderColor";
// 	Karaoke_AnimateColor			=	"karaoke.AnimateColor";
// 	Karaoke_NormalBorderColor		=	"karaoke.NormalBorderColor";
// 	Karaoke_NormalColor				=	"karaoke.NormalColor";
// 	Karaoke_AnimateBorderThickness	=	"karaoke.AnimateBorderThickness";
// 	Karaoke_NormalBorderThickness	=	"karaoke.NormalBorderThickness";
	Karaoke_TimeOffset				=	"karaoke.TimeOffset";
// 	Karaoke_Font					=	"karaoke.Font(";
	Karaoke_Artist					=	"karaoke.tag('歌手'";
	Karaoke_Name					=	"karaoke.tag('歌名'";
	Karaoke_Add						=	"karaoke.add('";	
}

CKscToKmc::~CKscToKmc()
{
	
}

void CKscToKmc::convert(CString srcFile, CString tagFile)
{
	CStdioFile fr;
	CStdioFile fw;
	if(!fr.Open(srcFile,CFile::modeRead | CFile::typeText))
	{
		return;
	}
	if(!fw.Open(tagFile,CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		fr.Close();
		return;
	}
	
	XString Title;
	XString Artist;
	XString Album;
	XString Offset;
// 	XString Font;
// 	XString Align;
// 	XString Margin;
// 	XString Leading;
// 	XString Normal1;
// 	XString Normal2;
// 	XString Normal3;
// 	XString Animate1;
// 	XString Animate2;
// 	XString Animate3;
	XString Lyric;
	
	// get file buffer
//  	long flen = fr.GetLength();
//  	char *fbuf = new char[flen+1];
//  	fr.ReadHuge(fbuf,flen);
//  	fbuf[flen] = '\0';
// 	fr.SeekToBegin();

	// parse lines
	XString Line;
	char LINESP[] = "\n";
	while(fr.ReadString(Line))
	{
		if( Line.Find(Karaoke_Name) == 0)
		{
			Title = GetXStringElement(Line,'\'',3);
			continue;
		}
		
		if( Line.Find(Karaoke_Artist) == 0)
		{
			Artist = GetXStringElement(Line,'\'',3);
			continue;
		}
		
		if( Line.Find(Karaoke_TimeOffset) == 0 )
		{
			Offset = Line.FromTo(Line.ReverseFind('=') + 1,Line.ReverseFind(';') -1 );
			Offset = Offset.Trim();
			continue;
		}
		
// 		if(Line.Find(Karaoke_Font) == 0 )
// 		{
// 			Font = Line.FromTo(Line.Find('(')+1,Line.ReverseFind(')')-1);
// 			Font.ReplaceAll(' ','\'');
// 			continue;
// 		}
		
		//color 
// 		if(Line.Find(Karaoke_AnimateBorderColor) == 0 )
// 		{
// 			Animate1 = RgbToHex(Line);
// 			continue;
// 		}
// 		if(Line.Find(Karaoke_AnimateColor) == 0)
// 		{
// 			Animate2 = RgbToHex(Line);
// 			continue;
// 		}
// 		
// 		if(Line.Find(Karaoke_AnimateBorderThickness) == 0)
// 		{
// 			Animate3 = Line.FromTo(Line.ReverseFind('=') + 1,Line.ReverseFind(';') -1 );
// 			Animate3 = Animate3.Trim();
// 			continue;
// 		}
		
// 		if(Line.Find(Karaoke_NormalBorderColor) == 0 )
// 		{
// 			Normal1 = RgbToHex(Line);
// 			continue;
// 		}
// 		if(Line.Find(Karaoke_NormalColor) == 0 )
// 		{
// 			Normal2 = RgbToHex(Line);
// 			continue;
// 		}
// 		
// 		if(Line.Find(Karaoke_NormalBorderThickness) == 0 )
// 		{
// 			Normal3 = Line.FromTo(Line.ReverseFind('=') + 1,Line.ReverseFind(';') -1 );
// 			Normal3 = Normal3.Trim();
// 			continue;
// 		}
		
		if(Line.Find(Karaoke_Add) == 0 )
		{
			Lyric += GetLyric(Line);
			continue;
		}
	}

	CString KMC;
	//KMC header
	fw.WriteString(UTF8_BOM + XMLHeader +  KMCStart);
// 	KMC += UTF8_BOM;
// 	KMC += XMLHeader;
// 	KMC += KMCStart;
	
	if(Title.IsEmpty())
	{
		Title = fr.GetFileName();
		Title = Title.Mid(0,Title.ReverseFind('.'));
	}

	if(!Title.IsEmpty())
		KMC += "ti=\"" + Title + "\" ";

	KMC += "ar=\"\" ";
	KMC += "al=\"\" ";
	KMC += "by=\"" + m_Author + "\"";
	
	if(!Offset.IsEmpty())
		KMC += "offset=\"" + Offset + "\" ";

// 	if(!Font.IsEmpty())
// 		KMC += "  font=\"" + Font + ", false\"\n";

// 	KMC += "  align=\"left,right\"\n";
// 	KMC += "  margin=\"5\" \n" ;
// 	KMC += "  leading=\"5\" \n" ;

// 	if(!Normal1.IsEmpty() || !Normal2.IsEmpty() || !Normal3.IsEmpty())
// 		KMC += "  normal=\"" + Normal1 + "," + Normal2 + "," + Normal3 + "\"\n";
// 
// 	if(!Animate1.IsEmpty() || !Animate2.IsEmpty() || !Animate3.IsEmpty())
// 		KMC += "  animate=\"" + Animate1 + "," + Animate2 + "," + Animate3 + "\"\n";
	KMC += ">\n";

	KMC += Lyric;
	KMC += KMCEnd;

	fw.WriteString(GBToUTF8(KMC));

	//release memory
// 	if(fbuf != NULL)
// 	{
// 		delete []fbuf;
// 		fbuf = NULL;
// 	}

	//close file
	fr.Close();
	fw.Close();
}


CString CKscToKmc::RgbToHex(XString &Line)
{
	XString &Values = Line.FromTo(Line.ReverseFind('(') + 1,Line.ReverseFind(')') -1);
	Values.SetSeparator(',');
	CString strResult="#";
	XString color;
	int n = Values.Count(',') + 1;

	for(int i=0;i<n;i++)
	{
		color.Format("%.2X",Values.Element(i).Int());
		strResult += color;
	}
//	Values.RestoreSeparator();
	return strResult;
}

CString CKscToKmc::GetLyric(XString &Line)
{
	if(Line.GetLength() < 2) 
		return "";
	
	Line.SetSeparator('\'');

	CString strResult = "  <l t=\"";

	strResult += Line.Element(1) + ',';
	strResult += Line.Element(3) + ',';
	strResult += Line.Element(7) + '\"';
// 	if(bFirst)
// 	{
// 		strResult+= " sec3=\"●\"";
// 	}
	strResult += ">" + Line.Element(5)  +"</l>\n";

//	Line.RestoreSeparator();

	return strResult;
}

CString CKscToKmc::GBToUTF8(const char* str)
{
	//std::string result;
	WCHAR *strSrc;
	TCHAR *szRes;
	
	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i+1];
	MultiByteToWideChar(CP_ACP, 0, str, -1, strSrc, i);
	
	//获得临时变量的大小
	i = WideCharToMultiByte(CP_UTF8, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new TCHAR[i+1];
	int j=WideCharToMultiByte(CP_UTF8, 0, strSrc, -1, szRes, i, NULL, NULL);
	
	//result = szRes;

	CString string = szRes;
	delete []strSrc;
	delete []szRes;

//	string.Format("%s",result.c_str());
	return string;
}

XString CKscToKmc::GetXStringElement(XString &xString, char Spliter, int index)
{
	xString.SetSeparator(Spliter);
	XString string = xString.Element(index);
//	xString.RestoreSeparator();	
	return string;
}
