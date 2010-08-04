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
	m_FilterParam = NULL;

	Karaoke_Artist					=	_T("karaoke.tag('歌手',");
	Karaoke_Name					=	_T("karaoke.tag('歌名'");
	Karaoke_Add						=	_T("karaoke.add('");
	Karaoke_Flag                    =   _T("karaoke");
}

CLyricText::~CLyricText()
{

}

BOOL CLyricText::LoadLyric(LPCTSTR pszFileName)
{
	CTextBuffer::LoadFromFile(pszFileName);

// 	CString FileFormat = GetFormat();
// 
// 	if(FileFormat == "LRC")
// 	{
// 		
// 	}
	return TRUE;
}

void CLyricText::ProcessLine(CString &Line)
{
	TCHAR LRC_FLAG = _T(']');
	TCHAR Ti[] = _T("[ti:");
	TCHAR Ar[] = _T("[ar:");
	TCHAR Al[] = _T("[al:");
	TCHAR By[] = _T("[by:");

	int Pos;

	// 从LRC中提取歌曲信息(歌名、歌手、专辑、编辑人)
	if( ((Pos = Line.Find(Ti)) != -1) || ((Pos = Line.Find(Ar)) != -1) 
		|| ((Pos = Line.Find(Al)) != -1) || ((Pos = Line.Find(By)) != -1))
	{
		int PosNext = Line.ReverseFind(LRC_FLAG);
		CString Info = Line.Mid(Pos + 4, PosNext - (Pos + 4));
		if((Pos = Line.Find(Ti)) != -1)
		{
			m_LyricHeader.ti = Info;
		}
		if((Pos = Line.Find(Ar)) != -1)
		{
			m_LyricHeader.ar = Info;	
		}
		if((Pos = Line.Find(Al)) != -1)
		{
			m_LyricHeader.al = Info;	
		}
		if((Pos = Line.Find(By)) != -1)
		{
			m_LyricHeader.by = Info;
		}
		Line = _T("");
		return;
	}
	ProcessKsc(Line);

	if(m_FilterParam == NULL)
	{
		return;
	}

	// 过滤LRC时间标签
	if(m_FilterParam->bRemoveLrc)
	{
		Pos = Line.ReverseFind(LRC_FLAG);
		if(Pos !=-1)
		{
			int nCount = Line.GetLength() - Pos;
			if(nCount>0)
				Line = Line.Mid(Pos + 1, nCount);
		}
	}

	// 裁掉Ksc时间标签
	if(m_FilterParam->bRemoveKsc)
	{
		// 裁掉LRC时间标签
		Pos = Line.ReverseFind(LRC_FLAG);
		if(Pos !=-1)
		{
			int nCount = Line.GetLength() - Pos;
			if(nCount>0)
				Line = Line.Mid(Pos + 1, nCount);
		}
	}

	if(m_FilterParam->IsReplaceAble())
	{
		Line.Replace(m_FilterParam->strReplaceSrc,m_FilterParam->strReplaceTag);
	}

	if(m_FilterParam->bTrimSpace)
	{
		Line.TrimLeft();
		Line.TrimRight();
	}
}

CString CLyricText::GetFormat()
{
	CString FileName = m_FileName;

	FileName.MakeUpper();
	int Pos = FileName.ReverseFind('.');
	return FileName.Mid(Pos + 1, FileName.GetLength() - Pos);
}

void CLyricText::GetFilterText(CString &Text)
{
	if(m_Lines.size()==0)
	{
		Text =  _T("");
		return;
	}
	
	/************************************************************************/
	/*  内容:关于vector的遍历删除
		任何改变 vector 长度的操作都会使已存在的迭代器失效。例如，在调用 push_back 之后，
		就不能再信赖指向 vector 的迭代器的值了。
        一个原则：对vector只要做了删除或是增加动作，就要示迭代器已经无效，必须重新从
		vector对象获取新的迭代器的值，而不能用临时变量、后缀自增等方法                                                                     */
	/************************************************************************/
	vector<LineInfo>::iterator it;
	for(it=m_Lines.begin();it!=m_Lines.end();)
	{
		CString &Line = it->Text;
		ProcessLine(Line);

		if(m_FilterParam && m_FilterParam->bRemoveEmptyLine)
		{		
			int n = 0;
			for(;n<Line.GetLength() && Line.GetAt(n) == 0x20;n++);
			BOOL bAllSpace = (n == Line.GetLength()) ;
			
			if(Line.IsEmpty() || bAllSpace) 
			{
				m_Lines.erase(it);
				continue;
			}
		}
		it++;
		Text += Line + LINE_SEPARATOR;
	}

	// 过滤xml,html标签
// 	if(m_FilterParam && m_FilterParam->bRemoveHTMLXML)
// 	{
// 		CString StartFlag = _T(">");
// 		CString EndFlag = _T("</");
// 		int pos1 = Text.Find(StartFlag);
// 		if(pos1!=-1)
// 		{
// 			int pos2 = Text.Find(EndFlag);
// 			if(pos2 != -1)
// 			{
// 				Text = Text.Mid(pos1+1, pos2 - pos1 -1 );
// 			}
// 		}
// 	}
}

void CLyricText::ProcessKsc(CString &Line)
{
	//parse KSC file
	BOOL bStartAdd = FALSE;
	if(StartWith(Line,Karaoke_Name))
	{
		int pos = Line.ReverseFind(',');
		CString Title = Line.Mid(pos+3,Line.GetLength()- pos -6);
		m_LyricHeader.ti = Title;
		Line = _T("");
		return;
	}
	
	if(StartWith(Line,Karaoke_Artist))
	{
		int pos = Line.ReverseFind(',');
		CString Artist = Line.Mid(pos+2,Line.GetLength()- pos -3);
		m_LyricHeader.ar = Artist;
		Line = _T("");
		return;
	}
	
	if(m_FilterParam && m_FilterParam->bRemoveKsc)
	{

		if(StartWith(Line,Karaoke_Add))
		{
			GetAddLine(Line);
			return;
		}

		if(StartWith(Line,Karaoke_Flag))
		{
			Line = _T("");
			return;
		}
	}
	
}

BOOL CLyricText::StartWith(CString &string, CString &subString)
{
	return string.Find(subString) == 0;	
}

void CLyricText::GetAddLine(CString &Line)
{
	if(Line.GetLength() < 2) 
	{
		Line = _T("");
		return;
	}
	
	int len = Line.GetLength();
	CString Flag = _T("', '");
	int pos = Line.Find(Flag);
	int startPos;
	if(pos!=-1)
	{
		pos = Line.Find(Flag, pos+Flag.GetLength());
		if(pos!=-1)
		{
			startPos = pos + Flag.GetLength();
			pos = Line.Find(Flag, pos+Flag.GetLength());
			if(pos != -1)
			{
				Line = Line.Mid(startPos, pos-startPos);
			}
		}
	}
}