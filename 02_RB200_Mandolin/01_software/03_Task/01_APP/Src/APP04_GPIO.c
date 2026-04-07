//*************************************************************************************************
//文件名:APP04_GPIO.c
//创建时间:2022.07.11
//版本说明:V1.0
//功能描述:MCU初始化-GPIO
//*************************************************************************************************
#include "Main.h"

/****************************************************************************************************/
/*Function_Name:InitCpuA0                                                                           */
/*Description  :CPUA系统初始化( 外设初始化 )                                                              */
/****************************************************************************************************/
void InitCpu1_GPIO(void)
{
    //轴1和轴2所有GPIO配置


    GPIO_writePin( 0,0 );    // 引脚Off
    GPIO_setPinConfig(GPIO_0_GPIO0);                          // 引脚#
    GPIO_setDirectionMode(0, GPIO_DIR_MODE_OUT);               // Output
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);                   // Open Drain
    GPIO_setMasterCore(0, GPIO_CORE_CPU1);                     // CPU1 使用

    GPIO_writePin( 1,0 );    // 引脚Off
    GPIO_setPinConfig(GPIO_1_GPIO1);                          // 引脚#
    GPIO_setDirectionMode(1, GPIO_DIR_MODE_OUT);               // Output
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);                   // Open Drain
    GPIO_setMasterCore(1, GPIO_CORE_CPU1);                     // CPU1 使用

    GPIO_writePin( 2,0 );    // 引脚Off
    GPIO_setPinConfig(GPIO_2_GPIO2);                          // 引脚#
    GPIO_setDirectionMode(2, GPIO_DIR_MODE_OUT);               // Output
    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);                   // Open Drain
    GPIO_setMasterCore(2, GPIO_CORE_CPU1);                     // CPU1 使用

    GPIO_writePin( 3,0 );    // 引脚Off
    GPIO_setPinConfig(GPIO_3_GPIO3);                          // 引脚#
    GPIO_setDirectionMode(3, GPIO_DIR_MODE_OUT);               // Output
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);                   // Open Drain
    GPIO_setMasterCore(3, GPIO_CORE_CPU1);                     // CPU1 使用

    GPIO_writePin( 4,0 );    // 引脚Off
    GPIO_setPinConfig(GPIO_4_GPIO4);                          // 引脚#
    GPIO_setDirectionMode(4, GPIO_DIR_MODE_OUT);               // Output
    GPIO_setPadConfig(4, GPIO_PIN_TYPE_STD);                   // Open Drain
    GPIO_setMasterCore(4, GPIO_CORE_CPU1);                     // CPU1 使用

    GPIO_writePin( 5,0 );    // 引脚Off
    GPIO_setPinConfig(GPIO_5_GPIO5);                          // 引脚#
    GPIO_setDirectionMode(5, GPIO_DIR_MODE_OUT);               // Output
    GPIO_setPadConfig(5, GPIO_PIN_TYPE_STD);                   // Open Drain
    GPIO_setMasterCore(5, GPIO_CORE_CPU1);                     // CPU1 使用


//    GPIO_writePin( 8,0 );    // 引脚Off
//    GPIO_setPinConfig(GPIO_8_GPIO8);                          // 引脚#
//    GPIO_setDirectionMode(8, GPIO_DIR_MODE_OUT);               // Output
//    GPIO_setPadConfig(8, GPIO_PIN_TYPE_STD);                   // Open Drain
//    GPIO_setMasterCore(8, GPIO_CORE_CPU1);                     // CPU1 使用
//---------------------------------------------------------------------------------------------
    // 再生制动引脚
    //---------------------------------------------------------------------------------------------
//    GPIO_setPinConfig(GPIO_75_GPIO75);                          // 引脚#
//    GPIO_setDirectionMode(75, GPIO_DIR_MODE_OUT);               // Output
//    GPIO_setPadConfig(75, GPIO_PIN_TYPE_STD);                   // Open Drain
//    GPIO_setMasterCore(75, GPIO_CORE_CPU1);                     // CPU1 使用
//    GPIO_setQualificationMode(75, GPIO_QUAL_SYNC);              // 滤波时间
//    KPX_BRAKE_OFF();
    //---------------------------------------------------------------------------------------------
    // MotA Can 地址
    //---------------------------------------------------------------------------------------------
//    GPIO_setPinConfig(GPIO_82_GPIO82);                          //  引脚#
//    GPIO_setDirectionMode(82, GPIO_DIR_MODE_IN);                //  Input
//    GPIO_setPadConfig(82, GPIO_PIN_TYPE_PULLUP);                //  上拉
//    GPIO_setMasterCore(82, GPIO_CORE_CPU1);                     //  CPU1使用
//    GPIO_setQualificationMode(82, GPIO_QUAL_6SAMPLE);           //  滤波时间
//
//    GPIO_setPinConfig(GPIO_89_GPIO89);                          //  引脚#
//    GPIO_setDirectionMode(89, GPIO_DIR_MODE_IN);                //  Input
//    GPIO_setPadConfig(89, GPIO_PIN_TYPE_PULLUP);                //  上拉
//    GPIO_setMasterCore(89, GPIO_CORE_CPU1);                     //  CPU1使用
//    GPIO_setQualificationMode(89, GPIO_QUAL_6SAMPLE);           //  滤波时间
//
//    GPIO_setPinConfig(GPIO_103_GPIO103);                          //  引脚#
//    GPIO_setDirectionMode(103, GPIO_DIR_MODE_IN);                //  Input
//    GPIO_setPadConfig(103, GPIO_PIN_TYPE_PULLUP);                //  上拉
//    GPIO_setMasterCore(103, GPIO_CORE_CPU1);                     //  CPU1使用
//    GPIO_setQualificationMode(103, GPIO_QUAL_6SAMPLE);           //  滤波时间
    //---------------------------------------------------------------------------------------------
    // ACT244 LOCK MotA 和MotB
    //---------------------------------------------------------------------------------------------
    MotA_PWM_Lock();
    GPIO_setPinConfig(GPIO_6_GPIO6);                            // 引脚#
    GPIO_setDirectionMode(6, GPIO_DIR_MODE_OUT);                // Output
    GPIO_setPadConfig(6, GPIO_PIN_TYPE_STD);                    // Open Drain
    GPIO_setMasterCore(6, GPIO_CORE_CPU1);                      // CPU1 使用
    GPIO_setQualificationMode(6, GPIO_QUAL_SYNC);               // 滤波时间


    //---------------------------------------------------------------------------------------------
    // 抱闸 LOCK MotA 和MotB
    //---------------------------------------------------------------------------------------------
//    GPIO_setPinConfig(GPIO_79_GPIO79);                          // 引脚#
//    GPIO_setDirectionMode(79, GPIO_DIR_MODE_OUT);               // Output
//    GPIO_setPadConfig(79, GPIO_PIN_TYPE_STD);                   // Open Drain
//    GPIO_setMasterCore(79, GPIO_CORE_CPU1);                     // CPU1 使用
//    GPIO_setQualificationMode(79, GPIO_QUAL_SYNC);              // 滤波时间

    //---------------------------------------------------------------------------------------------
    // MotA Input(X1~X4) Output(Y1~Y2)
    //---------------------------------------------------------------------------------------------
//    HWREG( GPIODATA_BASE + GPIO_O_GPBSET )   = 1UL << 17;       //GPIO49
//    HWREG( GPIODATA_BASE + GPIO_O_GPBSET )   = 1UL << 20;       //GPIO52
//
//    GPIO_setPinConfig(GPIO_12_GPIO12);                          //  引脚#
//    GPIO_setDirectionMode(12, GPIO_DIR_MODE_IN);                //  Input
//    GPIO_setPadConfig(12, GPIO_PIN_TYPE_INVERT);                //  上拉
//    GPIO_setMasterCore(12, GPIO_CORE_CPU1);                     //  CPU1使用
//    GPIO_setQualificationMode(12, GPIO_QUAL_6SAMPLE);           //  滤波时间
//
//    GPIO_setPinConfig(GPIO_13_GPIO13);                          //  引脚#
//    GPIO_setDirectionMode(13, GPIO_DIR_MODE_IN);                //  Input
//    GPIO_setPadConfig(13, GPIO_PIN_TYPE_INVERT);                //  上拉
//    GPIO_setMasterCore(13, GPIO_CORE_CPU1);                     //  CPU1使用
//    GPIO_setQualificationMode(13, GPIO_QUAL_6SAMPLE);           //  滤波时间
//
//    GPIO_setPinConfig(GPIO_14_GPIO14);                        //  引脚#
//    GPIO_setDirectionMode(14, GPIO_DIR_MODE_IN);               //  Input
//    GPIO_setPadConfig(147, GPIO_PIN_TYPE_INVERT);               //  上拉
//    GPIO_setMasterCore(14, GPIO_CORE_CPU1);                    //  CPU1使用
//    GPIO_setQualificationMode(14, GPIO_QUAL_6SAMPLE);          //  滤波时间
//
//    GPIO_setPinConfig(GPIO_15_GPIO15);                          //  引脚#
//    GPIO_setDirectionMode(15, GPIO_DIR_MODE_IN);                //  Input
//    GPIO_setPadConfig(15, GPIO_PIN_TYPE_INVERT);                //  上拉
//    GPIO_setMasterCore(15, GPIO_CORE_CPU1);                     //  CPU1使用
//    GPIO_setQualificationMode(15, GPIO_QUAL_6SAMPLE);           //  滤波时间
//
//    GPIO_setPinConfig(GPIO_49_GPIO49);                           // 引脚#
//    GPIO_setDirectionMode(49, GPIO_DIR_MODE_OUT);                // Output
//    GPIO_setPadConfig(49, GPIO_PIN_TYPE_STD);                    // Open Drain
//    GPIO_setMasterCore(49, GPIO_CORE_CPU1);                      // CPU1 使用
//    GPIO_setQualificationMode(49, GPIO_QUAL_SYNC);               // 滤波时间
//
//    GPIO_setPinConfig(GPIO_52_GPIO52);                           // 引脚#
//    GPIO_setDirectionMode(52, GPIO_DIR_MODE_OUT);                // Output
//    GPIO_setPadConfig(52, GPIO_PIN_TYPE_STD);                    // Open Drain
//    GPIO_setMasterCore(52, GPIO_CORE_CPU1);                      // CPU2 使用
//    GPIO_setQualificationMode(52, GPIO_QUAL_SYNC);               // 滤波时间



    //---------------------------------------------------------------------------------------------
    //  机型辨识 + 功率辨识
    //---------------------------------------------------------------------------------------------
    GPIO_setPinConfig(GPIO_93_GPIO93);                           //  引脚#
    GPIO_setDirectionMode(93, GPIO_DIR_MODE_IN);                 //  Input
    GPIO_setPadConfig(93, GPIO_PIN_TYPE_PULLUP);                 //  上拉
    GPIO_setMasterCore(93, GPIO_CORE_CPU1);                      //  CPU1使用
    GPIO_setQualificationMode(93, GPIO_QUAL_6SAMPLE);            //  滤波时间

    GPIO_setPinConfig(GPIO_94_GPIO94);                           //  引脚#
    GPIO_setDirectionMode(94, GPIO_DIR_MODE_IN);                 //  Input
    GPIO_setPadConfig(94, GPIO_PIN_TYPE_PULLUP);                 //  上拉
    GPIO_setMasterCore(94, GPIO_CORE_CPU1);                      //  CPU1使用
    GPIO_setQualificationMode(94, GPIO_QUAL_6SAMPLE);            //  滤波时间


    //---------------------------------------------------------------------------------------------
    // MOTA  LED信号(运行+故障)
    //---------------------------------------------------------------------------------------------
    KPX_MOTA_RUN_LED_OFF();
    KPX_MOTA_ERROR_LED_OFF();
    KPX_MOTA_POWER_ON();

//
//    GPIO_setPinConfig(GPIO_32_GPIO32);
//    GPIO_setDirectionMode(32, GPIO_DIR_MODE_OUT);
//    GPIO_setPadConfig(32, GPIO_PIN_TYPE_STD);
//    //GPIO_setMasterCore(32, GPIO_CORE_CPU1);
//    GPIO_setMasterCore(32, GPIO_CORE_CPU1_CLA1);
//    GPIO_setQualificationMode(32, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(GPIO_34_GPIO34);
    GPIO_setDirectionMode(34, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(34, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(34, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(34, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(GPIO_133_GPIO133);
    GPIO_setDirectionMode(133, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(133, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(133, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(133, GPIO_QUAL_SYNC);


    //---------------------------------------------------------------------------------------------
    //  单轴 和 双轴辨识
    //---------------------------------------------------------------------------------------------
    //---------------------------------------------------------------------------------------------
    //  ESC芯片复位引脚
    //---------------------------------------------------------------------------------------------
    GPIO_setPinConfig(GPIO_76_GPIO76);
    GPIO_setDirectionMode(76, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(76, GPIO_PIN_TYPE_STD);
    GPIO_setMasterCore(76, GPIO_CORE_CPU1);

    HWREG( GPIODATA_BASE + GPIO_O_GPCCLEAR )    = 1UL << 12;


    //---------------------------------------------------------------------------------------------
    // ICHaus PVL(NERR,NWRN,PRE)
    //---------------------------------------------------------------------------------------------
//    HWREG( GPIODATA_BASE + GPIO_O_GPACLEAR )   = 1UL << 19;
//
//    GPIO_setPinConfig(GPIO_19_GPIO19);                          //  引脚#
//    GPIO_setDirectionMode(19, GPIO_DIR_MODE_OUT);                //  Input
//    GPIO_setPadConfig(19, GPIO_PIN_TYPE_STD);                   //  上拉
//    GPIO_setMasterCore(19, GPIO_CORE_CPU1);                     //  CPU1使用
//    GPIO_setQualificationMode(19, GPIO_QUAL_SYNC);              //  滤波时间   TODO:PRE配置存在问题


    GPIO_setPinConfig(GPIO_20_GPIO20);                          //  引脚#
    GPIO_setDirectionMode(20, GPIO_DIR_MODE_IN);                //  Input
    GPIO_setPadConfig(20, GPIO_PIN_TYPE_INVERT);                //  上拉
    GPIO_setMasterCore(20, GPIO_CORE_CPU1);                     //  CPU1使用
    GPIO_setQualificationMode(20, GPIO_QUAL_6SAMPLE);           //  滤波时间

    GPIO_setPinConfig(GPIO_24_GPIO24);                          //  引脚#
    GPIO_setDirectionMode(24, GPIO_DIR_MODE_IN);                //  Input
    GPIO_setPadConfig(24, GPIO_PIN_TYPE_INVERT);                //  上拉
    GPIO_setMasterCore(24, GPIO_CORE_CPU1);                     //  CPU1使用
    GPIO_setQualificationMode(24, GPIO_QUAL_6SAMPLE);           //  滤波时间



    //---------------------------------------------------------------------------------------------
    //  STO硬件信号（MCU_CLOSE、STO EN、POWER_CUT）
    //---------------------------------------------------------------------------------------------
//    GPIO_setPinConfig(GPIO_10_GPIO10);                           //  引脚#
//    GPIO_setDirectionMode(10, GPIO_DIR_MODE_IN);                 //  Input
//    GPIO_setPadConfig(10, GPIO_PIN_TYPE_STD);                    //  上拉
//    GPIO_setMasterCore(10, GPIO_CORE_CPU1);                      //  CPU1使用
//    GPIO_setQualificationMode(15, GPIO_QUAL_6SAMPLE);            //  滤波时间
//
//    GPIO_setPinConfig(GPIO_198_GPIO198);                           //  引脚#
//
//    GPIO_setAnalogMode(198, GPIO_ANALOG_DISABLED);
//    GPIO_setDirectionMode(198, GPIO_DIR_MODE_IN);                 //  Input
//    GPIO_setPadConfig(198, GPIO_PIN_TYPE_STD);                    //  上拉
//    GPIO_setMasterCore(198, GPIO_CORE_CPU1);                      //  CPU1使用
//    GPIO_setQualificationMode(198, GPIO_QUAL_6SAMPLE);            //  滤波时间
//
//    GPIO_setPinConfig(GPIO_11_GPIO11);                           //  引脚#
//    GPIO_setDirectionMode(11, GPIO_DIR_MODE_IN);                 //  Input
//    GPIO_setPadConfig(11, GPIO_PIN_TYPE_STD);                    //  上拉
//    GPIO_setMasterCore(11, GPIO_CORE_CPU1);                      //  CPU1使用
//    GPIO_setQualificationMode(11, GPIO_QUAL_6SAMPLE);            //  滤波时间



    return;
}


//*************************************************************************************************
//
// Function: 机型自动选择 A = GPIO38; B = GPIO36;
//  AB = 00 脉冲型号
//  AB = 01 Can
//  AB = 10 EtherCAT
//  AB = 11 PN
//*************************************************************************************************
USHORT DriveModelSel( void )
{
#ifdef CPU1
    USHORT StateA1,StateA2;
    USHORT StateB1,StateB2;
    USHORT State1,State2;

    do
    {
        StateA1 = ( HWREG( GPIODATA_BASE + GPIO_O_GPCDAT ) >> 29 ) & 0x1;     // GPIO93
        StateB1 = ( HWREG( GPIODATA_BASE + GPIO_O_GPCDAT ) >> 30 ) & 0x1;     // GPIO94
        State1  = ( StateB1 << 1 ) + StateA1;

        KlibWaitms( 2 );

        StateA2 = ( HWREG( GPIODATA_BASE + GPIO_O_GPCDAT ) >> 29 ) & 0x1;     // GPIO93
        StateB2 = ( HWREG( GPIODATA_BASE + GPIO_O_GPCDAT ) >> 30 ) & 0x1;     // GPIO94
        State2  = ( StateB2 << 1 ) + StateA2;

    }while( State1 != State2);

    if( State1 >= 3 )
    {
        State1 = 0;
    }

    return State1;

#endif

}


typedef union
{
    struct{
    USHORT    X1        : 1;
    USHORT    X2        : 1;
    USHORT    X3        : 1;
    USHORT    X4        : 1;
    USHORT    Reserved  : 12;
    }f;
    USHORT w;
}XPORTDEFINE;
//*************************************************************************************************
//
// Function:  输入端子信号 X 扫描
//
//*************************************************************************************************
USHORT InputScan( void )
{
    XPORTDEFINE kx;
    kx.w = 0;
#ifdef CPU1
//    kx.f.X1 = ( HWREG( GPIODATA_BASE + GPIO_O_GPADAT ) >> 12 ) & 0x1;     // GPIO12
//    kx.f.X2 = ( HWREG( GPIODATA_BASE + GPIO_O_GPADAT ) >> 13 ) & 0x1;     // GPIO13
//    kx.f.X3 = ( HWREG( GPIODATA_BASE + GPIO_O_GPADAT ) >> 14 ) & 0x1;     // GPIO14
//    if( Kprm.f.AxisNum == 0 )
//    {
//        kx.f.X4 = ( HWREG( GPIODATA_BASE + GPIO_O_GPADAT ) >> 15  ) & 0x1;     // GPIO15
//    }
//    else
//    {
//        kx.f.X4 = 0;
//    }
#endif

    return (kx.w);
}

//*************************************************************************************************
//
// Function:  输出入端子信号 Y 扫描
//
//*************************************************************************************************
void OutputScan( USHORT kx )
{
#ifdef CPU1
//    //---------------------------------------------------------------------------------------------
//    if( ( kx & 0x0001 ) == 0x0000 )                             // Y1 : GPIO49
//    {
//        HWREG( GPIODATA_BASE + GPIO_O_GPBSET )   = 1UL << 17;
//    }
//    else
//    {
//        HWREG( GPIODATA_BASE + GPIO_O_GPBCLEAR ) = 1UL << 17;
//    }
//
//    //---------------------------------------------------------------------------------------------
//    if( ( kx & 0x0002 ) == 0x0000 )                             // Y2 : GPIO52
//    {
//        HWREG( GPIODATA_BASE + GPIO_O_GPBSET )   = 1UL << 20;
//    }
//    else
//    {
//        HWREG( GPIODATA_BASE + GPIO_O_GPBCLEAR ) = 1UL << 20;
//    }

#endif

    return;
}



