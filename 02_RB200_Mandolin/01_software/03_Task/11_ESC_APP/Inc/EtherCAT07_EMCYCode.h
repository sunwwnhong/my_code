/*
 * EtherCAT07_EMCYCode.h
 *
 *  Created on: 2021Äê01ÔÂ22ÈÕ
 *      Author: zhuxc
 */

#ifndef EtherCAT07_EMCYCode_H
#define EtherCAT07_EMCYCode_H

extern const USHORT EmcyCode[][2];
extern USHORT EtherCATErrorCode;
extern USHORT EtherCATErrorAddCode;
extern UCHAR  EtherCATErrorFlag;

extern void ServoErrorUpdate( USHORT ErrorCode );

#endif
