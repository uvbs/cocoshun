#if !defined(__LYRIC_H__)
#define __LYRIC_H__
#include <afxtempl.h>

#include <vector>
using std::vector;

struct LyricWord
{
	BOOL IsLyric;
	BOOL IsChs;
	double StartTime;
	double EndTime;
	CString Word;
	COLORREF Color;
	BOOL MarkedStart;
	BOOL MarkedEnd;

	LyricWord()
	{
		IsLyric = TRUE;
		UnMark();
	}

	BOOL IsMarkedAll()
	{
		return MarkedStart && MarkedEnd;
	}

	BOOL IsMarkedStart()
	{
		return MarkedStart && !MarkedEnd;
	}

	void UnMark()
	{
		MarkedStart = FALSE;
		MarkedEnd = FALSE;
	}

	double DelayTime()
	{
		return EndTime - StartTime;
	}
};

struct LyricLine
{
	double StartTime;
	double EndTime;		
	CString Line;
	vector <LyricWord> LyricWords;
};


#endif