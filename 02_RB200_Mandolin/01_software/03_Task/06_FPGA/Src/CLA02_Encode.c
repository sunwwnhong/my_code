/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : CLA02_Encode.c
* Version            : V0.1
* Date               : 2024
* Description        : 多摩川编码器接口
***********************************************************************************************/

#include "Main.h"
#include "CLA03_TFormat.h"
#include "PM_tformat_Include.h"
#include "MotA_TEncCLB.h"
#include "MotB_TEncCLB.h"
 #ifdef CPU1
#define MOTA_TFORMAT_CLB_BASE                               CLB1_BASE
#define MOTA_TFORMAT_RX_CRC_BASE                            CLB3_BASE
#define MOTA_TFORMAT_CLB_INPUTXBAR_SIMO_SOURCE              16
#define MOTA_TFORMAT_CLB_INPUTXBAR_SIMO_INPUT               XBAR_INPUT7
#define MOTA_TFORMAT_CLB_OUTPUTXBAR_TXEN                    XBAR_OUTPUT2
#define MOTA_TFORMAT_CLB_OUTPUTXBAR_TXEN_ENABLED_MUXES      (XBAR_MUX13)
#define MOTA_TFORMAT_CLB_OUTPUTXBAR_OutSET                  XBAR_OUT_MUX05_CLB1_OUT5
#define MOTA_TFORMAT_CLB_OUTPUTXBAR_OutMux                  (XBAR_MUX05)
#endif

  
  
  
#pragma RETAIN (encoderData);
#pragma RETAIN (errorData);
#pragma RETAIN (commandData);

PM_tformat_DataStruct tformatData;
volatile uint16_t tformatRxData[PM_TFORMAT_FIELDS_MAX];
PM_tformat_encoderStruct    encoderData = {0UL,0,0};
PM_tformat_errorStruct      errorData={0,0,0,0};
PM_tformat_commandStruct    commandData;
 
  
  
/**********************************************************************************************/
/* Function_Name: tformat_setupGPIO         */
/* Description  : 多摩川编码器协议接口GPIO初始化
                  调用：初始化
                  输入：
                  输出：   */
/**********************************************************************************************/
void tformat_setupGPIO( void )
{
#ifdef CPU1
      
	GPIO_setPinConfig(GPIO_41_CLB_OUTPUTXBAR2);
      
    GPIO_setPinConfig(GPIO_16_SPIA_PICO);
    GPIO_setPadConfig(16, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(16, GPIO_QUAL_ASYNC);
      
    GPIO_setPinConfig(GPIO_17_SPIA_POCI);
    GPIO_setPadConfig(17, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(17, GPIO_QUAL_ASYNC);
      
    GPIO_setPinConfig(GPIO_57_SPIA_PTE);
    GPIO_setPadConfig(57, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(57, GPIO_QUAL_ASYNC);
#endif

}
  
  
/**********************************************************************************************/
/* Function_Name: TFORMAT_CLB_INPUTXBAR_SIMO_init         */
/* Description  : 多摩川编码器协议接口CLB模块SIMO初始化
                  调用：初始化
                  输入：
                  输出：   */
/**********************************************************************************************/
void TFORMAT_CLB_INPUTXBAR_SIMO_init( void )
{
#ifdef CPU1
    XBAR_setInputPin(CLBINPUTXBAR_BASE, MOTA_TFORMAT_CLB_INPUTXBAR_SIMO_INPUT, MOTA_TFORMAT_CLB_INPUTXBAR_SIMO_SOURCE);
    XBAR_lockInput(CLBINPUTXBAR_BASE, MOTA_TFORMAT_CLB_INPUTXBAR_SIMO_INPUT);
#endif
}
 
  
/**********************************************************************************************/
/* Function_Name: TFORMAT_CLB_OUTPUTXBAR_TXEN_init         */
/* Description  : 多摩川编码器协议接口CLB模块TXEN初始化
                  调用：初始化
                  输入：
                  输出：   */
/**********************************************************************************************/
void TFORMAT_CLB_OUTPUTXBAR_TXEN_init( void )
{
#ifdef CPU1
    XBAR_setOutputLatchMode(CLBOUTPUTXBAR_BASE, MOTA_TFORMAT_CLB_OUTPUTXBAR_TXEN, false);
    XBAR_invertOutputSignal(CLBOUTPUTXBAR_BASE, MOTA_TFORMAT_CLB_OUTPUTXBAR_TXEN, false);
    XBAR_setOutputMuxConfig(CLBOUTPUTXBAR_BASE, MOTA_TFORMAT_CLB_OUTPUTXBAR_TXEN, MOTA_TFORMAT_CLB_OUTPUTXBAR_OutSET);
    XBAR_enableOutputMux(CLBOUTPUTXBAR_BASE, MOTA_TFORMAT_CLB_OUTPUTXBAR_TXEN, MOTA_TFORMAT_CLB_OUTPUTXBAR_OutMux);
#endif
}
 
 

/**********************************************************************************************/
/* Function_Name: TFormatSPI_init         */
/* Description  : 多摩川编码器协议SPI初始化
                  调用：初始化
                  输入：
                  输出：   */
/**********************************************************************************************/
void TFormatSPI_init( uint32_t base )
{
    SPI_disableModule(base);
    SPI_setConfig(base, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0,
                  SPI_MODE_PERIPHERAL, 25000, 16);
    SPI_enableFIFO(base);
    SPI_setFIFOInterruptLevel(base, SPI_FIFO_TXEMPTY, SPI_FIFO_RXEMPTY);
    SPI_disableLoopback(base);
    SPI_setEmulationMode(base, SPI_EMULATION_STOP_MIDWAY);
    SPI_enableModule(base);
}
 
  
/**********************************************************************************************/
/* Function_Name: MOTA_tformat_setupPeriph         */
/* Description  : 轴1多摩川编码器协议CLB模块初始化
                  调用：初始化
                  输入：
                  输出：   */
/**********************************************************************************************/
void MOTA_tformat_setupPeriph( void )
{
    MOTA_TileTformat(MOTA_TFORMAT_CLB_BASE);
    MOTA_TileTformatRxCRC(MOTA_TFORMAT_RX_CRC_BASE);
    MOTA_TFORMAT_CLB_init1();
    MOTA_TFORMAT_RX_CRC_init1();
}



/**********************************************************************************************/
/* Function_Name: MOT_tformat_setFreq         */
/* Description  : 多摩川波特率配置
                  调用：初始化
                  输入：
                  输出：   */
/**********************************************************************************************/
void MOT_tformat_setFreq(uint32_t base,uint32_t freqDiv)
{
    EALLOW;
    CLB_writeInterface(base,CLB_ADDR_COUNTER_0_MATCH1,(freqDiv - 1));
    CLB_writeInterface(base,CLB_ADDR_COUNTER_0_MATCH2,((2 * freqDiv) - 1));
    EDIS;
    return;
}
  
  
/**********************************************************************************************/
/* Function_Name: InitCpu1_SPI         */
/* Description  : 轴1和轴2的多摩川编码器SPI初始化
                  调用：初始化
                  输入：
                  输出：   */
/**********************************************************************************************/
void InitCpu1_SPI( void )
{
#ifdef CPU1

    MOTA_tformat_setupPeriph( );
    TFormatSPI_init(MOTA_TFORMAT_SPI);
    tformat_setupGPIO();
    TFORMAT_CLB_INPUTXBAR_SIMO_init();
    TFORMAT_CLB_OUTPUTXBAR_TXEN_init();
#endif
 #ifdef CPU1
    MOT_tformat_setFreq(MOTA_TFORMAT_CLB_BASE,TFORMAT_FREQ_DIVIDER);
    tformat_initSPIFIFO(MOTA_TFORMAT_SPI,DEVICE_LSPCLK_FREQ);
    SPI_enableModule(MOTA_TFORMAT_SPI);
#endif
      
    errorData = (struct PM_tformat_errorStruct) {0};
    encoderData = (struct PM_tformat_encoderStruct) {0};
 }
  
 
/**********************************************************************************************/
/* Function_Name: TFormatEncDataRead_ID0         */
/* Description  : 多摩川编码器ID0指令接收与发送
                  调用：SCANA周期
                  输入：
                  输出：   */
/**********************************************************************************************/
void TFormatEncDataRead_ID0( void )
{
    tformat_spiRxBuff();
    PM_tformat_receiveDataID0();                         
    if(TFormatID0_1_3_7_checkError( ) == PM_TFORMAT_PASS)        
    {
        encoderData.position = PM_tformat_updatePositionOrTurns(tformatData.dataField0,
                                                                tformatData.dataField1,
                                                                tformatData.dataField2);
        encoderData.turns   = 0;
        encoderData.Almc    = 0;
    }
    else
    {
        encoderData.Almc = 0x0100;
    }

    tformatData = (struct PM_tformat_DataStruct) {0};
    commandData.controlField = PM_TFORMAT_CFID0;
    PM_tformat_setupCommandReadoutOrReset(PM_TFORMAT_ID0,
                            PM_TFORMAT_RX_CLOCKS_ID0,
                            PM_TFORMAT_RX_FIELDS_ID0,
                            PM_TFORMAT_TX_CLOCKS_ID0,
                            PM_TFORMAT_FIFO_LEVEL_ID0);
    PM_tformat_startOperation();
}
 
  
/**********************************************************************************************/
/* Function_Name: TFormatEncDataRead_ID3         */
/* Description  : 多摩川编码器ID3指令接收与发送
                  调用：SCANA周期
                  输入：
                  输出：   */
/**********************************************************************************************/
void TFormatEncDataRead_ID3( void )
{
    tformat_spiRxBuff();
    PM_tformat_receiveDataID3();                         
    if(TFormatID0_1_3_7_checkError( ) == PM_TFORMAT_PASS)        
    {
        encoderData.position = PM_tformat_updatePositionOrTurns(tformatData.dataField0,
                                                                tformatData.dataField1,
                                                                tformatData.dataField2);
        encoderData.turns =    PM_tformat_updatePositionOrTurns(tformatData.dataField4,
                                                                tformatData.dataField5,
                                                                tformatData.dataField6);
        encoderData.Almc  =    PM_tformat_updateEncoderID(tformatData.dataField7);
    }
    else
    {
        encoderData.Almc = 0x0100;
    }
    tformatData = (struct PM_tformat_DataStruct) {0};
    commandData.controlField = PM_TFORMAT_CFID3;
    PM_tformat_setupCommandReadoutOrReset(PM_TFORMAT_ID3,
                            PM_TFORMAT_RX_CLOCKS_ID3,
                            PM_TFORMAT_RX_FIELDS_ID3,
                            PM_TFORMAT_TX_CLOCKS_ID3,
                            PM_TFORMAT_FIFO_LEVEL_ID3);
    PM_tformat_startOperation();
}
 
  
/**********************************************************************************************/
/* Function_Name: TFormat_ID3_Cmd         */
/* Description  : 多摩川编码器ID3指令发送
                  调用：SCANA周期
                  输入：
                  输出：   */
/**********************************************************************************************/
void TFormat_ID3_Cmd( void )
{
    tformatData = (struct PM_tformat_DataStruct) {0};
    commandData.controlField = PM_TFORMAT_CFID3;
    DEVICE_DELAY_US(115UL);
    PM_tformat_setupCommandReadoutOrReset(PM_TFORMAT_ID3,
                            PM_TFORMAT_RX_CLOCKS_ID3,
                            PM_TFORMAT_RX_FIELDS_ID3,
                            PM_TFORMAT_TX_CLOCKS_ID3,
                            PM_TFORMAT_FIFO_LEVEL_ID3);
    PM_tformat_startOperation();
}
  
  
/**********************************************************************************************/
/* Function_Name: TFormat_ID0_Cmd         */
/* Description  : 多摩川编码器ID0指令发送
                  调用：SCANA周期
                  输入：
                  输出：   */
/**********************************************************************************************/
void TFormat_ID0_Cmd( void )
{
    tformatData = (struct PM_tformat_DataStruct) {0};
    commandData.controlField = PM_TFORMAT_CFID0;
    DEVICE_DELAY_US(115UL);
    PM_tformat_setupCommandReadoutOrReset(PM_TFORMAT_ID0,
                            PM_TFORMAT_RX_CLOCKS_ID0,
                            PM_TFORMAT_RX_FIELDS_ID0,
                            PM_TFORMAT_TX_CLOCKS_ID0,
                            PM_TFORMAT_FIFO_LEVEL_ID0);
    PM_tformat_startOperation();
}
 
 
/**********************************************************************************************/
/* Function_Name: TFormat_OnlineCheck         */
/* Description  : 多摩川编码器ID2访问查找是否为多摩川编码器
                  调用：SCANA周期
                  输入：
                  输出：   */
/**********************************************************************************************/
uint16_t TFormat_OnlineCheck( void )
{
    uint16_t ReadTimes = 0;
    while( ReadTimes <= 30)
    {
        tformatData = (struct PM_tformat_DataStruct) {0};
        commandData.controlField = PM_TFORMAT_CFID2;
        DEVICE_DELAY_US( 2 );
        PM_tformat_setupCommandReadoutOrReset(PM_TFORMAT_ID2,
                                              PM_TFORMAT_RX_CLOCKS_ID2,
                                              PM_TFORMAT_RX_FIELDS_ID2,
                                              PM_TFORMAT_TX_CLOCKS_ID2,
                                              PM_TFORMAT_FIFO_LEVEL_ID2);
        DEVICE_DELAY_US( 2 );
        PM_tformat_startOperation();
        DEVICE_DELAY_US( 60 );
        tformat_spiRxBuff();
        PM_tformat_receiveDataID2();
        if(tformat_checkError(PM_TFORMAT_CFID2) == PM_TFORMAT_PASS)
        {
             return 1;
        }
        ReadTimes ++;
    }
    return 0;
}
  
  
/**********************************************************************************************/
/* Function_Name: TFormat_OnlineCheck         */
/* Description  : 多摩川编码器ID2访问查找是否为多摩川编码器
                  调用：初始化
                  输入：
                  输出：   */
/**********************************************************************************************/
uint16_t TFormat_WriteByte( uint16_t eepromAddress, uint16_t eepromData)
{
    uint16_t returnStatus;
    uint16_t writeTimes = 0;
    uint16_t Status = 0;
    while( writeTimes <= 31)
    {
          
        tformatData = (struct PM_tformat_DataStruct) {0};
        commandData.eepromAddress = eepromAddress;
        commandData.eepromData    = eepromData;
        commandData.controlField  = PM_TFORMAT_CFID6;
        PM_tformat_setupCommandWriteEEPROM(eepromAddress, eepromData);
        DEVICE_DELAY_US(10);
        PM_tformat_startOperation();
         DEVICE_DELAY_US( 8000 );      
         tformat_spiRxBuff();
        returnStatus = PM_tformat_receiveDataID6();
         if(returnStatus != PM_TFORMAT_EEPROM_BUSY)
        {
            if(tformat_checkError(PM_TFORMAT_CFID6) == PM_TFORMAT_PASS)
            {
                Status = 1;      
                return Status;
            }
        }
        else
        {
            writeTimes ++;
        }
    }
    return Status;
}

/**********************************************************************************************/
/* Function_Name: TFormat_WriteByteCmd         */
/* Description  : 多摩川编码器ID6 EEPROM写入命令发送
                  调用：电机参数写入时调用
                  输入：eepromAddress：规划EEPROM地址
                      eepromData:EEPROM数据
                  输出：   */
/**********************************************************************************************/
void TFormat_WriteByteCmd( uint16_t eepromAddress, uint16_t eepromData)
{
    tformatData = (struct PM_tformat_DataStruct) {0};
    commandData.eepromAddress = eepromAddress;
    commandData.eepromData    = eepromData;
    commandData.controlField  = PM_TFORMAT_CFID6;
    PM_tformat_setupCommandWriteEEPROM(eepromAddress, eepromData);
    DEVICE_DELAY_US(1);
    PM_tformat_startOperation();
}

/**********************************************************************************************/
/* Function_Name: TFormat_WriteByteCheck         */
/* Description  : 多摩川编码器ID6发送状态检查
                  调用：电机参数写入时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
uint16_t TFormat_WriteByteCheck( void )
{
    uint16_t returnStatus;
    tformat_spiRxBuff();
    returnStatus = PM_tformat_receiveDataID6();
    if(returnStatus != PM_TFORMAT_EEPROM_BUSY)
    {
        if(tformat_checkError(PM_TFORMAT_CFID6) == PM_TFORMAT_PASS)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
 
  
/**********************************************************************************************/
/* Function_Name: TFormat_ReadByte         */
/* Description  : 多摩川编码器IDD EEPROM读取
                  调用：初始化上电读取电机参数时调用
                  输入：eepromAddress：EEPROM地址
                  输出：   */
/**********************************************************************************************/
uint16_t TFormat_ReadByte( uint16_t eepromAddress )
{
    uint16_t returnStatus;
    uint16_t ReadTimes = 0;
    while( ReadTimes <= 31)
    {
        tformatData = (struct PM_tformat_DataStruct) {0};
        commandData.eepromAddress = eepromAddress;
        commandData.eepromData = 0;
        commandData.controlField = PM_TFORMAT_CFIDD;
        PM_tformat_setupCommandReadEEPROM(eepromAddress);
        DEVICE_DELAY_US(2);
        PM_tformat_startOperation();
        DEVICE_DELAY_US(5000);
        tformat_spiRxBuff();
        returnStatus = PM_tformat_receiveDataIDD();
        if(returnStatus != PM_TFORMAT_EEPROM_BUSY)
        {
            if(tformat_checkError(PM_TFORMAT_CFIDD) == PM_TFORMAT_PASS)
            {
                return 1;
            }
        }
        ReadTimes++;
    }
    return 0;
}
 
  
/**********************************************************************************************/
/* Function_Name: EncErrorClr_Cmd         */
/* Description  : 多摩川编码器IDC 指令
                  调用：多摩川编码器故障复位调用
                  输入：
                  输出：   */
/**********************************************************************************************/
void EncErrorClr_Cmd( void )
{
    tformatData = (struct PM_tformat_DataStruct) {0};
    commandData.controlField = PM_TFORMAT_CFIDC;
    DEVICE_DELAY_US(1);
    PM_tformat_setupCommandReadoutOrReset(PM_TFORMAT_IDC,
                            PM_TFORMAT_RX_CLOCKS_IDC,
                            PM_TFORMAT_RX_FIELDS_IDC,
                            PM_TFORMAT_TX_CLOCKS_IDC,
                            PM_TFORMAT_FIFO_LEVEL_IDC);
    PM_tformat_startOperation();
 
}
 
/**********************************************************************************************/
/* Function_Name: EncErrClr_Check         */
/* Description  : 多摩川编码器IDC 指令状态检查
                  调用：多摩川编码器故障复位调用
                  输入：
                  输出：   */
/**********************************************************************************************/
uint16_t EncErrClr_Check( void )
{
    tformat_spiRxBuff();
    PM_tformat_receiveDataID0_1_7_8_C();
    if(tformat_checkError(PM_TFORMAT_CFIDC) == PM_TFORMAT_PASS)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
 
/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/
