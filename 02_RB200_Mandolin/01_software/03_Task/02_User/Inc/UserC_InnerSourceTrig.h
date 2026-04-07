/*
 * UserC_InnerSourceTrig.h
 *
 *  Created on: 2023年2月29日
 *      Author: syhu
 */

#ifndef UserC_InnerSourceTrig_H
#define UserC_InnerSourceTrig_H


#define INNER_INPUT_FUNC    1

typedef struct
{
    UCHAR SglType;  //内部信号类型
    UCHAR SglTrig;  //内部信号触发
    LONG AmpVal;    // 幅值
    LONG OffSet;    //偏移量
    LONG Tperiod;  // 周期值（根据设定频率计算得出）
    LONG Tcnt;     // 时间计数
    LONG Theta;    //基于当前频率对应的角度
    LONG OutVal;   //内部信号输出
}INNERSIGNAL; //正弦波/方波激励信号

extern INNERSIGNAL CurSig;  //电流内部给定信号
extern INNERSIGNAL SpdSig;  //速度内部给定信号

extern void InputCurSigParaReset(void);
extern void InputSpdSigParaReset(void);
extern LONG InnerInputCal(INNERSIGNAL *Input);


#endif
