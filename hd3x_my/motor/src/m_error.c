//==================================================================================================
//
// 故障处理
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================

   
#include "m_error.h"
#include "m_main.h"
#include "m_interface.h"
#include "m_input.h"
#include "m_frqSrc.h"
#include "m_spinningLoad.h"
#include "m_cell.h"
#include "m_accDecDeal.h"
#include "m_interfaceModify.h"
#include "m_speedLoop.h"

#include "m_macro_error.h"
#include "m_fluxLoop.h"
#include "public.h"



// 河北敬业钢铁，输入缺相、输入电流不对称改为报警。1-这么修改。
#define ERROR_JINGYE_DEAL   0
//#define ERROR_JINGYE_DEAL   1



//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//! 在RAM中调试时，注意相关程序是否打开、相关变量是否赋值。
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!





#pragma DATA_SECTION(motorOlProtect, "data_ram");




Uint16 coreErrorCode;
/*========================================================================================*
* coreAlarmCode为报警代码(按bit位表示)
* bit pos:      7               6            5             4            3       2        1       0 
* mean:     编码器故障      速度反馈异常 初始位置异常 输入电流不对称 掉载故障 输出缺相 输入缺相 电机过载
* bit pos:      8               9           10
* mean:    输出电流不平衡   输入电压不平衡  输出电压不平衡
*=========================================================================================*/
u16 coreAlarmCode;              // 报警代码，每bit位含义参考c2fData.code.alarmCodeFromCore
f32 coreErrorInfo;              // 故障提示信息

void CoreErrorReset(void);
void OverLoadProtect(void);
//void SampleAbnormal(void);

#if DEBUG_P_OUT_GND
s16 outputGroundFaultTicker;
u16 outputGroundFaultError;
void OutputGroundFaultDetection(void);
#endif


s16 inputGroundFaultTicker;
u16 inputGroundFaultError;
void InputGroundFaultDetection(void);






u16 motorThermalOverLoadError;  // 电机过载
s16 inputOLStopStateError;      // 停机状态，输入电流超过30%
u16 tranTdOverLoadAlarm;        // 变压器过载报警
u16 tranTdOverLoadError;        // 变压器过载报错
s16 lineOverVolTicker;
u16 lineOverVolError;           // 电网输入电压超过120.0%
s16 lineOverVolBigTicker;
u16 lineOverVolBigError;        // 电网输入电压超过130.0%

s16 outputPhaseImbanlanceticker;
u16 outputPhaseImbanlanceError;

s16 inputPhaseImbanlanceticker;
u16 inputPhaseImbanlanceError;              // 输入电流不平衡
s16 inputPhaseLossTicker;
u16 inputPhaseLossError;                    // 输入缺相
u16 outputPhaseLossError;                   // 输出缺相
void InputPhaseImbalance(void);
void OutputPhaseImbalanceDetection(void);
void OutputPhaseLossDetect(void);
void LineOverVoltageFaultDetection(void);
void InputPhaseLossDetection(void);
void CoreErrorMiscDeal(void);
void InputVolImbalance(void);
void OutputVolImbalance(void);
void InputOLStopState(void);

u16 inCurOlFlag;
s16 motorOverVoltageTicker;
u16 motorOverVoltageError;
void MotorOverVoltageDetection(void);


s16 motorMagTicker;
u16 motorMagnetError;
void MotorMagnetErrorDetect(void);

#if DEBUG_P_ERR20
//s16 encoderLossTicker;
u16 encoderLossError;               // 编码器故障
u16 encoderFdbRightFlag;             // 编码器故障前纪录编码器反馈信号标记
bool encoderLossErrorOldFlag;        // 编码器故障快环使用标记
u16 encoderLossErrorCondition;      // 满足编码器故障判断条件
void EncoderLossDetection(void);
#endif


s16 inverterTdOverLoadError;    // 变频器过载标志
extern u16 udcHalfOverFlag;
extern f32 udcHalfOverVol;
extern u16 udcOverFlag;
extern f32 udcOverVol;


s16 bypassCellOverTicker;
u16 bypassCellOverError;
void BypassCellOver(void);

void HysterisisT(bool alarmState, s16 *alarmTicker, bool *state, s16 hysterisisLevel);



extern f32 inputVolFil;


s16 noMotorTicker;
u16 noMotorError;
void NoMotorDetection(void);



#if DEBUG_P_ERR95
u16 poweringFlag;   // 正在上电
f32 powerTicker;
f32 powerOffTicker;
#endif
//==============================================================================
//
// 性能故障处理
//
//==============================================================================
void CoreErrorDeal(void)
{
#if DEBUG_P_ERR95
    {
#define NO_F95_POWER_TIME   10  // 上电_s内不报F95
        u16 tmp;

        tmp = 1;
        if (inputVolFil > 0.5)
        {
            powerTicker += MAIN_LOOP_TIME;
            if (powerTicker >= NO_F95_POWER_TIME)
            {
                powerTicker = NO_F95_POWER_TIME;
                tmp = 0;
            }

            powerOffTicker = 0;
        }
        
        if (inputVolFil < 0.07)
        {
            powerOffTicker += MAIN_LOOP_TIME;
            if (powerOffTicker >= NO_F95_POWER_TIME)
            {
                powerOffTicker = NO_F95_POWER_TIME;
                tmp = 0;
            }

            powerTicker = 0;
        }

        poweringFlag = tmp;
    }

// 当没能进入快环中断时，报故障。
    {
        static u32 fastLoopTickerOld;
        extern u32 fastLoopTicker;
        extern u16 updateFpgaCarrierRegFlag;
        
        if (updateFpgaCarrierRegFlag)
        {
            if ((fastLoopTicker == fastLoopTickerOld) && (!poweringFlag))
            {
                if (!coreErrorCode)     // 上电_s内不报F95
                {
                    coreErrorCode = 95;
                }
            }
        }
        fastLoopTickerOld = fastLoopTicker;
    }
#endif

    CoreErrorMiscDeal();
    
    CoreErrorReset();
}



#define A_PHASE_LOSS 1
#define B_PHASE_LOSS 2
#define C_PHASE_LOSS 3
#define ABC_PHASE_LOSS 4

f32 motorOLInfo;               // 电机过载提示信息
u16 inputPhaseLossInfo;        // 输入缺相提示信息:1 = A_PHASE_LOSS 2 = B_PHASE_LOSS 3 = C_PHASE_LOSS
u16 outputPhaseLossInfo;       // 输出缺相提示信息
f32 inputPhaseImbanlanceInfo;  // 输入电流不对称提示信息
f32 encoderLossInfo;           // 编码器丢失提示信息
f32 outCurImbalanceInfo;       // 输出电流不平衡提示信息
f32 inputVolImbalanceInfo;     // 输入电压不对称提示信息
f32 outputVolImbalanceInfo;    // 输出电压不对称提示信息

// 故障复位处理
extern u16 ocFlag;
//extern void InitAd7606(void);
extern void UpdataFpgaCarrierReg(void);
//extern u16 ad7606SampleCnt;
//u16 hhghgoo;

//==============================================================================
//
// 性能故障复位
//
//==============================================================================
void CoreErrorReset(void)
{
    if (coreErrorCode)
    {
        if (coreSubCmd.bit.errorDealing)
        {
            
            if (95 == coreErrorCode)
            {
           //     InitAd7606();               // 重新复位AD7606。
                UpdataFpgaCarrierReg();     // 重新更新N1N2N3等
            }
 //           if (coreErrorCode == ERROR_AD_SAMPLE)
//            {
 //              InitAd7606();
//		       ad7606SampleCnt = 0;
//            }
            coreErrorCode = 0;
            
            ResetIoc();             // 复位(FPGA传递的)过流故障

            ocFlag = 0;
        }
    }

    if (coreAlarmCode)
    {

        if (coreSubCmd.bit.errorDealing)
        {
          //  hhghgoo++;
            // 报警复位
            coreAlarmCode = 0;
            // 报警提示信息复位
            motorOLInfo = 0;
            inputPhaseLossInfo = 0;
            outputPhaseLossInfo = 0;
            inputPhaseImbanlanceInfo = 0;
            encoderLossInfo = 0;
            outCurImbalanceInfo = 0;
            outputPhaseLossError = 0;
#if (INV_TYPE == HW_HD3x)
            udcHalfOverVol = 0;
#endif
        }
    }

    coreStatus.bit.coreErrorResetEnd = coreSubCmd.bit.errorDealing;
}

u16 inputVolImbalanceError;
u16 outputVolImbalanceError;
f32 inputEdNegSeqTotal;           // 输入电压负序分量有效值
f32 yNegSeqTotal;                 // 输出电压负序分量有效值
extern u16 excessiveLossFault;
extern u16 inputOneCycleFault;
//extern u16 sampleAbnormity;
extern f32 iNegSeqTotal;
extern f32 iInTotal;
extern f32 iInTotalFil;
extern f32 iTotalFilTd;
extern f32 iTotalMotor;
extern f32 outCurDataMax;
extern union CELL_BYPASS_FLAG cellBypassFlag;
extern struct CELL_OVERLOAD_PROTECT cellOlProtect;
extern f32 driveLosses;
//==============================================================================
//
// 
//
//==============================================================================
void CoreErrorMiscDeal(void)
{
    LineOverVoltageFaultDetection();
    MotorOverVoltageDetection();        // 电机过压保护
 #if !DEBUG_P_I_REG_ONLY
  //  MotorMagnetErrorDetect();           // 电机励磁故障
 #endif   
    InputPhaseLossDetection();
    InputPhaseImbalance();
    OutputPhaseImbalanceDetection();
    OutputPhaseLossDetect();            // 在OutputPhaseImbalanceDetection()之后调用。需要知道负序电流。
#if DEBUG_P_ERR20
    EncoderLossDetection();             // 编码器丢失故障
#endif
    OverLoadProtect();                  // 过载保护
    InputGroundFaultDetection();        // 输入对地阻抗偏小
#if DEBUG_P_OUT_GND
    OutputGroundFaultDetection();       // 输出对地阻抗偏小
#endif
//    SampleAbnormal();                   // 电流、电压采样异常判断
    BypassCellOver();                   // 旁路单元数超限
    InputVolImbalance();                // 输入电压不平衡
    OutputVolImbalance();               // 输出电压不平衡
    NoMotorDetection();                 // 输出未接电机，输出缺相故障   




    // 需要分断高压故障 //
    if ((coreErrorCode != ERROR_INPUT_VOL_BIG) && lineOverVolBigError)
    {
        coreErrorCode = ERROR_INPUT_VOL_BIG;
        coreErrorInfo = inputVolFil * driveParameterMenu.ratingInputVoltage / 1.05;//故障阈值放大了1.05倍，按照实际值提示
    }
   // else if ((coreErrorCode != ERROR_INPUT_OL) && (inCurOlFlag || inputOLStopStateError))
#if (INV_TYPE == HW_HD90)
    else if ((coreErrorCode != ERROR_INPUT_OL) && ( inputOLStopStateError))
    {
        coreErrorCode = ERROR_INPUT_OL;
        coreErrorInfo = iInTotalFil;
    }
#endif

    // 不需要分断高压故障 //
    if (!coreErrorCode)
    {
        coreErrorInfo = 0;                             // 保证无故障 无故障提示信息；有故障 提示信息可更新

        if (inputGroundFaultError)                     // 输入对地阻抗偏小
        {
//#if (INV_TYPE == HW_HD90)
            coreErrorCode = ERROR_TRANSFORMER_SHORT_TO_GND;
            coreErrorInfo = InputProcess.E0Average * 100.0;
//#endif
        }
#if (INV_TYPE == HW_HD90)
        else if (inCurOlFlag || tranTdOverLoadError)               // 根据变压器反时限曲线过载保护方式 报出的变压器轻过载
        {
            coreErrorCode = ERROR_INPUT_TD_OL;
            coreErrorInfo = iInTotalFil;
        }
#endif
        else if (lineOverVolError)                      // 电网输入电压超过120.0%
        {
//#if (INV_TYPE == HW_HD3x)
//            coreErrorCode = ERROR_OV_INPUT;
//#elif 1
            coreErrorCode = ERROR_OV_ACC_SPEED;
//#endif
            coreErrorInfo = inputVolFil;
        }
//#endif
#if DEBUG_P_OL
        else if (inverterTdOverLoadError)               // 变频器过载
        {
            coreErrorCode = ERROR_OL_INVERTER;
			
			if (driveParameterMenu.ratingOutputCurrent != 0)
			{
	            coreErrorInfo = cellOlProtect.cellCur * driveParameterMenu.ratingOutputCurrent * SQRT2;
			}
			else
			{
				coreErrorInfo = cellOlProtect.cellCur * motorPara.ratingCurrent * SQRT2;
			}
        }
#endif
        else if (motorOverVoltageError)                 // 电机过压
        {
        //    coreErrorCode = ERROR_MOTOR_OV;
        //    coreErrorInfo = OutputProcess.MotorVoltage;
        }
#if (INV_TYPE == HW_HD90)
        else if (excessiveLossFault)                    // 变频器损耗过大
        {
            coreErrorCode = EROR_EXCESSIVE_LOSS;
        }
        else if (inputOneCycleFault)                    // 变压器副边阻抗偏小，变频器输入无功过大
        {
            coreErrorCode = ERROR_INPUT_ONE_CYCLE;
            coreErrorInfo = driveLosses * 1000;
        }
#endif
#if DEBUG_P_OUT_GND
        else if (outputGroundFaultError)                // 输出对地阻抗偏小，Er023
        {
            coreErrorCode = ERROR_MOTOR_SHORT_TO_GND;
            coreErrorInfo = OutputProcess.E0Avg * 100.0;
        }
#endif
#if (INV_TYPE != HW_HD3x)
        else if (bypassCellOverError)                   // 旁路最小单元数超限
        {
            coreErrorCode = ERROR_BYPASS_CELL_OVER;
        }
#endif
      //  else if (sampleAbnormity)                       // 电流检测故障
      //  {
      //      coreErrorCode = ERROR_CURRENT_SAMPLE;
      //      coreErrorInfo = outCurDataMax;
     //   }
#if !DEBUG_P_I_REG_ONLY
        else if (motorMagnetError)
        {
            coreErrorCode = ERROR_MOTOR_MAGNET;         // 电机励磁故障
        }
#endif        
    }

    // 报警及报警提示信息//
    // 新加报警必须按以下格式书写：提示信息在前，报警代码在后 //
    // ALARM_OL_MOTOR 电机过载
#if DEBUG_P_OL
    if (motorThermalOverLoadError)
    {
        motorOLInfo = (coreAlarmCode & BIT0) ? 
						(motorOLInfo) : (iTotalMotor * motorPara.ratingCurrent * SQRT2);
        coreAlarmCode |= BIT0;
    }
#endif

    // ALARM_LOSE_PHASE_OUTPUT 输出缺相 
    coreAlarmCode = (outputPhaseLossError || noMotorError) ? (coreAlarmCode | BIT2) : coreAlarmCode;
    // coreAlarmCode = (outputPhaseLossError) ? (coreAlarmCode | BIT2) : coreAlarmCode;
    // ALARM_LOSE_PHASE_INPUT 输入缺相
    coreAlarmCode = (inputPhaseLossError) ? (coreAlarmCode | BIT1) : coreAlarmCode;

#if (INV_TYPE == HW_HD90)
    // ALARM_INPUT_CUR_IMBALANCE 输入电流不对称
    if (inputPhaseImbanlanceError)
    {
        inputPhaseImbanlanceInfo = (coreAlarmCode & BIT4) ? inputPhaseImbanlanceInfo :
                                        InputProcess.INegSeqTotal;
        coreAlarmCode |= BIT4;
    }
#endif

#if (INV_TYPE == HW_HD3x)   
// 半母线超限故障，需要跳高压
    coreAlarmCode = (udcHalfOverFlag) ? (coreAlarmCode | BIT11) : coreAlarmCode; 
#endif
#if DEBUG_P_ERR20
    // 编码器故障Err20
    if (encoderLossError)
    {
        f32 frequencyErrorTmp;
        frequencyErrorTmp = fabs(OutputProcess.EncoderSpeed - OutputProcess.FrequencyFiltered) / 
                                OutputProcess.RatedFrequency;
        encoderLossInfo = (coreAlarmCode & BIT7) ? encoderLossInfo : frequencyErrorTmp;
        coreAlarmCode |= BIT7;
    }
#endif

    // ALARM_OUTPUT_CUR_IMBALANCE 输出电流不对称
    if (outputPhaseImbanlanceError)            
    {
        outCurImbalanceInfo = (coreAlarmCode & BIT8) ? 
								(outCurImbalanceInfo) : (iNegSeqTotal * SQRT2 * motorPara.ratingCurrent);
        coreAlarmCode = (coreAlarmCode | BIT8);
    }

    // 输入电压不平衡
    if (inputVolImbalanceError)            
    {
        inputVolImbalanceInfo = (coreAlarmCode & BIT9) ? 
								(inputVolImbalanceInfo) : (inputEdNegSeqTotal * driveParameterMenu.ratingInputVoltage);
        coreAlarmCode = (coreAlarmCode | BIT9);
    }

    // 输出电压不平衡
    if (outputVolImbalanceError)            
    {
        outputVolImbalanceInfo = (coreAlarmCode & BIT10) ? outputVolImbalanceInfo : yNegSeqTotal;
        coreAlarmCode = (coreAlarmCode | BIT10);
    }
    
}







//==============================================================================
//
// 输入电流不平衡检测
// 
// 高压正常_s后才开始检查
//
//==============================================================================
void InputPhaseImbalance(void)
{
#if !DEBUG_PRG_IN_RAM
    bool faultFlag = FALSE;
    static f32 delay;

    InputProcess.INegSeqTotal = SqrtA2AddB2(InputProcess.IdNegSeq, InputProcess.IqNegSeq);


    if (OK != InputProcess.MediumVoltageStatus)
    {
        delay = 0;
    }
    else if (delay >= 1.5)  // 高压正常_s后才开始检查
    {
        faultFlag = (InputProcess.INegSeqTotal >= inputProtectMenu.phaseImbalanceLimit) ? TRUE : FALSE;
    }
    else
    {
        delay += MAIN_LOOP_TIME; 
    }

    Hysterisis(faultFlag, &inputPhaseImbanlanceticker, &inputPhaseImbanlanceError);
#endif
}





//==============================================================================
//
// 输出电流不平衡
//
//==============================================================================
extern f32 outPhaseNoBalanceSet;
f32 iNegSeqTotal;               // 一直在计算
void OutputPhaseImbalanceDetection(void)
{
#if !DEBUG_PRG_IN_RAM
    bool faultFlag = FALSE;
    f32 tmp = 0.008;            // 反馈频率很低时，负序电流认为一个固定的小值

    iNegSeqTotal = SqrtA2AddB2(OutputProcess.IdNegSeq, OutputProcess.IqNegSeq);

    if ((MAGNETIZING_STATE != DriveControl.State) && 
        (AUTO_TUNE_STATE != DriveControl.State)
       )
    {
        // 低于1Hz+额定转差时，不计算。相当于不判断 输出电流不平衡 与 输出缺相。
        if ((fabs(OutputProcess.MotorSpeedFiltered) > TWO_PI + OutputProcess.SlipRated) 
//            || (fabs(CommandGenerator.SpeedReference) > TWO_PI + OutputProcess.SlipRated)
            )
        {
            tmp = iNegSeqTotal;
            if (tmp >= outPhaseNoBalanceSet)
            {
                faultFlag = TRUE;
            }
        }
    }
    OutputProcess.INegSeqTotal = tmp;
    
    Hysterisis(faultFlag, &outputPhaseImbanlanceticker, &outputPhaseImbanlanceError);
#endif
}



#if DEBUG_P_OUT_PHASE_LOSS

#define OUT_PHASE_LOSS_T            400         // 输出缺相迟滞时间_ms(滤波时间固定)
#define OUT_PHASE_LOSS_CUR          0.010       // 缺相电流判断条件:还可适当减小至(敏感边界0.015-0.010迟钝边界)
#define OUT_PHASE_LOSS_SPEED_HZ     3.0         // 缺相判断条件:转速指令大于此值(敏感边界3Hz-5Hz迟钝边界),防止低频误报

struct PHASE_LOSS_STR uPhaseLoss;
struct PHASE_LOSS_STR vPhaseLoss;
struct PHASE_LOSS_STR wPhaseLoss;
u16 phaseLossEnable;
f32 phaseLossValue;
u16 phaseLossLevel;
f32 CursFilCalu,CursFilCalv,CursFilCalw;
f32 CursFilCalumax,CursFilCalvmax,CursFilCalwmax;
f32 CursFilCalumin,CursFilCalvmin,CursFilCalwmin;
f32 CursFilCalu1,CursFilCalv1,CursFilCalw1;
u16 PhaseLossInt;
extern u16 masterOrSlave;

void PhaseLossDetect(struct PHASE_LOSS_STR *p, u16 phaseLossEnable, f32 phaseLossValue, u16 phaseLossLevel);
//========================================================================================：
//目的:输出缺相检测
//输入:outCurData
//输出:outputPhaseLossError,outputPhaseLossInfo
//调用周期:2ms
//=========================================================================================/
void CurMaxcal()
{
	CursFilCalu = fabs(outCurData.u);
	CursFilCalv = fabs(outCurData.v);
	CursFilCalw = fabs(outCurData.w);

    CursFilCalu1 = CursFilCalu1 + CursFilCalu;
	CursFilCalv1 = CursFilCalv1 + CursFilCalv;
	CursFilCalw1 = CursFilCalw1 + CursFilCalw;
}

#define CUR_REF_LIMIT_Iq  (0.30)
#define CUR_FDB_LIMIT  (0.06)
extern f32 pllFluxSFrq;
u16 PlosInt = 800;
void OutputPhaseLossDetect(void)//10204
{

   // if ((PURE_VF != motorControlMode) &&
   if (
        (coreRunStatus.bit.run) &&
        (coreSubCmd.bit.outPhaseLossProtect) &&
        (coreMainCmd.bit.DCBrakeStatus == 0) &&
        (MAGNETIZING_STATE != DriveControl.State) &&
        (AUTO_TUNE_STATE != DriveControl.State) &&
        (SPINNING_LOAD_STATE != DriveControl.State) // 飞车启动过程不检测
	   )
	{
		phaseLossEnable = 1;
    }
	else
	{
	    phaseLossEnable = 0; 
		PhaseLossInt = 0;
		CursFilCalumax = 0;
		CursFilCalvmax = 0;
		CursFilCalwmax = 0;
		CursFilCalumin = 0;
		CursFilCalvmin = 0;
		CursFilCalwmin = 0;
		CursFilCalu1 = 0;
		CursFilCalv1 = 0;
		CursFilCalw1 = 0;
	}
//    phaseLossEnable = FALSE;
    if (phaseLossEnable)
	{
		PhaseLossInt++; // 计数开始
		CurMaxcal();    //计算MAX MIN
		if (PhaseLossInt > PlosInt)  //时间到了1秒？
		{			
			CursFilCalumax = CursFilCalu1 / (f32)PlosInt;
			CursFilCalvmax = CursFilCalv1 / (f32)PlosInt;
			CursFilCalwmax = CursFilCalw1 / (f32)PlosInt;

			if ((((CursFilCalumax > 0.08) || (CursFilCalvmax > 0.08) || (CursFilCalwmax > 0.08))
			&& ((CursFilCalumax < 0.02) || (CursFilCalvmax < 0.02) || (CursFilCalwmax < 0.02)))     
			|| ((CursFilCalumax < 0.02) && (CursFilCalvmax < 0.02) && (CursFilCalwmax < 0.02))
			)//满足报错条件？
			{
				outputPhaseLossError = 1;

				if((CursFilCalumax < 0.02) && (CursFilCalvmax < 0.02) && (CursFilCalwmax < 0.02))
				{
					//VF模式，三相没接电机，认为是在测试模式，不报输出缺相
					//同步机，三相电流小，不认为输出缺相，防止误报
                if(PURE_VF == motorControlMode)

                {
                    outputPhaseLossError = 0;
                }

				else if((PMSM_SVC == motorControlMode)||(PMSM_FVC == motorControlMode))

				 {
				   if ((fabs(OutputProcess.IqsRef) >= CUR_REF_LIMIT_Iq)&&(fabs(OutputProcess.IqsFil) <= CUR_FDB_LIMIT))
                    {
                       outputPhaseLossInfo = ABC_PHASE_LOSS;
                    }
				   else
				   {
				      outputPhaseLossError = 0;
				   }
				}

			    else
                  {
                        outputPhaseLossInfo = ABC_PHASE_LOSS;
                    }
				}
				/*
				if ((CursFilCalumax > 0.08) && (CursFilCalumax < 0.01))
				{
                    outputPhaseLossInfo = A_PHASE_LOSS;
				}
				else if ((CursFilCalvmax > 0.08) && (CursFilCalvmax < 0.01))
				{
                    outputPhaseLossInfo = B_PHASE_LOSS;
				}
				else if ((CursFilCalwmax > 0.08) && (CursFilCalwmax < 0.01))
				{
                    outputPhaseLossInfo = C_PHASE_LOSS;
				}*/
				if (((CursFilCalvmax > 0.08) || (CursFilCalwmax > 0.08)) && (CursFilCalumax < 0.02))
				{
                    outputPhaseLossInfo = A_PHASE_LOSS;
				}
				if (((CursFilCalumax > 0.08) || (CursFilCalwmax > 0.08)) && (CursFilCalvmax < 0.02))
				{
                    outputPhaseLossInfo = B_PHASE_LOSS;
				}
				if (((CursFilCalvmax > 0.08) || (CursFilCalumax > 0.08)) && (CursFilCalwmax < 0.02))
				{
                    outputPhaseLossInfo = C_PHASE_LOSS;
				}
			}
			else
			{
				//CursFilCalumax = 0;
		        //CursFilCalvmax = 0;
				//CursFilCalwmax = 0;
				CursFilCalu1 = 0;
				CursFilCalv1 = 0;
				CursFilCalw1 = 0;
			}
			PhaseLossInt = 0;

		}
	
	}

/*    phaseLossEnable = (
                       (OutputProcess.TotalCurrentFil > 0.15) &&
                       (fabs(CommandGenerator.SpeedReference) >=  OUT_PHASE_LOSS_SPEED_HZ * TWO_PI) &&
                       (coreRunStatus.bit.run) &&
                       (coreSubCmd.bit.outPhaseLossProtect) &&
                       (MAGNETIZING_STATE != DriveControl.State) &&
                       (AUTO_TUNE_STATE != DriveControl.State) &&
                       (PARA_INV_SLAVE != masterOrSlave)
                      );

    phaseLossValue = OUT_PHASE_LOSS_CUR;
    phaseLossLevel = OUT_PHASE_LOSS_T * I_MAIN_LOOP_TIME_MS;

    uPhaseLoss.cur = outCurData.u;
    vPhaseLoss.cur = outCurData.v;
    wPhaseLoss.cur = outCurData.w;


    // 双机并联，判断电机侧缺相
    if (masterOrSlave)
    {
        if (!PARA_WAY_SEL)
        {
            uPhaseLoss.cur = outCurData.u;
            vPhaseLoss.cur = outCurData.v;
            wPhaseLoss.cur = outCurData.w;
        }
        else if (1 == PARA_WAY_SEL)
        {
            uPhaseLoss.cur = outCurData.uParaInv;
            vPhaseLoss.cur = outCurData.vParaInv;
            wPhaseLoss.cur = outCurData.wParaInv;
        }
    }
    else
    {
        uPhaseLoss.cur = outCurData.u;
        vPhaseLoss.cur = outCurData.v;
        wPhaseLoss.cur = outCurData.w;
    }

    PhaseLossDetect(&uPhaseLoss, phaseLossEnable, phaseLossValue, phaseLossLevel);
    PhaseLossDetect(&vPhaseLoss, phaseLossEnable, phaseLossValue, phaseLossLevel);
    PhaseLossDetect(&wPhaseLoss, phaseLossEnable, phaseLossValue, phaseLossLevel);

    outputPhaseLossError = (uPhaseLoss.phaseLossState || vPhaseLoss.phaseLossState || wPhaseLoss.phaseLossState
                            ) ? TRUE : FALSE;

    if (uPhaseLoss.phaseLossState)
    {
        outputPhaseLossInfo = A_PHASE_LOSS;
    }
    else if (vPhaseLoss.phaseLossState)
    {
        outputPhaseLossInfo = B_PHASE_LOSS;
    }
    else if (wPhaseLoss.phaseLossState)
    {
        outputPhaseLossInfo = C_PHASE_LOSS;
    }*/
}



/*========================================================================================：
目的:缺相检测函数
输入:struct PHASE_LOSS_STR、缺相使能phaseLossEnable、缺相阈值phaseLossValue、缺相滤波时间phaseLossLevel
输出:缺相状态phaseLossState
调用周期:2ms
*=========================================================================================*/
void PhaseLossDetect(struct PHASE_LOSS_STR *p, u16 phaseLossDetectEnable, f32 phaseLossDetectValue, u16 phaseLossDetectLevel)
{
    if (phaseLossDetectEnable)
    {
        if (p->cur <= phaseLossDetectValue)                       // 缺相判断及滤波
        {
            p->phaseLossicker++;
            p->phaseLossicker = GetMin(p->phaseLossicker, phaseLossLevel);      // 计时器饱和
        }
        else
        {
            p->phaseLossicker = 0;
        }
    }
    else
    {
        p->phaseLossicker = 0;
    }

    p->phaseLossState = (p->phaseLossicker >= phaseLossDetectLevel) ? TRUE : FALSE;
}

#elif 1

void OutputPhaseLossDetect(void){}

#endif



#if (INV_TYPE == HW_HD3x)

#define OVER_VOLTAGE_SET    1.10               //输入过压点根据过检要求设置
#define OVER_VOLTAGE_SET_OPEN_INPUT    1.4    //输入跳闸点和母线电压上限点一致

#elif 1

#define OVER_VOLTAGE_SET    1.2
#define OVER_VOLTAGE_SET_OPEN_INPUT    1.4

#endif
//f32 OVER_VOLTAGE_SET = 1.2;
//==============================================================================
//
// 电网输入电压过高
//
//==============================================================================
u16 inputVolFiltest = 0;

void LineOverVoltageFaultDetection(void)
{
    bool faultFlag;
   //HD33 输入电压过压 由ARM报出来，DSP值负责输入电压超限和母线超限
    faultFlag = (inputVolFil > OVER_VOLTAGE_SET) ? TRUE : FALSE;
   
#if (INV_TYPE == HW_HD3x) 
    faultFlag = FALSE;
#endif

    Hysterisis(faultFlag, &lineOverVolTicker, &lineOverVolError);
    
#if !DEBUG_PRG_IN_RAM
    faultFlag = (inputVolFil > OVER_VOLTAGE_SET_OPEN_INPUT) ? TRUE : FALSE;

	if(inputVolFil > OVER_VOLTAGE_SET_OPEN_INPUT)
	{
		inputVolFiltest++;
	}
    Hysterisis(faultFlag, &lineOverVolBigTicker, &lineOverVolBigError);
#endif
}





u16 aInputPhaseLossTicker, bInputPhaseLossTicker, cInputPhaseLossTicker;
//==============================================================================
//
// 输入缺相处理，Err12
//
//==============================================================================
void InputPhaseLossDetection(void)
{
#if !DEBUG_PRG_IN_RAM
    bool alarmFlag = false;
    u32 inVolDataMin;
    u32 tmp1, tmp2, tmp3;
    u16 inVolPhaseLossTickerMax;
    
    if ((inputVolFil > 0.5) &&
        (coreSubCmd.bit.inPhaseLossProtect) &&
        (InputProcessDisplay.Erms > 0.6) && 
        (InputProcess.eUnbalance > 0.30)
#if (INV_MODEL == INV_3300)
		&&
		(motorControlOtherEnable.bit.inVol == 1)//3300有输入电压采样才进行输入缺相保护
#endif
       )
    {
        alarmFlag = true;

        tmp1 = (u32)(fabs(inVolData.u) * 10000.0);
        tmp2 = (u32)(fabs(inVolData.v) * 10000.0);
        tmp3 = (u32)(fabs(inVolData.w) * 10000.0);
        inVolDataMin = GetMin3(tmp1, tmp2, tmp3);
        if (inVolDataMin == tmp1)
        {
            aInputPhaseLossTicker++;
        }
        else if (inVolDataMin == tmp2)
        {
            bInputPhaseLossTicker++;
        }
        else
        {
            cInputPhaseLossTicker++;
        }
    }
    else
    {
        aInputPhaseLossTicker = 0;
        bInputPhaseLossTicker = 0;
        cInputPhaseLossTicker = 0;
    }
    
    Hysterisis(alarmFlag, &inputPhaseLossTicker, &inputPhaseLossError);

    // 缺相相序检测
    inVolPhaseLossTickerMax = GetMax3(aInputPhaseLossTicker, bInputPhaseLossTicker, cInputPhaseLossTicker);
    
    if (inputPhaseLossError)
    {
        if (aInputPhaseLossTicker == inVolPhaseLossTickerMax)
        {
            inputPhaseLossInfo = A_PHASE_LOSS;
        }
        else if (bInputPhaseLossTicker == inVolPhaseLossTickerMax)
        {
            inputPhaseLossInfo = B_PHASE_LOSS;
        }
        else
        {
            inputPhaseLossInfo = C_PHASE_LOSS;
        }
    }
#endif

#if (INV_MODEL == INV_3300)
	if(cfGroup[18] == 1)
	{
		inputPhaseLossError = 1;
	}
#endif

}






f32 motorTripVoltage;       // 电机过压保护点，100.0%对应电机额定电压
#define MOTOR_OVER_VOL_DELAY    2000    // 满足判断条件延迟__ms
//==============================================================================
//
// 电机过压故障检测
//
//==============================================================================
void MotorOverVoltageDetection(void)
{
#if !DEBUG_PRG_IN_RAM
    bool alarmFlag = false;
    static s16 delay;

    if ((TRUE == OutputProcess.Enable) &&
        (SPINNING_LOAD_STATE != DriveControl.State) &&
        (AUTO_TUNE_STATE != DriveControl.State)
        )
    {
        if (delay > MOTOR_OVER_VOL_DELAY / MAIN_LOOP_TIME_MS)
        {
            if (OutputProcess.MotorVoltage > motorTripVoltage)
            {
                alarmFlag = true;
            }
        }
        else
        {
            delay++;
        }
    }
    else
    {
        delay = 0;
    }

    Hysterisis(alarmFlag, &motorOverVoltageTicker, &motorOverVoltageError);
#endif
}




extern struct FLUX_REGULATOR_STR fluxRegData;
extern f32 fluxFdb;

#define     MOTOR_MAG_LIMIT     0.35        // 磁链给定与反馈之差阈值
#define     MOTOR_MAG_MAX       5000        // 故障判断维持__ms
//==============================================================================
//
// 电机励磁故障检测
// 判断磁链给定与反馈相差很大，且维持一段时间后报错
//
//==============================================================================
void MotorMagnetErrorDetect(void)
{
#if !DEBUG_PRG_IN_RAM
    bool faultFlag = false;
    static u16 motorMagnetErrorTicker;
    
    if ((coreRunStatus.bit.run) &&
        (inputVolFil > 0.5) &&                          // 上高压
        (RUN_STATE == DriveControl.State) &&            // 正常运行状态下
        (OutputProcess.ControlAlgorithm != PURE_VF)     // VF控制不检测
        )
    {
        if (fabs(fluxRegData.fluxRef - fluxFdb) > MOTOR_MAG_LIMIT)          
        {           
            if (motorMagnetErrorTicker > MOTOR_MAG_MAX/MAIN_LOOP_TIME_MS)
            {
                faultFlag = TRUE;
            }
            else
            {
                motorMagnetErrorTicker++;
            }
        }
        else
        {
            motorMagnetErrorTicker = 0;
        }
    }
    else
    {
        motorMagnetErrorTicker = 0;
    }

    Hysterisis(faultFlag, &motorMagTicker, &motorMagnetError);
#endif
}


#if DEBUG_P_ERR20
//u16 encoderLossT = 200;
f32 encoderSpeedOld;
extern u16 clControl;
extern f32 fluxFdbFil;
extern f32 encoderSpeedFil;
extern f32 svcSpeedEst;
enum ENCODERLOSS_DETECT_MODE encoderLossdetectMode;

#define ENCODERLOSS_TICKER_MAX  2000 // ms 
//#define ENCODER_LOSS_SPEED_HZ     2.0     // 编码器丢失故障低于(包含)__ Hz不检测
#define ENCODERLOSS_BEGIN_MAX   5           // 编码器判断最大拍

//==============================================================================
//
// 编码器丢失故障检测
// 编码器反馈频率，与估算的速度之间相差较大时，可以认为编码器丢失。
//
//==============================================================================
void EncoderLossDetection(void)
{
    bool alarmFlag = false;
    static u16 encoderLossTicker;
    static u16 encoderLossBeginTicker;

    if ((TRUE == OutputProcess.Enable) && 
        (IDLE_STATE != DriveControl.State) &&  
        (MAGNETIZING_STATE != DriveControl.State) &&    // 预励磁阶段不检测
        (PLL_FREQUENCY_VALID == SpinningLoad.Status) && // 锁相环有效
        (0.0 != corePgPara.elem.encoderLossLimit) &&
        (clControl) &&                                  // 闭环控制才检测
        (fluxFdbFil > 0.50 * fluxCtrlMenu.fluxDemand)
       )
    {
        encoderLossErrorCondition = TRUE;   // 编码器故障检测条件

        switch(encoderLossdetectMode)
        {
            case ENCODERLOSS_DETECT_BEGIN:  // 编码器故障检测第一阶段
                encoderLossTicker++;
                if (encoderLossTicker <= ENCODERLOSS_TICKER_MAX/SLOW_LOOP_TIME_MS)   // 小于2s
                {
                    if (fabs(OutputProcess.EncoderSpeed - svcSpeedEst) >
                        (f32)corePgPara.elem.encoderLossLimit * (1.0/1000) * OutputProcess.RatedFrequency
                       )
                    {
                        encoderLossBeginTicker++;
                        encoderFdbRightFlag = true;     // 出现编码器信号异常时就纪录
                        encoderLossErrorOldFlag = true;
                        if (encoderLossBeginTicker >= ENCODERLOSS_BEGIN_MAX)
                        {
                            alarmFlag = true;
                            encoderLossBeginTicker = 0;
                            encoderLossdetectMode = ENCODERLOSS_DETECT_END;
                        }
                        else
                        {
                            encoderLossdetectMode = ENCODERLOSS_DETECT_BEGIN;
                        }                                                
                    }
                    else
                    {
                        encoderLossBeginTicker = 0;
                        encoderFdbRightFlag = false;
                        encoderLossdetectMode = ENCODERLOSS_DETECT_BEGIN;
                    }
                }
                else
                {
                    encoderLossTicker = 0;    
                    encoderLossdetectMode = ENCODERLOSS_DETECT_CONTINUE;
                }
                break;

            case ENCODERLOSS_DETECT_CONTINUE:   // 编码器故障检测第二阶段
                if (fabs(encoderSpeedOld - OutputProcess.EncoderSpeed) > 
                        3.0 * OutputProcess.SlipRated   // 上一拍编码器反馈与当前拍编码器反馈速度之差大于3倍额定转差
                    )
                {
                    alarmFlag = true;
                    encoderFdbRightFlag = true;
                    encoderLossErrorOldFlag = true;
                    encoderLossdetectMode = ENCODERLOSS_DETECT_END;
                } 
                else
                {
                    encoderLossdetectMode = ENCODERLOSS_DETECT_CONTINUE;
                }
                break;

            case ENCODERLOSS_DETECT_END:    // 编码器故障检测结束
                encoderLossBeginTicker = 0;
                break;
            default:
                break;
        }

    }
    else
    {
        encoderLossdetectMode = ENCODERLOSS_DETECT_BEGIN;
        encoderLossErrorCondition = false;
        encoderLossErrorOldFlag = false;
    }

//    HysterisisT(alarmFlag, &encoderLossTicker, &encoderLossError, encoderLossT);

    if (TRUE == OutputProcess.Enable)
    {
        if (!encoderLossError)
        {
            encoderLossError = alarmFlag;
        }
    }
    else
    {
        encoderLossError = alarmFlag;
        encoderLossErrorOldFlag = false;
        encoderFdbRightFlag = false;    // 停机时，编码器反馈前一拍清零
    }
    

//    Hysterisis(alarmFlag, &encoderLossTicker, &encoderLossError);

// 出现编码器信号丢失时，记录丢失前一拍的编码器反馈速度
    if (!encoderFdbRightFlag)
    {   
        encoderSpeedOld = OutputProcess.EncoderSpeed;    
    }
}
#endif




//==============================================================================
//
// 输入对地阻抗偏小故障检测
//
//==============================================================================
void InputGroundFaultDetection(void)
{
#if !DEBUG_PRG_IN_RAM
    bool faultFlag = FALSE;

    if (OK == InputProcess.MediumVoltageStatus)
    {
        faultFlag = (InputProcess.E0Average >= inputProtectMenu.groundFaultLimit);
    }

    if (inputProtectMenu.groundFaultLimit)
    {
        Hysterisis(faultFlag, &inputGroundFaultTicker, &inputGroundFaultError);
    }
    else
    {
        inputGroundFaultTicker = 0;
        inputGroundFaultError = 0;
    }
#endif
}





//==============================================================================
//
// 输出对地阻抗偏小故障检测
//
//==============================================================================
#if DEBUG_P_OUT_GND
// 在RAM中调试时，注意相关程序是否打开、相关变量是否赋值。
// (outputGroundFaultLimit, outputGroundFaultGainR, OutputProcess.Y0DC, OutputProcess.Y0Avg)

f32 outputGroundFaultLimit;     // F9-28 输出对地阻抗偏小故障阈值
//f32 outputGroundFaultGainR;     // 输出对地阻抗偏小滤波增益R
#define OUTPUT_GROUND_FAULT_DELAY   2000    // 输出对地阻抗偏小，电机运行延迟一段时间才检测，_ms
//s16 OUTPUT_GROUND_FAULT_DELAY = 2000;       // 启动前缺一相，延迟时间长一些报输出缺相

void OutputGroundFaultDetection(void)
{
    static s16 delay;
    bool faultFlag = FALSE;
    f32 tmp;

    if (TRUE == OutputProcess.Enable)
    {
        if  ((UP_TRANSFER_STATE == DriveControl.State) || 
             (DOWN_TRANSFER_STATE == DriveControl.State) ||
             ((AUTO_TUNE_STATE == DriveControl.State))||
             (ROTOR_INITIAL_STATE == DriveControl.State)
            )
        {
            delay = 0;
        }
        else if (delay > OUTPUT_GROUND_FAULT_DELAY / MAIN_LOOP_TIME_MS)
        {
// 根据e0伏秒值，计算实际值
// 请参考CurVolRmsCalc()中计算输出电压有效值
            tmp = (fluxStatorObserverMenu.lowFrqWo > 30.0) ? CALC_VOL_A1 : CALC_VOL_A;
            OutputProcess.E0Avg = tmp * motorPara.iFPuOmegaOne * 
                (OutputProcess.Y0Avg * SqrtA2AddB2(OutputProcess.Frequency, CALC_VOL_B)
                 + OutputProcess.Y0DC * CALC_VOL_B
                );

            OutputProcess.E0Avg = fabs(OutputProcess.E0Avg);
            faultFlag = (OutputProcess.E0Avg >= outputGroundFaultLimit);
        }
        else
        {
            delay++;
        }
    }
    else
    {
        delay = 0;
        OutputProcess.E0Avg = 0;
    }

    if (outputGroundFaultLimit)
    {
       // Hysterisis(faultFlag, &outputGroundFaultTicker, &outputGroundFaultError);
    }
    else
    {
        outputGroundFaultTicker = 0;
        outputGroundFaultError = 0;
    }
}
#endif




//==============================================================================
//
// 旁路单元数超限
//
//==============================================================================
void BypassCellOver(void)
{
#if ((INV_TYPE == HW_HD90) && (!DEBUG_PRG_IN_RAM))
    bool faultFlag = false;

    if ((inputVolFil > 0.5) &&                      // 上高压
        (cellCheckFlag.bit.cellFirstChkArmOk)       // 单元自检完成后
        )
    {
        faultFlag = cellBypassFlag.bit.bypassCellfaultFlag;
    }    

    Hysterisis(faultFlag, &bypassCellOverTicker, &bypassCellOverError);    
#endif
}


//==============================================================================
//
// 滞环处理
//
//==============================================================================
void Hysterisis(bool alarmState, s16 *alarmTicker, bool *state)
{
    if (FALSE == alarmState)
    {
        if (*alarmTicker > 0)
        {
            (*alarmTicker)--;
        }
    }
    else
    {
        if (*alarmTicker < HYSTERISIS_LEVEL)
        {
            (*alarmTicker)++;
        }
    }

    if (HYSTERISIS_LEVEL == *alarmTicker)
    {
        *state = TRUE;
    }
    else if (0 == *alarmTicker)
    {
        *state = FALSE;
    }
}




#if 0
//==============================================================================
//
// 滞环处理
// 时间可以通过参数hysterisisLevel设置
// hysterisisLevel单位为ms
//
//==============================================================================
void HysterisisT(bool alarmState, s16 *alarmTicker, bool *state, s16 hysterisisLevel)
{
    if (FALSE == alarmState)
    {
        if (*alarmTicker > 0)
        {
            (*alarmTicker)--;
        }
    }
    else
    {
        if (*alarmTicker < hysterisisLevel * I_MAIN_LOOP_TIME_MS)
        {
            (*alarmTicker)++;
        }
    }

    if (hysterisisLevel * I_MAIN_LOOP_TIME_MS == *alarmTicker)
    {
        *state = TRUE;
    }
    else if (0 == *alarmTicker)
    {
        *state = FALSE;
    }
}
#endif






#if DEBUG_P_OL

/*
const struct CELL_CUR_Tim cellCurTim3L[] =      // 电流必须由大到小，并且不允许两组电流相等
{
    {2.0,  1 },
    {1.8,  10},                                 // 以上三组数据为估计值
    {1.5,  20},                                 // HD92过载测试数据{cur/1PU,olTim/s}
    {1.4,  50},                                 // 以下参数为由测试数据按Td运算求得
    {1.3,  100},   
    {1.2,  150},
    {1.1,  360},
    {1.05, 600}
};
*/
#if (INV_MODEL == INV_1140)

const struct CELL_CUR_Tim cellCurTim3L[] =      // 电流必须由大到小，并且不允许两组电流相等
{
	{2.0,  1 },
    {1.8,  10},									// 以上二组数据为估计值
	{1.7,  20},
    {1.65, 27},                                 
    {1.6,  35},
    {1.55, 45},
    {1.5,  90},                                 // 以上三组数据为估计值
    {1.45, 150},                                 // HD92过载测试数据{cur/1PU,olTim/s}
    {1.4,  180},                                 // 以下参数为由测试数据按Td运算求得
    {1.35, 330},   
    {1.3,  800},
    {1.25, 1900},
    {1.2,  3276},
	{1.1,  6600},
	{1.05, 9800}
};
	
#elif (INV_MODEL == INV_3300)

const struct CELL_CUR_Tim cellCurTim3L[] =      // 电流必须由大到小，并且不允许两组电流相等
{
    {2.0,  1 },
    {1.8,  10},                                 // 以上三组数据为估计值
    {1.5,  60},                                 // 过载测试数据{cur/1PU,olTim/s}
    //{1.4,  78},                                 // 以下参数为由测试数据按Td运算求得
    //{1.3,  108},
    {1.2,  3600},
    //{1.1,  357},
    //{1.05, 731},
};

#endif

struct MOTOR_OVERLOAD_PROTECT motorOlProtect;   
struct TRANSFORMER_OVERLOAD_PROTECT transformerOlProtect;     
u16 cellCurTimeNum;
s16 transformerOLMode;  // 变压器过载保护方式选择:1默认反时限曲线 2反时限表格

void OverLoadProtectMotor(void);                                                      // 电机过载保护程序
void InputOL(void);
void OverLoadProtectTransformer(void);                                              // 变压器过载保护程序               
void OverLoadProtectCell(const struct CELL_CUR_Tim *,struct CELL_OVERLOAD_PROTECT *);  // 单元过载
void OverLoadTime(const struct CELL_CUR_Tim *, f32);                                   // 单元过载时间计算
void CellReduceRatingFun(void);
/*========================================================================================*
过载保护函数：
目的：根据不同过载保护对象，在不同的过所允许的过载运行间，对保护对象作反时限过载保护；
输出：过载错误指令；
过载保护函数，调用周期:2ms
*=========================================================================================*/
void OverLoadProtect(void)      		 
{
    OverLoadProtectMotor();
/*
#if (INV_TYPE == HW_HD90)
    if ((CELL_TYPE_690 == cellMenu.cellVoltage) ||
        (CELL_TYPE_690_DURIAN == cellMenu.cellVoltage) 
        )
    {
        cellCurTimeNum = SIZEOF(cellCurTim2L);                  // HD90电流-时间组数
        OverLoadProtectCell(cellCurTim2L, &cellOlProtect);
    }
    else if (CELL_TYPE_AFE_1140 == cellMenu.cellVoltage)
    {
        cellCurTimeNum = SIZEOF(cellCurTim3L);                  // HD92电流-时间组数
        OverLoadProtectCell(cellCurTim3L, &cellOlProtect);
    }
#elif (INV_TYPE == HW_HD3x) 
*/
    cellCurTimeNum = SIZEOF(cellCurTim3L);                      // HD3x
    OverLoadProtectCell(cellCurTim3L, &cellOlProtect);
//#endif
/*
    
    CellReduceRatingFun();
#if (INV_TYPE == HW_HD90) 
    if (CUR_TIME_INVERATIO_TABLE == transformerOLMode)
    {
        InputOL();
    }
    else
    {
        OverLoadProtectTransformer();
    }
    InputOLStopState();
#endif
*/
}


#define TD_RATING_CUR_MOTOR         1.05        // 电机反时限过载保护额定电流,1*IN->1.05*IN，防止误报
#define TD_RATING_CUR_BASE_MOTOR    1.2         
/*============================================================================================*
电机过载保护函数：
      目前仅做了F9-00 = 0(禁止电机过载保护)和F9-00 = 1(直接反时限过载保护)
目的：根据不同过载保护对象，在不同的过所允许的过载运行时间，对保护对象作反时限过载保护；
输入：电机过载使能、电机的过载系数和过载运行时间，默认1.2IN过载60s;
输出：Error11过载错误指令；
过载保护计算公式: 
      热容量            td = 过载时间time * (过载保护阈值olCoef^2 - 额定电流tdRatedCur^2)
      每拍增加的热量值  heat = MAIN_LOOP_TIME * (实际电流iTotalFilTd^2 - 额定电流tdRatedCur^2)
==============================================================================================*/
void OverLoadProtectMotor(void)
{
    f32 heat;           // 每拍累加的热量
    f32 tdRatedCur;     // 电机反时限过载保护额定电流
 
    tdRatedCur = (motorOlProtect.olCoef >= TD_RATING_CUR_BASE_MOTOR) ? 
        TD_RATING_CUR_MOTOR : 
        (motorOlProtect.olCoef * (TD_RATING_CUR_MOTOR / TD_RATING_CUR_BASE_MOTOR));
        
    motorOlProtect.td = motorOlProtect.time *
        (motorOlProtect.olCoef * motorOlProtect.olCoef - tdRatedCur * tdRatedCur);
    
//    if (1 == motorOlProtect.enable)     // 开启电机过载软件保护
    if (0 != motorOlProtect.enable)     // 开启电机过载软件保护，F9-00设置为非0
    {
        heat = ((iTotalMotor * iTotalMotor - tdRatedCur * tdRatedCur) * MAIN_LOOP_TIME);
        motorOlProtect.thermal += heat;        
        motorOlProtect.thermal = GetMax(motorOlProtect.thermal, 0.0);
        
        motorOlProtect.predict = 
            (motorOlProtect.thermal >= motorOlProtect.td * motorOlProtect.predictCoef) ? 1 : 0; // 电机过载预警
        motorThermalOverLoadError = (motorOlProtect.thermal >= motorOlProtect.td) ? 1 : 0;      // 电机过载报错
    }
    else if (0 == motorOlProtect.enable)    // 禁止电机过载软件保护
    {
        motorOlProtect.thermal = 0;
        motorOlProtect.predict = 0;
        motorThermalOverLoadError = 0;
    }
    else                                    // F9-00衰减反时限对电机无保护
    {
        ;
    }
}



#define OL_TIME_TRANSFORMER         60     // 变压器过载保护动作时间
#define HEAT_DEREASE_T_TRANSFORMER  300    // 小于额定电流对应的散热时间:发生过载故障后，需降额运行6至10min，将热量全部散尽
#define TD_RATING_CUR_TRANSFORMER   1.05   // 变压器反时限过载保护额定电流
#define OL_ONCE_TRANSFORMER_TIME    600    // 10min允许过载一次
#define OL_RUN_TRANSFORMER_TIME     10     // 过载后，可再次继续过载10s(按1.2/60s定义)，应小于OL_TIME_TRANSFORMER

u32 tranTimer;                              // 本次发生变压器过载时刻
u32 tranPreTimerPointer;                    // 上次发生变压器过载时刻
s16 tranTimerPointerEnd;                    // thermal上升沿定位结束
f32 tranPreThermal;                         // thermal > Td，上次thermal上升沿时刻thermal值
f32 tranPreThermalSum;                      // 计算并保存本次上升沿之前累加的tranThermal，以td为基值
f32 tranThermalSum;
f32 ktLimit;                                // 本次thermal上升沿，允许运行时间
f32 ktPreLimit;                             // 上次thermal上升沿，允许运行时间

/*========================================================================================*
变压器过载保护函数：
目的：对变压器作反时限过载保护；
输入：变压器过载使能;
      HD92多绕组变压器技术协议的过载能力要求: 1.5倍过载60s，偶尔过载
      HD90多绕组变压器技术协议的过载能力要求: 1.2倍过载60s，偶尔过载
输出：tranTdOverLoadError不需分断高压；
公式: 参见电机过载保护函数说明 
过载保护函数，调用周期:2ms
*=========================================================================================*/
void OverLoadProtectTransformer(void)
{
    f32 heat;                                           // 每拍累加的热量
    f32 transformerCur;
    f32 k0, kt;
    f32 ktThermalPreSection;                            // thermal上次上升到本次上升沿之间累加的热量
    f32 ktThermalNowSection;                            // thermal上升过程中计算自本次上升沿累加的热量

    /*变压器过载保护开关
      停机状态下，InputOLStopState()过载保护；运行状态下，OverLoadProtectTransformer()过载保护
      目的:断开IO板和主控板排线，iInTotal会很大，如果启用OverLoadProtectTransformer()短时间积累太多热量
      导致再重新接线排线，热量还未散出，仍报错*/
    transformerOlProtect.enable = ((CUR_TIME_INVERATIO_CURVE == transformerOLMode) && (OK == InputProcess.MediumVoltageStatus))? TRUE : FALSE;//合上高压以后再报这个故障
    transformerOlProtect.time = OL_TIME_TRANSFORMER;    // 变压器过载保护动作时间，单位/s
    transformerCur = iInTotalFil;
    
    if (CELL_TYPE_AFE_1140 == cellMenu.cellVoltage)
    {
        transformerOlProtect.olCoef = 1.5;              // 变压器过载保护阈值，基值:变压器额定电流 
    }
    else if (CELL_TYPE_690 == cellMenu.cellVoltage)
    {
        transformerOlProtect.olCoef = 1.2;
    }
    else
    {
        transformerOlProtect.olCoef = 1.2;
    }

    transformerOlProtect.td = transformerOlProtect.time * 
        (transformerOlProtect.olCoef * transformerOlProtect.olCoef - 
         TD_RATING_CUR_TRANSFORMER * TD_RATING_CUR_TRANSFORMER);

    // k0 = 1 / 6
    // kt = 1 / (600 - 120) * (1 - 1 / 6)
    // ktLimit = (k0 + t * kt)
    // ktThermalLimit  = (1 / 6 + (t / 480) * (1 - 1 / 6)) * TD = ktLimit * TD
    k0 = OL_RUN_TRANSFORMER_TIME * (1.0 / OL_TIME_TRANSFORMER);
    kt = (1 / (OL_ONCE_TRANSFORMER_TIME - 2.0 * OL_TIME_TRANSFORMER) * (1 - k0));

    // 输入电流小于变压器额定电流时对应的散热时间均设定为HEAT_DEREASE_T_TRANSFORMER
    if (transformerCur < 1)
    {
        heat = -transformerOlProtect.td / HEAT_DEREASE_T_TRANSFORMER;
    }
    else if ((1 <= transformerCur) && (transformerCur < TD_RATING_CUR_TRANSFORMER))    // [1, 1.05)
    {
        heat = 0;
    }
    else //if (transformerCur >= TD_RATING_CUR_TRANSFORMER)
    {
        heat = transformerCur * transformerCur - TD_RATING_CUR_TRANSFORMER * TD_RATING_CUR_TRANSFORMER;
    }

    heat *= MAIN_LOOP_TIME;

    if (transformerOlProtect.enable)
    {                
        transformerOlProtect.thermal += heat;
        transformerOlProtect.thermal = GetMax(transformerOlProtect.thermal, 0.0);

        if (transformerOlProtect.thermal >= transformerOlProtect.td)
        {
            tranTdOverLoadAlarm = 1;            // 第一发生过载，报警

            if (heat > 0)
            {
                // 保存温度上升沿数据
                if (!tranTimerPointerEnd)
                {
                    ktLimit = k0 + (tranTimer * MAIN_LOOP_TIME) * kt;  // [1/6, 1]

                    // 考虑10min钟内两次升温时刻之间时间段的热量累加效果(升温时间点确定条件:heat > 0)
                    // tranPreThermal为上次升温时刻对应的热量
                    tranPreThermal = GetMax(tranPreThermal, transformerOlProtect.td); // 防止第一拍Prethermal小于td
                    ktThermalPreSection = transformerOlProtect.thermal - tranPreThermal;

                    ktPreLimit = k0 + (tranPreTimerPointer * MAIN_LOOP_TIME) * kt;    // [1/6, 1]
                    tranPreThermalSum +=  ktThermalPreSection / ktPreLimit;
                    // tranPreTimerPointer为上次升温时刻对应的时刻
                    // tranPreThermal为上次升温时刻对应的温度
                    tranPreTimerPointer = tranTimer;
                    tranPreThermal = transformerOlProtect.thermal;
                    tranTimerPointerEnd = 1;
                }

                // 上升沿过程中报错
                ktThermalNowSection = transformerOlProtect.thermal - tranPreThermal;
                tranThermalSum = ktThermalNowSection / ktLimit + tranPreThermalSum;

                if ((tranThermalSum > transformerOlProtect.td) && 
                    (tranTimer <= OL_ONCE_TRANSFORMER_TIME / MAIN_LOOP_TIME))
                {
                    tranTdOverLoadError = 1;
                }
            }
            else
            {
                tranTimerPointerEnd = 0;      // tranTdTimerPointerEnd清零
            }

            if ((tranTimer >= OL_ONCE_TRANSFORMER_TIME / MAIN_LOOP_TIME) &&
                (tranThermalSum <= transformerOlProtect.td))
            {
                transformerOlProtect.thermal = 0;
            }
            
            tranTimer++;
        }
        else
        {
            // 计时器及标记清零
            tranTimer = 0;
            tranTimerPointerEnd = 0;
            tranPreThermal = 0;
            // 报警及报错复位
            tranTdOverLoadAlarm = 0;
            tranTdOverLoadError = 0;
            // thermal清零
            tranThermalSum = 0;
            tranPreThermalSum = 0;
        }
    }
    else
    {
        // 计时器及标记清零
        tranTimer = 0;
        tranTimerPointerEnd = 0;
        tranPreThermal = 0;
        // 报警及报错复位
        tranTdOverLoadAlarm = 0;
        tranTdOverLoadError = 0;
        // thermal清零
        tranThermalSum = 0;
        tranPreThermalSum = 0;
        transformerOlProtect.thermal = 0;
    }
}



#define INPUT_OL_CUR_IDLE_STATE 0.3        // 停机时，输入电流超过30%
#define INPUT_OL_TIME_IDLE_STATE 10        // 停机时，输入电流超过30%，并且持续10s
extern u16 errorProtectOtherEnable1;
s16 inputOlStopStateTicker;
s16 inputOLStopStateEnable;
/*========================================================================================*
变频器停机状态，输入电流超过30%，DSP报错函数：
目的:1)停机时，输入电流超过0.3，并且持续10s，报错；
输入:1)iInTotal(仅使用)
输出:1)inCurOlFlag，需分断高压
调用周期:2ms
*=========================================================================================*/
void InputOLStopState (void)
{
    // inputOLStopStateEnable = (errorProtectOtherEnable1 && BIT4)&&( (OK == InputProcess.MediumVoltageStatus)) ? 1 : 0;//F9-72  bit4 为1  表示该功能打开，为0 表示该功能关闭
    inputOLStopStateEnable = (errorProtectOtherEnable1 && BIT4) ? 1 : 0;//F9-72	bit4 为1  表示该功能打开，为0 表示该功能关闭
    if (
        (iInTotalFil >= INPUT_OL_CUR_IDLE_STATE) &&
        (!coreRunStatus.bit.run) &&
        (TRUE == inputOLStopStateEnable)
        )
    {
        if (!inputOLStopStateError)
        {
            inputOlStopStateTicker++;
        }
    }
    else
    {
        inputOlStopStateTicker--;
        
        if (inputOlStopStateTicker < 0)
        {
            inputOlStopStateTicker = 0;
        }
    }

    inputOLStopStateError = (inputOlStopStateTicker >= INPUT_OL_TIME_IDLE_STATE * I_MAIN_LOOP_TIME) ? 
        TRUE : FALSE;
}




#define INPUT_CUR_LIMIT1            1.2         // 变频器额定电流的_倍
#define INPUT_CUR_TICKER_LIMIT1     60 //120         // _s
#define INPUT_CUR_LIMIT2            1.5         // 变频器额定电流的_倍
#define INPUT_CUR_TICKER_LIMIT2     20//40          // _s
#define INPUT_CUR_LIMIT3            1.65        // 变频器额定电流的_倍
#define INPUT_CUR_TICKER_LIMIT3     5//10          // _s


// 输入电流过载
f32 inCurOlTicker1;
f32 inCurOlTicker2;
f32 inCurOlTicker3;
u16 inCurOlFlag1;
u16 inCurOlFlag2;
u16 inCurOlFlag3;

//==============================================================================
//
// 输入过载
//
//==============================================================================
void InputOL(void)
{
   if (OK == InputProcess.MediumVoltageStatus)
   {
       if (iInTotalFil > INPUT_CUR_LIMIT1)
       {
            if (inCurOlTicker1 < INPUT_CUR_TICKER_LIMIT1 / MAIN_LOOP_TIME)
                inCurOlTicker1++;
            else
                inCurOlFlag1 = TRUE;
       }
       else
       {
           inCurOlTicker1 = inCurOlTicker1 - 2.0;		
           if (inCurOlTicker1 < 0)
               inCurOlTicker1 = 0;
           if (inCurOlTicker1 == 0)
           {
               inCurOlFlag1 = FALSE;
           }
       }

    
#if !DEBUG_PRG_IN_RAM
    if (iInTotalFil > INPUT_CUR_LIMIT2)
    {
        if (inCurOlTicker2 < INPUT_CUR_TICKER_LIMIT2 * I_MAIN_LOOP_TIME)
            inCurOlTicker2++;
        else
            inCurOlFlag2 = TRUE;
    }
    else
    {
        inCurOlTicker2 = inCurOlTicker2 - 0.666;        //可以复位时间变为60S
        if (inCurOlTicker2 < 0)
            inCurOlTicker2 = 0;
        if (inCurOlTicker2 == 0)
        {
            inCurOlFlag2= FALSE;
        }
    }
    
    if (iInTotalFil > INPUT_CUR_LIMIT3)
    {
        if (inCurOlTicker3 < INPUT_CUR_TICKER_LIMIT3 * I_MAIN_LOOP_TIME)
            inCurOlTicker3++;
        else
            inCurOlFlag3 = TRUE;
    }
    else
    {
        inCurOlTicker3 = inCurOlTicker3 - 0.16;
        if (inCurOlTicker3 < 0)
            inCurOlTicker3 = 0;
        if (inCurOlTicker3 == 0)
        {
            inCurOlFlag3= FALSE;
        }
    }
#endif

    inCurOlFlag = FALSE;
    if (inCurOlFlag1  
        || inCurOlFlag2 
        || inCurOlFlag3  
       )
    {
        inCurOlFlag = TRUE;
    }
}
}



#define CELL_OL_TIME_MIN      0.01             // 电流大于cellCurTim最大值所对应的最小过载运行时间/s
#define PREDICT_TIM           10               // 提前预报警时间/s
#define DEREASE_RATING_TIM    600              // 发生过载后，设定降额运行，所允许的降额运行时间/s
#define HEAT_DEREASE_CUR_CELL 0.91             // 散热基准电流:0.91IN在10min内将热量全部散出
#define HEAT_DEREASE_T_CELL   600              // 0.91IN 600s内将热量全部散出/停机后 103s将热量散出 
struct CELL_OVERLOAD_PROTECT cellOlProtect = 
{
    1,                                         // 单元过载保护默认打开
    0,                                         // 每拍增加的热量初始化值
    900                                        // 单元热容量初始化值
};
f32 reduceRatingTimer;                         // 降额运行时间计数
u16 reduceRatingCell;                          // 降额运行标识:reduceRatingCell == 1
/*========================================================================================*
单元过载保护函数：
目的：对单元作反时限过载保护；
输入：单元过载cellCurTim表格；
输出：提前10s报过载预警/若过载时间小于10s，立即报过载预警；Error10过载错误指令/降额运行
公式: 参见电机过载保护函数说明
过载保护函数，调用周期:2ms
*=========================================================================================*/
void OverLoadProtectCell(const struct CELL_CUR_Tim *p, struct CELL_OVERLOAD_PROTECT *q)
{
    f32 predictThermal;
    f32 heatDereaseTd;                                           // 散热能力选用的Td(0.91IN在10min内将热量全部散出)
	f32 currentCoeff;
	if(funcCode.code.OlProtectCoff == 0)
    {
		currentCoeff = 1.0;
	}
	else
	{
		currentCoeff = (f32)funcCode.code.OlProtectCoff * 0.01;
	}
    q->enable = 1;
	if (driveParameterMenu.ratingOutputCurrent != 0)
	{
    	q->cellCur = currentCoeff * iTotalFilTd * motorPara.ratingCurrent / driveParameterMenu.ratingOutputCurrent;
	}
	else
	{
		q->cellCur = currentCoeff * iTotalFilTd ;
	}
	heatDereaseTd = (HEAT_DEREASE_CUR_CELL * HEAT_DEREASE_CUR_CELL - 1 * 1) * (-HEAT_DEREASE_T_CELL);
        
    // 不同单元电流对应的过载过载时间计算    
    if ((0 <= q->cellCur) && (q->cellCur <= 2 - (p + cellCurTimeNum - 1)->cur))             // [0,(2-1.05)]PU:散热能力
    {  
        q->olTime = heatDereaseTd / (q->cellCur * q->cellCur - 1);       
    }
    else if (((p + cellCurTimeNum - 1)->cur <= q->cellCur) && (q->cellCur <= (p + 0)->cur))  // [1.05,1.5/2.5]PU:发热能力
    {
        OverLoadTime(p, q->cellCur);
    }
    else if (q->cellCur > (p + 0)->cur)                                                       // (cur > 1.5/2.5)PU
    {
        q->olTime = CELL_OL_TIME_MIN;    
    }

    // 每拍累加的热量值
    q->heat = ((2 - (p + cellCurTimeNum - 1)->cur < q->cellCur) && 
               (q->cellCur < (p + cellCurTimeNum - 1)->cur)
              ) ? 0 : (q->td / q->olTime * MAIN_LOOP_TIME);

    // 过载使能
    if (q->enable)
    {        
        q->thermal += q->heat;      	
        q->thermal = GetMax(q->thermal, 0);

        // (0 < olTime < PREDICT_TIM)立即报警;(olTime > PREDICT_TIM)提前PREDICT_TIM报警
        predictThermal = (q->olTime - PREDICT_TIM) / q->olTime * q->td;
        q->predict = (q->thermal >= predictThermal) ? 1 : 0;                            // 单元过载预报警
        inverterTdOverLoadError = (q->thermal >= (q->td * 0.98)) ? 1 : 0;               // ERR10报错
 		//inverterTdOverLoadError = (q->thermal >= (q->td * 0.98)) ? 0 : 0;
        // 降额有效:1)过载保护使能；2)F9-47故障动作选择为降额运行；
        if ((inverterTdOverLoadError) && (1 == coreRunStatus.bit.run))
        {
            reduceRatingCell = 1;
        }
        if (1 == reduceRatingCell)
        {
            reduceRatingTimer += 0.002;
        }

        // 目前发生过载后，DSP即停机，暂无降额运行
        // 降额动作不使能:1)过载保护不使能；2)F9-47故障动作选为报错；3)降额运行持续600s，停机等效为降额运行
        if (reduceRatingTimer >= DEREASE_RATING_TIM)
        {
            reduceRatingCell = 0;
            reduceRatingTimer = 0;
        }
    }
    else
    {
        q->thermal = 0;                         
        q->predict = 0;    
        inverterTdOverLoadError = 0;
        reduceRatingCell = 0;
        reduceRatingTimer = 0;
    }
}



f32 iqMaxReduceRating;                  // 降额运行最大转矩电流限幅值
extern f32 idRef;
#define REDUCE_RATING_REF 0.95          // 降额运行时，输出电流限幅值 
/*========================================================================================*
目的：求取过载保护降额运行时iqRef限幅值
输入：1)过载保护使能;2)过载保护动作选定降额运行
输出：iqMaxReduceRating；
调用周期:2ms
*=========================================================================================*/
void CellReduceRatingFun(void)
{
    f32 reduceRatingCurCell;

    if ((cellOlProtect.enable) && (reduceRatingCell))
    {
        reduceRatingCurCell = REDUCE_RATING_REF * driveParameterMenu.ratingOutputCurrent / motorPara.ratingCurrent;
        iqMaxReduceRating = SqrtA2SubB2(reduceRatingCurCell, idRef);
    }
}



/*========================================================================================*
求取单元过载时间函数：
目的：根据单元cellCurTim表格，求取当前电流(仅限cellCurTim的电流范围)对应的过载时间；
输入：1)单元过载cellCurTim表格;2)当前电流值
输出：过载运行时间cellOlProtect.olTime；
调用周期:2ms
*=========================================================================================*/
void OverLoadTime(const struct CELL_CUR_Tim *p, f32 cur)
{
    s16 i;
    f32 delta;

    for (i = 0; i < cellCurTimeNum; i++)
    { 		 				
        if (cur - (p + i)->cur >= 0)              // (x1,y1)=(p[i-1].cur,p[i-1].time)  (x2,y2)=(p[i].cur,p[i].time)
        {                    	
            delta = ((p + i)->time - (p + i - 1)->time) / ((p + i)->cur - (p + i - 1)->cur);
            cellOlProtect.olTime = (cur - (p + i - 1)->cur) * delta + (p + i - 1)->time;
            break;                    
        }
    }
}



s16 inVolRPZeroPointTicker, inVolSPZeroPointTicker;     // 输入电压采样值过零点时快环拍数
s16 outVolUPZeroPointTicker, outVolVPZeroPointTicker;   // 输出电压采样值过零点时快环拍数
s16 inCurRPZeroPointTicker, inCurTPZeroPointTicker;     // 输入电流采样值过零点时快环拍数
s16 outCurUPZeroPointTicker,outCurWPZeroPointTicker;    // 输出电流采样值过零点时快环怕数

// 断IU+15V电源-0.682V 断-15V电源+0.72V
#define FL_SAMPLE_ALARM 0.5       // 停机时，输出电流霍尔+-15V电源接线有问题时，如果IU测试点电压高于此值，报错
//u16 sampleAbnormity;              // 采样异常报错标记
s16 sampleAbnormalOutVol, sampleAbnormalOutCur; // 输出电压、输出电流采样异常标记(传给ARM作为故障提示)
s16 sampleAbnomityEnable;                       // 采样异常使能开关(电流检测故障ERR18): 0 禁止；1 默认开启
s16 sampleSequenceEnable;                       // 采样相序计算程序使能开关：0代表禁止；1代表使能，默认关闭
s16 sampleAlarmTicker, samplePhaseTicker;
f32 outCurDataMax;                              // 输出电流达到X倍电机额定电流

struct SAMPLE_PHASE_DELAY samplePhaseDelay;
/*========================================================================================*
电流采样异常报错函数：
目的:1)霍尔电源未接(停机状态，报ERR18)；
     2)调试使用:采样相序计算
     (仅作调试使用:1)空载低频VF运行；2)F6-10 = 1自由停车方式)
输入:1)FL_SAMPLE_ALARM，THREE_PHASE_CURRENT_SAMPLE outCurData(仅使用)
输出:1)sampleAbnormity
调用周期:2ms
*=========================================================================================*/
/*
void SampleAbnormal (void)
{
    bool alarmFlag = false;
    f32 flSampleAlarmBase;              // FL_SAMPLE_ALARM电压值对应的输出电流标幺值
    s16 flPowerError;                   // 霍尔电源接线
    f32 tmp1, tmp2, tmp3;
    f32 tickerInPu, tickerOutPu;
    f32 inVolPhaseSeq = 0;                  // 输入电压: R相超前S相角度:正序范围
    f32 outVolPhaseSeq = 0;                 // 输出电压: U相超前V相角度:正序范围
    f32 inCurPhaseSeq = 0;                  // 输入电流: T相超前R相角度:正序范围
    f32 outCurPhaseSeq = 0;                 // 输出电流: W相超前U相角度:正序范围


    if (sampleSequenceEnable)
    {
        tickerInPu = pwmT * 360 * fabs(InputProcess.Frequency) * I_TWO_PI;
        
        // 采样相序计算慢环处理
        inVolPhaseSeq = (inVolSPZeroPointTicker - inVolRPZeroPointTicker) * tickerInPu;
        inVolPhaseSeq = (inVolPhaseSeq < -180) ? (inVolPhaseSeq + 360) : inVolPhaseSeq;
        inVolPhaseSeq = (inVolPhaseSeq > 180) ? (inVolPhaseSeq - 360) : inVolPhaseSeq;

        inCurPhaseSeq = (inCurRPZeroPointTicker - inCurTPZeroPointTicker) * tickerInPu;
        inCurPhaseSeq = (inCurPhaseSeq < -180) ? (inCurPhaseSeq + 360) : inCurPhaseSeq;
        inCurPhaseSeq = (inCurPhaseSeq > 180) ? (inCurPhaseSeq - 360) : inCurPhaseSeq;

        if (TRUE == coreRunStatus.bit.run)
        {
            tickerOutPu = pwmT * 360 * OutputProcess.Frequency * I_TWO_PI;

            outVolPhaseSeq = (outVolVPZeroPointTicker - outVolUPZeroPointTicker) * tickerOutPu;
            outVolPhaseSeq = (outVolPhaseSeq < -180) ? (outVolPhaseSeq + 360) : outVolPhaseSeq;
            outVolPhaseSeq = (outVolPhaseSeq > 180) ? (outVolPhaseSeq - 360) : outVolPhaseSeq;

            outCurPhaseSeq = (outCurUPZeroPointTicker - outCurWPZeroPointTicker) * tickerOutPu;
            outCurPhaseSeq = (outCurPhaseSeq < -180) ? (outCurPhaseSeq + 360) : outCurPhaseSeq;
            outCurPhaseSeq = (outCurPhaseSeq > 180) ? (outCurPhaseSeq - 360) : outCurPhaseSeq;
        }

        samplePhaseDelay.inVolDisp = LPF_GainR(inVolPhaseSeq, samplePhaseDelay.inVolDisp, 0.005);
        samplePhaseDelay.outVolDisp = LPF_GainR(outVolPhaseSeq, samplePhaseDelay.outVolDisp, 0.005);
        samplePhaseDelay.inCurDisp = LPF_GainR(inCurPhaseSeq, samplePhaseDelay.inCurDisp, 0.005);
        samplePhaseDelay.outCurDisp = LPF_GainR(outCurPhaseSeq, samplePhaseDelay.outCurDisp, 0.005);
    }
    else
    {
        samplePhaseDelay.inVolDisp = 0;
        samplePhaseDelay.outVolDisp = 0;
        samplePhaseDelay.inCurDisp = 0;
        samplePhaseDelay.outCurDisp = 0;
    }

    // 停机状态，如果测试点IU/IV电压值大于FL_SAMPLE_ALARM，则报
    // 双机并联，检测流
    if (masterOrSlave)
    {
        if (!PARA_WAY_SEL)
        {
            tmp1 = fabs(outCurData.u0ParaInv);
            tmp2 = fabs(outCurData.v0ParaInv);
            tmp3 = fabs(outCurData.w0ParaInv);
        }
        else if (1 == PARA_WAY_SEL)
        {
            tmp1 = fabs(outCurData.u0);
            tmp2 = fabs(outCurData.v0);
            tmp3 = fabs(outCurData.w0);
        }
    }
    else
    {
        tmp1 = fabs(outCurData.u0);
        tmp2 = fabs(outCurData.v0);
        tmp3 = fabs(outCurData.w0);
    }
    
    outCurDataMax = GetMax3(tmp1, tmp2, tmp3);
    flSampleAlarmBase = FL_SAMPLE_ALARM * outCurData.scaler / (10.0 / 32768);
    flPowerError = ((!coreRunStatus.bit.run) && (outCurDataMax >= flSampleAlarmBase)) ? TRUE : FALSE;
   
    if (sampleAbnomityEnable && flPowerError)
    {
        alarmFlag = TRUE;
    }

    Hysterisis(alarmFlag, &sampleAlarmTicker, &sampleAbnormity);
}
*/


/*求取过零点拍数*/
#define CroZeroPointTimerMacro(previous, now, zeroTicker, ticker)    \
{                                                   \
    if (((previous) < 0.0) && ((now) >= 0.0))       \
    {                                               \
        (zeroTicker) = (ticker);                    \
    }                                               \
                                                    \
    (previous) = (now);                             \
}


extern u32 fastLoopTicker;

void SamplePhaseCalc(void);
/*========================================================================================*
采样相序计算函数：
目的:计算采样电压电流A、B相位差，从而判断采样线是否接反及三相采样量相位不对称度，作为调试时参考
输入:三相采样电流、电压值
输出:过零点拍数,用时3微秒
调用周期:pwmT
*=========================================================================================*/
void SamplePhaseCalc (void)
{
    if (sampleSequenceEnable)
    {
        static f32 inVolRP, inVolSP;
        static f32 inCurRP, inCurTP;
        static f32 outVolUP, outVolVP;
        static f32 outCurUP, outCurWP;
        f32 inCurU, inCurW, outCurU, outCurW;

// 根据硬件实际采样电流判断相序
        inCurU = inCurData.u;
        inCurW = inCurData.w;
        outCurU = outCurData.u;
        outCurW = outCurData.w;

#if (HW_CELL_ALL_FUNC != HW_CELL)   // 非全功能小样机
        inCurU = inCurData.v;
        inCurW = inCurData.u;
        outCurU = outCurData.v;
        outCurW = outCurData.u;
#endif
        // 输入电压RS相位延迟计算
        CroZeroPointTimerMacro(inVolRP, inVolData.u, inVolRPZeroPointTicker, fastLoopTicker);
        CroZeroPointTimerMacro(inVolSP, inVolData.v, inVolSPZeroPointTicker, fastLoopTicker);
        
        // 输出电压UV相位延迟计算
        CroZeroPointTimerMacro(outVolUP, outVolData.u, outVolUPZeroPointTicker, fastLoopTicker);
        CroZeroPointTimerMacro(outVolVP, outVolData.v, outVolVPZeroPointTicker, fastLoopTicker);  
        
        // 输入电流RS相位延迟计算
        CroZeroPointTimerMacro(inCurRP, inCurU, inCurRPZeroPointTicker, fastLoopTicker);
        CroZeroPointTimerMacro(inCurTP, inCurW, inCurTPZeroPointTicker, fastLoopTicker);
        
        // 输出电流UV相位延迟计算
        CroZeroPointTimerMacro(outCurUP, outCurU, outCurUPZeroPointTicker, fastLoopTicker);
        CroZeroPointTimerMacro(outCurWP, outCurW, outCurWPZeroPointTicker, fastLoopTicker);
    }
}




#elif 1


//u16 sampleAbnormity;
struct SAMPLE_PHASE_DELAY samplePhaseDelay;
struct MOTOR_OVERLOAD_PROTECT motorOlProtect;
f32 outCurDataMax;



void OverLoadProtect(void){}
void SamplePhaseCalc (void){}
//void SampleAbnormal (void){}


#endif

s16 inputVolImbalanceTicker;
f32 inputvolimbalanceLimit;

//==============================================================================
//
// 输入电压不平衡，输入电压负序分量判断
//
//==============================================================================
void InputVolImbalance(void)
{
#if !DEBUG_PRG_IN_RAM
    bool faultFlag = false;

    inputEdNegSeqTotal = SqrtA2AddB2(InputProcess.EdNegative, InputProcess.EqNegative);

    if ((inputVolFil > 0.5) &&                      // 上高压
        (0.0 != inputvolimbalanceLimit)
        )
    {
        if (inputEdNegSeqTotal > inputvolimbalanceLimit)          
        {
            faultFlag = TRUE;
        }        
    }    

    Hysterisis(faultFlag, &inputVolImbalanceTicker, &inputVolImbalanceError);    
#endif
}

s16 outputVolImbalanceTicker;
f32 outputvolimbalanceLimit;
extern f32 ydNegSeq1;
extern f32 yqNegSeq1;
#define OUTPUT_VOL_IMBALANCE_DELAY   1500    // 输出电压不平衡故障，电机运行延迟一段时间才检测，_ms
//==============================================================================
//
// 输出电压不平衡，输出电压伏秒负序分量判断
//
//==============================================================================
void OutputVolImbalance(void)
{
#if !DEBUG_PRG_IN_RAM
    bool faultFlag = false;
    static s16 delay;

    yNegSeqTotal = SqrtA2AddB2(ydNegSeq1, yqNegSeq1);

    if ((inputVolFil > 0.5) &&                              // 上高压
        (0.0 != outputvolimbalanceLimit) &&
        (coreMainCmd.bit.run) &&                            // 运行时
        (AUTO_TUNE_STATE != DriveControl.State) &&          // 调谐时不检测
        (SPINNING_LOAD_STATE != DriveControl.State)         // 飞车启动过程不检测
        )
    {        
        if (delay > OUTPUT_VOL_IMBALANCE_DELAY / MAIN_LOOP_TIME_MS)
        {
            if (yNegSeqTotal > outputvolimbalanceLimit)
            {
                faultFlag = TRUE;
            }            
        }
        else
        {
            delay++;
        }
    }
    else
    {
        delay = 0;
    }

    Hysterisis(faultFlag, &outputVolImbalanceTicker, &outputVolImbalanceError);    
#endif
}

#define NO_MOTOR_CUR_REF_LIMIT_Id  (0.10)
#define NO_MOTOR_CUR_REF_LIMIT_Iq  (0.30)
#define NO_MOTOR_CUR_FDB_LIMIT  (0.06)
// 有误报的可能？？？
//==============================================================================
//
// 输出没有接电机时，报故障。防止报F23, F55等。
// 暂时报输出缺相。
//
//==============================================================================
void NoMotorDetection(void)
{
    extern f32 iTotalFdb;
    u16 faultFlag = 0;
    u16 faultFlag_id = 0;
    u16 faultFlag_iq = 0;
    
    if ((OutputProcess.ControlAlgorithm != PURE_VF) && 
        (OutputProcess.ControlAlgorithm != SIN_ONLY) &&
        (coreRunStatus.bit.run) &&
        (coreSubCmd.bit.outPhaseLossProtect) && 
        (AUTO_TUNE_STATE != DriveControl.State) &&      // 调谐过程不检测
        (SPINNING_LOAD_STATE != DriveControl.State) &&  // 飞车启动过程不检测
        (MAGNETIZING_STATE != DriveControl.State)       // 预励磁过程不检测
       )
    {
        if (fabs(OutputProcess.IdsRef) >= NO_MOTOR_CUR_REF_LIMIT_Id)
        {
            if (fabs(OutputProcess.IdsFil) <= NO_MOTOR_CUR_FDB_LIMIT)
            {
                faultFlag_id = 1;
            }
        }
        if (fabs(OutputProcess.IqsRef) >= NO_MOTOR_CUR_REF_LIMIT_Iq)
        {
            if (fabs(OutputProcess.IqsFil) <= NO_MOTOR_CUR_FDB_LIMIT)
            {
                faultFlag_iq = 1;
            }
        }

        if ((faultFlag_id) && (faultFlag_iq))
        {
            faultFlag = 1;
        }

        Hysterisis(faultFlag, &noMotorTicker, &noMotorError);

		if(noMotorError == 1)
		{
	        outputPhaseLossInfo = A_PHASE_LOSS + B_PHASE_LOSS + C_PHASE_LOSS;
		}

    }
    else
    {
        noMotorTicker = 0;
        noMotorError = 0;
    }
    
}







