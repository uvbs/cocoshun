#if !defined(__LYRIC_H__)
#define __LYRIC_H__
#include <afxtempl.h>

#include <vector>
using std::vector;

struct LyricWord
{
	BOOL IsLyric;
	BOOL IsChs;
	double DelayTime;
	CString Word;
	COLORREF Color;
	BOOL IsMarked;
	
	LyricWord()
	{
		IsLyric = TRUE;
		IsMarked = FALSE;
	}
};

struct LyricLine
{
	double StartTime;
	double EndTime;		
	CString Line;
	vector <LyricWord> LyricWords;

	LyricLine()
	{
		LyricWords.clear();
	}
};


#endif