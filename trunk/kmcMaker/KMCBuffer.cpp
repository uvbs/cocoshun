// KMCBuffer.cpp: implementation of the CKMCBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KmcMaker.h"
#include "KMCBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKmcBuffer::CKmcBuffer(vector <LyricLine> *LyricLines)
{
	m_LyricLines = LyricLines;
}

CKmcBuffer::~CKmcBuffer()
{

}

void CKmcBuffer::GetKmcLyric(CString &KmcLyric)
{
	if(m_LyricLines == NULL)
	{
		KmcLyric = _T("");
		return;
	}

	CString xmlHeader = _T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n");
	CString kmcStart = _T("<kmc ti=\"\" ar=\"\" al=\"\" by=\"\">\r\n");
	CString kmcEnd = _T("</kmc>\r\n");
	CString lStart = _T("    <l t=\"");
	CString lClose = _T("\">");
	CString lEnd = _T("</l>\r\n");

	if(m_LyricHeader != NULL)
		kmcStart.Format(_T("<kmc ti=\"%s\" ar=\"%s\" al=\"%s\" by=\"%s\" offset=\"0\" duration=\"%s\">\r\n"),m_LyricHeader->ti,m_LyricHeader->ar,m_LyricHeader->al,m_LyricHeader->by,m_LyricHeader->duration);
	KmcLyric += xmlHeader;
	KmcLyric += kmcStart;
	for(int i=0; i<m_LyricLines->size();i++)
	{
		KmcLyric += lStart;

		CString Line;
		vector<LyricWord> Lws = m_LyricLines->at(i).LyricWords;
		Line.Format(_T("%s,%s,"), DoubleToTime(m_LyricLines->at(i).StartTime),DoubleToTime(m_LyricLines->at(i).EndTime));
		for(int j=0;j<Lws.size();j++)
		{
			LyricWord Lw = Lws.at(j);
			if(Lw.IsMarkedAll())
			{
				CString Delay;
				Delay.Format(_T("%.0f"), (Lw.EndTime - Lw.StartTime) * 1000);
				Line += Delay;
				if(j < Lws.size() -1)
				{
					Line += ',';
				}
			}
		}

		KmcLyric += Line;

		KmcLyric += lClose;
		KmcLyric += m_LyricLines->at(i).Line;
		KmcLyric += lEnd;
	}
	KmcLyric += kmcEnd;
}

CString CKmcBuffer::DoubleToTime(double time)
{
	CString FormmatedTime;
	int Minute = (int) (time / 60);
	int Second = (int) time % 60;
	int Millisecond = (int)(time * 1000) % 1000;

	FormmatedTime.Format(_T("%0.2d:%0.2d.%0.3d"),Minute, Second, Millisecond);
	return FormmatedTime;
}
