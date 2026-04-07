/*
 * App07_IIC.h
 *
 *  Created on: 2022Äê7ÔÂ14ÈÕ
 *      Author: zhuxc
 */

#ifndef App07_IIC_H
#define App07_IIC_H


//
// Error messages for read and write functions
//
#define ERROR_BUS_BUSY              0x1000
#define ERROR_NACK_RECEIVED         0x2000
#define ERROR_ARBITRATION_LOST      0x3000
#define ERROR_STOP_NOT_READY        0x5555

#define MAX_BUFFER_SIZE             64
#define I2C_FIFO_LEVEL              16

#define MAX_7_BIT_ADDRESS           127U
#define MAX_10_BIT_ADDRESS          1023U


//GPIO 25
#define KPX_EepromWP_Disable        HWREG( GPIODATA_BASE + GPIO_O_GPASET )   = 1UL << 25;
#define KPX_EepromWP_Enable         HWREG( GPIODATA_BASE + GPIO_O_GPACLEAR ) = 1UL << 25;



/*-------------------------------------------------------------------------------------------------*/

extern void InitCpu1_IIC( void );
extern USHORT EepromReadValue(void);
/*-------------------------------------------------------------------------------------------------*/
extern USHORT RCMD_WriteDeviceAdd(USHORT WriteAddr);
extern USHORT WriteEepromOneByte(USHORT WriteData);
extern USHORT WriteEepromStop( void );
extern USHORT ReadDataFromEeprom(void);
extern void IIC_StopFlagClear(void);
extern USHORT WriteDeviceAdd(USHORT WriteAddr);
extern USHORT ReadEepromOneWord(USHORT ReadAddr);
extern USHORT WriteEepromOnePage(uint16_t WriteAddr,uint16_t *WriteData);
extern USHORT ReadEepromOnePage( uint16_t ReadAddr,uint16_t *ReadData );
extern USHORT WriteEepromOneWord(uint16_t WriteAddr,uint16_t WriteData);
#endif

