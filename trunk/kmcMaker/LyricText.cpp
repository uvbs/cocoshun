// LyricText.cpp: implementation of the CLyricText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KmcMaker.h"
#include "LyricText.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLyricText::CLyricText()
{

}

CLyricText::~CLyricText()
{

}

BOOL CLyricText::LoadLyric(LPCTSTR pszFileName)
{
	CTextBuffer::LoadFromFile(pszFileName);

	CString FileFormat = GetFormat();

	if(FileFormat == "LRC")
	{
		SplitLRC();
	}

	return TRUE;
}

void CLyricText::SplitLRC()
{
	TCHAR LRC_FLAG = ']';
	TCHAR *Ti = _T("[ti:");
	TCHAR *Ar = _T("[ar:");
	TCHAR *Al = _T("[al:");

	for(int i=0;i<m_Lines.GetSize();i++)
	{
		LineInfo &Li = m_Lines.GetAt(i);
		CString &Text = Li.Text;

		if(Text.IsEmpty()) continue;

		int Pos;
		if( ((Pos = Text.Find(Ti)) != -1) || ((Pos = Text.Find(Ar)) != -1) || ((Pos = Text.Find(Al)) != -1) )
		{
			int PosNext = Text.ReverseFind(LRC_FLAG);
			Text = Text.Mid(Pos + 4, PosNext - (Pos + 4));
			m_Lines.SetAt(i, Li);
			continue;
		}


		Pos = Text.ReverseFind(LRC_FLAG);
		if(Pos !=-1)
		{
			Text = Text.Mid(Pos + 1, Text.GetAllocLength() - Pos);
			Text.TrimLeft();
			Text.TrimRight();
		}

		if(Text.IsEmpty()) m_Lines.RemoveAt(i);
		m_Lines.SetAt(i, Li);
	}
}

CString CLyricText::GetFormat()
{
	CString FileName = m_FileName;

	FileName.MakeUpper();
	int Pos = FileName.ReverseFind('.');
	return FileName.Mid(Pos + 1, FileName.GetLength() - Pos);
}
