/*
 * Mot07_MotorParamCal.h
 *
 *  Created on: 2017楠烇拷8閺堬拷29閺冿拷
 *      Author: zhuxc
 */
 #ifndef Mot07_MotorParamCal_H
#define Mot07_MotorParamCal_H
  
  
/*********************************基本参数定义*************************************************/
typedef	struct
{										 
 #if(FLOAT_USE == 1)
/*-----------------------------------------------------------------------------------------*/
    float  fMotPulse;      // Motor Encoder PulseNo         [p/rev]     [p/360deg]
    float  fFbPulse;       // Feedback PulseNo (Menc/Fenc)      [p/rev]     [p/360deg]
    LONG   XfbPulse1;      // Feedback PulseNo for I/F          [p/rev]     [p/mm]
    LONG   XfbPulse2;      // Feedback PulseNo for I/F          [p/rev]     [p/pitch]
/*-----------------------------------------------------------------------------------------*/
    float  fKmotpls;       // Motor Encoder Pulse Factor        [rad/p]     [m/p]
    float  fKfbpls;        // FB Pulse Factor (Menc/Fenc)       [rad/p]     [m/p]
    float  fKeangle;       // 电角度转换系数       [Erad/Mrad] [Erad/m]    */
/*-----------------------------------------------------------------------------------------*/
    float  fRatSpd;        // RatedSpeed                        [rad/sec]   [m/sec]
    float  fExpSpd;        // Motor Speed   Exponent            [-]         [-]
    float  fExpTrq;        // Motor Torque  Exponent            [-]         [-]
    float  fExpMotW;       // Motor Power   Exponent            [-]         [-]
    float  fExpJmot;       // Motor Inertia Exponent            [-]         [-]
/*-----------------------------------------------------------------------------------------*/
    float  fOvrSpd;        // OverSpeed                     [rad/sec]   [m/sec]
    float  fMaxTrq;        // Max.Torque                        [Nm]        [N]
    float  fJmot;          // Motor Rotor Inertia               [kg*m^2]    [kg]
    float  fMotEmf;        // Motor EMF Constant                [Vrms/r/s]  [Vrms/m/s]
    float  fOvrPspd;       // Pulse Speed at OvrSpd         [p/sec]     [p/sec]
    float  fMaxPspd;       // Pulse Speed at MaxSpd         [p/sec]     [p/sec]
    float  fNorspdConv;    // Normalized Speed Trans Factor [r/min,mm/s --> NorSpd]
    float  fKMotSpdConv;   // 速度换算系数          [0.1r/min,0.1mm/s->p/ms]
	float  fKConvLoadSpd;  // Normalized Speed Trans Factor [r/min,mm/s --> NorSpd]
    float  fKnorspd;       // Normalized Speed Trans Factor [r/min,mm/s --> NorSpd]

    float  VCOffset;        //母线电压偏置                    [PnE10(V) -->Bprm.VdetMax]
    float   VCGain;         //母线增益系数
#else
    LONG    VCOffset;
#endif
    LONG    FbPulse;        // Feedback PulseNo (Menc/Fenc)      [p/rev]     [p/360deg]
    LONG	MotPulse;       // Motor Encoder PulseNo         [p/rev]     [p/360deg]
    KSGAIN	Kfbpls;         // FB Pulse Factor (Menc/Fenc)       [rad/p]     [m/p]
    KSGAIN	Kmotpls;        // Motor Encoder Pulse Factor        [rad/p]     [m/p]
	KSGAIN  KmotplsFC;
	float   fKmotplsFC;
    KSGAIN	Keangle;        // 电角度转换系数      [Erad/Mrad] [Erad/m]    */
    KSGAIN	RatSpd;         // RatedSpeed                        [rad/sec]   [m/sec]
    KSGAIN	OvrSpd;         // OverSpeed                     [rad/sec]   [m/sec]
    KSGAIN	MaxAcc;         // Max.Acceleration                 [rad/s^2]   [m/s^2]
    KSGAIN	MaxTrq;         // Max.Torque                       [Nm]        [N]
    KSGAIN	MaxCur;         // Max.Current                      [A]         [A]
    float  fMaxCur;         // Max.Current                      [A]         [A]

    KSGAIN	Vdc;		    // DC Voltage                       [V]         [V]
    float   fVdc;           // DC Voltage                       [V]         [V]
    KSGAIN	MotW;           // Motor Power                      [W]         [W]
    KSGAIN	MotR;           // Motor Resistance                 [ohm]       [ohm]
    float  fMotR;           // Motor Resistance                 [ohm]       [ohm]
    KSGAIN	MotLd;          // Motor d-axis Inductance          [H]         [H]
    KSGAIN  MotLq;          // Motor q-axis Inductance          [H]         [H]
    float  fMotLd;          // Motor d-axis Inductance          [H]         [H]
    float  fMotLq;          // Motor q-axis Inductance          [H]         [H]
    KSGAIN  MotLdb;         // Motor Inductance for DbAlmChk    [H]         [H]
    KSGAIN  MotEmf;         // Motor EMF Constant               [Vrms/r/s]  [Vrms/m/s]
    KSGAIN  Jmot;           // Motor Rotor Inertia              [kg*m^2]    [kg]
    /*-------------------------------------------------------------------------------------------*/
    KSGAIN  OvrPspd;        // Pulse Speed at OvrSpd            [p/sec]     [p/sec]
    KSGAIN  MaxPspd;        // Pulse Speed at MaxSpd            [p/sec]     [p/sec]
    KSGAIN  Knorspd;        // Normalized Speed Trans Factor    [r/min,mm/s --> NorSpd]
    KSGAIN  NorspdConv;     // Normalized Speed Trans Factor    [r/min,mm/s --> NorSpd]
    KSGAIN  KMotSpdConv;    // 速度换算系数          [0.1r/min,0.1mm/s->p/ms]
	KSGAIN  KConvLoadSpd;
/*-------------------------------------------------------------------------------------------*/
    KSGAIN  ExpSpd;                 // Motor Speed   Exponent           [-]         [-]
    KSGAIN  ExpTrq;                 // Motor Torque  Exponent           [-]         [-]
    KSGAIN  ExpMotW;                // Motor Power   Exponent           [-]         [-]
    KSGAIN  ExpJmot;                // Motor Inertia Exponent           [-]         [-]
/*------------------------------------------------------------------------------------------*/
    USHORT  PerMaxTrq;              // Max.  Torque Percent =300        [%]         [%]
    float   fPerMaxTrq;             // Max.  Torque Percent =300        [%]         [%]

    USHORT  PerMaxIee;
    USHORT  PerOvrSpd;              // Over  Speed Percent              [0.01%]     [0.01%]
    LONG    NorOvrSpd;              // Over  Speed Normalized           [2^24]      [2^24]
    LONG    NorMaxSpd;              // Max.  Speed Normalized           [2^24/OS]   [2^24/OS]
    LONG    NorRatSpd;              // Rated Speed Normalized           [2^24/OS]   [2^24/OS]
    LONG    NorRatSpd1;             // Rated Speed Normalized           [15000/OS]
/*------------------------------------------------------------------------------------------*/
    LONG    AmpMotWatRatio;         // (驱动器容量  / 电机容量 ) * 2^16
    LONG    AmpMotImaxRatio;        // (驱动器最大电流 / 电机最大电流) * 2^16
/*------------------------------------------------------------------------------------------*/
    UCHAR   AmpInVcode;             // Amp Input  Volt Code             [-]         [-]
    UCHAR   AmpOutVcode;            // Amp Output Volt Code PnE11查表 [-]         [-]
    UCHAR   AmpDcinType;            // Amp DC Input Type (AC:0, DC:1)   [-]         [-]
    UCHAR   AmpOut2VType;           // Amp 倍压器规格(TRUE/FALSE)        [-]         [-]
    USHORT  AmpUnVolt;              // Amp Volt for UnXXX Monitor       [V]         [V]
    ULONG   AmpDCVolt;              // Amp Volt for UnXXX Monitor       [V]         [V]
/*------------------------------------------------------------------------------------------*/
    UCHAR   MotVcode;               // Motor Volt Code  PnF00.h& 0x0F   [-]         [-]
    UCHAR   MaxVel;                 // Max Velocity                     [100r/min]  [100mm/s]
    USHORT  MotUnVolt;              // Motor Volt For UnXXX Monitor     [V]         [V]
    USHORT  VdetMax;                // Amp Volt detect at max input     [data/MaxV] [data/MaxV] 检测电路最大电压对应的标幺值
    USHORT  VdetAdMax;              // Amp Volt AD detect at max input  [data/MaxV] [data/MaxV] 检测电路最大电压对应的AD值
/*-------------------------------------------------------------------------------------------*/
} BPRMDAT;
 
extern	BPRMDAT	Bprm;					 
extern void BprmCommonMotorParamCal( void );
extern void fBprmCommonMotorParamCal( void );
extern void BprmRotaryMotorParamCal( void );
 
#endif
