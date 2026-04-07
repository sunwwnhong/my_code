//*************************************************************************************************
//文件名:APP15_Can.c
//创建时间:2022.07.11
//版本说明:V1.0
//功能描述:Can初始化配置
//*************************************************************************************************
#include "Main.h"
#include "string.h"


#ifdef CPU1
#define NUM_OF_MSG                    (16U)

#define MCAN_FIFO_0_WATERMARK         (NUM_OF_MSG)
#define MCAN_FIFO_1_WATERMARK         (NUM_OF_MSG)

#define MCAN_RX_BUFF_NUM              (0U)

#define MCAN_RX_BUFF_ELEM_SIZE        (MCAN_ELEM_SIZE_8BYTES)
#define MCAN_RX_FIFO0_ELEM_SIZE       (MCAN_ELEM_SIZE_8BYTES)
#define MCAN_RX_FIFO1_ELEM_SIZE       (MCAN_ELEM_SIZE_8BYTES)

#define MCAN_TX_BUFF_SIZE             (NUM_OF_MSG)
#define MCAN_TX_BUFF_ELEM_SIZE        (MCAN_ELEM_SIZE_8BYTES)

#define MCAN_STD_ID_FILTER_NUM        (8U)
#define MCAN_EXT_ID_FILTER_NUM        (0U)
#define MCAN_STD_ID_FILT_START_ADDR   (0U)

#define MCAN_FIFO_0_NUM               (0)
#define MCAN_FIFO_0_ELEM_SIZE         (MCAN_ELEM_SIZE_8BYTES)
#define MCAN_FIFO_1_NUM               (NUM_OF_MSG)
#define MCAN_FIFO_1_ELEM_SIZE         (MCAN_ELEM_SIZE_8BYTES)


#define MCAN_EXT_ID_FILT_START_ADDR   (MCAN_STD_ID_FILT_START_ADDR + ((MCAN_STD_ID_FILTER_NUM * 1 * 4U)))

#define MCAN_FIFO_0_START_ADDR        (MCAN_EXT_ID_FILT_START_ADDR + ((MCAN_EXT_ID_FILTER_NUM * 2 * 4U)))
#define MCAN_FIFO_1_START_ADDR        (MCAN_FIFO_0_START_ADDR +  (4 * 4U * MCAN_FIFO_0_NUM))
#define MCAN_RX_BUFF_START_ADDR       (MCAN_FIFO_1_START_ADDR +  (4 * 4U * MCAN_FIFO_1_NUM))
#define MCAN_TX_BUFF_START_ADDR       (MCAN_RX_BUFF_START_ADDR + (4 * 4U * MCAN_RX_BUFF_NUM))
#define MCAN_TX_EVENT_START_ADDR      (MCAN_TX_BUFF_START_ADDR + (4 * 4U * MCAN_TX_BUFF_SIZE))


MCAN_RxBufElement RxMsg;
MCAN_TxBufElement TxMsg;
MCAN_RxFIFOStatus RxFS;
USHORT MCFIFOIndex = 0;

#endif





#ifdef CPU1
/****************************************************************************************************/
/*                                                                                                  */
/*  MCan初始化                                                                                        */
/*                                                                                                  */
/****************************************************************************************************/
static void MCANConfig(void)
{
    MCAN_InitParams initParams;
    MCAN_MsgRAMConfigParams    msgRAMConfigParams;
    MCAN_StdMsgIDFilterElement stdFiltelem;
    MCAN_BitTimingParams       bitTimes;

    //
    //  Initializing all structs to zero to prevent stray values
    //
    memset(&initParams,0,sizeof(initParams) / 2);
    memset(&msgRAMConfigParams,0,sizeof(msgRAMConfigParams) / 2);
    memset(&stdFiltelem,0,sizeof(stdFiltelem) / 2);
    memset(&bitTimes,0,sizeof(bitTimes) / 2);

    //
    // Initialize MCAN Init parameters.
    //
    initParams.fdMode            = 0x0U; // FD operation enabled.
    initParams.brsEnable         = 0x0U; // Bit rate switching enabled.


    //
    // Transmitter Delay Compensation parameters.
    //
    initParams.tdcConfig.tdcf    = 0xAU;
    initParams.tdcConfig.tdco    = 0x6U;
    //
    // Initialize other MCAN_InitParams elements
    //
    initParams.txpEnable        = 0x0U;
    initParams.efbi             = 0x0U;
    initParams.pxhddisable      = 0x0U;
    initParams.darEnable        = 0x0U;
    initParams.wkupReqEnable    = 0x1U;
    initParams.autoWkupEnable   = 0x1U;
    initParams.emulationEnable  = 0x1U;
    initParams.wdcPreload       = 0xFFU;
    initParams.tdcEnable        = 0x1U;

    //
    // Initialize Message RAM Sections Configuration Parameters
    //
    msgRAMConfigParams.txStartAddr          = MCAN_TX_BUFF_START_ADDR;
    // Tx Buffers Start Address.
    msgRAMConfigParams.txBufNum             = MCAN_TX_BUFF_SIZE;
    // Number of Dedicated Transmit Buffers.
    msgRAMConfigParams.txBufMode            = 1U;
    msgRAMConfigParams.txBufElemSize        = MCAN_ELEM_SIZE_8BYTES;
    msgRAMConfigParams.txFIFOSize           = MCAN_TX_BUFF_SIZE;
    //--------------------------------------------------------------------------
    //
    // Initialize Message RAM Sections Configuration Parameters 【 Recive 】
    //
    msgRAMConfigParams.flssa                = MCAN_STD_ID_FILT_START_ADDR;
    // Standard ID Filter List Start Address (0).
    msgRAMConfigParams.lss                  = MCAN_STD_ID_FILTER_NUM;
    // Standard ID Filter List Size (1).

    msgRAMConfigParams.rxFIFO1startAddr     = MCAN_FIFO_1_START_ADDR;
    // Rx FIFO1 Start Address (748U).
    msgRAMConfigParams.rxFIFO1size          = MCAN_FIFO_1_NUM;
    // Number of Rx FIFO elements (1).
    msgRAMConfigParams.rxFIFO1waterMark     = MCAN_FIFO_1_WATERMARK;
    // Level for Rx FIFO 1 watermark interrupt (1).
    msgRAMConfigParams.rxFIFO1OpMode        = 0U;           /* 0: Block;1:overwrite */
    // FIFO blocking mode.
    msgRAMConfigParams.rxFIFO1ElemSize      = MCAN_ELEM_SIZE_8BYTES;
    // Rx FIFO1 Element Size. RBDS field of MCAN_RXESC Register

    //
    // Initialize Message RAM Sections Configuration Parameters【 Trans 】
    //
    msgRAMConfigParams.txStartAddr          = MCAN_TX_BUFF_START_ADDR;
    // Tx Buffers Start Address.
    msgRAMConfigParams.txBufNum             = MCAN_TX_BUFF_SIZE;
    // Number of Dedicated Transmit Buffers.
    msgRAMConfigParams.txBufMode            = 0U;
    msgRAMConfigParams.txBufElemSize        = MCAN_ELEM_SIZE_8BYTES;

    //
    // Initialize bit timings.
    //
    switch((Prm.Mode >> 8) & 0x000F)
    {
        /*------------------------------------------------------------------------------------------*/
        case 0: //20K
            bitTimes.nomRatePrescalar   = 0xC7U;    // Nominal Baud Rate Pre-scaler.
            bitTimes.nomTimeSeg1        = 0x4U;     // Nominal Time segment before SP
            bitTimes.nomTimeSeg2        = 0x3U;     // Nominal Time segment after SP.
            bitTimes.nomSynchJumpWidth  = 0x3U;     // Nominal SJW
        break;
        /*------------------------------------------------------------------------------------------*/
        case 1: //50K
            bitTimes.nomRatePrescalar   = 0x4FU;     // Nominal Baud Rate Pre-scaler.
            bitTimes.nomTimeSeg1        = 0x4U;     // Nominal Time segment before SP
            bitTimes.nomTimeSeg2        = 0x3U;     // Nominal Time segment after SP.
            bitTimes.nomSynchJumpWidth  = 0x3U;     // Nominal SJW
        break;
        /*------------------------------------------------------------------------------------------*/
        case 2: //100K
            bitTimes.nomRatePrescalar   = 0x27U;    // Nominal Baud Rate Pre-scaler.
            bitTimes.nomTimeSeg1        = 0x4U;     // Nominal Time segment before SP
            bitTimes.nomTimeSeg2        = 0x3U;     // Nominal Time segment after SP.
            bitTimes.nomSynchJumpWidth  = 0x3U;     // Nominal SJW
        break;
        /*------------------------------------------------------------------------------------------*/
        case 3: //125K
            bitTimes.nomRatePrescalar   = 0x1FU;    // Nominal Baud Rate Pre-scaler.
            bitTimes.nomTimeSeg1        = 0x4U;     // Nominal Time segment before SP
            bitTimes.nomTimeSeg2        = 0x3U;     // Nominal Time segment after SP.
            bitTimes.nomSynchJumpWidth  = 0x3U;     // Nominal SJW
        break;
        /*------------------------------------------------------------------------------------------*/
        case 4: //250K
            bitTimes.nomRatePrescalar   = 0xFU;     // Nominal Baud Rate Pre-scaler.
            bitTimes.nomTimeSeg1        = 0x4U;     // Nominal Time segment before SP
            bitTimes.nomTimeSeg2        = 0x3U;     // Nominal Time segment after SP.
            bitTimes.nomSynchJumpWidth  = 0x3U;     // Nominal SJW
        break;
        /*------------------------------------------------------------------------------------------*/
        case 5: //500K
            bitTimes.nomRatePrescalar   = 0x9U;     // Nominal Baud Rate Pre-scaler.
            bitTimes.nomTimeSeg1        = 0x3U;     // Nominal Time segment before SP
            bitTimes.nomTimeSeg2        = 0x2U;     // Nominal Time segment after SP.
            bitTimes.nomSynchJumpWidth  = 0x2U;     // Nominal SJW
        break;
        /*------------------------------------------------------------------------------------------*/
        case 6: //1MHz
            bitTimes.nomRatePrescalar   = 0x3U;     // Nominal Baud Rate Pre-scaler.
            bitTimes.nomTimeSeg1        = 0x5U;     // Nominal Time segment before SP
            bitTimes.nomTimeSeg2        = 0x2U;     // Nominal Time segment after SP.
            bitTimes.nomSynchJumpWidth  = 0x2U;     // Nominal SJW
        break;
        /*------------------------------------------------------------------------------------------*/
        default://异常时默认500KHz
            bitTimes.nomRatePrescalar   = 0x9U;     // Nominal Baud Rate Pre-scaler.
            bitTimes.nomTimeSeg1        = 0x3U;     // Nominal Time segment before SP
            bitTimes.nomTimeSeg2        = 0x2U;     // Nominal Time segment after SP.
            bitTimes.nomSynchJumpWidth  = 0x3U;     // Nominal SJW
        break;
        /*------------------------------------------------------------------------------------------*/
    }
    //
    // Wait for memory initialization to happen.
    //
    while(0 == MCAN_isMemInitDone(MCAN0_BASE))
    {
        ;
    }

    //
    // Put MCAN in SW initialization mode.
    //
    MCAN_setOpMode(MCAN0_BASE, MCAN_OPERATION_MODE_SW_INIT);

    //
    // Wait till MCAN is not initialized.
    //
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(MCAN0_BASE))
    {;}

    //
    // Initialize MCAN module.
    //
    MCAN_init(MCAN0_BASE, &initParams);

    //
    // Configure Bit timings.
    //
    MCAN_setBitTime(MCAN0_BASE, &bitTimes);

    //
    // Configure Message RAM Sections
    //
    MCAN_msgRAMConfig(MCAN0_BASE, &msgRAMConfigParams);

    //
    // Configure Standard ID filter element
    //
    stdFiltelem.sfid1              = SDOID_R + Prm.Address;   // 【SDO】
    stdFiltelem.sfid2              = 0xFFFF;   // Standard ID Filter Mask.
    stdFiltelem.sfec               = 0x2U;          // Store into FIFO 1.
    stdFiltelem.sft                = 0x2U;          // SFID1 = filter; SFID2 = mask
    MCAN_addStdMsgIDFilter(MCAN0_BASE, 0U, &stdFiltelem);

    stdFiltelem.sfid1              = PDO1ID_R + Prm.Address;   // 【RPDO1】
    stdFiltelem.sfid2              = 0xFFFF;   // Standard ID Filter Mask.
    stdFiltelem.sfec               = 0x2U;          // Store into FIFO 1.
    stdFiltelem.sft                = 0x2U;          // SFID1 = filter; SFID2 = mask
    MCAN_addStdMsgIDFilter(MCAN0_BASE, 1U, &stdFiltelem);

    stdFiltelem.sfid1              = PDO2ID_R + Prm.Address;   // 【RPDO2】
    stdFiltelem.sfid2              = 0xFFFF;   // Standard ID Filter Mask.
    stdFiltelem.sfec               = 0x2U;      // Store into FIFO 1.
    stdFiltelem.sft                = 0x2U;      // SFID1 = filter; SFID2 = mask
    MCAN_addStdMsgIDFilter(MCAN0_BASE, 2U, &stdFiltelem);

    stdFiltelem.sfid1              = PDO3ID_R + Prm.Address;   // 【RPDO3】
    stdFiltelem.sfid2              = 0xFFFF;   // Standard ID Filter Mask.
    stdFiltelem.sfec               = 0x2U;          // Store into FIFO 1.
    stdFiltelem.sft                = 0x2U;          // SFID1 = filter; SFID2 = mask
    MCAN_addStdMsgIDFilter(MCAN0_BASE, 3U, &stdFiltelem);

    stdFiltelem.sfid1              = PDO4ID_R + Prm.Address;   // 【RPDO4】
    stdFiltelem.sfid2              = 0xFFFF;        // Standard ID Filter Mask.
    stdFiltelem.sfec               = 0x2U;          // Store into FIFO 1.
    stdFiltelem.sft                = 0x2U;          // SFID1 = filter; SFID2 = mask
    MCAN_addStdMsgIDFilter(MCAN0_BASE, 4U, &stdFiltelem);

    stdFiltelem.sfid1              = NMT_T;         // 【NMT】 【0】
    stdFiltelem.sfid2              = 0xFFFF;        // Standard ID Filter Mask.
    stdFiltelem.sfec               = 0x2U;          // Store into FIFO 1.
    stdFiltelem.sft                = 0x2U;          // SFID1 = filter; SFID2 = mask
    MCAN_addStdMsgIDFilter(MCAN0_BASE, 5U, &stdFiltelem);

    stdFiltelem.sfid1              = SYNC;          // 【SYNC】【80】
    stdFiltelem.sfid2              = 0xFFFF;        // Standard ID Filter Mask.
    stdFiltelem.sfec               = 0x2U;          // Store into FIFO 1.
    stdFiltelem.sft                = 0x2U;          // SFID1 = filter; SFID2 = mask
    MCAN_addStdMsgIDFilter(MCAN0_BASE, 6U, &stdFiltelem);

    stdFiltelem.sfid1              = BEAT;    //0x73F;      // 【BEAT】【700】
    stdFiltelem.sfid2              = 0xFFC0;  //0xFFFF;       // Standard ID Filter Mask.
    stdFiltelem.sfec               = 0x2U;          // Store into FIFO 1.
    stdFiltelem.sft                = 0x2U;          // SFID1 = filter; SFID2 = mask
    MCAN_addStdMsgIDFilter(MCAN0_BASE, 7U, &stdFiltelem);

    //
    // Take MCAN out of the SW initialization mode
    //
    MCAN_setOpMode(MCAN0_BASE, MCAN_OPERATION_MODE_NORMAL);

    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(MCAN0_BASE))
    {
        ;
    }
}
#endif

/****************************************************************************************************/
/*                                                                                                  */
/*  Can初始化                                                                                         */
/*                                                                                                  */
/****************************************************************************************************/
void InitCpu1_Can( void )
{
#ifdef CPU1
    //
    // Allocate MCAN (a shared peripheral) to CPU1 (C28x)
    //
  //  SysCtl_allocateSharedPeripheral(SYSCTL_PALLOCATE_MCAN_A,0x0U);

    //
    // Configure the divisor for the MCAN bit-clock
    //
    SysCtl_setMCANClk(SYSCTL_MCANA,SYSCTL_MCANCLK_DIV_5);

    //
    // Configure GPIO pins for MCANTX/MCANRX operation
    //
    GPIO_setPadConfig(214, GPIO_PIN_TYPE_PULLUP);
    GPIO_setAnalogMode(214, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig( GPIO_214_MCANA_RX );

    GPIO_setPadConfig(217, GPIO_PIN_TYPE_PULLUP);
    GPIO_setAnalogMode(217, GPIO_ANALOG_DISABLED);
    GPIO_setQualificationMode(217, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig( GPIO_217_MCANA_TX );


    //
    // Configure the MCAN Module.
    //

    MCANConfig();
#endif


    //---------------------------------------------------------------------------------------------
    // 相关数据清零
    //---------------------------------------------------------------------------------------------
#ifdef CPU1
    TxMsg.rtr      = 0U;
    TxMsg.xtd      = 0U;        // 0: Standard;1:extended
    TxMsg.esi      = 0U;
    TxMsg.brs      = 0U;
    TxMsg.fdf      = 0U;
    TxMsg.efc      = 1U;
    TxMsg.mm       = 0xAAU;
#endif
}

//*************************************************************************************************
//
// Can 总线异常检测
//
//*************************************************************************************************
void CanBussOffCheck( void )
{
#ifdef CPU1
    uint32_t DataTmp = *(volatile uint32_t *) (MCAN0_BASE + MCAN_CCCR);
    if( (DataTmp & 0x0001UL) == 0x0001UL )
    {
        *(volatile uint32_t *) (MCAN0_BASE + MCAN_CCCR) = 0UL;
    }
#endif
}


