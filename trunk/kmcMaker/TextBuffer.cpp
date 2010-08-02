// TextBuffer.cpp: implementation of the CTextBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KmcMaker.h"
#include "TextBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextBuffer::CTextBuffer()
{
	m_FileName = _T("");
}

CTextBuffer::~CTextBuffer()
{

}

BOOL CTextBuffer::LoadFromFile(LPCTSTR pszFileName)
{
	CTextFileRead FileReader(pszFileName);
	
	if(! FileReader.IsOpen())
	{
		FileReader.Close();
		return FALSE;
	}
	m_Lines.RemoveAll();
	m_FileName = pszFileName;

	m_Lines.SetSize(0,4096);
	CString Line;
	int LineNum = 0;
	while(FileReader.ReadLine(Line))
	{
		LineInfo Li;
		Li.Num = LineNum++;
		Li.Text = Line;

		m_Lines.Add(Li);
	}
	FileReader.Close();

	return TRUE;
}

BOOL CTextBuffer::SaveToFile(LPCTSTR pszFileName)
{
	CTextFileWrite FileWriter(pszFileName);
	
	if(! FileWriter.IsOpen())
	{
		return FALSE;
	}
	
	CString Line;
	for(int i=0; i<m_Lines.GetSize();i++)
	{
		LineInfo Li = m_Lines.GetAt(i);
		FileWriter.Write(Li.Text + LINE_SEPARATOR);
	}

	FileWriter.Close();
	return TRUE;
}

CString CTextBuffer::GetText()
{
	if(m_Lines.GetSize()==0)
	{
		return _T("");
	}

	CString Text;
	for(int i=0;i<m_Lines.GetSize();i++)
	{
		Text += m_Lines.GetAt(i).Text + LINE_SEPARATOR;
	}

	return Text;
}