/*
 * Mot01_ScanA.h
 *
 *  Created on: 2017楠烇拷2閺堬拷28閺冿拷
 *      Author: zhuxc
 */
 #ifndef Mot01_ScanA_H
#define Mot01_ScanA_H
 
  
  
  
/**********************************ScanA 输入变量定义****************************************/
typedef	struct
{
        SHORT	IqRefMon;				// q轴电流指令监控             [15000/Imax]
        SHORT	IdRefMon;				// d轴电流指令监控             [15000/Imax]
        LONG	IqRefMon1;				// q轴电流指令监控             [15000/Imax]
        LONG	IdRefMon1;				// d轴电流指令监控             [15000/Imax]
 		SHORT	IdRef;					// d轴电流指令                [15000/Imax]
		SHORT	IqRef;					// q轴电流指令                [15000/Imax]
 		SHORT	Pcmpd;					// 相位补偿（延迟补偿）           [65536/360deg]
		SHORT	Pcmps;					// 相位补偿（速度补偿计）      [65536/360deg]
 		SHORT	IqRefMon_l;				// q轴电流指令监控（上次值）    [15000/Imax]
		SHORT	IqRefMon_a;				// q轴电流指令监控（平均值）    [15000/Imax]
        ULONG   IeeSum;                 // 电流有效值之和
 		LONG	IqFbMon;				// q轴电流FB监控             [15000/Imax]
		LONG	IdFbMon;				// d轴电流FB监控             [15000/Imax]
        float   fIqFbMon;                
        float   fIdFbMon;                
        LONG    CurrentU;               // U相电流FB监控             [ADC采样值]
        LONG    CurrentV;               // V相电流FB监控             [ADC采样值]
        LONG    CurrentW;               // W相电流FB监控             [ADC采样值]
        float   Idc;                    // 母线电流FB监控            [ADC采样值]
        float   IdcFil;                 // 母线电流FB监控             [ADC采样值]

        LONG    IdcMon;                 // 母线电流FB监控             [ADC采样值]

        LONG    CurrentTmp;
        float   IeeMonitor;
        ULONG   Ctrl_Word;              // 对象字典6040
        ULONG   Stus_Word;              // 对象字典6041
        LONG    Targe_Pos;              // 对象字典607A
        LONG    Pulse_PosFB;            // 对象字典6064
        LONG    Actual_VelRPM;          //电机转速606C
        LONG    Profile_VelRPM;         //轮廓速度6081
        LONG    InterPos_CMD;           //插补位置指令60C1
        LONG    Pos_CMDVal;             //电机位置指令60FC
        LONG    Target_Vel;             //目标速度60FF
        LONG    Monitor1;
        LONG    Monitor2;
        LONG    Monitor3;
        LONG    Monitor4;
        LONG    Monitor5;
 		LONG	MotPos;		            // 电机位置(Ring)               [32bitRingPulse]
		LONG	dMotPos;				// 电机角度增量                   [pulse/ScanB]
		LONG	MotSpd;					// 转速控制输入、免调整控制和速度观测器的输入[2^24/OvrSpd]
		LONG    MotSpdFilt;                 // 转速控制输入、免调整控制和速度观测器的输入[2^24/OvrSpd]
        LONG    ABSMotSpd;
        LONG	MotSpdOld;				// 电机速度（前一拍）            [2^24/OvrSpd]
		LONG	AbsMotSpd;				// 电机速度绝对值              [2^24/OvrSpd]
        LONG    ORGDelta;               // 脉冲指令量

        /* 负载编码器与全闭环位置反馈相关变量 */
        LONG    FencPos;                /* Fenc  Position (Ring)        [32bitRingPulse]  */

        LONG    FencPosUnit;            /* 全闭环光栅尺脉冲累加计数             */
        LONG    dFencPosUnit;           /* 全闭环光栅尺脉冲增量（SCANB）             */
        LONG    MixFbkErr;              /* 光学尺混合偏差( 编码器单位 )                               */
        LONG    dMotPosUnit;             /* 光学尺混合偏差(用户单位)            [用户单位]              */
        LONG    dMotPosBUnit;             /* 光学尺混合偏差(用户单位)           [用户单位]              */

        LONG    MixUserErr;             /* 光学尺混合偏差(SCANB)             [用户单位]                    */
        LONG    dMixPulAErr;            /* 混合偏差增量原始值 (SCANA)         [编码器单位]                */
        LONG    dMixPulAErrFil;         /* 混合偏差增量(SCANA)滤波值          [编码器单位]                                             */
        LONG    dFencPosOri;            /* 负载端位置增量（编码器单位）          [编码器单位]                   */
        LONG    dFencPos;               /* Delta Fenc Position          [pulse/ScanA]               */
        LONG    FencSpd;                /* Load Speed                   [2^24/OvrSpd]   <V158>      */
        LONG    FencRemain;             /* 光学尺单位转换成编码器单位余数                           */
        LONG    FencCompValue;          /* 全闭环脉冲补偿累加量                                     */

 		LONG	TrqRefoLimit;			// 限幅后得转矩指令 [2^24/MaxTrq]
 		SHORT	IqDist;					// q轴干扰扭矩                   [15000/MaxTrq]
        LONG    TorqReachCnt;           // 转矩到达信号
        LONG    SpdErrCnt;               
} AINK;

  
  
typedef	struct
{
 		struct {							 
		UINT	VelRippleComp		:1;		 // 转矩脉动补偿
		UINT	Spare01 			:15;	 
		} f;
 		LONG	dPcmda;			             // 位置指令输入增量[指令单位]
		LONG	dPosRefi;					 // 位置控制：位置指令差分输入       [Pulse/Scan]
		LONG	dPosFbki;					 // 位置控制：位置反馈差分输入       [Pulse/Scan]
		LONG	NextdPcmda;					 // 下一次位置指令增量值              [指令単位]
		LONG	NextdPosRefi;				 // 位置控制：下一次位置指令差分      [Pulse/Scan]
		LONG	SpdRefp;					 // 位置控制：速度指令               [2^24/OvrSpd]
		LONG	SpdRefi;					 // 速度控制：速度指令               [2^24/OvrSpd]
		LONG	SpdFbki;					 // 速度控制：速度反馈               [2^24/OvrSpd]
		LONG	SpdObsFbki;					 // 速度控制：速度反馈(OBS后)     [2^24/OvrSpd]
		LONG	TrqRefs;					 // 速度控制：转矩指令输出          [2^24/MaxTrq]
		LONG	SpdFFCx;					 // 扩展控制：速度前馈补偿         [2^24/OvrSpd]
		LONG	SpdFBCx;					 // 扩展控制：速度反馈补偿         [2^24/OvrSpd]
		LONG	TrqFFCx;					 // 扩展控制：前馈转矩补偿         [2^24/MaxTrq]
		LONG	TrqFBCx;					 // 扩展控制：反馈转矩补偿         [2^24/MaxTrq]
        LONG    TLObs;					     // 扩展控制：Tl观测器补偿         [2^24/MaxTrq]
		LONG	TrqRefi;					 // 转矩滤波器：转矩指令输入        [2^24/MaxTrq]
		LONG    TrqRefiTemp;                 // 转矩滤波器: 转矩指令输入         [2^24/MaxTrq]
        LONG	TrqRefo;					 // 转矩滤波器：转矩指令输出        [2^24/MaxTrq]
        LONG    TrqComp;
		LONG	TrqRefo_l;					 // 转矩滤波器：转矩指令输出        [2^24/MaxTrq]
		LONG	TrqRefo_a;					 // 转矩滤波器：转矩指令输出        [2^24/MaxTrq]
		LONG	TrqRefoComp;				 // 校正转矩指令输出                [2^24/MaxTrq]
		LONG	DisTrqRef3;					 // 扰动转矩指令输入                    [2^24/MaxTrq]
		LONG	MotSpd_l;					 // 电机速度 前回值                    [2^24/OvrSpd]
		LONG	MotSpd_a;					 // 电机速度 平均值                    [2^24/OvrSpd]
		LONG    MotSpd_c;                    // 电机速度 补偿值                    [2^24/OvrSpd]
        USHORT	RefRenewalCnt;				 // ScanA位置命令更新过程
		USHORT	RefRenewalChkCnt;			 // 位置命令检查更新
 		LONG	FencSpd_l;					 // 前回全闭环速度                 [2^24/OvrSpd]
		LONG	FencSpd_a;					 // 平均全闭环速度                 [2^24/OvrSpd]
		LONG	SpdObsFbki_l;				 // 前回全闭环速度                 [2^24/OvrSpd]
		LONG	SpdObsFbki_a;				 // 平均全闭环速度                 [2^24/OvrSpd]
 
} AOUTV;
  
  
extern	AINK AinK;						 
extern  AOUTV AoutV;
extern void ApiScanAMain( void );
#endif
