
#ifndef __F_FRQ_SRC_H__
#define __F_FRQ_SRC_H__

// ----------------函数声明---------------------------------------------- 
extern void FrqSrcDeal(void);
extern void UpdateFrqAim(void);
extern int32 FrqPlcSetDeal(void);
extern int32 UpdateMultiSetFrq(Uint16 step);
extern void ResetUpDownFrq(void);
extern void AccDecTimeCalc(void);
// ----------------函数声明结束------------------------------------------ 


#define ACC_DEC_FRQ_NONE    0
#define ACC_DEC_FRQ_WAIT    1
#define ACC_DEC_FRQ_DONE    2

struct FRQ_FLAG_BITS
{
    Uint16 comp:1;          // 0:   运算
    Uint16 upDown:1;        // 数字设定，UP/DOWN可修改
    Uint16 x:1;             // 1:   X
    Uint16 y:1;             // 2:   Y
    
    Uint16 fcPosLimit:1;    // 3:   有数字设定，且正向限幅
    Uint16 fcNegLimit:1;    // 4:   有数字设定，且正向限幅
    
    Uint16 upDownoperationStatus:1;        // 5:   本次有UP/DN操作标志(防止上限频率变大后,UP/DN因为被限幅，无法随着变化)

    Uint16 frqSetLimit:1;                    // 设定频率被限制
};
union FRQ_FLAG
{
    Uint16 all;
    struct FRQ_FLAG_BITS bit;
};

extern union FRQ_FLAG frqFlag;

struct FRQ_XY
{
    int32 x;    // 主频率X
    int32 y;    // 辅频率Y
    int32 z;    // 辅频率Y偏置
};

extern struct FRQ_XY frqXy;

typedef struct
{
	// input
	Uint16 frq;     // 跳跃频率
	Uint16 range;   // 跳跃频率幅度

	// output
	Uint32 low;     // 跳跃频率范围的low
	Uint32 high;    // 跳跃频率范围的high
} JUMP_FRQ;
// 功能部分使用的PID
typedef struct
{
    void  (*calc)(void *);  // Pointer to calculation function

    int32  ref;             // PID给定，Q15
    int32  fdb;             // PID反馈，Q15

    int32  Kp;              // 比例增益
    int32  Ki;              // 积分增益
    int32  Kd;              // 微分增益

    int32  Kp2;             // 第2参数的P
    int32  Ki2;             // 第2参数
    int32  Kd2;             // 第2参数

    int16  Qp;              // Kp的Q格式
    int16  Qi;              // Ki的Q格式
    int16  Qd;              // Kd的Q格式

    int32  deltaMax;        // Q15, 两次输出之间偏差的最大值
    int32  deltaMin;        // Q15, 两次输出之间偏差的最大值
    int32  outMax;          // Q15，PID输出最大值
    int32  outMin;          // Q15，PID输出最小值
    int32  pidDLimit;       // Q15, PID微分限幅
    int32  errorDead;       // 小于偏差极限，则PID不调节, Q15
    int32  errorSmall;      // 变积分使用
    int32  errorBig;        // 变积分使用

    int32  error;           // PID偏差，Q15, 注意可能超过0xffff
    int32  error1;          // 
    int32  error2;

    int32  delta;           // 两次输出之间的差值

    int32  deltaPRem;       // P计算的Remainder
    int32  deltaIRem;       // I计算的Remainder
    int32  deltaDRem;       // D计算的Remainder
    int32  deltaRemainder;  // 两次输出之间限幅之后的余值，保留下次计算使用

    int32  out;             // Output: PID output, Q15
} PID_FUNC;


#define PID_FUNC_DEFAULTS         \
{                                 \
    (void (*)(void *))PidFuncCalc \
}



extern PID_FUNC pidFunc;
void PidFuncCalc(PID_FUNC *);


//-------------------------------------

#define UP_DN_OPERATION_ON          1
#define UP_DN_OPERATION_OFF         0

#define RUN_MODE_SPEED_CTRL     0   // 速度控制
#define RUN_MODE_TORQUE_CTRL    1   // 转矩控制
//#define RUN_MODE_POSITION_CTRL  2   // 位置控制
extern u16 runMode; // 运行模式


extern int32 frq;
extern int32 frqTmp;
extern int32 frqAim;
extern int32 frqAimTmp;
extern int32 frqAimTmp0;
extern int32 frqCurAim;        // 当前目标频率，注意在每次调用AccDecFrqCalc()之前要更新frqCurAim
extern Uint16 frqAimDisp;
extern int32 frqAiPu;

extern int32 frqRun, frqRunTmp;

extern int32 frqCurAimOld;
extern int32 frqDroop; 
extern Uint16 frqDisp;
extern Uint32 accFrqTime;      // 加速时间，单位同功能码
extern Uint32 decFrqTime;      // 减速时间

extern Uint16 maxFrq;          // 最大频率
extern Uint16 lowerFrq;        // 下限频率
extern Uint16 upperFrq;        // 下限频率
extern int16 upperTorque;
extern int16 torqueAim;
extern Uint16 upDownFrqInit;


extern u16 bFrqDigital;         // 数字设定频率标志，不包括UP/DOWN完成之后一段时间的显示处理时间
extern Uint16 frqKeyUpDownDelta;   // 使用面板UP/DOWN增减频率的delata
extern int32 upDownFrq;
//extern Uint16 upDownDelta;
extern u16 bFrqDigitalDone4WaitDelay;

extern Uint32 plcTime;
extern u16 plcStepRemOld;   // PLC记忆的step
extern Uint32 plcTimeRemOld;   // PLC记忆的time
extern int16 inputFrq;
extern Uint16 outVoltage;
extern Uint16 frqXDisp;
extern Uint16 frqYDisp;
extern int16 inputFrqForTrans;
#endif











