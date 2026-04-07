/*
 * Mot64_SerialNum.h
 *
 *  Created on: 2024Äê3ÔÂ21ÈÕ
 *      Author: syhu
 */
#ifndef Mot64_SerialNum_H
#define Mot64_SerialNum_H


#define EEPADR_SERVOINF      0x07F0

extern void SnHoldUpdate( void );
extern void SnRead(void);
extern void SnWriteEn(void);

#endif
