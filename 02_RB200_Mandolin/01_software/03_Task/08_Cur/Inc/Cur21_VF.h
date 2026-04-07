/*
 * Cur21_VF.h
 *
 *  Created on: 2020年6月12日
 *      Author: zhuxc
 */
 #ifndef Cur21_VF_H
#define Cur21_VF_H
    
 typedef struct {
		ULONG	VfTimeAcc;  // V/F加减速时间
        LONG	KTheta;     // V/F模式下的单位频率下SCANA对应delt电气角度
        float   IFSetCur;   //目标电流设定
        float   fKTheta;    //电气角增量大小
        float   I_Acc;      //电流增量大小
 		} VFP;
typedef struct {
		ULONG	I_Timer;    //电流累加持续时间
		USHORT	If_I_Step;  //IF电流控制状态
		USHORT  If_A_Step;  //IF电气角度控制状态
        SHORT	MotPhase;   //相位输出
        USHORT  Reserved;
		} VFV;
 typedef	struct {
        VFP P;
        VFV V;
 		float  IFCurOut;    //IF模式电流输出
		float  IFFreOut;    //电气频率输出
 }VFCTRL;
 
extern VFCTRL  VfCtrl;
void PcalVfSoftStartAcc( void );
void SoftStartVfRef( void );   
extern void PcalVfVSet( void );
#endif
