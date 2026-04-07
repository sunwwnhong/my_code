/*
 * CLA07_CTek5900.h
 *
 *  Created on: 2025年07月10日
 *      Author: MP
 */
#ifndef CLA07_CTek5900_H
#define CLA07_CTek5900_H

#define CTek_5900WR_CMD    0x5B00
#define CTek_5900RD_CMD    0x6200

#define KTM59_WRITE_REG                      0x5B000000
#define KTM59_READ_REG                       0x62000000

#define KTM59_NLC_DATA_ADDR                  0xB0
#define KTM59_NLC_WR_ADDR                    0xAF


#define KTM5900_Load_En     (Prm.Pn532 == 0)

 typedef struct
{
     USHORT MTPStep;             // MTP烧写流程
     USHORT MTPEN;               // MTP烧写使能
     USHORT MTPCnt;              // MTP烧写次数
     USHORT MTPWaitCnt;          // MTP-SPI通讯延时

     USHORT Data256Step;         // 写256点数据步骤
     USHORT DataArry8;           // 写256点数组8循环
     USHORT DataArry32;          // 写256点数组32循环
     USHORT DataArryWait;        // 写256点数组等待时间
     USHORT DataWritetimes;      // 写256点数组次数


     USHORT CaliStep;            // 校准流程
     ULONG  CaliWaitCnt;         // 校准等待延时
     USHORT CaliEn;              // 校准使能
     USHORT CaliRslt;            // 校准结果

 }CONNTEK_VAR;
 extern CONNTEK_VAR CTek_V;


 typedef struct
 {
     USHORT Enable;
     USHORT Start;
     USHORT StartCnt;
     USHORT End;
     SHORT  Sector;
     LONG  Record[130];
     LONG  Count[130];
     LONG  FinalRecord[130];
     LONG  FirstRec;
     LONG  Sum[130];
     LONG  RecSum;
     SHORT  WriteEn;
     SHORT  WriteStep;
     SHORT  WriteNum;
 }LOADCOMPENS_VAR;

extern LOADCOMPENS_VAR CompensLD;

extern LONG  CTek5900_Pos;
extern LONG  CTek5900_Comp;
extern ULONG  CTek5900_PosOri;
extern uint16_t KTM59CaliStatus;

extern void CTek5900_PosRead( void );
extern uint16_t CTek5900_ReadReg(uint16_t Addr, uint32_t base);
extern uint16_t CTek5900_WriteReg(uint16_t data, uint16_t Addr, uint32_t base);
extern void CompensateWriteEnable(void);
extern void CompensateRead(void);
extern void LoadEncCompensateRun(void);

extern void CTek5900PosBResret(void);
#endif
