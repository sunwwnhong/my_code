/*
 * Mot14_MRev.h
 *
 *  Created on: 2019Äê11ÔÂ18ÈÕ
 *      Author: zhuxc
 */
 #ifndef Mot14_MRev_H
#define Mot14_MRev_H
 typedef struct
{
    INT64 MRPulseSum;
    INT64 MrPulseBase;
    INT64 MRPulse;
    LONG MRPulseL;
    LONG MRPulseH;
    SHORT MRevOld;
    USHORT MRFlag;
    USHORT MROVFlag;
    LONG  MRRemain;
    SHORT  MRCnt;
     SHORT  MROVCheckOLd;
    UCHAR  MROVCheckFlag;
    UCHAR  MRDirect;
}MREVDEALP;
extern MREVDEALP MRevV;
 extern void MRevDealInit( void );
extern void MRevDeal( SHORT );
extern void MRevOverCheck( SHORT InData );
extern void MRRevCntSaved( void );
 #endif
