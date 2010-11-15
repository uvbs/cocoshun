// Util.cpp: implementation of the CUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "QQFarm.h"
#include "Util.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUtil::CUtil()
{

}

CUtil::~CUtil()
{

}

CString CUtil::binl2hex(int C[]) {
    CString B ="0123456789ABCDEF";
    CString D = "";
    for (int i = 0; i < sizeof(C) * 4; i++) {
        D += B.GetAt(C[i >> 2] >> i % 4 * 8 + 4 & 15) + B.GetAt(C[i >> 2] >> i % 4 * 8 & 15);
    }
    return D;
}

int CUtil::safe_add(int A, int D) {
    int C = (A & 65535) + (D & 65535);
    int B = (A >> 16) + (D >> 16) + (C >> 16);
    return (B << 16) | (C & 65535);
}

int CUtil::md5_cmn(int F, int C, int B, int A, int E, int D) {
    return safe_add(bit_rol(safe_add(safe_add(C, F), safe_add(A, D)), E), B);
}

int CUtil::md5_ff(int C, int B, int G, int F, int A, int E, int D) {
    return md5_cmn((B & G) | ((~B) & F), C, B, A, E, D);
}

int CUtil::md5_gg(int C, int B, int G, int F, int A, int E, int D) {
    return md5_cmn((B & F) | (G & (~F)), C, B, A, E, D);
}

int CUtil::md5_hh(int C, int B, int G, int F, int A, int E, int D) {
    return md5_cmn(B ^ G ^ F, C, B, A, E, D);
}

int CUtil::md5_ii(int C, int B, int G, int F, int A, int E, int D){
    return md5_cmn(G ^ (B | (~F)), C, B, A, E, D);
}

int CUtil::bit_rol(int A, int B) {
//	 return (A << B) | (A >>> (32 - B));
	return (A << B) | ((unsigned int)A >> (32 - B));
}

CString CUtil::binl2str(CString C) {
    CString D = "";
    int A = (1 << 8) - 1;
    for (int B = 0; B < C.GetLength() * 32; B += 8) {
//        D += (C[B >> 5] >>> (B % 32)) & A;
		D += ((unsigned int)C[B >> 5] >> (B % 32)) & A;
    }
    return D;
}

void CUtil::core_md5(int K[], int F,int ary[]) {
    K[F >> 5] |= 128 << ((F) % 32);
    K[(((F + 64) >> 9) << 4) + 14] = F;
    int J = 1732584193;
    int I = -271733879;
    int H = -1732584194;
    int G = 271733878;
	int len = sizeofAry(K);
    for (int C = 0; C < len; C += 16) {
        int E = J;
        int D = I;
        int B = H;
        int A = G;
        J = md5_ff(J, I, H, G, K[C + 0], 7, -680876936);
        G = md5_ff(G, J, I, H, K[C + 1], 12, -389564586);
        H = md5_ff(H, G, J, I, K[C + 2], 17, 606105819);
        I = md5_ff(I, H, G, J, K[C + 3], 22, -1044525330);
        J = md5_ff(J, I, H, G, K[C + 4], 7, -176418897);
        G = md5_ff(G, J, I, H, K[C + 5], 12, 1200080426);
        H = md5_ff(H, G, J, I, K[C + 6], 17, -1473231341);
        I = md5_ff(I, H, G, J, K[C + 7], 22, -45705983);
        J = md5_ff(J, I, H, G, K[C + 8], 7, 1770035416);
        G = md5_ff(G, J, I, H, K[C + 9], 12, -1958414417);
        H = md5_ff(H, G, J, I, K[C + 10], 17, -42063);
        I = md5_ff(I, H, G, J, K[C + 11], 22, -1990404162);
        J = md5_ff(J, I, H, G, K[C + 12], 7, 1804603682);
        G = md5_ff(G, J, I, H, K[C + 13], 12, -40341101);
        H = md5_ff(H, G, J, I, K[C + 14], 17, -1502002290);
        I = md5_ff(I, H, G, J, K[C + 15], 22, 1236535329);
        J = md5_gg(J, I, H, G, K[C + 1], 5, -165796510);
        G = md5_gg(G, J, I, H, K[C + 6], 9, -1069501632);
        H = md5_gg(H, G, J, I, K[C + 11], 14, 643717713);
        I = md5_gg(I, H, G, J, K[C + 0], 20, -373897302);
        J = md5_gg(J, I, H, G, K[C + 5], 5, -701558691);
        G = md5_gg(G, J, I, H, K[C + 10], 9, 38016083);
        H = md5_gg(H, G, J, I, K[C + 15], 14, -660478335);
        I = md5_gg(I, H, G, J, K[C + 4], 20, -405537848);
        J = md5_gg(J, I, H, G, K[C + 9], 5, 568446438);
        G = md5_gg(G, J, I, H, K[C + 14], 9, -1019803690);
        H = md5_gg(H, G, J, I, K[C + 3], 14, -187363961);
        I = md5_gg(I, H, G, J, K[C + 8], 20, 1163531501);
        J = md5_gg(J, I, H, G, K[C + 13], 5, -1444681467);
        G = md5_gg(G, J, I, H, K[C + 2], 9, -51403784);
        H = md5_gg(H, G, J, I, K[C + 7], 14, 1735328473);
        I = md5_gg(I, H, G, J, K[C + 12], 20, -1926607734);
        J = md5_hh(J, I, H, G, K[C + 5], 4, -378558);
        G = md5_hh(G, J, I, H, K[C + 8], 11, -2022574463);
        H = md5_hh(H, G, J, I, K[C + 11], 16, 1839030562);
        I = md5_hh(I, H, G, J, K[C + 14], 23, -35309556);
        J = md5_hh(J, I, H, G, K[C + 1], 4, -1530992060);
        G = md5_hh(G, J, I, H, K[C + 4], 11, 1272893353);
        H = md5_hh(H, G, J, I, K[C + 7], 16, -155497632);
        I = md5_hh(I, H, G, J, K[C + 10], 23, -1094730640);
        J = md5_hh(J, I, H, G, K[C + 13], 4, 681279174);
        G = md5_hh(G, J, I, H, K[C + 0], 11, -358537222);
        H = md5_hh(H, G, J, I, K[C + 3], 16, -722521979);
        I = md5_hh(I, H, G, J, K[C + 6], 23, 76029189);
        J = md5_hh(J, I, H, G, K[C + 9], 4, -640364487);
        G = md5_hh(G, J, I, H, K[C + 12], 11, -421815835);
        H = md5_hh(H, G, J, I, K[C + 15], 16, 530742520);
        I = md5_hh(I, H, G, J, K[C + 2], 23, -995338651);
        J = md5_ii(J, I, H, G, K[C + 0], 6, -198630844);
        G = md5_ii(G, J, I, H, K[C + 7], 10, 1126891415);
        H = md5_ii(H, G, J, I, K[C + 14], 15, -1416354905);
        I = md5_ii(I, H, G, J, K[C + 5], 21, -57434055);
        J = md5_ii(J, I, H, G, K[C + 12], 6, 1700485571);
        G = md5_ii(G, J, I, H, K[C + 3], 10, -1894986606);
        H = md5_ii(H, G, J, I, K[C + 10], 15, -1051523);
        I = md5_ii(I, H, G, J, K[C + 1], 21, -2054922799);
        J = md5_ii(J, I, H, G, K[C + 8], 6, 1873313359);
        G = md5_ii(G, J, I, H, K[C + 15], 10, -30611744);
        H = md5_ii(H, G, J, I, K[C + 6], 15, -1560198380);
        I = md5_ii(I, H, G, J, K[C + 13], 21, 1309151649);
        J = md5_ii(J, I, H, G, K[C + 4], 6, -145523070);
        G = md5_ii(G, J, I, H, K[C + 11], 10, -1120210379);
        H = md5_ii(H, G, J, I, K[C + 2], 15, 718787259);
        I = md5_ii(I, H, G, J, K[C + 9], 21, -343485551);
        J = safe_add(J, E);
        I = safe_add(I, D);
        H = safe_add(H, B);
        G = safe_add(G, A);
    }
	ary[0] = J;
	ary[1] = I;
	ary[2] = H;
	ary[3] = G;
//     if (mode == 16) {
//         return Array(I, H)
//     } else {
//        return Array(J, I, H, G)
/*		}*/
}

void CUtil::str2binl(CString D, int C[]) {
//	int C[] = new int[D.GetLength()];
	int A = (1 << 8) - 1;
	for (int B = 0; B < D.GetLength() * 8; B += 8) {
		C[B >> 5] |= (D.GetAt(B / 8) & A) << (B % 32);
	}
//	return C;
} 
CString CUtil::md5_3(CString B) 
{
	int Ary1[100] = {0};
	int Ary2[100] = {0};
	str2binl(B,Ary1);
	
    core_md5(Ary1, B.GetLength() * 8,Ary2);
    core_md5(Ary2, 16 * 8,Ary2);
    core_md5(Ary2, 16 * 8,Ary2);
    return binl2hex(Ary1);
}

CString CUtil::hex_md5(CString &A) {
	int ary1[200] = {0};
	int ary2[200] = {0};
	str2binl(A,ary2);
	core_md5(ary2, A.GetLength() * 8, ary1);

	return binl2hex(ary1);
} 

CString CUtil::md5( CString A )
{
	return hex_md5(A);
}

int CUtil::sizeofAry( int ary[] )
{
	int size = 0;
	for(;ary[size]!=0;size++);
	return size;
}
// CString CUtil::binl2str(CString &C) {
//     CString D = "";
//     CString A = (1 << 8) - 1;
//     for (int B = 0; B < C.GetLength() * 32; B += 8) {
//         D += String.fromCharCode(C[B >> 5] >>> B % 32 & A);
//     }
//     return D;
// }

