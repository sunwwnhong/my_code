//==================================================================================================
//
// 一些公共子函数，包括:
// DataLogDeal()        数据记录函数，调试使用
// RampCalc()           斜坡函数
// MemCopy()            memCpy
// LineCalc()           已知两点，求第三点
// StatisticDeal()      时间统计处理
// CrcValueWordCalc()   CRC16计算
// 
//
// Time-stamp: <2012-2-16 12:35:25  author, 0000>
//
//==================================================================================================


#include "main.h"

#include "m_macro_log.h"
#include "public.h"

#if DEBUG_FUNCTION_IN_RAM   // 将部分函数放到RAM中，加快运行速度
//#pragma CODE_SECTION(DataLogDeal     ,     "ramfuncs");
#pragma CODE_SECTION(LineChangeCalc  ,     "ramfuncs");
//#pragma CODE_SECTION(LineCalc        ,     "ramfuncs");
//#pragma CODE_SECTION(LpfCalc         ,     "ramfuncs");
//#pragma CODE_SECTION(StatisticDeal   ,     "ramfuncs");
//#pragma CODE_SECTION(BurrFilter      ,     "ramfuncs");
//#pragma CODE_SECTION(CrcValueByteCalc,     "ramfuncs");
//#pragma CODE_SECTION(CrcValueWordCalc,     "ramfuncs");

//#pragma DATA_SECTION(crc16Table,     "ramfuncs");   // 将CRC表格也放在RAM中，加快CRC校验速度
#endif




#if DEBUG_DATA_LOG

// 分配给调试示波器使用的RAM空间
// 与DSP28xxx_CodeStartBranch.asm的RAM初始化的长度要一致
#if !DEBUG_PRG_IN_RAM       // 程序放在FLASH中
//#define SCOPE_RAM_ALL           (1)   // PC后台监控打开时用这个
#define SCOPE_RAM_ALL           (0x6000-0x5FFF)  // 28335,0x8000；28232,0x6000；2808,0x4000
                                    // 用RAM仿真画图时，打开#define DEBUG_COMMUNICATE_TO_PC
#elif 1                     // 程序放在RAM中
//#define SCOPE_RAM_ALL           (1)
#define SCOPE_RAM_ALL           (0x3600-0x3500)  // 28335,0x4800
#endif


// 多少个调用周期，记录一次数据
//#define DATA_LOG_SKIP_CNT_MAX_INIT  12  // dataLog的 skipCntMax 的初始值
// 1/2/3//7//17//20//2//25//(u32)(3.6*10)  // 
#define DATA_LOG_SKIP_CNT_MAX_INIT  1


#define SCOPE_START_RUN_ARRAY_0     1   // 1-启动时，从数组的起始开始保存
#define SCOPE_ARRAY_USER_OVER_LOOP  0   // 1-数组使用完毕，自动从数组的起始重新循环

Uint16 dataLogScope[SCOPE_RAM_ALL];     // dataLog保存数据的数组
DATA_LOG_STRUCT dataLog = {DATA_LOG_SKIP_CNT_MAX_INIT,1000};

void LpfCalc(LowPassFilter *p);



#define RecordDataLog(N)                                        \
{                                                               \
    if (p->chNum >= (N) + 1)                                    \
        dataLogScope[(N) * p->len + p->index] = p->dataIn[N];   \
}
//=====================================================================
//
// 数据记录函数
// 把 p->dataIn[] 的数据依次存入 dataLogScope[] 中
//
// 输入:
//      p->chNum        需要记录的通道数量
//      p->dataIn[0->]  需要保存的数据
//      p->trig         当前拍是否要记录
// 参数:
//      p->skipCntMax   skip counter max, 每隔_次保存数据
// 输出:
//      dataLogScope[]  记录的数据放入数组 dataLogScope[] 中。可以拿来分析，绘图等。
//
// dataLogScope[]的记录方式:
// 1、p->len = dataLogScope[]的数组长度 / p->chNum，得到每个通道可以使用的RAM长度
// 2、第0个通道数据(p->dataIn[0])的记录位置:
//                  dataLogScope[0*p->len] -- dataLogScope[0*p->len + p->index - 1]
//    第1个通道数据(p->dataIn[1])的记录位置:
//                  dataLogScope[1*p->len] -- dataLogScope[1*p->len + p->index - 1]
//    ......
//    第n个通道数据(p->dataIn[n])的记录位置:
//                  dataLogScope[n*p->len] -- dataLogScope[n*p->len + p->index - 1]
//
// dataLogScope[] 为全局变量，需要用户另外定义。这样方便改变该数组的长度。
// 
//
//=====================================================================

void DataLogDeal(DATA_LOG_STRUCT *p)
{
    if ((0 == p->chNum) || (SIZEOF(p->dataIn) < p->chNum))      // 通道数超过范围
        return;

    if (p->trig)
    {
        if (!p->trigOld)            // 停机->运行
        {
            p->len = (Uint16)(SIZEOF(dataLogScope)) / p->chNum;
            p->skipCnt = 0;
            p->stop = 0;

#if SCOPE_START_RUN_ARRAY_0     // 启动时，从数组的起始开始保存
            p->index = 0;
#endif
        }

        p->skipCnt++;
        if (p->skipCnt >= p->skipCntMax)    // 每隔_次保存数据
        {
            p->skipCnt = 0;

            if (!p->stop)
            {
                RecordDataLog(0);
                RecordDataLog(1);
                RecordDataLog(2);
                RecordDataLog(3);
                RecordDataLog(4);
                RecordDataLog(5);

                p->index++;
                if (p->index >= p->len)     // 分配的RAM空间已经用完
                {
#if SCOPE_ARRAY_USER_OVER_LOOP
                    p->index = 0;           // 数组使用完毕，自动从数组的起始重新循环
#elif 1
                    p->stop = 1;            // 停止保存
#endif
                }
            }
        }
    }

    p->trigOld = p->trig;
}

#endif




//==============================================================================
//
// memCopy函数
//
//==============================================================================
void MemCopy(const Uint16 *SourceAddr, const Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while (SourceAddr < SourceEndAddr)
    {
       *DestAddr++ = *SourceAddr++;
    }
    return;
}





//==============================================================================
//
// 直线变化的计算(定点)，斜坡函数
// curValue->aimValue
//
//==============================================================================
#if 0
void LineChangeCalc(LINE_CHANGE_STRUCT *p)
{
    int32 delta;

    if (p->curValue != p->aimValue)
    {
        if (!p->tickerAll)
        {
            p->curValue = p->aimValue;
        }
        else
        {
            delta = ((int32)p->maxValue + p->remainder) / p->tickerAll;
            p->remainder = ((int32)p->maxValue + p->remainder) % p->tickerAll;

            if (p->aimValue > p->curValue)
            {
                p->curValue += delta;
                if (p->curValue > p->aimValue)
                    p->curValue = p->aimValue;
            }
            else
            {
                p->curValue -= delta;
                if (p->curValue < p->aimValue)
                    p->curValue = p->aimValue;
            }
        }
    }
}
#endif






//==============================================================================
//
// 直线变化的计算(浮点)，斜坡函数
// curValue->aimValue
//
//==============================================================================
void RampCalc(RAMP_CTRL_STRUCT *p)
{
    f32 delta;

    if (p->curValue == p->aimValue)
    {
        ;
    }
    else if (0 == p->tickerAll)
    {
        p->curValue = p->aimValue;
    }
    else
    {
        delta = p->maxValue / p->tickerAll;

        if (p->aimValue > p->curValue)
        {
            p->curValue += delta;
            if (p->curValue > p->aimValue)
                p->curValue = p->aimValue;
        }
        else
        {
            p->curValue -= delta;
            if (p->curValue < p->aimValue)
                p->curValue = p->aimValue;
        }
    }
}








//=====================================================================
//
// 相当于一条线段，已知两端点(x1,y1), (x2,y2), 求第三点(x, y)的y
// 请确保: x1 < x2
// 输出：Q4格式
//
// 1000 * 2^6 = 64000 < 65536，不会溢出。
// pulseInFrq目前最大为50000Hz，也不会溢出。
//
//=====================================================================
void LineCalc(LINE_STRUCT *p)
{
#if 0   // 若x1 < x2. 当x > x1, y = y2; 当x <= x1, y = y1.
    if (p->x <= p->x1)
        p->y = p->y1;
    else if (p->x >= p->x2)
        p->y = p->y2;
    else
        p->y = ((((int32)(p->x - p->x1) << 15) / (p->x2 - p->x1)) * (p->y2 - p->y1)
                 + ((int32)p->y1 << 15) + (1L << 14)) >> 15;
#elif 1
    int32 tmp;
    tmp = ((((int32)(p->x - p->x1) << 15) / (p->x2 - p->x1)) * (p->y2 - p->y1)
                 + ((int32)p->y1 << 15) + (1L << 14)) >> 15;

    // 若x1 < x2. 当x > x1, y = y2; 当x <= x1, y = y1.
    if((p->mode == 2) && (p->x < p->x1))    // 限幅且低于下限时为0
        p->y = 0;
    else if (p->x <= p->x1)
        p->y = p->y1;
    else if (p->x >= p->x2)
        p->y = p->y2;
    else
        p->y = tmp;

    if (p->mode == 1)    // 1，表示不限幅
        p->y = tmp;
#elif 1   //+e 可从数学上反应x1 < x2的情况。但暂不这样
    int32 max, min;

    max = GetMax(p->x1, p->x2);
    min = GetMin(p->x1, p->x2);

    if (p->x <= min)
        p->y = p->y1;
    else if (p->x >= max)
        p->y = p->y2;
    else
        p->y = ((((int32)(p->x - p->x1) << 15) / (p->x2 - p->x1)) * (p->y2 - p->y1)
                 + ((int32)p->y1 << 15) + (1L << 14)) >> 15;
#endif
}




#if !DEBUG_PRG_IN_RAM
//=====================================================================
//
// 浮点
// 相当于一条线段，已知两端点(x1,y1), (x2,y2), 求第三点(x, y)的y
// 请确保: x1 < x2
//
//=====================================================================
void LineFCalc(LINE_F_STRUCT *p)
{
    f32 tmp;
    
    tmp = (p->x - p->x1) * (p->y2 - p->y1) / (p->x2 - p->x1) + p->y1;

    // 若x1 < x2. 当x > x1, y = y2; 当x <= x1, y = y1.
    if ((p->mode == 2) && (p->x < p->x1))   // 限幅且低于下限时为0
        p->y = 0;
    else if (p->x <= p->x1)
        p->y = p->y1;
    else if (p->x >= p->x2)
        p->y = p->y2;
    else
        p->y = tmp;

    if (p->mode == 1)    // 1，表示不限幅
        p->y = tmp; 
}
#endif








//=====================================================================
//
// 低通滤波器函数，定点 
//
//=====================================================================
#if 0
void LpfCalc(LowPassFilter *p)
{
#if 0   // 这一种效果好像差一点，原因以后再查找. 输出可能超过32767, 65535。有bug
    int32 tmp;
    int16 t1 = p->t * TIME_UNIT_AI_PULSE_IN_FILTER;

    p->outOld = p->out;
    if (!p->t)
    {
        p->out = p->in;
    }
    else
    {
        tmp = ((int32)p->in - p->outOld + p->remainder) * AI_CALC_PERIOD;
        p->out = tmp / t1 + p->outOld;
        p->remainder = tmp % t1;
    }
#elif 1
    int32 tmp;

    p->outOld = p->out;
    if (!p->t)
    {
        p->out = p->in;
    }
    else
    {
        tmp = p->in + p->remainder - p->outOld;
        p->out = tmp / p->t + p->outOld;
        p->remainder = tmp % p->t;
    }
#elif 1
    int32 tmp;
    int32 out;

    p->outOld = p->out;
    if (!p->t)
    {
        p->out = p->in;
    }
    else
    {
        tmp = ((int32)p->in - p->outOld + p->remainder) * AI_CALC_PERIOD;
        out = tmp / (p->t * 1) + p->outOld;
        if ()


        p->out = tmp / (p->t * 1) + p->outOld;
        p->remainder = tmp % (p->t * 1);
    }
#endif
}
#endif




//==============================================================================
//
// 
//
//==============================================================================
#if 0
void LpfCalcIq(LowPassFilterIq *p)
{
    f32 tmp;

    p->outOld = p->out;
    if (!p->t)
    {
        p->out = p->in;
    }
    else
    {
        tmp = p->in + p->remainder - p->outOld;
        //p->out = _IQdiv(tmp, p->t) + p->outOld;
        //p->remainder = tmp % p->t;
        p->out = tmp / p->t;
        p->remainder = tmp - p->out * p->t;
        p->out += p->outOld;
    }
}
#endif


//=====================================================================
//
// 低通滤波器函数
// 注意:
//
//=====================================================================
void LpfCalc(LowPassFilter *p)
{
#if 0   // 这一种效果好像差一点，原因以后再查找. 输出可能超过32767, 65535。有bug
    int32 tmp;
    int16 t1 = p->t * TIME_UNIT_AI_PULSE_IN_FILTER;

    p->outOld = p->out;
    if (!p->t)
    {
        p->out = p->in;
    }
    else
    {
        tmp = ((int32)p->in - p->outOld + p->remainder) * AI_CALC_PERIOD;
        p->out = tmp / t1 + p->outOld;
        p->remainder = tmp % t1;
    }
#elif 1
    int32 tmp;

    p->outOld = p->out;
    if (!p->t)
    {
        p->out = p->in;
    }
    else
    {
        tmp = p->in + p->remainder - p->outOld;
        p->out = tmp / p->t + p->outOld;
        p->remainder = tmp % p->t;
    }
#elif 1
    int32 tmp;
    int32 out;

    p->outOld = p->out;
    if (!p->t)
    {
        p->out = p->in;
    }
    else
    {
        tmp = ((int32)p->in - p->outOld + p->remainder) * AI_CALC_PERIOD;
        out = tmp / (p->t * 1) + p->outOld;
        if ()
            
            
        p->out = tmp / (p->t * 1) + p->outOld;
        p->remainder = tmp % (p->t * 1);
    }
#endif
}











//==============================================================================
//
// 简单的时间统计处理，获取 一段时间内的 最大值、最小值、平均值。
// 统计周期: p->prd
// 
//==============================================================================
void StatisticDeal(STATISTICS_STRUCT *p)
{
// 修改为只求平均值
    p->sum += p->now;
    p->t++;
    if (p->t >= p->prd)     // 统计时间到
    {
        p->mean = p->sum / p->t;

        p->sum = 0;         // 相关数据重新初始化
        p->t = 0;
    }
}



void StatisticDeal1(STATISTICS_STRUCT *p)
{
    if (p->max < p->now)
    {
        p->max = p->now;
    }

    if (p->now < p->min)
    {
        p->min = p->now;
    }

    p->sum += p->now;
    p->t++;
    if (p->t >= p->prd)     // 统计时间到
    {
        p->mean = p->sum / p->t;

        p->sum = 0;         // 相关数据重新初始化
        p->t = 0;
        p->max = p->now;
        p->min = p->now;
    }
}




void StatisticDealMax(STATISTICS_STRUCT *p)
{
    if (p->max < p->now)
    {
        p->max = p->now;
    }

    p->t++;
    if (p->t >= p->prd)     // 统计时间到
    {
        p->t = 0;
        p->max = p->now;
    }
}






//==============================================================================
//
// 剔除毛刺处理的函数
//
//==============================================================================
#if 0
void BurrFilter(BURR_FILTER_STRUCT *p)
{
    f32 tmp;

    tmp = _IQabs(p->newData - p->out);  // 差值

    if (tmp <= p->err)
    {
        p->out = p->newData;
        if (tmp <= (p->err/2))
        {
            p->err = (p->err/2);
        }
    }
    else
    {
        p->err = (p->err*2);
    }

    p->err = (p->err > p->errMax) ? (p->errMax) : (p->err);
    p->err = (p->err < p->errMin) ? (p->errMin) : (p->err);
}
#endif









/* Table of CRC values */
/*
const Uint16 crc16Table[256] =
{
0x0000, 0xC1C0, 0x81C1, 0x4001, 0x01C3, 0xC003, 0x8002, 0x41C2, 0x01C6, 0xC006, 0x8007, 0x41C7,
0x0005, 0xC1C5, 0x81C4, 0x4004, 0x01CC, 0xC00C, 0x800D, 0x41CD, 0x000F, 0xC1CF, 0x81CE, 0x400E,
0x000A, 0xC1CA, 0x81CB, 0x400B, 0x01C9, 0xC009, 0x8008, 0x41C8, 0x01D8, 0xC018, 0x8019, 0x41D9,
0x001B, 0xC1DB, 0x81DA, 0x401A, 0x001E, 0xC1DE, 0x81DF, 0x401F, 0x01DD, 0xC01D, 0x801C, 0x41DC,
0x0014, 0xC1D4, 0x81D5, 0x4015, 0x01D7, 0xC017, 0x8016, 0x41D6, 0x01D2, 0xC012, 0x8013, 0x41D3,
0x0011, 0xC1D1, 0x81D0, 0x4010, 0x01F0, 0xC030, 0x8031, 0x41F1, 0x0033, 0xC1F3, 0x81F2, 0x4032,
0x0036, 0xC1F6, 0x81F7, 0x4037, 0x01F5, 0xC035, 0x8034, 0x41F4, 0x003C, 0xC1FC, 0x81FD, 0x403D,
0x01FF, 0xC03F, 0x803E, 0x41FE, 0x01FA, 0xC03A, 0x803B, 0x41FB, 0x0039, 0xC1F9, 0x81F8, 0x4038,
0x0028, 0xC1E8, 0x81E9, 0x4029, 0x01EB, 0xC02B, 0x802A, 0x41EA, 0x01EE, 0xC02E, 0x802F, 0x41EF,
0x002D, 0xC1ED, 0x81EC, 0x402C, 0x01E4, 0xC024, 0x8025, 0x41E5, 0x0027, 0xC1E7, 0x81E6, 0x4026,
0x0022, 0xC1E2, 0x81E3, 0x4023, 0x01E1, 0xC021, 0x8020, 0x41E0, 0x01A0, 0xC060, 0x8061, 0x41A1,
0x0063, 0xC1A3, 0x81A2, 0x4062, 0x0066, 0xC1A6, 0x81A7, 0x4067, 0x01A5, 0xC065, 0x8064, 0x41A4,
0x006C, 0xC1AC, 0x81AD, 0x406D, 0x01AF, 0xC06F, 0x806E, 0x41AE, 0x01AA, 0xC06A, 0x806B, 0x41AB,
0x0069, 0xC1A9, 0x81A8, 0x4068, 0x0078, 0xC1B8, 0x81B9, 0x4079, 0x01BB, 0xC07B, 0x807A, 0x41BA,
0x01BE, 0xC07E, 0x807F, 0x41BF, 0x007D, 0xC1BD, 0x81BC, 0x407C, 0x01B4, 0xC074, 0x8075, 0x41B5,
0x0077, 0xC1B7, 0x81B6, 0x4076, 0x0072, 0xC1B2, 0x81B3, 0x4073, 0x01B1, 0xC071, 0x8070, 0x41B0,
0x0050, 0xC190, 0x8191, 0x4051, 0x0193, 0xC053, 0x8052, 0x4192, 0x0196, 0xC056, 0x8057, 0x4197,
0x0055, 0xC195, 0x8194, 0x4054, 0x019C, 0xC05C, 0x805D, 0x419D, 0x005F, 0xC19F, 0x819E, 0x405E,
0x005A, 0xC19A, 0x819B, 0x405B, 0x0199, 0xC059, 0x8058, 0x4198, 0x0188, 0xC048, 0x8049, 0x4189,
0x004B, 0xC18B, 0x818A, 0x404A, 0x004E, 0xC18E, 0x818F, 0x404F, 0x018D, 0xC04D, 0x804C, 0x418C,
0x0044, 0xC184, 0x8185, 0x4045, 0x0187, 0xC047, 0x8046, 0x4186, 0x0182, 0xC042, 0x8043, 0x4183,
0x0041, 0xC181, 0x8180, 0x4040,
};
*/

//==============================================================================
//
// CRC16计算
// *data为字节
//
//==============================================================================
#if 0
Uint16 CrcValueByteCalc(const Uint16 *data, Uint16 length)  // 已知最佳
{
    Uint16 crcValue = 0xFFFF;
    Uint16 tmp;

    while (length--)
    {
        tmp = crc16Table[(crcValue & 0x00FF) ^ *data++];
        crcValue = ((tmp & 0x00FF) << 8) + ((tmp ^ crcValue) >> 8);
    }

    return (crcValue);
}
#endif



//==============================================================================
//
// CRC16计算
// *data为字
//
//==============================================================================
/*
Uint16 CrcValueWordCalc(const Uint16 *data, Uint16 length)
{
    Uint16 crcValue = 0xFFFF;
    Uint16 tmp;
    Uint16 dataTmp;
    Uint16 dataTmpHigh;
    Uint16 dataTmpLow;

    while (length--)
    {
        dataTmp = *data++;
        dataTmpHigh = dataTmp >> 8;  // 先计算高位
        dataTmpLow = dataTmp & 0xFF;

        tmp = crc16Table[(crcValue & 0x00FF) ^ dataTmpHigh];
        crcValue = ((tmp & 0x00FF) << 8) + ((tmp ^ crcValue) >> 8);

        tmp = crc16Table[(crcValue & 0x00FF) ^ dataTmpLow];
        crcValue = ((tmp & 0x00FF) << 8) + ((tmp ^ crcValue) >> 8);
    }

    return (crcValue);
}
*/










