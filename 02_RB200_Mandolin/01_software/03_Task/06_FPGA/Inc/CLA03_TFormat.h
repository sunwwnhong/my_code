/*
 * CLA03_TFormat.h
 *
 *  Created on: 2022Äê11ÔÂ17ÈÕ
 *      Author: zhuxc
 */
 #ifndef CLA03_TFormat_H
#define CLA03_TFormat_H
  
  
  
 #ifdef __cplusplus
extern "C"
{
#endif
 #include "PM_tformat_include.h"
#include "driverlib.h"
#include "device.h"
  
  
  
  
  
 #define TFORMAT_RUN_ID0     1
#define TFORMAT_RUN_ID1     1
#define TFORMAT_RUN_ID2     1
#define TFORMAT_RUN_ID3     1
#define TFORMAT_RUN_IDD_ID6 1   
#define TFORMAT_RUN_ID7     1
#define TFORMAT_RUN_ID8     1
#define TFORMAT_RUN_IDC     1
  
  
  
  
  
  
  
#define TFORMAT_CLB_CLOCK       60ul  
 
#define TFORMAT_BUS_CLOCK       2.5f  
#define TFORMAT_FREQ_DIVIDER    (TFORMAT_CLB_CLOCK /                           \
                                    (uint16_t) (2.0f * TFORMAT_BUS_CLOCK) )
#define TFORMAT_BIT_WIDTH       (TFORMAT_CLB_CLOCK /                           \
                                    (uint16_t) (TFORMAT_BUS_CLOCK) )
  
  
  
  
 #define TFORMAT_EEPROM_TEST_ADDR_START  0x73u
#define TFORMAT_EEPROM_TEST_ADDR_END    0x7Eu
  
  
  
 #define TFORMAT_IDLE_DELAY_US_START       10ul
#define TFORMAT_IDLE_DELAY_US_INCREMENT   15ul
  
  
  
#define TFORMAT_EEPROM_BUSY_US 18000ul
  
  
  
 #define TFORMAT_POWER_ON_DELAY_US 1500000ul
  
  
  
  
  
typedef struct PM_tformat_encoderStruct {
    uint32_t  position;
    int16_t   turns;
    uint16_t  Almc;
} PM_tformat_encoderStruct;
 extern PM_tformat_encoderStruct encoderData;
  
  
typedef struct PM_tformat_errorStruct {
    uint16_t  idCheckError;
    uint16_t  crcCheckError;
    uint16_t  eepromAddressError;
    uint16_t  eepromDataError;
} PM_tformat_errorStruct;
  
  
 typedef struct PM_tformat_commandStruct {
    uint32_t  controlField;
    uint32_t  eepromAddress;
    uint16_t  eepromData;
} PM_tformat_commandStruct;
  
  
  
  
  
  
  
  
  
  
  
 extern PM_tformat_encoderStruct encoderData;
  
  
  
  
  
  
  
extern PM_tformat_errorStruct errorData;
  
  
  
  
 extern PM_tformat_commandStruct commandData;
  
  
  
  
 
  
 
  
  
  
 
  
  
  
  
  
  
  
 uint16_t tformat_checkError(uint16_t controlFieldID) __attribute__((ramfunc));
uint16_t TFormatID0_1_3_7_checkError(void) __attribute__((ramfunc));
  
  
  
  
  
  
  
  
  
void tformat_spiRxBuff(void);
 
  
 
  
  
  
  
  
  
void tformat_init(void);
  
  
  
  
  
  
void tformat_initSPIFIFO(uint32_t base,uint32_t devLSPCLKFreq);
 
#if defined(_F2837X)
  
  
  
  
  
  
  
  
void tformat_configEPWM4(void);
#endif
  
  
  
  
  
#ifdef __cplusplus
}
#endif
 extern volatile USHORT SPIFFifoLevel;
 #endif
