 
 
 
 
 
 
 
 
 
 
 
 

#ifndef PM_TFORMAT_INTERNAL_INCLUDE_H
#define PM_TFORMAT_INTERNAL_INCLUDE_H

 
 
 
 
 
 
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "driverlib.h"
#include "clb_config.h"
#include "board.h"


#if defined(_F2837X)
#define PM_TFORMAT_CLB_SPI_CLK_OUT     CLB_OUTPUT_02
#define PM_TFORMAT_CLB_OE_OUT          CLB_OUTPUT_03
#define PM_TFORMAT_CLB_TXEN_OUT        CLB_OUTPUT_04
#define PM_TFORMAT_START_OPERATION_IN  (1UL << 0UL)
#define PM_TFORMAT_OE_IN               (1UL << 7UL)
#else
#define PM_TFORMAT_START_OPERATION_IN  (1UL << 0UL)
#endif


 
 
 
 
 
 
 

 
 
 
 
 
 
 
 
 
void tformat_initCLBXBAR(void);

 
 
 

 
 
 
 
 
 
 

 
 
 
 
 
 
 
 
 
static inline void tformat_configureCLBLen(
                                    uint16_t transmitClocks,
                                    uint16_t receiveClocks)
                                    __attribute__((ramfunc));

 
 
 
 
 
 
 
 
 
 
 
 
 
static inline void tformat_configureSPILen(void) __attribute__((ramfunc));

 
 
 
 
 
 
 
 
 
 
 
 
 
static inline void tformat_resetCLB(uint16_t tformatRXFields)
                                    __attribute__((ramfunc));

 
 
 

 
 
 
 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
uint16_t tformat_getRxCRCbyCLB() __attribute__((ramfunc));

 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
uint16_t tformat_getTxCRCbyVCRC(uint16_t *msgBuffer);

 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
uint16_t tformat_getCRCID0_1_7_8_C(void) __attribute__((ramfunc));

 
 
 
uint16_t tformat_getCRCID2(void) __attribute__((ramfunc));

 
 
 
uint16_t tformat_getCRCID3(void) __attribute__((ramfunc));

 
 
 
uint16_t tformat_getCRCIDD(void) __attribute__((ramfunc));

 
 
 
uint16_t tformat_getCRCID6(void) __attribute__((ramfunc));

 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
uint16_t tformat_getCRC(uint16_t nBitsData,
                               uint16_t *msg,
                               uint16_t *crcTable,
                               uint16_t rxLen)
                               __attribute__((ramfunc));

 
 
 

 
 
 
 
 
#ifdef __cplusplus
}
#endif

#endif  
