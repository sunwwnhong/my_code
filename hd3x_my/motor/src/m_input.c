//==================================================================================================
//
// 输入处理
// 输入电网电压、电流采样
// 相位获取
//
//
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#include "m_input.h"
#include "m_main.h"
#include "m_pll.h"
#include "m_frqSrc.h"
#include "m_cell.h"
#include "m_interfaceModify.h"
#include "m_macro_transfer.h"
#include "m_transfer.h"


#if !DEBUG_PRG_IN_RAM   // 程序放在Flash中
#define DEBUG_P_INPUT               1
#define DEBUG_P_MISC                1       // 1-一些零散的计算，INPUT_FAULT_DEAL, UNDER_VOL_RIDE_THRU有效时需要打开
#define DEBUG_P_INPUT_FAULT_DEAL    1       // 输入保护: 变压器副边阻抗偏小，变频器损耗过大
#define DEBUG_P_UNDER_VOL_RIDE_THRU 0       // 1-under voltage ride through 有效
#elif 1                 // 程序放在RAM中调试
#define DEBUG_P_INPUT               0
#define DEBUG_P_MISC                0       // 1-一些零散的计算，INPUT_FAULT_DEAL, UNDER_VOL_RIDE_THRU有效时需要打开
#define DEBUG_P_INPUT_FAULT_DEAL    0
#define DEBUG_P_UNDER_VOL_RIDE_THRU 0       // 1-under voltage ride through 有效
#endif





#if DEBUG_FUNCTION_IN_RAM   // 将部分函数放到RAM中，加快运行速度
//#pragma CODE_SECTION(InFastLoopControl,     "ramfuncs");
#endif

#pragma DATA_SECTION(InputProcess, "data_ram");
#pragma DATA_SECTION(InputProcessDisplay, "data_ram");


//extern struct SynchTransferType SynchTransfer;
struct InputProcessType InputProcess;
struct InputProcessDisplayType InputProcessDisplay;
extern struct DriveControlType DriveControl;  
extern union DSP_MAIN_COMMAND coreMainCmd;

// 电网输入电压
f32 inputVol;
f32 inputVolFil;
f32 inputVolDis;



#if DEBUG_P_INPUT

f32 deltaU;         // input vector angle


u16 inputOneCycleFault;
u16 excessiveLossFault;


#define PI_OVER_2   (ONE_PI / 2)


f32 harmonicOrder = 1.0;    // 8160
f32 harmonicsInteg = 0.001; // 8170


struct PiDataType InputProcessPllParams =
 //   {50 * 2.0 * TWO_PI,   -50 * 2.0 * TWO_PI,   0.3,    100.0};
//    {50 * 2.0 * TWO_PI,   -50 * 2.0 * TWO_PI,   1.0,    70.0};
      //{50 * 2.0 * TWO_PI,   -50 * 2.0 * TWO_PI,   0.5,    4.0};//160.0};
      {50 * 2.0 * TWO_PI,   -50 * 2.0 * TWO_PI,   0.5,    160};//160.0};
     // {50 * 2.0 * TWO_PI,   -50 * 2.0 * TWO_PI,   0.0001,    0.01};
  //    {50 * 2.0 * TWO_PI,   -50 * 2.0 * TWO_PI,   1.5,    4.0};

f32 intputpllKP = 1;
f32 intputpllKI = 0.05;

f32 inputPllSeed = 0;//TWO_PI * INPUT_BUS_FRQ;  // 输入电压处理的seed，跟相序有关
f32 PLLError;                       // LLError=Deviation of PLL output from seeded value
bool PLLReady;

//u16 StartupDelayCount, PowerupDelayCount; // Delays (counts) for software & MV startup


f32 driveLosses;    // difference between output and input power

f32 iaUSquared, ibUSquared, icUSquared;
f32 eaUSquared, ebUSquared, ecUSquared, e0Squared;
f32 InputPower, RawInputPower, SinglePhasingCurrentScaler;
//const f32 rmsConst = 2.0/3.0;        // for [sqrt(2.0)/sqrt(3.0)]^2
#define rmsConst    (2.0/3.0)           // for [sqrt(2.0)/sqrt(3.0)]^2

f32 iqMaxAllowed1;
extern Uint16 cfGroup[F2C_DEBUG_PARA_LEN];
void                             // returns nothing
HarmonicsCalc(
    volatile f32 *Signal,           // Signal to analyze
    f32 order,                      // Order of harmonic
    f32 delta,                      // phase angle radians
    volatile f32 *ah,               // pointer to A harmonic component
    volatile f32 *bh,               // pointer to B harmonic component
    volatile f32 *th,               // pointer to total harmonics
    f32 integGain,                  // integral gain
    s16   enable)                   // enable
;







f32                             // returns a thermal value representing
ThermalOverload(                // heat into transformer.
    f32 integGain,              // integrator gain
    f32 imax,                   // input current maximum of the 3 RMS input currents
    s16 enable)                 // enable
;


f32
CellOverCurrentProtection(
    f32 idsRef)
;



void
UnderVoltageRideThru(
    f32 pavg,                       // average power
    f32 erms,                       // line voltage
    f32 propGain,                   // proportional gain
    f32 integGain,                  // integral gain
    f32 iqsMax,                     // Iqs Max
    f32 *upperLimit,                // upper limit
    f32 *lowerLimit,                // lower limit
    u16 enable)                     // enable
;

/*

f32                                 // reactive current level
OneCycleProtection(
    f32 ktr,                        // constant
    f32 iq,                         // reactive current
    f32 id,                         // real current
    f32 integ_gain,                 // integral gain
    f32 erms,                       // RMS line voltage
    f32 iSPScaler,                  // Single Phasing Current Scaler
    s16 enable)
;

*/
//void ExcessiveDriveLossesDetection(void);

//f32 sdfa = TWO_PI * 50;

f32 ealpha, ebeta;                  // 2 phase input voltages
f32 ialpha, ibeta;                  // 2 phase input currents
extern f32 inputVolFil;
f32 iaDC, ibDC, icDC;               // ia,ib,ic的直流分量
f32 asasdsfq;
struct PHASE_LOCK_LOOP_STR pllDataInputPrc;
extern f32 afeFpgaData[3];
struct REGULATOR_STR regulatorDataInput;
//==============================================================================
//
// 输入处理，快环
//
//==============================================================================
void InFastLoopControl(void)
{

    f32 Ea;         // voltages
    f32 Eb; 
#if DEBUG_P_MISC
    f32 Ec;
    f32 edneg, eqneg;               // dq negative sequence voltages
    f32 Eab, Ebc, Eca;
//    f32 RawInputPower1; 
    static f32 eaUSquaredAcc, ebUSquaredAcc, ecUSquaredAcc;
    static f32 e0averageAcc;
  //  static f32 inputPowerAcc;
#endif
    static bool synchFilterReset;   // true表示一个电网周期时间到达，当 deltaU==2*PI 时，reset会有效
    static bool edSynchFilterReset; // true表示1/2个电网周期时间到达，当 deltaU==PI 时，reset会有效
    static f32 edaverageAcc, HalfPeriod;
    static f32 HalfCounter1, HalfCounter2;
    static f32 samplePeriod;        // sample period for synch filters
    static f32 sampleCounter;       // sample counter for synch filters
    f32 sinAngle, cosAngle;
//    f32 tmp;


//  #define FAKE_INPUT  // perfect input waveform for debugging and no inputs
#ifdef FAKE_INPUT
    {
        static f32 inputPhase = 0;
        inputPhase += 50 * TWO_PI * InputProcess.SamplePeriod;
        Modulo2PIMacro(&inputPhase);
        va  = sin(inputPhase);
        vb  = sin(inputPhase - (TWO_PI / 3.0));
        vc  = sin(inputPhase - (2.0 * TWO_PI / 3.0));
    }
#endif 
    Ea = inVolData.u;
    Eb = inVolData.v;
#if DEBUG_P_MISC
    Ec = inVolData.w;

// 输入电压零序分量
    SynchFilterMacro(2.0 * inVolData.e0 * inVolData.e0, e0Squared, e0averageAcc, samplePeriod, synchFilterReset);
#endif
 
// For rms calculation use measured voltage signals
    Eab = Ea - Eb;   // 线电压
    Ebc = Eb - Ec;
    Eca = Ec - Ea;
    SynchFilterMacro(rmsConst * Eab * Eab, eaUSquared, eaUSquaredAcc,
        HalfPeriod, (synchFilterReset || edSynchFilterReset));
    SynchFilterMacro(rmsConst * Ebc * Ebc, ebUSquared, ebUSquaredAcc,
        HalfPeriod, (synchFilterReset || edSynchFilterReset));
    SynchFilterMacro(rmsConst * Eca * Eca, ecUSquared, ecUSquaredAcc,
        HalfPeriod, (synchFilterReset || edSynchFilterReset)); 


    sampleCounter += 1.0;   // 采样计数器

// 1/2电网周期滤波
    if (HalfCounter2 == sampleCounter)
    {
        edSynchFilterReset = TRUE;          // 当 deltaU==PI 时，reset会有效
        HalfPeriod = 1.0 / HalfCounter2;
    }
    else
    {
        edSynchFilterReset = FALSE;
    }

    if (TRUE == synchFilterReset)
    {
        if (true == PLLReady)
        {
            samplePeriod =  1.0 / sampleCounter;
        }
        else
        {  // if there is no medium voltage contain the sample period
            samplePeriod = 1.0 / 25.0;
        }
        
       // HalfCounter1 = floor(0.5 * sampleCounter + 0.5);
        HalfCounter1 = (0.5 * sampleCounter + 0.5);
        HalfPeriod = 1.0 / HalfCounter1;
        HalfCounter2 = sampleCounter - HalfCounter1;
        
        sampleCounter = 0.0;
    }

   // ClarkeCalcMacro(inVolData.u, inVolData.v, ealpha, ebeta); 
   ealpha = (inVolData.u - 0.5 *inVolData.v -0.5 *inVolData.w) * 0.666666667;
   ebeta =  (inVolData.v - inVolData.w ) / SQRT3;
    sincos(deltaU, &sinAngle, &cosAngle);

// convert 2 phase voltages and currents to dq reference (and negative sequence) and filter
    ParkCalcMacroSc(
        ealpha * (1.0), 
        ebeta  * (1.0),
        sinAngle, cosAngle, InputProcess.EdRaw, InputProcess.EqRaw);  

    
#if DEBUG_P_MISC
// 输入电压零序分量
    ParkCalcMacroSc(ealpha, ebeta, -sinAngle, cosAngle, edneg, eqneg); 
#endif

// Filter Ed every 1/2 cycle of input frequency
    SynchFilterMacro(
        InputProcess.EdRaw, InputProcess.EdAverage, edaverageAcc,
        HalfPeriod, (synchFilterReset || edSynchFilterReset)
        );

// Synchronous filters for id and iq (at input frequency) 
    InputProcess.Ed = LPF_Gain(InputProcess.EdRaw, InputProcess.Ed, 0.75);    // k = 1/(1-0.75) = 4
#if DEBUG_P_MISC
    InputProcess.Eq = LPF_Gain(InputProcess.EqRaw, InputProcess.Eq, 0.75);

// filter Negative sequence components
    InputProcess.EdNegative = LPF_Gain(edneg, InputProcess.EdNegative, 0.999);
    InputProcess.EqNegative = LPF_Gain(eqneg, InputProcess.EqNegative, 0.999); 
#endif
    
    // 大于一定值时，才这样计算。
//    if (GetA2AddB2(InputProcess.EdRaw, InputProcess.EqRaw) >= 0.005 * 0.005)
    {
        // 锁相环，得到输入电网频率
        InputProcessPllParams.propGain = intputpllKP;
        InputProcessPllParams.integGain = intputpllKI;
        pllDataInputPrc.input = InputProcess.EqRaw; 
        pllDataInputPrc.seed = 1.0; 
        // pllDataInputPrc.seed = 50.0 * TWO_PI;
       //  pllDataInputPrc.angle = deltaU;
        PhaseLockLoopInput(&pllDataInputPrc);
       //PhaseLockLoop(&pllDataInputPrc);
        InputProcess.Frequency = pllDataInputPrc.frequency * 50;
        //InputProcess.Frequency = pllDataInputPrc.frequency;
        deltaU = pllDataInputPrc.angle;
        synchFilterReset = pllDataInputPrc.moduloFlag;
    } 
    if (GetA2AddB2(InputProcess.EdRaw, InputProcess.EqRaw) < 0.005 * 0.005) 
    {
        InputProcess.Frequency = 0;
//        synchFilterReset = FALSE;
    }
    
// 环流，使用输出相位，在没有输入电压采样时，可能需要
//    InputProcess.Frequency = sdfa;

#if DEBUG_P_SYNC_TRANSFER
    // calculate line flux vector angle
    InputProcess.LineFluxVectorAngle = deltaU - PI_OVER_2;
//	InputProcess.LineFluxVectorAngle = deltaU ;
    Modulo2PIMacro1(InputProcess.LineFluxVectorAngle);
#endif

}











//#define INPUT_BUS_FRQ_LIMIT 0.3
enum MVStatus {WAS_LOW, WAS_HIGH};
enum MVStatus mediumVoltageStatus;
f32 inputFrqFilterGain;
//==============================================================================
//
// 输入处理，慢环
//
//==============================================================================
void InSlowLoopControl(void)
{
#if DEBUG_P_MISC
    f32 erms;
    f32 sign;
    f32 iMax; 
    f32 tanOfInputCurrentAngle;
    static f32 iMaxFil;
#endif
    static u16 powerupTimer;
    static u16 startupTimer;
    u16 PowerupDelayCount;
//    const u16 StartupDelayCount = 600;
#define StartupDelayCount   600
//    f32 tmp;

#if DEBUG_P_MISC
    // calculate scaling correction factors for input power
    // 0.04 was obtained from readings on the drive. This value is two times the value
    // derived from the additional hardware delay in the voltage feedback (no current explanation)
    sign = (InputProcessDisplay.Id >= 0.0) ? 1.0 : (-1.0);
    tanOfInputCurrentAngle = InputProcessDisplay.Iq * sign / (fabs(InputProcessDisplay.Id) + 0.01);

// Calculated corrected input power
    InputPower = RawInputPower * (1 + 0.04 * tanOfInputCurrentAngle);

// 功率因数计算
    InputProcess.PowerFactor = PowerFactorCalc(InputProcess.Id, InputProcess.Iq);

    // calculate average power
    if (OK == InputProcess.MediumVoltageStatus)
    {
        InputProcess.AveragePower = LPF_K(InputPower, InputProcess.AveragePower, 10);
    }
    else
    {
        InputProcess.AveragePower = 0.0;
    }
    
    InputProcess.IaU = sqrt(iaUSquared);
    InputProcess.IbU = sqrt(ibUSquared);
    InputProcess.IcU = sqrt(icUSquared);

    InputProcess.EaU = sqrt(eaUSquared);
    InputProcess.EbU = sqrt(ebUSquared);
    InputProcess.EcU = sqrt(ecUSquared);
 
    InputProcess.E0Average = sqrt(e0Squared);

    erms = (InputProcess.EaU + InputProcess.EbU + InputProcess.EcU) / 3.0;
    if (erms == 0.0)
    {
		erms = 0.0001;
	}
    // Calculate highest input voltage in rms
    InputProcess.ErmsMax = GetMax3(fabs(InputProcess.EaU), fabs(InputProcess.EbU), fabs(InputProcess.EcU));
    InputProcess.eUnbalance = (InputProcess.ErmsMax - 
        GetMin3(fabs(InputProcess.EaU), fabs(InputProcess.EbU), fabs(InputProcess.EcU))
        ) / erms;

    // determine maximum phase current
    iMax = GetMax3(InputProcess.IaU, InputProcess.IbU, InputProcess.IcU);

    iMaxFil = LPF_K(iMax, iMaxFil, 125);  // 1/(1-0.992)=125
#endif

#if DEBUG_P_UNDER_VOL_RIDE_THRU
    // calculate under voltage ride through
    UnderVoltageRideThru(InputPower,
                         // adjust input voltage for tap setting
                         InputProcess.ErmsMax * (1.0 - InputProcess.TransformerTapSetting),
                         inputProtectMenu.undervoltageKp,
                         inputProtectMenu.undervoltageKi,
                         OutputProcess.MaximumTorqueCurrent,
                         &InputProcess.UnderVoltageLimit,
                         &InputProcess.UnderVoltageLowerLimit,
                         InputProcess.Enable);
#endif

#if DEBUG_P_INPUT_FAULT_DEAL
// Protect cells from excess current overload by calculating limit
    OutputProcess.CellOverLoadLimit = CellOverCurrentProtection(OutputProcess.IdsRef);

// calculate thermal overload
    InputProcess.ThermalOverloadLimit = ThermalOverload(
        inputProtectMenu.xformerThermalGain * 5.0 * InputProcess.SamplePeriod,
        iMaxFil, 
        InputProcess.Enable);

    // determine one cycle transformer current limit
//    InputProcess.OneCycleLimitInput = (!cellStatus.bit.cellCheckOver) ? 0.0 : InputProcess.Iq;
    InputProcess.OneCycleLimitInput = InputProcess.Iq;
/*
	InputProcess.OneCycleProtectionLimit = 
        OneCycleProtection( inputProtectMenu.xformerProtectK,
                            InputProcess.OneCycleLimitInput,
                            InputProcess.Id,
                            inputProtectMenu.oneCycleProtectKi,
                            erms, 
                            SinglePhasingCurrentScaler, 
                             InputProcess.Enable);
                  // (DriveControl.State != SPINNING_LOAD_STATE )&&(InputProcess.Enable )&& (OK == InputProcess.MediumVoltageStatus));   
         inputOneCycleFault = InputProcess.OneCycleProtectionLimit < 
        inputProtectMenu.oneCycleProtectLimit * OutputProcess.MaximumTorqueCurrent;
    if (0.0 == inputProtectMenu.oneCycleProtectKi)  // 增益设置为0，关闭变压器副边阻抗偏小故障。
    {
        inputOneCycleFault = 0;
    }
*/
  //  ExcessiveDriveLossesDetection();
#endif

#if DEBUG_P_MISC
    InputProcessDisplay.Ed = LPF_K(InputProcess.Ed, InputProcessDisplay.Ed, 100);   // 1/(1-0.99) = 100
    InputProcessDisplay.Eq = LPF_K(InputProcess.Eq, InputProcessDisplay.Eq, 100);
    InputProcessDisplay.Id = LPF_K(InputProcess.Id, InputProcessDisplay.Id, 2000);  // 1/(1-0.9995) = 2000
    InputProcessDisplay.Iq = LPF_K(InputProcess.Iq, InputProcessDisplay.Iq, 2000);
    InputProcessDisplay.AveragePower = LPF_K(InputProcess.AveragePower, InputProcessDisplay.AveragePower, 100);// 1/(1-0.99) = 100
    InputProcessDisplay.Erms = LPF_K(erms, InputProcessDisplay.Erms, 100);    // 1/(1-0.99)=100
    InputProcessDisplay.ErmsMax = LPF_K(InputProcess.ErmsMax, InputProcessDisplay.ErmsMax, 100);
    InputProcessDisplay.Irms = LPF_K(
        (InputProcess.IaU + InputProcess.IbU + InputProcess.IcU) * (1.0 / 3.0), InputProcessDisplay.Irms, 2000);
#endif

    // calculate PLLError as the deviation of the PLL output from the seeded value (of 50Hz)
    PLLError = LPF_K(fabs(InputProcess.Frequency - inputPllSeed), PLLError, 6);

    if ((startupTimer++ >= StartupDelayCount) || (UNKNOWN != InputProcess.MediumVoltageStatus))
    {
        startupTimer = StartupDelayCount;

        PowerupDelayCount = (u16)(0.04 * OutputProcess.FastLoopFrequency);
        if ((InputProcessDisplay.Erms > 0.60) && (powerupTimer++ >= PowerupDelayCount))
        {
            if (WAS_LOW == mediumVoltageStatus)
            {
				mediumVoltageStatus = WAS_HIGH;
			}
            InputProcess.MediumVoltageStatus = OK;
            powerupTimer = 3 * PowerupDelayCount;   // Do not allow powerupTimer to count if PowerupDelayCount gets increased due to cell bypass
        }
        else 
        {
            if (WAS_HIGH == mediumVoltageStatus) 
            {
				mediumVoltageStatus = WAS_LOW;
			}
            InputProcess.MediumVoltageStatus = LOW;
            if (powerupTimer > PowerupDelayCount)
            {
                powerupTimer = 0;                   // Reset powerupTimer, allow counting when MV gets applied again
            }
        }
    }

        // Change the sign of the seed value (of the input PLL) if PLLError is not low enough within first 40 counts (PLL output ~= 55 +/- 15 Hz)
//    if ((powerupTimer > 60) && (PLLError > 94.0))
//    { 
//        inputPllSeed = -TWO_PI * INPUT_BUS_FRQ;
//    }
//? 这一段代码，在高压电上电，再下电，好像有问题。

    // Set PLLReady to true if PLLError is low enough or if MV has been applied for ~0.13secs (or 80 counts @ 600Hz slow-loop sample rate)
    if (((powerupTimer > 60) && (PLLError < 94.0)) || (powerupTimer > 100))
    {
        PLLReady = true;
    }
    else
    {
        PLLReady = false;
    }
#define INPUT_FQR_FILTER_T   0.0500   
    InputProcess.frqFilterGain = 1.0 - OutputProcess.SlowLoopSamplePeriod / INPUT_FQR_FILTER_T;
    InputProcess.FrequencyFiltered = LPF_Gain(
        InputProcess.Frequency, InputProcess.FrequencyFiltered, InputProcess.frqFilterGain);
#if DEBUG_P_MISC
    if (OK == InputProcess.MediumVoltageStatus)
    {
        InputProcessDisplay.Frequency = InputProcess.FrequencyFiltered;
    }
    else
    {
        InputProcessDisplay.Frequency = 0.0;
    }

    // Calculate instantaneous Input Power, VAR, and VA and apply corrections based on phase delay in voltage feedback
    InputProcess.EdIq = InputProcess.Ed * (InputProcess.Iq - 0.04 * InputProcess.Id) / (1.0 - InputProcess.TransformerTapSetting);
    InputProcess.EdId = InputProcess.Ed * (InputProcess.Id + 0.04 * InputProcess.Iq) / (1.0 - InputProcess.TransformerTapSetting);
    InputProcess.Kva = SqrtA2AddB2(InputProcess.EdIq, InputProcess.EdId);
#endif

}






//==============================================================================
//
// 输入处理初始化
//
//==============================================================================
void InitInputProcessing(void)
{
   // if (pwmT < 1.0 /1450  && (SynchTransfer.UpTransferState >= WAITING_FOR_CONTACTOR_CLOSURE))
   // if (pwmT < 1.0 /1450 )
    {
       // InputProcess.SamplePeriod = 1.0 /1500;
    }
    //else
    {   
        InputProcess.SamplePeriod = pwmT;
    }
    InputProcess.Enable = TRUE;
    
    pllDataInputPrc.sampleRate = 50 * TWO_PI * InputProcess.SamplePeriod;

    
   // pllDataInputPrc.sampleRate =  InputProcess.SamplePeriod;
   //   pllDataInputPrc.sampleRate = TWO_PI * 50.0 *  CpuTimer0.PeriodInUSec * 0.000001;

//    pllDataInputPrc.seed = 0;
   // pllDataInputPrc.seed = inputPllSeed;


#if DEBUG_P_MISC
// 变压器原边接头设定
    switch (inputProtectMenu.xformerTapSetting)
    {
        case TAP_AT_MINUS_5_PERCENT:
            InputProcess.TransformerTapSetting = -0.05;
            break;

        case TAP_AT_PLUS_5_PERCENT:
            InputProcess.TransformerTapSetting = 0.05;
            break;

        case TAP_AT_ZERO:
        default:
            InputProcess.TransformerTapSetting = 0.0;
            break;
    }
#endif
}




//==============================================================================
//
// 根据给定的id和iq输入，计算功率因数
//
//==============================================================================
f32 PowerFactorCalc(f32 id, f32 iq)
{
    return (id / sqrt(id * id + iq * iq + 0.0001));
}








#if DEBUG_P_UNDER_VOL_RIDE_THRU
//==============================================================================
//
// 低电压穿越
// 低电压时的电流限制
//
//==============================================================================
//f32 pmax;
//f32 regenLimit = -0.003;
//f32 motoringPower, regenPower;
void
UnderVoltageRideThru(
    f32 pavg,                       // average power
    f32 erms,                       // line voltage
    f32 propGain,                   // proportional gain
    f32 integGain,                  // integral gain
    f32 iqsMax,                     // Iqs Max
    f32 *upperLimit,                // upper limit
    f32 *lowerLimit,                // lower limit
    u16 enable)                     // enable
{
    register f32 pmax;              // automatic variable pmax
    f32 motoringPower, regenPower;
    static struct PiDataType underVoltageRideThruParams = {1.0, 0.0, 0.001, 0.1, 0.0, 1.0};
    static struct PiDataType regenVoltageParams = {1.0, 0.0, 0.001, 0.1, 0.0, 1.0};
    static f32 sign = 1.0;
    //f32 regenLimit = -0.003;     // Default value for non afe operation


    motoringPower = 0.0;
    regenPower = 0.0;

    // Calculate maximum power cability based on available voltage

    // Is the rms volatge greater than .66 of rated?
    if (erms > 0.66)
    {                  // pMax=100% when erms=0.90 & pMax=50% when erms=0.66 m=2.083
        pmax = 2.083 * erms - 0.875;    // linear approximation y = mx + c; y = 2.083x - 0.875

        // Limit to 1.05
        pmax = (pmax > 1.05) ? 1.05 : pmax;
    }
    else
    {                              // pMax=50% when erms=0.66 & pMax=0% when erms <= 0.65 m=50
        pmax = 50.0 * erms - 32.5;      // linear approximation y = mx + c;  y = 50x - 32.5
    }

    // Limit to 0.0
    pmax = (pmax < 0.0) ? 0.0 : pmax;

    InputProcess.PmaxUV = pmax;

    // Handle upper limit calculation

    // Limit power to only positive
    motoringPower = (pavg > 0.0) ? pavg : motoringPower;

    underVoltageRideThruParams.propGain  = propGain;
    underVoltageRideThruParams.integGain = integGain;

    // Are we in a ride through condition?
    if (pmax == 0.0)
    {
        // Is the regen limit appear not be for afe?
        // If so, use it
//        if (OutputProcess.MotorRegenLimit > -0.05)
//        {
//            regenLimit = OutputProcess.MotorRegenLimit;
//        }

        // Have we not changed directions or reached zero speed?
        if (1)//((sign * CommandGenerator.SpeedReference) > 10.0)
        {
           // Calculate max power which can be absorbed (Note: is < 0.0)
            f32 temp = regenLimit / fabs(CommandGenerator.SpeedReference + ONE_PI * sign) * OutputProcess.RatedFrequency;

            // Make sure were not out of range
            temp = (temp < -iqsMax) ? (-iqsMax) : temp;

            underVoltageRideThruParams.maxLimit = 0.98 * temp;
            underVoltageRideThruParams.minLimit = 1.01 * underVoltageRideThruParams.maxLimit;
        }
        // Motor has changed directions
        else 
        {
            underVoltageRideThruParams.maxLimit = 0.0;
            underVoltageRideThruParams.minLimit = regenLimit * OutputProcess.IqsRated;
        }
    }
    // We have power
    else
    {
        // Save sign of speed
        sign = (CommandGenerator.SpeedReference < 0.0) ? (-1.0) : 1.0;

        underVoltageRideThruParams.maxLimit = iqsMax;
        underVoltageRideThruParams.minLimit = 0.0;
    }

    // Use a regulator to determine current limit
    {
        struct REGULATOR_STR regulatorData;

        regulatorData.input = pmax - motoringPower;
        regulatorData.pi = &underVoltageRideThruParams;
        regulatorData.enable = enable;
       ////// RegulatorCalc(&regulatorData);
        *upperLimit = regulatorData.out;
    }

    // Handle lower limit calculation

    // Limit power to only negative
    regenPower = (pavg < 0.0) ? (-pavg) : regenPower;

    regenVoltageParams.propGain  = propGain;
    regenVoltageParams.integGain = integGain;

    regenVoltageParams.maxLimit = iqsMax;
    regenVoltageParams.minLimit = 0.0;

    // Use a regulator to determine current limit
    {
        struct REGULATOR_STR regulatorData;

        regulatorData.input = pmax - regenPower;
        regulatorData.pi = &regenVoltageParams;
        regulatorData.enable = enable;
      //////  RegulatorCalc(&regulatorData);
        *lowerLimit = regulatorData.out;
    }
}

#endif




#if DEBUG_P_INPUT_FAULT_DEAL
extern f32 cellOverloadLevel;
//==============================================================================
//
// 单元过载保护
//
// 每10分钟，允许单元电流过载1分钟。单元过载电流阈值通过功能码FA-31设置。
// 过载达到1分钟后，单元电流必须减低到100%，以防损坏单元。
// 
//
//============================================================================== 
struct PiDataType CellOverLoadParams = {6.0, 0.0, 1.0};
f32 CellOverCurrentProtection(f32 idsRef)
{
    static bool overLoadFlag;       // flag is constant until changed
    static f32 tenMinuteTimer;
    f32 overLoadLimit;
    f32 error;
    struct REGULATOR_STR regulatorData;

    regulatorData.pi = &CellOverLoadParams;

    // start timer
    tenMinuteTimer += SLOW_LOOP_TIME;

    // test for 10 minute limit (10 minutes * 60 seconds)
    if (tenMinuteTimer >= 10.0 * 60.0)
    {
        regulatorData.input = 0;
        regulatorData.enable = false;
        // reset accumulator to zero (fall through to reset of flag and timer)
       RegulatorCalc(&regulatorData);
    }
    // if not timed out - integrate overload error
    else
    {
        // calculate overload error based on PU Cell current rating
        error = OutputProcess.TotalCurrent * motorPara.ratingCurrent
                / driveParameterMenu.ratingOutputCurrent - 1.0;

        // error normalized to one second based on Fault Thread timing
        regulatorData.input = error * SLOW_LOOP_TIME;
        regulatorData.enable = true;
        RegulatorCalc(&regulatorData);
    }

    // test for integrator at either limit
    if (0.0 == CellOverLoadParams.accumulator)
    {
        // clear limit flag
        overLoadFlag = false;

        // reset timer
        tenMinuteTimer = 0;
    }
    // overload exceeded - set flag
    else if (CellOverLoadParams.accumulator >= CellOverLoadParams.maxLimit)
    {
        // set limit flag
        overLoadFlag = true;
    }

    // calculate overload based on motor rated current
    overLoadLimit = ((true == overLoadFlag) ? 1.0 : cellOverloadLevel) *
                    driveParameterMenu.ratingOutputCurrent / motorPara.ratingCurrent;

    // return overload limit condition
    if (overLoadLimit > idsRef)
    {
        return SqrtA2SubB2(overLoadLimit, idsRef);
    }
    else
    {
        return 0.01;
    }
}



struct PiDataType thermalOverloadParams = {0.0, 0.0, 0.0, 0.0, 0.0, 1.0};
//==============================================================================
//
// 输入移相变压器的过载保护，基于变压器的热模型
//
//============================================================================== 
f32                                 // returns a thermal value representing
ThermalOverload(                    // heat into transformer.
    f32 integ_gain,                 // integrator gain
    f32 imax,                       // input current maximum of the 3 RMS input currents
    s16 enable)                     // enable
{
    thermalOverloadParams.integGain = integ_gain;
    thermalOverloadParams.maxLimit = OutputProcess.MaximumTorqueCurrent;

    // return regulated thermal value
    {
        struct REGULATOR_STR regulatorData;

        regulatorData.input = 1.05 - imax;
        regulatorData.pi = &thermalOverloadParams;
        regulatorData.enable = enable;
        RegulatorCalc(&regulatorData);
        
        return regulatorData.out;
    }
}



/*
//==============================================================================
//
// 输入移相变压器的副边短路保护
//
//============================================================================== 
f32                                 // reactive current level
OneCycleProtection(
    f32 ktr,                        // constant
    f32 iq,                         // reactive current
    f32 id,                         // real current
    f32 integ_gain,                 // integral gain
    f32 erms,                       // RMS line voltage
    f32 iSPScaler,                  // Single Phasing Current Scaler
    s16 enable)
{
    static struct PiDataType oneCycleProtectionParams = {3.0, 0.0, 0.001, 0.0, 0.0, 3.0};
    static f32 maxDecay;
    f32 ermsLimited, iqMaxAllowed, deltaIq;

    if (0.0 == integ_gain)  // 为0时，oneCycleProtectionParams.accumulator为清零。
    {
        integ_gain = 0.00004;
    }
    oneCycleProtectionParams.integGain = integ_gain * OutputProcess.SlowLoopSamplePeriod * 600;

    oneCycleProtectionParams.maxLimit  = 3.0 - maxDecay;

    if ((OK == InputProcess.MediumVoltageStatus)
        && (integ_gain >= 0.00005)
       )
    { 
        maxDecay = LPF_T(2.0, maxDecay, 0.15, OutputProcess.SlowLoopSamplePeriod);
    }
    else
    {
        oneCycleProtectionParams.accumulator = 3.0;
        maxDecay = 0.0;
    }

    if (erms < 0.60)
    {
        ermsLimited = 0.60;
    }
    else
    {
        ermsLimited = erms;
    }

    // calculate maximum allowable reactive current
    iqMaxAllowed = 1.1 * iSPScaler * (0.05 + ktr * id * id) / ermsLimited;
    iqMaxAllowed1 = iqMaxAllowed;

    // calculate excessive reactive current
    deltaIq = iqMaxAllowed - fabs(iq);

    InputProcess.ExcessReactiveCurrent = deltaIq;

    {
        struct REGULATOR_STR oneCycleProtect;

        oneCycleProtect.input = deltaIq;
        oneCycleProtect.pi = &oneCycleProtectionParams;
        oneCycleProtect.enable = enable;
     ////   RegulatorCalc(&oneCycleProtect);
        return oneCycleProtect.out;
    }

}


f32 powerDelta, inputPower, outputPower;
 f32 tripLevel;
*/

#define FaultCheckRate  SLOW_LOOP_TIME   // 
//==============================================================================
//
// 变频器损耗过大故障检测
//
//============================================================================== 
/*
void ExcessiveDriveLossesDetection(void)
{
    static struct PiDataType driveExcessiveLossParams = {1.0};
    bool alarmFlag = false, driveExcessiveLossEnable = false;
    f32 limit = 0.07, tripDelay = 1.5;// 持续时间超过1.5S
    static f32 timer;
    //static f32 tripLevel;

    static f32 inputPowerInitValue;
    static f32 decayCurve;
    static f32 powerupCount;
    static f32 decayRate = 4.0;

    //f32 powerDelta, inputPower, outputPower;
    

    driveExcessiveLossParams.integGain = 9.63 * SLOW_LOOP_TIME;
    driveExcessiveLossEnable = ((InputProcess.Enable || (OK == InputProcess.MediumVoltageStatus)
        && (0.0 != inputProtectMenu.excessLossIdle)));

    inputPower = InputProcess.AveragePower;

    // convert PU Output power to PU input power
    outputPower = (OutputProcess.AveragePower * motorPara.ratingCurrent * motorPara.ratingVoltage)
        / (driveParameterMenu.ratingInputCurrent * driveParameterMenu.ratingInputVoltage);

    powerDelta = inputPower - outputPower;
    powerDelta = (powerDelta < 0.0) ? 0.0 : powerDelta;

    // Drive Losses in PU input power
    driveLosses = powerDelta;

    // If drive is in idle state lower required trip limits
    if (IDLE_STATE == DriveControl.State)
    {
        if (OK != InputProcess.MediumVoltageStatus)
        {
            inputPowerInitValue = 3.0;
            decayCurve = 1.0;
            powerupCount = 0.0;
            decayRate = 6.67;
        }
        else
        {
            powerupCount += SLOW_LOOP_TIME;  // 高压上电1S以后
            if (powerupCount > 1.0)
            {
                powerupCount = 1.01;
                decayRate = 20.0;
            }
        }

        decayCurve = LPF_GAIN(0.0, decayCurve, (1.0 - decayRate * SLOW_LOOP_TIME));

        // limit for drive when in idle state
        limit = inputProtectMenu.excessLossIdle + decayCurve * inputPowerInitValue;
        driveExcessiveLossParams.integGain *= 100.0;            // increase gain 100 fold for idle state
      //  tripDelay = 0.01;   //此处暂时改为默认的1.5S 进行测试
    }
    else
    {
        inputPowerInitValue = fabs(inputPower);
        limit = inputProtectMenu.excessLossRunning;    // limit for drive while running
        decayCurve = 1.0;
    }
    
    {
        struct REGULATOR_STR excessiveLossProtect;

        excessiveLossProtect.input = powerDelta - limit;
        excessiveLossProtect.pi = &driveExcessiveLossParams;
        excessiveLossProtect.enable = driveExcessiveLossEnable;
      /////  RegulatorCalc(&excessiveLossProtect);
        tripLevel = excessiveLossProtect.out;
    }

    // Has trip delay been exhausted?
    if (tripLevel > 0.999)
    {
        if ((timer += SLOW_LOOP_TIME) > tripDelay)
        {
            alarmFlag = true;
        }
    }
    //else if ((timer -= SLOW_LOOP_TIME) < 0.0)
    else
    {
        alarmFlag = false;
        timer -= SLOW_LOOP_TIME	;
        if(timer < 0.0)
        	{
        	  timer = 0;
        	}
      //  timer = 0.0;
       
    }

    excessiveLossFault = alarmFlag;
	
    if ((0.0 == inputProtectMenu.excessLossIdle)) // FA-58设置为0，不进行变频器损耗过大故障检测。
    {
        excessiveLossFault = false;
    }
}
*/
#endif







#elif 1

f32 InputPower;

void InitInputProcessing(void){}
void InFastLoopControl(void){}


void InSlowLoopControl(void)
{
    InputProcess.Ed = 1.0;
    inputVolFil = 1.0;
}


#endif




