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

	CString lStart = "<l t=\"";
	CString lClose = "\">";
	CString lEnd = "</l>\n";

	KmcLyric += lStart;
		 
	for(int i=0; i<m_LyricLines->size();i++)
	{
		CString Line;
		vector<LyricWord> Lws = m_LyricLines->at(i).LyricWords;

		Line.Format("%s,%s,", DoubleToTime(m_LyricLines->at(i).StartTime),DoubleToTime(m_LyricLines->at(i).EndTime));

		for(int j=0;j<Lws.size();j++)
		{
			CString Delay;
			LyricWord Lw = Lws.at(j);
			if(Lw.IsMarked)
			{
				Delay.Format("%.0f", (Lw.EndTime - Lw.StartTime) * 1000);
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
}

CString CKmcBuffer::DoubleToTime(double time)
{
	CString FormmatedTime;
	int Minute = (int) (time / 60);
	int Second = (int) time % 60;
	int Millisecond = (int)(time * 1000) % 1000;

	FormmatedTime.Format("%0.2d:%0.2d.%0.3d",Minute, Second, Millisecond);
	return FormmatedTime;
}
