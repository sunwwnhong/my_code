/*
 * App15_Can.h
 *
 *  Created on: 2022Äê7ÔÂ12ÈÕ
 *      Author: zhuxc
 */

#ifndef App15_Can_H
#define App15_Can_H


extern MCAN_RxBufElement RxMsg;
extern MCAN_TxBufElement TxMsg;
extern MCAN_RxFIFOStatus RxFS;


extern USHORT MCFIFOIndex;
extern void InitCpu1_Can( void );
extern void CanBussOffCheck( void );

#endif

