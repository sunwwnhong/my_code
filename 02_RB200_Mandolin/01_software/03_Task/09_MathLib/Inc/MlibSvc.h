/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
*
* File Name          : MlibSvc.h
*
* Version            : V0.1
* Date               : 2024
***********************************************************************************************/
 
#include "Main.h"
#ifndef __MLIBSVC_H__
#define __MLIBSVC_H__
 
#define MLIBSVC		1
 
extern	const	UCHAR	MlibAsciiTbl[ ];
extern	const	UCHAR	MlibEvenAsciiTbl[ ];
 
/* 基本数字运算宏 */
#define MlibABS( u )	(((u)>=0) ? (u) : -(u))
#define MlibMAX( a, b )	(((a)>(b)) ? (a) : (b))
#define MlibMIN( a, b )	(((a)<(b)) ? (a) : (b))
#define	MlibLIMITUL( u, ulim, llim )	(((u)>=(ulim))? (ulim) : (((u)<=(llim))? (llim) : (u)))

/* 64位比较宏：GT(a>b),LT(a<b),GTE(a>=b),LTE(a<=b) */
#define	MlibEQ64( a, b )	( (a[1] == b[1]) && (a[0] == b[0]) )
#define	MlibGT64( a, b )	( (a[1] >  b[1]) || ((a[1] == b[1])&&((ULONG)a[0] >  (ULONG)b[0])) )
#define	MlibLT64( a, b )	( (a[1] <  b[1]) || ((a[1] == b[1])&&((ULONG)a[0] <  (ULONG)b[0])) )
#define	MlibGTE64( a, b )	( (a[1] >  b[1]) || ((a[1] == b[1])&&((ULONG)a[0] >= (ULONG)b[0])) )
#define	MlibLTE64( a, b )	( (a[1] <  b[1]) || ((a[1] == b[1])&&((ULONG)a[0] <= (ULONG)b[0])) )

/* 64位限幅宏 */
#define	MlibUPPERLMT64( x, ulim )	if( MlibGT64( x, ulim ) ){ x[0] = ulim[0]; x[1] = ulim[1];}
#define	MlibLOWERLMT64( x, llim )	if( MlibLT64( x, llim ) ){ x[0] = llim[0]; x[1] = llim[1];}
 
extern	const	SHORT	MlibFastSinTbl[1024];
/* 正余弦运算宏 */
#define	MlibFASTSINS16( a )	(MlibFastSinTbl[(a)&0x3FF])
#define MlibFASTCOSS16( a ) (MlibFastSinTbl[(a+256)&0x3FF])
extern LONG	MlibAtan16( SHORT a, SHORT b );
LONG	MlibCheckPowerOf2(
			ULONG	x 			);
 
/* 存储器复制函数 */
void    MlibCopyByteMemory(         //字节存储器复制
            UCHAR   *pSrcMem,               //复制到
            UCHAR   *pDesMem,               //复制源
            LONG    ByteNum     );
void    MlibCopyLongMemory(         //长存储器复制
            ULONG   *pSrcMem,               //复制到
            ULONG   *pDesMem,               //复制源
            LONG    LwdNum      );          //复制源

#define	MlibFastCopyMem01(ps,pd,i)	pd[i] = ps[i];
#define	MlibFastCopyMem02(ps,pd,i)	pd[i] = ps[i]; pd[i+1] = ps[i+1];
#define	MlibFastCopyMem03(ps,pd,i)	MlibFastCopyMem02(ps,pd,i); MlibFastCopyMem01(ps,pd,i+ 2);
#define	MlibFastCopyMem04(ps,pd,i)	MlibFastCopyMem02(ps,pd,i); MlibFastCopyMem02(ps,pd,i+ 2);
#define	MlibFastCopyMem05(ps,pd,i)	MlibFastCopyMem04(ps,pd,i); MlibFastCopyMem01(ps,pd,i+ 4);
#define	MlibFastCopyMem06(ps,pd,i)	MlibFastCopyMem04(ps,pd,i); MlibFastCopyMem02(ps,pd,i+ 4);
#define	MlibFastCopyMem07(ps,pd,i)	MlibFastCopyMem04(ps,pd,i); MlibFastCopyMem03(ps,pd,i+ 4);
#define	MlibFastCopyMem08(ps,pd,i)	MlibFastCopyMem04(ps,pd,i); MlibFastCopyMem04(ps,pd,i+ 4);
#define	MlibFastCopyMem09(ps,pd,i)	MlibFastCopyMem08(ps,pd,i); MlibFastCopyMem01(ps,pd,i+ 8);
#define	MlibFastCopyMem10(ps,pd,i)	MlibFastCopyMem08(ps,pd,i); MlibFastCopyMem02(ps,pd,i+ 8);
#define	MlibFastCopyMem11(ps,pd,i)	MlibFastCopyMem08(ps,pd,i); MlibFastCopyMem03(ps,pd,i+ 8);
#define	MlibFastCopyMem12(ps,pd,i)	MlibFastCopyMem08(ps,pd,i); MlibFastCopyMem04(ps,pd,i+ 8);
#define	MlibFastCopyMem13(ps,pd,i)	MlibFastCopyMem08(ps,pd,i); MlibFastCopyMem05(ps,pd,i+ 8);
#define	MlibFastCopyMem14(ps,pd,i)	MlibFastCopyMem08(ps,pd,i); MlibFastCopyMem06(ps,pd,i+ 8);
#define	MlibFastCopyMem15(ps,pd,i)	MlibFastCopyMem08(ps,pd,i); MlibFastCopyMem07(ps,pd,i+ 8);
#define	MlibFastCopyMem16(ps,pd,i)	MlibFastCopyMem08(ps,pd,i); MlibFastCopyMem08(ps,pd,i+ 8);
#define	MlibFastCopyMem17(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem01(ps,pd,i+16);
#define	MlibFastCopyMem18(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem02(ps,pd,i+16);
#define	MlibFastCopyMem19(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem03(ps,pd,i+16);
#define	MlibFastCopyMem20(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem04(ps,pd,i+16);
#define	MlibFastCopyMem21(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem05(ps,pd,i+16);
#define	MlibFastCopyMem22(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem06(ps,pd,i+16);
#define	MlibFastCopyMem23(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem07(ps,pd,i+16);
#define	MlibFastCopyMem24(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem08(ps,pd,i+16);
#define	MlibFastCopyMem25(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem09(ps,pd,i+16);
#define	MlibFastCopyMem26(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem10(ps,pd,i+16);
#define	MlibFastCopyMem27(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem11(ps,pd,i+16);
#define	MlibFastCopyMem28(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem12(ps,pd,i+16);
#define	MlibFastCopyMem29(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem13(ps,pd,i+16);
#define	MlibFastCopyMem30(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem14(ps,pd,i+16);
#define	MlibFastCopyMem31(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem15(ps,pd,i+16);
#define	MlibFastCopyMem32(ps,pd,i)	MlibFastCopyMem16(ps,pd,i); MlibFastCopyMem16(ps,pd,i+16);
#define	MlibFastCopyLongMemory( pSrc, pDes, LwdNum )\
		if(      (LwdNum) ==  1 ){ MlibFastCopyMem01( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) ==  2 ){ MlibFastCopyMem02( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) ==  3 ){ MlibFastCopyMem03( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) ==  4 ){ MlibFastCopyMem04( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) ==  5 ){ MlibFastCopyMem05( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) ==  6 ){ MlibFastCopyMem06( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) ==  7 ){ MlibFastCopyMem07( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) ==  8 ){ MlibFastCopyMem08( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) ==  9 ){ MlibFastCopyMem09( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 10 ){ MlibFastCopyMem10( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 11 ){ MlibFastCopyMem11( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 12 ){ MlibFastCopyMem12( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 13 ){ MlibFastCopyMem13( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 14 ){ MlibFastCopyMem14( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 15 ){ MlibFastCopyMem15( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 16 ){ MlibFastCopyMem16( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 17 ){ MlibFastCopyMem17( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 18 ){ MlibFastCopyMem18( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 19 ){ MlibFastCopyMem19( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 20 ){ MlibFastCopyMem20( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 21 ){ MlibFastCopyMem21( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 22 ){ MlibFastCopyMem22( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 23 ){ MlibFastCopyMem23( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else if( (LwdNum) == 24 ){ MlibFastCopyMem24( ((ULONG*)(pSrc)), ((ULONG*)(pDes)), 0 );}\
		else { MlibCopyLongMemory( (ULONG*)pSrc, (ULONG*)pDes, LwdNum );}
 
void	MlibCopyWordMemory(
			USHORT	*sptr,
			USHORT	*dptr,
			LONG	wordnum		);
#define	MlibFastRstMem01( px, i )	px[i] = 0;
#define	MlibFastRstMem02( px, i )	px[i] = 0; px[i+1] = 0;
#define	MlibFastRstMem03( px, i )	px[i] = 0; px[i+1] = 0; px[i+2] = 0;
#define	MlibFastRstMem04( px, i )	px[i] = 0; px[i+1] = 0; px[i+2] = 0; px[i+3] = 0;
#define	MlibFastRstMem05( px, i )	MlibFastRstMem04( px, i ); MlibFastRstMem01( px, i+ 4 );
#define	MlibFastRstMem06( px, i )	MlibFastRstMem04( px, i ); MlibFastRstMem02( px, i+ 4 );
#define	MlibFastRstMem07( px, i )	MlibFastRstMem04( px, i ); MlibFastRstMem03( px, i+ 4 );
#define	MlibFastRstMem08( px, i )	MlibFastRstMem04( px, i ); MlibFastRstMem04( px, i+ 4 );
#define	MlibFastRstMem09( px, i )	MlibFastRstMem08( px, i ); MlibFastRstMem01( px, i+ 8 );
#define	MlibFastRstMem10( px, i )	MlibFastRstMem08( px, i ); MlibFastRstMem02( px, i+ 8 );
#define	MlibFastRstMem11( px, i )	MlibFastRstMem08( px, i ); MlibFastRstMem03( px, i+ 8 );
#define	MlibFastRstMem12( px, i )	MlibFastRstMem08( px, i ); MlibFastRstMem04( px, i+ 8 );
#define	MlibFastRstMem13( px, i )	MlibFastRstMem08( px, i ); MlibFastRstMem05( px, i+ 8 );
#define	MlibFastRstMem14( px, i )	MlibFastRstMem08( px, i ); MlibFastRstMem06( px, i+ 8 );
#define	MlibFastRstMem15( px, i )	MlibFastRstMem08( px, i ); MlibFastRstMem07( px, i+ 8 );
#define	MlibFastRstMem16( px, i )	MlibFastRstMem08( px, i ); MlibFastRstMem08( px, i+ 8 );
#define	MlibFastRstMem17( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem01( px, i+16 );
#define	MlibFastRstMem18( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem02( px, i+16 );
#define	MlibFastRstMem19( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem03( px, i+16 );
#define	MlibFastRstMem20( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem04( px, i+16 );
#define	MlibFastRstMem21( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem05( px, i+16 );
#define	MlibFastRstMem22( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem06( px, i+16 );
#define	MlibFastRstMem23( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem07( px, i+16 );
#define	MlibFastRstMem24( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem08( px, i+16 );
#define	MlibFastRstMem25( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem09( px, i+16 );
#define	MlibFastRstMem26( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem10( px, i+16 );
#define	MlibFastRstMem27( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem11( px, i+16 );
#define	MlibFastRstMem28( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem12( px, i+16 );
#define	MlibFastRstMem29( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem13( px, i+16 );
#define	MlibFastRstMem30( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem14( px, i+16 );
#define	MlibFastRstMem31( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem15( px, i+16 );
#define	MlibFastRstMem32( px, i )	MlibFastRstMem16( px, i ); MlibFastRstMem16( px, i+16 );
#define	MlibFastResetLongMemory( pRstMem, LwdNum )\
		if(      (LwdNum) ==  1 ){ MlibFastRstMem01( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) ==  2 ){ MlibFastRstMem02( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) ==  3 ){ MlibFastRstMem03( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) ==  4 ){ MlibFastRstMem04( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) ==  5 ){ MlibFastRstMem05( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) ==  6 ){ MlibFastRstMem06( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) ==  7 ){ MlibFastRstMem07( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) ==  8 ){ MlibFastRstMem08( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) ==  9 ){ MlibFastRstMem09( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 10 ){ MlibFastRstMem10( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 11 ){ MlibFastRstMem11( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 12 ){ MlibFastRstMem12( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 13 ){ MlibFastRstMem13( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 14 ){ MlibFastRstMem14( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 15 ){ MlibFastRstMem15( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 16 ){ MlibFastRstMem16( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 17 ){ MlibFastRstMem17( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 18 ){ MlibFastRstMem18( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 19 ){ MlibFastRstMem19( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 20 ){ MlibFastRstMem20( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 21 ){ MlibFastRstMem21( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 22 ){ MlibFastRstMem22( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 23 ){ MlibFastRstMem23( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 24 ){ MlibFastRstMem24( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 25 ){ MlibFastRstMem25( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 26 ){ MlibFastRstMem26( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 27 ){ MlibFastRstMem27( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 28 ){ MlibFastRstMem28( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 29 ){ MlibFastRstMem29( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 30 ){ MlibFastRstMem30( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 31 ){ MlibFastRstMem31( ((LONG*)(pRstMem)), 0 );}\
		else if( (LwdNum) == 32 ){ MlibFastRstMem32( ((LONG*)(pRstMem)), 0 );}\
		else { MlibResetLongMemory( pRstMem, LwdNum );}
/* 基本控制运算函数 */
/******************************************************************************************************/
/*1）MlibLimitul（）       ：上下限                                    rv=上限值；*/
/*1-2）FlibLimitul（）     ：上下限                                    rv=上限值；*/
/*2）MlibMulgain（）       ：增益乘法（Limit标准：2^24）             rv=（kx*u）>>sx；0<=sx<=24*/
/*3）MlibMulgain27（）     ：增益乘法（Limit扩展：2^26）             rv=（kx*u）>>sx；0<=sx<=24*/
/*4）MlibMulgain29（）     ：增益乘法（Limit扩展：2^28）             rv=（kx*u）>>sx；0<=sx<=24*/
/*5）MlibMulgain30（）     ：增益乘法（Limit扩展：2^29）             rv=（kx*u）>>sx；0<=sx<=24*/
/*6）MlibMulgain32（）     ：增益乘法（Limit扩展：2^31）             rv=（kx*u）>>sx；0<=sx<=24*/
/*7）MlibMulgainSx48（）   ：增益乘法（smax放大）                       rv=（kx*u）>>sx；0<=sx<=48*/
/*8）MlibMulgainNolim（）  ：增益乘法（无限制）                      rv=（kx*u）>>sx；0<=sx<=24*/
/*9）MlibIntegral（）      ：积分运算（带限制）                      rv=（iu[1]>>>1）；iu[]=iu[]+kx*u；*/
/*9-2）FlibIntegral（）        ：积分运算（带限制）                      rv=iu；iu+=kx*u*/
/*-----------------------------------------------------------------------------------------*/
/*10）MlibPfbkxremLim（）  ：多余位置FB计算                           rv=（kx*u+pfbrem）>>>sx；*/
/*11）MlibPfbkxremNolim（） ：多余位置FB计算                          rv=（kx*u+pfbrem）>>>sx；*/
/*12）MlibMulkprem（）     ：多余位置增益乘法                           rv=（kx*u-（（kx*pfbrem）>>>>sx；*/
/*13）MlibMulkxBiasrem（） ：带偏置余数的增益乘法                     rv=（kx*u+rem+（sign（u）*bias>>s）>>sx；*/
/*-----------------------------------------------------------------------------------------*/
/*14）MlibKrMulgain（）        ：增益乘法（带增益比率）                    rv=（kr*u）>>sx；kr=（kx*r）/（10000<16）*/
/*15）MlibKrMulgain27（）  ：增益乘法（带增益比率）                    rv=（kr*u）>>sx；kr=（kx*r）/（10000<16）*/
/*16）MlibKrIntegral（）   ：积分运算（带增益比率）                    iu=iu+（kr*u）；rv=（（（iu[1]+x）>>1）；*/
/*-----------------------------------------------------------------------------------------*/
/*17）MlibSymMulgain（）   ：增益乘法（正负对称四舍五入）             rv=（kx*u）>>sx；0<=sx<=24*/
/*18）MlibSymMulgainNolim    ：增益乘法（正负对称四舍五入）             rv=（kx*u）>>sx；0<=sx<=24*/
/*19）MlibSymIntegral（）  ：积分运算（正负对称四舍五入）             rv=（iu[1]>>>1）；iu[]=iu[]+kx*u；*/
/*****************************************************************************************************/
LONG	MlibLimitul( LONG u, LONG ulim, LONG llim );
LONG	MlibMulgain( LONG u, LONG k );
LONG	MlibMulgain27( LONG u, LONG k );
LONG	MlibMulgain29( LONG u, LONG k );
LONG	MlibMulgain30( LONG u, LONG k );
LONG	MlibMulgain32( LONG u, LONG k );
LONG	MlibMulgainSx48( LONG u, LONG k );
LONG	MlibMulgainNolim( LONG u, LONG k );
LONG	MlibIntegral( LONG u, LONG k, LONG iu[2] );
LONG	MlibPfbkxremLim( LONG u, LONG k, LONG *pfbrem );
LONG	MlibPfbkxremNolim( LONG u, LONG k, LONG *pfbrem );
LONG	MlibMulkprem( LONG u, LONG k, LONG  pfbrem );
LONG	MlibMulkxBiasrem( LONG u, LONG k, LONG *rem, LONG bias );
LONG	MlibKrMulgain( LONG u, LONG k, LONG r );
LONG	MlibKrMulgain27( LONG u, LONG k, LONG r );
LONG	MlibKrIntegral( LONG u, LONG k, LONG r, LONG iu[2] );
LONG	MlibSymMulgain( LONG u, LONG k );
LONG	MlibSymMulgainNolim( LONG u, LONG k );
LONG	MlibSymIntegral( LONG u, LONG k, LONG iu[2] );
extern float   FlibLimitul(float,float,float);
extern float   flibIntegral( float, float, float *iu );

/* 滤波函数 */
/****************************************************************************************
1）MlibLpfilter1（）       ：一阶低通滤波器                rv=x+（（kx*（u-x））>>>24）；
2）MlibHpfilter1（）       ：一阶高通滤波器                rv=u-z；z=z+（（kx*（u-z））>>24）；
3）MlibLpfilter2（）       ：二阶低通滤波器                rv=（z[2]>>>1）；
4）MlibNxfilter2（）       ：二阶陷波滤波器                rv=k[2]*（u-（z[2]>>>1）-z[0]）+（z[2]>>>1）；
5）MlibLaufilter（）       ：直线加速器（LAU）滤波器      rv=z+dz or rv=z-dz；
7）MlibKrLpfilter1（） ：一阶低通滤波器（带比率）       rv=x+（（kr*（u-x））>>24）；
8）MlibLowPassfilter2（） ：二阶低通滤波运算（双一次变换）
******************************************************************************************/
LONG	MlibHpfilter1( LONG u, LONG k, LONG *z );
LONG	MlibLpfilter2( LONG u, LONG k[2], LONG z[3] );
LONG	MlibNxfilter2( LONG u, LONG k[3], LONG z[3] );
LONG	MlibLaufilter( LONG u, LONG z, LONG dz );
LONG	MlibKrLpfilter1( LONG u, LONG k, LONG r, LONG x );

/* 1次延迟位滤波器宏  */
#define	MlibBITFILTER1( out, oldin, newin )\
		{ out = (((oldin | newin) & out ) | (oldin & newin)); oldin = newin;}
 

/**************************************************************************************************
1）MlibPcmdIpfil（）       ：位置指令插值滤波器      rv=（pcmdin+rem）/n
2）MlibPcmdMafil（）       ：位置指令移动平均滤波器    rv=sum/n，sum=sum+pcmdin-pmafbuf[idx]
4）MlibPcmdImafil（）      ：位置插值移动平均滤波器    rv=sum/n，sum=sum+newpcmd/n-oldpcmd/n
6）MlibPcmdExpfil（）      ：位置指令指数加减速滤波器   rv=sum*kexp，sum=sum+pcmdin-rv
7）MlibPcmdLpfil1（）      ：位置指令1次低通滤波器        rv=z*kf，z=z+pcmdin-rv
8）MlibPcmdLpfil2（）      ：位置指令2次低通滤波器        rv=z[1]*kf1，z[0]=z[0]+pcmdin-rv
9）MlibPcmdNxfil2（）      ：位置指令二次陷波滤波器    rv=pcmdin-Delta（kf2*z[1]）
**************************************************************************************************/
/* 位置指令插补滤波器 */
typedef struct  {           //位置指令内插滤波器结构体定义
        LONG    cmdx;       //位置指令输入
        LONG    remx;       //位置指令输出余量
} PIPFV;
LONG    MlibPcmdIpfil( LONG pcmdin, LONG shift, LONG index, PIPFV *pipfvar );
typedef	struct	{
    SHORT   idx;        //缓冲
    SHORT   ksub;       //减法运算增益（0/1）
    LONG    sumx;       //位置指令合计
    LONG    remx;       //位置指令余数
    USHORT  zcntx;      //完成检查（0:完成）
    USHORT  spare;      //预留
} PMAFV;
LONG    MlibPcmdMafil( LONG pcmdin, LONG pmafnum, PMAFV *pmafvar, LONG *pmafbuf );

/* 位置指令插补移动平均滤波器 */
typedef struct  {           //位置指令内插移动平均滤波器结构体定义
    LONG    sumx;       //位置指令合计
    LONG    remx;       //位置指令余数
    LONG    newpcmd;    //位置指令输入
    LONG    oldpcmd;    //位置指令输入上次值
    USHORT  zcntx;      //完成检查（0:完成）
    USHORT  spare;      //预留
} PIMFV;

/* 位置指令指数加减速过滤器 */
LONG	MlibPcmdImafil( LONG pcmdin, LONG shift, LONG index, PIMFV *pimfvar );
typedef struct  {           //位置指令指数加减速过滤器结构体定义
    LONG    sumx;       //位置指令合计
    LONG    remx;       //位置指令余（未使用）
} PEXFV;
LONG	MlibPcmdExpfil( LONG pcmdin, LONG kexp, LONG pbias, PEXFV *pexfvar );

/* 位置指令低通滤波器 */
LONG	MlibPcmdLpfil1( LONG pcmdin, LONG kf, LONG *z );
LONG	MlibPcmdLpfil2( LONG pcmdin, LONG kf[2], LONG z[2] );
LONG	MlibPcmdNxfil2( LONG pcmdin, LONG kf[3], LONG z[3] );

/************************************************************************************************/
/*1）MlibPcmdEgear（） ：位置指令电子齿轮计算         rv=（B/A）*pcmda*/
/*2）MlibEgearRvscnv（）：电子齿轮逆变换计算         rv=（A/B）*inpls*/
/*3）MlibPcalKegear（） ：电子齿轮参数计算              OUT:egear.k1，egear.k2，etc*/
/*4）MlibPerrcalx（）  ：位置偏差计算X（FB单位）      rv=per64[0]；per64[]=per64[]+pcmd-pfbk；*/
/*5）MlibAposRg64iv（） ：初始绝对位置计算（逆电子齿轮）OUT:aposrg.apos[]，aposrem，etc*/
/*6）MlibAposRg64dp（） ：绝对位置更新计算（逆电子齿轮）OUT:aposrg.apos[]，aposrem，etc*/
/************************************************************************************************/
/* 电子齿轮&位置偏差结构体 */
typedef	struct	{
    LONG    a;      //电子齿轮A
    LONG    b;      //电子齿轮B
    LONG    k1;     //电子齿轮增益：b/a的上位bit
    LONG    k2;     //电子齿轮增益：b/a的下位bit
    LONG    g1;     //电子齿轮增益：a/b的上位bit
    LONG    g2;     //电子齿轮增益：a/b的下位bit

    double  Reca;
    double  Recb;
    float   fa;
    float   fb;
    float   adivb;
    float   bdiva;
} EGEAR;
typedef struct  {           //位置偏差A结构定义
    LONG    pfbkb;      //位置FB（指令单位）运算结果
    LONG    pfbkrem;    //位置FB（指令单位）运算结果余数
    LONG    per64[2];   //位置偏差64bit运算用
    LONG    per32s;     //位置偏差输出（四舍五入）
    LONG    per32a;     //位置偏差输出绝对值（四舍五入）
    LONG    per32sx;    //位置偏差输出（舍入）
    LONG    per32ax;    //位置偏差输出绝对值（）
    LONG    per32mx;    //位置偏差监控用（0.5以下为零）
} PERRA;
LONG	MlibPcmdEgear( LONG pcmda, EGEAR *egear, LONG *pcmdrem );
LONG    FlibPcmdEgear( LONG pcmda, EGEAR *egear, LONG *pcmdrem );
void	MlibPcalKegear( LONG a, LONG b, EGEAR *egear );
LONG	MlibEgearRvscnv( LONG inpls, EGEAR *egear, LONG *plsrem );
LONG    flibEgearRvscnv( LONG inpls, EGEAR *egear, LONG *plsrem );
LONG	MlibPerrcalx( LONG pcmdx, LONG pfbkx, LONG per64[2] );


/* 绝对位置运算（电子齿轮：FB单位-->指令单位） */
typedef struct  {
        LONG    dposix;     //位置差分[指令单位]
        LONG    aposrem;    //位置余量[指令单位]
        LONG    apos[2];    //绝对位置（64bit）[指令单位]
} APOSRG;

void	MlibAposRg64iv( LONG inipos0, LONG inipos1, EGEAR *egear, APOSRG *aposrg );
void	MlibAposRg64dp( LONG dposin, EGEAR *egear, APOSRG *aposrg, LONG *latchpos );
 
  
/* 位置指令生成器函数    */
/********************************************************************************************/
/*1）MlibPcmdMaker（）     ：位置指令生成器（64bit） rv=vp，vp=vp+vpacc/vp=vp-vpdec*/
/*2）MlibIpTposLimit（）   ：同上插值位置指令限制     rv=TRUE（Limit）/FALSE（NotLimit）*/
/*3）MlibRstPcmdMaker（）  ：同上复位处理             pcmdout[]=pcmdset0，pcmdset1，etc*/
/*4）MlibIpcalPcmdMaker      : 同上初始参数计算          OUT:pcmkprm.osvpm，maxvpm，pshlx，etc*/
/*5）MlibPcalaPcmdMaker      : 同上定位参数计算          AOUT:pcmkprm.vpacc，vpdec，vpamx，etc*/
/*6）MlibPcalaPcmdMkrIP      ：同上插值运算参数计算     AOUT:pcmkprm.ipmaxspd，ipmaxacc，etc*/
/*7）MlibPcalbPcmdMaker      : 同上定位参数计算          BOUT:pcmkprm.vpacc，vpdec，vpamx，etc*/
/*8）MlibPcalbPcmdMkrIP      ：同上插值运算参数计算     BOUT:pcmkprm.ipmaxspd，ipmaxacc，etc*/
/*********************************************************************************************/
typedef struct  {                   // 位置生成器参数结构定义
    LONG    osvpm;              // 电机位置指令速度                     [xpulse/scan]
    LONG    maxvpm;             // 最大电机位置指令速度                   [xpulse/scan]
    LONG    maxipv;             // 插值模式最大位置指令速度             [xpulse/scan]
    UCHAR   pshlx;              // 位置指令运算倍率（偏移）             [-]
    UCHAR   pcmd64f;            // 位置指令64位标志                        [TRUE/FALSE]
    USHORT  iptimes;            // Interpolate插值次数                  [-]
/*----------------------------------------------------------------------------------------------*/
    LONG    vpacc;              // 位置指令加速度                      [xpulse/scan/scan]
    LONG    vpdec;              // 位置指令減速度                      [xpulse/scan/scan]
    LONG    vpamx;              // 商(vpacc/vpdec)                       [-]
    LONG    vparx;              // 余数(vpacc%vpdec)                  [-]
    LONG    vpapx;              // 加速量减速停止脉冲量                   [xpulse]
    LONG    maxspd;             // 最大位置指令速度                     [2^24/OvrSpd]
/*----------------------------------------------------------------------------------------------*/
    LONG    ipmaxspd;           // 插值模式最大速度                     [ipulse/IPcycle]
    LONG    ipmaxacc;           // 插值模式最大加速度（未使用）           [ipulse/IPcycle^2]
    LONG    ipstpdec;           // 插值模式紧急停止减速度              [ipulse/IPcycle^2]
} PCMKP;
/*--------------------------------------------------------------------------------------------------*/
typedef struct  {                   // 位置生成器运算用变量结构体定义
    UCHAR   calendf;            // 运算结束标志（运算中：0，运算结束：1）
    UCHAR   cmderrf;            // 指令异常标志（插补模式位置指令异常，etc）
    UCHAR   pcmkmode;           // 位置指令生成模式
    UCHAR   modechgf;           // 位置指令生成模式变化标志
/*----------------------------------------------------------------------------------------------*/
    LONG    vpx;                // 位置指令速度                           [xpulse/scan]
    LONG    vpxrem;             // 位置指令速度输出余数                   [xpulse/scan]
    LONG    pcmdout[2];         // 位置指令输出绝对值                    [ipulse]
    LONG    avp;                // Work:位置指令速度绝对值               [xpulse/scan]
    LONG    n;                  // Work:商(avp/vpdec)                    [-]
    LONG    rem;                // Work:余数(avp%vpdec)                   [-]
    LONG    maxvp;              // Work:最大位置指令速度                [xpulse/scan]
/*----------------------------------------------------------------------------------------------*/
    LONG    ipvpi;              // Interpolate位置指令速度                [ipulse/IPcycle]
    LONG    ipvpx;              // Interpolate位置指令速度                [ipulse/scan]
    LONG    ipremi;             // Interpolate位置指令速度余数          [ipulse/scan]
    LONG    ipremx;             // Interpolate位置指令速度余数          [ipulse/scan]
    LONG    ipstopx[2];         // IpWork:减速停止位置计算值         [ipulse]
} PCMKV;
/*--------------------------------------------------------------------------------------------------*/
typedef struct  {                   // 位置生成器运算用变量（P&V）结构体定义
    PCMKP   P;                  // 参数
    PCMKV   V;                  // 运算变量
} PCMKPV;
  
  
/*  位置指令生成器运算执行函数   */
LONG    MlibPcmdMaker(          // 位置指令生成器运算执行函数
        LONG    pcmdin0,            // 位置指令输入(下位32bit)              [pulse]
        LONG    pcmdin1,            // 位置指令输入(上位32bit)              [pulse]
        LONG    pcmdspd,            // 位置指令速度(最大／进给)                [2^24/OvrSpd]
        PCMKPV  *pcmdmkr,           // 位置指令生成器运算用变量(P&V)        [-]
        ULONG   pcmkmode    );      // 位置指令生成模式                     [-]


/*  位置指令作成模式定义：基本模式应在下位字节定义 */
#define PCMKMODE_NONE   0x0000      // 位置指令生成模式 : 无
#define PCMKMODE_IPA    0x0001      // 位置指令生成模式 : 插补（有输入更新）
#define PCMKMODE_IPB    0x0101      // 位置指令生成模式 : 插补（无输入更新）
#define PCMKMODE_POS    0x0002      // 位置指令生成模式 : 定位
#define PCMKMODE_FEED   0x0003      // 位置指令生成模式 : 定速进给
#define PCMKMODE_STOP   0x0004      // 位置指令生成模式 : 减速停止

LONG    MlibIpTposLimit(        //插补位置指令限制运算
        LONG    *tpos,              //目标位置（64bit）[pulse]
        LONG    *lmtpos,            //极限位置（64bit）[pulse]
        LONG    lmtdir,             //限制方向（正侧/负侧）[-]
        PCMKPV  *pcmdmkr    );      //位置指令生成器运算用变量（P&V）[-]

#define IPTPOSLMT_PSIDE     1       //限制方向：正侧
#define IPTPOSLMT_NSIDE     0       //限制方向：负侧

void    MlibRstPcmdMaker(       //位置指令生成器复位处理
        LONG    pcmdset0,           //位置指令初始值（低位32bit）[pulse]
        LONG    pcmdset1,           //位置指令初始值（上位32bit）[pulse]
        PCMKPV  *pcmdmkr    );      //位置指令生成器运算用变量（P&V）[-]

LONG    MlibIpcalPcmdMaker( //位置指令生成器初始参数计算
        KSGAIN  ksosvp,             //脉冲速度[xpulse/scan]
        LONG    maxspdm,            //最大电机速度[2^24/OvrSpd]
        LONG    maxspdi,            //插值模式最大速度[2^24/OvrSpd]
        LONG    pcmd64f,            //位置指令64位标志[TRUE/FALSE]
        PCMKP   *pcmkprm    );      //计算结果输出结构指针[-]

LONG    MlibPcalaPcmdMaker( //位置指令生成器定位参数计算A
        LONG    maxspd,             //最大速度[2^24/OvrSpd]
        LONG    acctime,            //加速时间[xs]
        LONG    dectime,            //减速时间[xs]
        LONG    scantime,           //扫描时间[xs]
        PCMKP   *pcmkprm    );      //计算结果输出结构指针[-]

LONG    MlibPcalaPcmdMkrIP( //位置指令生成器插补运算参数计算A
        LONG    iptimes,            //插值次数[-]
        LONG    maxspd,             //最大速度[2^24/OvrSpd]
        LONG    ipacctm,            //最小加减速时间（未使用）[xs]
        LONG    ipdectm,            //紧急停止减速时间[xs]
        LONG    scantime,           //扫描时间[xs]
        PCMKP   *pcmkprm    );      //计算结果输出结构指针[-]

LONG    MlibPcalbPcmdMaker( //位置指令生成器定位参数计算B
        LONG    accrate,            //加速速率[10000pulse/s]
        LONG    decrate,            //减速率[10000pulse/s]
        LONG    scantime,           //扫描时间（stm）[us（Y=0）/ns（Y=1）]
        PCMKP   *pcmkprm,           //计算结果输出结构指针[-]
        LONG    insel       );      //输入选择（0xYX）[X：不使用，Y:us/ns选择]

LONG    MlibPcalbPcmdMkrIP( //位置指令生成器插补运算参数计算B
        LONG    iptimes,            //插值次数[-]
        LONG    ipaccrt,            //最大加减速率（未使用）
        LONG    ipdecrt,            //紧急停止减速率[10000pulse/s]
        LONG    scantime,           //扫描时间（stm）[us（Y=0）/ns（Y=1）]
        PCMKP   *pcmkprm,           //计算结果输出结构指针[-]
        LONG    insel       );      //输入选择（0xYX）[X：不使用，Y:us/ns选择]

/* 参数计算函数 */
/*********************************************************************************************
1）MlibPcalKxgain（）  ：比例增益计算 {kx，sx}=（a*b/c）<sx；
2）MlibPcalKskxkx（）  ：扩展增益计算 {kx，sx}={ka，sa}*b/c<sx；
3）MlibPcalKxkskx（）  ：扩展增益计算 {kx，sx}=a*{kb，sb}/c<sx；
4）MlibPcalKxkxks（）  ：扩展增益计算 {kx，sx}=a*b/{kc，sc}<sx；
5）MlibPcalKskskx（）  ：扩展增益计算 {kx，sx}={ka，sa}*{kb，sb}/c<sx；
6）MlibPcalKxksks（）  ：扩展增益计算 {kx，sx}=a*{kb，sb}/{kc，sc}<sx；
7）MlibPcalKsksks（）  ：扩展增益计算 {kx，sx}={ka，sa}*{kb，sb}/{kc，sc}<sx；
------------------------------------------------------------
8）MlibScalKxgain（）  ：比例增益计算（开始计算用）{kx，sx}=（a*b/c）<sx；（不需要指数初始化）
9）MlibScalKskxkx（）  ：扩展增益计算（开始计算用）{kx，sx}={ka，sa}*b/c<sx；
10）MlibScalKxkskx（）：扩展增益计算（开始计算用）{kx，sx}=a*{kb，sb}/c<sx；
11）MlibScalKxkxks（）：扩展增益计算（开始计算用）{kx，sx}=a*b/{kc，sc}<sx；
12）MlibScalKskskx（）：扩展增益计算（开始计算用）{kx，sx}={ka，sa}*{kb，sb}/c<sx；
13）MlibScalKxksks（）：扩展增益计算（开始计算用）{kx，sx}=a*{kb，sb}/{kc，sc}<sx；
14）MlibScalKsksks（）：扩展增益计算（开始计算用）{kx，sx}={ka，sa}*{kb，sb}/{kc，sc}<sx；
------------------------------------------------------------
15）MlibPcalKxaddx（）：比例增益相加  {kx，sx}={ka，sa}+{kb，sb}；
16）MlibPcalKxsubx（）：比例增益减法  {kx，sx}={ka,sa}-{kb，sb}；
17）MlibPcalKxmulx（）：比例增益乘法  {kx，sx}=（a*b*c）<sx；
18）MlibPcalKxdivx（）：比例增益除法  {kx，sx}={ka，sa}/{kb，sb}；
-----------------------------------------------------------
19）MlibPcalKf1gain（）    ：一阶滤波增益计算       {kf，24}=（ts/（tx+ts）<24；
20）MlibPcalKf2gain（）    ：二阶滤波增益计算       OUT:kf[0]，kf[1]
21）MlibPcalKnf2gain（）   ：二阶陷波滤波器增益计算OUT:kf[0]，kf[1]，kf[2]
**********************************************************************************************/
LONG	MlibPcalKxgain( LONG a,   LONG b,   LONG c,   LONG *psx, LONG smax );
LONG	MlibPcalKskxkx( LONG ksa, LONG b,   LONG c,   LONG *psx, LONG smax );
LONG	MlibPcalKxkskx( LONG a,   LONG ksb, LONG c,   LONG *psx, LONG smax );
LONG	MlibPcalKxkxks( LONG a,   LONG b,   LONG ksc, LONG *psx, LONG smax );
LONG	MlibPcalKskskx( LONG ksa, LONG ksb, LONG c,   LONG *psx, LONG smax );
LONG	MlibPcalKxksks( LONG a,   LONG ksb, LONG ksc, LONG *psx, LONG smax );
LONG	MlibPcalKsksks( LONG ksa, LONG ksb, LONG ksc, LONG *psx, LONG smax );
LONG	MlibScalKxgain( LONG a,   LONG b,   LONG c,   LONG *psx, LONG smax );
LONG	MlibScalKskxkx( LONG ksa, LONG b,   LONG c,   LONG *psx, LONG smax );
LONG	MlibScalKxkskx( LONG a,   LONG ksb, LONG c,   LONG *psx, LONG smax );
LONG	MlibScalKxkxks( LONG a,   LONG b,   LONG ksc, LONG *psx, LONG smax );
LONG	MlibScalKskskx( LONG ksa, LONG ksb, LONG c,   LONG *psx, LONG smax );
LONG	MlibScalKxksks( LONG a,   LONG ksb, LONG ksc, LONG *psx, LONG smax );
LONG	MlibScalKsksks( LONG ksa, LONG ksb, LONG ksc, LONG *psx, LONG smax );
LONG	MlibPcalKxaddx( LONG ka,  LONG sa,  LONG kb,  LONG sb,   LONG *psx );
LONG	MlibPcalKxsubx( LONG ka,  LONG sa,  LONG kb,  LONG sb,   LONG *psx );
LONG	MlibPcalKxmulx( LONG a,   LONG b,   LONG c,   LONG *psx            );
LONG	MlibPcalKxdivx( LONG ka,  LONG sa,  LONG kb,  LONG sb,   LONG smax );
LONG	MlibPcalKf1gain(LONG tx,  LONG	ts,	LONG	insel	);
 #if (FLOAT_USE==1)
float   FlibPcalKf1gain( LONG tx, LONG ts, LONG insel   );
#endif
 void	MlibPcalKf2gain(
		LONG	hz,
		LONG	dx,
		LONG	ts,
		LONG	kf[2],
		LONG	insel	);
void	MlibPcalKnf2gain(
		LONG	hz,
		LONG	qx,
		LONG	kn,
		LONG	ts,
		LONG	kf[3],
		LONG	insel	);
/*--------------------------------------------------------------------------------------------*/
LONG    MlibPcalKf1gain(        //一阶滤波增益计算
        LONG    tx,                 //时间常数（Tx）/频率（Fx）   [xs]，[0.1Hz]（X=0:Tx，X=1:Fx）
        LONG    ts,                 //周期[xs]，               [us/ns]（Y=0:us，Y=1:ns）
        LONG    insel   );          //输入选择（0xYX）            [X:Tx/Fx选择，Y:us/ns选择]

void    MlibPcalKf2gain(        //二阶滤波器增益计算
        LONG    hz,                 //滤波频率[0.1Hz]
        LONG    dx,                 //滤波器衰减系数[0.001]
        LONG    ts,                 //周期[us/ns]（Y=0:us，Y=1:ns）
        LONG    kf[2],              //计算结果存储指针[--]
        LONG    insel   );          //输入选择（0xYX）[X：不使用，Y:us/ns选择]

void    MlibPcalKnf2gain(       //二阶陷波滤波器增益计算
        LONG    hz,                 //滤波频率[0.1Hz]
        LONG    qx,                 //Q常数（Qx）/衰减系数（Dx）[0.001]（X=0:Qx，X=1:Dx）
        LONG    kn,                 //陷波深度增益[0.001]
        LONG    ts,                 //周期[us/ns]（Y=0:us，Y=1:ns）
        LONG    kf[3],              //计算结果存储指针[--]
        LONG    insel   );          //输入选择（0xYX）[X:Qx/Dx选择，Y:us/ns选择]

/* 增益操作宏 */
#define	MlibGAINKX( k )		((LONG)((k)<<8)>>8)
#if 0
#define	MlibGAINSX( k )		(((CHAR*)&(k))[3])
#else
#define MlibGAINSX( k )     ((k >> 24) & 0x00FF)
#endif
#define	MlibGAINRD( k )		(MlibGAINKX( k ) >> ((LONG) ((ULONG) (k)>>24)))

/* 基本数值运算函数 */
/**********************************************************************************************/
/*1）MlibAbs32（）     ：绝对值（32bit）*/
/*2）MlibAdd6432（）   ：加法（带符号，64bit+32bit）*/
/*3）MlibAdd6464（）   ：加法（带符号，64bit+64bit）*/
/*4）MlibSub6432（）   ：减法（带符号，64bit-32bit）*/
/*5）MlibSub6464（）   ：减法（带符号，64bit-64bit）*/
/*6）MlibErr6464（）   ：偏差（带符号，64bit-64bit，带返回值饱和功能）*/
/*7）MlibSatAdd24（   ）   ：饱和加法（带符号，32bit+32bit，Limit:0x010000000,0xFF000000）*/
/*8）MlibSatAdd28（）  ：饱和加法（带符号，32bit+32bit，Limit:0x100000,0xF0000000）*/
/*9）MlibSatAdd32（）  ：饱和加法（带符号，32bit+32bit，Limit:0x7FFFFFFF，0x800000000）*/
/*10）MlibSatAddu32（）    ：饱和加法（无符号，32bit+32bit，Limit:0xFFFFFFFF）*/
/*11）MlibMul3232（）  ：乘法（带符号，32bit*32bit）*/
/*12）MlibMulu32u32（）    ：乘法（无符号，32bit*32bit）*/
/*13）MlibMulhigh32（）    ：乘法（带符号，32bit*32bit，返回值：上位32bit，四舍五入）*/
/*14）MlibMulhighu32（）：乘法（无符号，32bit*32bit，返回值：上位32bit，四舍五入）*/
/*15）MlibDivhrem（）  ：除法（带符号，32bit/16bit，输出：商&余）*/
/*16）MlibDiv6432（）  ：除法（带符号，32bit*32bit/32bit，Limit:0x7FFFFFFF，四舍五入）*/
/*17）MlibDivx3232（） ：扩展除法（（（32bit<<sx）/32bit，限制：（qmax<sx）*/
/*18）MlibSqrtu32（）  ：根运算（输入：32bit，输出：16bit（Max.0xFFFF），四舍五入）*/
/*19）MlibSqrtu64（）  ：根运算（输入：64bit，输出：32bit（Max.0xFFFFFFFF），四舍五入）*/
/*20）MlibSqrtu32u32（）：根运算（输入：32bit*32bit，输出：32bit（Max.0xFFFFFF），四舍五入）*/
/*21）MlibSins16（）   ：Sin运算（输入：[0.1deg]，[360/16384deg]，输出：[1.0/1000]，[1.0/16384]）*/
/*22）MlibAbsErrchk32（）：绝对值偏差检查（rv=（｜a32-b32｜<=chk32）*/
/*23）MlibAbsErrchk64（）：绝对值偏差检查（rv=（｜a64-b64｜<=chk32）*/
/**********************************************************************************************/
LONG	MlibAbs32( LONG u );
void	MlibAdd6432( LONG *a, LONG  b, LONG *x );
void	MlibAdd6464( LONG *a, LONG *b, LONG *x );
void	MlibSub6432( LONG *a, LONG  b, LONG *x );
void	MlibSub6464( LONG *a, LONG *b, LONG *x );
LONG	MlibErr6464( LONG *a, LONG *b );
LONG	MlibSatAdd24( LONG a, LONG b );
LONG	MlibSatAdd28( LONG a, LONG b );
LONG	MlibSatAdd32( LONG a, LONG b );
ULONG	MlibSatAddu32( ULONG a, ULONG b );
void	MlibMul3232( LONG a, LONG b, LONG *x );
void	MlibMulu32u32( ULONG a, ULONG b, ULONG *x );
LONG	MlibMulhigh32( LONG a, LONG b );
ULONG	MlibMulhighu32( ULONG a, ULONG b );
USHORT	MlibSqrtu32( ULONG a );
 

/* 特殊运算处理函数 */
/***********************************************************************************************/
/*1）MlibSrhbiton（）：搜索位ON（从LSB/MsB搜索，    返回值：BitNo/NG（-1））*/
/*2）MlibSetCRC16（）：CRC16的设定（用于MEMOBUS），返回值：无*/
/*3）MlibChkCRC16（）：CRC16的检查（MEMOBUS用），  返回值：TRUE（正常）/FALSE（异常）*/
/***********************************************************************************************/
LONG	MlibSrhbiton( ULONG data, ULONG dir );
#define	SRH_FROM_LSB	0
#define	SRH_FROM_MSB	1
void	MlibSetCRC16( USHORT *Dbuf, LONG Length );
LONG	MlibChkCRC16( USHORT *Dbuf, LONG Length );
 
 
 
#endif
 
 
/*--------------------------------------------------------------------------------------------------*/
/*                                          End of The File                                         */
/*--------------------------------------------------------------------------------------------------*/
