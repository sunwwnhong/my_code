;// TI File $Revision: /main/1 $
;// Checkin $Date: August 18, 2006   13:45:55 $
;//###########################################################################
;//
;// FILE:  DSP2833x_CodeStartBranch.asm	
;//
;// TITLE: Branch for redirecting code execution after boot. 
;//
;// For these examples, code_start is the first code that is executed after
;// exiting the boot ROM code. 
;//
;// The codestart section in the linker cmd file is used to physically place
;// this code at the correct memory location.  This section should be placed 
;// at the location the BOOT ROM will re-direct the code to.  For example, 
;// for boot to FLASH this code will be located at 0x3f7ff6. 
;//
;// In addition, the example DSP2833x projects are setup such that the codegen
;// entry point is also set to the code_start label.  This is done by linker 
;// option -e in the project build options.  When the debugger loads the code,
;// it will automatically set the PC to the "entry point" address indicated by
;// the -e linker option.  In this case the debugger is simply assigning the PC, 
;// it is not the same as a full reset of the device. 
;// 
;// The compiler may warn that the entry point for the project is other then
;//  _c_init00.  _c_init00 is the C environment setup and is run before 
;// main() is entered. The code_start code will re-direct the execution 
;// to _c_init00 and thus there is no worry and this warning can be ignored. 
;// 
;//###########################################################################
;// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
;// $Release Date: August 4, 2009 $
;//###########################################################################


***********************************************************************

WD_DISABLE	.set	1		;set to 1 to disable WD, else set to 0

    .ref _c_int00
    .ref _InitClock
    .global code_start

    
    .if !$defined(DEBUG_IN_RAM) ; 程序在FLASH中
    
RAM_START       .set  8000H
;RAM_LEN         .set  6000H    ; 28232
RAM_LEN         .set  8000H     ; 28335

    .else                       ; 程序在RAM中
    
RAM_START       .set  0CA00H
;RAM_LEN         .set  2800H    ; 28232
RAM_LEN         .set  3600H     ; 28335

    .endif


***********************************************************************
* Function: codestart section
*
* Description: Branch to code starting point
***********************************************************************

    .sect "codestart"

code_start:
    .if WD_DISABLE == 1
        LB wd_disable       ;Branch to watchdog disable code
    .else
        LB _c_int00         ;Branch to start of boot.asm in RTS library
    .endif

;end codestart section


***********************************************************************
* Function: wd_disable
*
* Description: Disables the watchdog timer
***********************************************************************
    .if WD_DISABLE == 1

    .text
wd_disable:
    SETC OBJMODE        ;Set OBJMODE for 28x object code
    EALLOW              ;Enable EALLOW protected register access
    MOVZ DP, #7029h>>6  ;Set data page for WDCR register
    MOV @7029h, #0068h  ;Set WDDIS bit in WDCR to disable WD
    EDIS                ;Disable EALLOW protected register access

    LCR _InitClock      ; 初始化时钟

    MOV     ACC,    #0000 
    MOVL    XAR5,   #0000H      
    MOVL    XAR4,   #(800H-1)	;Clear M0,M1
    RPT     @AR4
    || MOV  *XAR5++, ACC

    MOVL    XAR5,   #RAM_START     
    MOVL    XAR4,   #(RAM_LEN-1)	;Clear DataRAM
    RPT     @AR4
    || MOV  *XAR5++, ACC
    
    LB _c_int00         ;Branch to start of boot.asm in RTS library

    .endif

;end wd_disable



	.end
	
;//===========================================================================
;// End of file.
;//===========================================================================
