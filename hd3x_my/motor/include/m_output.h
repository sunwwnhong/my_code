//==================================================================================================
//
// 输出处理，
// 定子磁链定向
// 
// 快环，慢环
// 
//
// Time-stamp: <2011-3-10 14:59:47  author, 0000>
//
//==================================================================================================


#ifndef __M_OUTPUT_H__
#define __M_OUTPUT_H__



#include "main.h"
#include "m_control.h" 
#include "m_stateControl.h"
#include "m_torqueLimitLogic.h"


#define UNIT_TIME               1000000.0    //时间单位0.000001s(1us)
#define UNIT_FREQUENCY          1.0         //频率单位0.1Hz


extern u16 smControl;
extern f32 pwmT;
extern u16 motorControlMode;



//===============================================================================
// AD7606 AD采样的通道
extern int16 adResult[];

#define AD7606_IU       (adResult[0])
#define AD7606_IV       (adResult[1])
#define AD7606_OUT_VU   (adResult[2])
#define AD7606_OUT_VV   (adResult[3])
#define AD7606_OUT_VW   (adResult[4])
#define AD7606_IU2      (adResult[5])
#define AD7606_IV2      (adResult[6])
#define AD7606_IW2      (adResult[7])
//===============================================================================



//===============================================================================
// HD3x，采样板，AD7606 AD采样的通道
extern u16 adResultFpga[];
//===============================================================================


//===============================================================================
// 双机并联
//extern s32 adResultParaInv[];
//#define AD7606_IU_PARA_INV (adResultParaInv[0])         // 并机电流
//#define AD7606_IV_PARA_INV (adResultParaInv[1])         // 并机电流
//===============================================================================



//===============================================================================
//DSP AD采样的通道
#define DSP_AD_IU1          (AdcRegs.ADCRESULT0 >> 4)       //
#define DSP_AD_UPO          (AdcRegs.ADCRESULT1 >> 4)       //
#define DSP_AD_UR           (AdcRegs.ADCRESULT2 >> 4)       //
#define DSP_AD_UT           (AdcRegs.ADCRESULT3 >> 4)       //
#define DSP_AD_IW1          (AdcRegs.ADCRESULT4 >> 4)       //
#define DSP_AD_INTER_U      (AdcRegs.ADCRESULT5 >> 4)       //
#define DSP_AD_INTER_V      (AdcRegs.ADCRESULT6 >> 4)       //
#define DSP_AD_INTER_W      (AdcRegs.ADCRESULT7 >> 4)       //
#define DSP_AD_IV1          (AdcRegs.ADCRESULT8 >> 4)       //
#define DSP_AD_UNO          (AdcRegs.ADCRESULT9 >> 4)       //
#define DSP_AD_US           (AdcRegs.ADCRESULT10>> 4)       //
#define DSP_AD_NTC1         (AdcRegs.ADCRESULT11>> 4)       //
#define DSP_AD_NTC2         (AdcRegs.ADCRESULT12>> 4)       //
#define DSP_AD_NTC3         (AdcRegs.ADCRESULT13>> 4)       //
#define DSP_AD_AI1          (AdcRegs.ADCRESULT14>> 4)       //
#define DSP_AD_AI2          (AdcRegs.ADCRESULT15>> 4)       //
//===============================================================================







// 单元类型
enum CELL_TYPE
{
    CELL_TYPE_690 = 0,               // 690V两电平二极管整流单元
    CELL_TYPE_AFE_1140 = 1,          // 1140V三电平可控整流单元，母线电压1800V
    CELL_TYPE_690_DURIAN = 2,       // 690V两电平榴莲单元
    CELL_TYPE_1140_QERATUD = 3          // 1140V三电平四象限
};



// 同步机控制模式
enum SmControlModeType
{
    DISABLED,           // 0
    TRANSITION,         // 1
    ENABLED             // 2
};




//==============================================================================
// 电机参数
typedef struct
{
//--------------------------------------------------------------------
// 实际值
    u16 motorType;          // F1-00  电机类型选择
    f32 ratingPower;        // F1-01  电机额定功率，kW
    f32 ratingVoltage;      // F1-02  电机额定电压, V
    f32 ratingCurrent;      // F1-03  电机额定电流，A
    f32 ratingFrq;          // F1-04  电机额定频率, Hz
    f32 ratingSpeed;        // F1-05  电机额定转速, rpm
    f32 rsOhms;             // 定子电阻，欧姆
    f32 rrOhms;             // 转子电阻，欧姆
    f32 iNoloadA;           // 空载电流，峰值，A

//--------------------------------------------------------------------
// 异步机PU值
    f32 rs;                 // F1-06  异步机定子电阻，pu
    f32 rr;                 // F1-07  异步机转子电阻，pu
    f32 lSigma;             // F1-08  漏感，pu
    f32 lm;                 // F1-09  异步机互感抗，pu
    f32 ls;                 // 异步机，定子电感，pu
    f32 lr;                 // 异步机，转子电感，pu
    f32 iNoload;            // F1-10  异步机空载电流，pu
	f32 IfModeRefCur;		// F1-11  IF模式设定电流，pu
	f32 PMLowSpdIdAddCur;	// F1-12  同步机低速d轴注入电流，pu

//--------------------------------------------------------------------
// PU值1代表的实际值
    f32 zPuOne;             // 额定电抗，欧姆
    f32 lPuOne;             // 额定电感, H
    f32 fPuOne;             // 额定频率，Hz
    
//--------------------------------------------------------------------
// 其它
    f32 fPuOmegaOne;        // fPuOne * 2*pi
    f32 iFPuOmegaOne;       // 1/fPuOmegaOne

    f32 lrDivLm;            // Lr/Lm
    f32 lLou;
    
//同步机PU值，暂时放着
    f32 smRs;               // F1-16  同步机定子电阻，pu
    f32 smLd;               // F1-17  同步机d轴电感，pu
    f32 smLq;               // F1-18  同步机q轴电感，pu 
    f32 smCoeff;            // F1-20  同步机反电动势系数

    f32 inertia;
} MotorPara;
extern MotorPara motorPara;
//==============================================================================

typedef struct COFF_FILTER1STF32_STRUCT_DEF{
	f32	Input;		//本拍输入值
	f32	InputLast;	//前一拍输入值
	f32	Out;		//前一拍输出值
	f32	Coff;		// 双线性变换滤波器系数	1/( 2*Torr/Ts + 1 ) = Ts / ( 2*Tor + Ts)
}COFF_FILTER1STF32_STRUCT; //一阶惯性滤波用的数据结构,用于f32型数据



//==============================================================================
typedef struct
{
    f32 u0;         // 采样的原始数据，只经过scaler，没有经过其它处理。HD9x，相电压；HD3x, 线电压
    f32 v0;
    f32 w0;
    
    f32 u;          // 最终使用值
    f32 v;
    f32 w;

    f32 ufpga;
    f32 vfpga;
    f32 wfpga;
    f32 ufpga0;
    f32 vfpga0;
    f32 zerodriftURSum;
    f32 zerodriftUTSum;
    f32 e0Fpga;
    f32 e0;         // zero sequence

    f32 zerodriftUR;// 零漂
    f32 zerodriftUT;// 零漂
    f32 scaler;     // 系数
} THREE_PHASE_SAMPLE;
extern THREE_PHASE_SAMPLE inCurData;
extern THREE_PHASE_SAMPLE inVolData;
extern THREE_PHASE_SAMPLE outVolData;

typedef struct
{
	f32 up;      // 上半部母线电压
	f32 down;    // 下半部母线电压
	f32 add;     // 总的母线电压
	f32 diff;    // 上部-下部母线电压差
	f32 scaler;  // 系数
} BUS_VOTAGE;
extern BUS_VOTAGE invbusVoltage;
void GetVoltageResult(void);
//==============================================================================




//==============================================================================
typedef struct
{
    f32 u0;         // 采样的原始数据，只经过scaler，没有经过其它处理。
    f32 v0;
    f32 w0;
    
    f32 u;          // 最后使用的值
    f32 v;
    f32 w;
    
    f32 offsetU;    // U相零漂
    f32 offsetV;    // V相零漂

    // 双机并联:PARA_WAY_SEL = 0 单机电流；PARA_WAY_SEL = 1 并机电流； 
    f32 u0ParaInv;
    f32 v0ParaInv;
    f32 w0ParaInv;
    
    f32 uParaInv;
    f32 vParaInv;
    f32 wParaInv;
    
    f32 offsetUParaInv;
    f32 offsetVParaInv;
    
    f32 scaler;     // 系数
} THREE_PHASE_CURRENT_SAMPLE;
extern THREE_PHASE_CURRENT_SAMPLE outCurData;
//==============================================================================




//==============================================================================
// AD_RESULT -> (极性调整) -> i0 -> (零漂处理) -> i1 -> (增益偏差处理) -> i2
// -> (*转换系数，得到Q24) -> i3 -> (防止饱和) -> i4 -> (剔除毛刺处理) -> i
// 最后没有这样使用
struct AD_CURRENT_DATA
{
    f32 i0;       // Q24, 零漂处理前
    f32 i1;       // 零漂处理后
    f32 i2;
    f32 i3;
    f32 i4;
    f32 i5;
    f32 offset;

    f32 i;
};
struct IUVW_DATA
{
    struct AD_CURRENT_DATA iu;
    struct AD_CURRENT_DATA iv;
    struct AD_CURRENT_DATA iw;

    f32 scaler;
};
//==============================================================================




//==============================================================================
// 电机控制模式
enum Algorithims
{
    IM_SVC1,    // 0，无速度传感器矢量控制，SVC1，异步机
    IM_FVC,     // 1，有速度传感器矢量控制，异步机
    IM_SVC2,    // 2，电压型开环矢量，SVC2，异步机
    
    PURE_VF,    // 3，标准(纯粹的)VF，一般调试使用
    SIN_ONLY,   // 4，仅发送正弦波，FPGA发PWM调试使用
    OLTM,       // 5，(开环)测试模式
    
    SM_SVC,     // 6，无速度传感器矢量控制，励磁同步机
    SM_FVC,     // 7, 有速度传感器矢量控制，励磁同步机
    SMDC_SVC,   // 8, 无速度传感器矢量控制，直流无刷励磁同步机
    PMSM_SVC,    // 9, 永磁同步机
    PMSM_FVC,   //10
    IM_SVC3,	//11 异步电机SVC3
    IM_SVC4     //12 异步电机SVC4
};
//==============================================================================






//==============================================================================
struct OutputProcessType                    // Output Process Data Structure
{
    enum Algorithims ControlAlgorithm;  // 0 Control Algorithm in use
    enum LimitStates LimitUsed;         // 1 使用了哪一种转矩限幅

    bool   Enable;                      // 2 使能。
    bool   ZeroSpeed;                   // 3 电机是否在零速
    bool   TorqueRegEnable;             // 4 速度环是否使能标志
    bool   SpeedRollback;               // 5 Speed Rollback flag
    bool   FluxRollback;                // 6 Flux Rollback flag
    bool   CellImbalance;               // 7 单元不对称
    bool   NeutralShift;                // 8 中性点偏移标志
    bool   BrakingEnable;               // 9 叠频制动使能
    bool   Braking;                     // 10 是否处于叠频制动 ->DualFrequencyAndRegenBraking()
    bool   SpinningLoadEnable;          // 11 飞车启动使能
    bool   DoFilterComp;                // 12 输出滤波器使能标志
    bool   HighStartingTorqueEnable;    // 13 高启动转矩模式使能

    f32 Ids;                            // 7 *2 Ids反馈
    f32 Iqs;                            // 8 *2 Iqs反馈
    f32 IdsRef;                         // 9 *2 Ids给定
    f32 IqsRef;                         // 10*2 Iqs给定
    f32 FluxDS;                         // 11*2 Flux DS反馈
    f32 FluxQS;                         // 12*2 Flux QS反馈
    f32 VdsRef;                         // 13*2 Vds给定，id电流环输出
    f32 VqsRef;                         // 14*2 Vqs给定，iq电流环输出
    f32 IqsMax;                         // 15*2 速度环上限
    f32 IqsMin;                         // 16*2 速度环下限
    f32 Frequency;                      // 17*2 output frequency, rad/sec, 同步频率
    f32 FrequencyFiltered;              // 18*2 output frequency 在一个速度环周期的平均值
    f32 PerUnitSpeedReference;          // 19*2 Speed reference / rated speed
    f32 SlipFrequency;                  // 20*2 slip frequency, rad/sec
    f32 MotorSpeed;                     // 21*2 motor speed (frequency - slip), rad/sec
    f32 MotorSpeedFiltered;             // 22*2 motor speed filtered, rad/sec
    f32 MotorSpeedPU;                   // 23*2 Motor speed Per Unit
    f32 MotorSpeedFilteredPU;           // 24*2 Motor speed filtered Per Unit 
    f32 WsFil;                          // 25*2 Ws filtered
    f32 WsFilPu;                        // 26*2 Ws filtered, PU
    f32 FluxDSFil;                      // 27*2 flux DS filtered
    f32 IdsFil;                         // 28*2 Ids filtered
    f32 IqsFil;                         // 29*2 Iqs filtered
    f32 FieldWeakeningLimit;            // 30*2 field weakening limit
    f32 OverSpeedLimit;                 // 31*2 Over Speed Limit Trip value
    f32 ZeroSpeedLimit;                 // 32*2 Zero Speed Limit value
    f32 CellOverLoadLimit;              // 33*2 Cell current overload limit
    f32 StatorResistance;               // 34*2 stator resistance
    f32 rsvd1;                          // 35*2 
    f32 rsvd2;                          // 36*2 
    f32 DeltaS;                         // 37*2 转子角度 0-2pi对应0-360度
    f32 DeltaSBackEMF;                  // 38*2 output vector agle used to calculate back EMF
    f32 FastLoopFrequency;              // 39*2 快环频率
    f32 FastLoopSamplePeriod;           // 40*2 Fast Loop Sample period
    f32 SlowLoopSamplePeriod;           // 41*2 Slow Loop Sample period
    f32 RatedFrequency;                 // 42*2 Rated motor speed in rad/sec (electrical).
    f32 iRatedFrequency;                // 43*2 1.0/RatedFrequency
    f32 SyncSpeed;                      // 44*2 Rated motor speed in RPM (synchronous speed)
    f32 SlipRated;                      // 45*2 rad/sec
    f32 MinimumSpeedReference;          // 46*2 Minimum speed reference
    f32 EncoderSpeed;                   // 47*2 Speed feedback from encoder, rad/sec
    f32 PeakVoltageClampLimit;          // 48*2 Peak Voltage Clamp Limit
    f32 PeakReductA;                    // 49*2 Peak reduction gain A phase
    f32 PeakReductB;                    // 50*2 Peak reduction gain B phase
    f32 PeakReductC;                    // 51*2 Peak reduction gain C phase
    f32 PeakReductKi;                   // 52*2 Peak reduction gain 1/2 * max(Ka, Kb, Kc)
    f32 PeakReductMax1;                 // 53*2 方便 PeakReductionCalc() 调用
    f32 UpdateSteps;                    // 54*2 number of interpolation steps for modulator, 已经没有使用
    f32 iStep;                          // 55*2 1.0/OutputProcess.UpdateSteps，方便使用
    f32 MaximiumLoadCurrent;            // 56*2 最大输出电流，根据转矩上限计算的。
    f32 MaximumTorqueCurrent;           // 57*2 根据过载和单元额定电流得到的最大转矩电流
    f32 MotorVoltageClampLimit;         // 58*2 motor voltage clamp limit 
    f32 MotorVoltage;                   // 59*2 motor voltage
    f32 BackEMF;                        // 60*2 motor back EMF
    f32 TotalCurrent;                   // 61*2 输出电流
    f32 TotalCurrentFil;                // 62*2 Filtered output current amplitude
    f32 MotorTorque;                    // 63*2 Motor Torque
    f32 AveragePower;                   // 64*2 average power out of drive
    f32 ShaftPower;                     // 65*2 Power to motor
    f32 PowerFactor;                    // 66*2 Power factor
    f32 CurrentRegIntegBraking;         // 67*2 叠频制动时的电流环Ki
    f32 CurrentRegInteg;                // 68*2 电流环Ki
    f32 SpeedRegInteg;                  // 69*2 速度环Ki
    f32 SpeedFilterGain;                // 70*2 速度滤波gain
    f32 FluxRegInteg;                   // 71*2 磁链环Ki
    f32 FluxFilterGain;                 // 72*2 磁链滤波gain
    f32 IdNegSeq;                       // 73*2 输出电流的负序分量
    f32 IqNegSeq;                       // 74*2 输出电流的负序分量
    f32 INegSeqTotal;                   // 75*2 输出电流的负序分量的有效值
    f32 Y0Avg;                          // 76*2 Zero Sequence Volt-secs (filtered), OutputGroundFault()使用
    f32 E0Avg;                          // 77*2 电机电压零序分量，滤波后
    f32 Y0DC;                           // 78*2 Zero Sequence motor voltage DC component
    f32 RatedLosses;                    // 79*2 rated motor losses
    f32 ThermalCapacity;                // 80*2 Motor Thermal Capacity in J/kW (J/Hp)
    f32 MaxMotorInertia;                // 81*2 maximum calculated inertia for TOL
    f32 MotorTorqueLimit;               // 82*2 (电动)转矩上限，功能码 F2-10 设定
    f32 MotorRegenLimit;                // 83*2 (发电)转矩上限，功能码 F2-12 设定
    f32 TolAccumulator;                 // 84*2 TOL integrator for inverse time
    f32 TolTimer;                       // 85*2 TOL time to trip accumulator
    f32 FilterCurrentIa;                // 86*2 Filter current in A phase
    f32 FilterCurrentIb;                // 87*2 Filter current in B phase
    f32 FilterCurrentIc;                // 88*2 Filter current in C phase
    f32 IModelFilterGain;               // 89*2 low pass filter gain for current model for low freq comp
    f32 DampingConstant;                // 90*2 Output filter damping constant
    f32 VDDampRef;                      // 91*2 D - axis damping voltage
    f32 VQDampRef;                      // 92*2 Q - axis damping voltage
    f32 FilterCurrentScaler;            // 93*2 Filter Current Scaler 
    f32 TOLZeroPercentPoint;            // 94*2 First point of curve
    f32 TOLTenPercentPoint;             // 95*2 Second point of curve
    f32 TOLSeventeenPercentPoint;       // 96*2 Third point of curve
    f32 TOLTwentyFivePercentPoint;      // 97*2 Forth point of curve
    f32 TOLFiftyPercentPoint;           // 98*2 Fifth point of curve
    f32 TOLHundredPercentPoint;         // 99*2 Sixth point of curve
    f32 IqsffRampRate;                  // 100*2 Iqs feed forward ramp rate
    f32 Iqsff;                          // 101*2 Iqs feed forward

    bool FluxPIRegulatorEnable;         // 204  Flux PI regulator enable
    bool SpeedRegulatorEnable;          // 205  Speed regulator enable
    bool RampHold;                      // 206  Flag to hold speed ramp output
    bool SMFieldEnable;                 // 207  投励命令
    s16 SlowLoopSamplingFactor;         // 208  Determines the Fast/Slow Loop sub-sampling factor

    f32 Droop;                          // 105*2 amount of speed droop applied, rad/sec
    f32 DroopPU;                        // 106*2 Speed Droop in PU rated frequency
    f32 FrequencyPU;                    // 107*2 Frequency in PU rated frequency
    f32 PeakVoltageClampLimitFilt;      // 108*2 Peak Voltage Clamp Limit filtered
    f32 TorqueCommand;                  // 109*2 Command for torque control
    f32 IqsRefRamp;                     // 110*2 Torque ramping at torque ramp rate
    
    bool   OverModulationEnable;        // 222 over-modulation enable for Micro Harmony (or others TBD)
    bool   ZeroTorque;                  // 223 Flag indicates torque ramp is at zero
    bool   TorqueRampHold;              // 224 Flag to hold off torque ramp
    bool   usePllAndDroop;              // 225 Flag to indicate the PLL and droop should be used
    bool   DeadTimeCompEnable;          // 226 死区补偿使能标志
    
    f32 DeadTimeComp;                   // 228 死区补偿时间

    bool   FluxFeedbackError;           // 230 Indicated FluxQS calculation error fault
    bool   RegenBrakingEnable;          // 231 Flag indicating condition for regen braking

  //  f32 SynchMotorFieldCurrent;         // 116*2 Synch Motor Field Current
    f32 IfieldFF;                       // 117*2 Feed forward with torque current saliency constant multiplier
    u16 SMDCMode;                       // 118*2 SMDC控制模式 
    f32 IdsRef1;                        // 119*2 SMDC时，初始励磁电流
    f32 IdsRef2;                        // 120*2 励磁电流环输出
    f32 SMCFluxRegulatorOutput;         // 121*2 励磁同步机的磁链环输出
    f32 IqGain;                         // 122*2 Iq gain
    f32 IqsRated;                       // 123*2 motor rated torque current
    f32 FastLoopFrequencyPU;            // 124 快环采样频率标幺值
    f32 FastLoopSamplePeriodPU;         // 125 快环采样时间标幺值
    f32 BaseTimeMotorRatePU;            // 126 标幺的时间基准值
};
extern struct OutputProcessType OutputProcess;
//==============================================================================



//==============================================================================
// 传递给FPGA的电压指令
struct VOL_CMD_TO_FPGA
{   // 与写给FPGA的顺序一致!
    int16 va;
    int16 vaPrime;
    int16 vb;
    int16 vbPrime;
    int16 vc;
    int16 vcPrime;

    int16 vaStep;
    int16 vaPrimeStep;
    int16 vbStep;
    int16 vbPrimeStep;
    int16 vcStep;
    int16 vcPrimeStep;

    u16 enable; // 给FPGA的使能信号
};
extern struct VOL_CMD_TO_FPGA outputVol;
//==============================================================================



//==============================================================================
struct OUTPUT_VOLTAGE_A
{
    f32 va;
    f32 vaPrime;
    f32 vb;
    f32 vbPrime;
    f32 vc;
    f32 vcPrime;

    f32 vaStep;
    f32 vaPrimeStep;
    f32 vbStep;
    f32 vbPrimeStep;
    f32 vcStep;
    f32 vcPrimeStep;
};
extern struct OUTPUT_VOLTAGE_A outputVolA;
//==============================================================================
struct VFSHOCKCTL_DATA
{
	f32 idlpffildata;      //    D轴低通输出
    f32 iqlpffildata;      //    Q轴低通输出
    f32 idlpfGain;         //    低通滤波器系数
    f32 shockCtlkd;         //     D轴系数比例设定值
    f32 shockCrlkq;          //   Q轴系数比例设定值
    f32 ierrhpfnow;         //     
    f32 ierrhpffildata;      //   高通滤波器输出，提取交流分量
    f32 ierrhpfgain;        //    高通滤波器系数设定
    f32 shockCtldeltaFrq;    // 振荡频率调节输出
	f32 shockCtlfrqgain;    //   振荡调节比例
    f32 shockCtlfrqgainSet;  // 振荡频率调节比例设定值
    f32 shcokfrqup;           //谐振频率上限
	f32 shockfrqdown;            //谐振频率下限

};
extern struct VFSHOCKCTL_DATA  vfshockdata;
//==============================================================================
// 电机控制模式
enum ParaInvMasterSlaveSelect
{
    ONE_INV,            // 0:单机
    PARA_INV_MASTER,    // 1:主机
    PARA_INV_SLAVE      // 2:从机
};
//==============================================================================





//void UpdateFpgaVoltageDataSinOnly(void);
void InitOutputProcessing(void);
void OutputFastLoopRfoc(void);
void OutputFastLoopSfoc(void);
void OutputProcessSlowLoop(void);
void OLTMDeal(void);
//void SaveEnergyCalc(void);





#endif  //__M_OUTPUT_H__



