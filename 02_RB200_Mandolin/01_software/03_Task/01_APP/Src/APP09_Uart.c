//*************************************************************************************************
//文件名:App09_Uart.c
//创建时间:2022.07.11
//版本说明:V1.0
//功能描述:Uart 初始化配置
//*************************************************************************************************
#include "Main.h"

#ifdef CPU1
#define RS485_Base  SCIA_BASE
#endif



/****************************************************************************************************/
/*                                                                                                  */
/*  Uart初始化                                                                                        */
/*                                                                                                  */
/****************************************************************************************************/
void InitCpu1_Uart( void )
{

#ifdef CPU1
    /*----------------------------------------------------------------------------------------------*/
    /* GPIO36 is the SCI Tx pin                                                                     */
    /*----------------------------------------------------------------------------------------------*/
    GPIO_setPinConfig( GPIO_36_SCIA_TX );
    GPIO_setPadConfig(36, GPIO_PIN_TYPE_PULLUP);

    /*----------------------------------------------------------------------------------------------*/
    /* GPIO35 is the SCI Rx pin.                                                                    */
    /*----------------------------------------------------------------------------------------------*/
    GPIO_setPinConfig( GPIO_35_SCIA_RX );
    GPIO_setQualificationMode(35, GPIO_QUAL_ASYNC);
    GPIO_setPadConfig(35, GPIO_PIN_TYPE_PULLUP);

    /*----------------------------------------------------------------------------------------------*/
    /* GPIO37 is Rx-Tx Selection.                                                                   */
    /*----------------------------------------------------------------------------------------------*/
    GPIO_setPinConfig(GPIO_37_GPIO37);
    GPIO_setDirectionMode(37, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(37, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(37, GPIO_QUAL_SYNC);
    GPIO_setMasterCore(37, GPIO_CORE_CPU1);

    Rx485_RxMODE();     // 初始化为接收状态

#endif

    /*----------------------------------------------------------------------------------------------*/
    /* Initialize SCIA and its FIFO                                                                 */
    /*----------------------------------------------------------------------------------------------*/
    SCI_performSoftwareReset(RS485_Base);

    /*----------------------------------------------------------------------------------------------*/
    /* Configure SCIA for echoback                                                                  */
    /*----------------------------------------------------------------------------------------------*/
ULONG Baud;
ULONG Config;
    //---------------------------------------------------------------------------------------------
    // 波特率选择
    //---------------------------------------------------------------------------------------------

    switch( Prm.Mode & 0x000F)
    {
        case 0x0000: Baud = 4800;   Sif.FrameEndValue = 95;  break;
        case 0x0001: Baud = 9600;   Sif.FrameEndValue = 48;  break;
        case 0x0002: Baud = 19200;  Sif.FrameEndValue = 25;  break;
        case 0x0003: Baud = 38400;  Sif.FrameEndValue = 13;  break;
        case 0x0004: Baud = 57600;  Sif.FrameEndValue = 9;   break;
        case 0x0005: Baud = 115200; Sif.FrameEndValue = 5;   break;
        default:
                     Baud = 19200;  Sif.FrameEndValue = 25;
                     KpiSetParamError( &pndef_Mode );
        break;
    }
    //---------------------------------------------------------------------------------------------
    // 通讯格式
    //---------------------------------------------------------------------------------------------
    switch( Prm.Mode & 0x00F0)
    {
        case 0x0000: Config = SCI_CONFIG_PAR_NONE | SCI_CONFIG_WLEN_8 | SCI_CONFIG_STOP_ONE;    break;
        case 0x0010: Config = SCI_CONFIG_PAR_EVEN | SCI_CONFIG_WLEN_8 | SCI_CONFIG_STOP_ONE;    break;
        case 0x0020: Config = SCI_CONFIG_PAR_ODD  | SCI_CONFIG_WLEN_8 | SCI_CONFIG_STOP_ONE;    break;
        case 0x0030: Config = SCI_CONFIG_PAR_NONE | SCI_CONFIG_WLEN_8 | SCI_CONFIG_STOP_TWO;    break;
        case 0x0040: Config = SCI_CONFIG_PAR_EVEN | SCI_CONFIG_WLEN_8 | SCI_CONFIG_STOP_TWO;    break;
        case 0x0050: Config = SCI_CONFIG_PAR_ODD  | SCI_CONFIG_WLEN_8 | SCI_CONFIG_STOP_TWO;    break;
        default:
            Config = SCI_CONFIG_PAR_NONE | SCI_CONFIG_WLEN_8 | SCI_CONFIG_STOP_ONE;
            KpiSetParamError( &pndef_Mode );
        break;
    }


    SCI_setConfig(RS485_Base, DEVICE_LSPCLK_FREQ, Baud, Config);
    /*----------------------------------------------------------------------------------------------*/
    SCI_resetChannels(RS485_Base);
    SCI_resetRxFIFO(RS485_Base);
    SCI_resetTxFIFO(RS485_Base);
    SCI_clearInterruptStatus(RS485_Base, SCI_INT_TXFF | SCI_INT_RXFF);
    SCI_enableFIFO(RS485_Base);
    SCI_enableModule(RS485_Base);
    SCI_performSoftwareReset(RS485_Base);
}

//#define SCI_RXSTATUS_Err (SCI_RXSTATUS_PARITY | SCI_RXSTATUS_OVERRUN| SCI_RXSTATUS_FRAMING|SCI_RXSTATUS_ERROR)
#define SCI_RXSTATUS_Err (SCI_RXSTATUS_OVERRUN| SCI_RXSTATUS_FRAMING|SCI_RXSTATUS_ERROR)



/****************************************************************************************************/
/*                                                                                                  */
/* Uart 收发数据测试                                                                                   */
/*                                                                                                  */
/****************************************************************************************************/
void RS485MsgManager( void )
{
    uint16_t i;
    uint16_t DataTmp;
    uint16_t FifoNum;
    volatile uint16_t dummy;
    ULONG rc;

//    if( Kprm.f.EtherCATNet == 1  )      // EtherCAT 无 RS485 通讯
//    {
//        return;
//    }

    //---------------------------------------------------------------------------------------------
    // 数据接收处理(进行奇/偶数校验以及相关错误处理)
    //---------------------------------------------------------------------------------------------
    DataTmp = HWREGH(RS485_Base + SCI_O_RXST);
    if( DataTmp & SCI_RXSTATUS_PARITY)
    {
        FifoNum = SCI_getRxFIFOStatus( RS485_Base );
        for( i = 0; i < FifoNum;i++ )
        {
            dummy = (uint16_t)(HWREGH(RS485_Base + SCI_O_RXBUF) & SCI_RXBUF_SAR_M);
        }
        Sif.SqStep = 0;
    }
    //---------------------------------------------------------------------------------------------
    // 数据接收处理(错误处理)
    //---------------------------------------------------------------------------------------------
    if((DataTmp & SCI_RXSTATUS_Err) != 0)
    {
#ifdef CPU1
        SciaRegs.SCICTL1.bit.SWRESET = 0;
        asm(" RPT #10 || NOP");
        SciaRegs.SCICTL1.bit.SWRESET = 1;
#endif

    }
    switch( Sif.SqStep )
    {
        //-----------------------------------------------------------------------------------------
        case SQSTEP_INITIAL:                        // 初始化
            Rx485_RxMODE( );
            Sif.SqStep = SQSTEP_STARTRX;
        break;
        //-----------------------------------------------------------------------------------------
        case SQSTEP_STARTRX:
            DataTmp = ((SCI_RxFIFOLevel)((HWREGH(RS485_Base + SCI_O_FFRX) & SCI_FFRX_RXFFST_M) >> \
                        SCI_FFRX_RXFFST_S));
            if( DataTmp != 0 )
            {
                Sif.RxDbcRv = DataTmp;              // 第一次接收到的数据
                for( i = 0;i < DataTmp; i++)
                {
                    Sif.RxBuf[ i ] = (uint16_t)(HWREGH(RS485_Base + SCI_O_RXBUF) & SCI_RXBUF_SAR_M);
                }
                Sif.FrameEndCnt = 0;                // 字符结束计数标志清零
                Sif.SqStep = SQSTEP_WAITRX;
            }
        break;
        //-----------------------------------------------------------------------------------------
        case SQSTEP_WAITRX:
            DataTmp = SCI_getRxFIFOStatus( RS485_Base );
            if( 0 != DataTmp)
            {
                for( i = 0; i < DataTmp;i++ )
                {
                    Sif.RxBuf[ Sif.RxDbcRv + i ] = (uint16_t)(HWREGH(RS485_Base + SCI_O_RXBUF) & SCI_RXBUF_SAR_M);
                }
                Sif.RxDbcRv += DataTmp;
                Sif.FrameEndCnt = 0;
            }
            else
            {
                Sif.FrameEndCnt ++;
            }
            /*--------------------------------------------------------------------------------------*/
            if( Sif.FrameEndCnt > Sif.FrameEndValue )
            {
                Sif.SqStep = SQSTEP_RXCMPLT;
            }
        break;
        //-----------------------------------------------------------------------------------------
        case SQSTEP_RXCMPLT:
            Sif.RcvbLength = Sif.RxDbcRv;         // 长度赋值
            rc = LpxSifMbusChkMyMsg( );                // 检查地址是否正确
            if( rc == TRUE )
            {
                Sif.SqStep = SQSTEP_WAITSTX;            // 数据是本机地址
            }
            else
            {
                Sif.SqStep = SQSTEP_INITIAL;            // 非本机地址数据,返回
            }
            break;
        //-----------------------------------------------------------------------------------------
        case SQSTEP_WAITSTX:
            break;
        //-----------------------------------------------------------------------------------------
        case SQSTEP_WAITSTX2:                           // 开始回复数据
             if( Sif.ReqStx == SIFREQ_STARTTX )
             {
                Sif.ReqStx  = 0x0000;
                Sif.TxBufpx = Sif.TxBuf;                // 发送Buf指针
                Sif.TransReMain = Sif.MbusTrnLength;    // 待发送数据长度
                Sif.TransSum    = 0;                    // 已经发送的长度;
                Rx485_TxMODE( );                        // 发送引脚置为发送状态
                Sif.SqStep  = SQSTEP_STARTTX;           // 数据搬移处理
             }
             else if( Sif.ReqStx == SIFREQ_NOANSWER )   // 无需应答数据,直接返回
             {
                Sif.ReqStx  = 0x0000;
                Sif.SqStep  = SQSTEP_INITIAL;
             }
             break;
        //-----------------------------------------------------------------------------------------
        case SQSTEP_STARTTX:                            // 开始发送
            rc = ((HWREGH(RS485_Base + SCI_O_FFTX) & SCI_FFTX_TXFFST_M) != 0) ? true : false;
            if( rc == false)
            {
                if( Sif.TransReMain > 16 )
                {
                    for( i = 0; i < 16; i++ )
                    {
                        HWREGH(RS485_Base + SCI_O_TXBUF) = Sif.TxBuf[ Sif.TransSum + i ];
                    }
                    Sif.TransSum  += 16;
                    Sif.TransReMain -= 16;
                }
                else
                {
                    for( i = 0; i < Sif.TransReMain; i++ )
                    {
                        HWREGH(RS485_Base + SCI_O_TXBUF) = Sif.TxBuf[ Sif.TransSum + i ];
                    }
                    Sif.TransSum  = 0;
                    Sif.TransReMain = 0;
                }
                if( Sif.TransReMain == 0 )
                {
                    Sif.SqStep = SQSTEP_WAITETX;
                }
            }
            break;
        //-----------------------------------------------------------------------------------------
        case SQSTEP_WAITETX:
            rc = (((HWREGH(RS485_Base + SCI_O_CTL2) & SCI_CTL2_TXEMPTY) == SCI_CTL2_TXEMPTY) ? false : true);
            if( rc == false )
            {
                Sif.SqStep = SQSTEP_INITIAL;
            }
            break;
        //-----------------------------------------------------------------------------------------
        default:
            Sif.SqStep = SQSTEP_INITIAL;
            break;
    }
}





