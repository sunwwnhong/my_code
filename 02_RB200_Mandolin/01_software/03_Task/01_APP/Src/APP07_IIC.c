//*************************************************************************************************
//文件名:App07_IIC.c
//创建时间:2022.07.11
//版本说明:V1.0
//功能描述:IIC 初始化配置
//*************************************************************************************************

#include "Main.h"

#ifdef CPU1
#define myI2C_Base    I2CA_BASE
#endif

struct I2CHandle EEPROM;
struct I2CHandle *currentMsgPtr;                   // Used in interrupt

uint16_t TX_MsgBuffer[MAX_BUFFER_SIZE];
uint16_t RX_MsgBuffer[MAX_BUFFER_SIZE];
uint32_t IIC_RW_Addr = 0;                           // IIC 读写地址
//
// Typedefs
//
struct I2CHandle
{
    uint32_t base;
    uint16_t SlaveAddr;                  // Slave address tied to the message.
    uint32_t *pControlAddr;
    uint16_t NumOfAddrBytes;
    uint16_t *pTX_MsgBuffer;             // Pointer to TX message buffer
    uint16_t *pRX_MsgBuffer;             // Pointer to RX message buffer
    uint16_t NumOfDataBytes;             // Number of valid bytes in message.
    struct I2CHandle *currentHandlePtr;
    uint16_t numofSixteenByte;
    uint16_t remainingBytes;
    uint16_t NumOfAttempts;             //  Number of attempts to make before reporting
                                        //  slave not ready (NACK condition)
    uint16_t Delay_us;                  //  Delay time in microsecs (us)
};


uint16_t I2C_MasterTransmitter(struct I2CHandle *I2C_Params);


/****************************************************************************************************/
/*                                                                                                  */
/*  IIC GPIO 引脚初始化                                                                                */
/*                                                                                                  */
/****************************************************************************************************/
void I2C_GPIO_init(void)
{
#ifdef CPU1
    //
    // I2C-SDA
    //
    GPIO_setDirectionMode(104, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(104, GPIO_PIN_TYPE_PULLUP);
    GPIO_setMasterCore(104, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(104, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_104_I2CA_SDA);

    //
    // I2C-SCL
    //
    GPIO_setDirectionMode(105, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(105, GPIO_PIN_TYPE_PULLUP);
    GPIO_setMasterCore(105, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(105, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_105_I2CA_SCL);

    //
    // WP
    //
    GPIO_setPinConfig(GPIO_25_GPIO25);
    GPIO_setDirectionMode(25, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(25, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(25, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(25, GPIO_QUAL_SYNC);
#endif


}

/****************************************************************************************************/
/*                                                                                                  */
/*  检查总线忙碌状态                                                                                    */
/*                                                                                                  */
/****************************************************************************************************/
uint16_t checkBusStatus(uint32_t base)
{

    if(I2C_isBusBusy(base))
    {
        return ERROR_BUS_BUSY;
    }

    if(I2C_getStopConditionStatus(base))
    {
        return ERROR_STOP_NOT_READY;
    }

    return 0;
}
#if 0
/****************************************************************************************************/
/*                                                                                                  */
/*  IIC 总线扫描                                                                                      */
/*                                                                                                  */
/****************************************************************************************************/
uint16_t I2CBusScan(uint32_t base, uint16_t *pAvailableI2C_slaves)
{
    uint16_t probeSlaveAddress, i;
    uint16_t status;
    //Disable interrupts on Stop condition, NACK and arbitration lost condition
    I2C_disableInterrupt(base, (I2C_INT_ADDR_SLAVE|I2C_INT_STOP_CONDITION | I2C_INT_ARB_LOST | I2C_INT_NO_ACK));

    i = 0;
    for(probeSlaveAddress = 1; probeSlaveAddress <= 50; probeSlaveAddress++)
    {
        //Check I2C bus status
        status = checkBusStatus(base);
        if(status)
        {
           return status;
        }

        I2C_setConfig(base, (I2C_MASTER_SEND_MODE | I2C_REPEAT_MODE));

        //Enable 10-bit addressing if probeSlaveAddress is greater than 127U
        if(probeSlaveAddress > MAX_7_BIT_ADDRESS)
        {
            //10-bit addressing
            I2C_setAddressMode(base, I2C_ADDR_MODE_10BITS);
        }

        // Setup slave address
        I2C_setSlaveAddress(base, probeSlaveAddress);


        I2C_sendStartCondition(base);

        //Wait for the slave address to be transmitted
        while(!(I2C_getStatus(base) & I2C_STS_REG_ACCESS_RDY));

        //Generate STOP condition
        I2C_sendStopCondition(base);

        //Wait for the I2CMDR.STP to be cleared
        while(I2C_getStopConditionStatus(base));

        //Wait for the Bus busy bit to be cleared
        while(I2C_isBusBusy(base));

        uint16_t I2CStatus = I2C_getStatus(base);

        //If Slave address is acknowledged, store slave address
        //in pAvailableI2C_slaves
        if(!(I2CStatus & I2C_STS_NO_ACK))
        {
            pAvailableI2C_slaves[i++] = probeSlaveAddress;
        }
        //Clear NACK bit in I2CSTR
        I2C_clearStatus(base,I2C_STS_NO_ACK|I2C_STS_ARB_LOST|I2C_STS_REG_ACCESS_RDY|I2C_STS_STOP_CONDITION);
    }

    I2C_setConfig(base, (I2C_MASTER_SEND_MODE));
    I2C_setAddressMode(base, I2C_ADDR_MODE_7BITS); //7-bit addressing
    I2C_enableInterrupt(base, (I2C_INT_ADDR_SLAVE|I2C_INT_STOP_CONDITION | I2C_INT_ARB_LOST | I2C_INT_NO_ACK));
    return SUCCESS;
}
#endif


/****************************************************************************************************/
/*                                                                                                  */
/*  IIC初始化                                                                                         */
/*                                                                                                  */
/****************************************************************************************************/
void InitCpu1_IIC( void )
{
#if 0
uint16_t AvailableI2C_slaves[20];
uint16_t status;
#endif
    /*----------------------------------------------------------------------------------------------*/
    /*  1 IIC 引脚初始化                                                                               */
    /*----------------------------------------------------------------------------------------------*/
#ifdef CPU1
    I2C_GPIO_init();    //轴1和轴2配置在CPU1执行
#endif
    /*----------------------------------------------------------------------------------------------*/
    /*  2 IIC 寄存器初始化                                                                             */
    /*----------------------------------------------------------------------------------------------*/
    I2C_disableModule(myI2C_Base);
    I2C_initMaster(myI2C_Base, DEVICE_SYSCLK_FREQ, 100000, I2C_DUTYCYCLE_50);
    I2C_setConfig(myI2C_Base, I2C_MASTER_SEND_MODE);
    I2C_setSlaveAddress(myI2C_Base, 80);
    I2C_setOwnSlaveAddress(myI2C_Base, 96); //I2CA address
    I2C_disableLoopback(myI2C_Base);
    I2C_setBitCount(myI2C_Base, I2C_BITCOUNT_8);
    I2C_setDataCount(myI2C_Base, 2);
    I2C_setAddressMode(myI2C_Base, I2C_ADDR_MODE_7BITS);
    I2C_enableFIFO(myI2C_Base);
    I2C_clearInterruptStatus(myI2C_Base, I2C_INT_ARB_LOST | I2C_INT_NO_ACK);
    I2C_setFIFOInterruptLevel(myI2C_Base, I2C_FIFO_TXEMPTY, I2C_FIFO_RX2);
    I2C_enableInterrupt(myI2C_Base, I2C_INT_ADDR_TARGET | I2C_INT_ARB_LOST | I2C_INT_NO_ACK | I2C_INT_STOP_CONDITION);
    I2C_setEmulationMode(myI2C_Base, I2C_EMULATION_FREE_RUN);
    I2C_enableModule(myI2C_Base);
#if 0
    uint16_t *pAvailableI2C_slaves = AvailableI2C_slaves;
    status = I2CBusScan(I2C_Base, pAvailableI2C_slaves);
#endif
    //
    // IIC 配置寄存器初始化
    //

    uint16_t i;

    for(i=0;i<MAX_BUFFER_SIZE;i++)
    {
        TX_MsgBuffer[i] = 0;
        RX_MsgBuffer[i] = 0;
    }

    EEPROM.SlaveAddr      = 0x50;
    EEPROM.base           = myI2C_Base;
    EEPROM.pControlAddr   = &IIC_RW_Addr;
    EEPROM.NumOfAddrBytes = 2;
    EEPROM.pTX_MsgBuffer  = TX_MsgBuffer;
    EEPROM.pRX_MsgBuffer  = RX_MsgBuffer;
    EEPROM.NumOfAttempts  = 15;
    EEPROM.Delay_us       = 30;
}




/****************************************************************************************************/
/*                                                                                                  */
/*  ACK 信号状态检测                                                                                   */
/*                                                                                                  */
/****************************************************************************************************/
uint16_t handleNACK(uint32_t base)
{
    if(I2C_getStatus(base) & I2C_STS_NO_ACK)
    {
        I2C_clearStatus(base, I2C_STS_NO_ACK);
        I2C_sendStopCondition(base);

        return ERROR_NACK_RECEIVED;
    }

    return 0;
}

/****************************************************************************************************/
/*                                                                                                  */
/*  发送从站地址                                                                                       */
/*                                                                                                  */
/****************************************************************************************************/
uint16_t I2C_TransmitSlaveAddress_ControlBytes(struct I2CHandle *I2C_Params)
{
    uint16_t status, attemptCount=1;

    uint32_t base = I2C_Params->base;

    status = 1;

    while(status & (attemptCount <= I2C_Params->NumOfAttempts))
    {
        status = checkBusStatus(base);
        attemptCount++;
        DEVICE_DELAY_US(I2C_Params->Delay_us);
    }

    if(status)
    {
        return status;
    }

    I2C_setConfig(base, (I2C_MASTER_SEND_MODE|I2C_REPEAT_MODE));

    if((I2C_Params->SlaveAddr) > MAX_7_BIT_ADDRESS)
    {
        //10-bit addressing
        I2C_setAddressMode(base, I2C_ADDR_MODE_10BITS);
    }

    // Setup slave address
    I2C_setSlaveAddress(base, I2C_Params->SlaveAddr);


    int16_t  i;
    uint32_t temp = *(I2C_Params->pControlAddr);

    for(i=I2C_Params->NumOfAddrBytes-1;i>=0;i--)
    {
        I2C_putData(base, (temp >> (i*8U)) & 0xFF);
    }

    I2C_sendStartCondition(base);

    DEVICE_DELAY_US(150U);

    status = handleNACK(base);
    if(status)
    {
      if(attemptCount <= (I2C_Params->NumOfAttempts))
      {
          attemptCount++;
          I2C_setConfig(base, (I2C_MASTER_SEND_MODE));
          I2C_sendStartCondition(base);
          DEVICE_DELAY_US(I2C_Params->Delay_us);
      }
      else
      {
          return status;
      }
    }

    attemptCount = 1;

    while(I2C_getTxFIFOStatus(base) && attemptCount <= 9 * (I2C_Params->NumOfAddrBytes + 2U))
    {
       status = handleNACK(base);
       if(status)
       {
          return status;
       }
       attemptCount++;
       DEVICE_DELAY_US(I2C_Params->Delay_us);
    }

    return 0;
}


/****************************************************************************************************/
/*                                                                                                  */
/*  发送数据处理                                                                                       */
/*                                                                                                  */
/****************************************************************************************************/
uint16_t I2C_MasterTransmitter(struct I2CHandle *I2C_Params)
{
    uint16_t status, attemptCount;

    uint32_t base = I2C_Params->base;

    I2C_disableFIFO(base);
    I2C_enableFIFO(base);

    status = I2C_TransmitSlaveAddress_ControlBytes(I2C_Params);

    if(status)
    {
        return status;
    }

    I2C_setDataCount(base, (I2C_Params->NumOfAddrBytes + I2C_Params->NumOfDataBytes));

    I2C_setFIFOInterruptLevel(base, I2C_FIFO_TXEMPTY, I2C_FIFO_RXFULL);

    I2C_enableInterrupt(base, I2C_INT_TXFF);

    uint16_t numofSixteenByte  = (I2C_Params->NumOfDataBytes) / I2C_FIFO_LEVEL;
    uint16_t remainingBytes    = (I2C_Params->NumOfDataBytes) % I2C_FIFO_LEVEL;

    uint16_t i,count = 0,buff_pos=0;

    while(count < numofSixteenByte)
    {
        for(i=1;i<=I2C_FIFO_LEVEL;i++)
        {
            I2C_putData(base, I2C_Params->pTX_MsgBuffer[buff_pos++]);
        }

        attemptCount = 1;
        while(I2C_getTxFIFOStatus(base) && attemptCount <= 9 * (I2C_FIFO_LEVEL + 2U))
        {
            status = handleNACK(base);
            if(status)
            {
              return status;
            }
            attemptCount++;
            DEVICE_DELAY_US(I2C_Params->Delay_us);
        }

        count++;
    }

    for (i=0; i < remainingBytes; i++)
    {
        I2C_putData(base, I2C_Params->pTX_MsgBuffer[buff_pos++]);
    }

    DEVICE_DELAY_US(I2C_Params->Delay_us);

    attemptCount = 1;
    while(I2C_getTxFIFOStatus(base) && attemptCount <= 9 * (remainingBytes + 2U))
    {
        status = handleNACK(base);
        if(status)
        {
          return status;
        }
        attemptCount++;
        DEVICE_DELAY_US(I2C_Params->Delay_us);
    }

    I2C_sendStopCondition(base);

    attemptCount = 1;
    while(I2C_getStopConditionStatus(base) && attemptCount <= 3U)
    {
        DEVICE_DELAY_US(I2C_Params->Delay_us);
        attemptCount++;
    }

    return 0;
}

/****************************************************************************************************/
/*                                                                                                  */
/*  接收数据处理                                                                                       */
/*                                                                                                  */
/****************************************************************************************************/
uint16_t I2C_MasterReceiver(struct I2CHandle *I2C_Params)
{
    uint16_t status;
    uint16_t attemptCount;

    uint32_t base = I2C_Params->base;

    I2C_disableFIFO(base);
    I2C_enableFIFO(base);

    status = I2C_TransmitSlaveAddress_ControlBytes(I2C_Params);

    if(status)
    {
        return status;
    }

    uint16_t numofSixteenByte  = (I2C_Params->NumOfDataBytes) / I2C_FIFO_LEVEL;
    uint16_t remainingBytes    = (I2C_Params->NumOfDataBytes) % I2C_FIFO_LEVEL;

    I2C_setConfig(base, (I2C_MASTER_RECEIVE_MODE|I2C_REPEAT_MODE));

    I2C_sendStartCondition(base);

    uint16_t i,count = 0,buff_pos=0;
    while(count < numofSixteenByte)
    {
        status = handleNACK(base);
        if(status)
        {
          return status;
        }

        count++;

        attemptCount = 1;
        while(!(I2C_getRxFIFOStatus(base) == I2C_FIFO_RXFULL) && attemptCount <= 9 * (I2C_FIFO_RXFULL + 2U))
        {
            DEVICE_DELAY_US(I2C_Params->Delay_us);
            attemptCount++;
        }

        for(i=0; i<I2C_FIFO_LEVEL; i++)
        {
            I2C_Params->pRX_MsgBuffer[buff_pos++] = I2C_getData(base);
        }
    }

    DEVICE_DELAY_US(I2C_Params->Delay_us);

    attemptCount = 1;
    while(!(I2C_getRxFIFOStatus(base) == remainingBytes) && attemptCount <= 9 * (remainingBytes + 2U))
    {
       DEVICE_DELAY_US(I2C_Params->Delay_us);
       attemptCount++;
    }

    I2C_sendStopCondition(base);

    attemptCount = 1;
    while(I2C_getStopConditionStatus(base) && attemptCount <= 3U)
    {
        DEVICE_DELAY_US(I2C_Params->Delay_us);
        attemptCount++;
    }

    status = handleNACK(base);
    if( status )
    {
        return status;
    }

    for(i=0; i<remainingBytes; i++)
    {
        I2C_Params->pRX_MsgBuffer[buff_pos++] = I2C_getData(base);
    }

/*    status = handleNACK(base);
    if( status )
    {
      return status;
    }
*/
    I2C_disableFIFO(base);
/*
    attemptCount = 1;
    while(I2C_getStopConditionStatus(base) && attemptCount <= 3U)
    {
        DEVICE_DELAY_US(I2C_Params->Delay_us);
        attemptCount++;
    }
*/
    return 0;

}

/****************************************************************************************************/
/*                                                                                                  */
/* IIC Word(16-bit)write                                                                            */
/*                                                                                                  */
/****************************************************************************************************/
USHORT WriteEepromOneWord(uint16_t WriteAddr,uint16_t WriteData)
{
    USHORT status = 0;
    USHORT WriteTimes = 0;

    do
    {
    IIC_RW_Addr             = WriteAddr;                             /* 写入地址                      */
    EEPROM.pControlAddr     = &IIC_RW_Addr;

    TX_MsgBuffer[0]         = WriteData & 0x00FF;                    /* 写入数据(L)                   */
    TX_MsgBuffer[1]         = (WriteData >> 8) & 0x00FF;             /* 写入数据(H)                   */

    EEPROM.pTX_MsgBuffer    = TX_MsgBuffer;
    EEPROM.NumOfDataBytes   = 2;
    status = I2C_MasterTransmitter(&EEPROM);

    WriteTimes ++;
    if( WriteTimes > 3 )
    {
        break;
    }

    }while( status != 0 );
    return 0;
}



/****************************************************************************************************/
/*                                                                                                  */
/* IIC One Page write                                                                               */
/*                                                                                                  */
/****************************************************************************************************/
USHORT WriteEepromOnePage(uint16_t WriteAddr,uint16_t *WriteData)
{
    uint8_t status;

    IIC_RW_Addr             = WriteAddr;                             /* 写入地址                      */
    EEPROM.pControlAddr     = &IIC_RW_Addr;

    EEPROM.pTX_MsgBuffer    = WriteData;                             /* 写入数据                      */
    EEPROM.NumOfDataBytes   = 32;
    status = I2C_MasterTransmitter(&EEPROM);

    if( 0 == status )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


/****************************************************************************************************/
/*                                                                                                  */
/* IIC One Page Read                                                                                */
/*                                                                                                  */
/****************************************************************************************************/
USHORT ReadEepromOnePage( uint16_t ReadAddr,uint16_t *ReadData )
{
    uint8_t status;

    IIC_RW_Addr             = ReadAddr;                              /* 写入地址                      */
    EEPROM.pControlAddr     = &IIC_RW_Addr;

    EEPROM.pRX_MsgBuffer    = ReadData;                              /* 写入数据                      */
    EEPROM.NumOfDataBytes   = 32;
    status = I2C_MasterReceiver(&EEPROM);

    if( 0 == status )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}



/****************************************************************************************************/
/*                                                                                                  */
/* IIC Word(16-bit)Read                                                                             */
/*                                                                                                  */
/****************************************************************************************************/
uint16_t RecivedData = 0;
USHORT ReadEepromOneWord(USHORT ReadAddr)
{
uint8_t status;
    IIC_RW_Addr   = ReadAddr;
    EEPROM.pControlAddr   = &IIC_RW_Addr;
    EEPROM.pRX_MsgBuffer  = RX_MsgBuffer;
    EEPROM.NumOfDataBytes = 2;

    status = I2C_MasterReceiver(&EEPROM);
    if( 0 == status )
    {
        RecivedData = RX_MsgBuffer[0] + (RX_MsgBuffer[1] << 8);
        return 0;
    }
    else
    {
        return 1;
    }
}

/****************************************************************************************************/
/*                                                                                                  */
/*                                      输出一个值进行转存                                               */
/*                                                                                                  */
/****************************************************************************************************/
USHORT EepromReadValue(void)
{
    return RecivedData;
}

/****************************************************************************************************/
/*                                                                                                  */
/*                                      解决IIC总线锁死问题                                          */
/*                                                                                                  */
/****************************************************************************************************/
void IIC_BusyReset(void)
{
    USHORT i;
    //--------------------------------CPU1_EEPROM_SCL引脚GPIO32---------------------------------------
    GPIO_setPinConfig(GPIO_105_GPIO105);                           //  SCL引脚#
    GPIO_setDirectionMode(105, GPIO_DIR_MODE_OUT);                //  Input
    GPIO_setPadConfig(105, GPIO_PIN_TYPE_STD);                    //  上拉
    GPIO_setMasterCore(105, GPIO_CORE_CPU1);                      //  CPU1使用
    GPIO_setQualificationMode(105, GPIO_QUAL_SYNC);            //  滤波时间

    //---------------------------连续输出超过9个时钟信号复位EEPROM2-------------------------------------
    for(i=0;i<16;i++)
    {
        HWREG( GPIODATA_BASE + GPIO_O_GPDSET )    = 1UL << 9;
        DEVICE_DELAY_US(5);
        HWREG( GPIODATA_BASE + GPIO_O_GPDCLEAR )  = 1UL << 9;
        DEVICE_DELAY_US(5);
    }
    HWREGH(I2CA_BASE + I2C_O_MDR) &= 0xF7FF;                        //清除CPU1_IIC_MDR_STP寄存器
}
