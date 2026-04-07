/*
 * Mot12_MoSenclf.h
 *
 *  Created on: 2017年10月26日
 *      Author: zhuxc
 */
#ifndef Mot12_MoSenclf_H
#define Mot12_MoSenclf_H
 
  
/* 电机编码器 : 参数定义 */
typedef  struct
{
	void	( *KpiReadMencPosition )( void );	    // 电机编码器读取位置函数
    struct                                          // 位信号定义
    {
        UINT EncCom4Mbps            : 1;            // 编码器通讯速度 8Mbps(1:4M;0:2.5M)
        UINT DivOut                 : 1;            // 最终分频脉冲输出Flag
        UINT ENCErrorFlag           : 1;            // 编码器错误标志

        UINT AbsoEncoder            : 1;            // 绝对式编码器
        UINT LowSpdMotor            : 1;            // 低速电机
        UINT RevAsmMotor            : 1;            // 马达反转连接Flag ，初始化时从电机读取设置
        UINT PlsTrn13bit            : 1;            // 脉冲变换13bit指定Flag(ASIC设定用)
        UINT DivPcmaskCtrl          : 1;            // 分频C相脉冲屏蔽控制Flag，是否MencP.DivOutSft 16，防止每圈输出多个C
        UINT CphaseLess             : 1;            // CphaseLess Encoder，直线型绝对值编码器为TRUE
        UINT PhaseOrderUWV          : 1;            // 动力输出相序ＵＷＶ，只在初始化是由Pn080.1设置
        UINT withPoleSensor         : 1;            // 有无霍尔传感器选择 (linear 专用)由Pn080.0设置0:TRUE
        UINT MotOrgChkAlways        : 1;            // 电机原点时刻监视(线性专用)
        UINT DivRatFix              : 1;            // 分频比/最大速度:固定/计算(线性专用)
        UINT CoreLessLinearMotor    : 1;            // CoreLess Linear Motor
        UINT SigmaTracMotor         : 1;            // Sigma Trac Linear Motor
        UINT ScaleWriteEnable       : 1;            // 编码器可否写入参数标志,初始化根据编码器类型设置(标准电机UT**禁止写入)

        UINT OrgClrByWrAdrCmd       : 1;            // Origin Clear By Write Address Command
        UINT TuningLessLowGainMotor : 1;            // 免调整控制低噪音电机设定(免调整专用)
        UINT WeakenFieldEnable      : 1;            // 电压FB方式削弱磁场控制强制有效标志
        UINT PhaOrgEqualCpos        : 1;            // 励磁电流位相选择开关（相位原点=电动机原点） Pn081.2
        UINT PoleReverse            : 1;            // 磁极信号逻辑反相选择(TRUE=反相使用),Pn081.3 编码器UVW扇区信号电平反转
        UINT OrgOffsetEnable        : 1;            // 分频C相输出选择开关(マグネスケール用)
        UINT SenSpecEnable          : 1;            // Prm 0x43(传感器规范)(TRUE=有效)
        UINT PoleWriteEnable        : 1;            // 电流相位参数标度写入允许标志
        UINT ScalePrmWrChkFlg       : 1;            // 参数写入范围检查标志
    } f;
    UCHAR  MorgSft;                                 // 安川为100-77 = 23
    UCHAR  MorgPassSft;                             // 安川为 96-77 = 19
    UCHAR  MposSftX;                                // Shift Data for Motor Position Cal.
    UCHAR  MposSftR;                                // Shift Data for Motor Position Cal.
    ULONG  EncPulseTimeBasic;                       // 编码器脉冲补偿时间基值
      
    USHORT DivRate;                                 // 分周比设定値
    UCHAR  AbsoEncType;                             // Absolute Encoder Type,Pn002.2绝对式或增量式,再由PnF00&0100选择是多圈还是单圈
    UCHAR  FATypeCode;                              // 编码器厂家代码：1:多摩川, 2: Nikon

 													 
    UCHAR   EncOffCnt;                              // 编码器断线计数
    UCHAR   FirstFlag;                              // 初始化运行标志
    UCHAR   PowerOnDelay;                              // 初始化运行标志
    LONG    PulseInitValue;                         // 多圈编码器零点位置多圈脉冲值
    LONG   PulseOffset;                             // 编码器相对零点位置偏移脉冲
    LONG   PulseNo;                                 // Pulse Number [pulse/rev] or [pulse/360deg]
    float  PulseNoDiv600;
	float  PulseNoDiv60;
	UCHAR  MotType;                                 // Motor Type 旋转或直线
    UCHAR  EncType;                                 // Motor Encoder Type:

    LONG   DivOvrSpd;                               // 分频输出过速转速 [2^24/OvrSpd]
    CHAR   OrgSegStatus;
    LONG   Kmotphase;                               // Gain for Motor Phase Cal. 极对数
    float  fKmotphase;
    LONG   MotspdA;                                 // Gain for Motor Spped Cal.
    float  fMotspdA;                                             
 	 
    LONG   AccErrLvl;                               // Motor Encoder Acc. Error Check
    LONG   TgonSpdLevel;
} MENCP;
  
typedef	union
{
    UINT w;
    struct {
        UINT    OverSPd         :1;     // 编码器过速故障
        UINT    FullAbsOver     :1;     //
        UINT    CountError      :1;     // 编码器解码异常故障
        UINT    CountOverflow   :1;     // 编码器多圈溢出故障
        UINT    EncOH           :1;     // 编码器过热报警
        UINT    MTERR           :1;     // 编码器备份报警
        UINT    BattError       :1;     // 编码器欠压报警
        UINT    BattAlarm       :1;     // 编码器欠压警告
        UINT    TMout           :1;     // 编码器状态超时
        UINT	Spare			:7;
    } f;
} ABSENCALM_DEF;
 
  
/* 电机编码器 : 相关变量定义 */
typedef  struct
{
    struct
    {
        UCHAR EncReady;  	            // Encoder Ready
        UCHAR PhaseReady;				// Motor Phase Ready (Phase Found Finish),电角度初始化(磁极检出)完成,
        UCHAR EncConnect;				// < Encoder Connected >
        UCHAR SeRxErr;					// Senc Receive Error
        UCHAR EncDataNG;	            // Encoder Data NG Flag
        UCHAR AccChkEnable;  			// Encoder Acc. Check Enable Flag
        UCHAR PosCmpEnable;			    // 位置修正执行许可,初始化为0，读过一次位置后为1
        UCHAR PosFirstReadFlag;	        // 位置信息第一次读取标志位
    } f;
    ABSENCALM_DEF EncStatus;            // 编码器状态
    DWORDX	RxPosL[ 2 ];	            // Encoder Position Data Low
    DWORDX  RxPosLOri[ 2 ];                // Encoder Position Data Low

    SHORT	RxPosH[ 2 ];				// Encoder Position Data High
    SHORT	RxMPos;						// 多圈值
    LONG    PosComp[4];
    LONG	MotPos;                     // 电机位置
    LONG    dMotPos;                    // 增量式编码器脉冲变化量
    LONG	MotAbsPos;					// 电机绝对位置
    LONG	MotPosX[ 2 ];				// Motor Encoder Position(校正后位置)[DependOnEncoder]初始化从编码器读取2^32/圈
    LONG	RcvPosX[ 3 ];				// Motor Encoder Position(受信位置) [DependOnEncoder]初始化从编码器读取2^32/圈
    LONG	SingTurn;                   // 一圈内的绝对坐标值
    USHORT  MotPhaseI;                  // 原始电角度 4096 对应 360°
    SHORT	MotPhase;					// 角度 4096对应 360deg

    USHORT  MstErrCnt;                  // Encoder Mst. Error Counter
    USHORT  ComErrCnt;                  // Encoder Com. Error Counter for Monitor
    USHORT  AccErrCnt;                  // Encoder Acc. Error Counter for Monitor

    SHORT   Temperature;			    // Encoder Temperature
    ULONG   MagicPos;                   // 磁编位置
    ULONG   MagicPosOld;                // 磁编上次位置
    USHORT  MagicErrFlg;                // 磁编异常跳变点
    LONG    MotSpd;                     // Motor Speed 初始化为0 [2^24/OvrSpd]
    USHORT  AccChkWaitCnt;              // 加速度检测开始计数值
} MENCV;
 
extern MENCP	MencP;
extern MENCV	MencV;								 
extern void	KpxSencInitMotorEncoder( void );
extern void RmxSencInitParamCalc( void );
 
#endif
