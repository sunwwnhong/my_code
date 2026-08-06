//==================================================================================================
//
// 输出处理，
// 定子磁链定向
// 
// 快环，慢环
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================




#include "m_main.h"
#include "m_interface.h"
#include "m_input.h"
#include "m_frqSrc.h"
#include "m_cell.h"
#include "m_cell_bypass.h"
#include "m_autoTune.h"
#include "m_autoTunePmsm.h"
#include "m_spinningLoad.h"
#include "m_transfer.h"
#include "m_brake.h"
#include "m_fluxStatorObserve.h"
#include "m_currentLoop.h"
#include "m_speedLoop.h"
#include "m_fluxLoop.h"
#include "m_slip.h"
#include "m_modInterpUpdate.h"
#include "m_peakReduction.h"
#include "m_deadbandComp.h"
#include "m_npc.h"
#include "pmsvc.h"
#include "m_macro_sm.h"
#include "m_macro_tune.h"
#include "m_macro_transfer.h"
#include "m_macro_lowFrq.h"
#include "m_macro_error.h"
#include "m_macro_loadSharing.h"
#include "m_accDecDeal.h"
#include "m_speedRollback.h"
#include "m_error.h"
#include "funcCode.h"
#include "m_ImSVC4CalcFlux.h"
#include "m_ImSvc3Include.h"

#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_P_ONLY_SIN            1       // 
#define DEBUG_P_SAVE_ENERGY         1
#elif 1                 // 程序放在RAM中调试
#define DEBUG_P_ONLY_SIN            0
#define DEBUG_P_SAVE_ENERGY         0
#endif





#define PEAK_REDUCTION          1      // peak reduction处理

#define DEBUG_P_I_REG_ONLY      0      // 仅调试电流闭环，调试使用

#if DEBUG_P_I_REG_ONLY
RAMP_CTRL_STRUCT idSetRamp1;
RAMP_CTRL_STRUCT iqSetRamp1;
#endif


#if DEBUG_FUNCTION_IN_RAM   // 将部分函数放到RAM中，加快运行速度 
#pragma CODE_SECTION(OutputFastLoopSfoc   ,     "ramfuncs");
#pragma CODE_SECTION(UpdateFpgaVoltageData,     "ramfuncs");
#pragma CODE_SECTION(OutputProcessSlowLoop,     "ramfuncs");
//#pragma CODE_SECTION(DqTo2ndTheta,     "ramfuncs");
#endif
#pragma DATA_SECTION(OutputProcess, "data_ram");


struct OutputProcessType OutputProcess; // 输出处理结构体
struct VOL_CMD_TO_FPGA outputVol;       // 传递给FPGA的电压指令


struct FLUX_STATOR_OBSERVE_STR fluxSData;
struct PHASE_LOCK_LOOP_STR pllDataBackEmf;
struct PHASE_LOCK_LOOP_STR pllDataS;
struct MAGNETIZING_CURRENT_REG_STR idRegData;
struct TORQUE_CURRENT_REG_STR iqRegData;
struct PEAK_REDUCTION_STR peakReductionData;
struct CELL_VOLTAGE_REGULATOR_STR cellVoltageRegulator;
struct FLUX_REGULATOR_STR fluxRegData;
struct SPEED_REGULATOR_STR spdRegData;

#define minimumPllFlux  0.04        // 有效锁相环的最小磁通

#define OUT_PLL_KP  160.0
#define OUT_PLL_KI  0.8

#define EMF_PLL_KP  188.0
#define EMF_PLL_KI  1.025

//? 环流与电机运行有区别
struct PiDataType OutputProcessPllParams =
//    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   0.417,    70.0, 0.0, 0.0};
//    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   1.025,    188.0, 0.0, 0.0};
//    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   0.3,      30.0,  0.0, 0.0}; // 贵州样机参数
//    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   1.0,      150.0, 0.0, 0.0};
//    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   0.3,      30.0};
    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   OUT_PLL_KI,      OUT_PLL_KP};   // PLL的PID增强
//    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   0.3,      50.0};    // 斯可络机器，带1140V电机时，参数弱一点电流波形好一些
//    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   0.2,      20.0};    // 斯可络机器，带1140V电机时，参数弱一点电流波形好一些
struct PiDataType BackEMFPllParams =
//    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   1.0,    100.0, 0.0, 0.0};
//    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   1.025,    188.0, 0.0, 0.0};
//    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   1.5,    500.0, 0.0, 0.0};
//    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   1.025,    188.0};
    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   EMF_PLL_KI,    EMF_PLL_KP};


//#define IdLoopOutMax_K      0.35    // id电流环输出限幅，0.3,0.4,0.5
#define IdLoopOutMax_K  (1.5) //电光防爆 0.8，急加速要设置大一些
//f32 IdLoopOutMax_K = 0.5;
#define SpdFdbFilTimeConst  4       // 1/2,1/4滤波
//#define SpdFdbFilTimeConst  8
//f32 SpdFdbFilTimeConst = 4.0;
extern f32 pllOutMax;
f32 fluxLoopOutMax;                 // 磁链环输出限幅
f32 idLoopOutMax;                   // id电流环输出限幅，0.3,0.4
#define iqLoopOutMax  (2.5)             // iq电流环输出限幅，0.5,1.25
f32 idLoopOutMax1;
u16 motorControlMode;               // F0-01 电机控制方式
f32 pwmT;                           // 快环周期，可以考虑删除
f32 spdRef;                         // 速度环给定
f32 spdFdb;                         // 速度环反馈
f32 idRef;                          // id给定
f32 iqRef;                          // iq给定
f32 idFdb;                          // id反馈
f32 iqFdb;                          // iq反馈
f32 fluxFdb;                        // flux反馈
f32 volAmpl;                        // 输出电压指令的幅值
f32 svcSpeedEst;                    // SVC辨识的电机速度
f32 syncFrqEst;
f32 outputProcessFrqSum;            // 求OutputProcess.Frequency在一个速度环周期的平均值
u16 outputProcessFrqTicker;
u16 speedLoopSpinEnable;            // 1-使能速度环。飞车启动，速度搜索期间，不使能速度环
f32 biasGain;
f32 internalPeakVoltageClampLimit;
f32 iInternalPeakVoltageClampLimit; // 1.0/internalPeakVoltageClampLimit
f32 torqCurRegLimit = 1.00;
f32 modulationIndex;
f32 coreCarrierFrqAct = 750;        // (单元的)(实际使用的)载波频率，给一个初值，防止为0时OutputProcess.FastLoopFrequency也为0 
// FPGA启动AD采样的频率为 OutputProcess.FastLoopFrequency
f32 deadTimeComp;                   // A5-00 死区补偿时间

f32 curLoopFeedForwardGain;         // A5-01 电流环前馈增益
f32 fluxLoopFeedForwardGain;        // A5-02 磁链环前馈增益
f32 zeroSpeedSet;                   // 
f32 pllFluxSFrq;                    // 同步频率
f32 deltaSPLL;                      // 定子磁链的相位
f32 pllBackEmfFrq;                  // 反电动势进行PLL的频率
f32 vds;                            // 励磁电流环的输出
f32 vqs;                            // 转矩电流环的输出
f32 cellDCVoltage;                  // 单元母线电压
f32 outVoltagePrg;                  // (程序)输出电压，叠频制动之前
u16 polePairs;                      // 电机极对数
u16 smControl;                      // F0-01控制方式选择了同步机。1-表示同步机控制
u16 clControl;                      // 1-表示闭环控制
u16 flux__Src;
u16 previousPllStatus  = PLL_FREQUENCY_NOT_VALID;
f32 DqTo2ndVdCal,DqTo2ndVqCal;
f32 DqTo2ndVdSamp,DqTo2ndVqSamp;
f32 DqTo2ndid,DqTo2ndiq;
union CELL_BYPASS_FLAG cellBypassFlag;
struct NPC_DATA npcData;
extern Uint16 coreCarrierFrq;
extern int32 frqMotorRun;
extern f32 coreUpperTorque;
extern f32 upperTorqueRegen;
extern u16 activeCells[3];
extern u16 reset_flag;
extern u32 cellBypassCmdNew;        // 加入手动更改T1_T2旁路后的旁路接触器命令
extern STATISTICS_STRUCT adc7606IsrTime;
extern Uint16 coreTuneCmd;
extern u16 encoderLossError;
extern u16 encoderLossErrorCondition;
extern Uint16 cellOffsetRegMirror[MAX_CELLS];
extern u16 brakeEnable;
extern f32 coreMaxFrqRads;
extern f32 inputVolDis;
extern f32 inputVolFil;
extern union DSP_SUB_STATUS coreSubStatus;
f32 dropFrq;
extern struct VFSHOCKCTL_DATA  vfshockdata;
extern f32 inputFrq1;
extern f32 DeltaImSvc4;
extern f32 ImSvc4FluxRFrq;
//extern f32 DeltaImSvc3;
extern f32 ImSvc3FluxRFrq;
extern int ImSvc3Vdout,ImSvc3Vqout;
u16 newCarrierFrquU16;
f32 newCarrierFrq;

/*
u16 IFchangeFlag,IFchangeFlagOld;
f32 DqTo2ndVdCal,DqTo2ndVqCal;
f32 DqTo2ndVdSamp,DqTo2ndVqSamp;
f32 DqTo2ndid,DqTo2ndiq;
*/
//==============================================================================
f32 iAlphaS, iBetaS;                // 定子电流(alpha and beta)
//f32 iAlphaSInv, iBetaSInv;          // 变频器侧的电流
f32 iAlphaSFilter, iBetaSFilter;    // LC滤波器的电容支路的电流
f32 iAlphaSMotor, iBetaSMotor;      // 有输出LC滤波器时，电机的定子电流(alpha and beta)
f32 yAlphaS, yBetaS;                // 输出电压伏秒(alpha & beta)
f32 fluxAlphaS, fluxBetaS;          // 定子磁链(alpha and beta)
f32 fluxAlphaSDC, fluxBetaSDC;      // 定子磁链的直流分量(alpha and beta)
f32 fluxDSBackEMF, fluxQSBackEMF;   // 电机反电动势的定子磁链(D & Q)
f32 fluxDS, fluxQS;                 // 定子磁链(D & Q)
f32 vaRef_,                         // park反变换和clarke反变换之后的电压指令，peak reduction之前
    vbRef_,
    vcRef_;
//f32 vaLossRef_,                     // 叠频制动的电压指令
//    vbLossRef_,
//    vcLossRef_;
//f32 vaRefPrime,                     // 插补值，死区补偿之后的电压指令
//    vbRefPrime, 
//    vcRefPrime; 
//==============================================================================
//void DqTo2ndCurrentControl(void);
//void DqToThetaControl(void);
//void DqTo2ndSpdFluxControl(void);
//void DqTo2ndControl(void);
//void DqTo2ndTheta(void);
extern void ModuleWaveGen(void);
extern void VFshockControl(void);
void DqTo2ndTheta(void);
void DqTo2ndStateControl(void);
void VolSatSuppControl(void);
extern void FastDecDeal(void);
extern void RunWithoutMidVoltage(void);
void UpdateFpgaVoltageData(void);
void UpdateFastLoopPara(void);
void PMSMCurParaAutoTune(void);

void UpdateFpgaTimeSequence (
    f32 *carrierFrq,    // 
    f32 *sampFreq,      // 
    u16 rank,           // 
    f32 *stepNumber)    // 
;
void AFEUpdateFpgaVoltageData(void);
void LAFEUpdateFpgaVoltageData(void);
void FluxIMAddCalc(void);
void IdrefPmsmCalc(void);
void PmsmMtpaCalc(void);
void InitOutputMotor(void);
void CellErrorEnableDeal(u32 cellFaultEnableFlag, u32 bypassFlag);
void CellBypassPhaseDeal(u16 Na, u16 Nb, u16 Nc);
f32 SpeedLoopPIParamCalc(f32 speedPIParamLowFrq, f32 speedPIParamHighFrq);
f32 deltaComp = -1.2;//-1.2  -0.5
void pmsvc_param_in();
void pmsvc_param1_in();
extern void PmsmSvcSpinload(void);
extern void calc_coef();
extern void calc_rotor_position();
extern 	void AutoTuneStage1FastDeal1Pmsm(void);
extern 	void AutoTuneStage1FastDeal2Pmsm(void);
extern 	void LoadSharingDeal1(void);
extern void PmInitPosDet(void);

void uvwOutCurrentCalc(void);

#if DEBUG_P_ERR20
//extern f32 encoderSpeedOld;
extern bool encoderLossErrorOldFlag;
#endif
//void UpdateFpgaVoltageDataOverModule(void);
extern f32 udcFil;
f32 speedGain;
f32 speeddelta;
extern f32 cellVolDelta;
struct NOTCHFILTER_STR
{
    f32 NotchWidth;
	f32 NotchDepth;
	f32 NotchFreq;
	f32 input;
	f32 last1input;
	f32 last2input;
	f32 output;
	f32 last1output;
	f32 last2output;
	f32 Ts;
};
struct NOTCHFILTER_STR FluxQNotchFilter;

void NotchFilter(struct NOTCHFILTER_STR *p);

//==============================================================================
//
//速度环参数在不同的切换频率下进行线性切换
//
//
//==============================================================================

f32 SpeedLoopPIParamCalc(f32 speedPIParamLowFrq ,f32 speedPIParamHighFrq)
{  
    f32 speedPIParam;
    
    if (speedLoopMenu.speedParaFrqLow == speedLoopMenu.speedParaFrqHigh)
    {
        if (fabs(CommandGenerator.SpeedReference) <= speedLoopMenu.speedParaFrqLow)
        {
            speedPIParam = speedPIParamLowFrq;
        }
        else if (fabs(CommandGenerator.SpeedReference) > speedLoopMenu.speedParaFrqLow)
        {
            speedPIParam = speedPIParamHighFrq;
        }
        
    }
    else if (fabs(CommandGenerator.SpeedReference) <= speedLoopMenu.speedParaFrqLow)
    {         
        speedPIParam = speedPIParamLowFrq;
    }
    else if (fabs(CommandGenerator.SpeedReference) >= speedLoopMenu.speedParaFrqHigh)
    {
        speedPIParam = speedPIParamHighFrq;
    }
    else
    {
        speedPIParam = (speedLoopMenu.speedParaFrqHigh - fabs(CommandGenerator.SpeedReference)) / 
                         (speedLoopMenu.speedParaFrqHigh - speedLoopMenu.speedParaFrqLow ) *
                         (speedPIParamLowFrq - speedPIParamHighFrq) + speedPIParamHighFrq;
    }
    return speedPIParam;
}



//==============================================================================
//
// 输出处理的初始化
//
//
//
//==============================================================================
void InitOutputProcessing(void)
{
    Uint16 Na, Nb, Nc;          // 实际的每相单元数
    Uint16 Ni;                  // 每相安装的单元数
    Uint16 Nmin;                // line to line单元数的最小值
 //   Uint16 ranks;               // 每相的最大单元数
    f32 tmp;
    static u16 NabcFlag; 
    
#if (INV_TYPE == HW_HD90)

    if (hwCellFlag)     // 大样机
    {
        if (CELL_TYPE_AFE_1140 == cellMenu.cellVoltage)    // 1140V三电平可控整流单元，母线电压_V
        {
            // 这个也老在变。
            cellDCVoltage = 1650;
    //        cellDCVoltage = 1500;
        }
        else    // 690V两电平整流单元，榴莲单元
        {
            cellDCVoltage = 1.35 * 690;
        }
    }
    else        // 非全功能小样机，全功能小样机
    {
        cellDCVoltage = 1.35 * 83; 
    }                                 

#elif (INV_TYPE == HW_HD3x)
    cellDCVoltage = udcFil * driveParameterMenu.ratingInputVoltage * (SQRT2 / SQRT3);
#endif

#if DEBUG_P_ERR20
//    tmp2 = coreSubCmd.bit.encoderLossDeal;  //  0-切换至SVC1，2-切换至SVC2，与F0-01含义一致
    OutputProcess.ControlAlgorithm = (enum Algorithims)motorControlMode;
    if (encoderLossError)
    {
        if (IM_FVC == OutputProcess.ControlAlgorithm)
        {
            if (0 == coreSubCmd.bit.encoderLossDeal)    // 切换为SVC1
            {
                OutputProcess.ControlAlgorithm = IM_SVC1;
            }
            else // if (2 == tmp2)  // 切换为SVC2
            {
                OutputProcess.ControlAlgorithm = IM_SVC2;
            }
        }
        else if (SM_FVC == OutputProcess.ControlAlgorithm)
        {
            OutputProcess.ControlAlgorithm = SM_SVC;
        }
    }
    
#elif 1
    OutputProcess.ControlAlgorithm = (enum Algorithims)motorControlMode;
#endif


// 动态调谐时，固定为SVC2。已放到ARM处理。
// 动态调谐，固定控制方式为SVC2；加速时间限制为20-200s。
#if 0
    if ((TUNE_IM_2 == coreTuneCmd) ||
        ((AUTO_TUNE_STATE == DriveControl.State) && (TUNE_NULL == coreTuneCmd))
       )
    {
        OutputProcess.ControlAlgorithm = IM_SVC2;
    }
#endif

    clControl = ((IM_FVC == OutputProcess.ControlAlgorithm) || 
                 (SM_FVC == OutputProcess.ControlAlgorithm)
                ) ? TRUE : FALSE;
#if DEBUG_P_SM_CONTROL
    smControl = ((SM_SVC == OutputProcess.ControlAlgorithm) ||
                 (SM_FVC == OutputProcess.ControlAlgorithm) ||
                 (SMDC_SVC == OutputProcess.ControlAlgorithm)
                ) ? TRUE : FALSE;
#endif

// 获取实际的每相单元数，上电自检初始化每相单元数
    Na = cellMenu.installedCellsPerPhase;
    Nb = cellMenu.installedCellsPerPhase;
    Nc = cellMenu.installedCellsPerPhase;
	if(coreCarrierFrq == 0)
	{
		coreCarrierFrqAct = 700;
	}
	newCarrierFrquU16 = (u16)(newCarrierFrq*10.0);
	if((coreCarrierFrq != newCarrierFrquU16)&&(newCarrierFrquU16 > 100))
	{
		coreCarrierFrq = newCarrierFrquU16;
	}
    coreCarrierFrqAct = (f32)coreCarrierFrq * (1.0/10);
    OutputProcess.FastLoopFrequency = coreCarrierFrqAct * 2;
    pwmT = 1.0 / OutputProcess.FastLoopFrequency;
//#endif

    OutputProcess.FastLoopSamplePeriod = pwmT;
    OutputProcess.SlowLoopSamplePeriod = SLOW_LOOP_TIME;

// 
    Ni = cellMenu.installedCellsPerPhase;

// 计算line to line单元数的最小值
    Nmin = GetMin3(Na + Nb, Nb + Nc, Nc + Na);

// 计算PVCL
// 2/3^0.5 * (Nmin / (2*Ni))
// 4/3 * cos(pi/6) = 2/(3^0.5)
    internalPeakVoltageClampLimit = (f32)Nmin / (SQRT3 * Ni);
    iInternalPeakVoltageClampLimit = 1.0 / internalPeakVoltageClampLimit;
    OutputProcess.PeakVoltageClampLimit = internalPeakVoltageClampLimit;

// 计算相电压gain
    OutputProcess.PeakReductA = (f32)Ni / Na;
    OutputProcess.PeakReductB = (f32)Ni / Nb;
    OutputProcess.PeakReductC = (f32)Ni / Nc;

// 计算peak reduction gain的最大值
    tmp = 1.0 / GetMax3(OutputProcess.PeakReductA,
                        OutputProcess.PeakReductB,
                        OutputProcess.PeakReductC);
    OutputProcess.PeakReductKi = 0.5 * tmp;
    tmp = tmp * 0.95 * InputProcess.Ed / OutputProcess.MotorVoltageClampLimit;
    if ((PURE_VF == motorControlMode) || (SIN_ONLY == motorControlMode))  // 纯粹的VF运行
    {
        tmp = 1.0;
    }
#if (INV_TYPE == HW_HD3x)   // 暂时这样
    tmp = 0.1;
#endif
    OutputProcess.PeakReductMax1 = tmp;

    biasGain = (0.475 * 9.0) * ((u32)Na*Nb*Nc) / ((u32)(Na+Nb+Nc) * (Na+Nb+Nc) * Ni);

#if CELL_BYPASS
    OutputProcess.CellImbalance =
        (OutputProcess.PeakReductA + OutputProcess.PeakReductB + OutputProcess.PeakReductC > 3.0) ?
        TRUE : FALSE;
#endif

// 极对数计算，考虑这种情况，33.3Hz，1000rpm
    tmp = (u16)(motorPara.ratingFrq * 60 / motorPara.ratingSpeed + 0.1);
    polePairs = (tmp < 1) ? 1 : tmp;

	if (cfGroup[19] != 0)
	{
	    speeddelta =  fabs(spdRegData.speedReference - spdRegData.wr) / motorPara.ratingFrq * I_TWO_PI;
        if(cellVolDelta <= 0.03)
        {
			speedGain = 1.0;
		}
		else if(speeddelta > 0.08)
		{
			speedGain = 1.5;
		}
		else if(speeddelta > 0.04)
		{
			speedGain = 1.2;
		}
		else
		{
			speedGain = 1.0;
		}
	}
	else
	{
		speedGain = 1.0;
	}
    OutputProcess.CurrentRegIntegBraking = currentLoopMenu.currentRegIntegBraking * OutputProcess.FastLoopSamplePeriod;
    OutputProcess.CurrentRegInteg = currentLoopMenu.currentRegInteg * OutputProcess.FastLoopSamplePeriod;
   // OutputProcess.SpeedFilterGain = 1.0 - OutputProcess.SlowLoopSamplePeriod / speedLoopMenu.speedFilterTimeConstant;     
    OutputProcess.SpeedRegInteg = SpeedLoopPIParamCalc(speedLoopMenu.speedRegIntegLowFrq, speedLoopMenu.speedRegInteg);
    OutputProcess.SpeedRegInteg = OutputProcess.SpeedRegInteg * OutputProcess.SlowLoopSamplePeriod * speedGain; 
	if(fluxCtrlMenu.fluxFilterTime == 0)
	{
		fluxCtrlMenu.fluxFilterTime = 0.5;
	}
    OutputProcess.FluxFilterGain = 1.0 - OutputProcess.SlowLoopSamplePeriod / fluxCtrlMenu.fluxFilterTime;
    OutputProcess.FluxRegInteg = fluxCtrlMenu.fluxIntegralGain * OutputProcess.SlowLoopSamplePeriod;

    OutputProcess.BrakingEnable = brakeEnable;

#if DEBUG_P_SPINNING_LOAD
    OutputProcess.SpinningLoadEnable = 
        ((SPINNING_LOAD_OFF == spinningLoadMenu.mode) || 
         (OLTM == OutputProcess.ControlAlgorithm)     ||
         (PURE_VF == OutputProcess.ControlAlgorithm)  ||
         (SMDC_SVC == OutputProcess.ControlAlgorithm) ||
          ((motorControlMode == PMSM_SVC) || (motorControlMode == PMSM_FVC))
        ) ? FALSE : TRUE;
#endif

    OutputProcess.RatedFrequency = motorPara.fPuOmegaOne;
    OutputProcess.iRatedFrequency = 1.0 / OutputProcess.RatedFrequency;

    OutputProcess.MotorTorqueLimit = coreUpperTorque;
#if DEBUG_P_AUTO_TUNE
#define TUNE_UPPER_TORQUE   1.1     // 放大一点，使额定负载可以跑起来。
    if (TUNE_IM_2 == coreTuneCmd)
    {
        OutputProcess.MotorTorqueLimit = GetMin(OutputProcess.MotorTorqueLimit, TUNE_UPPER_TORQUE); 
    }
#endif

    OutputProcess.MotorRegenLimit = upperTorqueRegen;


// 一些其它处理
#if DEBUG_P_SM_CONTROL
    if (!OutputProcess.Enable)
    {
        OutputProcess.SMDCMode = (SMDC_SVC == OutputProcess.ControlAlgorithm)
            ? ENABLED : DISABLED;
    }

    if (OutputProcess.Enable)
    {
        BackEMFPllParams.propGain = EMF_PLL_KP;
        BackEMFPllParams.integGain = EMF_PLL_KI;

//        OutputProcessPllParams.propGain = OUT_PLL_KP;
//        OutputProcessPllParams.integGain = OUT_PLL_KI;
    }
    else if (smControl) // 同步机飞车启动时，PLL增强
    {
        BackEMFPllParams.propGain = 2.0 * EMF_PLL_KP;
        BackEMFPllParams.integGain = 5.0 * EMF_PLL_KI; 

//        OutputProcessPllParams.propGain = 5.0 * OUT_PLL_KP;
//        OutputProcessPllParams.integGain = 2.0 * OUT_PLL_KI;
    }
#endif
#if 0
/*
    if (
        ((SYNCH_TRANSFER_DOWN == synchTransfer) &&
        (WAITING_FOR_FLUX_TO_BUILD >= SynchTransfer.DownTransferState)) 
        )
    {
        OutputProcessPllParams.propGain= 800.0;// 800.0;   //write by zhangyuan 
        OutputProcessPllParams.integGain = 4.0;//4
    }
    else
	*/
    {
        OutputProcessPllParams.propGain = OUT_PLL_KP;
        OutputProcessPllParams.integGain = OUT_PLL_KI;
    }
#endif    

// 环流标志
#if DEBUG_P_SYNC_TRANSFER
 //   circulatingCurrentFlag = ((CirCurMode) && (SYNCH_TRANSFER_DOWN == synchTransfer));
#endif


// 输出处理的初始化，主要是电机部分
    InitOutputMotor();

}








extern f32 outVoltageHwFil;
extern u16 tuneStage1NoFlag;
//extern f32 outputGroundFaultGainR;

f32 iqFdbDroopFil;                      // 下垂控制用的转矩电流反馈
//u16 sfg = 1;
f32 iNegGainR;

f32 spdLoopMagnet;
f32 spdFluxMagnet;
f32 iqLimitMagnet;

#if DEBUG_P_SYNC_TRANSFER   // 环流时防止电流环发散保护
extern Uint16 coreErrorCode;
//s32 curTickerTemp;
f32 currentLoopErrLimit = 0.20; // 防止电流环发散保护阈值
f32 CUR_ERR_TICKER_MAX = 100;   // 防止电流环发散保护持续__拍
#endif
f32 idStopDC;
extern f32 iqRegSpinningLoad;
f32 reactivePower;              // 无功功率，PU
f32 ydNegSeq1;      // 输出电压伏秒负序分量
f32 yqNegSeq1;
extern f32 npcErrMinH;
extern f32 npcErrMinL; 
//f32 sinThetaTest,cosThetaTest;
f32 sinTheta, cosTheta;     // 角度的正余弦值，减少执行时间。
f32 sinThetaPM, cosThetaPM;     // 角度的正余弦值，减少执行时间。
//u16 fdsxcnt;
//f32 gPm_Rs,gPm_Ld,gPm_Lq,gPm_Bemf;
long gPm_Speed_Lpf= 100;
//f32 vdsPm,vqsPm,thetaPm,vdsPmtheta,vqsPmtheta,idFdbPm,iqFdbPm,vdsPmSp,vqsPmSp;
f32 FrqPmsmsvc,DeltaPmsmSvc;
extern f32 uAlphaS,uBetaS;
extern u16 dcBrakeStartflag;
f32 dcBrakeStartCur;
f32 dcBrakeStopCur;
f32 E1R;
//u16 Uvoltage,Vvoltage;
//f32 PWMDuty;
extern u16 dcBrakeenable;
//f32 testPos;
extern f32 AlphaOutputVol;
extern f32 BetaOutputVol;
f32 yAlphaSRef, yBetaSRef;
u16 DCBrakeStatusTmp;
//f32 sinThetaOb,cosThetaOb;
//f32 idfdbPmsmOb,iqfdbPmsmOb;
f32 sampleVoldOb,sampleVolqOb;
f32 sdsds = 1.5;
f32 sinThetatmp, cosThetatmp;     // 角度的正余弦值，减少执行时间。
//f32 Idstest,Iqstest;
f32 DeltaSTmp;
f32 DeltaSTmpstart = 0;
f32 OutputProcessIds,OutputProcessIqs;
f32 sampleVoldObTmp,sampleVolqObTmp;
f32 OutputProcessDeltaSVF,OutputProcessFrequencyVF;
u16  IFmodelFlga = 0;  //  1表示在矢量控制中进去IF模式，0表示切换到矢量模式
u16 IFmodelFlgaOld = 0;
//extern f32 vaRefTest_,vbRefTest_,vcRefTest_;
/*
f32 iAlphaSLpf,iBetaSLpf;
f32 yAlphaSLpf,yBetaSLpf;
f32 iAlphaSSG,iBetaSSG;
f32 yAlphaSSG,yBetaSSG;
*/
extern f32 VMPhiOB,DeltaImSvc4,PhiRefOB;
//==============================================================================
//
// 输出处理，快环
// 电流环
//
// 根据采样的电流、电压(伏秒值)，
// 计算应该输出电压指令
//
//==============================================================================
f32 yalpha_ob,ybeta_ob;
f32 fluxQSFil;
f32 yAlphaSOffset,yBetaSOffset;
f32 NotchFiltercoff = 1.005;
f32 vaLastUpdate, vbLastUpdate, vcLastUpdate; 

f32 moudleCMCoeff = 0;
f32 moudleVMCoeff = 0;
f32 deltaTheta;
f32 DeltaSOB;
f32 FrequencyOB;
f32 deltaSPLLOB;
f32 pllBackEmfFrqPU;
f32 DeltaSBackEMFPU;
f32 fluxDSBackEMFFil;
extern u16 stopTimeCntMax;
extern u16 stopTimeCnt;
extern f32 pllFluxSFrqPu;
extern f32 pllBackEmfFrqPu;
volatile u16 stopTimeCntMaxFluxS;
volatile u16 stopTimeCntFluxS;
u16 yFluxSOffset = 0;

u32 DisEnableCnt123 = 0;

void OutputFastLoopSfoc(void)
{
    u16 tmp1;
    u16 tmp2;
    f32 tmp;
	f32 sinThetaOb,cosThetaOb;
	//static u32 DisEnableCnt = 0;
//    f32 sinThetatmp, cosThetatmp;     // 角度的正余弦值，减少执行时间。
#if !DEBUG_PRG_IN_RAM
    f32 idNegSeq, iqNegSeq;     // 输出电流的负序分量
    f32 ydNegSeq, yqNegSeq;     // 输出电压伏秒的负序分量
#endif
    f32 idLoopOutMax2;

#if DEBUG_P_I_REG_ONLY
    npcErrMinH = 0.0;
    npcErrMinL = -0.15;
#endif

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
    tmp = GetA2AddB2(yAlphaS, yBetaS);
    tmp1 = (tmp >= 0.005 * 0.005);
    tmp2 = (tmp >= minimumPllFlux * minimumPllFlux);

   if (tuneStage1NoFlag)   // 不 处于AutoTune的Stage1
	{
//------------------------------------------------------------------------------
// Back EMF Calculation，没有起多大作用
// 计算硬件检测的输出电压使用了

        ParkCalcMacro(yAlphaS, yBetaS, - 1.0 * pllBackEmfFrq *OutputProcess.FastLoopSamplePeriod + OutputProcess.DeltaSBackEMF, fluxDSBackEMF, fluxQSBackEMF);  // 72clk
        //ParkCalcMacro(AlphaOutputVol, BetaOutputVol, - 1.0 * pllBackEmfFrq *OutputProcess.FastLoopSamplePeriod + OutputProcess.DeltaSBackEMF, fluxDSBackEMF, fluxQSBackEMF);  // 72clk

        // 反电动势大于一定值时，才这样计算。
        if (tmp1)
        {
            // 183clk
            pllDataBackEmf.input = fluxQSBackEMF;
//            pllDataBackEmf.angle = OutputProcess.DeltaSBackEMF;
            PhaseLockLoop(&pllDataBackEmf);            // 143clk
            pllBackEmfFrq = pllDataBackEmf.frequency;
            OutputProcess.DeltaSBackEMF = pllDataBackEmf.angle;
        }
        else
        {
            pllBackEmfFrq = 0.0001;

            if (!OutputProcess.Enable)  // 停机时，且反电动势很小时，积分项要清零
            {
                BackEMFPllParams.accumulator = 0;
                BackEMFPllParams.lastInput = 0;
            }
        }
		pllBackEmfFrqPU = pllBackEmfFrq/(50.0*TWO_PI);
		DeltaSBackEMFPU = OutputProcess.DeltaSBackEMF;
		fluxDSBackEMFFil = LPF_K(fluxDSBackEMF, fluxDSBackEMFFil, 4);
 /*
        OutputProcess.BackEMF = LPF_K(
            pllBackEmfFrq * OutputProcess.iRatedFrequency * fluxDSBackEMF,
            OutputProcess.BackEMF,
            80    // k = 1/(1-0.9875) = 80
            );
		*/
		OutputProcess.BackEMF = pllBackEmfFrq * OutputProcess.iRatedFrequency * fluxDSBackEMF;
//------------------------------------------------------------------------------


// 定子磁链观测
// 部分参数的赋值在 OutputProcessSlowLoop() 的最后。
        {   // 222clk 
		   	{
		   		if(OutputProcess.FastLoopSamplePeriod != 0.0)
			    {
			    	stopTimeCntMaxFluxS  = 6.0 / OutputProcess.FastLoopSamplePeriod;
			    }
				else
				{
					stopTimeCntMaxFluxS = 12600;
				}
				/*
				if((!coreRunStatus.bit.run)&&(E1R<0.003))
				{
					stopTimeCntFluxS++;
					if(stopTimeCntFluxS >= stopTimeCntMaxFluxS)
					{
						stopTimeCntFluxS = stopTimeCntMaxFluxS;
					}
				}
				
				if(coreMainCmd.bit.run)
				{
					stopTimeCntFluxS = 0;
				}*/
				stopTimeCntFluxS++;
				if(stopTimeCntFluxS >= stopTimeCntMaxFluxS)
				{
					stopTimeCntFluxS = stopTimeCntMaxFluxS + 1;
					yFluxSOffset = 1;
					
				}

				if((!coreRunStatus.bit.run)&&(E1R<0.003)&&(yFluxSOffset == 0))
			    {
			    	DisEnableCnt123++;
			        yAlphaSOffset += _IQ18mpy((_IQ18(0.02)), yAlphaS - yAlphaSOffset);
			        yBetaSOffset += _IQ18mpy((_IQ18(0.02)), yBetaS - yBetaSOffset);
			    }
			
				//fluxSData.yalpha = (yAlphaS - yAlphaSOffset)*cfGroup[10]*0.001;
	            //fluxSData.ybeta = (yBetaS - yBetaSOffset)*cfGroup[11]*0.001;
	            
				
				if(funcCode.code.ObVolSel == 1)
				{
					fluxSData.yalpha = yAlphaS;
	            	fluxSData.ybeta = yBetaS;
				}
				else
				{
					fluxSData.yalpha = (yAlphaS - yAlphaSOffset);
	            	fluxSData.ybeta = (yBetaS- yBetaSOffset)*1.011;
				}
				yalpha_ob = fluxSData.yalpha;
				ybeta_ob = fluxSData.ybeta;
	            fluxSData.ialpha = iAlphaS;
	            fluxSData.ibeta = iBetaS;
		   }
            fluxSData.spinStatusIsPllNotValid = (PLL_FREQUENCY_NOT_VALID == SpinningLoad.Status)
//                && (SYNCH_TRANSFER_DOWN != synchTransfer)
													;
            fluxSData.speedReference = CommandGenerator.SpeedReference;
//            fluxSData.speedReference = OutputProcess.WsFil;     // 应该使用这个?
            FluxStatorObserve(&fluxSData);//磁链观测器
            fluxAlphaS = fluxSData.falpha;
            fluxBetaS = fluxSData.fbeta;
            
        }
       pllFluxSFrqPu = pllFluxSFrq * motorPara.iFPuOmegaOne;
       pllBackEmfFrqPu = pllBackEmfFrq * motorPara.iFPuOmegaOne;
// 输出滤波器的处理
        FluxStatorObserveLC();

        ParkCalcMacro(fluxAlphaS, fluxBetaS, 
            deltaSPLL - pllFluxSFrq *OutputProcess.FastLoopSamplePeriod , fluxDS, fluxQS);   // 76clk

        // filter
        {
            OutputProcess.FluxDS = LPF_K(fluxDS, OutputProcess.FluxDS, 4);  // 1/(1-0.75) = 4
            OutputProcess.FluxQS = LPF_K(fluxQS, OutputProcess.FluxQS, 4);
        }
		//fluxQSFil = LPF_K(fluxQS, fluxQSFil, 2);
		
//------------------------------------------------------------------------------
#if 1//!DEBUG_P_SYNC_TRANSFER  // 环流时不能进行这些检测?
        tmp = 0;

        // 判断PLL数据是否有效，飞车启动使用
        if ( (tmp2) &&     // (OutputProcess.FluxDS > minimumPllFlux)
             ( (FALSE == OutputProcess.ZeroSpeed) ||
               (TRUE == clControl) ||
               (IM_SVC1 == motorControlMode)  ||
               (IM_SVC2 == motorControlMode)  ||
               (IM_SVC4 == motorControlMode)  ||
               (PURE_VF == motorControlMode)
             )
           )
        {
            SpinningLoad.Status = PLL_FREQUENCY_VALID;
        }
        else
        {
            SpinningLoad.Status = PLL_FREQUENCY_NOT_VALID;
            // 1->0，有效变为无效
            if ((PLL_FREQUENCY_VALID == SpinningLoad.Status) && (IDLE_STATE == DriveControl.State)
           // if ((PLL_FREQUENCY_VALID == previousPllStatus) && (IDLE_STATE == DriveControl.State)
//                && (sfg)
                )
            {
                OutputProcessPllParams.accumulator = 0.0;
                OutputProcessPllParams.lastInput = 0.0;
            }    
		}
#endif
//------------------------------------------------------------------------------


// 同步频率计算
// 231clk
    
        // 大于一定值时，才这样计算。
        if ((tmp1))
        {
			FluxQNotchFilter.input = fluxQS;
			FluxQNotchFilter.NotchDepth = 0.05;
			FluxQNotchFilter.NotchWidth = 5.0 * TWO_PI;
			if(abs(pllFluxSFrq) < (30.0 * TWO_PI))
			{
				FluxQNotchFilter.NotchFreq = 100.0 * TWO_PI;
			}
			else
			{
				FluxQNotchFilter.NotchFreq = pllFluxSFrq*2.0*NotchFiltercoff;
			}
			NotchFilter(&FluxQNotchFilter);
			fluxQSFil = FluxQNotchFilter.output;
		
            pllDataS.input = fluxQS;
			 //pllDataS.input = fluxQSFil;
//            pllDataS.angle = deltaSPLL;
            PhaseLockLoop(&pllDataS);
            pllFluxSFrq = pllDataS.frequency;
            deltaSPLL = pllDataS.angle;
        }
        else
        {
            pllFluxSFrq = 0;

			FluxQNotchFilter.last1input = 0;
			FluxQNotchFilter.last2input = 0;
			FluxQNotchFilter.last1output = 0;
			FluxQNotchFilter.last2output = 0;
        }
		
      sincos(OutputProcess.DeltaS , &sinTheta, &cosTheta);         // 56clk
      ParkCalcMacroSc(iAlphaS, iBetaS, sinTheta, cosTheta, OutputProcess.Ids, OutputProcess.Iqs);
	  ParkCalcMacroSc(AlphaOutputVol,BetaOutputVol,sinTheta,cosTheta,sampleVoldOb,sampleVolqOb);
      sincos(OutputProcess.DeltaS +  sdsds * OutputProcess.Frequency * OutputProcess.FastLoopSamplePeriod , &sinThetaPM, &cosThetaPM); 
	  DqTo2ndTheta();  


	 
		
	 if((motorControlMode == PMSM_SVC)||(motorControlMode == PMSM_FVC))
      {
       //中断中更新变量
	    sincos(DeltaPmsmSvc , &sinThetaOb, &cosThetaOb); 
    	ParkCalcMacroSc(iAlphaS, iBetaS, sinThetaOb, cosThetaOb, OutputProcessIds, OutputProcessIqs);
		ParkCalcMacroSc(AlphaOutputVol,BetaOutputVol,sinThetaOb,cosThetaOb,sampleVoldObTmp,sampleVolqObTmp);

		pmsvc_param1_in();
	    pmsvc_param_in();
	    //计算磁场辨识函数需要的参数
		calc_coef();
		//辨识磁场角度、电机转速
		calc_rotor_position();
	    //磁场角度传给电流变换角度
	    PmsmSvcSpinload();
    	FrqPmsmsvc = (f32)PmSvcData.est_omg * 0.00390625;  // 1/256
    	DeltaPmsmSvc = (f32)PmSvcData.est_angel * 6.283185307179586476925286766559/(f32)4294967296;    //zss 2*pi/2^32
    	Modulo2PI(&DeltaPmsmSvc);
 	  }	 
 	 if(fabs(CommandGenerator.SpeedReference / TWO_PI)< 20.0)
 	 {
		moudleCMCoeff = 1.0;
		moudleVMCoeff = 0.0;
	 }
	 else if(fabs(CommandGenerator.SpeedReference / TWO_PI)> 25.0)
	 {
		moudleCMCoeff = 0.0;
		moudleVMCoeff = 1.0;
	 }
	 else
	 {
		moudleCMCoeff =  1.0 - (fabs(CommandGenerator.SpeedReference / TWO_PI) - 20.0)/5.0;
		moudleVMCoeff = 1.0 - moudleCMCoeff;	             
	 }
     IFmodelFlgaOld = IFmodelFlga;
	 if((funcCode.code.IfOrVectorSwitchFreq != 0)&&(AUTO_TUNE_STATE != DriveControl.State))
	 {
		 if (fabs(CommandGenerator.SpeedReference * I_TWO_PI) < (0.01 *funcCode.code.IfOrVectorSwitchFreq)) //增加电流闭环功能  
		 {
			 IFmodelFlga = 1;
		 }
		 else
		 {
			IFmodelFlga = 0;
		 }   
	 }
	 else
	 {
		IFmodelFlga = 0;
	 }

#if 1
         if ((PURE_VF != motorControlMode) 
		 	//&&
    //        ((true == OutputProcess.usePllAndDroop) || 
   //          (true == torqueMode)
   //         )
           )
        {	
           OutputProcessFrequencyVF = CommandGenerator.SpeedReference;
           OutputProcessDeltaSVF += OutputProcessFrequencyVF * OutputProcess.FastLoopSamplePeriod;
		   Modulo2PI(&OutputProcessDeltaSVF);
		   if (IFmodelFlga == 1)
		   {
          		OutputProcess.Frequency = OutputProcessFrequencyVF;
                OutputProcess.DeltaS = OutputProcessDeltaSVF;
		   }
           else
           {   
        	    if((motorControlMode != PMSM_SVC)&&(motorControlMode != PMSM_FVC))
        	    {
        	    	if((motorControlMode == IM_SVC4)&&
        	                (AUTO_TUNE_STATE != DriveControl.State))
        	    	{
						OutputProcess.Frequency = ImSvc4FluxRFrq;
						OutputProcess.DeltaS = DeltaImSvc4;
        	    	}
					else
					{
                        if((cfGroup[12] != 0)&&(AUTO_TUNE_STATE != DriveControl.State))
                        {
                         //   deltaTheta = (deltaSPLL  + deltaComp * OutputProcess.Frequency *OutputProcess.FastLoopSamplePeriod) - DeltaImSvc4;
                              deltaTheta = (OutputProcess.DeltaSBackEMF) - DeltaImSvc4;
							//Modulo2PI(&deltaTheta);
							if(CommandGenerator.SpeedReference > 0.0)
							{
								Modulo2PI(&deltaTheta);
							}
							else
							{
								if(deltaTheta > 0.0)
								{
									deltaTheta = deltaTheta - TWO_PI;
								}
							}
							OutputProcess.DeltaS = DeltaImSvc4 +  moudleVMCoeff*(deltaTheta);
							DeltaSOB = OutputProcess.DeltaS;
							Modulo2PI(&DeltaSOB);
                            OutputProcess.Frequency = moudleCMCoeff * ImSvc4FluxRFrq +
								                    pllBackEmfFrq * moudleVMCoeff;
						}
					    else
					    {
							OutputProcess.Frequency = pllFluxSFrq;
				       		OutputProcess.DeltaS = deltaSPLL  + deltaComp * OutputProcess.Frequency *OutputProcess.FastLoopSamplePeriod  ;
					    }
					}
	           	}
			    else if(motorControlMode == PMSM_SVC)
			    {   				   
					OutputProcess.DeltaS = DeltaPmsmSvc;
					OutputProcess.Frequency = FrqPmsmsvc;
			    }
				OutputProcessDeltaSVF = OutputProcess.DeltaS;//矢量切回IF时的角度
           	}
				//else
				if(coreMainCmd.bit.DCBrakeStatus == 0)
	           //                 &&(DCBrakeStatusTmp == 0))
				{
					DeltaSTmp = OutputProcess.DeltaS;
					idStopDC = idRef;
					//同步机如果停机后再启动，使用飞车启动的角度，或者磁极位置
					//异步机可以使用最后一拍的角度或者0度
				}  
				if(dcBrakeStartflag == 1)
				{ 
					OutputProcess.DeltaS = DeltaSTmpstart;
				}  //此种方案适合异步机启动直流制动，同步机需要知道磁极位置
				if(coreMainCmd.bit.DCBrakeStatus == 1)
				{   
					OutputProcess.DeltaS = DeltaSTmp;
				}//此方案适合停机时候的直流制动
				DCBrakeStatusTmp = coreMainCmd.bit.DCBrakeStatus;
			Modulo2PI(&OutputProcess.DeltaS);
			
        }
        else
#endif
        {   // 使用给定频率作为同步频率。积分得到相位。
            VFshockControl(); //VF震荡抑制
            OutputProcess.Frequency = CommandGenerator.SpeedReference + vfshockdata.shockCtldeltaFrq;           
            OutputProcess.DeltaS += OutputProcess.Frequency * OutputProcess.FastLoopSamplePeriod;
            Modulo2PI(&OutputProcess.DeltaS);		//2pi内的弧度	
        } 
		DqTo2ndStateControl();  //IF切换到矢量时电流环的处理
// 同步切换的一些处理
//        TransferFastDeal();
// 求OutputProcess.Frequency在一个速度环周期的平均值
        {
            outputProcessFrqSum += OutputProcess.Frequency;
            outputProcessFrqTicker++;
        }
    }
    else
    {
        // 正在进行 auto tune stage 1
        if((motorControlMode == PMSM_SVC)||(motorControlMode == PMSM_FVC))
        {
			AutoTuneStage1FastDeal1Pmsm();
        }
		else
		{
        	AutoTuneStage1FastDeal1();
		}
    }
//#if !DEBUG_PRG_IN_RAM
// 计算定子电流的负序分量。判断相不平衡使用
    ParkCalcMacroSc(iAlphaS, iBetaS, -sinTheta, cosTheta, idNegSeq, iqNegSeq);  // -OutputProcess.DeltaS
    ParkCalcMacroSc(yAlphaS, yBetaS, -sinTheta, cosTheta, ydNegSeq, yqNegSeq);
//#endif
    
	OutputProcess.FrequencyFiltered = LPF_K(OutputProcess.Frequency, OutputProcess.FrequencyFiltered, 10);

	//正常应该是更新角度后再进行电流变换，不改动之前的程序，仅对SVC34做处理
        if(((motorControlMode == IM_SVC4) || (motorControlMode == IM_SVC3))&&
                (AUTO_TUNE_STATE != DriveControl.State))
        {
            sincos(OutputProcess.DeltaS , &sinTheta, &cosTheta);         // 56clk
            ParkCalcMacroSc(iAlphaS, iBetaS, sinTheta, cosTheta, OutputProcess.Ids, OutputProcess.Iqs);
        }
	
    {
        idFdb = OutputProcess.Ids;
        iqFdb = OutputProcess.Iqs;
    }

    if (tuneStage1NoFlag)       // 不 处于AutoTune的Stage1
    {
    
//==============================================================================
// 电流环调
      //  f32 idLoopOutMax2;

#if DEBUG_P_DUAL_FRQ_BRAKE
        if (TRUE == OutputProcess.Braking)
        {
            idFdb = OutputProcess.IdsFil;
            iqFdb = OutputProcess.IqsFil;
        }
#endif

        idLoopOutMax2 = idLoopOutMax1;

//------------------------------------------------------------------------------

#if DEBUG_P_SPINNING_LOAD
        {
            static u16 presetcount;
            
            // 飞车启动后，PID的积分
            if (TRUE == SpinningLoad.PresetMagnetizingCurrentRegulator)
            {
                extern struct PiDataType idRegulatorParams;
                
                if (presetcount == 0)
                {
                    idRegulatorParams.accumulator = OutputProcess.VdsRef;
                }
                else if (presetcount >= 3)
                {
                    SpinningLoad.PresetMagnetizingCurrentRegulator = FALSE;
                    presetcount = 0;
                }
                presetcount++;
                
                idLoopOutMax2 = 0.25 * idLoopOutMax1;
            }
            // 飞车启动后，PID的积分需要赋初值
            if (TRUE == SpinningLoad.PresetTorqueCurrentRegulator)
            {
                extern struct PiDataType iqRegulatorParams;
//                extern f32 vqsffScaler;
                
                SpinningLoad.PresetTorqueCurrentRegulator = FALSE;
               
                iqRegulatorParams.accumulator = iqRegSpinningLoad;
            }
        }
#endif

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	if(( (IFmodelFlga == 1) ||
//            (AUTO_TUNE_STATE == DriveControl.State)))
	{
        // 励磁电流环调节器
        {   // 148clk
        //if ((cfGroup[11] == 1000)
        if((IFmodelFlga == 1)
			//||(motorControlMode == PMSM_SVC)
			)
        {
    	    idRegData.reference = motorPara.IfModeRefCur;
			iqRegData.reference = 0;
			idRef  = motorPara.IfModeRefCur;
        }
            idRegData.feedback = idFdb;
            idRegData.maxLimit = idLoopOutMax2;
#if DEBUG_P_SYNC_TRANSFER
            if ((DOWN_TRANSFER_STATE == DriveControl.State) && (OutputProcess.Enable)) 
            {   // 临时这样处理
                extern f32 inputVolFil;
                CommandGenerator.FluxReference = fluxCtrlMenu.fluxDemand * inputVolFil;
            }
#endif
            idRegData.fluxReference = CommandGenerator.FluxReference;//使能后是1
            MagnetizingCurrentReg(&idRegData);
            vds = idRegData.out;
        }
        // 励磁电流环输出
        OutputProcess.VdsRef = vds; 
        
        // 转矩电流环调节器
        {   // 218clk
            iqRegData.feedback = iqFdb;
            iqRegData.speedReference = CommandGenerator.SpeedReference;
            iqRegData.globalEnable = OutputProcess.Enable;
            TorqueCurrentReg(&iqRegData);
            vqs = iqRegData.out;
        }
        // 转矩电流环输出
        OutputProcess.VqsRef = vqs;
	}
//	else
	{
	//	SVCNEWCalOutVolt();//ImSVC3 电流环 不支持IF切SVC3的电流环
	//	CalcABVolt();

	//	vds = (f32)ImSvc3Vdout * (1/4096.0);
	//	vqs = (f32)ImSvc3Vqout * (1/4096.0);
	//	OutputProcess.VdsRef = vds;
	//	OutputProcess.VqsRef = vqs;
	}

	//if(motorControlMode == IM_SVC4)
	{
		ImSVC4CalcUI();
		if (OutputProcess.Enable)
		{
			ImSVCCalcFlux();
		}
		else
		{
			ReSetImSVC4Data();
		}
	}
	
//------------------------------------------------------------------------------

//==============================================================================
        if (PURE_VF == motorControlMode)
        {
            OutputProcess.VdsRef = volAmpl;
            OutputProcess.VqsRef = 0.0;
        }
   ///=================================================================================
   ///=================================================================================
        // 程序的输出电压计算
        outVoltagePrg = SqrtA2AddB2(OutputProcess.VdsRef, OutputProcess.VqsRef);

        tmp = outVoltagePrg * iInternalPeakVoltageClampLimit;
      //  modulationIndex = LPF_K(tmp, modulationIndex, 6);  // 1-1/6.0 = 0.8333

// 将两相旋转坐标系下的ud,uq转换为三相静止坐标系下的va,vb,vc
  
   if(motorControlMode == PMSM_SVC)
    {
		sinThetatmp = sinThetaPM;
		cosThetatmp = cosThetaPM;
	}
	else
	{
		sinThetatmp = sinTheta;
		cosThetatmp = cosTheta;
	}
	/*
	  if(cfGroup[16] == 2)
	  {
		// Conversion2rTo3sMacroSc(OutputProcess.VdsRef, OutputProcess.VqsRef,     // 19clk
        //   sinThetatmp, cosThetatmp, 
        //    vaRefTest_, vbRefTest_, vcRefTest_);
		 ModuleWaveGen();


	  }
	  else
	  */
	  {
	   // if(cfGroup[16] == 1)
	   // {
	    	//ModuleWaveGen();
	    //}	  

        Conversion2rTo3sMacroSc(OutputProcess.VdsRef, OutputProcess.VqsRef,     // 19clk
          //  sinThetaPM, cosThetaPM, 
          // sinTheta, cosTheta, 
           sinThetatmp, cosThetatmp, 
            vaRef_, vbRef_, vcRef_);
#if DEBUG_P_DUAL_FRQ_BRAKE
// 将两相旋转坐标系下的 vdLoss 转换为三相静止坐标系下的va,vb,vc。
// 没有使能叠频制动时，vaLossRef_、vbLossRef_、vcLossRef_均为0。
        Conversion2rTo3sMacroSc(dualFrqBrake.vdLoss, 0,                         // 20clk
            dualFrqBrake.sinThetaLoss, dualFrqBrake.cosThetaLoss, 
            vaLossRef_, vbLossRef_, vcLossRef_);
#endif
	  }

    }
    else
    {
        if((motorControlMode == PMSM_SVC)||(motorControlMode == PMSM_FVC))
        {
			AutoTuneStage1FastDeal2Pmsm();
		}
		else
		{
        // 正在进行 auto tune stage 1
        	AutoTuneStage1FastDeal2();
		}

      //  vaLossRef_ = 0.0;
      //  vbLossRef_ = 0.0;
      //  vcLossRef_ = 0.0;
    }
    ClarkeCalcMacro(vaRef_*udcFil, vbRef_*udcFil, yAlphaSRef, yBetaSRef);
/*
   if(cfGroup[16] == 2)
   {
  	  UpdateFpgaVoltageDataOverModule();
  }
   else
   */
  {
      // 更新传递给FPGA的电压指令
      UpdateFpgaVoltageData();                                                    // 990
   }
	//增加三次谐波后的三相之和不为0，需要这样计算
	//ClarkeCalcMacro(vaLastUpdateOB*udcFil, vbLastUpdateOB*udcFil, yAlphaSRef, yBetaSRef);
	//yAlphaSRef = (2.0*vaLastUpdateOB - vbLastUpdateOB - vcLastUpdateOB)*udcFil * (1.0 / 3.0);
   //yBetaSRef = (vbLastUpdateOB - vcLastUpdateOB)*udcFil* (0.577350269189626);

    tmp = OutputProcess.Frequency * OutputProcess.iRatedFrequency * OutputProcess.FluxDS;
    OutputProcess.ShaftPower = LPF_K(tmp * OutputProcess.Iqs, OutputProcess.ShaftPower, 10); // 1/(1-0.9)=10
   reactivePower            = LPF_K(tmp * OutputProcess.Ids, reactivePower,10); // 1/(1-0.9)=10
   OutputProcess.WsFil = LPF_K( OutputProcess.Frequency, OutputProcess.WsFil,4); // 1/(1-0.9)=10
   OutputProcess.FastLoopFrequencyPU = OutputProcess.FastLoopSamplePeriod/(1.0/(TWO_PI * motorPara.ratingFrq ));
}



void ModInterpUpdateA(void);
/*
void UpdateFpgaVoltageDataOverModule(void)
{
  //  f32 vaRef, vbRef, vcRef;   
	f32 vcom;
  
    vaLastUpdate = vaRef_;
    vbLastUpdate = vbRef_;
    vcLastUpdate = vcRef_;
    {
        npcData.ia = outCurData.u;
        npcData.ib = outCurData.v;
        npcData.ic = outCurData.w;
        npcData.ua = vaLastUpdate;
        npcData.ub = vbLastUpdate;
        npcData.uc = vcLastUpdate;         
        npcData.upn = invbusVoltage.diff;   // 中点偏差，PU
        NpcDeal1(&npcData);                  // 中点箝位处理
        vaLastUpdate += npcData.v0;
        vbLastUpdate += npcData.v0;
        vcLastUpdate += npcData.v0;
    }
	 vcom = (GetMax3(vaLastUpdate, vbLastUpdate, vcLastUpdate)
	 	              + GetMin3(vaLastUpdate, vbLastUpdate, vcLastUpdate)) * 0.5;
     vaLastUpdate =  vaLastUpdate - vcom ;
     vbLastUpdate =  vbLastUpdate - vcom ;
	 vcLastUpdate =  vcLastUpdate - vcom ;
	 
// 更新至outputVol
    ModInterpUpdateA(OutputProcess.Frequency);
}
*/
//==============================================================================
//
// 更新传递给FPGA的电压指令
// 
// 根据 三相电压指令vaRef_，vbRef_，vcRef_和叠频制动叠加的三相电压指令vaLossRef_，
// vbLossRef_，vcLossRef_，进行peak reduction()和死区补偿处理，得到
// 传递给FPGA的电压指令outputVol
//
//==============================================================================
extern f32 udcFil2;
void UpdateFpgaVoltageData(void)
{
    static bool lastEnable;                 // last state of enable
    static u16 E1R_deadTimeCompEn = 0;
    
    f32 deltaMidPt;                         // 插补的中间点相位
    f32 uaRef, ubRef, ucRef;                // peak reduction之后的电压指令
    f32 vaRef, vbRef, vcRef;                // 死区补偿之后的电压指令
    f32 vaRefStep, vbRefStep, vcRefStep;

    f32 vaRefPrime1, vbRefPrime1, vcRefPrime1;
    f32 uaRefPrime, ubRefPrime, ucRefPrime; // 插补值，peak reduction之后的电压指令
    f32 vaRefStepPrime, vbRefStepPrime, vcRefStepPrime;
    
//    f32 vaLastUpdate, vbLastUpdate, vcLastUpdate;

	struct DEADBAND_COMP_STR deadbandCompData;

// peak reduction
// 当输出电压超过限制时，叠加三次谐波或者过调制，提高电压输出。
#if PEAK_REDUCTION
    {   // 182clk
        peakReductionData.aref = vaRef_ ;/// udcFil2;//+ vaLossRef_;   // 将制动损耗叠加到三相电压指令上
        peakReductionData.bref = vbRef_ ;/// udcFil2 ;//+ vbLossRef_;
        peakReductionData.cref = vcRef_ ;/// udcFil2 ;//+ vcLossRef_;
        peakReductionData.speedRef = outVoltagePrg;      // OutputProcess.PerUnitSpeedReference
        PeakReductionCalc(&peakReductionData);          // 160clk
        uaRef = peakReductionData.ea;
        ubRef = peakReductionData.eb;
        ucRef = peakReductionData.ec;
    }
#elif 1
    uaRef = vaRef_ + vaLossRef_;
    ubRef = vbRef_ + vbLossRef_;
    ucRef = vcRef_ + vcLossRef_;
#endif

	/*死区补偿*/	
	if(fabs(E1R) >= 0.25)
	{
		E1R_deadTimeCompEn = 0;
	}
	else if(fabs(E1R) <= 0.15)
	{
		E1R_deadTimeCompEn = 1;
	}
		
	if((E1R_deadTimeCompEn == 0) || (deadTimeComp == 0.0))
	{
		OutputProcess.DeadTimeCompEnable = FALSE;
	}
	OutputProcess.DeadTimeComp = (coreCarrierFrqAct*2.0*((deadTimeComp*0.000001 + Ton - Toff) / 2.0));

	deadbandCompData.ua = uaRef;
	deadbandCompData.ub = ubRef;
	deadbandCompData.uc = ucRef;
	deadbandCompData.ia = outCurData.u;
	deadbandCompData.ib = outCurData.v;
	deadbandCompData.ic = outCurData.w;
	deadbandCompData.dtComp = OutputProcess.DeadTimeComp;
	deadbandCompData.enable = OutputProcess.DeadTimeCompEnable;
	DeadTimeCompCalcNew(&deadbandCompData);
	vaRef = deadbandCompData.ua;
	vbRef = deadbandCompData.ub;
	vcRef = deadbandCompData.uc; 
	/*死区补偿*/
	
    vaLastUpdate = vaRef;
    vbLastUpdate = vbRef;
    vcLastUpdate = vcRef;

	//vaLastUpdateOB = vaLastUpdate;
	//vbLastUpdateOB = vbLastUpdate;
	//vcLastUpdateOB = vcLastUpdate;
	
    {
        npcData.ia = outCurData.u;
        npcData.ib = outCurData.v;
        npcData.ic = outCurData.w;
        npcData.ua = vaLastUpdate;
        npcData.ub = vbLastUpdate;
        npcData.uc = vcLastUpdate;         
        npcData.upn = invbusVoltage.diff;   // 中点偏差，PU
        NpcDeal1(&npcData);                  // 中点箝位处理
        npcData.v0 = 0;//双绕组共用PWM驱动，不用零序注入调节中点电位
        vaLastUpdate += npcData.v0;
        vbLastUpdate += npcData.v0;
        vcLastUpdate += npcData.v0;
        vaRef += npcData.v0;
        vbRef += npcData.v0;
        vcRef += npcData.v0;
    }
 //  vaRef -=  (GetMax3(vaRef, vbRef, vcRef) + GetMin3(vaRef, vbRef, vcRef)) * 0.5;
//	 vbRef -=  (GetMax3(vaRef, vbRef, vcRef) + GetMin3(vaRef, vbRef, vcRef)) * 0.5;
//	 vcRef -=  (GetMax3(vaRef, vbRef, vcRef) + GetMin3(vaRef, vbRef, vcRef)) * 0.5;
    //vbLastUpdate  = 0;
   // vcLastUpdate  = 0;
// 更新至outputVol
#if (2 != FPGA_PWM_VER)
    ModInterpUpdateMacro(           // 124clk
        vaLastUpdate, vbLastUpdate, vcLastUpdate,
        vaRefStep, vbRefStep, vcRefStep,
        vaRef, vbRef, vcRef,
        vaRefStepPrime, vbRefStepPrime, vcRefStepPrime);
#elif 1
    ModInterpUpdateA();
#endif

}
extern f32 afeVa,afeVb,afeVc;
extern f32 VolMag;
extern struct PHASE_LOCK_LOOP_STR inVolPll;
void AFEUpdateFpgaVoltageData(void)
{
    static bool lastEnable;                 // last state of enable
    
    f32 deltaMidPt;                         // 插补的中间点相位
    f32 uaRef, ubRef, ucRef;                // peak reduction之后的电压指令
    f32 vaRef, vbRef, vcRef;                // 死区补偿之后的电压指令
    f32 vaRefStep, vbRefStep, vcRefStep;

    f32 vaRefPrime1, vbRefPrime1, vcRefPrime1;
    f32 uaRefPrime, ubRefPrime, ucRefPrime; // 插补值，peak reduction之后的电压指令
    f32 vaRefStepPrime, vbRefStepPrime, vcRefStepPrime;
    
//    f32 vaLastUpdate, vbLastUpdate, vcLastUpdate;

  //  struct DEADBAND_COMP_STR deadbandCompData;

// peak reduction
// 当输出电压超过限制时，叠加三次谐波或者过调制，提高电压输出。

    {   // 182clk
        peakReductionData.aref = afeVa;   // 将制动损耗叠加到三相电压指令上
        peakReductionData.bref = afeVb;
        peakReductionData.cref = afeVc;
        peakReductionData.speedRef = VolMag;     // OutputProcess.PerUnitSpeedReference
		peakReductionData.enable = 1;
		PeakReductionCalc(&peakReductionData);          // 160clk
        uaRef = peakReductionData.ea;
        ubRef = peakReductionData.eb;
        ucRef = peakReductionData.ec;
    }

    vaLastUpdate = uaRef;
    vbLastUpdate = ubRef;
    vcLastUpdate = ucRef;

    {
        npcData.ia = outCurData.u;
        npcData.ib = outCurData.v;
        npcData.ic = outCurData.w;
        npcData.ua = vaLastUpdate;
        npcData.ub = vbLastUpdate;
        npcData.uc = vcLastUpdate;         
        npcData.upn = invbusVoltage.diff;   // 中点偏差，PU
//        npcData.upn = -invbusVoltage.diff;   // 中点偏差，PU
        NpcDeal1(&npcData);                  // 中点箝位处理
      //  if(motorControlMode == PURE_VF)
      //  {
      //  	vaLastUpdate = 1.0;
      //      vbLastUpdate = 1.0;
		//	vcLastUpdate = 1.0;
      //  }
		//else
		{
        	vaLastUpdate += npcData.v0;
        	vbLastUpdate += npcData.v0;
        	vcLastUpdate += npcData.v0;
		}
        
    }
	if(motorControlMode == PURE_VF)
	{ 
		OutputProcess.Frequency = 50.0 * TWO_PI;
	}
	else
	{
		OutputProcess.Frequency =	fabs(inVolPll.frequency) *50.0 * TWO_PI;
	}
    ModInterpUpdateA();

}

extern int16 LafeVa,LafeVb,LafeVc;
extern f32 fpgazaibo;

void LAFEUpdateFpgaVoltageData(void)
{		
	Calzaibo();
	
	vaLastUpdate = LafeVa;
	vbLastUpdate = LafeVb;
	vcLastUpdate = LafeVc;
	
	outputVol.va 		= (u16)((s32)(vaLastUpdate * (fpgazaibo + 1.0) /2 )&0x0000FFFF);
	outputVol.vb 		= (u16)((s32)(vbLastUpdate * (fpgazaibo + 1.0) /2 )&0x0000FFFF);
	outputVol.vc 		= (u16)((s32)(vcLastUpdate * (fpgazaibo + 1.0) /2 )&0x0000FFFF);
	outputVol.vaPrime 	= (u16)((s32)(vaLastUpdate * (fpgazaibo + 1.0) /2 )>> 16);
	outputVol.vbPrime 	= (u16)((s32)(vbLastUpdate * (fpgazaibo + 1.0) /2 )>> 16);
	outputVol.vcPrime 	= (u16)((s32)(vcLastUpdate * (fpgazaibo + 1.0) /2 )>> 16);

}


//f32 idRefGive = 0.5;
f32 idRefFil;       // 显示使用
f32 iqRefFil;
f32 idFdbFil;
f32 iqFdbFil;
f32 pllFluxSFrqFil;
f32 fluxFdbFil;

f32 inputE0Fil;         // 输入电压零序分量
f32 outputE0AvgFil;     // 输出电压零序分量
f32 inputINegFil;       // 输入电流负序分量
f32 outputINegFil;      // 输出电流负序分量
f32 outputE0Fil;        // 输出电压的伏秒，零序分量

f32 energySaveIq;
f32 energySaveCalcOutput;
u16 energySaveEnable;       // 节能使能开关
extern f32 pllOutMax;


//void FluxControlSm(void);
//void HighStartingTorqueStateMachine(void);
//void LoadSharingDeal(void);

extern u16 reduceRatingCell;
extern f32 iqMaxReduceRating;
//extern u16 netContactorAcknowledge;                    // 工频接触器吸合标记位，以后可由DI使能
extern f32 iNoloadDownTransfer;
f32 magnetizingMaxVaule = 0.03; // 对每相一个单元， 大了容易过压
extern bool rollbackenableflag;
//extern enum ENCODERLOSS_DETECT_MODE encoderLossdetectMode;
f32 OutputMotorSpeedFiltered;
f32 idRefTmp;
//f32 inputVolGain = 1.060;
extern f32 iTotalInvDis;
f32 LMT_VSC = 1.0;  // VSC start level
//f32 G_VSC_P = 0.3;  // 0.5
//f32 G_VSC_I = 1;    //
#define  LMT_VSC_UL  0.0
#define   LMT_VSC_LL  -1.0
struct PI_REGULATOR_STR volSatCtr;
f32 idrefWeakField;
struct PMSMMTPA PmsmMtpa;
extern f32 udcFil2;
//================================================================================
struct PI_REGULATOR_STR
{
    f32 out;                        // regulated  output
    f32 Lastout;                    // regulated  output
    f32 fdb;                        // Feedback
    f32 ref;                        // Reference
    f32 delta;                      // Delta
    f32 maxLimit;                   // maximum limit
    f32 minLimit;                   // minimum limit
    f32 propGain;                   // proportional gain
    f32 integGain;                  // integral gain
    f32 accumulator;                // integr
    f32 lastInput;                  // lastInput
    s16 enable; 

};
//================================================================================
struct PMSMMTPA
{
	f32 Is;
	f32 Ld;
	f32 Lq;
	f32 bemf;
	f32 cosbeta;
	f32 sinbeta;
	f32 id;
	f32 iq;
};

//================================================================================
void PiRegulator(struct PI_REGULATOR_STR *p)
{    
    f32 output;
    f32 kpOut;

    kpOut = p->propGain * p->delta;
    
    if ((p->integGain != 0.0) && (p->enable) && (p->Lastout > p->minLimit) && (p->Lastout < p->maxLimit))
    {   
        p->accumulator = p->accumulator + 0.5 * p->integGain * (p->delta + p->lastInput);
    }

	if(!p->enable)
    {   
		p->accumulator = 0.0;
		p->Lastout = 0.0;
		p->delta = 0.0;
    }
    
    output = p->accumulator + kpOut;
    output = (output > p->maxLimit) ? p->maxLimit : output;
    output = (output < p->minLimit) ? p->minLimit : output;

    p->lastInput = p->delta;     // save error(n) into error(n-1)
    p->Lastout = output;
        
    p->out = output * p->enable;
}
//==============================================================================
//
// Voltage saturation suppression control (VSC)
//
//==============================================================================
void VolSatSuppControl(void)
{
   f32 tmp;
  //  E1R = LPF_T(sqrt(vds*vds + vqs*vqs),E1R,0.15,0.002);
    tmp=  udcFil2 * driveParameterMenu.ratingInputVoltage /motorPara.ratingVoltage -(f32)((s32)(s16)funcCode.code.WeakFluxdepth)*0.01;
	
  	if(tmp <= LMT_VSC)//向上滤波，向下不滤波
  	{
  		LMT_VSC = tmp;
  	}
	else
	{
		LMT_VSC = LPF_K(tmp,LMT_VSC,2);
	}
	
	volSatCtr.ref = LMT_VSC;
    volSatCtr.fdb = E1R;
    volSatCtr.delta = volSatCtr.ref - volSatCtr.fdb; 
	if((motorControlMode == IM_SVC3)||(motorControlMode == IM_SVC4))
	{
		volSatCtr.propGain = fluxCtrlMenu.fluxRegPropGain * 0.3;
	    volSatCtr.integGain = OutputProcess.FluxRegInteg * 0.3;//G_VSC_I * 0.002;
	}
	else
	{
	    volSatCtr.propGain = fluxCtrlMenu.fluxRegPropGain;
	    volSatCtr.integGain = OutputProcess.FluxRegInteg;//G_VSC_I * 0.002;
	}
    
    volSatCtr.maxLimit = LMT_VSC_UL;
    volSatCtr.minLimit = LMT_VSC_LL;      
  
    volSatCtr.enable = OutputProcess.Enable;
    
    PiRegulator(&volSatCtr);
    
    idrefWeakField = volSatCtr.out;
}
extern u16 pluseStatusReadFromFpga;
//==============================================================================
//
// 输出处理，慢环
//
// 速
// 
// 反馈速度的计算过程:
// 1、得到OutputProcess.Frequency(FrequencyFiltered)/OutputProcess.EncoderSpeed/svcSpeedEst
// 2、根据控制方式(ControlAlgorithm)，对应的值赋值给OutputProcess.MotorSpeed
// 3、滤波，得到OutputProcess.MotorSpeedFiltered，作为速度环反馈
//
//==============================================================================
extern union ROTOR_POSITION_REG RotorPositionPwmReg;
extern void SvcSlipFrqCalcNew(void);
extern u16  CanRxTxCon;
f32 OutputDeltaSPu;//输出角度标幺值
f32 idRefIMSVC34;
f32 fluxLoopOutMaxcoeff = 1.1;
f32 fluxAddref;
f32 dcoeff = 0.0;
//extern u16 timeStatusReadFromFpga;
void OutputProcessSlowLoop(void)
{
    f32 tmp;
    f32 tmpMax, tmpMin; 

    pllOutMax = 100;
	pluseStatusReadFromFpga = interfaceRam[Dsp_wr_rsvd1];
    dcoeff = 0.01 * cfGroup[15];
	if(dcoeff >= 1.0)
	{
		dcoeff = 1.0;
	}
	if(dcoeff <= 0.0)
	{
		dcoeff = 0;
	}
	/*
	if(cfGroup[12] == 0)
	{
		interfaceRam[FPGA_REG_CurSampleDelay] = 120*20;
	}
	else
	{
		interfaceRam[FPGA_REG_CurSampleDelay] = cfGroup[12];
	}
	*/
	
	//timeStatusReadFromFpga = interfaceRam[Dsp_wr_rsvd1];
	if((funcCode.code.motorParaM1.InitPosDetPulse != 0)
		 &&((motorControlMode == PMSM_SVC)||(motorControlMode == PMSM_FVC))
		 )
	{
		if((ROTOR_INITIAL_STATE == DriveControl.State)
		 &&(RotorPositionPwmReg.bit.finishFlg == 0)
		  )
    	{
		    PmInitPosDet();
    	}
	}
	//IM SVC4
	//if(motorControlMode == IM_SVC4)
	{
		CalcImSVCOmg();
		CalcSvcEstCoef();
	}
	
	
// 求OutputProcess.Frequency在一个速度环周期的平均值
    {
        DINT;   // 关闭全局中断，保证数据一致性
        /*
        if (0 != outputProcessFrqTicker)
        {   // 简单的平均值滤波
            OutputProcess.FrequencyFiltered = outputProcessFrqSum / outputProcessFrqTicker;
        }
        else
        {   // 会导致 OutputProcess.MotorSpeedFiltered 会一直1.#INF
            OutputProcess.FrequencyFiltered = 0;
        }
		*/
        //OutputProcess.FrequencyFiltered = OutputProcess.Frequency;
        outputProcessFrqSum = 0;    // 清零，准备下次计算
        outputProcessFrqTicker = 0;
        EINT;
    }

#if DEBUG_P_SPINNING_LOAD
    if (TRUE == SpinningLoad.UseSpeedReference)
    {
        OutputProcess.FrequencyFiltered = SpinningLoad.SpeedReference;
        OutputProcess.MotorSpeedFiltered = SpinningLoad.SpeedReference;

        SpinningLoad.UseSpeedReference = FALSE;
    }
#endif
/////   OutputProcess.Y0DC = OutputProcess.Y0Avg = 0.0;
// 编码器反馈速度
    OutputProcess.EncoderSpeed = (f32)frqMotorRun * (TWO_PI / 100); 

// SVC时的辨识速度计算
#if DEBUG_P_SVC
   // SvcSlipFrqCalc();   // SVC时的转差频率计算，得到OutputProcess.SlipFrequency
    SvcSlipFrqCalcNew();
    svcSpeedEst = OutputProcess.FrequencyFiltered - OutputProcess.SlipFrequency;
    syncFrqEst = OutputProcess.EncoderSpeed + OutputProcess.SlipFrequency;
#endif

    // 速度反馈OutputProcess.MotorSpeed
    if (TRUE == clControl)
    {
        {
            OutputProcess.MotorSpeed = OutputProcess.EncoderSpeed;
        }
    }
#if DEBUG_P_SVC
    else if (IM_SVC1 == OutputProcess.ControlAlgorithm)
    {
        OutputProcess.MotorSpeed = svcSpeedEst;
    }
#endif
    else
    {
        OutputProcess.MotorSpeed = OutputProcess.FrequencyFiltered;
    }
    
// 滤波，得到MotorSpeedFiltered，作为速度环的反馈
#if 1
    OutputProcess.MotorSpeedFiltered = OutputProcess.MotorSpeedFiltered +
        (OutputProcess.MotorSpeed - OutputProcess.MotorSpeedFiltered) / SpdFdbFilTimeConst;

#if DEBUG_P_ERR20
// 加入编码器丢失时的处理，速度环参数调弱一拍
    {
        static u16 encodeLossFlag;  // 编码器信号丢失标记

//        if (ENCODERLOSS_DETECT_CONTINUE == encoderLossdetectMode) 
        {
//            if (fabs(encoderSpeedOld - OutputProcess.EncoderSpeed) > 
      //              3.0 * OutputProcess.SlipRated   // 上一拍编码器反馈与当前拍编码器反馈速度之差大于3倍额定转差
  //              )
            {
                encodeLossFlag = TRUE;

                OutputProcess.MotorSpeedFiltered = OutputProcess.FrequencyFiltered;
//                OutputProcess.MotorSpeedFiltered = svcSpeedEst;
                speedLoopMenu.speedRegProp = speedLoopMenu.speedRegProp * 0.3;
                speedLoopMenu.speedRegInteg = speedLoopMenu.speedRegInteg * 0.3;
            }
        }
    }
#endif

#elif 1 // 效果好像差一点？
    OutputProcess.MotorSpeedFiltered = LPF_Gain(OutputProcess.MotorSpeed,
                                        OutputProcess.MotorSpeedFiltered, OutputProcess.SpeedFilterGain);
#endif

// 一些标幺值计算
    OutputProcess.MotorSpeedPU = OutputProcess.MotorSpeed * OutputProcess.iRatedFrequency;
    OutputProcess.DroopPU = OutputProcess.Droop * OutputProcess.iRatedFrequency;
    OutputProcess.FrequencyPU = OutputProcess.FrequencyFiltered * OutputProcess.iRatedFrequency;
    OutputProcess.MotorSpeedFilteredPU = OutputProcess.MotorSpeedFiltered * OutputProcess.iRatedFrequency;
    OutputMotorSpeedFiltered = LPF_K(OutputProcess.MotorSpeedFilteredPU,OutputMotorSpeedFiltered,10);
    OutputDeltaSPu = OutputProcess.DeltaS*I_TWO_PI;
    OutputProcess.WsFilPu = OutputProcess.WsFil * OutputProcess.iRatedFrequency;

    tmp = zeroSpeedSet * OutputProcess.RatedFrequency;
    tmp = GetMax(tmp, 3.0);
    OutputProcess.ZeroSpeed = (fabs(OutputProcess.MotorSpeedFiltered) <= tmp) ? TRUE : FALSE;

#if DEBUG_P_SM_CONTROL
    if (TRUE == smControl)      // 同步机控制
    {
        OutputProcess.NeutralShift = false;
    }
    else
#endif
#if CELL_BYPASS
    if (( fabs(CommandGenerator.SpeedReferencePU) > 
          OutputProcess.PeakReductKi * (2 * 0.90) * InputProcess.Ed / OutputProcess.MotorVoltageClampLimit
        ) &&
        (TRUE == OutputProcess.CellImbalance)
       )
    {
        OutputProcess.NeutralShift = true;
    }
    else
    {
        OutputProcess.NeutralShift = false;
    }
#endif

// 速度环上下限，即转矩上下限。
// 当磁链环不能正常闭环时，减小转矩?
#if 1

	if(spdRegData.speedReference >= 0)//xubin 20220921 方便功率平衡不用修改参数
	{
		tmpMax = OutputProcess.MotorTorqueLimit;    // 直接由F2-10，F2-12确定
    	tmpMin = OutputProcess.MotorRegenLimit; 
	}
	else
	{
		tmpMax = -OutputProcess.MotorRegenLimit;    // 直接由F2-10，F2-12确定
    	tmpMin = -OutputProcess.MotorTorqueLimit; 
	}
	
    //tmpMax = OutputProcess.MotorTorqueLimit;    // 直接由F2-10，F2-12确定
    //tmpMin = OutputProcess.MotorRegenLimit; 
#elif 1
    LimitLogic(&tmpMax, &tmpMin, &OutputProcess.LimitUsed);
#if 0
    if (1 == reduceRatingCell)                  // 单元发生过载后，降额运行10min，允许下次过载
    {
        tmpMax = GetMin(tmpMax,  iqMaxReduceRating);
        tmpMin = GetMax(tmpMin, -iqMaxReduceRating);
    }
#endif
#endif
    OutputProcess.IqsMax = tmpMax;
    OutputProcess.IqsMin = tmpMin;
    if (DriveControl.State == MAGNETIZING_STATE)    // 预励磁期间，限制iq输出
	{
        OutputProcess.IqsMin = -magnetizingMaxVaule;
	    OutputProcess.IqsMax = magnetizingMaxVaule; 
	}

	//SVC3速度观测
	//if(OutputProcess.Enable == true)
	//{
	//	SVCNEWCalRotorSpeed();
	//}
	
// 上切换的相位同步计算，得到SynchTransfer.PhaseRegOutput
 //   UpTransferSlowDeal();

// 计算转矩给定
#if 0 // DEBUG_P_TORQUE_TEST
    // 测试模式
    if (TORQUE == ctrlLoopTestMenu.testType)
    {
        OutputProcess.IqsRef = TorqueTest(OutputProcess.IqsMax, OutputProcess.IqsMin);
    }
    else
#endif
// 速度调节器
#if DEBUG_P_AUTO_TUNE
    // 调谐时，部分时间需要禁止速度环，由tune自己给定
    if ((TRUE == AutoTune.OpenSpeedLoop) && (AUTO_TUNE_STATE == DriveControl.State))
    {
        iqRef = AutoTune.IqsRef + OutputProcess.Iqsff;
    }
    else
#endif
    {
#if !DEBUG_P_I_REG_ONLY
        if (CanRxTxCon > 1)       
        {
        	LoadSharingDeal1();
       	}
		else
		{
	        OutputProcessPllParams.maxLimit = pllOutMax * TWO_PI;
	        OutputProcessPllParams.minLimit = -pllOutMax * TWO_PI;
		}
        spdRegData.speedReference = CommandGenerator.SpeedReference + dropFrq * TWO_PI; ;// + SynchTransfer.PhaseRegOutput; 
        SpeedRollbackDeal();
        spdRegData.wr = OutputProcess.MotorSpeedFiltered;   // 速度反馈
        spdRegData.maxLimit = OutputProcess.IqsMax;         // 速度环输出上限
        spdRegData.minLimit = OutputProcess.IqsMin;         // 速度环输出下限 
        FastDecDeal();
        spdRegData.propGain = speedGain * SpeedLoopPIParamCalc(speedLoopMenu.speedRegPropLowFrq, speedLoopMenu.speedRegProp);
     // spdRegData.propGain = speedLoopMenu.speedRegProp;
        spdRegData.kf = speedLoopMenu.speedRegKf;
     // OutputProcess.IqGain为转矩电流环的iqGain，表示转矩电流给定的增益
        OutputProcess.IqGain = 1.0;
        spdRegData.integGain = OutputProcess.IqGain * OutputProcess.SpeedRegInteg; 
        spdRegData.enable = (OutputProcess.Enable) &&(IFmodelFlga == 0)&&
			     (OutputProcess.SpeedRegulatorEnable) 
			     &&
                (DriveControl.State != MAGNETIZING_STATE)
                //||((DriveControl.State != AUTO_TUNE_STATE)&&
                 //(((motorControlMode == PMSM_SVC)||(motorControlMode == PMSM_FVC))))
                 && speedLoopSpinEnable
                 &&(dcBrakeStartflag != 1);  
        SpeedRegulator(&spdRegData);
        iqRef = spdRegData.out + OutputProcess.Iqsff;   
        // 瞬停不停功能函数

#if (INV_TYPE == HW_HD90)          
        RunWithoutMidVoltage();
#endif

#endif
    }
     // 磁链环调节器
    if ((motorControlOtherEnable.bit.fastSpinningLoad) &&
        (TRUE == FastSpinningLoad.UseFluxFdbFastSpinningLoad)
        )
    {
        OutputProcess.FluxDS = SpinningLoad.FluxReference;
        FastSpinningLoad.UseFluxFdbFastSpinningLoad = FALSE;
    }
    FluxIMAddCalc();
// 叠频制动时，使用同步滤波值    
	if((cfGroup[12] != 0)&&(AUTO_TUNE_STATE != DriveControl.State))
    {
		//fluxFdb = moudleCMCoeff * VMPhiOB/PhiRefOB + OutputProcess.FluxDS * moudleVMCoeff;
		fluxFdb = moudleCMCoeff * VMPhiOB/PhiRefOB + fluxDSBackEMFFil * moudleVMCoeff
		          - fluxAddref ;
	}
	else
	{
    	if(AUTO_TUNE_STATE == DriveControl.State)
    	{
			fluxAddref = 0;
		}
		
    	fluxFdb =  OutputProcess.FluxDS - fluxAddref;
	}

   if(AUTO_TUNE_STATE == DriveControl.State)
    {
        if(CommandGenerator.FluxReference >= 1.0)
        {
			CommandGenerator.FluxReference = 1.0;
		}		
	}
	   
    {   // 异步机磁链环
//#if (DEBUG_P_FLUX_REG && (!DEBUG_P_I_REG_ONLY))
#if (1)      
		fluxRegData.fluxRef = CommandGenerator.FluxReference;
        fluxRegData.fluxDsFil = fluxFdb;
        fluxRegData.propGain = fluxCtrlMenu.fluxRegPropGain;
        fluxRegData.integGain = OutputProcess.FluxRegInteg;
        fluxRegData.idsRated = fluxLoopOutMax;
        fluxRegData.mi = modulationIndex;
        fluxRegData.filterGain = OutputProcess.FluxFilterGain;
        fluxRegData.lSigma = motorPara.lSigma;
        fluxRegData.iNoload = motorPara.iNoload;                            // 下切换和环流处理
        fluxRegData.iqGain = OutputProcess.IqGain; 
        fluxRegData.piRegulatorEnable = OutputProcess.FluxPIRegulatorEnable 
			                            && (dcBrakeStartflag != 1);    // 高启动转矩模式与正常模式区分开
        fluxRegData.globalEnable = OutputProcess.Enable
			                          && (dcBrakeStartflag != 1);
        FluxRegulator(&fluxRegData);
        idRefTmp = fluxRegData.out;
        if (((motorControlMode == IM_SVC1)||(motorControlMode == IM_SVC2))
			|| (AUTO_TUNE_STATE == DriveControl.State))
        {
    		idRef = idRefTmp;
        }

		else if(motorControlMode == IM_SVC4)
		{
			idRefIMSVC34 = motorPara.iNoloadA / (motorPara.ratingCurrent*SQRT2);		
			idRef = FieldWeakeningIMSVC4(idRefIMSVC34);//异步机SVC3、4弱磁处理
			
			//VolSatSuppControl();
			//idRef = motorPara.iNoloadA / (motorPara.ratingCurrent*SQRT2) + idrefWeakField;
		}
        	    	
		if((motorControlMode == PMSM_SVC) ||(motorControlMode == PMSM_FVC))
		{
        	VolSatSuppControl();
			IdrefPmsmCalc();
			PmsmMtpaCalc();
			idRef = idRef + idrefWeakField + PmsmMtpa.id;
			
			//idRef = idRef + idrefWeakField;
			//idRef = idRef + idrefWeakField + PmsmMtpa.id;// + PmsmMtpa(void);
			//idRef = fluxRegData.iNoload;
			//此处增加MTPA  定子磁链定向 ，这里是转子磁链，需要调整位置
		}
#elif 0

#if 0
        // 磁链不闭环，使用空载电流作为励磁电流
        idRef = motorPara.iNoload;
#elif 1
        idSetRamp1.maxValue = 1.0;
        idSetRamp1.tickerAll = 2000/SLOW_LOOP_TIME_MS;
        idSetRamp1.aimValue = motorPara.iNoload;
        if (!coreRunStatus.bit.run)
        {
            idSetRamp1.curValue = 0;    // 停机时要清零
        }
        else
        {
            RampCalc(&idSetRamp1); 
        }
        idRef = idSetRamp1.curValue;
#endif

#endif
    }


#if DEBUG_P_DUAL_FRQ_BRAKE
// 确定叠频制动是否有效
// 有效时，计算叠频制动的损耗(loss reference)
    {
        dualFrqBrake.configBrakingEnable = OutputProcess.BrakingEnable;

        dualFrqBrake.wsFilPu = OutputProcess.WsFilPu;
        dualFrqBrake.motorSpeed = OutputProcess.MotorSpeed;
        dualFrqBrake.iqsRef = OutputProcess.IqsRef;
        dualFrqBrake.iqsMax = OutputProcess.IqsMax;
        dualFrqBrake.iqsMin = OutputProcess.IqsMin;
        dualFrqBrake.regenTorqueLimit = OutputProcess.MotorRegenLimit;
        dualFrqBrake.stateIsNotMag = (MAGNETIZING_STATE != DriveControl.State);
        dualFrqBrake.voltageClampLimit = GetMin(OutputProcess.PeakVoltageClampLimit, OutputProcess.MotorVoltageClampLimit);
        dualFrqBrake.deadTimeComp = OutputProcess.DeadTimeComp;
        dualFrqBrake.outVol = outVoltagePrg;
        dualFrqBrake.inPrcEd = InputProcess.Ed;
        dualFrqBrake.MotorVoltageClampLimit = OutputProcess.MotorVoltageClampLimit;
        dualFrqBrake.iRatedFrequency = OutputProcess.iRatedFrequency;
        DualFrequencyAndRegenBraking(&dualFrqBrake);
    }
#endif
    OutputProcess.IdsFil =LPF_K(OutputProcess.Ids, OutputProcess.IdsFil, 2);
    OutputProcess.IqsFil =LPF_K(OutputProcess.Iqs, OutputProcess.IqsFil, 2);
   // OutputProcess.TotalCurrent = SqrtA2AddB2(OutputProcess.Iqs, OutputProcess.Ids);
    OutputProcess.TotalCurrent = SqrtA2AddB2(OutputProcess.IqsFil, OutputProcess.IdsFil);
// 总电流进行滤波，输出缺相判断可以使用
    OutputProcess.TotalCurrentFil = LPF_K(OutputProcess.TotalCurrent, OutputProcess.TotalCurrentFil, 100);  // 1/(1-0.99)=100
    
#if !DEBUG_PRG_IN_RAM
// 计算电机电压
    tmp  = OutputProcess.WsFilPu * OutputProcess.FluxDSFil + OutputProcess.IqsFil * motorPara.rs;
  //  OutputProcess.MotorVoltage = LPF_K(SqrtA2AddB2(tmp, (OutputProcess.IdsFil * motorPara.rs)), 
  //      OutputProcess.MotorVoltage, 40);  // 1/(1-0.975) = 40
   OutputProcess.MotorVoltage = SqrtA2AddB2(tmp, (OutputProcess.IdsFil * motorPara.rs));
// 功率因数计算
    tmp = PowerFactorCalc(OutputProcess.IqsFil, OutputProcess.IdsFil);
    OutputProcess.PowerFactor = LPF_K(tmp, OutputProcess.PowerFactor, 10);
#endif

// 平均功率
    tmp = OutputProcess.ShaftPower +
         OutputProcess.TotalCurrent * OutputProcess.TotalCurrent * OutputProcess.StatorResistance;
    //OutputProcess.AveragePower = LPF_K(tmp, OutputProcess.AveragePower, 10);  // 1/(1-0.90) = 10

// 高启动转矩控制
   // HighStartingTorqueStateMachine();
#if 1
// 高启动转矩模式无效时，为如下代码
//void HighStartingTorqueStateMachine(void)
{
    OutputProcess.SMDCMode = DISABLED;
	
   // OutputProcess.SpeedRegulatorEnable = true;
    OutputProcess.FluxPIRegulatorEnable = true;
    OutputProcess.RampHold = false;
    OutputProcess.Iqsff = 0.0;
  //  PLLEnablePMM = true;
    OutputProcess.usePllAndDroop = true;
  //  SpeedLoopPreset = false;
    if((motorControlMode == PMSM_SVC)||(motorControlMode == PMSM_FVC))
    {
		if ((AUTO_TUNE_STATE == DriveControl.State)||(MAGNETIZING_STATE == DriveControl.State))
		{
			OutputProcess.SpeedRegulatorEnable = false;
		}
		else
		{
		   	OutputProcess.SpeedRegulatorEnable = true;
		}
	}
    else
	{
			OutputProcess.SpeedRegulatorEnable = true;
 	}
}
#endif


// 死区补偿使能标志
    {
        if (OutputProcess.TotalCurrent < 0.02)
        {
            OutputProcess.DeadTimeCompEnable = FALSE;
        }
        else if (OutputProcess.TotalCurrent > 0.05)
        {
            OutputProcess.DeadTimeCompEnable = TRUE;
        }
    }

// 环流和上切换时，计算 idRef, iqRef
    // 限幅设定，放在 TransferSlowDeal() 之前
// 磁链环上限=输出电流限制*k
    //fluxLoopOutMax = OutputProcess.MaximiumLoadCurrent * 0.9;   // 磁链环输出限幅
    fluxLoopOutMax = OutputProcess.MaximiumLoadCurrent * fluxLoopOutMaxcoeff;
    idLoopOutMax = IdLoopOutMax_K;                              // id电流环输出限幅
//    TransferSlowDeal();

#if DEBUG_P_I_REG_ONLY

#if 0
    iqRef = (s32)(s16)CirCurSet * (1.0 / 1000);
#elif 1
    iqSetRamp1.maxValue = 1.0;
    iqSetRamp1.tickerAll = 2000/SLOW_LOOP_TIME_MS;
    iqSetRamp1.aimValue = (s32)(s16)CirCurSet * (1.0 / 1000);
    if (!coreRunStatus.bit.run)
    {
        iqSetRamp1.curValue = 0;    // 停机时要清零
    }
    else
    {
        RampCalc(&iqSetRamp1); 
    }
    iqRef = iqSetRamp1.curValue;
#endif

#endif


// 负荷分配的一些处理
// 主要是iqRef的修改
// 须放在 UpdateFastLoopPara() 之前
#if DEBUG_P_LOAD_SHARING
//    LoadSharingDeal();      
#endif

// idRef, iqRef更新至电流环使用的 OutputProcess.IdsRef, OutputProcess.IqsRef。
// 一些快环使用数据的初始化
	PMSMCurParaAutoTune();
    UpdateFastLoopPara();

// 一些显示数据的滤波
    idRefFil = LPF_K(idRef, idRefFil, 50);                  // 显示使用
    idFdbFil = LPF_K(OutputProcess.Ids, idFdbFil, 50);      // 显示使用
    iqFdbFil = LPF_K(OutputProcess.Iqs, iqFdbFil, 50);
    pllFluxSFrqFil = LPF_K(pllFluxSFrq, pllFluxSFrqFil, 50);
    fluxFdbFil = LPF_K(fluxFdb, fluxFdbFil, 50);

#if !DEBUG_PRG_IN_RAM
    inputE0Fil = LPF_K(InputProcess.E0Average, inputE0Fil, 50);             // 输入电压零序分量
    outputE0AvgFil = LPF_K(OutputProcess.E0Avg, outputE0AvgFil, 20);        // 输出电压零序分量
    inputINegFil = LPF_K(InputProcess.INegSeqTotal, inputINegFil, 50);      // 输入电流负序分量
    outputINegFil = LPF_K(OutputProcess.INegSeqTotal, outputINegFil, 50);   // 输出电流负序分量
    outputE0Fil = LPF_K(outVolData.e0, outputE0Fil, 50);                    // 输出电压的伏秒，零序分量

    // 380皮带机下垂控制转矩电流滤波时间64ms
    iqFdbDroopFil = LPF_T(OutputProcess.Iqs, iqFdbDroopFil, 64, MAIN_LOOP_TIME_MS);
#endif
}

//==============================================================================
//
// 电流环参数自整定
//
//==============================================================================
	
f32 kp_d_Pmsm;
f32 ki_d_Pmsm;
f32 kp_q_Pmsm;
f32 ki_q_Pmsm;

void PMSMCurParaAutoTune(void)
{
	//f32 gPm_Rs,gPm_Ld,gPm_Lq;
	f32 Td,Td_Per;
	
	f32 kp_d;
    f32 ki_d;
	f32 kp_q;
	f32 ki_q;

	//static f32 zunibi = 0.707;
	//防止除0
	if(OutputProcess.FastLoopFrequency < 0.000001)
	{
		OutputProcess.FastLoopFrequency = 0.000001;
	}
	Td = 1.5 / OutputProcess.FastLoopFrequency;
	Td_Per = Td / motorPara.iFPuOmegaOne;//时间标幺
	if((motorControlMode == PMSM_SVC)||(motorControlMode == PMSM_FVC))
	{

		//Td = 1.5Tc 延迟时间为1.5倍的电流环执行周期
		//Td = 1.5 / OutputProcess.FastLoopFrequency;
		//Td_Per = Td / motorPara.iFPuOmegaOne;//时间标幺

		kp_d = motorPara.smLd * 1.15 / (2.0 * Td_Per);//motorPara.smLd标幺值无单位
		//Ki=R/(2*Td*Kpwm)*Tc=R/(3*Kpwm)
		ki_d = motorPara.smRs * 1.15 / 3.0;//motorPara.smRs标幺值无单位

		kp_q = motorPara.smLq * 1.15 / (2.0 * Td_Per);//motorPara.smLq标幺值无单位
		ki_q = ki_d;
	}
	else
	{
		/*
		kp_d =  0.4 * motorPara.lSigma /( OutputProcess.FastLoopSamplePeriod/(1.0/(TWO_PI * motorPara.ratingFrq )));
		ki_d =  0.8 * kp_d * (motorPara.rs) ;
		*/
		kp_d =  1.25 * motorPara.lSigma;
		ki_d =  0.5  * (motorPara.rs) * OutputProcess.FastLoopSamplePeriod / motorPara.iFPuOmegaOne  ;
		kp_q = kp_d;
		ki_q = ki_d;
	}
	
	kp_d_Pmsm = kp_d;
	ki_d_Pmsm = ki_d;

	kp_q_Pmsm = kp_q;
	ki_q_Pmsm = ki_q;
}

extern u16 PLLEnablePMM;
//extern f32 iTotalRef;
f32 swPoleCoeff = 1.0;
f32 TmpstopRefIntor,TmpstopRef;

f32 angel_test = 0.25;
f32 sin_test,cos_test;
f32 buchang = 0;
f32 fb = 10.0;
f32 Idaikuan = 0.1;
u16 ACRPiSelfAdation = 0;
f32 RsSwitch30Hz;
//==============================================================================
//
// 一些快环使用数据的初始化
//
//==============================================================================
void UpdateFastLoopPara(void)
{
//----------------fluxSData-----------------------------
    f32 rsTmp;
    f32 lsTmp;
    f32 enable1;
//----------------fluxSData-----------------------------

//----------------pllDataS-----------------------------
    f32 pllFeedForward;
    f32 enable2;
//----------------pllDataS-----------------------------

//----------------idRegData iqRegData-----------------------------
    f32 kp_d;
    f32 ki_d;
	f32 kp_q;
    f32 ki_q;
//        f32 idLoopOutMax1;
//----------------idRegData iqRegData-----------------------------
    f32 K;
//----------------fluxSData-----------------------------
    rsTmp = OutputProcess.StatorResistance * OutputProcess.RatedFrequency;  //
    lsTmp = motorPara.ls;       //

    //荣信50Hz电流波动
    //定子30Hz~50Hz电阻线性减小
	//使用反馈电压时，定子电阻不用线性减小
	if(funcCode.code.ObVolSel == 2)
	{
		rsTmp = OutputProcess.StatorResistance * OutputProcess.RatedFrequency;
	}
	else
	{
		if(AUTO_TUNE_STATE == DriveControl.State)
   		{
        	rsTmp = OutputProcess.StatorResistance * OutputProcess.RatedFrequency;
    	}
		else
		{
			if (fabs(CommandGenerator.SpeedReference) > (TWO_PI *30.0) )
        	{
            	if((50.0*TWO_PI - fabs(CommandGenerator.SpeedReference)) > 0.0)
            	{
                	rsTmp = (((OutputProcess.StatorResistance-0.01) * OutputProcess.RatedFrequency)*(50.0*TWO_PI - fabs(CommandGenerator.SpeedReference))/((TWO_PI *20.0))) + 0.01;
            	}
            	else
            	{
                	rsTmp = (0.01 * OutputProcess.RatedFrequency);
            	}
        	}
			else
			{
				rsTmp = OutputProcess.StatorResistance * OutputProcess.RatedFrequency;
			}
			
		}
    }
	RsSwitch30Hz = rsTmp;
#if DEBUG_P_SYNC_TRANSFER
//    if ((SYNCH_TRANSFER_DOWN == synchTransfer) ||
//        (WAITING_FOR_PHASE_LOCK <= SynchTransfer.UpTransferState)
//        )
//    {
//        rsTmp = 0.0;
//        lsTmp = 0.0;
//    }
#endif

    enable1 = 
        (
#if DEBUG_P_SM_CONTROL
         (PLLEnablePMM && OutputProcess.SMFieldEnable) ||   // 励磁步机
         ((SM_SVC != OutputProcess.ControlAlgorithm) &&
          (SMDC_SVC != OutputProcess.ControlAlgorithm) &&
           OutputProcess.Enable
         )
         // ||
#elif 1
        OutputProcess.Enable 
        //||
#endif
//         (SYNCH_TRANSFER_DOWN == synchTransfer)          // 下切换，也要使能
        ); 
//----------------fluxSData-----------------------------

//----------------pllDataS-----------------------------
#if 0//DEBUG_P_SYNC_TRANSFER
//    if (SYNCH_TRANSFER_DOWN == synchTransfer)
 //   {   // 以电网频率作为前馈
        // 还需要修改，采样的电网频率有可能为负
 //       pllFeedForward = TWO_PI * INPUT_BUS_FRQ;
 //   }
//    else
#endif
    {
        pllFeedForward = (clControl) ? 
            OutputProcess.EncoderSpeed : 0.0;
//        pllFeedForward = 0.0;
//                OutputProcess.EncoderSpeed;
//                CommandGenerator.SpeedReference;
    }
    enable2 = OutputProcess.Enable || 
        OutputProcess.SpinningLoadEnable 
        //|| 
//        (SYNCH_TRANSFER_DOWN == synchTransfer)
			;
//----------------pllDataS-----------------------------


//----------------idRegData iqRegData-----------------------------
#if DEBUG_P_DUAL_FRQ_BRAKE
    if (TRUE == OutputProcess.Braking)
    {
        //kp = currentLoopMenu.currentRegPropBraking;
        //ki = OutputProcess.CurrentRegIntegBraking;
        kp_d = currentLoopMenu.currentRegPropBraking;
        ki_d = OutputProcess.CurrentRegIntegBraking;
        kp_q = currentLoopMenu.currentRegPropBraking;
        ki_q = OutputProcess.CurrentRegIntegBraking;
//        idLoopOutMax1 = internalPeakVoltageClampLimit * 0.5;
        idLoopOutMax1 = idLoopOutMax * 1.25;
    }
    else
#endif
    {
    	if(cfGroup[17] == 1)//电流环参数自适应
    	{
			kp_d = kp_d_Pmsm * currentLoopMenu.currentRegProp / 0.3;
			ki_d = ki_d_Pmsm * currentLoopMenu.currentRegInteg / 15.0;
			kp_q = kp_q_Pmsm * currentLoopMenu.currentRegProp / 0.3;
			ki_q = ki_q_Pmsm * currentLoopMenu.currentRegInteg / 15.0;
    	}
		else
		{
			kp_d = currentLoopMenu.currentRegProp;
			ki_d = OutputProcess.CurrentRegInteg;
			kp_q = currentLoopMenu.currentRegProp;
			ki_q = OutputProcess.CurrentRegInteg;
		}
    
        //kp = currentLoopMenu.currentRegProp;
        //ki = OutputProcess.CurrentRegInteg;
//        idLoopOutMax1 = internalPeakVoltageClampLimit * 0.3;
        idLoopOutMax1 = idLoopOutMax;
  
    } 
//----------------idRegData iqRegData-----------------------------


    DINT;   // 保证电流环快环中断使用的数据是对应的。
    if((motorControlMode == PMSM_SVC)||(motorControlMode == PMSM_FVC))
    {
		if (AUTO_TUNE_STATE != DriveControl.State)
		{
    		OutputProcess.IdsRef = idRef;
    		OutputProcess.IqsRef = iqRef;
		}
	}
    else
	{
    	//OutputProcess.IdsRef = idRef;
    	//OutputProcess.IqsRef = iqRef;

		if ((AUTO_TUNE_STATE != DriveControl.State) ||
			((AUTO_TUNE_STATE == DriveControl.State) && (AT_DONE != AutoTune.StatusStage2)))
		{
			OutputProcess.IdsRef = idRef;	
			OutputProcess.IqsRef = iqRef;
		}
 	}

// fluxSData的一些初始化
    fluxSData.wHw = fluxStatorObserverMenu.lowFrqWo;
    fluxSData.rs = rsTmp;
//if(fabs(CommandGenerator.SpeedReference /motorPara.iFPuOmegaOne) 
   if(cfGroup[14] == 0)
   {
		swPoleCoeff = 1.0;
   }
   else
   {
		swPoleCoeff = (f32)cfGroup[14]  * 0.1;
		if(swPoleCoeff >= 15.0)
		{
			swPoleCoeff = 15.0;
		}
		if(swPoleCoeff <= 1.0)
		{
			swPoleCoeff = 1.0;
		}
   }
    if(fabs(CommandGenerator.SpeedReference *I_TWO_PI) <= 20.0)
    {
		fluxSData.softwareCompPole = fluxStatorObserverMenu.swCompensatorPole;
	}
	else
	{
	    K = 10.0 - (30.0 - fabs(CommandGenerator.SpeedReference *I_TWO_PI));
		if(K >= swPoleCoeff)
		{
			K = swPoleCoeff;
		}
		fluxSData.softwareCompPole = fluxStatorObserverMenu.swCompensatorPole * K ;

	}
   // fluxSData.softwareCompPole = fluxStatorObserverMenu.swCompensatorPole * 2.0;
    fluxSData.lowFrqComGain = fluxStatorObserverMenu.lowFrqComGain;
    fluxSData.samplePeriod = OutputProcess.FastLoopSamplePeriod;
    fluxSData.spinningLoadEnable = OutputProcess.SpinningLoadEnable;
    fluxSData.isSpin = (SPINNING_LOAD_STATE == DriveControl.State);
    fluxSData.ls = lsTmp;
    fluxSData.enable = enable1;

// pllDataS的一些初始化
    pllDataS.sampleRate = OutputProcess.FastLoopSamplePeriod;
    pllDataS.seed = pllFeedForward;
    pllDataS.enable = enable2;
    
//    DownTransferPhaseLockDeal();

// pllDataBackEmf的一些初始化
    pllDataBackEmf.sampleRate = OutputProcess.FastLoopSamplePeriod;
    pllDataBackEmf.seed = (clControl) ? 
        OutputProcess.EncoderSpeed : 0.0;
//            pllDataBackEmf.seed = 0.0;
//            pllDataBackEmf.seed = OutputProcess.EncoderSpeed;
    pllDataBackEmf.enable = TRUE;

// idRegData 的
	if((IFmodelFlga == 1)&&(AUTO_TUNE_STATE != DriveControl.State))
    {
    	OutputProcess.IdsRef = motorPara.IfModeRefCur;
    }
	else if(dcBrakeStartflag == 1)
	{
		idRegData.reference = dcBrakeStartCur;
	}
	else if(coreMainCmd.bit.DCBrakeStatus == 1)
	{   
	   	if(dcBrakeStopCur > idStopDC)
	    {
			idRegData.reference = idStopDC;
	   	}
		else
		{
			idRegData.reference = dcBrakeStopCur;
		}
	}//此方案适合停机时候的直流制动
	else
	{
		idRegData.reference = OutputProcess.IdsRef;
	}

    //idRegData.propGain = kp; 
    idRegData.propGain = kp_d;
	if(outVoltagePrg >= 1.1)
	{
    	//idRegData.integGain = ki * 1.3 * outVoltagePrg;
		idRegData.integGain = ki_d * 1.3 * outVoltagePrg;
		
	}
	else
	{
		//idRegData.integGain = ki;
		idRegData.integGain = ki_d;
	}
//        idRegData.maxLimit = idLoopOutMax1;
//    idRegData.fluxReference = CommandGenerator.FluxReference;

// iqRegData 的一些初始化
   // if (cfGroup[11] == 1000)
	if(IFmodelFlga == 1)
    {
    	OutputProcess.IqsRef = 0.0;
    }
	else if(dcBrakeStartflag == 1)
	{
		iqRegData.reference = 0;
	}
	else if(coreMainCmd.bit.DCBrakeStatus == 1)
	{   
	    if(dcBrakeStopCur > idStopDC)
	    {
			
			TmpstopRef= sqrt(dcBrakeStopCur * dcBrakeStopCur  - idStopDC * idStopDC) ;
			if(iqRegData.reference < TmpstopRef)
			{
				TmpstopRefIntor = TmpstopRefIntor + 0.02;
			}
			else
			{
				TmpstopRefIntor = TmpstopRefIntor - 0.02;
			}
			iqRegData.reference =	TmpstopRefIntor;
	    }
		else
		{
			iqRegData.reference = 0;
		}
	}//此方案适合停机时候的直流制动
	else
	{
		iqRegData.reference = OutputProcess.IqsRef;
	}
	TmpstopRefIntor = iqRegData.reference;
    //iqRegData.reference = OutputProcess.IqsRef;
    //iqRegData.propGain = kp;
	iqRegData.propGain = kp_q;
	if(outVoltagePrg >= 1.1)
	{
    	//iqRegData.integGain = ki * outVoltagePrg;
		iqRegData.integGain = ki_q * outVoltagePrg;
	}
	else
	{
		//iqRegData.integGain = ki;
		iqRegData.integGain = ki_q;
	}
    iqRegData.maxLimit = iqLoopOutMax;
    iqRegData.motorSpeed = OutputProcess.MotorSpeedFiltered;
//    iqRegData.globalEnable = OutputProcess.Enable;
	/*
	//电流环带宽测试
	if(OutputProcess.Enable == 1)
	{
		buchang = fb*TWO_PI*1024.0/OutputProcess.FastLoopFrequency;
		angel_test = buchang + angel_test;
	}
	else
	{
		angel_test = 0;
	}
	sincos(angel_test/1024.0,&sin_test,&cos_test);
	
	OutputProcess.IdsRef = 0;
	OutputProcess.IqsRef = Idaikuan*sin_test;
	//OutputProcess.IqsRef = 0.1;

	idRegData.reference = OutputProcess.IdsRef;
	iqRegData.reference = OutputProcess.IqsRef;
		*/

// peakReductionData的一些初始化
    peakReductionData.biasGain = biasGain;
    peakReductionData.peakReductMax = OutputProcess.PeakReductMax1;
    peakReductionData.peakReductKi = OutputProcess.PeakReductKi;
    peakReductionData.peakReductA = OutputProcess.PeakReductA;
    peakReductionData.peakReductB = OutputProcess.PeakReductB;
    peakReductionData.peakReductC = OutputProcess.PeakReductC;
    peakReductionData.enable = OutputProcess.Enable;

// dualFrqBrake的一些初始化
    dualFrqBrake.samplePeriod = OutputProcess.FastLoopSamplePeriod;
    
    EINT;

#if !DEBUG_PRG_IN_RAM
  //  iTotalRef = SqrtA2AddB2(OutputProcess.IdsRef, OutputProcess.IqsRef);    // 输出总电流，给定

#define I_NEGSEQTOTAL_FILTER_T  0.2     // 输出电流的负序分量滤波时间, _s
    iNegGainR = OutputProcess.FastLoopSamplePeriod * (1.0 / I_NEGSEQTOTAL_FILTER_T);
#endif
}


#if DEBUG_P_SAVE_ENERGY
/*========================================================================================*
* FUNCTION:
*        SaveEnergyCalc
* INPUT:
*       iqRef
* RETURN:
*       fluxRegData.fluxRef
* CALLED BY:
*       void OutputProcessSlowLoop(void)
* AUTHOR:
*       TangJie
* DATA:
*       2012.11.27
*=========================================================================================*/
/*
#define ENERGY_SAVE_GAINR 0.002                                          // 节能滤波增益
#define ENERGY_SAVE_FLUX_MIN 0.6                                         // 节能最小磁链给定
f32 energySaveCurveSlope = 0.6;                                          // 节能曲线斜率
void SaveEnergyCalc(void)
{
      f32 tmp;

      energySaveIq = LPF_GainR(iqRef, energySaveIq, ENERGY_SAVE_GAINR);
      tmp = fabs(energySaveIq) * energySaveCurveSlope + ENERGY_SAVE_FLUX_MIN;
      
	  if (tmp > 1.0)
	  {	  
	  	   energySaveCalcOutput = 1.0;
	  }
	  else
	  {
		   energySaveCalcOutput = tmp;
	  }
}
*/
#endif



/*

#if DEBUG_P_ONLY_SIN

f32 outPhaseFpga;               // 输出电压指令的相位
f32 outPhaseFpgaPrime;          //

extern f32 outPhaseStep;

f32 ua1,ub1,uc1;
f32 ua,ub,uc;
f32 ua1P,ub1P,uc1P;
f32 uaP,ubP,ucP;

struct OUTPUT_VOLTAGE_A outputVolA;
//==============================================================================
//
// 计算给FPGA的输出电压指令，仅有正弦波
// 调试FPGA发PWM波时使用
// 当 F0-01=9时，才会调用该函数
//
//==============================================================================
void UpdateFpgaVoltageDataSinOnly(void)
{
    f32 a,b,c;
    static f32 vaLastUpdateA, vbLastUpdateA, vcLastUpdateA;
    static Uint16 runOld;

    if (coreRunStatus.bit.run)
    {
        outPhaseFpga += outPhaseStep;
        if (outPhaseFpga > _IQ(1))
            outPhaseFpga -= _IQ(1);
        else if (outPhaseFpga < _IQ(-1))
            outPhaseFpga += _IQ(1);

        a = _IQcosPU(outPhaseFpga);
        b = _IQcosPU(outPhaseFpga - _IQ(1.0/3));
        c = _IQcosPU(outPhaseFpga - _IQ(2.0/3));
        a = _IQmpy(a, volAmpl);
        b = _IQmpy(b, volAmpl);
        c = _IQmpy(c, volAmpl);

#if 1
        ua1 = a;
        ub1 = b;
        uc1 = c;

        {
            peakReductionData.aref = ua1;
            peakReductionData.bref = ub1;
            peakReductionData.cref = uc1;
            peakReductionData.speedRef = OutputProcess.PerUnitSpeedReference;     // outVoltagePrg
            peakReductionData.biasGain = biasGain;
            peakReductionData.peakReductMax = OutputProcess.PeakReductMax1;
            peakReductionData.peakReductKi = OutputProcess.PeakReductKi;
            peakReductionData.peakReductA = OutputProcess.PeakReductA;
            peakReductionData.peakReductB = OutputProcess.PeakReductB;
            peakReductionData.peakReductC = OutputProcess.PeakReductC;
            peakReductionData.enable = OutputProcess.Enable;
            PeakReductionCalc(&peakReductionData);
            ua = peakReductionData.ea;
            ub = peakReductionData.eb;
            uc = peakReductionData.ec;
        }

        a = ua;
        b = ub;
        c = uc;
#endif

        outputVolA.va = a;
        outputVolA.vb = b;
        outputVolA.vc = c;

        if (FALSE == runOld)    // FALSE->TRUE
        {
            vaLastUpdateA = 0;
            vbLastUpdateA = 0;
            vcLastUpdateA = 0;
        }
        else
        {
            vaLastUpdateA = outputVolA.vaPrime;                      // save last values
            vbLastUpdateA = outputVolA.vbPrime;
            vcLastUpdateA = outputVolA.vcPrime;
        }

        outputVolA.vaStep = (outputVolA.va - vaLastUpdateA) * OutputProcess.iStep;
        outputVolA.vbStep = (outputVolA.vb - vbLastUpdateA) * OutputProcess.iStep;
        outputVolA.vcStep = (outputVolA.vc - vcLastUpdateA) * OutputProcess.iStep;

        outPhaseFpgaPrime = outPhaseFpga + outPhaseStep / 2;
        a = _IQcosPU(outPhaseFpgaPrime);
        b = _IQcosPU(outPhaseFpgaPrime - _IQ(1.0/3));
        c = _IQcosPU(outPhaseFpgaPrime - _IQ(2.0/3));
        a = _IQmpy(a, volAmpl);
        b = _IQmpy(b, volAmpl);
        c = _IQmpy(c, volAmpl);
#if 1
        ua1P = a;
        ub1P = b;
        uc1P = c;

        {
            peakReductionData.aref = ua1P;
            peakReductionData.bref = ub1P;
            peakReductionData.cref = uc1P;
            peakReductionData.speedRef = OutputProcess.PerUnitSpeedReference;     // outVoltagePrg
            peakReductionData.biasGain = biasGain;
            peakReductionData.peakReductMax = OutputProcess.PeakReductMax1;
            peakReductionData.peakReductKi = OutputProcess.PeakReductKi;
            peakReductionData.peakReductA = OutputProcess.PeakReductA;
            peakReductionData.peakReductB = OutputProcess.PeakReductB;
            peakReductionData.peakReductC = OutputProcess.PeakReductC;
            peakReductionData.enable = OutputProcess.Enable;
            PeakReductionCalc(&peakReductionData);
            uaP = peakReductionData.ea;
            ubP = peakReductionData.eb;
            ucP = peakReductionData.ec;
        }

        a = uaP;
        b = ubP;
        c = ucP;
#endif
        outputVolA.vaPrime = a;
        outputVolA.vbPrime = b;
        outputVolA.vcPrime = c;

        outputVolA.vaPrimeStep = (outputVolA.vaPrime - outputVolA.va) * OutputProcess.iStep;
        outputVolA.vbPrimeStep = (outputVolA.vbPrime - outputVolA.vb) * OutputProcess.iStep;
        outputVolA.vcPrimeStep = (outputVolA.vcPrime - outputVolA.vc) * OutputProcess.iStep;

#if 0   // 暂时step给0
        outputVolA.vaStep = 0;
        outputVolA.vbStep = 0;
        outputVolA.vcStep = 0;

        outputVolA.vaPrimeStep = 0;
        outputVolA.vbPrimeStep = 0;
        outputVolA.vcPrimeStep = 0;
#endif 
    }
    else    // 停机时清零
    {
//     ......   outputVolA.va = 0; 
    }

    runOld = coreRunStatus.bit.run;

    ModInterpUpdateMacro(vaLastUpdateA, vbLastUpdateA, vcLastUpdateA, 
        outputVolA.vaStep, outputVolA.vbStep, outputVolA.vcStep, 
        outputVolA.va, outputVolA.vb, outputVolA.vc, 
        outputVolA.vaPrimeStep, outputVolA.vbPrimeStep, outputVolA.vcPrimeStep);
}
#elif 1
void UpdateFpgaVoltageDataSinOnly(void){}
#endif
*/
 



extern LINE_STRUCT outVolLine;
extern struct PHASE_LOCK_LOOP_STR pllDataInputPrc;
extern struct PiDataType InputProcessPllParams;
extern struct REGULATOR_STR regulatorDataId;
extern struct REGULATOR_STR regulatorDataIq;
extern struct PiDataType idRegulatorParams;
extern struct PiDataType iqRegulatorParams;
//extern struct REGULATOR_STR upTransfer;
extern struct PiDataType upTransferPI;
//==============================================================================
//
// 上电初始化性能的一些变量
//
//==============================================================================
void InitPerformanceData(void)
{
// 剔除毛刺的参数赋值
//    iuBurrFilter.errMin = _IQ(0.146484375);
//    iuBurrFilter.errMax = _IQ(3.90625);
//    ivBurrFilter.errMin = _IQ(0.146484375);
//    ivBurrFilter.errMax = _IQ(3.90625);

//    outVolLine.mode = 0;
//    outVolLine.x1 = 0;
//    outVolLine.y1 = 0;
    outVolLine.y2 = 0x7FFF;

    fluxSData.pOutPllPi = &OutputProcessPllParams;
    pllDataS.pllParams = &OutputProcessPllParams;
    pllDataBackEmf.pllParams = &BackEMFPllParams;
    iqRegData.iqGain = &OutputProcess.IqGain;
    iqRegData.enable = &OutputProcess.TorqueRegEnable;
    spdRegData.speedRollback = &OutputProcess.SpeedRollback;
    pllDataInputPrc.pllParams = &InputProcessPllParams;
    pllDataInputPrc.enable = TRUE;

    regulatorDataId.pi = &idRegulatorParams;
    regulatorDataIq.pi = &iqRegulatorParams;
    
#if DEBUG_P_SYNC_TRANSFER
//    upTransfer.pi = &upTransferPI;
#endif

    dualFrqBrake.idsFil = &OutputProcess.IdsFil;
    dualFrqBrake.iqsFil = &OutputProcess.IqsFil;
    dualFrqBrake.fluxDSFil = &OutputProcess.FluxDSFil;
    dualFrqBrake.wsFil = &OutputProcess.WsFil;
#if DEBUG_P_DUAL_FRQ_BRAKE
    dualFrqBrake.regenBraking = &OutputProcess.RegenBrakingEnable;
    dualFrqBrake.fluxSource = &flux__Src;
    dualFrqBrake.braking = &OutputProcess.Braking;
#endif
}



//==============================================================================
//
// 永磁同步电机，SVC
//
//==============================================================================


//==============================================================================
//
// 永磁同步电机，SVC，参数预处理
//
//==============================================================================
// motorPara.smRs                  // 同步机定子电阻, CF-18
// motorPara.smLd                  // 同步机d轴电感, CF-19
// motorPara.smLq                  // 同步机q轴电感, CF-20
// motorPara.smCoeff               // 同步机反电动势系数，单位1V，F1-10
// corePgPara.elem.encoderAngle    // 编码器安装角，单位0.1度，F1-31
//中断中更新变量
//long gPm_Rs,gPm_Ld,gPm_Lq,gPm_Bemf,gPm_Speed_Lpf=100;
////extern f32 udcFil1;
////extern u16 hwCellFlag;     // 1-大样机，0-小样机(包括全功能小样机和非全功能小样机)
void pmsvc_param_in()
{
  {   
	  if(funcCode.code.ObVolSel == 2)
	  {
	     PmSvcData.csrvd =   sampleVoldObTmp * 4096.0; 
	     PmSvcData.csrvq =   sampleVolqObTmp * 4096.0;
	  }
	  else// if(funcCode.code.ObVolSel == 1)
	  {
	     PmSvcData.csrvd =  (f32)funcCode.code.SwObVolCoff * 0.01 * OutputProcess.VdsRef * 4096.0 * udcFil; 
	     PmSvcData.csrvq =  (f32)funcCode.code.SwObVolCoff * 0.01 * OutputProcess.VqsRef * 4096.0 * udcFil;
	  }
	  /*
	  else
	  {
	      if(fabs(CommandGenerator.SpeedReference * motorPara.iFPuOmegaOne) >= 0.18)
	      {
			 PmSvcData.csrvd =  sampleVoldObTmp * 4096.0; 
	     	 PmSvcData.csrvq =  sampleVolqObTmp * 4096.0;
		  }
		  else
		  {
	         PmSvcData.csrvd =  (f32)funcCode.code.SwObVolCoff * 0.01 * OutputProcess.VdsRef * 4096.0 * udcFil; 
	     	 PmSvcData.csrvq =  (f32)funcCode.code.SwObVolCoff * 0.01 * OutputProcess.VqsRef * 4096.0 * udcFil;
		  }
	  }
	  */
		PmSvcData.fdbid = (long)(OutputProcessIds * 4096L);
		PmSvcData.fdbiq = (long)(OutputProcessIqs * 4096L);
		//PmSvcData.fdbid =  (long)(idRef * 4096L);
		//PmSvcData.fdbiq =  (long)(iqRef * 4096L);
  	}
}
//2MS更新变量,运行中不能修改
int coef_bem_set = 50;//50;
int coef_beta_set = 20;//10;
void pmsvc_param1_in()
{	
    f32 gPm_Rs,gPm_Ld,gPm_Lq,gPm_Bemf;

	PmSvcData.pmsvc_control = 1;
	coef_bem_set = funcCode.code.PmsmCoefBemSet;
	if(coef_bem_set == 0)
	{
		coef_bem_set = 40;
	}
	if(coef_bem_set <= 10)
	{
		coef_bem_set = 10;
	}
	if(coef_bem_set >= 300)
	{
		coef_bem_set = 300;
	}
	if(PmSvcData.pmsvc_control == 0)
	{
		return;
	}
  // motorPara.smRs = 0.06;
//	motorPara.smLd = 0.14;
//	motorPara.smLq = 0.14;
//	motorPara.smCoeff = 0.94;
	if (motorPara.ratingVoltage * motorPara.ratingCurrent * motorPara.smRs * motorPara.smLd
		* motorPara.smLq * motorPara.smCoeff*motorPara.ratingFrq*motorPara.lPuOne == 0.0)
	{
	   motorPara.ratingVoltage = 1140.0;
	   motorPara.zPuOne = 18.0;
	   motorPara.ratingCurrent = 12.0;
	   motorPara.smRs = 0.03;
	   motorPara.smLd = 0.2;
	   motorPara.smLq = 0.2;
	   motorPara.smCoeff = 0.9;
	   OutputProcess.FastLoopFrequency = 1500;
	   motorPara.ratingFrq = 50.0;
	   motorPara.lPuOne = 0.2;
	}
    gPm_Rs   = motorPara.smRs * motorPara.zPuOne * 1000;    // 直流电阻，F1-16，mΩ
    gPm_Ld   = motorPara.smLd * motorPara.lPuOne * 1000000; // d轴电感, F1-17，uH
    gPm_Lq   = motorPara.smLq * motorPara.lPuOne * 1000000; // q轴电感, F1-18，1uH
    gPm_Bemf = motorPara.smCoeff * motorPara.ratingVoltage * (1000.0/SQRT3*SQRT2/(TWO_PI)) / motorPara.ratingFrq;
 
    
	PmSvcData.r = gPm_Rs;
	PmSvcData.ld = gPm_Ld;
//	PmSvcData.lq = gPm_Ld;
    PmSvcData.lq = gPm_Lq;
	PmSvcData.bemf = gPm_Bemf;//实际磁链，放大1000倍
	PmSvcData.motor_curr = motorPara.ratingCurrent * 10L;
	PmSvcData.motor_volt = motorPara.ratingVoltage;
	
//下列变量需要有功能码可以设置
	
	PmSvcData.low_speed_fcset = 20;
	PmSvcData.speed_lpf_k =  gPm_Speed_Lpf;
    if(PmSvcData.speed_lpf_k < 32)
    {
        PmSvcData.speed_lpf_k = 32;
    }
	PmSvcData.low_speed_idmax = 300;

	PmSvcData.coef_bem_set = coef_bem_set;
	PmSvcData.coef_beta_set = coef_beta_set;	
	PmSvcData.fcset = OutputProcess.FastLoopFrequency;
	

}

void FluxIMAddCalc(void)
{
    
	f32 spdPu;
	f32 idSetTmp;
	
	spdPu = fabs(CommandGenerator.SpeedReference * motorPara.iFPuOmegaOne);
	
	if(spdPu <= 0.05)
	{
		idSetTmp = motorPara.PMLowSpdIdAddCur;//可根据负载调节大小
	}
	else if(spdPu >= 0.15)//防止影响MTPA效果
	{
		idSetTmp = 0.01;
	}
	else
	{
		idSetTmp = motorPara.PMLowSpdIdAddCur - (motorPara.PMLowSpdIdAddCur - 0.01) / 0.1 *(spdPu - 0.1);	
	}				
	fluxAddref = idSetTmp;
    if(AUTO_TUNE_STATE == DriveControl.State)
    {
		fluxAddref = 0;
	}
	
}


void IdrefPmsmCalc(void)
{
    
	f32 spdPu;
	f32 idSetTmp;
	static f32 idSetTmp2;
	f32 idSetTmp1;
	static u16  idRefFlag = 0;
	
	spdPu = fabs(CommandGenerator.SpeedReference * motorPara.iFPuOmegaOne);
	
	if(spdPu <= 0.1)
	{
		idSetTmp = motorPara.PMLowSpdIdAddCur;//可根据负载调节大小
	}
	else if(spdPu >= 0.2)//防止影响MTPA效果
	{
		idSetTmp = 0.1;
		//idSetTmp = 0.0;
	}
	else
	{
		idSetTmp = motorPara.PMLowSpdIdAddCur - (motorPara.PMLowSpdIdAddCur - 0.1) / 0.1 *(spdPu - 0.1);	
		//idSetTmp = motorPara.iNoload - motorPara.iNoload / 0.1 *(spdPu - 0.1);
	}	

	if(IFmodelFlga == 1)//每次执行IF模式，需要过渡一次
	{
		idRefFlag = 0;
	}

	
	if((funcCode.code.IfOrVectorSwitchFreq != 0)&&(AUTO_TUNE_STATE != DriveControl.State) && (idRefFlag == 0))
	{	    
		if(IFmodelFlga == 0)
		{
			if(idRef > (idSetTmp + 0.01))
			{	
				idRef = idRef - 0.001;
			}			
			if(idRef < (idSetTmp - 0.001))
			{
			   idRef = idRef + 0.01;
			}

			if(idRef < 0.1)//IF切矢量，d轴电流过渡完成
			{
				idRefFlag = 1;
			}
		}
	}
	else
	{
		idRef = idSetTmp;
	}
	
}

/******************************
同步机MTPA控制
*******************************/
void PmsmMtpaCalc(void)
{
	f32 Temp;
	f32 Temp1;
	f32 Is;
	f32 Ld;
	f32 Lq;
	f32 bemf;
	f32 spdPu;

	spdPu = fabs(CommandGenerator.SpeedReference * motorPara.iFPuOmegaOne);
	
	if((AUTO_TUNE_STATE == DriveControl.State) ||
		(IFmodelFlga == 1) || 
		(OutputProcess.Enable == 0) ||
		(spdPu <= 0.2) ||	//低速不执行MTPA，防止角度没收敛导致过流
		(funcCode.code.PmsmMtpaCtlEn == 0))//默认不开启MTPA，防止飞车启动过流
	{
		PmsmMtpa.id = 0;
		PmsmMtpa.iq = 0;
		return;
	}

	PmsmMtpa.Is = iqRef * motorPara.ratingCurrent * SQRT2;//实际电流幅值
	PmsmMtpa.Ld = (f32)PmSvcData.ld;//实际电感，uH
	PmsmMtpa.Lq = (f32)PmSvcData.lq;//实际电感，uH
	PmsmMtpa.bemf = (f32)PmSvcData.bemf;//实际磁链，0.001 WB
	Is = iqRef * motorPara.ratingCurrent * SQRT2;
	Ld = PmsmMtpa.Ld / 1000.0;
	Lq = PmsmMtpa.Lq / 1000.0;
	bemf = PmsmMtpa.bemf;
	/*
	if(fabs(iqRef) >= 0.01)
	{

	Temp = sqrt(bemf * bemf + 8.0 * (Ld - Lq) * (Ld - Lq) * Is * Is);
	PmsmMtpa_Test1 = Temp;
	Temp1 = 4.0 * (Ld - Lq) * Is;
	PmsmMtpa_Test2 = Temp1;
	
	PmsmMtpa.cosbeta = (Temp - bemf)/Temp1;

	PmsmMtpa.sinbeta = sqrt(1.0 - PmsmMtpa.cosbeta * PmsmMtpa.cosbeta);

	PmsmMtpa.id = iqRef * PmsmMtpa.cosbeta;
	PmsmMtpa.iq = iqRef * PmsmMtpa.sinbeta;

	iqRef = PmsmMtpa.iq;
	}
	*/
	
	Temp = sqrt(bemf * bemf + 8.0 * (Ld - Lq) * (Ld - Lq) * Is * Is);
	//PmsmMtpa_Test1 = Temp;
	Temp1 = 4.0 * (Ld - Lq);
	//PmsmMtpa_Test2 = Temp1;

	PmsmMtpa.id = (Temp - bemf)/Temp1;
	PmsmMtpa.iq = sqrt(iqRef*iqRef - PmsmMtpa.id*PmsmMtpa.id);
	if(iqRef >= 0.0)
	{
		iqRef = PmsmMtpa.iq;
	}
	else
	{
		iqRef = -PmsmMtpa.iq;
	}
	
}

//f32 deltTheta;
void DqTo2ndTheta(void)
{
    f32 deltTheta;
	struct PARK_STR           park_data;
//	struct PARK_INVERSION_STR park_inr_data;

	f32 secondTheta,tmpTheta;
//	f32 deltTheta;

	tmpTheta = OutputProcess.DeltaS;//当前角度

    if(PMSM_SVC == motorControlMode)
    {
		secondTheta = DeltaPmsmSvc;
	}
    if((IM_SVC1 == motorControlMode)||(IM_SVC2 == motorControlMode))
    {
		secondTheta = deltaSPLL;
	}	
	//if(IM_SVC3 == motorControlMode)//SCV3其实不支持IF切矢量
	//{
	//	secondTheta = DeltaImSvc3;
	//}
	if(IM_SVC4 == motorControlMode)
	{
		secondTheta = DeltaImSvc4;
	}
		
    deltTheta = secondTheta - tmpTheta;
	Modulo2PI(&deltTheta);
	
	park_data.alpha = OutputProcess.VdsRef;
	park_data.beta = OutputProcess.VqsRef;
	park_data.angle = deltTheta;
	ParkCalc(&park_data);
    DqTo2ndVdCal = park_data.d;
	DqTo2ndVqCal = park_data.q;

/*
	park_data.alpha = AlphaOutputVol;
	park_data.beta = BetaOutputVol;
	park_data.angle = secondTheta;
	ParkCalc(&park_data);
    DqTo2ndVdSamp = park_data.d;
	DqTo2ndVqSamp = park_data.q;
*/
	park_data.alpha = iAlphaS;
	park_data.beta = iBetaS;
	park_data.angle = secondTheta;
	ParkCalc(&park_data);
    DqTo2ndid = park_data.d;
	DqTo2ndiq = park_data.q;
}

void DqTo2ndStateControl(void)
{
   if((IFmodelFlga == 0)&&(IFmodelFlgaOld == 1)&&(AUTO_TUNE_STATE != DriveControl.State))
   {
        OutputProcess.IdsRef = DqTo2ndid;
		OutputProcess.IqsRef = DqTo2ndiq;
		OutputProcess.Ids = DqTo2ndid;
		OutputProcess.Iqs = DqTo2ndiq;
		idRef = DqTo2ndid;
		iqRef = DqTo2ndiq;
		idFdb = DqTo2ndid;
		iqFdb = DqTo2ndiq;
		OutputProcess.VdsRef = DqTo2ndVdCal;
		OutputProcess.VqsRef = DqTo2ndVqCal;
		idRegulatorParams.accumulator = DqTo2ndVdCal;
		iqRegulatorParams.accumulator = DqTo2ndVqCal;
   }

}


void Calzaibo(void);

f32 fpgazaibo;

//extern f32 fpgazaibo;
//extern f32 newCarrierFrq;
void Calzaiboint(void)
{
	 coreCarrierFrqAct = newCarrierFrq;
	 fpgazaibo = 120.0  * 1000000 /coreCarrierFrqAct;
	 interfaceRam[FPGA_REG_CARRIERH] = ((s32)fpgazaibo)>> 16;
	 interfaceRam[FPGA_REG_CARRIERl] = ((s32)fpgazaibo)& 0x0000FFFF;
	 interfaceRam[FPGA_REG_CARRIERINT] = 1;
}

void Calzaibo(void)
{
	 coreCarrierFrqAct = newCarrierFrq;
	 coreCarrierFrq = coreCarrierFrqAct * 10.0;
     fpgazaibo = 120.0  * 1000000 /coreCarrierFrqAct;

	 interfaceRam[FPGA_REG_CARRIERH] = ((s32)fpgazaibo)>> 16;
	 interfaceRam[FPGA_REG_CARRIERl] = ((s32)fpgazaibo)& 0x0000FFFF;
	
}


//==============================================================================
//
// uvw输入电流
// 
// 
// 调用周期: 快环中断
//
//==============================================================================
f32 iuDisFil; //u相输出电流显示
f32 ivDisFil; //v相输出电流显示
f32 iwDisFil; //w相输出电流显示

f32 iuDisFilTmp; //u相输出电流显示
f32 ivDisFilTmp; //v相输出电流显示
f32 iwDisFilTmp; //w相输出电流显示


u16 CalTimesReal = 0;
f32 iuSum = 0.0;
f32 ivSum = 0.0;
f32 iwSum = 0.0;

u16 CalTimes = 0;
f32 iuDis = 0; //u相输出电流显示
f32 ivDis = 0; //v相输出电流显示
f32 iwDis = 0; //w相输出电流显示

f32 AveragePower;

f32 PowerAdjustCoff;
f32 IqsFilPower,FrequencyPower;

f32 IdsFilPower,IqsFilPower,CurrentPhase,VoltPhase,PowerPhase,PowerPhaseFilter;
f32 Volt,VoltFilter,CurPer,CurPerFilter,SinPower,CosPower;

f32 powertest = 1.0;

void uvwOutCurrentCalc(void)
{
	//u16 CalTimes;
	//static u16 CalTimesReal = 0;
	//f32 iuDis; //u相输出电流显示
	//f32 ivDis; //v相输出电流显示
	//f32 iwDis; //w相输出电流显示
	
	//static f32 iuSum = 0.0;
	//static f32 ivSum = 0.0;
	//static f32 iwSum = 0.0;
	//f32 AveragePower;
	
	if((((fabs(pllBackEmfFrq)) <= TWO_PI) && (cellMenu.cellVoltage != 3)) || 
		(!coreRunStatus.bit.run) //停机
		)
	{
		iuDisFil = 0;
		ivDisFil = 0;
		iwDisFil = 0;

		iuDisFilTmp = 0;
		ivDisFilTmp = 0;
		iwDisFilTmp = 0;

		OutputProcess.AveragePower = 0.0;
	}
	else
	{
		if(CalTimesReal == 0)//防止计算点数一直变
		{
			if(cellMenu.cellVoltage != 3)
			{
				CalTimes = (u16)(5.0*OutputProcess.FastLoopFrequency * TWO_PI / (fabs(pllBackEmfFrq)));
			}
			else
			{
				CalTimes = (u16)(5.0*OutputProcess.FastLoopFrequency / (fabs(inputFrq1)));
			}
		}
		
		if(CalTimesReal < CalTimes)
		{
			CalTimesReal++;
			iuSum = iuSum + outCurData.u * outCurData.u;
			ivSum = ivSum + outCurData.v * outCurData.v;
			iwSum = iwSum + outCurData.w * outCurData.w;
		}
		else
		{
			iuDis = SQRT2 * sqrt(iuSum / (f32)CalTimes);//电流标幺的是电机额定电流峰值，所以要乘上根号2
			ivDis = SQRT2 * sqrt(ivSum / (f32)CalTimes);
			iwDis = SQRT2 * sqrt(iwSum / (f32)CalTimes);

			CalTimesReal = 0;
			iuSum = 0.0;
			ivSum = 0.0;
			iwSum = 0.0;
		}

		iuDisFilTmp = LPF_T(iuDis, iuDisFilTmp, 0.05, OutputProcess.FastLoopSamplePeriod);
		ivDisFilTmp = LPF_T(ivDis, ivDisFilTmp, 0.05, OutputProcess.FastLoopSamplePeriod);
		iwDisFilTmp = LPF_T(iwDis, iwDisFilTmp, 0.05, OutputProcess.FastLoopSamplePeriod);
		
		if(((iuDisFilTmp+ivDisFilTmp+iwDisFilTmp)/3.0) <= 0.01 ) //VF不接电机电流清零
		{
			iuDisFil = 0.0;
			ivDisFil = 0.0;
			iwDisFil = 0.0;
		}
		else
		{
			iuDisFil = iuDisFilTmp;
			ivDisFil = ivDisFilTmp;
			iwDisFil = iwDisFilTmp;	
		}
	}

	if(funcCode.code.DispOutPowerAdjustCoff == 0)
	{
		PowerAdjustCoff = 1.0;
	}
	else
	{
		PowerAdjustCoff = (f32)funcCode.code.DispOutPowerAdjustCoff * 0.01;
	}
	
	if((PMSM_FVC == motorControlMode)||(PMSM_SVC == motorControlMode))
	{
		//AveragePower = fabs(10.0 * (outCurData.u * outVolData.u + outCurData.v * outVolData.v + outCurData.w * outVolData.w) / 3.0);
		
		//AveragePower = fabs(PowerAdjustCoff * SQRT3 * 0.5 * (outCurData.u * vaRef_ + outCurData.v * vbRef_ + outCurData.w * vcRef_));
		
		//AveragePower = fabs(PowerAdjustCoff * 10.0 * SQRT3 * 0.5 *(AlphaOutputVol * iAlphaS + BetaOutputVol * iBetaS));

		AveragePower = PowerAdjustCoff * 10.0 * SQRT3 * 0.5 *(AlphaOutputVol * iAlphaS + BetaOutputVol * iBetaS);

		OutputProcess.AveragePower = LPF_T(AveragePower, OutputProcess.AveragePower, 50, 1000.0 * OutputProcess.FastLoopSamplePeriod);
	}
	else if((IM_SVC1  == motorControlMode)||
			(IM_FVC  == motorControlMode) ||
			(IM_SVC2  == motorControlMode)||
			(IM_SVC3  == motorControlMode)||
			(IM_SVC4  == motorControlMode))
	{
		/*
		IqsFilPower = LPF_T(OutputProcess.IqsFil, IqsFilPower, 10000.0, 1000.0 * OutputProcess.FastLoopSamplePeriod);
		FrequencyPower = LPF_T(OutputProcess.Frequency, FrequencyPower, 1000.0, 1000.0 * OutputProcess.FastLoopSamplePeriod);
		AveragePower = fabs(PowerAdjustCoff * (IqsFilPower * (FrequencyPower / (TWO_PI * motorPara.ratingFrq)))*motorPara.ratingPower)*10.0*1.04;
		OutputProcess.AveragePower = LPF_T(AveragePower, OutputProcess.AveragePower, 500, 1000.0 * OutputProcess.FastLoopSamplePeriod);
		*/
		IqsFilPower = LPF_T(OutputProcess.IqsFil, IqsFilPower, 100, 1000.0 * OutputProcess.FastLoopSamplePeriod);
		IdsFilPower = LPF_T(OutputProcess.IdsFil, IdsFilPower, 100, 1000.0 * OutputProcess.FastLoopSamplePeriod);
		if(fabs(IdsFilPower) < 0.000001)
		{	
			IdsFilPower = 0.000001;
		}
		CurrentPhase = atan(IqsFilPower/IdsFilPower);
		if(IdsFilPower < 0.0)
		{
			CurrentPhase = CurrentPhase + ONE_PI;
			//Modulo2PI(&CurrentPhase);
		}
		if(fabs(vds) < 0.000001)
		{	
			vds = 0.000001;
		}
		VoltPhase = atan(vqs/vds);
		if(vds < 0.0)
		{
			VoltPhase = VoltPhase + ONE_PI;
		}

		PowerPhase = VoltPhase - CurrentPhase;
		Modulo2PI(&PowerPhase);

		PowerPhaseFilter = LPF_T(PowerPhase, PowerPhaseFilter, 1000.0, 1000.0 * OutputProcess.FastLoopSamplePeriod);
		Volt = SqrtA2AddB2(vqs,vds);
		VoltFilter = LPF_T(Volt, VoltFilter, 1000.0, 1000.0 * OutputProcess.FastLoopSamplePeriod);
		CurPerFilter = SqrtA2AddB2(IqsFilPower,IdsFilPower);
		sincos(PowerPhaseFilter,&SinPower,&CosPower);
		AveragePower = PowerAdjustCoff * motorPara.ratingVoltage * motorPara.ratingCurrent *
			SQRT3 * VoltFilter * CurPerFilter * CosPower / 100.0;//单位：0.1kw
		
		OutputProcess.AveragePower = LPF_T(AveragePower, OutputProcess.AveragePower, 50, 1000.0 * OutputProcess.FastLoopSamplePeriod);
		
	}
	else
	{
		OutputProcess.AveragePower = 0.0;
	}
}


void NotchFilter(struct NOTCHFILTER_STR *p)
{	
	f32 a,b,c,d,e,f;
	
	p->Ts = OutputProcess.FastLoopSamplePeriod;
	
	//4+K*B*2*ts+Wo^2*ts^2
	a = 4.0 + p->NotchDepth*p->NotchWidth*2.0*p->Ts + p->NotchFreq*p->NotchFreq*p->Ts*p->Ts;
	//Wo^2*ts^2*2-8
	b = p->NotchFreq*p->NotchFreq*p->Ts*p->Ts*2 - 8.0;
	//4-K*B*2*ts+Wo^2*ts^2
	c = 4.0 - p->NotchDepth*p->NotchWidth*2.0*p->Ts + p->NotchFreq*p->NotchFreq*p->Ts*p->Ts;
	//1/(4+B*2*ts+Wo^2*ts^2)
	d = 1.0/(4.0 + p->NotchWidth*2.0*p->Ts + p->NotchFreq*p->NotchFreq*p->Ts*p->Ts);
	//Wo^2*ts^2*2-8
	e = p->NotchFreq*p->NotchFreq*p->Ts*p->Ts*2.0 - 8.0;
	//4-B*2*ts+Wo^2*ts^2
	f = 4.0 - p->NotchWidth*2.0*p->Ts + p->NotchFreq*p->NotchFreq*p->Ts*p->Ts;

	p->output = p->input * a * d + 
				p->last1input * b * d +
				p->last2input * c * d -
				p->last1output * e * d -
				p->last2output * f * d;

	p->last2input = p->last1input;
	p->last1input = p->input;
	p->last2output = p->last1output;
	p->last1output = p->output;
}


