//==================================================================================================
//
// 交互经常需要修改的一些宏定义、结构体
// 以及 大样机、小样机的宏定义
// 
// 单独文件，修改之后减少编译时间
//
//
// Time-stamp: <2012-2-22 5:43:18  author, 0000>
//
//==================================================================================================


#ifndef __M_INTERFACE_MODIFY_H__
#define __M_INTERFACE_MODIFY_H__




#include "main.h"
#include "m_interfacePublic.h"
#include "m_blackBoxDeal.h"



// 会经常更改，所以单独文件






//=====================================================================
// 大样机、小样机的宏定义
// 会经常更改，所以也放在这个文件中
#define HW_CELL_ALL_FUNC    0                   // 0 -大样机，全功能小样机
#define HW_CELL_PART_FUNC   10                  // 10-非全功能小样机，2014年5月6日目前仅1台(4#，四象限小样机)
#define HD33_A_BIG          1 
#define HD33_A_SMALL        0  
#define HD33_A              0
#define HW_CELL             HW_CELL_ALL_FUNC    // 大样机，全功能小样机
//#define HW_CELL             HW_CELL_PART_FUNC   // 非全功能小样机，2014年5月6日目前仅1台(4#，四象限小样机)
//=====================================================================





//=====================================================================
// FPGA发波版本，0-HD90，0,1-电流波形包络有波动，2-2014年3月的版本
//#if (INV_TYPE == HW_HD90)
//#define FPGA_PWM_VER    0
//#elif 1
//#define FPGA_PWM_VER    1
//#define FPGA_PWM_VER    2
//#endif
#define FPGA_PWM_VER    2
//=====================================================================



//==============================================================================
// DSP与FPGA的交互
// 前面地址为 DSP写，ARM读
// 后面地址为 DSP读，ARM写
#define DSP_W_LEN               512     // DSP写的长度，前面AUTO_TUNE_PARA_LEN为调谐数据
#define DSP_R_LEN               512     // DSP读的长度

#define C2F_MSG_RAM_BASE_ADDR   0x000000    // 性能给功能的msg ram的base address
#define F2C_MSG_RAM_BASE_ADDR   DSP_W_LEN   // 功能给性能的msg ram的base address

#define DSP_W_TUNE_ADDR C2F_MSG_RAM_BASE_ADDR                   // DSP写(调谐数据autoTunePara)的偏移地址
#define DSP_W_ADDR      (DSP_W_TUNE_ADDR + AUTO_TUNE_PARA_LEN)  // DSP写(数据c2fData)的偏移地址
#define DSP_R_ADDR      F2C_MSG_RAM_BASE_ADDR                   // DSP读(数据f2cData)的偏移地址

#define FPGA_REG_BASE_ADDR      (DSP_R_ADDR+DSP_R_LEN)  // DSP与FPGA交互register(寄存器)的base address
#define FPGA_REG_LEN            1000        // DSP与FPGA交互register(寄存器)的长度
//==============================================================================



//==============================================================================
#define MAX_CELL_PER_PHASE  10          // 每相单元数的最大值
#define MAX_PHASE           3           // 多少相，最大值。一般是三相系统
#define MAX_CELLS           (MAX_PHASE * MAX_CELL_PER_PHASE)    // 系统最多有多少个单元。
//==============================================================================



//==============================================================================
// FPGA的寄存器地址
#define FPGA_REG_rsel_va_wr         (FPGA_REG_BASE_ADDR + 0x0000)
#define FPGA_REG_rsel_vap_wr        (FPGA_REG_BASE_ADDR + 0x0001)
#define FPGA_REG_rsel_vb_wr         (FPGA_REG_BASE_ADDR + 0x0002)
#define FPGA_REG_rsel_vbp_wr        (FPGA_REG_BASE_ADDR + 0x0003)
#define FPGA_REG_rsel_vc_wr         (FPGA_REG_BASE_ADDR + 0x0004)
#define FPGA_REG_rsel_vcp_wr        (FPGA_REG_BASE_ADDR + 0x0005)
#define FPGA_REG_rsel_va_step_wr    (FPGA_REG_BASE_ADDR + 0x0006)
#define FPGA_REG_rsel_vap_step_wr   (FPGA_REG_BASE_ADDR + 0x0007)
#define FPGA_REG_rsel_vb_step_wr    (FPGA_REG_BASE_ADDR + 0x0008)
#define FPGA_REG_rsel_vbp_step_wr   (FPGA_REG_BASE_ADDR + 0x0009)
#define FPGA_REG_rsel_vc_step_vr    (FPGA_REG_BASE_ADDR + 0x000a)
#define FPGA_REG_rsel_vcp_step_wr   (FPGA_REG_BASE_ADDR + 0x000b)
#define FPGA_REG_runEnable          (FPGA_REG_BASE_ADDR + 0x000c)   // 使能PWM
#define FPGA_REG_N1                 (FPGA_REG_BASE_ADDR + 0x000d)   // 写N1寄存器的值
#define FPGA_REG_A                  (FPGA_REG_BASE_ADDR + 0x000e)   // 写a寄存器的值
#define FPGA_REG_B                  (FPGA_REG_BASE_ADDR + 0x000f)   // 写b寄存器的值
#define FPGA_REG_N3                 (FPGA_REG_BASE_ADDR + 0x0010)   // 写N3寄存器的值
#define FPGA_REG_N2                 (FPGA_REG_BASE_ADDR + 0x0011)   // 写N2寄存器的值
#define FPGA_REG_reset_watchdog     (FPGA_REG_BASE_ADDR + 0x0012)
#define FPGA_REG_rsel_clk_ena       (FPGA_REG_BASE_ADDR + 0x0013)
#define FPGA_REG_Fb_rect_Flag       (FPGA_REG_BASE_ADDR + 0x0014)	//回馈整流标志

#define FPGA_REG_GENERAL_ERROR      (FPGA_REG_BASE_ADDR + 0x0020)
#define FPGA_REG_RST_ERROR          (FPGA_REG_BASE_ADDR + 0x0021)
#define FPGA_REG_ERROR              (FPGA_REG_BASE_ADDR + 0x0022)   // 整机过流故障
//#define FPGA_REG_DSP_W_VOL          (FPGA_REG_BASE_ADDR + 0x0023)   // DSP写电压指令
#define FPGA_REG_Ver_fpga           (FPGA_REG_BASE_ADDR + 0x0026)   // FPGA 版本地址

#define DSP_FEEDFORWARD             (FPGA_REG_BASE_ADDR + 0x0028)   // DSP写给FPGA，再传递给整流的前馈数据

#define FPGA_REG_COM_ERR_RST        (FPGA_REG_BASE_ADDR + 0x0033)   //通讯复位命令，写0x5A5A为复位
                                                                    //适用于FPGA两次通讯错误才报出来的程序
#define FPGA_CELLDIAG_EN            (FPGA_REG_BASE_ADDR + 0x003e)   // 单元诊断先向0x"003e"地址写0x"5A5A", 写完参数，再向这个地址写0x"A5A5"

#define FPGA_REG_N1_ENABLE          (FPGA_REG_BASE_ADDR + 0x0040)   // 写N1、N2、N3、a、b之前先向0x"0040"地址写“5A5A”, 写完参数，再向这个地址写“A5A5”


#define FPGA_REG_CARRIERl           (FPGA_REG_BASE_ADDR + 0x0060)
#define FPGA_REG_CARRIERH           (FPGA_REG_BASE_ADDR + 0x0061)
#define FPGA_REG_CARRIERINT         (FPGA_REG_BASE_ADDR + 0x0062)




#define FPGA_REG_R_N1               (FPGA_REG_BASE_ADDR + 0x0082)   // 读取N1寄存器的值
#define FPGA_REG_R_A                (FPGA_REG_BASE_ADDR + 0x0083)   // 读取a寄存器的值
#define FPGA_REG_R_B                (FPGA_REG_BASE_ADDR + 0x0084)   // 读取b寄存器的值
#define FPGA_REG_R_N3               (FPGA_REG_BASE_ADDR + 0x0085)   // 读取N3寄存器的值
#define FPGA_REG_R_N2               (FPGA_REG_BASE_ADDR + 0x0086)   // 读取N2寄存器的值


#define FPGA_REG_SyncStopReg0       (FPGA_REG_BASE_ADDR + 0x00b1)
#define FPGA_REG_SyncStopReg1       (FPGA_REG_BASE_ADDR + 0x0131)
#define FPGA_REG_SyncStopReg2       (FPGA_REG_BASE_ADDR + 0x01b1)
#define FPGA_REG_SyncStopReg3       (FPGA_REG_BASE_ADDR + 0x0231)
#define FPGA_REG_SyncStopReg4       (FPGA_REG_BASE_ADDR + 0x02b1)


#define FPGA_REG_VoltageReg0        (FPGA_REG_BASE_ADDR + 0x00b6)
#define FPGA_REG_VoltageReg1        (FPGA_REG_BASE_ADDR + 0x0136)
#define FPGA_REG_VoltageReg2        (FPGA_REG_BASE_ADDR + 0x01b6)
#define FPGA_REG_VoltageReg3        (FPGA_REG_BASE_ADDR + 0x0236)
#define FPGA_REG_VoltageReg4        (FPGA_REG_BASE_ADDR + 0x02b6)


#define FPGA_REG_cellOffset0        (FPGA_REG_BASE_ADDR + 0x0087)
#define FPGA_REG_cellOffset1        (FPGA_REG_BASE_ADDR + 0x0088)
#define FPGA_REG_cellOffset2        (FPGA_REG_BASE_ADDR + 0x0089)
#define FPGA_REG_cellOffset3        (FPGA_REG_BASE_ADDR + 0x008a)
#define FPGA_REG_cellOffset4        (FPGA_REG_BASE_ADDR + 0x008b)
#define FPGA_REG_cellOffset5        (FPGA_REG_BASE_ADDR + 0x008c)
#define FPGA_REG_cellOffset6        (FPGA_REG_BASE_ADDR + 0x0107)
#define FPGA_REG_cellOffset7        (FPGA_REG_BASE_ADDR + 0x0108)
#define FPGA_REG_cellOffset8        (FPGA_REG_BASE_ADDR + 0x0109)
#define FPGA_REG_cellOffset9        (FPGA_REG_BASE_ADDR + 0x010A)
#define FPGA_REG_cellOffset10       (FPGA_REG_BASE_ADDR + 0x010B)
#define FPGA_REG_cellOffset11       (FPGA_REG_BASE_ADDR + 0x010C)
#define FPGA_REG_cellOffset12       (FPGA_REG_BASE_ADDR + 0x0187)
#define FPGA_REG_cellOffset13       (FPGA_REG_BASE_ADDR + 0x0188)
#define FPGA_REG_cellOffset14       (FPGA_REG_BASE_ADDR + 0x0189)
#define FPGA_REG_cellOffset15       (FPGA_REG_BASE_ADDR + 0x018A)
#define FPGA_REG_cellOffset16       (FPGA_REG_BASE_ADDR + 0x018B)
#define FPGA_REG_cellOffset17       (FPGA_REG_BASE_ADDR + 0x018C)
#define FPGA_REG_cellOffset18       (FPGA_REG_BASE_ADDR + 0x0207)
#define FPGA_REG_cellOffset19       (FPGA_REG_BASE_ADDR + 0x0208)
#define FPGA_REG_cellOffset20       (FPGA_REG_BASE_ADDR + 0x0209)
#define FPGA_REG_cellOffset21       (FPGA_REG_BASE_ADDR + 0x020A)
#define FPGA_REG_cellOffset22       (FPGA_REG_BASE_ADDR + 0x020B)
#define FPGA_REG_cellOffset23       (FPGA_REG_BASE_ADDR + 0x020C)
#define FPGA_REG_cellOffset24       (FPGA_REG_BASE_ADDR + 0x0287)
#define FPGA_REG_cellOffset25       (FPGA_REG_BASE_ADDR + 0x0288)
#define FPGA_REG_cellOffset26       (FPGA_REG_BASE_ADDR + 0x0289)
#define FPGA_REG_cellOffset27       (FPGA_REG_BASE_ADDR + 0x028A)
#define FPGA_REG_cellOffset28       (FPGA_REG_BASE_ADDR + 0x028B)
#define FPGA_REG_cellOffset29       (FPGA_REG_BASE_ADDR + 0x028C)


#define FPGA_REG_cellFault0         (FPGA_REG_BASE_ADDR + 0x0093)
#define FPGA_REG_cellFault1         (FPGA_REG_BASE_ADDR + 0x0113)
#define FPGA_REG_cellFault2         (FPGA_REG_BASE_ADDR + 0x0193)
#define FPGA_REG_cellFault3         (FPGA_REG_BASE_ADDR + 0x0213)
#define FPGA_REG_cellFault4         (FPGA_REG_BASE_ADDR + 0x0293)

//单元通讯中断和奇偶校验故障寄存器
#define FPGA_REG_linkErr0           (FPGA_REG_BASE_ADDR + 0x0096)
#define FPGA_REG_linkErr1           (FPGA_REG_BASE_ADDR + 0x0116)
#define FPGA_REG_linkErr2           (FPGA_REG_BASE_ADDR + 0x0196)
#define FPGA_REG_linkErr3           (FPGA_REG_BASE_ADDR + 0x0216)
#define FPGA_REG_linkErr4           (FPGA_REG_BASE_ADDR + 0x0296) 


//   单元电压寄存器
#define FPGA_REG_VOLT0              (FPGA_REG_BASE_ADDR + 0x00b7)
#define FPGA_REG_VOLT1              (FPGA_REG_BASE_ADDR + 0x00b8)
#define FPGA_REG_VOLT2              (FPGA_REG_BASE_ADDR + 0x00b9)
#define FPGA_REG_VOLT3              (FPGA_REG_BASE_ADDR + 0x00ba)
#define FPGA_REG_VOLT4              (FPGA_REG_BASE_ADDR + 0x00bb)
#define FPGA_REG_VOLT5              (FPGA_REG_BASE_ADDR + 0x00bc)
#define FPGA_REG_VOLT6              (FPGA_REG_BASE_ADDR + 0x0137)
#define FPGA_REG_VOLT7              (FPGA_REG_BASE_ADDR + 0x0138)
#define FPGA_REG_VOLT8              (FPGA_REG_BASE_ADDR + 0x0139)
#define FPGA_REG_VOLT9              (FPGA_REG_BASE_ADDR + 0x013a)
#define FPGA_REG_VOLT10             (FPGA_REG_BASE_ADDR + 0x013b)
#define FPGA_REG_VOLT11             (FPGA_REG_BASE_ADDR + 0x013c)
#define FPGA_REG_VOLT12             (FPGA_REG_BASE_ADDR + 0x01b7)
#define FPGA_REG_VOLT13             (FPGA_REG_BASE_ADDR + 0x01b8)
#define FPGA_REG_VOLT14             (FPGA_REG_BASE_ADDR + 0x01b9)
#define FPGA_REG_VOLT15             (FPGA_REG_BASE_ADDR + 0x01ba)
#define FPGA_REG_VOLT16             (FPGA_REG_BASE_ADDR + 0x01bb)
#define FPGA_REG_VOLT17             (FPGA_REG_BASE_ADDR + 0x01bc)
#define FPGA_REG_VOLT18             (FPGA_REG_BASE_ADDR + 0x0237)
#define FPGA_REG_VOLT19             (FPGA_REG_BASE_ADDR + 0x0238)
#define FPGA_REG_VOLT20             (FPGA_REG_BASE_ADDR + 0x0239)
#define FPGA_REG_VOLT21             (FPGA_REG_BASE_ADDR + 0x023a)
#define FPGA_REG_VOLT22             (FPGA_REG_BASE_ADDR + 0x023b)
#define FPGA_REG_VOLT23             (FPGA_REG_BASE_ADDR + 0x023c)
#define FPGA_REG_VOLT24             (FPGA_REG_BASE_ADDR + 0x02b7)//
#define FPGA_REG_VOLT25             (FPGA_REG_BASE_ADDR + 0x02b8)
#define FPGA_REG_VOLT26             (FPGA_REG_BASE_ADDR + 0x02b9)
#define FPGA_REG_VOLT27             (FPGA_REG_BASE_ADDR + 0x02ba)
#define FPGA_REG_VOLT28             (FPGA_REG_BASE_ADDR + 0x02bb)
#define FPGA_REG_VOLT29             (FPGA_REG_BASE_ADDR + 0x02bc)



#define FPGA_REG_rsel_vd_afe_wr    (FPGA_REG_BASE_ADDR + 0x01da)
//#define FPGA_REG_rsel_vq_afe_wr    (FPGA_REG_BASE_ADDR + 0x01d8)
//#define FPGA_REG_rsel_theta_wr     (FPGA_REG_BASE_ADDR + 0x01d9)

#define FPGA_REG_rsel_vd_afe_rd    (FPGA_REG_BASE_ADDR + 0x01d7)
#define FPGA_REG_rsel_vq_afe_rd    (FPGA_REG_BASE_ADDR + 0x01d8)
#define FPGA_REG_rsel_theta_rd    (FPGA_REG_BASE_ADDR + 0x01d9)

#define FPGA_REG_portsel_en         (FPGA_REG_BASE_ADDR + 0x0041) 
   
//FPGA光纤通讯端口设定寄存器，可以通过写以下寄存器的值，完成30个单元的通讯端口设定
//FPGA端口设定值读取，可以读取已经设定的端口值 


// 高炉鼓风机双机并联
#define FPGA_REG_IU_wr                  (FPGA_REG_BASE_ADDR + 0x0052)
#define FPGA_REG_IV_wr                  (FPGA_REG_BASE_ADDR + 0x0053)
#define FPGA_REG_VU_wr                  (FPGA_REG_BASE_ADDR + 0x0054)
#define FPGA_REG_VV_wr                  (FPGA_REG_BASE_ADDR + 0x0055)
#define FPGA_REG_VW_wr                  (FPGA_REG_BASE_ADDR + 0x0056)
#define FPGA_REG_WR_end                 (FPGA_REG_BASE_ADDR + 0x005c)  //凯撒中在主机写完VA,VB,VC的时候 也需要
                                                                       //操作一下 该寄存器，表示主机发送的值也完成






#define FPGA_REG_IU_rd                  (FPGA_REG_BASE_ADDR + 0x0057)
#define FPGA_REG_IV_rd                  (FPGA_REG_BASE_ADDR + 0x0058)
#define FPGA_REG_VU_rd                  (FPGA_REG_BASE_ADDR + 0x0059)
#define FPGA_REG_VV_rd                  (FPGA_REG_BASE_ADDR + 0x005a)
#define FPGA_REG_VW_rd                  (FPGA_REG_BASE_ADDR + 0x005b)
#define FPGA_REG_SEND_end               (FPGA_REG_BASE_ADDR + 0x0069) 


// HD3x采样板，这些地址是连续的
#define FPGA_REG_SampleCh1              (FPGA_REG_BASE_ADDR + 0x006a)   // 采样板7606通道1采样的值
#define FPGA_REG_SampleCh2              (FPGA_REG_BASE_ADDR + 0x006b)   // 采样板7606通道2采样的值
#define FPGA_REG_SampleCh3              (FPGA_REG_BASE_ADDR + 0x006c)   // 采样板7606通道3采样的值
#define FPGA_REG_SampleCh4              (FPGA_REG_BASE_ADDR + 0x006d)   // 采样板7606通道4采样的值 
#define FPGA_REG_SampleCh5              (FPGA_REG_BASE_ADDR + 0x006e)   // 采样板7606通道5采样的值
#define FPGA_REG_SampleCh6              (FPGA_REG_BASE_ADDR + 0x006f)   // 采样板7606通道6采样的值
#define FPGA_REG_SampleCh7              (FPGA_REG_BASE_ADDR + 0x0070)   // 采样板7606通道7采样的值
#define FPGA_REG_SampleCh8              (FPGA_REG_BASE_ADDR + 0x0071)   // 采样板7606通道8采样的值 
#define FPGA_REG_SampleUpdata           (FPGA_REG_BASE_ADDR + 0x0072)   // 采样数据更新标识寄存器，更新即加1


// 二代板的AD7606采样
#define FPGA_REG_SampleSecondBoardCh1   (FPGA_REG_BASE_ADDR + 0x0073)

//调谐定子电阻占空比
#define FPGA_TUNE_Rs_Ua_Duty         		(FPGA_REG_BASE_ADDR + 0x00c0)
#define FPGA_Rotor_Position_wr         (FPGA_REG_BASE_ADDR + 0x00c3)   //转子位置辨识 寄存器值需要确认
//#define FPGA_Rotor_Position_wr1         (FPGA_REG_BASE_ADDR + 0x00c3) 
//#define FPGA_REG_port1sel_rd           (FPGA_REG_BASE_ADDR + 0x00c3) 
#define FPGA_REG_port2sel_rd           (FPGA_REG_BASE_ADDR + 0x00c4)  //输出电压采样读取U
#define FPGA_REG_port3sel_rd           (FPGA_REG_BASE_ADDR + 0x00c5)  //输出电压采样读取U
#define FPGA_REG_port4sel_rd           (FPGA_REG_BASE_ADDR + 0x00c6) 
#define FPGA_REG_port5sel_rd           (FPGA_REG_BASE_ADDR + 0x00c7) 
#define FPGA_REG_port6sel_rd           (FPGA_REG_BASE_ADDR + 0x00c8)
                        
#define FPGA_REG_port7sel_rd           (FPGA_REG_BASE_ADDR + 0x0143) 
#define FPGA_REG_port8sel_rd           (FPGA_REG_BASE_ADDR + 0x0144) 
#define FPGA_REG_port9sel_rd           (FPGA_REG_BASE_ADDR + 0x0145) 
#define FPGA_REG_port10sel_rd          (FPGA_REG_BASE_ADDR + 0x0146) 
#define FPGA_REG_port11sel_rd          (FPGA_REG_BASE_ADDR + 0x0147) 
#define FPGA_REG_port12sel_rd          (FPGA_REG_BASE_ADDR + 0x0148)
                         
#define FPGA_REG_port13sel_rd          (FPGA_REG_BASE_ADDR + 0x01c3) 
#define FPGA_REG_port14sel_rd          (FPGA_REG_BASE_ADDR + 0x01c4) 
#define FPGA_REG_port15sel_rd          (FPGA_REG_BASE_ADDR + 0x01c5) 
#define FPGA_REG_port16sel_rd          (FPGA_REG_BASE_ADDR + 0x01c6) 
#define FPGA_REG_port17sel_rd          (FPGA_REG_BASE_ADDR + 0x01c7) 
#define FPGA_REG_port18sel_rd          (FPGA_REG_BASE_ADDR + 0x01c8) 
                         
#define FPGA_REG_port19sel_rd          (FPGA_REG_BASE_ADDR + 0x0243) 
#define FPGA_REG_port20sel_rd          (FPGA_REG_BASE_ADDR + 0x0244) 
#define FPGA_REG_port21sel_rd          (FPGA_REG_BASE_ADDR + 0x0245) 
#define FPGA_REG_port22sel_rd          (FPGA_REG_BASE_ADDR + 0x0246) 
#define FPGA_REG_port23sel_rd          (FPGA_REG_BASE_ADDR + 0x0247) 
#define FPGA_REG_port24sel_rd          (FPGA_REG_BASE_ADDR + 0x0248)
                         
#define FPGA_REG_port25sel_rd          (FPGA_REG_BASE_ADDR + 0x02c3) 
#define FPGA_REG_port26sel_rd          (FPGA_REG_BASE_ADDR + 0x02c4) 
#define FPGA_REG_port27sel_rd          (FPGA_REG_BASE_ADDR + 0x02c5) 
#define FPGA_REG_port28sel_rd          (FPGA_REG_BASE_ADDR + 0x02c6) 
#define FPGA_REG_port29sel_rd          (FPGA_REG_BASE_ADDR + 0x02c7) 
#define FPGA_REG_port30sel_rd          (FPGA_REG_BASE_ADDR + 0x02c8)      


#define FPGA_REG_temp0              (FPGA_REG_BASE_ADDR + 0x008d)
#define FPGA_REG_temp1              (FPGA_REG_BASE_ADDR + 0x008e)
#define FPGA_REG_temp2              (FPGA_REG_BASE_ADDR + 0x008f)
#define FPGA_REG_temp3              (FPGA_REG_BASE_ADDR + 0x0090)
#define FPGA_REG_temp4              (FPGA_REG_BASE_ADDR + 0x0091)
#define FPGA_REG_temp5              (FPGA_REG_BASE_ADDR + 0x0092)
#define FPGA_REG_temp6              (FPGA_REG_BASE_ADDR + 0x010d)
#define FPGA_REG_temp7              (FPGA_REG_BASE_ADDR + 0x010e)
#define FPGA_REG_temp8              (FPGA_REG_BASE_ADDR + 0x010f)
#define FPGA_REG_temp9              (FPGA_REG_BASE_ADDR + 0x0110)
#define FPGA_REG_temp10             (FPGA_REG_BASE_ADDR + 0x0111)
#define FPGA_REG_temp11             (FPGA_REG_BASE_ADDR + 0x0112)
#define FPGA_REG_temp12             (FPGA_REG_BASE_ADDR + 0x018d)
#define FPGA_REG_temp13             (FPGA_REG_BASE_ADDR + 0x018e)
#define FPGA_REG_temp14             (FPGA_REG_BASE_ADDR + 0x018f)
#define FPGA_REG_temp15             (FPGA_REG_BASE_ADDR + 0x0190)
#define FPGA_REG_temp16             (FPGA_REG_BASE_ADDR + 0x0191)
#define FPGA_REG_temp17             (FPGA_REG_BASE_ADDR + 0x0192)
#define FPGA_REG_temp18             (FPGA_REG_BASE_ADDR + 0x020d)
#define FPGA_REG_temp19             (FPGA_REG_BASE_ADDR + 0x020e)
#define FPGA_REG_temp20             (FPGA_REG_BASE_ADDR + 0x020f)
#define FPGA_REG_temp21             (FPGA_REG_BASE_ADDR + 0x0210)
#define FPGA_REG_temp22             (FPGA_REG_BASE_ADDR + 0x0211)
#define FPGA_REG_temp23             (FPGA_REG_BASE_ADDR + 0x0212)
#define FPGA_REG_temp24             (FPGA_REG_BASE_ADDR + 0x028d)
#define FPGA_REG_temp25             (FPGA_REG_BASE_ADDR + 0x028e)
#define FPGA_REG_temp26             (FPGA_REG_BASE_ADDR + 0x028f)
#define FPGA_REG_temp27             (FPGA_REG_BASE_ADDR + 0x0290)
#define FPGA_REG_temp28             (FPGA_REG_BASE_ADDR + 0x0291)
#define FPGA_REG_temp29             (FPGA_REG_BASE_ADDR + 0x0292)

// 单元故障屏蔽
//#define FPGA_REG_FAULT_BLOCK00      (FPGA_REG_BASE_ADDR + 0x0095)  // 输出电压采样卡读取信号 RS                  //block0, bit0-5表示cell1-6；   
                                                                                                  // bit8-13表示link1-6，其他未用
//#define FPGA_REG_FAULT_BLOCK01      (FPGA_REG_BASE_ADDR + 0x0098)   //输出电压采样卡读取信号  ST                                // bit0、2、4、6、8、10分别表示commfault1-6
                                                                                                   // bit1、3、5、7、9、11分别表示parity_error1-6
#define FPGA_REG_FAULT_BLOCK10      (FPGA_REG_BASE_ADDR + 0x0115)
#define FPGA_REG_FAULT_BLOCK11      (FPGA_REG_BASE_ADDR + 0x0118)
#define FPGA_REG_FAULT_BLOCK20      (FPGA_REG_BASE_ADDR + 0x0195)
#define FPGA_REG_FAULT_BLOCK21      (FPGA_REG_BASE_ADDR + 0x0198)
#define FPGA_REG_FAULT_BLOCK30      (FPGA_REG_BASE_ADDR + 0x0215)
#define FPGA_REG_FAULT_BLOCK31      (FPGA_REG_BASE_ADDR + 0x0218)
#define FPGA_REG_FAULT_BLOCK40      (FPGA_REG_BASE_ADDR + 0x0295)  
#define FPGA_REG_FAULT_BLOCK41      (FPGA_REG_BASE_ADDR + 0x0298)  

// 单元返回的通讯数据  //永磁同步电机电感，转子位置辨识返回时间及电流寄存器 
#define FPGA_REG_cellDb_A1          (FPGA_REG_BASE_ADDR + 0x00a3)   // A1
#define FPGA_REG_cellDb_B1          (FPGA_REG_BASE_ADDR + 0x00a4)   // B1
#define FPGA_REG_cellDb_C1          (FPGA_REG_BASE_ADDR + 0x00a5)   // C1
#define FPGA_REG_cellDb_A2          (FPGA_REG_BASE_ADDR + 0x00a6)   // A2
#define FPGA_REG_cellDb_B2          (FPGA_REG_BASE_ADDR + 0x00a7)   // B2
#define FPGA_REG_cellDb_C2          (FPGA_REG_BASE_ADDR + 0x00a8)   // C2
#define FPGA_REG_cellDb_A3          (FPGA_REG_BASE_ADDR + 0x0123)   // A3
#define FPGA_REG_cellDb_B3          (FPGA_REG_BASE_ADDR + 0x0124)   // B3
#define FPGA_REG_cellDb_C3          (FPGA_REG_BASE_ADDR + 0x0125)   // C3
#define FPGA_REG_cellDb_A4          (FPGA_REG_BASE_ADDR + 0x0126)   // A4
#define FPGA_REG_cellDb_B4          (FPGA_REG_BASE_ADDR + 0x0127)   // B4
#define FPGA_REG_cellDb_C4          (FPGA_REG_BASE_ADDR + 0x0128)   // C4
#define FPGA_REG_cellDb_A5          (FPGA_REG_BASE_ADDR + 0x01a3)   // A5
#define FPGA_REG_cellDb_B5          (FPGA_REG_BASE_ADDR + 0x01a4)   // B5
#define FPGA_REG_cellDb_C5          (FPGA_REG_BASE_ADDR + 0x01a5)   // C5
#define FPGA_REG_cellDb_A6          (FPGA_REG_BASE_ADDR + 0x01a6)   // A6
#define FPGA_REG_cellDb_B6          (FPGA_REG_BASE_ADDR + 0x01a7)   // B6
#define FPGA_REG_cellDb_C6          (FPGA_REG_BASE_ADDR + 0x01a8)   // C6
#define FPGA_REG_cellDb_A7          (FPGA_REG_BASE_ADDR + 0x0223)   // A7
#define FPGA_REG_cellDb_B7          (FPGA_REG_BASE_ADDR + 0x0224)   // B7
#define FPGA_REG_cellDb_C7          (FPGA_REG_BASE_ADDR + 0x0225)   // C7
#define FPGA_REG_cellDb_A8          (FPGA_REG_BASE_ADDR + 0x0226)   // A8
#define FPGA_REG_cellDb_B8          (FPGA_REG_BASE_ADDR + 0x0227)   // B8
#define FPGA_REG_cellDb_C8          (FPGA_REG_BASE_ADDR + 0x0228)   // C8
#define FPGA_REG_cellDb_A9          (FPGA_REG_BASE_ADDR + 0x02a3)   // A9
#define FPGA_REG_cellDb_B9          (FPGA_REG_BASE_ADDR + 0x02a4)   // B9
#define FPGA_REG_cellDb_C9          (FPGA_REG_BASE_ADDR + 0x02a5)   // C9
#define FPGA_REG_cellDb_A10         (FPGA_REG_BASE_ADDR + 0x02a6)   // A10
#define FPGA_REG_cellDb_B10         (FPGA_REG_BASE_ADDR + 0x02a7)   // B10
#define FPGA_REG_cellDb_C10         (FPGA_REG_BASE_ADDR + 0x02a8)   // C10


#define FPGA_REG_OUT_VOLTAGEU        (FPGA_REG_BASE_ADDR + 0x0095)   // C10  输出电压采样U
#define FPGA_REG_OUT_VOLTAGEV        (FPGA_REG_BASE_ADDR + 0x0098)   // C10
#define FPGA_REG_OUT_VOLTAGEW        (FPGA_REG_BASE_ADDR + 0x019B)   // C10
// 单元旁路命令
#define FPGA_REG_bypassCmd0         (FPGA_REG_BASE_ADDR + 0x00ad)   // 设定电流模式下的电流绝对值
#define FPGA_REG_bypassCmd1         (FPGA_REG_BASE_ADDR + 0x012d)  //  永磁同步电机脉冲发波方式控制字
#define FPGA_REG_bypassCmd2         (FPGA_REG_BASE_ADDR + 0x01ad)  //  设定的脉冲宽度时间值
#define FPGA_REG_bypassCmd3         (FPGA_REG_BASE_ADDR + 0x022d)  //   
#define FPGA_REG_bypassCmd4         (FPGA_REG_BASE_ADDR + 0x02ad)

// 单元旁路反馈
#define FPGA_REG_bypassFdb0         (FPGA_REG_BASE_ADDR + 0x00ae)   // 低六位有效,A1,B1,C1,A2,B2,C2
//#define FPGA_REG_CurSampleDelay		(FPGA_REG_BASE_ADDR + 0x00ae)

#define FPGA_REG_bypassFdb1         (FPGA_REG_BASE_ADDR + 0x012e)
#define FPGA_REG_bypassFdb2         (FPGA_REG_BASE_ADDR + 0x01ae)
#define FPGA_REG_bypassFdb3         (FPGA_REG_BASE_ADDR + 0x022e)
#define FPGA_REG_bypassFdb4         (FPGA_REG_BASE_ADDR + 0x02ae)

#define Dsp_wr_rsvd1                (FPGA_REG_BASE_ADDR + 0x0060)
#define Dsp_wr_rsvd2                (FPGA_REG_BASE_ADDR + 0x0061)
#define Dsp_wr_rsvd3                (FPGA_REG_BASE_ADDR + 0x0062)
#define Dsp_wr_rsvd4               (FPGA_REG_BASE_ADDR + 0x0063) //可以作为DO 的写寄存器
#define Dsp_wr_rsvd5               (FPGA_REG_BASE_ADDR + 0x0064) //可以作为DO 的写寄存器

#define Dsp_rd_rsvd1                (FPGA_REG_BASE_ADDR + 0x0065) //可以作为DI 的读寄存器
#define Dsp_rd_rsvd2               (FPGA_REG_BASE_ADDR + 0x0066) //可以作为DI 的读寄存器
#define Dsp_rd_rsvd3               (FPGA_REG_BASE_ADDR + 0x0067) //UIGBT 故障
#define Dsp_rd_rsvd4                 (FPGA_REG_BASE_ADDR + 0x0068) //VIGBT故障
#define Dsp_rd_rsvd5               (FPGA_REG_BASE_ADDR + 0x0069) //WIGBT故障
//==============================================================================
// DSP  到FPGA 的功能相关的数据交互
//==============================================================================


//  DSP 写
#define FPGA_REG_DO0         (FPGA_REG_BASE_ADDR + 0x02b0)  // DO 1-16
#define FPGA_REG_DO1         (FPGA_REG_BASE_ADDR + 0x02b1)  // DO 17-32
#define FPGA_REG_AUX_CMD    (FPGA_REG_BASE_ADDR + 0x02b2)  // DO 17-32
//#define FPGA_REG_Ver        (FPGA_REG_BASE_ADDR + 0x02b1)  // FPGA 版本号已经有了
#define FPGA_REG_selfCeck   (FPGA_REG_BASE_ADDR + 0x02b3)  // 自检模式下的IGBT驱动
//  DSP 读
#define FPGA_REG_DI0         (FPGA_REG_BASE_ADDR + 0x02C0)  // DI 1-16
#define FPGA_REG_DI1         (FPGA_REG_BASE_ADDR + 0x02C1)  // DI 17-32
//#define FPGA_REG_selfCeck   (FPGA_REG_BASE_ADDR + 0x02C2)  // 自检模式下的IGBT驱动





//==============================================================================
#define FPGA_N1_ENABLE      0x5A5A      // 开启写N1N2N3ab寄存器使能的值
#define FPGA_N1_DISENABLE   0xA5A5      // 关闭写N1N2N3ab寄存器使能的值
//==============================================================================




//==============================================================================
// 功能->性能的交互数据
#define F2C_TEST_PARA_LEN       10  // CE组，调测使用的参数
#define F2C_DEBUG_PARA_LEN      25  // CF组，功能给性能，调试使用的参数
//==============================================================================
// 请确保 sizeof(struct FUNC_TO_CORE_SLOW_DATA_A_STRUCT)与
// sizeof(struct FUNC_TO_CORE_SLOW_DATA_B_STRUCT) 两者一样。
struct FUNC_TO_CORE_SLOW_DATA_A_STRUCT
{
    u16 upperTorque;            // 0    转矩限定，速度控制的电动转矩
    u16 frqCurAim2Core;         // 1    当前目标频率. 减速(停机)时为0
    u16 carrierFrq;             // 2    载波频率，单元开关频率
    u16 maxFrq;                 // 3    最大频率
    u16 upperTorqueRegen;       // 4    速度控制的发电转矩
    u16 curSampleDelayComp;     // 5   电流检测延时补偿
    u16 motorTripVoltage;       // 6   电机过压保护点
    u16 spinningLoadPara[3];    // 7-9 飞车启动参数 F6-16 - 18
    u16 SyncTransferMenu[6];    // 10-15 同步切换
    u16 invIOCSetpoint;         // 16 F9-30 过流点设定
    u16 invCurrentLimit;        // 17 F9-31 

    struct MOTOR_PARA_STRUCT_ARM motorParaArm;  // 18-27 F1-00 - F1-26 电机参数，注意与功能码顺序不全不一致，目前10个
    union PG_PARA pgPara;                       // 28-34 F1-27 - F1-36 PG卡参数，目前7个
    
    u16 SpeedLoopMenu[9];                // 35-43 F2-00 - F2-08 速度环参数
    u16 CurrentLoopMenu[4];              // 44-47 F2-13 - F2-16 电流环参数
    u16 LowFrequencyCompensationMenu[3]; // 48-50 A5-08 - A5-10 
    u16 FluxContrlMenu[5];               // 51-55 F2-23 - F2-27
    u16 overLoadPara[3];                 // 56-58 F9-01 - F9-03
    u16 uvGainWarp;                      // 59 FF-05 UV两相增益偏差
    u16 cellBypassCmdArmL;               // 60 单元0-15的旁路命令
    u16 cellBypassCmdArmH;               // 61 单元16-29的旁路命令
    u16 cellCheckFlag;                   // 62 单元检测标记

    u16 CellMenu[4];                     // 63-66 
    u16 zeroSpeed;                       // 67 F8-47
    u16 protectMenu[15];                 // 68-82 F9-14 - F9-28, F9-15输出电流不平衡阈值, F9-17保留，F9-27保留
    u16 BrakingMenu[4];                  // 83-86 F6-12 - F6-15
    u16 VolCurSampleMenu[10];            // 87-96 FF-06 - FF-15
    
    u16 DriveRatingMenu[4];              // 97-100 FF-16 - FF-19
    u16 DeadTimeComp;                    // 101  A5-00
   u16 rsvd_slowA;                             // 102 保留
    u16 offTransitoryMenu[2];            // 103-104
     u16 rsvd2;                           // 105
    u16 overVolInhibitKp;                // 106 过压抑制电压环Kp 
    u16 overVolInhibitKi;                // 107 过压抑制电压环Ki
    u16 IfModeRefCur;		    		 // F1-11 IF模式设定电流 // LS_20240229
    u16 PMLowSpdIdAddCur;		    	 // F1-12 同步机低速d轴注入电流 // LS_20240229
    u16 rotorResistance;                 // F1-07 异步机转子电阻 // LS_20240325
    u16 rsvd[12-3];						 // 105-119 // LS_20240325
};
#define FUNC_TO_CORE_SLOW_DATA_A_LEN  (sizeof(struct FUNC_TO_CORE_SLOW_DATA_A_STRUCT)/(sizeof(u16)))
struct FUNC_TO_CORE_SLOW_DATA_B_STRUCT
{
    u16 FeedForwardConstant;                // 0  A5-01   电流环前馈增益
    u16 fluxLoopFeedForwardGain;            // 1  A5-02   磁链环前馈增益
    u16 OutputConnectionMenu[6];            // 2-7 FF-23, A5-03 - A5-07
    u16 HighStartingTorqueMenu[3];          // 8-10 A5-12 - A5-14
    u16 fluxCompLimit;                      // 11  A5-15 磁链观测补偿限幅
    u16 fluxLoopCloseFrq;                   // 12  A5-16 磁链闭环频率
    u16 fluxOpenIdRef;                      // 13  A5-17 磁链开环时励磁电流给定
    u16 motorControlOtherEnable;            // 14  A5-18 各种使能
    u16 npcKp;                              // 15  A5-19 中点控制比例增益
    u16 npcKi;                              // 16  A5-20 中点控制积分增益
    u16 npcMax;                             // 17  A5-21 中点控制输出上限 
    u16 rsvdA5[1];                          // 18  A5-22
    u16 halfGenVolOV;                       // 19  A5-23 半母线过压点设定
    u16 halfGenVolOL;                       // 20  A5-24 半母线超限点设定
    u16 coreFunc[2];                        // 21- 22  F9-72 其它故障保护选择1、F9-73
    u16 windowFrq;                          // 23  负荷分配，视窗
    u16 aoData[9];                          // 24-32
    u16 ceTestPara[F2C_TEST_PARA_LEN];      // 33-42 测试参数，在CE[]
    
    u16 debugParaCF[F2C_DEBUG_PARA_LEN];    // 43-67 功能给性能的调试参数，目前为25个，在CF[]


    u16 flowSampleAddr[6];                  // 68-73 C0-00~C0-06
    u16 motorStall[2];                      // 74-75 F9-40~F9-41
    u16 motorExcitation[2];                 // 76-77 F9-42~F9-43
    u16 rsvd_slow[20];                      // 78-97
    u16 genVolOV;                           // 98 A5-25 母线过压点设定
    u16 genVolOL;                           // 99 A5-26 母线超限点设定
    u16 rsvd[24];							// 100-119 保留20个

};
#define FUNC_TO_CORE_SLOW_DATA_B_LEN  (sizeof(struct FUNC_TO_CORE_SLOW_DATA_B_STRUCT)/(sizeof(u16)))
union FUNC_TO_CORE_SLOW_DATA
{
    u16 all[FUNC_TO_CORE_SLOW_DATA_A_LEN];

    struct FUNC_TO_CORE_SLOW_DATA_A_STRUCT codeA;
    struct FUNC_TO_CORE_SLOW_DATA_B_STRUCT codeB;
};


struct FUNC_TO_CORE_DATA_STRUCT
{
    u16 mainCmd;                // 0    主命令字
    u16 frq2Core;               // 1    实时速度给定
    u16 mainCmd1;               // 2    主命令字1
    u16 subCmd;                 // 3    辅助命令字
    u16 tuneCmd;                // 4    调谐选择
    
    u16 vfSeparateVol;          // 5    VF分离时的输出电压
    u16 vfCurve;                // 6    VF曲线选择
    u16 ovGain;                 // 7    过压失速增益
    u16 ovPoint;                // 8    过压失速保护电压
    u16 ocGain;                 // 9    过流失速增益
    u16 ocPoint;                // 10   过流失速保护电流

    u16 masterTorque;           // 11   负荷分配，主从控制 主机输出转矩
    u16 masterSpeedMotor;       // 12   负荷分配，主机同步频率
    
    u16 rsvd_Fast[10];       // 13-22 预留10个

//===以上，每1拍传递1次
//---------------------------------------------------------------------
//===以下，每2拍传递1次

    union FUNC_TO_CORE_SLOW_DATA slowData;  // 23-142 共120个

//============
    u16 flag;                // 143 arm标记位
    u16 crc;                 // 144
    u16 rsvdEnd;             // 145 任何时候都不用这个数据且放到最后
};
#define FUNC_TO_CORE_DATA_LEN  (sizeof(struct FUNC_TO_CORE_DATA_STRUCT)/(sizeof(u16)))
union FUNC_TO_CORE_DATA
{
    u16 all[FUNC_TO_CORE_DATA_LEN];

    struct FUNC_TO_CORE_DATA_STRUCT code;
};
//extern union FUNC_TO_CORE_DATA f2cData;
//==============================================================================




//==============================================================================
// 性能->功能的交互数据
#define CORE_TO_FUNC_DEBUG_PARA_LEN     15  // UF组，性能给功能，调试使用的参数
// 请确保 sizeof(struct CORE_TO_FUNC_SLOW_DATA_A_STRUCT)与
// sizeof(struct CORE_TO_FUNC_SLOW_DATA_B_STRUCT) 两者一样。
struct CORE_TO_FUNC_SLOW_DATA_A_STRUCT
{
    u16 currentPu;                  // 0    电流标幺值，当电机额定电流与变频器的额定电流相差较大时，可能与电机额定电流不同.
    u16 ai1Sample;                  // 1    AI1的采样值，已经滤波
    u16 ai2Sample;                  // 2    AI2的采样值，已经滤波
    u16 inputCurrent;               // 3    输入电流
    u16 coreMaxFrqBypass;           // 4    旁路运行最大频率限制

    u16 motorSoftVersion;           // 5    DSP软件版本号
    u16 FPGAVersion;                // 6    FPGA 软件版本号

    u16 cellBypassFdbL;             // 7    单元0-15旁路完成标记
    u16 cellBypassFdbH;             // 8    单元16-29旁路完成标记
    u16 cellBypassEnableL;          // 9    允许旁路的单元标记 0-15
    u16 cellBypassEnableH;          // 10   允许旁路的单元标记 16-29

    u16 coreErrorCode;              // 11   Ux-00   性能产生的故障
    u16 fastLoopClks;               // 12   Ux-01   快环花销的时钟周期，0.1us
    u16 mainLoopUs;                 // 13   Ux-02   主循环花销的时间，0.1us
    u16 coreCarrierFrqAct;          // 14   Ux-03   (单元的)(实际使用的)载波频率，0.1Hz
    u16 fastLoopFrequency;          // 15   Ux-04   快环频率(整机载波频率)，Hz
    u16 inputSAct;                  // 16   Ux-05   输入视在功率，单位0.1kVA
    u16 inputPowerAct;              // 17   Ux-06   输入功率，单位0.1kW
    u16 outputPowerAct;             // 18   Ux-07   输出功率，单位0.1kW
    u16 driveLosses;                // 19   Ux-08   变频器损耗，0.1%
    u16 coreInfo0[1];               // 20   Ux-09   无单位

    u16 debugParaUF[CORE_TO_FUNC_DEBUG_PARA_LEN];    // 21-35 #使用UF[]组
    
//    u16 iTotalMotor;                // 36   !!!电机电流，双机并联用，目前不合并在HD90里
    u16 idCurrent;                  // 36   U0-92   励磁电流显示
     u16 unpcFil;                       // 37   正负母线电压偏差
    u16 reactivePower;              // 38   无功功率
    u16 dropFrq;					//功率平衡调节
    u16 rsvd[9];                   // 39-48 保留
};
#define CORE_TO_FUNC_SLOW_DATA_A_LEN  (sizeof(struct CORE_TO_FUNC_SLOW_DATA_A_STRUCT)/(sizeof(u16)))
struct CORE_TO_FUNC_SLOW_DATA_B_STRUCT
{
    
    u16 coreInfo1[10];              // 00-09  Ux-10 - UA-19   无单位
    u16 coreInfo2[10];              // 10-19  Ux-20 - UA-29   0.1%
    u16 coreInfo3[10];              // 20-29  Ux-30 - UA-39   0.1%
    u16 coreInfo4[10];              // 30-39  Ux-40 - UA-49   0.1%
    u16 rsvd[9];					// 40-48  保留
    
};
#define CORE_TO_FUNC_SLOW_DATA_B_LEN  (sizeof(struct CORE_TO_FUNC_SLOW_DATA_B_STRUCT)/(sizeof(u16)))
union CORE_TO_FUNC_SLOW_DATA
{
    u16 all[CORE_TO_FUNC_SLOW_DATA_A_LEN];

    struct CORE_TO_FUNC_SLOW_DATA_A_STRUCT codeA;
    struct CORE_TO_FUNC_SLOW_DATA_B_STRUCT codeB;
};



struct CORE_TO_FUNC_DATA_STRUCT
{
    u16 dspStatus;              // 0    状态
    u16 motorCtrlTuneStatus;    // 1    参数辨识状态字
    
    u16 errorCodeFromCore;      // 2    性能故障代码
    u16 alarmCodeFromCore;      // 3    性能告警代码
    u16 coreErrorInfo;          // 4    故障提示信息
    u16 coreAlarmInfo[16];
    //u16 coreAlarmInfo[4];       // 5-8
    //u16 coreAlarmInfo4[12];     // 9-20 报警提示信息
    u16 dspSubStatus;           // 21

    u16 syncFrq;                // 22   同步频率
    u16 speedMotor;             // 23   输出频率
    u16 encoderFdb;             // 24   编码器反馈频率，PU值
    
    u16 outVoltage;             // 25   输出电压
    u16 generatrixVoltage;      // 26   母线电压
    u16 torqueCurrent;          // 27   转矩电流，基值是传递过来的“实际使用的电流基值”
    u16 itDisp;                 // 28   输出转矩
    u16 outCurrent;             // 29   输出电流
    u16 outPower;               // 30   输出功率
    u16 inputPower;             // 31   输入功率，Q12，PU值。1PU=输入额定电流*输入额定电压*sqrt(3)。
    u16 inputVoltage;           // 32   输入电压
    u16 inputFrq;               // 33   输入电压的频率
//    u16 autoTunePara[AUTO_TUNE_PARA_LEN];            // 32-61 调谐参数，目前为30个。顺序见AUTO_TUNE_PARA_LEN定义
// 单独出来了。

    u16 cellBlockStatus;        // 34   单元block状态
    u16 cellStatus;             // 35   单元状态1
    u16 cellStatusL;            // 36   单元状态2
    u16 cellVolVer;             // 37   单元版本号,电压
    u16 rsvd;                   // 38   保留
    u16 currentOc;              // 39   三相最大输出电流瞬时值，PU。1PU=变频器额定输出电流*sqrt(2) 
 
    u16 sampleFastT;            // 40   快环数据采样个数--黑匣子数据
    u16 uoutCurrent;            // 41   u输出电流
    u16 voutCurrent;            // 42   v输出电流
    u16 woutCurrent;            // 43   w输出电流
    
    u16 outPowerH;              // 44   输出功率 // LS_20221128
    u16 rsvd1[6];               // 43-50   保留
    
//===以上，每1拍传递1次
//---------------------------------------------------------------------
//===以下，每2拍传递1次

    union CORE_TO_FUNC_SLOW_DATA slowData;  // 44-83 共40个

//=============================================
    u16 sampleD[6][12];         // 100-171 快环交互数据
    
    u16 flag;                   // 172
    u16 crc;                    // 173
    u16 rsvdEnd;                // 174  任何时候都不用这个数据且放到最后

};
#define CORE_TO_FUNC_DATA_LEN  (sizeof(struct CORE_TO_FUNC_DATA_STRUCT)/(sizeof(u16)))
union CORE_TO_FUNC_DATA
{
    u16 all[CORE_TO_FUNC_DATA_LEN];

    struct CORE_TO_FUNC_DATA_STRUCT code;
};
//extern union CORE_TO_FUNC_DATA c2fData;
//==============================================================================







#endif  //__M_INTERFACE_MODIFY_H__





