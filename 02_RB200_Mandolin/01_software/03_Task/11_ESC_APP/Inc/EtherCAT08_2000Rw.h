/*
 * EtherCAT08_2000Rw.h
 *
 *  Created on: 2021Äê01ÔÂ22ÈÕ
 *      Author: zhuxc
 */
//#include "Main.h"
#ifndef EtherCAT08_2000Rw_H
#define EtherCAT08_2000Rw_H


extern void IPC_Initial( void );
extern USHORT DT201X_Check(USHORT RegNo);
extern USHORT DT20XX_Check(USHORT RegNo);
extern unsigned long *UnMonTblAddress(USHORT Index, USHORT SubIndex);
extern USHORT *UnPnTblAddress(USHORT Index, USHORT SubIndex);



#endif
