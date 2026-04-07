/*
 * Can00_Main.h
 *
 *  Created on: 2019年08月13日
 *      Author: zhuxc
 */

#ifndef Can00_Main_H
#define Can00_Main_H


#include "Can01_Can.h"
#include "Can02_ODBDef.h"
#include "Can03_ODBMngr.h"
#include "Can04_PDOMngr.h"
#include "Can05_SDOMngr.h"
#include "Can06_PosCmd.h"
#include "Can07_SpdCmd.h"
#include "Can08_TorqCmd.h"
#include "CanOpen_OrigSearch.h"

/*--------------------------------------------------------------------------------------------------*/
#define CanOPenVer  12                          /* CanOpen 版本号                                   */
/*--------------------------------------------------------------------------------------------------*/

#define CAN_EXFUNC0_0_EN        ((Prm.CanControl & 0x0001) == 0x0001)          //CAN自启动 PDO功能码映射

#define CAN_EXFUNC0_1_EN        ((Prm.CanControl & 0x0002) == 0x0002)          // CAN6-F启动
#define CAN_EXFUNC0_1_DIS       ((Prm.CanControl & 0x0002) == 0x0000)

#define CAN_EXFUNC0_2_EN        ((Prm.CanControl & 0x0004) == 0x0004)          //绝对位置自动更新
#define CAN_EXFUNC0_3_EN        ((Prm.CanControl & 0x0008) == 0x0008)          //绝对位置轮廓速度自动更新
#define CAN_EXFUNC0_4_EN        ((Prm.CanControl & 0x0010) == 0x0010)          //开环轮廓位置模式
#define CAN_EXFUNC0_5_EN        ((Prm.CanControl & 0x0020) == 0x0020)
#define CAN_EXFUNC0_6_EN        ((Prm.CanControl & 0x0040) == 0x0040)          //速度单位转换
#define CAN_EXFUNC0_7_EN        ((Prm.CanControl & 0x0080) == 0x0080)          //手自动切换
#define CAN_EXFUNC0_7_DIS       ((Prm.CanControl & 0x0080) == 0x0000)
#define CAN_EXFUNC0_8_EN        ((Prm.CanControl & 0x0100) == 0x0100)          //输入端子状态监控

#define CAN_EXFUNC0_10_EN       ((Prm.CanControl & 0x0400) == 0x0400)          //屏蔽【2000】组对象字典
#define CAN_EXFUNC0_10_DIS      ((Prm.CanControl & 0x0400) == 0x0000)

#define CAN_EXFUNC0_11_EN       ((Prm.CanControl & 0x0800) == 0x0800)          //转矩输出报警
#define CAN_EXFUNC0_12_EN       ((Prm.CanControl & 0x1000) == 0x1000)          //CAN急停快速停机
#define CAN_EXFUNC0_12_DIS      ((Prm.CanControl & 0x1000) == 0x0000)

#define CAN_EXFUNC0_13_EN       ((Prm.CanControl & 0x2000) == 0x2000)          //外部故障信号输入
#define CAN_EXFUNC0_14_EN       ((Prm.CanControl & 0x4000) == 0x4000)          //CAN回原运行到原点偏置

#define CAN_EXFUNC0_15_DIS       ((Prm.CanControl & 0x8000) == 0x0000)         //CAN复位节点通讯不进行PDO初始化

#define CAN_EXFUNC1_0_EN        ((Prm.CanControl2 & 0x0001) == 0x0001)         //原点回归状态EEPROM写入功能

#define CAN_EXFUNC1_1_DIS        ((Prm.CanControl2 & 0x0002) == 0x0000)
#define CAN_EXFUNC1_1_EN         ((Prm.CanControl2 & 0x0002) == 0x0002)

#define CAN_EXFUNC1_2_DIS        ((Prm.CanControl2 & 0x0004) == 0x0000)        //使能端子关联控制字
#define CAN_EXFUNC1_2_EN         ((Prm.CanControl2 & 0x0004) == 0x0004)        //使能端子关联控制字

#define CAN_EXFUNC1_3_DIS        ((Prm.CanControl2 & 0x0008) == 0x0000)        //EA机型断线报警
#define CAN_EXFUNC1_3_EN         ((Prm.CanControl2 & 0x0008) == 0x0008)   

#define CAN_EXFUNC1_4_DIS        ((Prm.CanControl2 & 0x0010) == 0x0000)        //【6041:bit10】位置到达判定标准修改
#define CAN_EXFUNC1_4_EN         ((Prm.CanControl2 & 0x0010) == 0x0010)

#define CiA402StatusMachine      ((Prm.CanControl2 & 0x0020) == 0x0020)        // CiA402协议切换
#define CiA402_SPEEDOVER_EN         ((Prm.CanControl2 & 0x0040) == 0x0040)        // 速度误差过大判定

#define ECAT_402_COUNT_UNIT      ((Prm.CanControl2 & 0x0080) == 0x0080)        // 单位cnt切换

#define MIT_402_EN               ((Prm.CanControl2 & 0x0200) == 0x0200)        // MIT参数采用402对象字典

extern void CanOpen_2msLoop( void );


#endif
