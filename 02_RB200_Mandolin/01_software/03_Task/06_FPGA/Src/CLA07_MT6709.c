  
  
  
#include "Main.h"

#define WR_CMD    0x00
#define RD_CMD    0x80
#define RANG_BIT  0x01
#define CAL_FREQ  Prm.Pn531
#define AUTO_CAL_MODE  0x03
#define MT6709_CORRECT_ON Prm.Pn530

void MT6709_InitCpu1_SPIB( void );
uint16_t SPI_3Line_Write2Bytes(uint16_t data,uint16_t Addr);
uint32_t SPI_3Line_Read2Bytes(uint16_t Addr);

const USHORT DUMMY_BYTE[6] = {0};
MT6709_VAR MT6709_V;

uint8_t MT6709_TXdummy_num;
USHORT MT6709_crcErrCnt = 0;
USHORT MT6709_CorrectStep = 0;
USHORT MT6709_waittime = 0;
USHORT MT6709_CAL_STATE = 0;
uint16_t MT6709_receive_data;
uint16_t MT6709_Txdata;
uint8_t SpiBRxBuf8[10];

void MT6709_init(void)
{
    MT6709_InitCpu1_SPIB();
    MT6709_Config_Init();
}

void MT6709_InitCpu1_SPIB( void )
{
    EALLOW;

    //---------------------------------------------------------------------------------------------
    // 引脚定义
    //---------------------------------------------------------------------------------------------
    //
    // SPIB -> CLK
    //
#if 1

    GPIO_setAnalogMode(199, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_199_SPIB_CLK);
    GPIO_setPadConfig(199, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(199, GPIO_QUAL_ASYNC);
#endif
    //
    // SPIB -> SIMO
    //
    GPIO_setAnalogMode(201, GPIO_ANALOG_DISABLED);
    GPIO_setDirectionMode(201, GPIO_DIR_MODE_OUT);                // Output
    GPIO_setPinConfig(GPIO_201_SPIB_PICO);
    GPIO_setPadConfig(201, GPIO_PIN_TYPE_STD );
    GPIO_setQualificationMode(201, GPIO_QUAL_ASYNC);
    //
    // SPIB -> SOMI
    //
//    GPIO_setAnalogMode(202, GPIO_ANALOG_DISABLED);
//    GPIO_setPinConfig(GPIO_202_SPIB_POCI);
//    GPIO_setPadConfig(202, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
//    GPIO_setQualificationMode(202, GPIO_QUAL_ASYNC);
    //
    // SPIB -> STEN
    //
//    GPIO_setAnalogMode(200, GPIO_ANALOG_DISABLED);
//    GPIO_setPinConfig(GPIO_200_SPIB_PTE);
//    GPIO_setPadConfig(200, GPIO_PIN_TYPE_STD);
//    GPIO_setQualificationMode(200, GPIO_QUAL_ASYNC);
    GPIO_setAnalogMode(200, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_200_GPIO200);
    GPIO_setDirectionMode(200, GPIO_DIR_MODE_OUT);               // Output
    GPIO_setPadConfig(200, GPIO_PIN_TYPE_STD);                   // Open Drain
    GPIO_setMasterCore(200, GPIO_CORE_CPU1);                     // CPU1 使用
    GPIO_writePin( 200,1 );    // 引脚On


    //
    // 矫正
    //
    //---------------------------------------------------------------------------------------------
    // MT6709相关接口(FAULT、STATUS、PWM、CAL_EN)
    //---------------------------------------------------------------------------------------------
    /*
    GPIO_setAnalogMode(212, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_212_GPIO212);                           //  引脚#
    GPIO_setDirectionMode(212, GPIO_DIR_MODE_IN);                 //  Output
    GPIO_setPadConfig(212, GPIO_PIN_TYPE_STD);                    //  上拉
    GPIO_setMasterCore(212, GPIO_CORE_CPU1);                      //  CPU1使用
    GPIO_setQualificationMode(212, GPIO_QUAL_6SAMPLE);            //  滤波时间

    GPIO_setAnalogMode(211, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_211_GPIO211);                           //  引脚#
    GPIO_setDirectionMode(211, GPIO_DIR_MODE_IN);                 //  Output
    GPIO_setPadConfig(211, GPIO_PIN_TYPE_STD);                    //  上拉
    GPIO_setMasterCore(211, GPIO_CORE_CPU1);                      //  CPU1使用
    GPIO_setQualificationMode(211, GPIO_QUAL_6SAMPLE);            //  滤波时间
     */


    SPI_disableModule(SPIB_BASE);
    SPI_setConfig(SPIB_BASE, \
                  DEVICE_LSPCLK_FREQ, \
                  SPI_PROT_POL0PHA0,\
                  SPI_MODE_CONTROLLER, \
                  2000000, \
                  8);
    SPI_enableTriWire(SPIB_BASE);       // 开启三线SPI
    SPI_enableFIFO(SPIB_BASE);          // 开启FIFO

    SPI_disableLoopback(SPIB_BASE);
    SPI_setEmulationMode(SPIB_BASE, SPI_EMULATION_STOP_MIDWAY);
    SPI_enableModule(SPIB_BASE);

    EDIS;
}


void MT6709_Config_Init(void)
{
    uint16_t res = 0;
    uint16_t Txdata = 0;
    uint16_t SpiBTxBuf[10];
    uint16_t SpiBRxBuf[10];
    uint32_t SafeWord;

    //自校准转速设置
    res = SPI_3Line_Read2Bytes(0x18);
    Txdata = (res & 0xFFF0) + CAL_FREQ;
    SafeWord = SPI_3Line_Write2Bytes(Txdata,0x18);
    //AinK.Monitor4 = SPI_3Line_Read2Bytes(0x18);

    //自校准模式设置
    res = SPI_3Line_Read2Bytes(0x19);
    Txdata = (res & 0x0FFF) + (AUTO_CAL_MODE << 12);
    SafeWord = SPI_3Line_Write2Bytes(Txdata,0x19);

    //自校准必定通过配置
    res = SPI_3Line_Read2Bytes(0x1B);
    Txdata = (res & 0x0FFF) + (0x01 << 12);
    SafeWord = SPI_3Line_Write2Bytes(Txdata,0x1B);

}


uint16_t SPI_3Line_Write2Bytes(uint16_t data,uint16_t Addr)
{
    uint16_t Len = 0;
    uint16_t i = 0;
    uint16_t dummy = 0;
    uint16_t SpiBTxBuf[10];
    uint16_t SpiBRxBuf[10];
    uint16_t safe_word;

    //写指令操作,Range = 1，写入一个字（带安全字节）
    SpiBTxBuf[0] = (((uint16_t)WR_CMD)  + (((uint16_t)Addr) >> 4))<< 8;
    SpiBTxBuf[1] = (((((uint16_t)Addr) & 0x0f) << 4) + ((uint16_t)RANG_BIT))<< 8;
    //写入数据
    SpiBTxBuf[2] = ((data >> 8) << 8);
    SpiBTxBuf[3] = ((data & 0x00ff) << 8);

    //指令发送
    GPIO_setDirectionMode(201, GPIO_DIR_MODE_OUT);                // Output
    SPI_enableTalk(SPIB_BASE); // Enable Transmit path

    GPIO_writePin( 200,0 );    // 引脚Off

    HWREGH(SPIB_BASE + SPI_O_TXBUF) = SpiBTxBuf[ 0 ];
    HWREGH(SPIB_BASE + SPI_O_TXBUF) = SpiBTxBuf[ 1 ];
    HWREGH(SPIB_BASE + SPI_O_TXBUF) = SpiBTxBuf[ 2 ];
    HWREGH(SPIB_BASE + SPI_O_TXBUF) = SpiBTxBuf[ 3 ];
    KlibWaitus(30);

    //while(SPI_isBusy(SPIA_BASE));

    dummy = SPI_readDataNonBlocking(SPIB_BASE); // 丢弃
    dummy = SPI_readDataNonBlocking(SPIB_BASE);
    dummy = SPI_readDataNonBlocking(SPIB_BASE);
    dummy = SPI_readDataNonBlocking(SPIB_BASE);

    KlibWaitus(5);

    SPI_disableTalk(SPIB_BASE); // Disable Transmit path
    GPIO_setDirectionMode(201, GPIO_DIR_MODE_IN);                // Output

    HWREGH(SPIB_BASE + SPI_O_TXBUF) = dummy; // Send dummy to start tx
    HWREGH(SPIB_BASE + SPI_O_TXBUF) = dummy; // Send dummy to start tx

    //while(SPI_isBusy(SPIA_BASE));
    KlibWaitus(15);

    GPIO_writePin( 200,1 );    // 引脚Off

    Len = SPI_getRxFIFOStatus(SPIB_BASE);
    if( Len != 0 )
    {
        for( i = 0; i < Len; i++ )
        {
            SpiBRxBuf[ i ] = SPI_readDataNonBlocking(SPIB_BASE);
        }
    }

    //反馈安全字节
    safe_word = ((SpiBRxBuf[0] & 0x00FF) << 8)  + (SpiBRxBuf[1] & 0x00FF);
    return safe_word;
}


uint32_t SPI_3Line_Read2Bytes(uint16_t Addr)
{
    uint16_t dummy = 0 ;
    uint16_t safe_word;
    uint16_t receive_data;
    uint16_t Len = 0;
    uint16_t i = 0;
    uint16_t SpiBTxBuf[10];
    uint16_t SpiBRxBuf[10];
    uint8_t SpiBRxBuf8[10];

    //读指令操作,Range = 1，写入一个字（带安全字节）
    SpiBTxBuf[0] = (((uint16_t)RD_CMD)  + (((uint16_t)Addr) >> 4))<< 8;
    SpiBTxBuf[1] = (((((uint16_t)Addr) & 0x0f) << 4) + ((uint16_t)RANG_BIT))<< 8;

    //发送读指令
    GPIO_setDirectionMode(201, GPIO_DIR_MODE_OUT);                // Output
    SPI_enableTalk(SPIB_BASE); // Enable Transmit path
    GPIO_writePin( 200,0 );    // 引脚Off

    HWREGH(SPIB_BASE + SPI_O_TXBUF) = SpiBTxBuf[ 0 ];
    HWREGH(SPIB_BASE + SPI_O_TXBUF) = SpiBTxBuf[ 1 ];

    //while(SPI_isBusy(SPIA_BASE));
    KlibWaitus(15);

    dummy = SPI_readDataNonBlocking(SPIB_BASE); // 丢弃
    dummy = SPI_readDataNonBlocking(SPIB_BASE);

    //等待反馈数据

    KlibWaitus(5);
    SPI_disableTalk(SPIB_BASE); // Disable Transmit path
    GPIO_setDirectionMode(201, GPIO_DIR_MODE_IN);                // Input

    HWREGH(SPIB_BASE + SPI_O_TXBUF) = dummy; // Send dummy to start tx
    HWREGH(SPIB_BASE + SPI_O_TXBUF) = dummy; // Send dummy to start tx
    HWREGH(SPIB_BASE + SPI_O_TXBUF) = dummy; // Send dummy to start tx
    HWREGH(SPIB_BASE + SPI_O_TXBUF) = dummy; // Send dummy to start tx

    //while(SPI_isBusy(SPIA_BASE));
    KlibWaitus(30);

    GPIO_writePin( 200,1 );    // 引脚Off

    Len = SPI_getRxFIFOStatus(SPIB_BASE);
    if( Len != 0 )
    {
        for( i = 0; i < Len; i++ )
        {
            SpiBRxBuf[ i ] = SPI_readDataNonBlocking(SPIB_BASE);
            SpiBRxBuf8[i+2] = (uint8_t)(SpiBRxBuf[i] & 0xFF);
        }
    }

    SpiBRxBuf8[0] = SpiBTxBuf[0] >> 8;
    SpiBRxBuf8[1] = SpiBTxBuf[1] >> 8;

    //返回数据和安全字节
    receive_data = (((uint16_t)SpiBRxBuf8[2]) << 8) +((uint16_t)SpiBRxBuf8[3]) ;

    return receive_data;
}

/**********************************************************************************************/
/* Function_Name: MT6709_PosWrite_Cmd         */
/* Description  : 6709实时读取位置指令发送
               调用：每个SCANA获取一次
               输入：
               输出：   */
/**********************************************************************************************/
void MT6709_PosWrite_Cmd( uint32_t base )
{
    // 启用发送
    GPIO_setDirectionMode(201, GPIO_DIR_MODE_OUT);                // Output
    SPI_enableTalk(base);

    //SPI_clearInterruptStatus(base, SPI_INT_RXFF);  //清中断标志

    GPIO_writePin( 200,0 );    // 引脚Off
    if(MT6709_CORRECT_ON == 1)//校准标志
    {
        switch( MT6709_CorrectStep )
        {
            /*------------------------------------------------------------------------------------------*/
            case 0:
                SPI_writeDataNonBlocking( base, 0x8000 );  //读校准开关寄存器,读07寄存器1个字+安全字
                SPI_writeDataNonBlocking( base, 0x7100 );  //8071
                MT6709_TXdummy_num = 4;
            break;
            /*------------------------------------------------------------------------------------------*/
            case 1:
                MT6709_Txdata = (MT6709_receive_data & 0xFFFE) + 0x01;
                SPI_writeDataNonBlocking( base, 0x0000 );  //写校准开关寄存器,开启校准
                SPI_writeDataNonBlocking( base, 0x7100 );  //0070
                SPI_writeDataNonBlocking( base, ((MT6709_Txdata >> 8) << 8) );
                SPI_writeDataNonBlocking( base, ((MT6709_Txdata & 0x00ff) << 8) );
                MT6709_TXdummy_num = 2;
            break;
            case 2:
                SPI_writeDataNonBlocking( base, 0x8E00 );  //读校准状态,读E4寄存器1个字+安全字
                SPI_writeDataNonBlocking( base, 0x4100 );  //8E41
                MT6709_TXdummy_num = 4;
            break;
            case 3:
                MT6709_Txdata = (MT6709_receive_data & 0xFFFE);
                SPI_writeDataNonBlocking( base, 0x0000 );  //写校准开关寄存器,关闭校准
                SPI_writeDataNonBlocking( base, 0x7100 );  //0070
                SPI_writeDataNonBlocking( base, ((MT6709_Txdata >> 8) << 8) );
                SPI_writeDataNonBlocking( base, ((MT6709_Txdata & 0x00ff) << 8) );
                MT6709_TXdummy_num = 2;
            break;
            /*------------------------------------------------------------------------------------------*/
            default:
            break;
        }
    }
    else
    {
        SPI_writeDataNonBlocking( base, 0x8000 );  //读位置,读01寄存器2个字+安全字
        SPI_writeDataNonBlocking( base, 0x1200 );  //8012
        MT6709_TXdummy_num = 6;
    }

}

/**********************************************************************************************/
/* Function_Name: MT6709_PosRead_Cmd         */
/* Description  : 6709实时读取位置指令发送(后24bit)
               调用：每个SCANA获取一次
               输入：
               输出：   */
/**********************************************************************************************/
void MT6709_PosRead_Cmd( uint32_t base )
{
    USHORT i,dummy;

    if((MT6709_CorrectStep==1) || (MT6709_CorrectStep==3))
    {
        dummy = SPI_readDataNonBlocking(base);
        dummy = SPI_readDataNonBlocking(base);
        dummy = SPI_readDataNonBlocking(base);
        dummy = SPI_readDataNonBlocking(base);
    }
    else
    {
        dummy = SPI_readDataNonBlocking(base); // 丢弃
        dummy = SPI_readDataNonBlocking(base);
    }

    //  启用接收
    SPI_disableTalk(base);
    GPIO_setDirectionMode(201, GPIO_DIR_MODE_IN);                // IN

    // 连续发送4或6个dummy字节
    for(i = 0; i < MT6709_TXdummy_num; i++)
   {
      SPI_writeDataNonBlocking(base, DUMMY_BYTE[i]);
   }


}
/**********************************************************************************************/
/* Function_Name: MT6709_CRC_Check         */
/* Description  : CRC polynomial X^8+X^4+X^3+X^2+1, width=8bits, poly=1D, init=ff, xorout=FF *
            调用：
            输入：
            输出： */
/**********************************************************************************************/
uint8_t MT6709_CRC_Check(uint8_t *ptr, uint8_t len)
{
    uint8_t i = 0;
    uint8_t cPoly= 0x1D;
    uint8_t crc=0xFF;

    while(len--)
    {
        crc ^= *ptr++;

        for (i=8; i>0; --i)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ cPoly;
            else
                crc = (crc << 1);
        }
    }
    crc = crc ^ 0xFF;
    crc = crc & 0xFF;
    return (crc);
}


void MT6709_ReadAngleA( void )
{
USHORT i,Len_111;
USHORT rDataSPI[6] = {0};
uint8_t rDataSPI8[8] = {0};
ULONG  PosTmp;

/*
    //IF模式不读取位置
    if( (( Prm.b_prm0_0 & 0x000F ) == 0x0007) && (( Prm.Icmu & 0x0010 ) == 0x0000) )
    {
        MT6709_V.PosA = 0;
        MT6709_V.StatusA = 0;
        return;
    }
*/
    GPIO_writePin( 200,1 );    // 引脚On
    //每个SCANA周期先从寄存器中获取位置参数，再发送位置指令，在EEPROM写入和初始化完成后会先执行位置指令发送后在SCANA中再获取
    Len_111 = SPI_getRxFIFOStatus(SPIB_BASE);
    if( Len_111 != 0)
    {
        for( i = 0; i < Len_111; i ++)
        {
            rDataSPI[ i ] = SPI_readDataNonBlocking(SPIB_BASE);
            rDataSPI8[i+2] = (uint8_t)(rDataSPI[i] & 0xFF);

        }

        if(MT6709_CORRECT_ON == 1)
        {
            switch( MT6709_CorrectStep )
            {
                /*------------------------------------------------------------------------------------------*/
                case 0:
                    MT6709_receive_data = (((uint16_t)SpiBRxBuf8[2]) << 8) + ((uint16_t)SpiBRxBuf8[3]);
                    MT6709_CorrectStep  ++;
                break;
                /*------------------------------------------------------------------------------------------*/
                case 1:
                    MT6709_CorrectStep  ++;
                break;
                case 2:
                    rDataSPI8[0] = 0x8E;
                    rDataSPI8[1] = 0x41;

                    if(MT6709_CRC_Check(rDataSPI8, 4) == rDataSPI8[5])//CRC校验正确,默认设置只校验SPI命令和数据字，没有安全字部分
                    {
                        MT6709_CAL_STATE = rDataSPI8[2] & 0x03;

                        if(MT6709_crcErrCnt != 0)
                            MT6709_crcErrCnt--;
                    }
                    else
                    {
                        MT6709_crcErrCnt++;
                        if(MT6709_crcErrCnt > 100)
                            KPI_ALARMSET( ALM_PGCOM  );             // A.C90 : 编码器通信異常
                    }

                    if((MT6709_CAL_STATE ==2) || (MT6709_CAL_STATE ==3))
                    {
                        MT6709_waittime ++;
                        if(MT6709_waittime > 10000)     //校准完成等待大于500ms
                            MT6709_CorrectStep  ++;
                    }
                break;
                case 3:
                    MT6709_CORRECT_ON = MT6709_CAL_STATE;
                    MT6709_CorrectStep = 0;
                    MT6709_waittime = 0;
                break;
                /*------------------------------------------------------------------------------------------*/
                default:
                break;
            }
        }
        else
        {
            rDataSPI8[0] = 0x80;
            rDataSPI8[1] = 0x12;

            if(MT6709_CRC_Check(rDataSPI8, 6) == rDataSPI8[7])//CRC校验正确,默认设置只校验SPI命令和数据字，没有安全字部分
            {
                CTek5900_PosOri = (((LONG)rDataSPI8[ 2 ]<< 9) + ((LONG)rDataSPI8[ 3 ]<< 1) + ((rDataSPI8[ 4 ] & 0x80) >>7)) <<2;

                if(Prm.Pn534)
                    CTek5900_PosOri = FencV.FencPulseNo - CTek5900_PosOri - 1;

                if(MT6709_crcErrCnt != 0)
                    MT6709_crcErrCnt--;

                if( POS_COMPENS_ENABLE )
                    CTek5900_Comp = IntegralComp(CTek5900_PosOri);
                else
                    CTek5900_Comp = CTek5900_PosOri;


                PosTmp = (CTek5900_Comp + FencV.FencPulseNo - ULONGOF( Prm.PosBOffSetL, Prm.PosBOffSetH )) & 0x7FFFF;
                CTek5900_Pos = PosTmp;
            }
            else
            {
                MT6709_crcErrCnt++;
                if(MT6709_crcErrCnt > 100)
                    KPI_ALARMSET( ALM_PGCOM  );             // A.C90 : 编码器通信異常
            }

        }

    }
    else
    {
        MT6709_V.StatusA |= 0x0100;
    }

    //发送位置指令
    LoadEncCompensateRun();

    MT6709_PosWrite_Cmd( SPIB_BASE );
}

void MT6709_ST_MT_Get( void )
{
    MT6709_ReadAngleA();
}

