/*
 * App04_GPIO.h
 *
 *  Created on: 2022Äê7ÔÂ12ÈÕ
 *      Author: zhuxc
 */

#ifndef App04_GPIO_H
#define App04_GPIO_H


#define MotA_PWM_Lock()             HWREG( GPIODATA_BASE + GPIO_O_GPASET )      = 1UL << 6;     //GPIO6
#define MotA_PWM_UnLock()           HWREG( GPIODATA_BASE + GPIO_O_GPACLEAR )    = 1UL << 6;



#define KPX_BRAKE_ON()              HWREG( GPIODATA_BASE + GPIO_O_GPCSET )      = 1UL << 11;    //GPIO75
#define KPX_BRAKE_OFF()             HWREG( GPIODATA_BASE + GPIO_O_GPCCLEAR )    = 1UL << 11;

#define KPX_MOTA_BRAKE_ON()         HWREG( GPIODATA_BASE + GPIO_O_GPCSET )      = 1UL << 15;    //GPIO79
#define KPX_MOTA_BRAKE_OFF()        HWREG( GPIODATA_BASE + GPIO_O_GPCCLEAR )    = 1UL << 15;



#define KPX_MOTA_RUN_LED_OFF()      HWREG( GPIODATA_BASE + GPIO_O_GPBCLEAR )    = 1UL ;         //GPIO32
#define KPX_MOTA_RUN_LED_ON()       HWREG( GPIODATA_BASE + GPIO_O_GPBSET )      = 1UL ;
#define KPX_MOTA_RUN_LED_TOG()      HWREG( GPIODATA_BASE + GPIO_O_GPBTOGGLE )   = 1UL ;
#define KPX_MOTA_POWER_OFF()        HWREG( GPIODATA_BASE + GPIO_O_GPECLEAR )    = 1UL << 5;     //GPIO133
#define KPX_MOTA_POWER_ON()         HWREG( GPIODATA_BASE + GPIO_O_GPESET )      = 1UL << 5;
#define KPX_MOTA_ERROR_LED_OFF()    HWREG( GPIODATA_BASE + GPIO_O_GPBCLEAR )    = 1UL << 2;     //GPIO34
#define KPX_MOTA_ERROR_LED_ON()     HWREG( GPIODATA_BASE + GPIO_O_GPBSET )      = 1UL << 2;



#define TEST4_H HWREG( GPIODATA_BASE + GPIO_O_GPASET )      = 1UL << 15;
#define TEST4_L HWREG( GPIODATA_BASE + GPIO_O_GPACLEAR )    = 1UL << 15;
#define TEST5_H HWREG( GPIODATA_BASE + GPIO_O_GPBSET )      = 1UL << 5;
#define TEST5_L HWREG( GPIODATA_BASE + GPIO_O_GPBCLEAR )    = 1UL << 5;
#define TEST5_TG HWREG( GPIODATA_BASE + GPIO_O_GPBTOGGLE )  = 1UL << 5;

#define TEST6_H HWREG( GPIODATA_BASE + GPIO_O_GPDSET )      = 1UL << 24;
#define TEST6_L HWREG( GPIODATA_BASE + GPIO_O_GPDCLEAR )    = 1UL << 24;
#define TEST6_TG HWREG( GPIODATA_BASE + GPIO_O_GPDTOGGLE )  = 1UL << 24;


#define TEST145_H HWREG( GPIODATA_BASE + GPIO_O_GPCSET )      = 1UL << 30;
#define TEST145_L HWREG( GPIODATA_BASE + GPIO_O_GPCCLEAR )    = 1UL << 30;
#define TEST146_H HWREG( GPIODATA_BASE + GPIO_O_GPCSET )      = 1UL << 31;
#define TEST146_L HWREG( GPIODATA_BASE + GPIO_O_GPCCLEAR )    = 1UL << 31;
#define TEST147_H HWREG( GPIODATA_BASE + GPIO_O_GPASET )      = 1UL << 17;
#define TEST147_L HWREG( GPIODATA_BASE + GPIO_O_GPACLEAR )    = 1UL << 17;
//-------------------------------------------------------------------------------------------------


#ifdef CPU1
#define X3_Status   (( HWREG( GPIODATA_BASE + GPIO_O_GPADAT ) >> 14 ) & 0x1)            //GPIO14
#define X4_Status   (( HWREG( GPIODATA_BASE + GPIO_O_GPADAT ) >> 15 ) & 0x1)            //GPIO15
#define STO1_Status   0
#define STO2_Status   0

#define IcHaus_ErrSts    (( HWREG( GPIODATA_BASE + GPIO_O_GPADAT ) >> 20 ) & 0x1)
#define IcHaus_WarnSts   (( HWREG( GPIODATA_BASE + GPIO_O_GPADAT ) >> 24 ) & 0x1)


#define MT6709_ErrSts    (( HWREG( GPIODATA_BASE + GPIO_O_GPGDAT ) >> 20 ) & 0x1)

#define MT6709_CAL_EN()     HWREG( GPIODATA_BASE + GPIO_O_GPGSET )      = 1UL << 17;     //GPIO209
#define MT6709_CAL_DIS()    HWREG( GPIODATA_BASE + GPIO_O_GPGCLEAR )      = 1UL << 17;     //GPIO209



#endif

extern void InitCpu1_GPIO( void );

extern USHORT DriveModelSel( void );

extern USHORT InputScan( void );
extern void OutputScan( USHORT kx );

#endif

