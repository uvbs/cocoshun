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

CKscToKmc::CKscToKmc()
{
	XMLHeader	= "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
	KMCStart	= "<kmc\n";
	XMLClose	= ">\n";
	KMCEnd		= "</kmc>\n";
	
	Karaoke_AnimateBorderColor		=	"karaoke.AnimateBorderColor";
	Karaoke_AnimateColor			=	"karaoke.AnimateColor";
	Karaoke_NormalBorderColor		=	"karaoke.NormalBorderColor";
	Karaoke_NormalColor				=	"karaoke.NormalColor";
	Karaoke_AnimateBorderThickness	=	"karaoke.AnimateBorderThickness";
	Karaoke_NormalBorderThickness	=	"karaoke.NormalBorderThickness";
	Karaoke_TimeOffset				=	"karaoke.TimeOffset";
	Karaoke_Font					=	"karaoke.Font(";
	Karaoke_Artist					=	"karaoke.tag('歌手',";
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
	
	//write KMC header
	byte utf8_Bom[] = {0xEF, 0xBB, 0xBF};
	fw.Write(utf8_Bom,3);
	fw.WriteString(XMLHeader);
	fw.WriteString(KMCStart);
	
	CString Title;
	CString Artist;
	CString Album;
	CString Author;
	CString Offset;
	CString Font;
	CString Align;
	CString Margin;
	CString Leading;
	CString Normal1;
	CString Normal2;
	CString Normal3;
	CString Animate1;
	CString Animate2;
	CString Animate3;
	CString Lyric;
	
	//parse KSC file
	CString Line;
	BOOL bStartAdd = FALSE;
	while(fr.ReadString(Line))
	{
		//if(!bStartAdd)
		{
			if(StartWith(Line,Karaoke_Name))
			{
				int pos = Line.ReverseFind(',');
				Title = Line.Mid(pos+3,Line.GetLength()- pos -6);
			}
			
			if(StartWith(Line,Karaoke_Artist))
			{
				int pos = Line.ReverseFind(',');
				Artist = Line.Mid(pos+2,Line.GetLength()- pos -3);
			}
			
			if(StartWith(Line,Karaoke_TimeOffset))
			{
				int pos = Line.ReverseFind('=') + 1;
				int count = Line.GetLength()- pos -1;
				Offset = Line.Mid(pos,count);
				Offset.TrimLeft();
				Offset.TrimRight();
			}
			
			if(StartWith(Line,Karaoke_Font))
			{
				int pos = Line.Find('(') + 1;
				int count = Line.GetLength() - pos - 2;
				Font = Line.Mid(pos, count);
				Font.Replace('\'',' ');
			}
			
			//color 
			if(StartWith(Line,Karaoke_AnimateBorderColor))
			{
				Animate1 = RgbToHex(Line);
			}
			if(StartWith(Line, Karaoke_AnimateColor))
			{
				Animate2 = RgbToHex(Line);
			}
			
			if(StartWith(Line, Karaoke_AnimateBorderThickness))
			{
				int pos = Line.ReverseFind('=') + 1 ;
				Animate3 = Line.Mid(pos, Line.GetLength() - pos -1);
			}
			
			if(StartWith(Line, Karaoke_NormalBorderColor	))
			{
				
				Normal1 = RgbToHex(Line);
			}
			if(StartWith(Line, Karaoke_NormalColor))
			{
				Normal2 = RgbToHex(Line);
			}
			
			if(StartWith(Line, Karaoke_NormalBorderThickness))
			{
				int pos = Line.ReverseFind('=') + 1 ;
				Normal3 = Line.Mid(pos, Line.GetLength() - pos -1);
			}
			
			
			if(StartWith(Line,Karaoke_Add))
			{
				Lyric += GetAddLine(Line, Lyric.IsEmpty());
// 				bStartAdd = TRUE;
// 				continue;
			}
		}
		
// 		if(bStartAdd )
// 		{
// 			if(!Line.IsEmpty())
// 				Lyric += GetAddLine(Line, FALSE);
// 		}
	}
	
	if(Title.IsEmpty())
	{
		Title = fr.GetFileName();
		Title = Title.Mid(0,Title.ReverseFind('.'));
	}

	if(!Title.IsEmpty())
		fw.WriteString(GBToUTF8("  title=\"" + Title + "\"\n"));

	fw.WriteString(GBToUTF8("  artist=\"\"\n"));
	fw.WriteString(GBToUTF8("  album=\"\"\n"));
	fw.WriteString(GBToUTF8("  author=\"\"\n"));

	if(!Offset.IsEmpty())
		fw.WriteString(GBToUTF8("  offset=\"" + Offset + "\"\n"));

	if(!Font.IsEmpty())
		fw.WriteString(GBToUTF8("  font=\"" + Font + ",false\"\n"));

	fw.WriteString(GBToUTF8("  align=\"left,right\"\n") );
	fw.WriteString(GBToUTF8("  margin=\"5\" \n" ));
	fw.WriteString(GBToUTF8("  leading=\"5\" \n" ));

	if(!Normal1.IsEmpty() || !Normal2.IsEmpty() || !Normal3.IsEmpty())
		fw.WriteString(GBToUTF8("  normal=\"" + Normal1 + "," + Normal2 + "," + Normal3 + "\"\n"));

	if(!Animate1.IsEmpty() || !Animate2.IsEmpty() || !Animate3.IsEmpty())
		fw.WriteString(GBToUTF8("  animate=\"" + Animate1 + "," + Animate2 + "," + Animate3 + "\"\n"));
	fw.WriteString(GBToUTF8(">\n\n" ));

	fw.WriteString(Lyric);
	fw.WriteString(KMCEnd);	

	fr.Close();
	fw.Close();
}

BOOL CKscToKmc::StartWith(CString &string, CString &subString)
{
	return string.Find(subString) == 0;
}

int  CKscToKmc::Split(const CString	&s, CStringArray &sa, char chSplitter)
{
	int   nLen=s.GetLength(),   nLastPos,   nPos; 
	bool   bContinue; 
	
	sa.RemoveAll(); 
	nLastPos=0; 
	do 
	{ 
		bContinue=false; 
		nPos   =   s.Find(chSplitter,   nLastPos); 
		if   (-1!=nPos) 
		{ 
			sa.Add(s.Mid(nLastPos,   nPos-nLastPos)); 
			nLastPos=nPos+1; 
			if   (nLastPos   !=   nLen)   bContinue=true; 
		} 
	}   while   (bContinue); 
	
	if   (nLastPos   !=   nLen) 
		sa.Add(s.Mid(nLastPos,   nLen-nLastPos)); 
}

CString CKscToKmc::RgbToHex(CString &Line)
{
	int pos = Line.ReverseFind('(') + 1;
	int count = Line.GetLength() - pos - 2;
	CString Values = Line.Mid(pos,count);
	CStringArray Arys;
	Split(Values,Arys,',');
	CString strResult="#";
	for(int i=0;i<Arys.GetSize();i++)
	{
		CString color = Arys.GetAt(i);
		color.TrimLeft();
		color.TrimRight();
		int v = atoi(color);
		color.Format("%.2X",v);
		strResult += color;
	}
	
	return strResult;
}

CString CKscToKmc::GetAddLine(CString &Line,BOOL bFirst)
{
	if(Line.GetLength() < 2) 
		return "";
	
	int len = Line.GetLength();
	CStringArray Arys;
	int pos1;
	int pos2;
	TCHAR cFlag = '\'';
	for(;;)
	{
		pos1 = Line.Find(cFlag);
		pos2 = Line.Find(cFlag, pos1 + 1);
		if(pos1 == -1 || pos2 ==-1 )
			break;

		CString seg = Line.Mid(pos1,pos2-pos1);
		Arys.Add(seg);
		Line = Line.Mid(pos2+1);
	}

 	CString addResult;
	CString strResult = "  <l t=\"";
	
	CString s1 = Arys.GetAt(0);
	s1.TrimLeft("'");
	s1.TrimRight("'");
	CString s2 = Arys.GetAt(1);
	s2.TrimLeft("'");
	s2.TrimRight("'");
	CString s3 = Arys.GetAt(2);
	s3.TrimLeft("'");
	s3.TrimRight("'");

	
	strResult+=s1+',';
	strResult+=s2+',';
	CString s4;
	for(int i=3;i<Arys.GetSize();i++)
	{
		s4 = Arys.GetAt(3);
		s4.TrimLeft("'");
		s4.TrimRight("'");
	}
	strResult+=s4;
	if(bFirst)
	{
		strResult+= "\" sec3=\"●";
	}
	strResult+="\">";
	strResult+=s3 + "</l>\n";


 	strResult = GBToUTF8(strResult.GetBuffer(0));
 	
	return strResult;
}

CString CKscToKmc::GBToUTF8(const char* str)
{
	std::string result;
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
	
	result = szRes;
	delete []strSrc;
	delete []szRes;

	CString string ;
	string.Format("%s",result.c_str());
	return string;
}


