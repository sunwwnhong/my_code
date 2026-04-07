/*
 * CLA06_IcHaus.h
 *
 *  Created on: 2024年4月9日
 *      Author: syhu
 */
 #ifndef CLA06_IcHaus_H
#define CLA06_IcHaus_H

#define ICHAUS_TEST    0

/* 电机端编码器配备PVL */
#define MOTOR_PVL_EN    (((Prm.PosJump & 0x0010) == 0x0010) || ((Prm.PosJump & 0x0020) == 0x0020))
/* 负载端编码器配备PVL */
#define LOAD_PVL_EN     (((Prm.PosJump & 0x0100) == 0x0100) || ((Prm.PosJump & 0x0200) == 0x0200))


#define POS_COMPENS_ENABLE   ( Prm.Pn599 == 0x001 )          //TODO 单圈位置线性补偿

#define POS_COMPENS_64_ENABLE   ( Prm.Pn599 == 0x002 )          //TODO 单圈位置线性补偿

#define MOTOR_MULTI_EN  ((Prm.PosJump & 0x0010) == 0x0010)    /* 电机端多圈编码器当多圈用  */
//#define MOTOR_SINGLE_EN ((Prm.PosJump & 0x0020) == 0x0020)    /* 电机端多圈编码器当单圈用  */

#define LOAD_MULTI_EN   ((Prm.PosJump & 0x0100) == 0x0100)    /* 负载端多圈编码器当多圈用  */
//#define LOAD_SINGLE_EN  ((Prm.PosJump & 0x0200) == 0x0200)    /* 负载端多圈编码器当单圈用  */



//积分补偿数据结构体
typedef struct
{
  LONG    Page1integral[130];
  USHORT    SumL;
  USHORT    SumH;
  LONG     CheckSum;
  USHORT    CheckSumL;
  USHORT    CheckSumH;
} StructTypeEepromRWPage1integral;

//积分补偿数据结构体
typedef struct
{
  LONG    MotorEncComp[12];
  USHORT    SumL;
  USHORT    SumH;
  LONG     CheckSum;
  USHORT    CheckSumL;
  USHORT    CheckSumH;
} StructTypeEepromMotEnc;

extern USHORT icMu_Status_A ;
extern USHORT icMu_Status_B ;
extern ULONG icMu_Pos_B;
extern ULONG icMu_Pos_A;

extern USHORT icMuPosAGet( void );
extern void icMuPosBGet( void );

extern void icMuEEPROMRead( uint32_t base );
extern void icMuEEPROMWrite( void );

extern void CompParaInitFromEEP( void );

extern void icHausPrePulOutPut(void);

extern void icHaus_Comm_Erro(void);
extern ULONG MultiPos_A;
extern ULONG MultiPos_B;

extern void icMuLPFParaWrite(void);
extern void icMuStatusRead( void );

extern uint32_t IntegralComp( int32_t a);
extern uint32_t IntegralComp12( uint32_t a);

extern StructTypeEepromRWPage1integral    stEepromintegral ;      //积分补偿数据结构体
extern StructTypeEepromMotEnc    MotEncCompData ;      //积分补偿数据结构体

 #endif
