
#ifndef __F_AUXFLAG_H__
#define __F_AUXFLAG_H__

//======================================================================
//#include "stm32f10x_gpio.h"

// ----------------函数声明---------------------------------------------- 
extern void func0MsDeal(void);
extern void func05MsDeal(void);
extern void func2msDealA(void);
extern void func2msDealB(void);
extern void func2msDealC(void);
extern void func2msDealD(void);
extern void OtherPeripheralConfigration(void);
//extern void HighSwitchCloseEnableConfirm(void);
// ----------------函数声明结束------------------------------------------
extern Uint16 sysStatus;
/*
//-------------LED----------//
#define RUN_LED_OFF  GPIO_SetBits(GPIOF, GPIO_Pin_11)	//sci led 置灭	A0
#define RUN_LED_ON  GPIO_ResetBits(GPIOF, GPIO_Pin_11)	//sci led 置灭	A0

#define ERROR_LED_OFF  GPIO_SetBits(GPIOE, GPIO_Pin_6)	//error led 置灭	
#define ERROR_LED_ON  GPIO_ResetBits(GPIOE, GPIO_Pin_6)	//error led 置亮	

#define SYSTEM_ERROR_LED_OFF  GPIO_SetBits(GPIOC, GPIO_Pin_7)	//error led 置灭	
#define SYSTEM_ERROR_LED_ON  GPIO_ResetBits(GPIOC, GPIO_Pin_7)	//error led 置亮

//------------FPGA OK---------//
#define FPGA_READY_OK_TEM   (((GPIOC->IDR & 0x0100) == 0x0000) ? (TRUE) : (FALSE))
// DSP写RAM完成
#define RAM_DSP_OK          (!(GPIOG->IDR & 0x0020))  // PG5
// ARM写RAM的标志
#define RAM_ARM_ON      GPIO_SetBits(GPIOG, GPIO_Pin_4)     //BUSY
#define RAM_ARM_OFF     GPIO_ResetBits(GPIOG, GPIO_Pin_4)   //FREE


//----------------SD--------------------//
#if 0
#define SPI_CS_DISABLE	{GPIO_SetBits(GPIOB,GPIO_Pin_12);}
#define SPI_CS_ENABLE	{GPIO_ResetBits(GPIOB,GPIO_Pin_12);}
#define SPI_DO_HIGH		{GPIO_SetBits(GPIOB,GPIO_Pin_15);}
#endif
*/
#define RAM_DATA_ADDR_CON   0x00000000UL // 0x20000000UL // LS_20221205

struct FPGA_STATUS_BITS
{   
	Uint16 watchdog:1;		// 0 DSP写sin值超时状态 0-正常; 1-超时故障
	Uint16 sampleErr1:1;     // 1 输出电压采样板通讯异常
	Uint16 sampleErr2:1;     // 1 输出电压采样板通讯异常
	Uint16 sampleErr3:1;     // 1 输出电压采样板通讯异常
	Uint16 rsvd:12;			// 2-15 保留
};

union FPGA_STATUS
{
	Uint16 all;
	struct FPGA_STATUS_BITS bit;
};
extern union FPGA_STATUS statusFromFpga;

#define HMI_INIT_TIME           30000       // 30s

#define ARM_READ_WRITE_DI_DATA_LENGTH   2   // DIDO数据长度
#define ARM_READ_WRITE_DO_DATA_LENGTH   2   // DIDO数据长度
#define ARM_READ_WRITE_DATA_LENGTH_3X  8
extern Uint16 doWriteData[ARM_READ_WRITE_DO_DATA_LENGTH];
extern Uint16 diReadData[ARM_READ_WRITE_DI_DATA_LENGTH];
//extern Uint16 inv3xRcvData[ARM_READ_WRITE_DATA_LENGTH_3X];
extern Uint16 inv3xSendData[ARM_READ_WRITE_DATA_LENGTH_3X];
extern Uint16 fpgaProductionVersion;
extern Uint16 cellBypassNum;
extern Uint16 validCellNum;        // 当前系统单元总数
extern Uint16 cellBypassAttribute;  // 单元旁路属性
extern int16 kernelTemp;

#define WIND_MOTOR_NOMAL    0   // 风机正常
#define WIND_MOTOR_ALARM    1   // 有F9-76个风机故障，其他风机正常
#define WIND_MOTOR_INVALID  2   // 风机未开或者有F9-76个以上风机故障
extern Uint16 windMotorStaus;
extern Uint16 windErrorFuncInfo;

extern Uint16 interPhaseCellNoMin; // 相间最小单元数
extern u16 protoFlag;
extern Uint16 invCurrLimit;
extern Uint32 volLineMax;
extern Uint16 carrierFrq;
extern Uint16 tempDiffer;              // 温度差

#endif


