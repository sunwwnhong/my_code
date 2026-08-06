//==================================================================================================
//
// 性能与功能都会使用的一些结构体定义
//
//
//
// Time-stamp: <2011-3-10 14:59:47  author, 0000>
//
//==================================================================================================


#ifndef __M_INTERFACE_PUBLIC_H__
#define __M_INTERFACE_PUBLIC_H__


#include "main.h"



//==============================================================================
#define MOTOR_TYPE_ACI_GENERAL  0   // 普通异步电机
#define MOTOR_TYPE_ACI_INV      1   // 变频异步电机
#define MOTOR_TYPE_PMSM         2   // 永磁同步电机
struct MOTOR_PARA_STRUCT_ARM
{
    // 电机基本参数
    Uint16 motorType;               // F1-00  电机类型选择
    Uint16 ratingPower;             // F1-01  电机额定功率
    Uint16 ratingVoltage;           // F1-02  电机额定电压
    Uint16 ratingCurrent;           // F1-03  电机额定电流
    Uint16 ratingFrq;               // F1-04  电机额定频率
    Uint16 ratingSpeed;             // F1-05  电机额定转速

    // 异步机调谐参数
    Uint16 statorResistance;        // F1-06  异步机定子电阻
//    Uint16 rotorResistance;         // F1-07  异步机转子电阻
    Uint16 leakInductance;          // F1-08  异步机漏感抗
//    Uint16 mutualInductance;        // F1-09  异步机互感抗
    Uint16 zeroLoadCurrent;         // F1-10  异步机空载电流
//    Uint16 rsvdF11[5];

    // 同步机调谐参数
    Uint16 pmsmRs;                  // F1-16  同步机定子电阻
    Uint16 pmsmLd;                  // F1-17  同步机d轴电感
    Uint16 pmsmLq;                  // F1-18  同步机q轴电感
//    Uint16 pmsmRsLdUnit;            // F1-19  同步机电感电阻单位
    Uint16 pmsmCoeff;               // F1-20  同步机反电动势系数
//    Uint16 pmsmCheckTime;           // F1-21  同步机输出缺相检测时间


//    Uint16 rsvdF12[4];

    Uint16 inertia;                 // F1-26  惯量

};
#define MOTOR_PARA_LEN  (sizeof(struct MOTOR_PARA_STRUCT_ARM)/sizeof(Uint16))
union MOTOR_PARA
{
    Uint16 all[MOTOR_PARA_LEN];

    struct MOTOR_PARA_STRUCT_ARM elem;
};
//==============================================================================



//==============================================================================
struct PG_PARA_STRUCT
{
    // PG卡参数
    Uint16 encoderPulse;            // F1-27    编码器脉冲线数
    Uint16 pgType;                  // F1-28    编码器类型
//    Uint16 fvcPgSrc;                // F1-29    速度反馈PG卡选择, 0-QEP1,1-QEP2(扩展)
// 请使用 coreMainCmd1.bit.pgLocation
//    Uint16 encoderDir;              // F1-30    编码器相序/主方向
// 请使用 coreMainCmd1.bit.fvcPgLogic
    Uint16 encoderAngle;            // F1-31    编码器安装角
    Uint16 uvwSignDir;              // F1-32    UVW信号方向
    Uint16 uvwSignAngle;            // F1-33    UVW信号零点位置角
    Uint16 encoderPole;             // F1-34    旋变极对数
//    Uint16 uvwSignPole;             // F1-35    UVW极对数
    Uint16 encoderLossLimit;        // F1-36    速度反馈PG断线检测时间==>编码器丢失检测阈值
};
#define PG_PARA_LEN (sizeof(struct PG_PARA_STRUCT)/sizeof(Uint16))
union PG_PARA
{
    Uint16 all[PG_PARA_LEN];

    struct PG_PARA_STRUCT elem;
};
//==============================================================================




//==============================================================================
struct VC_PARA_STRUCT
{
    Uint16 vcSpdLoopKp1;            // F2-00  速度环比例增益1
    Uint16 vcSpdLoopTi1;            // F2-01  速度环积分时间1
    Uint16 vcSpdLoopChgFrq1;        // F2-02  切换频率1
    Uint16 vcSpdLoopKp2;            // F2-03  速度环比例增益2
    Uint16 vcSpdLoopTi2;            // F2-04  速度环积分时间2

    Uint16 vcSpdLoopChgFrq2;        // F2-05  切换频率2
    Uint16 vcSlipCompCoef;          // F2-06  转差补偿系数
    Uint16 vcSpdLoopFilterTime;     // F2-07  速度环滤波时间常数
    Uint16 vcOverMagGain;           // F2-08  矢量控制过励磁增益
    Uint16 spdCtrlDriveTorqueLimitSrc;  // F2-09  速度控制(驱动)转矩上限源

    Uint16 spdCtrlDriveTorqueLimit;     // F2-10  速度控制(驱动)转矩上限数字设定
    Uint16 spdCtrlBrakeTorqueLimitSrc;  // F2-11  速度控制(制动)转矩上限源
    Uint16 spdCtrlBrakeTorqueLimit;     // F2-12  速度控制(制动)转矩上限数字设定
    Uint16 acrKp;                       // F2-13  电流环比例增益
    Uint16 acrKi;                       // F2-14  电流环积分增益
    Uint16 acrKpBrake;                  // F2-15  电流环比例增益(叠频制动时)
    Uint16 acrKiBrake;                  // F2-16  电流环积分增益(叠频制动时)
    
    Uint16 vcSpdLoopTd;                 // F2-17  速度环微分时间

    Uint16 weakFlusMode;            // F2-18 同步机弱磁模式
    Uint16 weakFlusCoef;            // F2-19 同步机弱磁系数
    Uint16 weakFlusCurMax;          // F2-20 最大弱磁电流
    Uint16 weakFlusAutoCoef;        // F2-21 弱磁自动调谐系数
    Uint16 weakFlusIntegrMul;       // F2-22 弱磁积分倍数
};
#define VC_PARA_LEN (sizeof(struct VC_PARA_STRUCT) / sizeof(Uint16) )
union VC_PARA
{
    Uint16 all[VC_PARA_LEN];
    struct VC_PARA_STRUCT code;
};
//==============================================================================




//==============================================================================
struct AUTO_TUNE_PARA_STRUCT
{
    Uint16 rs;              //  0 F1-06  定子电阻
    Uint16 rr;              //  1 F1-07  转子电阻
    Uint16 lSigma;          //  2 F1-08  L Sigma，= sigma * Ls
    Uint16 lm;              //  3 F1-09  互感
    Uint16 iNoLoad;         //  4 F1-10  空载电流
    Uint16 pmsmRs;          //  5 F1-16  同步机定子电阻
    Uint16 pmsmLd;          //  6 F1-17  同步机d轴电感
    Uint16 pmsmLq;          //  7 F1-18  同步机q轴电感
    Uint16 rsvd1;           //  8
    Uint16 pmsmCoeff;       //  9 F1-20  同步机反电动势系数
    Uint16 acrKp;           // 10 F2-13  电流环比例增益
    Uint16 acrKi;           // 11 F2-14  电流环积分增益
    Uint16 acrKpBrake;      // 12 F2-15  电流环比例增益(叠频制动时)
    Uint16 acrKiBrake;      // 13 F2-16  电流环积分增益(叠频制动时)
    Uint16 rsvd2;           // 14
    Uint16 encoderDir;      // 15 F1-30  编码器相序/主方向
    Uint16 rtPos;           // 16 
    Uint16 uvGainWarp;      // 17 FF-05  UV两相增益偏差
    Uint16 rsvd5;           // 18
    Uint16 inertia;         // 19 F1-26  惯量
    Uint16 PluseWidth;      //  20 F1-22  转子位置脉冲辨识宽度  
    Uint16 rsvd[8];        //
    Uint16 crc;
};
#define AUTO_TUNE_PARA_LEN (sizeof(struct AUTO_TUNE_PARA_STRUCT) / sizeof(Uint16) )
union AUTO_TUNE_PARA
{
    Uint16 all[AUTO_TUNE_PARA_LEN];
    struct AUTO_TUNE_PARA_STRUCT code;
};
//==============================================================================















//==============================================================================
// dspMainCmd, 转递给性能的主命令字
//
struct DSP_MAIN_COMMAND_BITS
{                               // bits  description
    Uint16 run:1;               // 0,    0:stop, 1:run
    Uint16 startBrake:1;        // 1,    start brake
    Uint16 stopBrake:1;         // 2,    stop brake
    Uint16 motorCtrlMode:4;     // 6:3   00-IM_SVC1, 01-IM_FVC, 10-IM_SVC2,... 见enum Algorithims说明
    Uint16 startFlux:1;         // 7:    预励磁
    Uint16 torqueCtrl:1;        // 8     转矩控制
    Uint16 accDecStatus:2;      // 10:9  0 恒速； 1 加速； 2 减速. //! 目前转差补偿使用了该标志
    Uint16 spdLoopI1:1;         // 11    速度环积分分离
    // Uint16 synchTransfer:2;     // 13:12 0-none；1-Up(变频->工频)；2-Down. 功能码暂放在F8-52
    Uint16 DCBrakeStatus:2;     // 13:12 直流制动状态 // LS_20210421
    Uint16 codeAB:1;            // 14, 0-codeA, 1-codeB
    Uint16 rsvd:1;              // 15
};
union DSP_MAIN_COMMAND
{
    Uint16                       all;
    struct DSP_MAIN_COMMAND_BITS bit;
};
//==============================================================================



//==============================================================================
// dspMainCmd1, 转递给性能的主命令字1，运行中不可更改
//
struct DSP_MAIN_COMMAND1_BITS
{                               // bits  description
    Uint16 pgLocation:2;        // 1:0,  速度反馈PG选择. 0：本地PG，1：扩展PG，2：PULSE脉冲输入（DI5）
    Uint16 fvcPgLogic:1;        // 2,    速度反馈PG卡，AB相序. 1-B超前A.
    Uint16 deadCompMode:3;      // 5:3,  死区补偿模式选择. 0－死区补偿模式0；1－死区补偿模式1
    Uint16 modulationMode:1;    // 6     调制方式，0-异步调制，1-同步调制
    Uint16 newKernel:1;         // 7     一代板二代板选择，0-一代板，1-二代板
    Uint16 quickTranUp:1;       // 8     保留
    Uint16 frqPoint:2;          // 10:9  频率指令小数点。0: 1Hz；1：0.1Hz；2：0.01Hz
    Uint16 speedTrack:2;        // 12:11 0－转速跟踪无效，1－正向飞车启动，2－反向飞车启动, 3-正反向飞车启动
    Uint16 shortGnd:1;          // 13    上电对地短路检测标志
    Uint16 masterOrSlave:2;     // 14:15 0:单机 1:主机 2:从机 
};
union DSP_MAIN_COMMAND1
{
    Uint16                       all;
    struct DSP_MAIN_COMMAND1_BITS bit;
};
//==============================================================================



//==============================================================================
// dspSubCmd, 转递给性能的辅命令字
//
struct DSP_SUB_COMMAND_BITS
{                                       // bits  description
    Uint16 errorDealing:1;              // 0,    1:ERROR TALK, 功能正在进行故障处理
    Uint16 outPhaseLossProtect:1;       // 1,    输出缺相保护
    Uint16 inPhaseLossProtect:1;        // 2,    输入缺相保护
    Uint16 overloadMode:2;              // 3-4,  电机过载保护模式，功能码F9-00
    Uint16 loseLoadProtectMode:1;       // 5,    输出掉载保护使能标志
//    Uint16 poffTransitoryNoStop:1;      // 5,    瞬停不停使能
    Uint16 cbc:1;                       // 6,    逐波限流功能使能标志
    Uint16 varFcByTem:1;                // 7    载波频率随温度调整
    Uint16 dualFrqBrakeEnable:1;        // 8    F6-11	叠频制动使能
    Uint16 invContactorFdb:1;           // 9    变频接触器反馈
    Uint16 netContactorFdb:1;           // 10   工频接触器反馈
    Uint16 motorContactorFdb:1;         // 11   电机接触器反馈
    Uint16 afeMode00:1;                 // 12   AFE 进00模式
    Uint16 encoderLossDeal:2;           // 13-14  FVC时，编码器故障时的处理，0-停机, 1-SVC1, 2-SVC2
    u16 highStartingEnable:1;           // 15   A5-11	高启动转矩模式使能
};
union DSP_SUB_COMMAND
{
    Uint16                      all;
    struct DSP_SUB_COMMAND_BITS bit;
};
//==============================================================================



//==============================================================================
// 性能传递给功能的状态字
//
struct DSP_STATUS_BITS
{                                   // bits  description
    Uint16 runEnable:1;		        // 0     1-初始化完成，可以运行标志
    Uint16 uv:1;                    // 1     母线电压欠压故障标志  0-欠压  1-不欠压
    Uint16 run:1;                   // 2     运行/停机状态标志
    Uint16 coreErrorResetEnd:1;     // 3     性能故障复位完成
    Uint16 speedTrackEnd:1;         // 4     转速跟踪结束标志
    Uint16 inverterPreOl:1;         // 5     变频器过载预报警标志
    Uint16 motorPreOl:1;            // 6     电机过载预报警标志
    Uint16 forbidAccDecSpd:1;       // 7     DSP给的加减速禁止标志，1-禁止加减速
    Uint16 outAirSwitchOff:1;       // 8     变频器输出空开断开标志，即掉载标志
    Uint16 codeAB:1;                // 9     0-codeA, 1-codeB
    u16 invContactor:1;             // 10    无冲击电流的工变频切换，变频接触器，1-吸合。DO-50
    u16 netContactor:1;             // 11    无冲击电流的工变频切换，工频接触器，1-吸合。DO-51
    u16 upTransferFinish:1;         // 12    上切换完成
    u16 downTransferFinish:1;       // 13    下切换完成
    u16 motorContactor:1;           // 14    电机接触器输出接触器。1-吸合。DO-49
    Uint16 exciteCmd:1;             // 15    励磁同步机励磁命令
};
union DSP_STATUS
{
   Uint16                   all;
   struct DSP_STATUS_BITS   bit;
};
//==============================================================================



//==============================================================================
// 性能传递给功能的辅助状态字
//
struct DSP_SUB_STATUS_BITS
{                                   // bits  description
    Uint16 accDecStatus:2;          // 0:1   0 恒速； 1 加速； 2 减速

    Uint16 invContactOff:1;         // 2 变频接触器释放
    Uint16 netContactOn:1;          // 3 工频接触器吸合
    Uint16 netContactOff:1;         // 4 工频接触器释放
    Uint16 overLoad:1;              // 5 负载太重 需要减小风门
    Uint16 lockPhase:2;             // 6:7 锁相 0 不管 1:成功 2:失败

    Uint16 netCurCmd:1;             // 8    高炉鼓风机工频电流
    Uint16 cellVolFluct:1;          // 9    母线电压波动标志
    Uint16 speedRollBack:1;         // 10   速度环RollBack标记
    
    Uint16 rsvd:5;                  // 11:15  保留
};
union DSP_SUB_STATUS
{
   Uint16                       all;
   struct DSP_SUB_STATUS_BITS   bit;
};
//==============================================================================









#endif  //__M_INTERFACE_PUBLIC_H__




