//==================================================================================================
//
// 飞车启动
//
//
//
//
//==================================================================================================


#include "m_spinningLoad.h"
#include "m_main.h"
#include "m_modInterpUpdate.h"
#include "m_frqSrc.h"
#include "m_peakReduction.h"
#include "m_deadbandComp.h"
#include "m_fluxStatorObserve.h"
#include "m_interfacePublic.h"
#include "m_pll.h"
#include "m_interfaceModify.h"

#include "pmsvc.h"
#include "main.h"


//#pragma CODE_SECTION(SpinningLoadControl   ,     "ramfuncs");
//#pragma DATA_SECTION(SpinningLoad, "data_ram");

struct SPINNING_LOAD_TYPE SpinningLoad;
struct FAST_SPINNING_LOAD_TYPE FastSpinningLoad;

extern Uint16 cfGroup[F2C_DEBUG_PARA_LEN];

extern u16 speedLoopSpinEnable;     // 仅飞车启动扫频期间不使能速度环
extern f32 pllBackEmfFrq;
extern f32 biasGain;
extern struct PiDataType BackEMFPllParams;
extern struct PiDataType OutputProcessPllParams;
extern f32 fluxAlphaS, fluxBetaS;
extern struct PHASE_LOCK_LOOP_STR pllDataS;
extern struct FLUX_STATOR_OBSERVE_STR fluxSData;
extern struct PiDataType iqRegulatorParams;

extern f32 DeltaImSvc4;
extern f32 ImSvc4FluxRFrq;


extern void UpdateFpgaVoltageData(void);

f32 iqRegSpinningLoad;  // 飞车启动完成uq积分初始值
f32 idRegSpinningLoad;

void FpgaVoltageDataSpinUpdate(void);

void SpinningLoadSlowDeal(void);

#if DEBUG_P_SPINNING_LOAD
u16 spinLoadStatus;     // 0-表示第一次进入 SpinningLoadState() 函数
f32 SpeedReferenceCore2Fun;
//==============================================================================
//
// 飞车启动状态处理
// 性能主循环调用
//
//==============================================================================
void SpinningLoadState(void)
{
    u16 tmp = 1;
    f32 coef;
    
    if (0 == spinLoadStatus)
    {
        spinLoadStatus = 1;  // 已经进入了 SpinningLoadState() 函数

        speedLoopSpinEnable = 0;
        
        
        if ((PLL_FREQUENCY_VALID == SpinningLoad.Status) || // Is the PLL valid or likely to become valid?
            (SM_SVC == OutputProcess.ControlAlgorithm)  ||
            (SM_FVC == OutputProcess.ControlAlgorithm) ||
            (IM_FVC == OutputProcess.ControlAlgorithm)    // CLVC，有编码器
           )
        {
            // If closed loop system use encoder speed to seed drive speed
            if ((IM_FVC == OutputProcess.ControlAlgorithm) || (SM_FVC == OutputProcess.ControlAlgorithm))
            {
                OutputProcess.Frequency = OutputProcess.EncoderSpeed;   // 使用编码器反馈速度
            }
            
#if 1//DEBUG_P_SM_CONTROL
            if (((SM_SVC == OutputProcess.ControlAlgorithm) || (SM_FVC == OutputProcess.ControlAlgorithm))
                && (PLL_FREQUENCY_VALID != SpinningLoad.Status)
               )
            {
                OutputProcess.SMFieldEnable = false;
                tmp = 0;
                
//                coreStatus.bit.forbidAccDecSpd = 1;

                SpinningLoad.SpeedReference = pllBackEmfFrq;
            }
            else//有剩磁，直接进预励磁状态
#endif
            {
                SpinningLoad.UseSpeedReference = TRUE;
#if 1
                SpinningLoad.SpeedReference = OutputProcess.Frequency;
#elif 1
                SpinningLoad.SpeedReference = pllBackEmfFrq;
#endif
                SpinningLoad.PresetTorqueCurrentRegulator = TRUE;
                SpinningLoad.PresetMagnetizingCurrentRegulator = TRUE;
                if (!smControl)
                {
                    FastSpinningLoad.UseFluxFdbFastSpinningLoad = TRUE;
                }
            }
                coef = 1.0;

            // 系数0.5加入，可解决单元旁路状态下的停机立即飞车启动有电流冲击问题，20160620
            iqRegSpinningLoad = OutputProcess.VqsRef 
                + coef * OutputProcess.FluxDS * OutputProcess.Frequency * OutputProcess.iRatedFrequency;
			idRegSpinningLoad = OutputProcess.VdsRef;
            SpinningLoad.UseFluxReference = TRUE;
            SpinningLoad.FluxReference = fabs(OutputProcess.FluxDSFil);
            DriveControl.State = MAGNETIZING_STATE;     // 直接进入励磁状态
            pllDataS.pllParams = &OutputProcessPllParams;
            fluxSData.pOutPllPi = &OutputProcessPllParams;            
            speedLoopSpinEnable = 1;   
//            CommandGenerator.SpeedReference = SpinningLoad.SpeedReference;
            SpeedReferenceCore2Fun = SpinningLoad.SpeedReference;
        }
        // PLL not valid, go to scan mode
    } 
    else    // 正在扫描
    {
        SpeedReferenceCore2Fun = SpinningLoad.SpeedReference;
//		DriveControl.State = MAGNETIZING_STATE;
        
        if (SPINNING_LOAD_DONE == SpinningLoad.Status)//扫频完成，进入预励磁状态
        {
            // 在 SpinningLoadControl() 中处理了
            DriveControl.State = MAGNETIZING_STATE;
            speedLoopSpinEnable = 1;              
//            if (TRUE == SpinningLoad.UseSpeedReference)
//            {
//                OutputProcess.Frequency = OutputProcessPllParams.accumulator = SpinningLoad.SpeedReference;
//            }
        }
        // Has there been an error?
        //else if ((SPINNING_LOAD_CURRENT_ERROR == SpinningLoad.Status) ||
        //         (SPINNING_LOAD_SCAN_ERROR == SpinningLoad.Status)
        //        ) 
        else if (SPINNING_LOAD_CURRENT_ERROR == SpinningLoad.Status)
        {
#if 0
            SpinningLoad.Status = SPINNING_LOAD_DONE;
            DriveControl.State = IDLE_STATE;
#elif 1
            if (!coreErrorCode)
            {
                coreErrorCode = 130;     // 原96为环流没合电抗器故障
            }                
#endif
        }
    } 

    if (tmp)
    {
        coreRunStatus.bit.run = 1;
        OutputProcess.Enable = true;
    }
}




//#define OUT_PLL_KP_SPIN  1000.0  //1000.0
//#define OUT_PLL_KI_SPIN  150.0   // 100.0过小观测的同步频率起不来
f32 OUT_PLL_KP_SPIN = 10000.0;
f32 OUT_PLL_KI_SPIN = 1000.0;    // 小了快速飞车启动不起来，暂时先用全局变量
struct PiDataType OutputProcessPllParamsSpinningLoad =
    {50 * 2 * TWO_PI,   -50 * 2 * TWO_PI,   8000.0,      400.0};   // PLL的PID增强  
struct PiDataType magCurrentRegParams    = {0.8, -0.8, 0.100};
struct PiDataType torqueCurrentRegParams = {1.2, -1.2, 0.100};
//extern struct PHASE_LOCK_LOOP_STR pllDataS;
extern f32 iAlphaS, iBetaS;             // local stator current (alpha and beta)
extern f32 yAlphaS, yBetaS;             // local volt-sec measurement alpha & beta
extern f32 outputProcessFrqSum;
extern u16 outputProcessFrqTicker;

extern f32 fluxAlphaSDC, fluxBetaSDC;
extern f32 pllFluxSFrq;
f32 deltaSpin;
f32 fluxSS, fluxSSaaa;
f32 fluxDS1, fluxQS1;
//f32 deltaSPLLSpin;
extern f32 deltaSPLL;
extern f32 pllFluxSFrqFil;
extern f32 fluxFdbFil;
//#define SPINNINGLOAD_MIN_FRQ_HZ  5.0    // 扫频最低频率
f32 SPINNINGLOAD_MIN_FRQ_HZ = 5.0;
f32 FAST_SPINNINGLOAD_MIN_FRQ_HZ = 3.0;

extern f32 lcLPu;
f32 coreFrqAimHzOld;
f32 sdafa = 0.03;
extern f32 pwmT;
extern f32 coreMaxFrqRads;
extern f32 vaLastUpdate, vbLastUpdate, vcLastUpdate;    // 暂时使用全局变量，HD33使用。
//extern struct FLUX_STATOR_OBSERVE_STR fluxSData;
extern void ModInterpUpdateA(void);
u16 spinloadCurentRampTest;
f32 sinThetaSinload, cosThetaSinload;
extern   f32 vaRef_,vbRef_,vcRef_;              // peak reduction之前的电压指令
//==============================================================================
//
// 飞车启动控制
// 快环调用
//
//==============================================================================
void SpinningLoadControl(void)
{
//    static struct PiDataType magCurrentRegParams;
//    static struct PiDataType torqueCurrentRegParams;
//    static f32 deltaSpin;
    f32 minimumScanSpeed;
    f32 spinningLoadThresholdScaler;
    f32 fluxDS, fluxQS;      // flux (D & Q) 
    f32 vds, vqs;
//--------------------------------------------------------------------
   // f32 vaRef_,              // peak reduction之前的电压指令
    //    vbRef_,
   //     vcRef_;
    f32 vaRef,               // 死区补偿之后的电压指令
        vbRef,
        vcRef;
    f32 deltaMidPt;          // interpolator midpoint angle
    f32 uaRef, ubRef, ucRef; // peak reduction之后的电压指令
    f32 uaRefPrime, ubRefPrime, ucRefPrime;
    static f32 vaRefPrime, vbRefPrime, vcRefPrime;
    f32 vaRefPrime1, vbRefPrime1, vcRefPrime1;

    f32 vaRefStep, vbRefStep, vcRefStep;
    f32 vaRefStepPrime, vbRefStepPrime, vcRefStepPrime;
//    f32 vaLastUpdate, vbLastUpdate, vcLastUpdate;
//--------------------------------------------------------------------

    struct PEAK_REDUCTION_STR peakReductionData;
   // struct DEADBAND_COMP_STR deadbandCompData;

    f32 frqDelta;
    f32 tmp;
    f32 tmp1;

    static u16 curLoopWrongFlag;

    static u16 fastSpinningLoadTicker;
    u16 fastSpinningLoadLowFrqFlag = 0;
    
    if (PLL_FREQUENCY_NOT_VALID == SpinningLoad.Status)
    {   // 进行初始化
        magCurrentRegParams.propGain        = currentLoopMenu.currentRegProp;
        magCurrentRegParams.integGain       = OutputProcess.CurrentRegInteg;
        torqueCurrentRegParams.propGain     = currentLoopMenu.currentRegProp;
        torqueCurrentRegParams.integGain    = OutputProcess.CurrentRegInteg;
        magCurrentRegParams.accumulator     = 0.0;
        torqueCurrentRegParams.accumulator  = 0.0;
        magCurrentRegParams.lastInput       = 0.0;
        torqueCurrentRegParams.lastInput    = 0.0;
        deltaSpin = 0.0;
        deltaSPLL = 0.0;
        SpinningLoad.Mode = spinningLoadMenu.mode;

        OutputProcess.Frequency = 0.0;
//        pllDataS.pllParams = &OutputProcessPllParamsSpinningLoad;     // PI参数太强，影响了启动
        pllDataS.pllParams = &OutputProcessPllParams;
        pllDataS.enable = TRUE;
        pllDataS.sampleRate = OutputProcess.FastLoopSamplePeriod;
        pllDataS.seed   = 0.0;  
/*
// fastSpinningLoad 初始化
        if (TRUE == motorControlOtherEnable.bit.fastSpinningLoad)
        {
            OutputProcessPllParamsSpinningLoad.accumulator = 0.0;// 1.1 * coreMaxFrqRads;   // 使用停机前的频率和0可能导致快速飞车启动不起来，单位rad/s，改最大频率实验
            
            OutputProcessPllParamsSpinningLoad.propGain = OUT_PLL_KP_SPIN;
            OutputProcessPllParamsSpinningLoad.integGain = OUT_PLL_KI_SPIN;

            OutputProcess.Frequency = OutputProcessPllParamsSpinningLoad.accumulator;
            pllDataS.pllParams = &OutputProcessPllParamsSpinningLoad;
            coreFrqAimHzOld = coreFrqAimHz;
        }
        */
        // 搜索频率赋初值
        if (FALSE == motorControlOtherEnable.bit.fastSpinningLoad)
        {
            SpinningLoad.SpeedReference = 1.05 * coreMaxFrqRads ;//* ((f32)cfGroup[22]/100.0);// 1.05倍最大频率开始扫频
            if (NEGATIVE == SpinningLoad.Mode)
            {
                SpinningLoad.SpeedReference = -SpinningLoad.SpeedReference;
            }           
        }

        
        OutputProcess.IqsRef                = 0.0;
        OutputProcess.IdsRef                = 0.0;
        SpinningLoad.UseSpeedReference      = FALSE;
        SpinningLoad.UseFluxReference       = FALSE;
        SpinningLoad.PresetTorqueCurrentRegulator = FALSE;
        SpinningLoad.PresetMagnetizingCurrentRegulator = FALSE;
        FastSpinningLoad.UseFluxFdbFastSpinningLoad = FALSE;
        SpinningLoad.Status                 = SPINNING_LOAD_CURRENT_RAMP_UP;
		
//        spinningLoadThresholdScaler         = 1.0;
    }
    else
    {
        // 定子磁链观测
        {
//            struct FLUX_STATOR_OBSERVE_STR fluxSData;
//            extern struct FLUX_STATOR_OBSERVE_STR fluxSData;

            fluxSData.yalpha = yAlphaS;
            fluxSData.ybeta = yBetaS;
            fluxSData.ialpha = iAlphaS;
            fluxSData.ibeta = iBetaS;
            fluxSData.wHw = fluxStatorObserverMenu.lowFrqWo;
            fluxSData.rs = OutputProcess.StatorResistance * OutputProcess.RatedFrequency;
            fluxSData.softwareCompPole = fluxStatorObserverMenu.swCompensatorPole;
            fluxSData.lowFrqComGain = fluxStatorObserverMenu.lowFrqComGain;
            fluxSData.samplePeriod = OutputProcess.FastLoopSamplePeriod;
            fluxSData.spinStatusIsPllNotValid = (PLL_FREQUENCY_NOT_VALID == SpinningLoad.Status);
            fluxSData.spinningLoadEnable = TRUE;
            fluxSData.isSpin = 0;
            fluxSData.pOutPllPi = pllDataS.pllParams;
            fluxSData.speedReference = TWO_PI * 50;
            fluxSData.ls = motorPara.ls;
            fluxSData.enable = OutputProcess.Enable;
            FluxStatorObserve(&fluxSData);
            fluxAlphaS = fluxSData.falpha;
            fluxBetaS = fluxSData.fbeta;

            fluxSS = sqrt(fluxAlphaS * fluxAlphaS + fluxBetaS * fluxBetaS);
        }
        ParkCalcMacro(fluxAlphaS - fluxAlphaSDC, fluxBetaS - fluxBetaSDC, 
            deltaSPLL, fluxDS1, fluxQS1);   // 76clk            


        // 输出滤波器的处理
        FluxStatorObserveLC();
        
// 同步频率计算
        // 大于一定值时，才这样计算。
        //if ((GetA2AddB2(yAlphaS, yBetaS) >= 0.005 * 0.005) &&
         //   (SPINNING_LOAD_CURRENT_RAMP_UP != SpinningLoad.Status)
           // )  
        if (GetA2AddB2(yAlphaS, yBetaS) >= 0.005 * 0.005)//快速飞车启动用的
        {
            pllDataS.input = fluxQS1;
            pllDataS.angle = deltaSPLL;
            PhaseLockLoop(&pllDataS);
            pllFluxSFrq = pllDataS.frequency;
            deltaSPLL = pllDataS.angle;
        }
        else
        {
            pllFluxSFrq = 0;

#if 0   // 快速飞车启动，电流斜坡过程不进行PLL            
            if (TRUE == motorControlOtherEnable.bit.fastSpinningLoad) 
            {
                OutputProcessPllParamsSpinningLoad.accumulator = 0.0; 
                SpinningLoad.SpeedReference = 0.0;
            }
#endif            
        }

    // 显示用
        pllFluxSFrqFil = LPF_K(pllFluxSFrq, pllFluxSFrqFil, 4);
        fluxFdbFil = LPF_K(fluxDS1, fluxFdbFil, 4);
        
        if (TRUE == motorControlOtherEnable.bit.fastSpinningLoad)     
        {
            deltaSpin = deltaSPLL;
            SpinningLoad.SpeedReference = pllFluxSFrq;  // 观测过程同步频率赋值
        }
        else
        {
            deltaSpin += SpinningLoad.SpeedReference * OutputProcess.FastLoopSamplePeriod;
            Modulo2PI(&deltaSpin);
        }

        {
            struct PARK_STR parkData;

            parkData.alpha = iAlphaS;
            parkData.beta  = iBetaS;
            parkData.angle = deltaSpin;
            ParkCalc(&parkData);
            OutputProcess.Ids = parkData.d;
            OutputProcess.Iqs = parkData.q;
        }

        {
            struct REGULATOR_STR regulatorData;
            extern f32 idRegError;
            extern f32 iqRegError;
          //  static u16 ticker;

            idRegError = OutputProcess.IdsRef - OutputProcess.Ids;
            regulatorData.input = idRegError;

            // 飞车启动电流正常闭环判断
#if 0
            if (fabs(idRegError) > 0.8 * OutputProcess.IdsRef)
            {
                ticker++;
                if (500 == ticker)
                {
                    ticker = 0;
                    curLoopWrongFlag = TRUE;
                }
            }
            else
            {
                ticker = 0;
                curLoopWrongFlag = FALSE;
            }
#endif
            
            regulatorData.pi = &magCurrentRegParams;
            regulatorData.enable = TRUE;
            RegulatorCalc(&regulatorData);
            OutputProcess.VdsRef = vds = regulatorData.out;

            iqRegError = OutputProcess.IqsRef - OutputProcess.Iqs;
            regulatorData.input = iqRegError;
            regulatorData.pi = &torqueCurrentRegParams;
            regulatorData.enable = TRUE;
            RegulatorCalc(&regulatorData);
            OutputProcess.VqsRef = vqs = regulatorData.out; 
        }

//        tmp = 1.0 / (fabs(SpinningLoad.SpeedReference * OutputProcess.iRatedFrequency) + 0.1);
        tmp = fabs(SpinningLoad.SpeedReference * OutputProcess.iRatedFrequency) + 0.05;
        tmp = GetMax(tmp, 0.1);
        tmp = 1.0 / tmp;

// 测试任务编号A13110715，ID2
// 处理单元旁路状态扫描不到频率的问题
//        tmp1 = OutputProcess.PeakVoltageClampLimit / OutputProcess.MotorVoltageClampLimit;
        tmp1 = (2.0/SQRT3) / OutputProcess.MotorVoltageClampLimit;
        
        fluxQS = (OutputProcess.StatorResistance * OutputProcess.Ids - vds * tmp1) * tmp;
        fluxDS = fabs(vqs) * tmp1 * tmp - OutputProcess.Ids * lcLPu;
//        fluxDS = fabs(vqs) * tmp - OutputProcess.Ids * lcLPu;
        fluxSSaaa = fabs(vqs) * tmp - OutputProcess.Ids * lcLPu;

//        fluxDS = sqrt(yAlphaS * yAlphaS + yBetaS * yBetaS); // 2014-04-14 caizhun

        if (TRUE == motorControlOtherEnable.bit.fastSpinningLoad) 
        {
            OutputProcess.FluxDS = LPF_Gain(fluxDS1, OutputProcess.FluxDS, 0.75);
            OutputProcess.FluxQS = LPF_Gain(fluxQS1, OutputProcess.FluxQS, 0.75);
        }
        else
        {
            OutputProcess.FluxDS = LPF_Gain(fluxDS, OutputProcess.FluxDS, 0.75);  // 1/(1-0.75)=4
            OutputProcess.FluxQS = LPF_Gain(fluxQS, OutputProcess.FluxQS, 0.75);      
        }
//------------------------------------------------------------------------------
        sincos(deltaSpin, &sinThetaSinload, &cosThetaSinload);         // 56clk
// 计算发送给FPGA的va vb vc
        Conversion2rTo3sMacroSc(OutputProcess.VdsRef, OutputProcess.VqsRef,     // 19clk
            sinThetaSinload, cosThetaSinload, 
            vaRef_, vbRef_, vcRef_);
       UpdateFpgaVoltageData();  
        SpinningLoad.FluxReference = OutputProcess.FluxDS;
//------------------------------------------------------------------------------

        switch (SpinningLoad.Status)
        {
            case SPINNING_LOAD_CURRENT_RAMP_UP:     // 电流逐渐增加到设定值 currentLevel
                if (TRUE == motorControlOtherEnable.bit.fastSpinningLoad) 
                {
                    OutputProcess.IqsRef = 0.0;                
                }
                else
                {
                    switch (spinningLoadMenu.mode)
                    {
                         case POSITIVE:
                            if (OutputProcess.IqsRef < 0.05)//q轴电流加不到0.05就跳转到下一个状态，取决于d轴电流增加的快慢
                            {
                                OutputProcess.IqsRef += 0.001;
                            }
                            break;

                        case NEGATIVE: 
                           if (OutputProcess.IqsRef > -0.05)
                            {
                                OutputProcess.IqsRef -= 0.001;
                            }
                            break; 

                        case BOTH: 
                            OutputProcess.IqsRef = 0.0;
                            break;

                        default:
                            break;    
                    }
                }

                tmp = OutputProcess.FastLoopSamplePeriod / spinningLoadMenu.currentRampRate;
#if 0                
                if (TRUE == motorControlOtherEnable.bit.fastSpinningLoad)   // 快速飞车启动，使用空载电流励磁
                {
                    spinningLoadMenu.currentLevel = motorPara.iNoload < 0.2 ? 0.2: motorPara.iNoload;
                    tmp = OutputProcess.FastLoopSamplePeriod / sdafa;    
                }
#endif                
                if (OutputProcess.IdsRef < spinningLoadMenu.currentLevel)   // HD33载波频率很低时，每拍步长大
                {
                    OutputProcess.IdsRef += tmp;
                    if (OutputProcess.IdsRef > spinningLoadMenu.currentLevel)
                    {
                        OutputProcess.IdsRef = spinningLoadMenu.currentLevel;
                    }
                }
				else if((fabs(OutputProcess.IqsRef) < 0.05) &&
					((spinningLoadMenu.mode == POSITIVE) || (spinningLoadMenu.mode == NEGATIVE)))
				{
					//等待q轴电流增加
				}
                else if ((OutputProcess.Ids > spinningLoadMenu.maximumCurrent) || 
                    (OutputProcess.Iqs > spinningLoadMenu.maximumCurrent) 
                    //(TRUE == curLoopWrongFlag)    // 飞车启动过程电流没闭上，暂时先不加入
                   )    // 电流超过阈值
                {
                    OutputProcess.IdsRef = 0.0;
                    OutputProcess.IqsRef = 0.0;
                    SpinningLoad.Status = SPINNING_LOAD_CURRENT_ERROR;
                }
                else
                {
                    SpinningLoad.Status = SPINNING_LOAD_SCAN_IN_PROGRESS;
                    if (TRUE == motorControlOtherEnable.bit.fastSpinningLoad)
                    {
                        SpinningLoad.Status = FAST_SPINNING_LOAD_OBSERVER;
                    }
                }
                break;

            case SPINNING_LOAD_SCAN_IN_PROGRESS:    // 开始扫描
                if (fabs(SpinningLoad.SpeedReference) < OutputProcess.RatedFrequency * 0.1)//380电机可能低频范围和阈值系数改大
                {
                    spinningLoadThresholdScaler = 2.0 - 
                        10.0 * fabs(SpinningLoad.SpeedReference) * OutputProcess.iRatedFrequency;
                }
                else
                {
                    spinningLoadThresholdScaler = 1.0;
                }
                tmp = (OutputProcess.FluxDS > spinningLoadThresholdScaler * spinningLoadMenu.threshold)
                    ? TRUE : FALSE;
                
                // 每个调用周期，频率的变化值
                frqDelta = OutputProcess.RatedFrequency * OutputProcess.FastLoopSamplePeriod / spinningLoadMenu.speedRampRate;
                
                minimumScanSpeed = TWO_PI * SPINNINGLOAD_MIN_FRQ_HZ;

                switch (SpinningLoad.Mode)
                {
                    case POSITIVE:      // 正方向搜索，从1.05倍最大频率逐渐减小
                        SpinningLoad.SpeedReference -= frqDelta;
                        if (SpinningLoad.SpeedReference > minimumScanSpeed) 
                        {
                            if ((tmp) && (TRUE != curLoopWrongFlag))    // 搜索成功，电流正常闭环
                            {
                                SpinningLoad.Status = SPINNING_LOAD_YES;
                            }
                        }
                        else            // 搜索失败
                        {
                            if (BOTH == spinningLoadMenu.mode)      // 双向搜索
                            {
                                SpinningLoad.SpeedReference = -1.05 * coreMaxFrqRads;  // 1.05倍最大频率开始扫频
                                SpinningLoad.Status = SPINNING_LOAD_CURRENT_RAMP_UP;
                                SpinningLoad.Mode = NEGATIVE;   // 双向搜索，正向搜索不成功，搜索负向
                            }
                            else
                            {
                                SpinningLoad.Status = SPINNING_LOAD_NO;
                            }
                        }
                        break;

                    case NEGATIVE:      // 反方向搜索，从-1.1倍额定频率逐渐减小
                        SpinningLoad.SpeedReference += frqDelta;
                        if (SpinningLoad.SpeedReference < -minimumScanSpeed) 
                        {
                            if (tmp)    // 搜索成功
                            {
                                SpinningLoad.Status = SPINNING_LOAD_YES;
                            }
                        }
                        else            // 搜索失败
                        {
                            SpinningLoad.Status = SPINNING_LOAD_NO;
                        }
                        break;

                    case BOTH:          // 两个方向都搜索
                        SpinningLoad.Mode = POSITIVE;   // 先搜索正向
                        break;

                    default:
                        break;
                }
                break;
                
            case SPINNING_LOAD_YES:     // 搜索成功
                SpinningLoad.UseSpeedReference = TRUE;  // 搜索成功，参数赋值
                SpinningLoad.FluxReference = OutputProcess.FluxDS;
                SpinningLoad.PresetTorqueCurrentRegulator = TRUE;
                SpinningLoad.PresetMagnetizingCurrentRegulator = TRUE;
                FastSpinningLoad.UseFluxFdbFastSpinningLoad = TRUE;
                SpinningLoad.UseFluxReference = TRUE;
                SpinningLoad.Status = SPINNING_LOAD_CURRENT_RAMP_DOWN;
                break;

            case SPINNING_LOAD_NO:      // 搜索失败
                SpinningLoad.SpeedReference = 0.0;
                SpinningLoad.UseSpeedReference = TRUE;
                SpinningLoad.FluxReference = 0.0;
                SpinningLoad.PresetTorqueCurrentRegulator = TRUE;
                SpinningLoad.PresetMagnetizingCurrentRegulator = TRUE;
                FastSpinningLoad.UseFluxFdbFastSpinningLoad = TRUE;
                SpinningLoad.UseFluxReference = TRUE;
                SpinningLoad.Status = SPINNING_LOAD_CURRENT_RAMP_DOWN;
                break;

            case SPINNING_LOAD_CURRENT_ERROR:
                //break;
            case FAST_SPINNING_LOAD_OBSERVER:

                tmp = (OutputProcess.FluxDS > spinningLoadMenu.threshold)
                    ? TRUE : FALSE;
                
#define FAST_SPINNINGLOAD_LOWFRQ_TIME   0.5     // 低频处理累计等待时间，s
                if ((fabs(SpinningLoad.SpeedReference) < TWO_PI * FAST_SPINNINGLOAD_MIN_FRQ_HZ) &&
                    (!tmp)
                    )
                {
                    fastSpinningLoadTicker++;
                    fastSpinningLoadLowFrqFlag = (fastSpinningLoadTicker > 
                        OutputProcess.FastLoopFrequency * FAST_SPINNINGLOAD_LOWFRQ_TIME) ? TRUE : FALSE;
                }   
   
                if (((tmp) && (TRUE != curLoopWrongFlag)) ||
                    (fastSpinningLoadLowFrqFlag)
                    )
                {
                    SpinningLoad.Status = SPINNING_LOAD_YES;
                    fastSpinningLoadTicker = 0;
                }
                else
                {
                    SpinningLoad.Status = FAST_SPINNING_LOAD_OBSERVER;                    
                }                
                break; 
            case SPINNING_LOAD_CURRENT_RAMP_DOWN:
//                if ((OutputProcess.IdsRef -= 0.001) <= 0.0)
//                {
//                    OutputProcess.IdsRef = 0.0;
//                    SpinningLoad.Status = SPINNING_LOAD_DONE;
//                }
                // iq减小至0
                if (FALSE == motorControlOtherEnable.bit.fastSpinningLoad)
                {
                    switch (SpinningLoad.Mode)
                    {
                         case POSITIVE:
                            if (OutputProcess.IqsRef > 0.0)
                            {
                                OutputProcess.IqsRef -= 0.001;
                                SpinningLoad.Status = SPINNING_LOAD_CURRENT_RAMP_DOWN;
                            }
                            else
                            {
                                OutputProcess.IqsRef = 0.0;
                                SpinningLoad.Status = SPINNING_LOAD_DONE;
								spinloadCurentRampTest++;
                            }
                            break;

                        case NEGATIVE: 
                            if (OutputProcess.IqsRef < 0.0)
                            {
                                OutputProcess.IqsRef += 0.001;
                                SpinningLoad.Status = SPINNING_LOAD_CURRENT_RAMP_DOWN;
                            }
                            else
                            {
                                OutputProcess.IqsRef = 0.0;
                                SpinningLoad.Status = SPINNING_LOAD_DONE;
                            }
                            break;
                        default:
                            SpinningLoad.Status = SPINNING_LOAD_DONE;
                            break; 
                    }
                }
                else
                {
                    SpinningLoad.Status = SPINNING_LOAD_DONE;
                }
//                SpinningLoad.Status = SPINNING_LOAD_DONE;
                break;

            case SPINNING_LOAD_DONE:
            default:
                break;
        }
    }

    if (SPINNING_LOAD_DONE == SpinningLoad.Status)  // 搜索完成
    {
        if (TRUE == SpinningLoad.UseSpeedReference) // 搜索到了频率
        {
            extern struct PiDataType idRegulatorParams;
            extern struct PiDataType iqRegulatorParams;

            if (FALSE == motorControlOtherEnable.bit.fastSpinningLoad)      
            {                                
    //            deltaSPLL = deltaSpin + SpinningLoad.SpeedReference * OutputProcess.FastLoopSamplePeriod * 0;
    //            deltaSPLL = deltaSpin + SpinningLoad.SpeedReference * OutputProcess.SlowLoopSamplePeriod * 0.5;
    //            Modulo2PI(&deltaSPLL);
                deltaSPLL = deltaSpin;
                pllDataS.angle = deltaSpin;
//                pllDataBackEmf.angle = deltaSpin;

                SpinningLoad.SpeedReference = 
                    (fabs(SpinningLoad.SpeedReference) <= TWO_PI * SPINNINGLOAD_MIN_FRQ_HZ) ? 0.0: (SpinningLoad.SpeedReference);
                BackEMFPllParams.accumulator = SpinningLoad.SpeedReference;
                //OutputProcess.DeltaSBackEMF = deltaSpin;
                OutputProcessPllParams.accumulator = SpinningLoad.SpeedReference;                
            }
            else
            {                
                tmp = (fabs(SpinningLoad.SpeedReference) <= TWO_PI * FAST_SPINNINGLOAD_MIN_FRQ_HZ) ? 0.0: (SpinningLoad.SpeedReference);  

                SpinningLoad.SpeedReference = tmp;                    
                BackEMFPllParams.accumulator = tmp;                
                OutputProcessPllParams.accumulator = tmp;
                pllDataS.angle = deltaSpin;
            }

            OutputProcessPllParams.lastInput = 0.0;
            BackEMFPllParams.lastInput = 0.0;
            OutputProcess.Frequency = SpinningLoad.SpeedReference;
            pllDataS.pllParams = &OutputProcessPllParams;
            fluxSData.pOutPllPi = &OutputProcessPllParams;
//            pllDataBackEmf.pllParams = &BackEMFPllParams;
            OutputProcess.DeltaSBackEMF = deltaSpin;
            OutputProcess.DeltaS = deltaSpin; 

			if(motorControlMode == IM_SVC4)
			{
				ImSvc4FluxRFrq = SpinningLoad.SpeedReference;
            	DeltaImSvc4 = deltaSpin;
            	//OutputProcess.DeltaS = DeltaImSvc4;
			}

            iqRegSpinningLoad = OutputProcess.VqsRef;
			/*
            if((fabs(pllBackEmfFrq) / TWO_PI) > 30.0)
            {
            	SpinningLoad.SpeedReference = pllBackEmfFrq;
            }
            */

//            idRegulatorParams.accumulator = magCurrentRegParams.accumulator;
//            idRegulatorParams.lastInput = 0;
//            iqRegulatorParams.accumulator = torqueCurrentRegParams.accumulator;
//            iqRegulatorParams.lastInput = 0;
        }
        
#if 0
        coreRunStatus.bit.run = 0;
        OutputProcess.Enable = FALSE;
        DriveControl.State = COAST_STATE;
        if (!coreErrorCode)
            coreErrorCode = 94;
#endif
    }

    // 求OutputProcess.Frequency在一个速度环周期的平均值
    {
        outputProcessFrqSum += SpinningLoad.SpeedReference;
        outputProcessFrqTicker++;
    }
}



//==============================================================================
//
// 计算发送给FPGA的va vb vc
//
//==============================================================================
//void FpgaVoltageDataSpinUpdate(void)
//{
//    ;
//}



f32 dgfs = 0.03;
extern RAMP_CTRL_STRUCT fluxRampCtrl;
extern struct PiDataType FluxRegulatorParams;
//==============================================================================
//
// 在 磁链给定斜坡处理函数 中调用，慢环
//
//==============================================================================
void SpinningLoadSlowDeal(void)
{
    if (TRUE == SpinningLoad.UseFluxReference)
    {
        extern f32 idRef;
        f32 tmp;
        
        tmp = GetMin(SpinningLoad.FluxReference, fluxCtrlMenu.fluxDemand);

        if (smControl)
        {
            FluxRegulatorParams.accumulator = tmp;      // 磁链环积分初始值赋值为给励磁柜的励磁电流
        }
        else
        {
            FluxRegulatorParams.accumulator = OutputProcess.IdsRef -    // 磁链环积分初始值赋值为转速跟踪的id
                tmp * motorPara.iNoload * 1.0 + dgfs;  // 
            idRef = OutputProcess.IdsRef;       // 
        }

        fluxRampCtrl.curValue = tmp;
        
        SpinningLoad.UseFluxReference = FALSE;
    }
}

extern PMSVC_EST_SPEED_DATA PmSvcData;
#define Rsample  (56)
#define Csample  (0.47)
extern struct PHASE_LOCK_LOOP_STR pllDataBackEmf;
extern f32 outVoltage;
extern u16  IFmodelFlga;
extern f32 sampleVoldOb,sampleVolqOb;
extern u16 motorControlMode;
extern f32 DeltaPmsmSvc;
void PmsmSvcSpinload(void);
void PmsmSvcSpinload(void)
{
	f32 angleTmp;
	f32 tmp;
    f32 R2CVolPara;
	f32 abspllBackEmfFrq;
	static u16 TurnTimes = 0;
	static u16 RunFlag = 0;

	if(((motorControlMode != PMSM_SVC) && (motorControlMode != PMSM_FVC)) || 
		(SPINNING_LOAD_OFF == spinningLoadMenu.mode))
	{
		return;
	}
	
	R2CVolPara = 1000.0 /(Rsample *Csample);
	tmp = R2CVolPara;
    abspllBackEmfFrq = fabs(pllBackEmfFrq);
    angleTmp = atan(fabs(pllBackEmfFrq/tmp));
	
	if(pllBackEmfFrq > 0)
	{
		angleTmp = pllDataBackEmf.angle + angleTmp - (ONE_PI * 0.5);//转子角度
		angleTmp = angleTmp - 0.75 * OutputProcess.FastLoopSamplePeriod * abspllBackEmfFrq;//补偿离散化引起的误差
	}
	else
	{
		angleTmp = pllDataBackEmf.angle - angleTmp + (ONE_PI * 0.5);
		angleTmp = angleTmp + 0.75 * OutputProcess.FastLoopSamplePeriod * abspllBackEmfFrq;
	}
    Modulo2PI(&angleTmp);
	
	if(angleTmp > ONE_PI)//观测器的角度是-pi到pi
	{
		angleTmp = angleTmp - TWO_PI;
	}

    if(coreRunStatus.bit.run == 0)
    {	
    	TurnTimes = 0;

		if(fabs(pllBackEmfFrq) > (motorPara.ratingFrq * 3.0 * TWO_PI / 50.0))
		{
			CommandGenerator.SpeedReference = pllBackEmfFrq;//IF模式从新起来
			PmSvcData.est_bem = outVoltage * motorPara.ratingVoltage /SQRT3 *SQRT2 *128;
			PmSvcData.est_bem1 = PmSvcData.est_bem;
			PmSvcData.est_angel = angleTmp * (f32)4294967296 /TWO_PI;
			PmSvcData.est_omg =(long)(pllBackEmfFrq * 256.0);
			PmSvcData.est_omgm1 = PmSvcData.est_omg;
			PmSvcData.est_omgm = PmSvcData.est_omg;
			PmSvcData.est_omg_lpf = PmSvcData.est_omg;
			PmSvcData.id1 = PmSvcData.id;
			PmSvcData.iq1 = PmSvcData.iq;
			PmSvcData.vd1 = PmSvcData.vd;
			PmSvcData.vq1 = PmSvcData.vq;
		}
		else
		{
			PmSvcData.est_bem = 0;
			PmSvcData.est_bem1 = 0;
			PmSvcData.est_angel = 0;
			PmSvcData.est_omg = 0;
			PmSvcData.est_omgm1 = 0;
			PmSvcData.est_omgm = 0;

		}
	}
	else
	{
		if((IFmodelFlga == 1) && (coreStatus.bit.speedTrackEnd == 0))
		{
			CommandGenerator.SpeedReference = pllBackEmfFrq;
		}
		
		TurnTimes++;
		if((TurnTimes < 5) &&
			(fabs(pllBackEmfFrq) > (motorPara.ratingFrq * 3.0 * TWO_PI / 50.0)))
		{
			PmSvcData.est_angel = angleTmp * (f32)4294967296 /TWO_PI;
			PmSvcData.est_omg =(long)(pllBackEmfFrq * 256.0);
		}
		else
		{
			TurnTimes = 5;
		}
	}
	//同步机飞车启动补偿反电动势
	if((coreRunStatus.bit.run == 1) && (RunFlag == 0))
	{
		iqRegulatorParams.accumulator = sampleVolqOb;
	}

	RunFlag = coreRunStatus.bit.run;
	
}


#elif 1

f32 coreFrqAimHzOld;
void SpinningLoadSlowDeal(void){}

#endif








