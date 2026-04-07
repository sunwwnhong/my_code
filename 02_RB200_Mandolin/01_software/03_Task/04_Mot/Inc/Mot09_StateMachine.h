/*
 * Mot02_StateMachine.h
 *
 *  Created on: 2017年6月28日
 *      Author: zhuxc
 */
 #ifndef Mot09_StateMachine_H
#define Mot09_StateMachine_H
    
  
/**********************************基本控制模式定义********************************************/
#define CTRLMODE_SPD        0x0000          // 速度控制模式（模拟指令）
#define CTRLMODE_POS        0x0001          // 位置控制模式（脉冲列指令）
#define CTRLMODE_TRQ        0x0002          // 扭矩控制模式（模拟指令）
#define CTRLMODE_JOG        0x0003          // JOG运行模式
#define CTRLMODE_ZSRCH      0x0004          // 原点搜索模式
#define CTRLMODE_ZPHASE     0x0005          // 电机零点搜索
#define CTRLMODE_VF         0x0006          // VF模式
#define CTRLMODE_POS_MIT    0x0007          // MIT模式

/**********************************扩展控制模式定义********************************************/
#define CTRLMODE_CSPD       0x0100          // 内部设定速度控制模式(接点指令)
#define CTRLMODE_PJOG       0x0101          // 程序JOG运行模式
#define CTRLMODE_NOCMD      0xFFFF

/**********************************零控制模式定义*********************************************/
#define CTRLMODE_ZNONE      0x00            // No zero control
#define CTRLMODE_ZSTOP      0x01            // 零速停止模式:速度指令直接为0
#define CTRLMODE_ZCLMP      0x02            // 零位固定模式:速度指令为-位置误差*位置增益
#define CTRLMODE_DSTOP      0x03            // 减速停止模式:速度指令为梯形递减
#define CTRLMODE_DZSTOP     0x04
 
 
  
extern void StateMachine_Init(void);
 
#endif
