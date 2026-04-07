/*
 * Mot1_PanOper.h
 *
 *  Created on: 2017骞�5鏈�15鏃�
 *      Author: zhuxc
 */
 #ifndef Mot51_PanOper_H
#define Mot51_PanOper_H
 #include "Main.h"
#include "SvOption.h"
 #define PNL_LED_NUM 5                                    
 typedef	struct
{
    UCHAR	PnlBtn;                                      
    UCHAR   PnlBtnLast;                                  
    UCHAR   PnlBtnCnt;                                   
    UCHAR   KeyMode;                                     
    USHORT	KeyTime;                                     
    USHORT  BlnkTime;                                    
    USHORT  LastAlarm;                                   
    UCHAR   DispMode;                                    
    UCHAR   CurPos;                                      
    UCHAR   CurPosMax;                                   
    UCHAR   LedDisBuf[PNL_LED_NUM];                      
      
     LEDDSP  DspData;                                     
     USHORT  OpBlnkTime;                                  
     USHORT  CurFunIndx;                                  
    USHORT  CurMonIndx;                                  
    USHORT  CurPrmIndx;                                  
    USHORT  PrmWrState;                                  
    ULONG	ModifyData;
    UCHAR   LedTestCnt;
    UCHAR   LedDisStep;
}PANOPER;
extern PANOPER PanOper;
 
  
  
  
  
  
  
     
#define	LEDCODE_B0		0x01
#define	LEDCODE_B1		0x02
#define	LEDCODE_B2		0x04
#define	LEDCODE_B3		0x08
#define	LEDCODE_B4		0x10
#define	LEDCODE_B5		0x20
#define	LEDCODE_B6		0x40
#define	LEDCODE_B7		0x80
  
#define	LEDCODE_ZERO	0x3F         
#define	LEDCODE_1		0x06         
#define	LEDCODE_2		0x5B         
#define	LEDCODE_3		0x4F         
#define	LEDCODE_4		0x66         
#define	LEDCODE_5		0x6D         
#define	LEDCODE_6		0x7D         
#define	LEDCODE_7		0x27         
#define	LEDCODE_8		0x7F         
#define	LEDCODE_9		0x6F         
#define	LEDCODE_A		0x77         
#define	LEDCODE_B		0x7C         
#define	LEDCODE_C		0x39         
#define	LEDCODE_D		0x5E         
#define	LEDCODE_E		0x79         
#define	LEDCODE_F		0x71         
#define	LEDCODE_G		0x3D         
#define	LEDCODE_H		0x76         
#define	LEDCODE_sH		0x74         
#define	LEDCODE_J		0x0E         
#define	LEDCODE_L		0x38         
#define	LEDCODE_N		0x54         
#define	LEDCODE_sO		0x5C         
#define	LEDCODE_P		0x73         
#define	LEDCODE_Q		0x67         
#define	LEDCODE_R		0x50         
#define	LEDCODE_T		0x78         
#define	LEDCODE_U		0x3E         
#define	LEDCODE_sU		0x1C         
#define	LEDCODE_Y		0x6E         
#define	LEDCODE_MINUS	0x40         
#define	LEDCODE_POINT	0x80         
#define	LEDCODE_BLANK	0x00         
 #define	OPWM_None				0
#define	OPWM_UpdtWait			1
#define	OPWM_UpdtBlnk			2
#define	OPWM_InfWrWait			3
 
extern void	PanOperManager(void);
extern void	RpxLedSetStr(UCHAR *str_ptr, LEDDSP *leddspp, USHORT startdgt, USHORT length);
extern void	RpxLedSetValHex(USHORT data, LEDDSP *leddspp, USHORT startdgt, USHORT digit);
extern void	RpxLedSetBlnk(LEDDSP *leddspp, UCHAR blnkptn);
extern void	RpxLedSetValDec(USHORT data, LEDDSP *leddspp, USHORT startdgt, USHORT digit, USHORT sup_flg,USHORT decimals);
extern void RpxLedDispMonDecLong(ULONG ldata, LEDDSP *leddspp, USHORT dsp_pos, USHORT decimals, USHORT sign);
extern void	RpxLedSetStatusBits(LEDDSP *leddspp);
extern USHORT KpiGetAlarmInfo( void );
extern void RpxPnlOpMonInit( void );
extern void	RpxLedSetFlag(USHORT data, LEDDSP *leddspp, USHORT startdgt, USHORT digit);
extern void RpxLedDispMonDecWord(USHORT data, LEDDSP *leddspp, USHORT decimals, USHORT sign);
#endif
