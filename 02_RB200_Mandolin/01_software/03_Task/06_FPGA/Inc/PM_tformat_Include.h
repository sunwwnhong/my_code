 
 
 
 
 
 
 
 
 
 
 
 

#ifndef PM_TFORMAT_INCLUDE_H
#define PM_TFORMAT_INCLUDE_H

 
 
 
 
 
 
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "driverlib.h"
#include "PM_tformat_deprecated.h"

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

#if defined(_F2837X) || defined(F2837x_DEVICE)
    #define PM_TFORMAT_SPI              SPIB_BASE
    #define PM_TFORMAT_RX_CRC_BY_C28X
    #define PM_TFORMAT_TX_CRC_BY_C28X

#elif defined(_F28002X) || defined(F28002x_DEVICE)
    #define PM_TFORMAT_SPI              SPIB_BASE
    #define PM_TFORMAT_RX_CRC_BY_CLB
    #define PM_TFORMAT_TX_CRC_BY_VCRC
    #define PM_TFORMAT_USE_CLB_INPUTXBAR

#elif defined(_F28004X) || defined(F28004x_DEVICE)
    #define PM_TFORMAT_SPI              SPIB_BASE
    #define PM_TFORMAT_RX_CRC_BY_CLB
    #define PM_TFORMAT_TX_CRC_BY_C28X

#elif defined(_F28003X) || defined(F28003x_DEVICE)
    #define PM_TFORMAT_SPI              SPIB_BASE
    #define PM_TFORMAT_RX_CRC_BY_CLB
    #define PM_TFORMAT_TX_CRC_BY_VCRC
    #define PM_TFORMAT_USE_CLB_INPUTXBAR

#elif defined(_F2838X) || defined(F2838x_DEVICE)
    #define MOTA_TFORMAT_SPI              SPIA_BASE
    #define MOTB_TFORMAT_SPI              SPIB_BASE
    #define PM_TFORMAT_RX_CRC_BY_CLB
    #define PM_TFORMAT_TX_CRC_BY_VCRC
    #define PM_TFORMAT_USE_CLB_INPUTXBAR
#else
    #error Device should match a predefined symbol in the build options.
#endif

 
 
 


 
 
 
 
 
 
 
 
 
 
#define PM_TFORMAT_CODEID0  0x00u    
#define PM_TFORMAT_CODEID1  0x11u    
#define PM_TFORMAT_CODEID2  0x09u    
#define PM_TFORMAT_CODEID3  0x18u    
#define PM_TFORMAT_CODEID6  0x0Cu    
#define PM_TFORMAT_CODEIDD  0x17u    
#define PM_TFORMAT_CODEID7  0x1Du    
#define PM_TFORMAT_CODEID8  0x03u    
#define PM_TFORMAT_CODEIDC  0x06u    

 
 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#define PM_TFORMAT_CFID0 (PM_TFORMAT_CODEID0 | 0x40u)  
#define PM_TFORMAT_CFID1 (PM_TFORMAT_CODEID1 | 0x40u)  
#define PM_TFORMAT_CFID2 (PM_TFORMAT_CODEID2 | 0x40u)  
#define PM_TFORMAT_CFID3 (PM_TFORMAT_CODEID3 | 0x40u)  
#define PM_TFORMAT_CFID6 (PM_TFORMAT_CODEID6 | 0x40u)  
#define PM_TFORMAT_CFIDD (PM_TFORMAT_CODEIDD | 0x40u)  
#define PM_TFORMAT_CFID7 (PM_TFORMAT_CODEID7 | 0x40u)  
#define PM_TFORMAT_CFID8 (PM_TFORMAT_CODEID8 | 0x40u)  
#define PM_TFORMAT_CFIDC (PM_TFORMAT_CODEIDC | 0x40u)  

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

enum commandID6_D
    {
       PM_TFORMAT_ID6 = ((PM_TFORMAT_CODEID6 << 6u ) | 0x903Fu),
       PM_TFORMAT_IDD = ((PM_TFORMAT_CODEIDD << 6u ) | 0x903Fu)
    };


enum commandID0_1_2_3_7_8_C
    {
        PM_TFORMAT_ID0 = ((PM_TFORMAT_CODEID0 << 6u ) | 0x903Fu),
        PM_TFORMAT_ID1 = ((PM_TFORMAT_CODEID1 << 6u ) | 0x903Fu),
        PM_TFORMAT_ID2 = ((PM_TFORMAT_CODEID2 << 6u ) | 0x903Fu),
        PM_TFORMAT_ID3 = ((PM_TFORMAT_CODEID3 << 6u ) | 0x903Fu),
        PM_TFORMAT_ID7 = ((PM_TFORMAT_CODEID7 << 6u ) | 0x903Fu),
        PM_TFORMAT_ID8 = ((PM_TFORMAT_CODEID8 << 6u ) | 0x903Fu),
        PM_TFORMAT_IDC = ((PM_TFORMAT_CODEIDC << 6u ) | 0x903Fu)
    };

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#define PM_TFORMAT_TX_FIELDS_ID0    1u
#define PM_TFORMAT_TX_FIELDS_ID1    1u
#define PM_TFORMAT_TX_FIELDS_ID2    1u
#define PM_TFORMAT_TX_FIELDS_ID3    1u
#define PM_TFORMAT_TX_FIELDS_ID7    1u
#define PM_TFORMAT_TX_FIELDS_ID8    1u
#define PM_TFORMAT_TX_FIELDS_IDC    1u
#define PM_TFORMAT_TX_FIELDS_ID6    4u
#define PM_TFORMAT_TX_FIELDS_IDD    3u

#define PM_TFORMAT_RX_FIELDS_ID0    6u
#define PM_TFORMAT_RX_FIELDS_ID1    6u
#define PM_TFORMAT_RX_FIELDS_ID2    4u
#define PM_TFORMAT_RX_FIELDS_ID3    11u
#define PM_TFORMAT_RX_FIELDS_ID7    6u
#define PM_TFORMAT_RX_FIELDS_ID8    6u
#define PM_TFORMAT_RX_FIELDS_IDC    6u
#define PM_TFORMAT_RX_FIELDS_ID6    4u
#define PM_TFORMAT_RX_FIELDS_IDD    4u

#define PM_TFORMAT_RX_FIELDS_MAX    11u
#define PM_TFORMAT_TX_FIELDS_MAX     4u
#define PM_TFORMAT_FIELDS_MAX                                                  \
           (PM_TFORMAT_TX_FIELDS_ID3 + PM_TFORMAT_RX_FIELDS_ID3)

 
 
 

 
 
 
 
 
 
 
 
 
#define PM_TFORMAT_FIELD_BITS               10u
#define PM_TFORMAT_FIELD_DATA_BITS          8u
#define PM_TFORMAT_ONE_DATA_FIELD           PM_TFORMAT_FIELD_DATA_BITS
#define PM_TFORMAT_TWO_DATA_FIELDS          (PM_TFORMAT_FIELD_DATA_BITS * 2ul)
#define PM_TFORMAT_THREE_DATA_FIELDS        (PM_TFORMAT_FIELD_DATA_BITS * 3ul)
#define PM_TFORMAT_FIELD_BITS               10u
#define PM_TFORMAT_IDLE_BIT                 1u
#define PM_TFORMAT_ALIGN_LEFT(a)            (a << 8)
#define PM_TFORMAT_ADD_DELIMITER_START(a) ( (a >> 2u) | (1u << 15u) )
#define PM_TFORMAT_FIFO_WORD_BITS           PM_TFORMAT_FIELD_BITS


 
 
 
 
 
 
 
 
 
 
#define PM_TFORMAT_TX_CLOCKS_ID0 (PM_TFORMAT_IDLE_BIT                          \
                + (PM_TFORMAT_TX_FIELDS_ID0 * PM_TFORMAT_FIELD_BITS))
#define PM_TFORMAT_TX_CLOCKS_ID1 (PM_TFORMAT_IDLE_BIT                          \
                + (PM_TFORMAT_TX_FIELDS_ID1 * PM_TFORMAT_FIELD_BITS))
#define PM_TFORMAT_TX_CLOCKS_ID2 (PM_TFORMAT_IDLE_BIT                          \
                + (PM_TFORMAT_TX_FIELDS_ID2 * PM_TFORMAT_FIELD_BITS))
#define PM_TFORMAT_TX_CLOCKS_ID3 (PM_TFORMAT_IDLE_BIT                          \
                +  (PM_TFORMAT_TX_FIELDS_ID3 * PM_TFORMAT_FIELD_BITS))
#define PM_TFORMAT_TX_CLOCKS_ID6 (PM_TFORMAT_IDLE_BIT                          \
                + (PM_TFORMAT_TX_FIELDS_ID6 * PM_TFORMAT_FIELD_BITS))
#define PM_TFORMAT_TX_CLOCKS_ID7 (PM_TFORMAT_IDLE_BIT                          \
                + (PM_TFORMAT_TX_FIELDS_ID7 * PM_TFORMAT_FIELD_BITS))
#define PM_TFORMAT_TX_CLOCKS_ID8 (PM_TFORMAT_IDLE_BIT                          \
                + (PM_TFORMAT_TX_FIELDS_ID8 * PM_TFORMAT_FIELD_BITS))
#define PM_TFORMAT_TX_CLOCKS_IDC (PM_TFORMAT_IDLE_BIT                          \
                + (PM_TFORMAT_TX_FIELDS_IDC * PM_TFORMAT_FIELD_BITS))
#define PM_TFORMAT_TX_CLOCKS_IDD (PM_TFORMAT_IDLE_BIT                          \
                + (PM_TFORMAT_TX_FIELDS_IDD * PM_TFORMAT_FIELD_BITS))

 
 
 
 
 
 
 
 
 
 
 

#define PM_TFORMAT_RX_CLOCKS_ID0                                               \
                    (PM_TFORMAT_RX_FIELDS_ID0 * PM_TFORMAT_FIELD_BITS)
#define PM_TFORMAT_RX_CLOCKS_ID1                                               \
                    (PM_TFORMAT_RX_FIELDS_ID1 * PM_TFORMAT_FIELD_BITS)
#define PM_TFORMAT_RX_CLOCKS_ID2                                               \
                    (PM_TFORMAT_RX_FIELDS_ID2 * PM_TFORMAT_FIELD_BITS)
#define PM_TFORMAT_RX_CLOCKS_ID3                                               \
                    (PM_TFORMAT_RX_FIELDS_ID3 * PM_TFORMAT_FIELD_BITS)
#define PM_TFORMAT_RX_CLOCKS_ID6                                               \
                    (PM_TFORMAT_RX_FIELDS_ID6 * PM_TFORMAT_FIELD_BITS)
#define PM_TFORMAT_RX_CLOCKS_ID7                                               \
                    (PM_TFORMAT_RX_FIELDS_ID7 * PM_TFORMAT_FIELD_BITS)
#define PM_TFORMAT_RX_CLOCKS_ID8                                               \
                    (PM_TFORMAT_RX_FIELDS_ID8 * PM_TFORMAT_FIELD_BITS)
#define PM_TFORMAT_RX_CLOCKS_IDC                                               \
                    (PM_TFORMAT_RX_FIELDS_IDC * PM_TFORMAT_FIELD_BITS)
#define PM_TFORMAT_RX_CLOCKS_IDD                                               \
                    (PM_TFORMAT_RX_FIELDS_IDD * PM_TFORMAT_FIELD_BITS)
#define PM_TFORMAT_RX_CLOCKS_MAX                                               \
                    (PM_TFORMAT_RX_FIELDS_MAX * PM_TFORMAT_FIELD_BITS)

#define PM_TFORMAT_RX_CLOCKS_IDX                                               \
                    (PM_TFORMAT_RX_FIELDS_ID3 * PM_TFORMAT_FIELD_BITS)

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#define PM_TFORMAT_FIFO_LEVEL_ID0                                              \
                    (PM_TFORMAT_RX_FIELDS_ID0 + PM_TFORMAT_TX_FIELDS_ID0)
#define PM_TFORMAT_FIFO_LEVEL_ID1                                              \
                    (PM_TFORMAT_RX_FIELDS_ID1 + PM_TFORMAT_TX_FIELDS_ID1)
#define PM_TFORMAT_FIFO_LEVEL_ID2                                              \
                    (PM_TFORMAT_RX_FIELDS_ID2 + PM_TFORMAT_TX_FIELDS_ID2)
#define PM_TFORMAT_FIFO_LEVEL_ID3                                              \
                    (PM_TFORMAT_RX_FIELDS_ID3 + PM_TFORMAT_TX_FIELDS_ID3)
#define PM_TFORMAT_FIFO_LEVEL_ID6                                              \
                    (PM_TFORMAT_RX_FIELDS_ID6 + PM_TFORMAT_TX_FIELDS_ID6)
#define PM_TFORMAT_FIFO_LEVEL_ID7                                              \
                    (PM_TFORMAT_RX_FIELDS_ID7 + PM_TFORMAT_TX_FIELDS_ID7)
#define PM_TFORMAT_FIFO_LEVEL_ID8                                              \
                    (PM_TFORMAT_RX_FIELDS_ID8 + PM_TFORMAT_TX_FIELDS_ID8)
#define PM_TFORMAT_FIFO_LEVEL_IDC                                              \
                    (PM_TFORMAT_RX_FIELDS_IDC + PM_TFORMAT_TX_FIELDS_IDC)
#define PM_TFORMAT_FIFO_LEVEL_IDD                                              \
                    (PM_TFORMAT_RX_FIELDS_IDD + PM_TFORMAT_TX_FIELDS_IDD)
#define PM_TFORMAT_FIFO_LEVEL_MAX                                              \
                    (PM_TFORMAT_RX_FIELDS_MAX + PM_TFORMAT_TX_FIELDS_MAX)
 
 
 
 
 
 
 
 
 
 
#define PM_TFORMAT_CRC_START        0
#define PM_TFORMAT_NBITS_POLY       8u
#define PM_TFORMAT_POLY             0x01u
#define PM_TFORMAT_CRCTABLE_SIZE    256u
#define PM_TFORMAT_CRC_MASK         0xFFu


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
#define PM_TFORMAT_RX_CRC_BYTES_ID0   (PM_TFORMAT_RX_FIELDS_ID0 - 1u)
#define PM_TFORMAT_RX_CRC_BYTES_ID1   (PM_TFORMAT_RX_FIELDS_ID1 - 1u)
#define PM_TFORMAT_RX_CRC_BYTES_ID2   (PM_TFORMAT_RX_FIELDS_ID2 - 1u)
#define PM_TFORMAT_RX_CRC_BYTES_ID3   (PM_TFORMAT_RX_FIELDS_ID3 - 1u)
#define PM_TFORMAT_RX_CRC_BYTES_ID6   (PM_TFORMAT_RX_FIELDS_ID6 - 1u)
#define PM_TFORMAT_RX_CRC_BYTES_IDD   (PM_TFORMAT_RX_FIELDS_IDD - 1u)
#define PM_TFORMAT_RX_CRC_BYTES_ID7   (PM_TFORMAT_RX_FIELDS_ID7 - 1u)
#define PM_TFORMAT_RX_CRC_BYTES_ID8   (PM_TFORMAT_RX_FIELDS_ID8 - 1u)
#define PM_TFORMAT_RX_CRC_BYTES_IDC   (PM_TFORMAT_RX_FIELDS_IDC - 1u)

#define PM_TFORMAT_RX_CRC_BITS_ID0    (PM_TFORMAT_RX_CRC_BYTES_ID0 *           \
                                            PM_TFORMAT_FIELD_DATA_BITS)
#define PM_TFORMAT_RX_CRC_BITS_ID1    (PM_TFORMAT_RX_CRC_BYTES_ID1 *           \
                                             PM_TFORMAT_FIELD_DATA_BITS)
#define PM_TFORMAT_RX_CRC_BITS_ID2    (PM_TFORMAT_RX_CRC_BYTES_ID2 *           \
                                             PM_TFORMAT_FIELD_DATA_BITS)
#define PM_TFORMAT_RX_CRC_BITS_ID3    (PM_TFORMAT_RX_CRC_BYTES_ID3 *           \
                                            PM_TFORMAT_FIELD_DATA_BITS)
#define PM_TFORMAT_RX_CRC_BITS_ID6    (PM_TFORMAT_RX_CRC_BYTES_ID6 *           \
                                            PM_TFORMAT_FIELD_DATA_BITS)
#define PM_TFORMAT_RX_CRC_BITS_IDD    (PM_TFORMAT_RX_CRC_BYTES_IDD *           \
                                            PM_TFORMAT_FIELD_DATA_BITS)
#define PM_TFORMAT_RX_CRC_BITS_ID7    (PM_TFORMAT_RX_CRC_BYTES_ID7 *           \
                                            PM_TFORMAT_FIELD_DATA_BITS)
#define PM_TFORMAT_RX_CRC_BITS_ID8    (PM_TFORMAT_RX_CRC_BYTES_ID8 *           \
                                            PM_TFORMAT_FIELD_DATA_BITS)
#define PM_TFORMAT_RX_CRC_BITS_IDC    (PM_TFORMAT_RX_CRC_BYTES_IDC *           \
                                            PM_TFORMAT_FIELD_DATA_BITS)

 
 
 
 
 
 
 
#define PM_TFORMAT_TX_CRC_BYTES_ID6  (PM_TFORMAT_TX_FIELDS_ID6 - 1u)
#define PM_TFORMAT_TX_CRC_BYTES_IDD  (PM_TFORMAT_TX_FIELDS_IDD - 1u)

#define PM_TFORMAT_TX_CRC_BITS_ID6   (PM_TFORMAT_TX_CRC_BYTES_ID6 *            \
                                            PM_TFORMAT_FIELD_DATA_BITS)
#define PM_TFORMAT_TX_CRC_BITS_IDD   (PM_TFORMAT_TX_CRC_BYTES_IDD *            \
                                            PM_TFORMAT_FIELD_DATA_BITS)

 
 
 
 
 
#define PM_TFORMAT_PASS               0
#define PM_TFORMAT_CRC_CLB_ERROR      0xFFFF
#define PM_TFORMAT_CRC_CHECK_ERROR    0xFFFEP
#define PM_TFORMAT_EEPROM_BUSY        0xFFFD
#define PM_TFORMAT_ID_CHECK_ERROR     0xFFFC

 
 
 
 
 
 

typedef struct PM_tformat_DataStruct {
    uint16_t  controlField;
    uint16_t  statusField;
    uint16_t  dataField0;
    uint16_t  dataField1;
    uint16_t  dataField2;
    uint16_t  dataField3;
    uint16_t  dataField4;
    uint16_t  dataField5;
    uint16_t  dataField6;
    uint16_t  dataField7;
    uint16_t  crcField;
    uint16_t  crcCheck;
    uint16_t  eepromAddressField;
    uint16_t  eepromWrDataField;
    uint16_t  eepromRdDataField;
    volatile bool  dataReady;
    uint16_t  fifoLevel;
} PM_tformat_DataStruct;

 
 
 

 
 
 
 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
extern PM_tformat_DataStruct tformatData;


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
extern volatile uint16_t tformatRxData[PM_TFORMAT_FIELDS_MAX];

 
 
 
 
 
 
#if defined(PM_TFORMAT_CRC_TABLE)
extern uint16_t tformatCRCtable[PM_TFORMAT_CRCTABLE_SIZE];
#endif

 
 
 
 
 
 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
void PM_tformat_generateCRCTable(uint16_t nBits,
                                 uint16_t polynomial,
                                 uint16_t *pTable);

 
 
 
 
 
 
 
 
 
void PM_tformat_setupPeriph();

 
 
 
 
 
 
 
 
 
 
void PM_tformat_setFreq(uint32_t freqDiv);

 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
void PM_tformat_setupCommandReadoutOrReset(enum commandID0_1_2_3_7_8_C,
                             uint16_t tformatRXClocks,
                             uint16_t tformatRXFields,
                             uint16_t tformatTXClocks,
                             uint16_t tformatFIFOLevel)
                             __attribute__((ramfunc));

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
void PM_tformat_setupCommandReadEEPROM(uint16_t eepromAddr)
                                       __attribute__((ramfunc));

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
void PM_tformat_setupCommandWriteEEPROM(uint16_t eepromAddr,
                                        uint16_t eepromData)
                                        __attribute__((ramfunc));

 
 
 
 
 
 
 
 
 
 
 
 
 
void PM_tformat_startOperation(void);

 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
void PM_tformat_receiveDataID0_1_7_8_C(void) __attribute__((ramfunc));

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
void PM_tformat_receiveDataID2(void) __attribute__((ramfunc));

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
void PM_tformat_receiveDataID3(void) __attribute__((ramfunc));

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
uint16_t PM_tformat_receiveDataIDD(void) __attribute__((ramfunc));

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
uint16_t PM_tformat_receiveDataID6(void)  __attribute__((ramfunc));

 
 
 

 
 
 
#define PM_tformat_receiveDataID0 PM_tformat_receiveDataID0_1_7_8_C
#define PM_tformat_receiveDataID1 PM_tformat_receiveDataID0_1_7_8_C
#define PM_tformat_receiveDataID7 PM_tformat_receiveDataID0_1_7_8_C
#define PM_tformat_receiveDataID8 PM_tformat_receiveDataID0_1_7_8_C
#define PM_tformat_receiveDataIDC PM_tformat_receiveDataID0_1_7_8_C

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
uint32_t PM_tformat_updatePositionOrTurns(uint16_t field0,
                                          uint16_t field1,
                                          uint16_t field2 )
                                         __attribute__((ramfunc));

 
 
 
 
 
 
 
 
 
 
 
 
 
uint16_t PM_tformat_updateEncoderID(uint16_t enidField)
                                   __attribute__((ramfunc));

 
 
 

 
 
 
 
 
#ifdef __cplusplus
}
#endif

#endif  
