/*
 * CLA07_CTek5900.h
 *
 *  Created on: 2025Äê07ÔÂ10ÈÕ
 *      Author: MP
 */
#ifndef CLA07_MT6709_H
#define CLA07_MT6709_H


//---------------------------------------------------------------------------------------------
extern void MT6709_init(void);
extern void MT6709_Config_Init(void);

extern void MT6709_PosWrite_Cmd( uint32_t base );
extern void MT6709_PosRead_Cmd( uint32_t base );
extern void MT6709_ReadAngleA( void );
extern void MT6709_ST_MT_Get( void );

typedef struct
{
    USHORT StatusA;
    SHORT DelayCnt;

    ULONG  PosA;
    ULONG  PosAOri;
    LONG  PosALast;
    LONG  Single;
    LONG  Multi;
    LONG  PoleCnt;

    USHORT AngleOffSet;

}MT6709_VAR;

extern MT6709_VAR MT6709_V;

#endif
