// Util.h: interface for the CUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTIL_H__49F7E68E_BC69_4F7B_BB60_30056FE39D88__INCLUDED_)
#define AFX_UTIL_H__49F7E68E_BC69_4F7B_BB60_30056FE39D88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUtil  
{
public:
	CUtil();
	virtual ~CUtil();
	CString md5_3(CString B);
	CString md5(CString A);
private:
	CString binl2hex(int C[]);
	int safe_add(int A, int D);
	int md5_cmn(int F, int C, int B, int A, int E, int D);
	int md5_ff(int C, int B, int G, int F, int A, int E, int D);
	int md5_gg(int C, int B, int G, int F, int A, int E, int D);
	int md5_hh(int C, int B, int G, int F, int A, int E, int D);
	int md5_ii(int C, int B, int G, int F, int A, int E, int D);
	int bit_rol(int A, int B);
	CString binl2str(CString C);
	void core_md5(int K[], int F, int ary[]);
	void str2binl(CString D, int C[]);
	CString hex_md5(CString &A);
	int sizeofAry(int ary[]);
};

#endif // !defined(AFX_UTIL_H__49F7E68E_BC69_4F7B_BB60_30056FE39D88__INCLUDED_)
