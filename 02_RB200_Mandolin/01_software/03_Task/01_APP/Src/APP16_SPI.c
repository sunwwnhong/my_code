//*************************************************************************************************
//文件名:APP16_SPI.c
//创建时间:2022.07.11
//版本说明:V1.0
//功能描述:Can初始化配置
//*************************************************************************************************
#include "Main.h"
/*
__interrupt void spiaRxFIFOISR(void);
const USHORT DUMMY_BYTE[3] = {0x0505,0x0505,0x0505};
USHORT TEST_333 = 0;

__interrupt void spiaRxFIFOISR(void)
{
    USHORT i,trash;

    trash = SPI_readDataNonBlocking(SPIA_BASE); // 丢弃

    //  启用接收
    SPI_disableTalk(SPIA_BASE);
    GPIO_setDirectionMode(16, GPIO_DIR_MODE_IN);                // IN

    SPI_disableInterrupt(SPIA_BASE, SPI_INT_RXFF);        //FIFO RX中断去使能
    SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF);  //清中断标志

    //  确认PIE中断
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP6);

    // 连续发送3个dummy字节
    for(i = 0; i < 3; i++)
   {
      SPI_writeDataNonBlocking(SPIA_BASE, DUMMY_BYTE[i]);
   }

    TEST_333++;

}
*/

//*************************************************************************************************
//
// SPI初始化,ICHAUS 电机端编码器用
//
//*************************************************************************************************
void InitCpu1_SPIA( void )
{
    EALLOW;

    //---------------------------------------------------------------------------------------------
    // 引脚定义
    //---------------------------------------------------------------------------------------------
    //
    // SPIA -> CLK
    //
    GPIO_setAnalogMode(18, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_18_SPIA_CLK);
    GPIO_setPadConfig(18, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(18, GPIO_QUAL_ASYNC);

    //
    // SPIA -> SIMO
    //
    GPIO_setAnalogMode(16, GPIO_ANALOG_DISABLED);
    GPIO_setDirectionMode(16, GPIO_DIR_MODE_OUT);                // Output
    GPIO_setPinConfig(GPIO_16_SPIA_PICO);
    GPIO_setPadConfig(16, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(16, GPIO_QUAL_ASYNC);
    //
    // SPIA -> SOMI
    //
    //GPIO_setPinConfig(GPIO_17_SPIA_POCI);
    //GPIO_setPadConfig(17, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    //GPIO_setQualificationMode(17, GPIO_QUAL_ASYNC);
    //
    // SPIA -> STEN
    //
    //GPIO_setPinConfig(GPIO_57_SPIA_PTE);
    //GPIO_setPadConfig(57, GPIO_PIN_TYPE_STD);
    //GPIO_setQualificationMode(57, GPIO_QUAL_ASYNC);

    GPIO_setAnalogMode(17, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_17_GPIO17);
    GPIO_setDirectionMode(17, GPIO_DIR_MODE_OUT);               // Output
    GPIO_setPadConfig(17, GPIO_PIN_TYPE_STD);                   // Open Drain
    GPIO_setMasterCore(17, GPIO_CORE_CPU1);                     // CPU1 使用
    GPIO_writePin( 17,0 );    // 引脚Off

    GPIO_setAnalogMode(57, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_57_GPIO57);
    GPIO_setDirectionMode(57, GPIO_DIR_MODE_OUT);               // Output
    GPIO_setPadConfig(57, GPIO_PIN_TYPE_STD);                   // Open Drain
    GPIO_setMasterCore(57, GPIO_CORE_CPU1);                     // CPU1 使用
    GPIO_writePin( 57,1 );    // 引脚On

    SPI_disableModule(SPIA_BASE);
    SPI_setConfig(SPIA_BASE, \
                  DEVICE_LSPCLK_FREQ, \
                  SPI_PROT_POL1PHA0,\
                  SPI_MODE_CONTROLLER, \
                  1000000, \
                  8);
    SPI_enableTriWire(SPIA_BASE);   //3线SPI使能
    SPI_enableFIFO(SPIA_BASE);          // 开启FIFO
    //SPI_setFIFOInterruptLevel(SPIA_BASE, SPI_FIFO_TX0, SPI_FIFO_RX1); //FIFO中断等级配置，TX不使用默认，RX配置为1

    SPI_disableLoopback(SPIA_BASE);
    SPI_setEmulationMode(SPIA_BASE, SPI_EMULATION_STOP_MIDWAY);
    SPI_enableModule(SPIA_BASE);

    //Interrupt_register(INT_SPIA_RX, &spiaRxFIFOISR);
    //Interrupt_enable(INT_SPIA_RX);

    EDIS;
}

void InitCpu1_SPIB( void )
{
    EALLOW;

    //---------------------------------------------------------------------------------------------
    // 引脚定义
    //---------------------------------------------------------------------------------------------
    //
    // SPIB -> CLK
    //
    GPIO_setAnalogMode(199, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_199_SPIB_CLK);

    GPIO_setPadConfig(199, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(199, GPIO_QUAL_ASYNC);

    //
    // SPIB -> SIMO
    //
    GPIO_setAnalogMode(201, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_201_SPIB_PICO);
    GPIO_setPadConfig(201, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(201, GPIO_QUAL_ASYNC);
    //
    // SPIB -> SOMI
    //
    GPIO_setAnalogMode(202, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_202_SPIB_POCI);
    GPIO_setPadConfig(202, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(202, GPIO_QUAL_ASYNC);
    //
    // SPIB -> STEN
    //
    GPIO_setAnalogMode(200, GPIO_ANALOG_DISABLED);
    GPIO_setPinConfig(GPIO_200_SPIB_PTE);
    GPIO_setPadConfig(200, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(200, GPIO_QUAL_ASYNC);

    //@20250725 yjp SPI模式调整为与CTek5900适配
    SPI_disableModule(SPIB_BASE);
    SPI_setConfig(SPIB_BASE, \
                  DEVICE_LSPCLK_FREQ, \
                  SPI_PROT_POL0PHA1,\
                  SPI_MODE_CONTROLLER, \
                  5000000, \
                  8);
    SPI_enableFIFO(SPIB_BASE);          // 开启FIFO

    SPI_disableLoopback(SPIB_BASE);
    SPI_setEmulationMode(SPIB_BASE, SPI_EMULATION_STOP_MIDWAY);
    SPI_enableModule(SPIB_BASE);

    EDIS;
}

void InitCpu1_SPIB_HiZ(void)
{
    GPIO_setPinConfig(GPIO_199_GPIO199);                          //  引脚#
    GPIO_setDirectionMode(199, GPIO_DIR_MODE_IN);                //  Input
    GPIO_setPadConfig(199, GPIO_PIN_TYPE_STD);                //  上拉
    GPIO_setMasterCore(199, GPIO_CORE_CPU1);                     //  CPU1使用
    GPIO_setQualificationMode(199, GPIO_QUAL_6SAMPLE);           //  滤波时间

    GPIO_setPinConfig(GPIO_200_GPIO200);                           // 引脚#
    GPIO_setDirectionMode(200, GPIO_DIR_MODE_IN);                // Output
    GPIO_setPadConfig(200, GPIO_PIN_TYPE_STD);                    // Open Drain
    GPIO_setMasterCore(200, GPIO_CORE_CPU1);                      // CPU1 使用
    GPIO_setQualificationMode(200, GPIO_QUAL_SYNC);               // 滤波时间

    GPIO_setPinConfig(GPIO_201_GPIO201);                           // 引脚#
    GPIO_setDirectionMode(201, GPIO_DIR_MODE_IN);                // Output
    GPIO_setPadConfig(201, GPIO_PIN_TYPE_STD);                    // Open Drain
    GPIO_setMasterCore(201, GPIO_CORE_CPU1);                      // CPU2 使用
    GPIO_setQualificationMode(201, GPIO_QUAL_SYNC);               // 滤波时间

    GPIO_setPinConfig(GPIO_202_GPIO202);                           // 引脚#
    GPIO_setDirectionMode(202, GPIO_DIR_MODE_IN);                // Output
    GPIO_setPadConfig(202, GPIO_PIN_TYPE_STD);                    // Open Drain
    GPIO_setMasterCore(202, GPIO_CORE_CPU1);                      // CPU2 使用
    GPIO_setQualificationMode(202, GPIO_QUAL_SYNC);               // 滤波时间
}


void InitCpu1_SPIA_HiZ(void)
{
    GPIO_setPinConfig(GPIO_18_GPIO18);                          //  引脚#
    GPIO_setDirectionMode(18, GPIO_DIR_MODE_IN);                //  Input
    GPIO_setPadConfig(18, GPIO_PIN_TYPE_STD);                //  上拉
    GPIO_setMasterCore(18, GPIO_CORE_CPU1);                     //  CPU1使用
    GPIO_setQualificationMode(18, GPIO_QUAL_6SAMPLE);           //  滤波时间

    GPIO_setPinConfig(GPIO_57_GPIO57);                           // 引脚#
    GPIO_setDirectionMode(57, GPIO_DIR_MODE_IN);                // Output
    GPIO_setPadConfig(57, GPIO_PIN_TYPE_STD);                    // Open Drain
    GPIO_setMasterCore(57, GPIO_CORE_CPU1);                      // CPU1 使用
    GPIO_setQualificationMode(57, GPIO_QUAL_SYNC);               // 滤波时间

    GPIO_setPinConfig(GPIO_16_GPIO16);                           // 引脚#
    GPIO_setDirectionMode(16, GPIO_DIR_MODE_IN);                // Output
    GPIO_setPadConfig(16, GPIO_PIN_TYPE_STD);                    // Open Drain
    GPIO_setMasterCore(16, GPIO_CORE_CPU1);                      // CPU2 使用
    GPIO_setQualificationMode(16, GPIO_QUAL_SYNC);               // 滤波时间

    GPIO_setPinConfig(GPIO_17_GPIO17);                           // 引脚#
    GPIO_setDirectionMode(17, GPIO_DIR_MODE_IN);                // Output
    GPIO_setPadConfig(17, GPIO_PIN_TYPE_STD);                    // Open Drain
    GPIO_setMasterCore(17, GPIO_CORE_CPU1);                      // CPU2 使用
    GPIO_setQualificationMode(17, GPIO_QUAL_SYNC);               // 滤波时间
}


