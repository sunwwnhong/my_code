MEMORY
{
   BEGIN            : origin = 0x088000, length = 0x000002  // Update the codestart location as needed

   BOOT_RSVD        : origin = 0x000002, length = 0x0001AF     /* Part of M0, BOOT rom will use this for stack */
   RAMM0            : origin = 0x0001B1, length = 0x00024F
   RAMM1            : origin = 0x000400, length = 0x000400

   RAMD0            : origin = 0x00C000, length = 0x002000
   RAMD1            : origin = 0x00E000, length = 0x002000
   RAMD2            : origin = 0x01A000, length = 0x002000  // Can be mapped to either CPU1 or CPU2. When configured to CPU2, use the address 0x8000. User should comment/uncomment based on core selection
   RAMD3            : origin = 0x01C000, length = 0x002000  // Can be mapped to either CPU1 or CPU2. When configured to CPU2, use the address 0xA000. User should comment/uncomment based on core selection
   RAMD4            : origin = 0x01E000, length = 0x002000  // Can be mapped to either CPU1 or CPU2. When configured to CPU2, use the address 0xC000. User should comment/uncomment based on core selection
   RAMD5            : origin = 0x020000, length = 0x002000  // Can be mapped to either CPU1 or CPU2. When configured to CPU2, use the address 0xE000. User should comment/uncomment based on core selection

   RAMLS0_1           : origin = 0x008000, length = 0x001000
  // RAMLS1           : origin = 0x008800, length = 0x000800
   RAMLS2           : origin = 0x009000, length = 0x000800
   RAMLS3_4           : origin = 0x009800, length = 0x001000
   //RAMLS4           : origin = 0x00A000, length = 0x000800
   RAMLS5_6           : origin = 0x00A800, length = 0x001000
   //RAMLS6           : origin = 0x00B000, length = 0x000800
   RAMLS7           : origin = 0x00B800, length = 0x000800
   RAMLS8           : origin = 0x022000, length = 0x002000  // When configured as CLA program use the address 0x4000
   RAMLS9           : origin = 0x024000, length = 0x002000  // When configured as CLA program use the address 0x6000

   // RAMLS8_CLA    : origin = 0x004000, length = 0x002000  // Use only if configured as CLA program memory
   // RAMLS9_CLA    : origin = 0x006000, length = 0x002000  // Use only if configured as CLA program memory

   RAMGS0           : origin = 0x010000, length = 0x002000
   RAMGS1           : origin = 0x012000, length = 0x002000
   RAMGS2_4           : origin = 0x014000, length = 0x006000
 //  RAMGS3           : origin = 0x016000, length = 0x002000
 //  RAMGS4           : origin = 0x018000, length = 0x002000

   /* Flash Banks (128 sectors each) */
   FLASH_BANK1_3     : origin = 0x088002, length = 0x56FFE  // Can be mapped to either CPU1 or CPU2. User should comment/uncomment based on core selection
  // FLASH_BANK2       : origin = 0x0D0000, length = 0x10000  // Can be mapped to either CPU1 or CPU2. User should comment/uncomment based on core selection
  // FLASH_BANK2     : origin = 0x0C0000, length = 0x20000  // Can be mapped to either CPU1 or CPU2. User should comment/uncomment based on core selection
  // FLASH_BANK3     : origin = 0x0E0000, length = 0x20000  // Can be mapped to either CPU1 or CPU2. User should comment/uncomment based on core selection
  // FLASH_BANK4      : origin = 0x0E0000, length = 0x1FFF8  // Can be mapped to either CPU1 or CPU2. User should comment/uncomment based on core selection
   FLASH_BANK4     : origin = 0x00DF000, length = 0x00FF8  // Can be mapped to either CPU1 or CPU2. User should comment/uncomment based on core selection
   FLASHCHECK		: origin = 0x0DFFF8, length = 0x000008  /* on-chip Flash */


   CPU1TOCPU2RAM    : origin = 0x03A000, length = 0x000400
   CPU2TOCPU1RAM    : origin = 0x03B000, length = 0x000400

   CLATOCPURAM      : origin = 0x001480,   length = 0x000080
   CPUTOCLARAM      : origin = 0x001500,   length = 0x000080
   CLATODMARAM      : origin = 0x001680,   length = 0x000080
   DMATOCLARAM      : origin = 0x001700,   length = 0x000080

   CANA_MSG_RAM     : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000, length = 0x000800
   RESET            : origin = 0x3FFFC0, length = 0x000002
}


SECTIONS
{
   codestart        : > BEGIN
   .text            : > FLASH_BANK1_3, ALIGN(8)
   .cinit           : > FLASH_BANK1_3, ALIGN(8)
   .switch          : > FLASH_BANK1_3, ALIGN(8)
   .reset           : > RESET, TYPE = DSECT /* not used, */

   .stack           : > RAMD0
#if defined(__TI_EABI__)
   .bss             : > RAMGS2_4
   .bss:output      : > RAMLS3_4
   .init_array      : > FLASH_BANK1_3, ALIGN(8)
   .const           : > FLASH_BANK1_3, ALIGN(8)
   .data            : > RAMLS8
   .sysmem          : > RAMLS3_4
#else
   .pinit           : > FLASH_BANK1_3, ALIGN(8)
   .ebss            : >> RAMLS5 | RAMLS6 //!!!
   .econst          : > FLASH_BANK1_3, ALIGN(8)
   .esysmem         : > RAMLS5
#endif




   ramgs0 : > RAMGS0, type=NOINIT
   ramgs1 : > RAMGS1, type=NOINIT

   MSGRAM_CPU1_TO_CPU2 > CPU1TOCPU2RAM, type=NOINIT
   MSGRAM_CPU2_TO_CPU1 > CPU2TOCPU1RAM, type=NOINIT

//   dclfuncs 			: > FLASH_BANK4, ALIGN(8)

//   FLASHCHECK_ADDR		: > FLASHCHECK

   #if defined(__TI_EABI__)
       .TI.ramfunc : {} LOAD = FLASH_BANK1_3,
                        RUN = RAMLS3_4,
                        LOAD_START(RamfuncsLoadStart),
                        LOAD_SIZE(RamfuncsLoadSize),
                        LOAD_END(RamfuncsLoadEnd),
                        RUN_START(RamfuncsRunStart),
                        RUN_SIZE(RamfuncsRunSize),
                        RUN_END(RamfuncsRunEnd),
                        ALIGN(8)
   #else
       .TI.ramfunc : {} LOAD = FLASH_BANK1_3,
                        RUN = RAMLS3_4,
                        LOAD_START(_RamfuncsLoadStart),
                        LOAD_SIZE(_RamfuncsLoadSize),
                        LOAD_END(_RamfuncsLoadEnd),
                        RUN_START(_RamfuncsRunStart),
                        RUN_SIZE(_RamfuncsRunSize),
                        RUN_END(_RamfuncsRunEnd),
                        ALIGN(8)
   #endif

/* CLA specific sections */

#if defined(__TI_EABI__)
    /* CLA specific sections */
    Cla1Prog        : LOAD = FLASH_BANK4,
                      RUN = RAMLS5_6,
                      LOAD_START(Cla1ProgLoadStart),
                      RUN_START(Cla1ProgRunStart),
                      LOAD_SIZE(Cla1ProgLoadSize),
                      ALIGN(4)
#else
    /* CLA specific sections */
    Cla1Prog        : LOAD = FLASH_BANK4,
                      RUN = RAMLS5_6,
                      LOAD_START(_Cla1ProgLoadStart),
                      RUN_START(_Cla1ProgRunStart),
                      LOAD_SIZE(_Cla1ProgLoadSize),
                      ALIGN(4)
#endif

   Cla1ToCpuMsgRAM  : > CLATOCPURAM, type=NOINIT
   CpuToCla1MsgRAM  : > CPUTOCLARAM, type=NOINIT

   .scratchpad      : > RAMLS7		//CLA临时变量空间
   .bss_cla         : > RAMLS7		//CLA全局变量

   Cla1DataRam      : > RAMLS7		//CLA数据RAM

#if defined(__TI_EABI__)
   .const_cla      : LOAD = FLASH_BANK1_3,
                      RUN = RAMLS7,
                      RUN_START(Cla1ConstRunStart),
                      LOAD_START(Cla1ConstLoadStart),
                      LOAD_SIZE(Cla1ConstLoadSize),
                      ALIGN(4)
#else
   .const_cla      : LOAD = FLASH_BANK1_3,
                      RUN = RAMLS7,
                      RUN_START(_Cla1ConstRunStart),
                      LOAD_START(_Cla1ConstLoadStart),
                      LOAD_SIZE(_Cla1ConstLoadSize),
                      ALIGN(4)
#endif
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
