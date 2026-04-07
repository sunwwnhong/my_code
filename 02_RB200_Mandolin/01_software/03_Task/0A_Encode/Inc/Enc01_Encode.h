/*
 * Enc01_Encode.h
 *
 *  Created on: 2018Äê1ÔÂ25ÈÕ
 *      Author: zhuxc
 */
 #ifndef Enc01_Encode_H
#define Enc01_Encode_H
 #include "Main.h"
#define EncEepromDataNum        39                               
#define	MENC_INCRE_TYPE			0x00							 
#define	MENC_MABSO_TYPE			0x10   							 
  
typedef struct
{
    ULONG SingTurn;                                              
    ULONG MultTrun;                                              
    USHORT ENCDataBuf[EncEepromDataNum];                         
    USHORT  ABSEncWriteStep;                                   	 
    USHORT  ABSEncWriteCnt;                                    	 
    USHORT ABSEncWriteDelyCnt;                                	 
    USHORT MEncClrCmd;											 
    USHORT MEncClrStatus;										 
    USHORT MEncClrStep;											 
    USHORT MEncClrCnt;											 
    USHORT DataWriteToEeprom;									 
}  ENC_STRUCT_DEF;
extern ENC_STRUCT_DEF EncCodeV; 
 extern void MotorEncType_Init(void);                             
extern void MEncClrDeal(void);									 
extern void MotorInfWriteToEnc(void);                            
#endif
