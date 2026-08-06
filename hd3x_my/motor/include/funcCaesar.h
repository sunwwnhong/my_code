//----------------------------------------------------------//
// File Name		: funcHd33.h	
// Description		: HD33相关逻辑处理
// Time				: 2011.03.02
// Editor			: xxxxx
// Co.				: xxxxx
//----------------------------------------------------------//
#ifndef __F_FUNC_CAESAR_H__
#define __F_FUNC_CAESAR_H__



// ----------------函数声明------------------------------------------
extern void CaesarDiagnoseProcess(void);
extern int16 TemperatureCalc(Uint16 adTemp);

// ----------------函数声明结束------------------------------------------
struct INV_HD3X_CHECK_FLAG_BITS
{
    Uint16 reset:1;         // 0 复位
    Uint16 rsvd:15;         // 1-15 保留
};
union INV_HD3X_CHECK_FLAG
{
    Uint16 all;
    struct  INV_HD3X_CHECK_FLAG_BITS bit;
};
extern union INV_HD3X_CHECK_FLAG invHd3xCheckFlag;

struct INV_SILICON_STATUS_FLAG_BITS
{
    Uint16 bSilicon1Status:4;       // 0-3 可控硅1状态
    Uint16 bSilicon2Status:4;       // 4-7 可控硅2状态
    Uint16 bInputVolErr:1;          // 8 输入电压采样异常
    Uint16 bGenvolErr:1;            // 9 母线电压采样异常
    Uint16 bTempErr:1;              // 10 温度采样板死机
    Uint16 bOutVolErr:1;            // 11 输出电压采样板异常 -- 岸电输出两级采样
    
    Uint16 rsvd2:4;                 // 12-15 保留
};
union INV_SILICON_STATUS_FLAG
{
    Uint16 all;
    struct  INV_SILICON_STATUS_FLAG_BITS bit;
};
extern union INV_SILICON_STATUS_FLAG invSiliconStatusFlag, invSiliconStatus;

struct Q_STATUS_BITS
{
    u16 QQ1:4;    // Q1 状态
    u16 QQ2:4;    // Q2 状态
    u16 QQ3:4;    // Q3 保留
    u16 QQ4:4;    // Q4 保留
};
//struct Q_STATUS_BITS bitIgbt;
union Q_STATUS
{
    Uint16 all;
    struct Q_STATUS_BITS bit;
};
extern union Q_STATUS /*qStatusU,qStatusV,qStatusW*/ qStatusU14, qStatusU56V12, qStatusV36, qStatusW14, qStatusW56, qStatusAll; // LS_20231116
extern u16 /*qStatusUErr,qStatusVErr,qStatusWErr*/ qStatusErrU14, qStatusErrU56V12, qStatusErrV36, qStatusErrW14, qStatusErrW56, qStatusErrAll; // LS_20231116

//-------------------------------------------------//

struct POWER_LOGIC_STATUS_BITS
{
    Uint16 bHd33ErrDiagnoseEnable:1;    // 0 检测可控硅故障使能     
    Uint16 rsvd:15;                     // 2-15

};
union POWER_LOGIC_STATUS
{
    Uint16 all;
    struct  POWER_LOGIC_STATUS_BITS bit;
};
extern union POWER_LOGIC_STATUS powerLogicStatus;
//-------------------------------------------------//

struct INV_HD33_STATUS_BITS
{
    Uint16 bOverTemperatureFault:3;     // 0-2 过温故障
    Uint16 bOverTemperatureAlarm:3;     // 3-5 过温报警

    Uint16 rsvd:10;                     // 6-15

};
union INV_HD33_STATUS
{
    Uint16  all;
    struct  INV_HD33_STATUS_BITS bit;
};
extern union INV_HD33_STATUS invHd33Status;

//-------------------------------------------//

#define NPC_ERR_TEMP_UP     70 // 75
#define NPC_ERR_TEMP_DOWN   65 // 70
#define NPC_ALARM_TEMP      55 // 65


#define AD_MAX_UVW      	32767

#define NPC_TEMP_MIN    	(-400)
#define NPC_TEMP_MAX    	(1200)

#define FAULT_CHECK_TIME	1000		// 自检

extern Uint16 invSiliconEnable;
extern Uint16 invIgbtDiagnose;
extern int16 uTemperature, vTemperature, wTemperature;
extern Uint32 ratingUdc;
#endif


//----------------------------END-------------------------//

