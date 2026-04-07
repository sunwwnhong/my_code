//*************************************************************************************************
//
//                           Copyright (C) ××× Electric Corporation
//                                  版权所有 · All right Reserved
//                                          2019 ~
//*************************************************************************************************
//文件名:EtherCAT01_ET1100.c
//创建时间:2019.06.26
//版本说明:V1.0
//功能描述:EtherCAT ESC--38x 相关配置
//*************************************************************************************************
#include "Main.h"

#include "EtherCAT01_2838x.h"

#ifdef ETHERCAT_STACK
#include "EtherCAT00_Main.h"
#endif


void memcpy_fast(void *dst,void *src, uint16_t num_words);

//*************************************************************************************************
//
// ESC_releaseHW
//
//*************************************************************************************************
void ESC_releaseHW(void)
{
    //
    // Intentionally empty - Implementation is left to the end user
    //
}

//*************************************************************************************************
//
// ESC_applicationLayerHandler
//
//*************************************************************************************************
__interrupt void ESC_applicationLayerHandler(void)
{
#ifdef ETHERCAT_STACK
#if AL_EVENT_ENABLED
    //
    // When stack is included and application event enabled, call stack PDI ISR
    //
    PDI_Isr();
#endif  // AL_EVENT_ENABLED
#endif  // ETHERCAT_STACK

    //
    // Acknowledge and clear interrupt in ESCSS
    //

    ESCSS_clearRawInterruptStatus(ESC_SS_BASE, ESCSS_INTR_CLR_IRQ_CLR);

    //
    // Acknowledge this interrupt located in PIE group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}


//*************************************************************************************************
//
// ESC_applicationSync0Handler
//
//*************************************************************************************************
__interrupt void ESC_applicationSync0Handler(void)
{

#if 0
    Sync0_Isr();
    ESCSS_clearRawInterruptStatus(ESC_SS_BASE, ESCSS_INTR_CLR_SYNC0_CLR);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
#else
    uint16_t TempPIEIER;
    TempPIEIER = PieCtrlRegs.PIEIER1.all; // Save PIEIER register for later
    IER |= 0x001;                         // Set global priority by adjusting IER
    IER &= 0x001;
    PieCtrlRegs.PIEIER1.all &= 0x0008;    // Set group priority by adjusting PIEIER1 to allow INT1.4 to interrupt current ISR
    PieCtrlRegs.PIEACK.all = 0xFFFF;      // Enable PIE interrupts
    asm("       NOP");                    // Wait one cycle
    EINT;                                 // Clear INTM to enable interrupts

    Sync0_Isr( );

    /*------------------------------------------------------------------------------------------*/
    /* 示波器通道显示                                                                           */
    /*------------------------------------------------------------------------------------------*/

    AinK.Ctrl_Word = u16ControlWord;
    AinK.Targe_Pos = s32TargetPos;
    AinK.Targe_Pos = s32TargetPos;                                                    //目标位置607A
    AinK.Pulse_PosFB = s32PosActVal;                                                  //电机位置6064
    AinK.Actual_VelRPM  = s32VelActualVal;                                            //电机速度606C
    AinK.Profile_VelRPM = u32ProfileVel;                                              //轮廓速度6081
    AinK.InterPos_CMD   = InterPolDataRecord.u32PosCmd;                               //插补位置60C1
    AinK.Pos_CMDVal     = s32PosDemandVal;                                            //电机位置指令60FC
    AinK.Target_Vel     = s32TargetVel;                                               //目标速度60FF

    DINT;
    PieCtrlRegs.PIEIER1.all = TempPIEIER;
#endif
    ESCSS_clearRawInterruptStatus(ESC_SS_BASE, ESCSS_INTR_CLR_SYNC0_CLR);
}

//*************************************************************************************************
//
// ESC_applicationSync1Handler
//
//*************************************************************************************************
__interrupt void ESC_applicationSync1Handler(void)
{
#ifdef ETHERCAT_STACK
#if DC_SUPPORTED
    //
    // When stack is included and DC is enabled, call stack Sync1 ISR
    //
    Sync1_Isr();
#endif  // DC_SUPPORTED
#endif  // ETHERCAT_STACK

    //
    // Acknowledge and clear interrupt in ESCSS
    //
    ESCSS_clearRawInterruptStatus(ESC_SS_BASE, ESCSS_INTR_CLR_SYNC1_CLR);

    //
    // Acknowledge this interrupt located in PIE group 5
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}


//*************************************************************************************************
//
// ESC_getTimer
//
//*************************************************************************************************
uint32_t ESC_getTimer(void)
{
    //
    // Return 1's compliment of the CPU timer
    //
    return(~((uint32_t)CPUTimer_getTimerCount(CPUTIMER2_BASE)));
}

//*************************************************************************************************
//
// ESC_clearTimer
//
//*************************************************************************************************
void ESC_clearTimer(void)
{
    //
    // Set the timer period count
    //
    CPUTimer_setPeriod(CPUTIMER2_BASE, 0xFFFFFFFFUL);

    //
    // Reload timer with the period count value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER2_BASE);
}

//*************************************************************************************************
//
// ESC_timerIncPerMilliSec
//
//*************************************************************************************************
uint32_t ESC_timerIncPerMilliSec(void)
{
    //
    // Returns value based on core frequency of 200MHz.
    //
    return((uint32_t)200000UL);
}


//*************************************************************************************************
//
// ESC_readBlockISR
//
//*************************************************************************************************
void ESC_readBlockISR(ESCMEM_ADDR *pData, uint16_t address, uint16_t len)
{
    uint16_t i;
    //
    // Create pointer to ESC Address
    //
    const void * escSource = (void *)(ESC_BASE + (uint32_t)(address >> 1U));

    //uint32_t Addr = ESC_BASE + (uint32_t)(address >> 1U);

    //
    // Copy ESC data to buffer. Convert lengths to words.
    //
    memcpy(pData, escSource, (size_t)((len + 1U) >> 1U));

    //memcpy_fast(pData, escSource, (size_t)((len + 1U) >> 1U));

    //for( i = 0; i < (len >> 1);i++)
    //{
    //    pData[ i ] = *(ESCMEM_ADDR*)( Addr + i );
    //}

    //
    // Determine if length (in bytes) is even or odd
    // (No action on even)
    //
    if((len & 0x1U) == 0x1U)
    {
        //
        // Clear extra byte in buffer
        //
        i = (len - 1U) >> 1U;
        pData[i] = (pData[i] & ESC_M_LSB);
    }
}

//*************************************************************************************************
//
// ESC_readBlock
//
//*************************************************************************************************
void ESC_readBlock(ESCMEM_ADDR *pData, uint16_t address, uint16_t len)
{
    //
    // Disables interrupts
    //
    //DINT;

    //
    // Perform copy of ESC data to buffer
    //
    ESC_readBlockISR(pData, address, len);

    //
    // Enable interrupts
    //
    //EINT;
}

//*************************************************************************************************
//
// ESC_readDWordISR
//
//*************************************************************************************************
uint32_t ESC_readDWordISR(uint16_t address)
{
    //
    // Read 32-bit address from ESC memory
    //
    return(HWREG(ESC_BASE + (address >> 1U)));
}

//*************************************************************************************************
//
// ESC_readDWord
//
//*************************************************************************************************
uint32_t ESC_readDWord(uint16_t address)
{
    uint32_t dWordValue;

    //
    // Disables interrupts
    //
    //DINT;

    //
    // Read 32-bit address from ESC memory
    //
    dWordValue = ESC_readDWordISR(address);

    //
    // Enable interrupts
    //
    //EINT;

    //
    // Return value
    //
    return(dWordValue);
}

//*************************************************************************************************
//
// ESC_readWordISR
//
//*************************************************************************************************
uint16_t ESC_readWordISR(uint16_t address)
{
    //
    // Read 16-bit address from ESC memory
    //
    return(HWREGH(ESC_BASE + (address >> 1U)));
}

//*************************************************************************************************
//
// ESC_readWord
//
//*************************************************************************************************
uint16_t ESC_readWord(uint16_t address)
{
    uint16_t wordValue;

    //
    // Disables interrupts
    //
    //DINT;

    //
    // Read 16-bit address from ESC memory
    //
    wordValue = ESC_readWordISR(address);

    //
    // Enable interrupts
    //
    //EINT;

    //
    // Return value
    //
    return(wordValue);
}

//*************************************************************************************************
//
// ESC_writeBlockISR
//
//*************************************************************************************************
void ESC_writeBlockISR(ESCMEM_ADDR *pData, uint16_t address, uint16_t len)
{
    uint16_t wordValue;

    //
    // Create pointer to ESC Address
    //
    void * escDest = (void *)(ESC_BASE + (uint32_t)(address >> 1U));

    //
    // Determine if length (in bytes) is even or odd
    //
    if((len & 0x1U) == 0x1U)
    {
        //
        // Odd Length
        //

        //
        // Copy even bytes of buffer data to ESC memory.
        // Convert length to words.
        //
        memcpy(escDest, pData, (size_t)((len - 1U) >> 1U));

        //
        // Read last 16-bit word
        //
        wordValue = ESC_readWordISR(address + (len - 1U));

        //
        // Modify word data and set new data
        //
        wordValue &= ESC_M_MSB;
        wordValue |= (pData[((len - 1U) >> 1U)] & ESC_M_LSB);

        //
        // Write modified value to ESC destination
        //
        ESC_writeWordISR(wordValue, (address + (len - 1U)));
    }
    else
    {
        //
        // Even Length
        //

        //
        // Copy buffer data to ESC memory. Convert length to words.
        //
        memcpy(escDest, pData, (size_t)(len >> 1U));
    }
}

//*************************************************************************************************
//
// ESC_writeBlock
//
//*************************************************************************************************
void ESC_writeBlock(ESCMEM_ADDR *pData, uint16_t address, uint16_t len)
{
    //
    // Disables interrupts
    //
    //DINT;

    //
    // Write data buffer into ESC memory
    //
    ESC_writeBlockISR(pData, address, len);

    //
    // Enable interrupts
    //
    //EINT;
}

//*************************************************************************************************
//
// ESC_writeDWordISR
//
//*************************************************************************************************
void ESC_writeDWordISR(uint32_t dWordValue, uint16_t address)
{
    //
    // Write two 16-bit words to ESC memory
    //
    HWREG(ESC_BASE + (address >> 1U)) = dWordValue;
}

//*************************************************************************************************
//
// ESC_writeDWord
//
//*************************************************************************************************
void ESC_writeDWord(uint32_t dWordValue, uint16_t address)
{
    //
    // Disables interrupts
    //
    //DINT;

    //
    // Write two 16-words into ESC memory
    //
    ESC_writeDWordISR(dWordValue, address);

    //
    // Enable interrupts
    //
    //EINT;
}

//*************************************************************************************************
//
// ESC_writeWordISR
//
//*************************************************************************************************
void ESC_writeWordISR(uint16_t wordValue, uint16_t address)
{
    //
    // Write 16-bit word into ESC memory
    //
    HWREGH(ESC_BASE + (address >> 1U)) = wordValue;
}

//*************************************************************************************************
//
// ESC_writeWord
//
//*************************************************************************************************
void ESC_writeWord(uint16_t wordValue, uint16_t address)
{
    //
    // Disables interrupts
    //
    //DINT;

    //
    // Write one 16-word into ESC memory
    //
    ESC_writeWordISR(wordValue, address);

    //
    // Enable interrupts
    //
    //EINT;
}

//*************************************************************************************************
//
// ESC_setLed
//
//*************************************************************************************************
void ESC_setLed(uint16_t runLed, uint16_t errLed)
{
    //
    // Set/Clear Run LED
    //
    GPIO_writePin(ESC_RUN_LED_GPIO, (uint32_t)(runLed));

    //
    // Set/Clear Error LED
    //
    GPIO_writePin(ESC_ERR_LED_GPIO, (uint32_t)(errLed));
}





//*************************************************************************************************
//
// ESC_loadedCheckEEPROM
//
//*************************************************************************************************
uint16_t ESC_loadedCheckEEPROM(void)
{
    uint16_t status;

    //
    // Get ESC DL Status register
    //
    status = ESC_readWordISR(ESC_O_DL_STATUS);

    //
    // Check if EEPROM is loaded
    //
    if((status & ESC_DL_STATUS_EEPROMLOAD_M) == ESC_DL_STATUS_EEPROMLOAD_M)
    {
        //
        // Get ESC EEPROM Status register
        //
        status = ESC_readWordISR(ESC_O_EEPROM_STATUS);

        //
        // Check if EEPROM is loaded and device information is okay
        //
        if((status & ESC_EEPROM_STATUS_EEPROMLOAD_M) == ESC_EEPROM_SUCCESS)
        {
            return(ESC_EEPROM_SUCCESS);
        }
        else
        {
            return(ESC_EEPROM_LOAD_ERROR);
        }
    }
    else
    {
        //
        // DL Status indicated EEPROM is not loaded
        //
        return(ESC_EEPROM_NOT_LOADED);
    }
}

//*************************************************************************************************
//
// ESC_resetESC
//
//*************************************************************************************************
void ESC_resetESC(void)
{
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_ECAT);
}

//*************************************************************************************************
//
// ESC_holdESCInReset
//
//*************************************************************************************************
void ESC_holdESCInReset(void)
{
    //
    // Put ESC in reset
    //
    EALLOW;
    HWREGH(DEVCFG_BASE + SYSCTL_O_SOFTPRES23) |= SYSCTL_SOFTPRES23_ETHERCAT;
    EDIS;
}

//*************************************************************************************************
//
// ESC_releaseESCReset
//
//*************************************************************************************************
void ESC_releaseESCReset(void)
{
    //
    // Release from reset
    //
    EALLOW;
    HWREGH(DEVCFG_BASE + SYSCTL_O_SOFTPRES23) &= (~SYSCTL_SOFTPRES23_ETHERCAT);
    EDIS;
}


//*************************************************************************************************
//
// EtherCAT 引脚和时钟初始化
//
//*************************************************************************************************
void EtherCAT_GPIOInit( void )
{
    //
    // Setup AUX Clock for ECAT and CM
    // Configured to 500MHz raw ((25 * 20 IMULT) /1)
    //
#if 0
    SysCtl_setAuxClock(SYSCTL_AUXPLL_ENABLE | SYSCTL_AUXPLL_OSCSRC_XTAL |
                       SYSCTL_AUXPLL_IMULT(20) | SYSCTL_AUXPLL_FMULT_0 |
                       SYSCTL_AUXPLL_DIV_1);
#endif
    //
    // Configure GPIOs for ECAT
    //

    //
    // PHY CLK
    //
#if 1
    GPIO_setPinConfig(GPIO_48_ESC_PHY_CLK);
    //GPIO_setPadConfig(154, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPadConfig(48, GPIO_PIN_TYPE_STD);
#endif
    //
    // PHY Reset
    //
    GPIO_setPinConfig(GPIO_76_ESC_PHY_RESETN);
    //GPIO_setQualificationMode(76,GPIO_QUAL_ASYNC);
    GPIO_setPadConfig(76, GPIO_PIN_TYPE_STD); //20230831 Add
    KlibWaitms( 50 );

    //
    // I2C for EEPROM
    //
    GPIO_setPinConfig(GPIO_40_ESC_I2C_SDA);
    GPIO_setQualificationMode(40,GPIO_QUAL_ASYNC);
    GPIO_setPadConfig(40,GPIO_PIN_TYPE_PULLUP);

    GPIO_setPinConfig(GPIO_30_ESC_I2C_SCL);
    GPIO_setQualificationMode(30,GPIO_QUAL_ASYNC);
    GPIO_setPadConfig(30,GPIO_PIN_TYPE_PULLUP);

    //
    // P0 TX and RX DATA
    //
    GPIO_setPinConfig(GPIO_87_ESC_TX0_DATA0);
    GPIO_setQualificationMode(87,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_88_ESC_TX0_DATA1);
    GPIO_setQualificationMode(88,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_89_ESC_TX0_DATA2);
    GPIO_setQualificationMode(89,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_90_ESC_TX0_DATA3);
    GPIO_setQualificationMode(90,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_80_ESC_RX0_DATA0);
    GPIO_setQualificationMode(80,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_28_ESC_RX0_DATA1);
    GPIO_setQualificationMode(28,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_29_ESC_RX0_DATA2);
    GPIO_setQualificationMode(29,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_83_ESC_RX0_DATA3);
    GPIO_setQualificationMode(83,GPIO_QUAL_ASYNC);

    //
    // P0 TX Enable, RX DV, RX ERR
    //
    GPIO_setPinConfig(GPIO_56_ESC_TX0_ENA);
    GPIO_setQualificationMode(56,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_78_ESC_RX0_DV);
    GPIO_setQualificationMode(78,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_26_ESC_RX0_ERR);
    GPIO_setPadConfig(26,GPIO_PIN_TYPE_STD);

    //
    // P0 TX and RX Clk
    //
    GPIO_setPinConfig(GPIO_85_ESC_TX0_CLK);
    GPIO_setQualificationMode(85,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_77_ESC_RX0_CLK);
    GPIO_setQualificationMode(77,GPIO_QUAL_ASYNC);

    //
    // P0 Linkstatus and Link Active LED
    //
    GPIO_setPinConfig(GPIO_86_ESC_PHY0_LINKSTATUS);
    GPIO_setPadConfig(86, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_58_ESC_LED_LINK0_ACTIVE);
    GPIO_setQualificationMode(58, GPIO_QUAL_ASYNC);
    GPIO_setPadConfig(58, GPIO_PIN_TYPE_INVERT);
//    GPIO_setPinConfig(GPIO_86_ESC_PHY0_LINKSTATUS);
//    GPIO_setPadConfig(86,GPIO_PIN_TYPE_INVERT);
//    GPIO_setQualificationMode(86,GPIO_QUAL_ASYNC);
//
//    GPIO_setPinConfig(GPIO_58_ESC_LED_LINK0_ACTIVE);
//    GPIO_setQualificationMode(58, GPIO_QUAL_ASYNC);

    //
    // P0+P1 MDIO CLK and Data
    //
    GPIO_setPinConfig(GPIO_62_ESC_MDIO_CLK);
    GPIO_setQualificationMode(62,GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(GPIO_27_ESC_MDIO_DATA);
    GPIO_setQualificationMode(27,GPIO_QUAL_ASYNC);

    //
    // P1 TX and RX DATA
    //
    GPIO_setPinConfig(GPIO_22_ESC_TX1_DATA0);
    GPIO_setQualificationMode(22,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_74_ESC_TX1_DATA1);
    GPIO_setQualificationMode(74,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_73_ESC_TX1_DATA2);
    GPIO_setQualificationMode(73,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_19_ESC_TX1_DATA3);
    GPIO_setQualificationMode(19,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_63_ESC_RX1_DATA0);
    GPIO_setQualificationMode(63,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_64_ESC_RX1_DATA1);
    GPIO_setQualificationMode(64,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_65_ESC_RX1_DATA2);
    GPIO_setQualificationMode(65,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_66_ESC_RX1_DATA3);
    GPIO_setQualificationMode(66,GPIO_QUAL_ASYNC);

    //
    // P1 TX Enable, RX DV, RX ERR
    //
    GPIO_setPinConfig(GPIO_45_ESC_TX1_ENA);
    GPIO_setQualificationMode(45,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_70_ESC_RX1_DV);
    GPIO_setQualificationMode(70,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_71_ESC_RX1_ERR);
    GPIO_setPadConfig(71,GPIO_PIN_TYPE_STD);

    //
    // P1 TX and RX Clk
    //
    GPIO_setPinConfig(GPIO_44_ESC_TX1_CLK);
    GPIO_setQualificationMode(44,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_69_ESC_RX1_CLK);
    GPIO_setQualificationMode(69,GPIO_QUAL_ASYNC);

    //
    // P1 Linkstatus and Link Active LED
    //

    GPIO_setPinConfig(GPIO_68_ESC_PHY1_LINKSTATUS);
    GPIO_setPadConfig(68, GPIO_PIN_TYPE_STD);

    GPIO_setPinConfig(GPIO_59_ESC_LED_LINK1_ACTIVE);

    GPIO_setQualificationMode(59, GPIO_QUAL_ASYNC);
    GPIO_setPadConfig(59, GPIO_PIN_TYPE_INVERT);
//    GPIO_setPinConfig(GPIO_68_ESC_PHY1_LINKSTATUS);
//    GPIO_setPadConfig(68,GPIO_PIN_TYPE_INVERT);
//    GPIO_setQualificationMode(68,GPIO_QUAL_ASYNC);
//
//    GPIO_setPinConfig(GPIO_59_ESC_LED_LINK1_ACTIVE);
//    GPIO_setQualificationMode(59, GPIO_QUAL_ASYNC);

    //
    // Sync and Latch
    //
    // Note these GPIOs aren't required for EtherCAT
    // operation and are configured here for demonstration,
    // analysis, and debug purposes
    //
    //GPIO_setPinConfig(GPIO_125_ESC_LATCH0);
    //GPIO_setPinConfig(GPIO_126_ESC_LATCH1);

//    GPIO_setPinConfig(GPIO_127_ESC_SYNC0);
//    GPIO_setPinConfig(GPIO_128_ESC_SYNC1);
//    GPIO_setDirectionMode(127, GPIO_DIR_MODE_OUT);
//    GPIO_setDirectionMode(128, GPIO_DIR_MODE_OUT);

    //
    // Set GPIO direction for ECAT RUN/ERR LEDs
    //
//    GPIO_setDirectionMode(146U, GPIO_DIR_MODE_OUT);
//    GPIO_setPadConfig(146U, GPIO_PIN_TYPE_STD);
//    GPIO_setDirectionMode(145U, GPIO_DIR_MODE_OUT);
//    GPIO_setPadConfig(145U, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_33_ESC_LED_ERR);
    GPIO_setQualificationMode(33,GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(GPIO_61_ESC_LED_RUN);
    GPIO_setQualificationMode(61,GPIO_QUAL_ASYNC);
}

//*************************************************************************************************
//
// EtherCAT 初始化引脚初始化
//
//*************************************************************************************************
uint16_t ESC_initHW( void )
{
    //
    // Set application-specific timeout for waiting for EEPROM to load
    // and one for waiting for memory initialization
    // (End user can adjust as needed)
    //
    uint16_t eepromTimeOut = 0x1500U;
    uint16_t memoryTimeOut = 0x500U;
    //
    // EtherCAT 引脚初始化
    //
    EtherCAT_GPIOInit( );

    //
    // Register EtherCAT Interrupt Handlers
    //
    Interrupt_register(INT_ECAT,        &ESC_applicationLayerHandler);
    Interrupt_register(INT_ECATSYNC0,   &ESC_applicationSync0Handler);
//    Interrupt_register(INT_ECATSYNC1,   &ESC_applicationSync1Handler);

    //
    // Configure and Start timer
    //
    CPUTimer_setPeriod(CPUTIMER2_BASE, 0xFFFFFFFFUL);
    CPUTimer_setPreScaler(CPUTIMER2_BASE, 0U);
    CPUTimer_startTimer(CPUTIMER2_BASE);

#if 0
    // Aux = 500MHz and use /5 to get 100MHz for ECAT IP
    // (There is a built in /4 to get 25MHz for PHY when using internal clocking for PHY)

    SysCtl_setECatClk(SYSCTL_ECATCLKOUT_DIV_5, SYSCTL_SOURCE_AUXPLL,ESC_USE_INT_PHY_CLK);
#else
    // SysClk = 200MHz and use /2 to get 100MHz for ECAT IP
    // (There is a built in /4 to get 25MHz for PHY when using internal clocking for PHY)
    //SysCtl_setECatClk(SYSCTL_ECATCLKOUT_DIV_2, SYSCTL_SOURCE_SYSPLL,ESC_USE_INT_PHY_CLK);
    SysCtl_setECatClk(SYSCTL_ECATCLKOUT_DIV_2, SYSCTL_SOURCE_SYSPLL,ESC_USE_INT_PHY_CLK);

#endif

    KlibWaitms( 20 );
    //
    // Configure EEPROM Size for 16K bits or less
    //
    ESCSS_configureEEPROMSize(ESC_SS_CONFIG_BASE, ESCSS_GREATER_THAN_16K);

    //
    // Reset ESC
    //
    ESC_resetESC();

    //
    // Initialize ESCSS Memory
    //
    ESCSS_initMemory(ESC_SS_BASE);

    //
    // Wait for ESCSS memory initialization to complete
    //
    if(ESCSS_getMemoryInitDoneStatusBlocking(ESC_SS_BASE, memoryTimeOut) != ESCSS_API_SUCCESS)
    {
        return(ESC_HW_INIT_FAIL);
    }

    //
    // Wait (with time out) for EEPROM to be loaded
    //
    while(ESC_loadedCheckEEPROM() != ESC_EEPROM_SUCCESS)
    {
        eepromTimeOut--;

        //
        // On time out, return fail
        //
        if(eepromTimeOut == 0U)
        {
            return(ESC_HW_INIT_FAIL);
        }
    }

    //
    // Initialize AL Event Mask to zero to prevent ESC interrupts until
    // set during stack state transition to SAFEOP
    //

    ESC_writeDWordISR(0UL,  ESC_O_AL_EVENTMASK );

    //
    // Enable ECAT/PDI, Sync0, and Sync1 interrupts in ESCSS
    //
#if 0
    ESCSS_setMaskedInterruptStatus(ESC_SS_BASE,
                                   (ESCSS_INTR_MASK_IRQ_MASK |
                                    ESCSS_INTR_MASK_SYNC0_MASK |
                                    ESCSS_INTR_MASK_SYNC1_MASK));
#else
    HWREGH(ESC_SS_BASE + ESCSS_O_INTR_MASK) |= (ESCSS_INTR_MASK_IRQ_MASK|ESCSS_INTR_MASK_SYNC0_MASK);
#endif


    //
    // Connect ESCSS Sync0/1 signals to respective interrupts in PIE
    //
    ESCSS_configureSync0Connections(ESC_SS_BASE, ESCSS_SYNC0_CONFIG_C28X_PIE_EN,ESCSS_VALID_KEY_VALUE);
    ESCSS_configureSync1Connections(ESC_SS_BASE, ESCSS_SYNC1_CONFIG_C28X_PIE_EN,ESCSS_VALID_KEY_VALUE);

    //
    // Enable ECAT/PDI, Sync0, and Sync1 interrupts in CPU
    //
    ESCSS_clearRawInterruptStatus(ESC_SS_BASE, ESCSS_INTR_CLR_IRQ_CLR);
    ESCSS_clearRawInterruptStatus(ESC_SS_BASE, ESCSS_INTR_CLR_SYNC0_CLR);
    //Interrupt_enable(INT_ECAT);
    Interrupt_enable(INT_ECATSYNC0);
    //Interrupt_enable(INT_ECATSYNC1);
    return(ESC_HW_INIT_SUCCESS);
}


//*************************************************************************************************
//
// ESC 中断开启
//
//*************************************************************************************************
void ESCINT_Start( void )
{



}

//
// End of File
//
