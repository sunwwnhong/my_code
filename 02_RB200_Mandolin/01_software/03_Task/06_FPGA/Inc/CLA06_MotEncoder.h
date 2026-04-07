/*
 * CLA05_DSPUpdate.h
 *
 *  Created on: 2023Äê4ÔÂ4ÈÕ
 *      Author: zhuxc
 */
#ifndef CLA06_MotEncoder_H
#define CLA06_MotEncoder_H

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

}MotEncoder_VAR;

extern MotEncoder_VAR MotEncoder_V;

typedef struct
{
    USHORT  A_Ori;
    USHORT  B_Ori;
    USHORT  A_Max[23];
    USHORT  B_Max[23];
    USHORT  A_Min[23];
    USHORT  B_Min[23];
    ULONG  A_Max_ave;
    ULONG  B_Max_ave;
    ULONG  A_Min_ave;
    ULONG  B_Min_ave;
    USHORT  A_Offset;
    USHORT  B_Offset;
    USHORT  AB_Gain;
    ULONG  Theta;
    SHORT   A;
    SHORT   B;

    USHORT MagRing_Pole;

    float errorOld;
    float errorNew;

    float angleObs;
    float errorWfT;
    float rpsObs;

    float picon_K0;
    float picon_K1;

    USHORT first;

}Mag_Dec;

extern Mag_Dec MagDec;
extern void fun_SinCos_ADC_Init(void);
extern void fun_SinCos_ADC_Correct(void);
extern void fun_SinCos_ADC_Deal(void);
extern void fun_SinCos_PLL(void);
extern void MotEncoder_ST_MT_Get( void );

extern void CorrectSave(void);

#endif
