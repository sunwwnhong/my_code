/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
*
* File Name          : Seq09_StopMode.h
*
* Version            : V0.1
* Date               : 2024
***********************************************************************************************/

 #ifndef Seq09_StopMode_H
#define Seq09_StopMode_H
     
/*--------------------------------------------------------------------------------------------------*/
#define STOPMODE_NOTSTOP    0x00            /* 非停止（什么也不做）                                   */
#define STOPMODE_ZEROSTOP   0x01            /* 零速停止 G2故障等                                   */
#define STOPMODE_LDECSTOP   0x02            /* 減速停止                                             */
/*--------------------------------------------------------------------------------------------------*/
#define STOPMODE_DBSTOPDB   0x04            /* 通过(动态制动器)来停止电机(Pn004.1==0)               */
#define STOPMODE_DBSTOPFR   0x05            /* 通过DB停机，然后解除DB(Pn004.1==1)                    */
#define STOPMODE_FREERUN    0x06            /* 不使用DB，使电机处于自由运行状态(Pn004.1==2)            */
/*--------------------------------------------------------------------------------------------------*/
#define OTSTOPMODE_DEFAULT  0x00            //与伺服OFF停机保持一致
#define OTSTOPMODE_ZSTOPZC  0x01            //OT停机方式：按照最大转矩零速停机并锁轴
#define OTSTOPMODE_ZSTOPFR  0x02            //OT停机方式：按照最大转矩零速停机并进入自由状态

 
extern void	LpxStopModeManager( void );
 #endif
