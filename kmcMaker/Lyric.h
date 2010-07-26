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
	BOOL IsMarked;

	LyricWord()
	{
		IsLyric = TRUE;
		IsMarked = FALSE;
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

// 	LyricLine()
// 	{
// 		LyricWords.clear();
// 	}
};


#endif