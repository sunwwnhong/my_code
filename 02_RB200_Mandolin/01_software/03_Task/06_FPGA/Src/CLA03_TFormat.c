/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : CLA03_TFormat.c
* Version            : V0.1
* Date               : 2024
* Description        : 多摩川编码器接口
***********************************************************************************************/
  
  
#include "Main.h"
#include "CLA03_TFormat.h"
#include "PM_tformat_Include.h"
 
 
  
/**********************************************************************************************/
/* Function_Name: tformat_initSPIFIFO         */
/* Description  : 多摩川编码器协议接口SPI初始化
                  调用：初始化
                  输入：
                  输出：   */
/**********************************************************************************************/
void tformat_initSPIFIFO(uint32_t base,uint32_t devLSPCLKFreq)
{
    SPI_disableModule(base);
    SPI_disableLoopback(base);
    SPI_setConfig(base,
                  devLSPCLKFreq,
                  SPI_PROT_POL1PHA0,

                  SPI_MODE_PERIPHERAL,
                  500000,
                  PM_TFORMAT_FIFO_WORD_BITS);
    SPI_clearInterruptStatus(base, SPI_INT_RX_OVERRUN |
                             SPI_INT_RX_DATA_TX_EMPTY | SPI_INT_RXFF |
                             SPI_INT_RXFF_OVERFLOW | SPI_INT_TXFF);
    SPI_enableFIFO(base);
    SPI_setFIFOInterruptLevel(base, SPI_FIFO_TX3, SPI_FIFO_RX3);
    SPI_setEmulationMode(base, SPI_EMULATION_FREE_RUN);
    SPI_resetTxFIFO(base);
    SPI_resetRxFIFO(base);
}
 
  
/**********************************************************************************************/
/* Function_Name: tformat_spiRxBuff         */
/* Description  : 多摩川编码器SPI数据接收
                  调用：初始化
                  输入：
                  输出：   */
/**********************************************************************************************/
void tformat_spiRxBuff(void)
{
    uint16_t i;
 #pragma MUST_ITERATE(5, 12, 1)
#ifdef CPU1
    for (i = 0; i < tformatData.fifoLevel; i++)
    {
        tformatRxData[i] = (HWREGH(MOTA_TFORMAT_SPI + SPI_O_RXBUF)) & 0xFF;
    }
#if 0
    uint16_t FifoStatus;
    FifoStatus = ((SPI_RxFIFOLevel)((HWREGH(MOTA_TFORMAT_SPI + SPI_O_FFRX) & SPI_FFRX_RXFFST_M) >> SPI_FFRX_RXFFST_S));
    if( FifoStatus != 0 )
    {
        for( i= 0 ; i < FifoStatus; i++ )
        {
            SPIDummy = HWREGH(MOTA_TFORMAT_SPI + SPI_O_RXBUF);
        }
    }
#endif
#endif
}

/**********************************************************************************************/
/* Function_Name: tformat_checkError         */
/* Description  : 多摩川编码器ID指令发送检查
                  调用：初始化
                  输入：
                  输出：   */
/**********************************************************************************************/
uint16_t tformat_checkError(uint16_t controlFieldID)
{
    uint16_t errorFlag = PM_TFORMAT_PASS;
      
      
    if(commandData.controlField != tformatData.controlField)
    {
        errorFlag = 1;
        errorData.idCheckError = 1;
    }
    if(tformatData.crcCheck != tformatData.crcField)
    {
        errorFlag = 1;
        errorData.crcCheckError = 1;
    }
      
      
      
    if(controlFieldID == PM_TFORMAT_CFID6)
    {
        if(commandData.eepromAddress != tformatData.eepromAddressField)
        {
            errorFlag = 1;
            errorData.eepromAddressError = 1;
        }
        if(commandData.eepromData != tformatData.eepromWrDataField)
        {
            errorFlag = 1;
            errorData.eepromDataError = 1;
        }
    }
      
      
      
    if(controlFieldID == PM_TFORMAT_CFIDD)
    {
        if(commandData.eepromAddress != tformatData.eepromAddressField)
        {
            errorFlag = 1;
            errorData.eepromAddressError = 1;
        }
    }
    return(errorFlag);
}


/**********************************************************************************************/
/* Function_Name: TFormatID0_1_3_7_checkError         */
/* Description  : 多摩川编码器ID指令CRC校验排查
                  调用：初始化
                  输入：
                  输出：   */
/**********************************************************************************************/
uint16_t TFormatID0_1_3_7_checkError( void )
{
    uint16_t errorFlag = PM_TFORMAT_PASS;
      
      
 #if 0
    if(commandData.controlField != tformatData.controlField)
    {
        errorFlag = 1;
    }
#endif
    if(tformatData.crcCheck != tformatData.crcField)
    {
        errorFlag = 1;
    }
    return(errorFlag);
}
 
