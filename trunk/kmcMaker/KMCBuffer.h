// KMCBuffer.h: interface for the CKMCBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KMCBUFFER_H__A9EC74B9_5F0E_4A2B_BAE2_DD90E3C2B58B__INCLUDED_)
#define AFX_KMCBUFFER_H__A9EC74B9_5F0E_4A2B_BAE2_DD90E3C2B58B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Lyric.h"

class CKmcBuffer  
{
public:
	void GetKmcLyric(CString &KmcLyric);
	CKmcBuffer(vector <LyricLine> *LyricLines);
	virtual ~CKmcBuffer();

private:
	vector <LyricLine> *m_LyricLines;
protected:
	CString DoubleToTime(double time);
};

#endif // !defined(AFX_KMCBUFFER_H__A9EC74B9_5F0E_4A2B_BAE2_DD90E3C2B58B__INCLUDED_)
