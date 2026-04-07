/*
 * Cur03_CurSamp.h
 *
 *  Created on: 2017年6月14日
 *      Author: zhuxc
 */
#ifndef Cur03_CurSamp_H
#define Cur03_CurSamp_H
 
  
typedef	struct
{
 		struct {
                    UINT	ZeroOk		    :1;         // 电流零点采样完成标志
                    UINT    ZeroClr         :1;	        // 电流零点清零标志
                    UINT	ZeroErr 		:1;         // 电流零点异常标志
                    UINT	PowOffFlg 		:1;         // 外部输入电源掉电标志
                    UINT	PhaseLostflg	:1;         // 外部缺相信号计数器
                    UINT	PowOffWarFlg0	:1;         // 外部掉电警报标志
                    UINT	PowOffWarFlg1	:1;         // 保留
                    UINT	Spare 		    :9;                  
		} f;
}CURFLG;
typedef struct
{
    LONG    ADCSample_IuSum;        // U 相电流累加值
    LONG    ADCSample_IvSum;        // V 相电流累加值
    LONG    ADCSample_IWSum;        // W 相电流累加值
    ULONG   PowerOffTime;           // 电网掉电滤波检测时间计数
    CURFLG  CurFlg;                 // 电流标志位
    USHORT  ADCSample_I12Cnt;       // 两相电流累计次数
    SHORT   ADCSample_Iu;           // U 相电流采样值（偏移后的）
    SHORT   ADCSample_Iv;           // V 相电流采样值（偏移后的）
    SHORT   ADCSample_Iw;           // W 相电流采样值（偏移后的）
    SHORT   IvSim;                  // V相仿真电流 (未用)
    SHORT   IwSim;                  // W相仿真电流 (未用)
    SHORT   IuZero;                 // U相零点
    SHORT   IvZero;                 // V相零点
    SHORT   IwZero;                 // W相零点
    USHORT  drivType;               // 驱动器功率等级识别
}CURRENT_STRUCT_DEF;
#define CURRENT_STRUCT_DEFAULT {0L,0L,0UL,0,0,0,0,0,0,0,0,0,0,0} 
extern CURRENT_STRUCT_DEF CurrentSample;
extern void KpxCheckFPGAOCAlarm(void);
#ifdef CPU1
extern void MotA_CurrentZeroSet(void);
#endif
extern void CurrentSim(USHORT Index);
extern void KpxCheckFPGAOCAlarm(void);
extern void PowerOffCheckTime( void );
#endif
