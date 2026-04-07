/*
 * Can05_SDOMngr.h
 *
 *  Created on: 2017Äê7ÔÂ25ÈÕ
 *      Author: zhuxc
 */

#ifndef Can05_SDOMngr_H
#define Can05_SDOMngr_H


extern USHORT ODB2XXX_Check(USHORT OD_Addr,USHORT OD_SubIndex);
extern void ODB2XXX_ReadDeal(USHORT OD_IndexValue,USHORT SDOSendNum);
extern void ODB2XXX_WriteDeal(USHORT OD_IndexValue,USHORT SDOSendNum,UCHAR TYPE);
extern USHORT ODB2EXX_Check(USHORT OD_Addr,USHORT OD_SubIndex);
extern void ODB2EXX_ReadDeal(USHORT OD_IndexValue,USHORT SDOSendNum);

#endif
