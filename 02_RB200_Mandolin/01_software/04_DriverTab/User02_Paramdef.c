/****************************************************************************************************/
/*																									*/
/*																									*/
/*		User02_Paramdef.c : 参数定义源文件															*/
/*																									*/
/*																									*/
/****************************************************************************************************/
/*																									*/
/*																									*/
/*		1. 参数定义																					*/
/*																									*/
/*		2. 参数管理表																				*/
/*																									*/
/*																									*/
/*																									*/
/*																									*/
/*																									*/
/*																									*/
/************** Copyright (C) ××× Electric Corporation *******************************************/
/*																									*/
/*		2026.3/.17 : Made by Excel Macro															*/
/*																									*/
/*																									*/
/****************************************************************************************************/
#include "User02_Paramdef.h"
#include "UserGroble.h"





/****************************************************************************************************/
/*																									*/
/*		标准参数计算函数																			*/
/*																									*/
/****************************************************************************************************/
/*--------------------------------------------------------------------------------------------------*/
/*		标准参数计算函数																			*/
/*--------------------------------------------------------------------------------------------------*/
LONG	pncal_StdDummy( ULONG Cmd, ULONG Data, ULONG Digit )
{
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/





/****************************************************************************************************/
/*																									*/
/*		参数定义																					*/
/*																									*/
/****************************************************************************************************/
/****************************************************************************************************/
/*		Pn000 : 功能选择应用开关0 [－]																*/
/****************************************************************************************************/
LONG	pncal_dummy( ULONG Cmd, ULONG Data, ULONG Digit )
{
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_b_prm0_0 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0006,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.b_prm0_0),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x2218),
};



/****************************************************************************************************/
/*		Pn001 : 伺服使能开关 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_b_prm0_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0008,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.b_prm0_1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0011),
};



/****************************************************************************************************/
/*		Pn002 : 电机旋转方向 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_motdir = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x000A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.motdir),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0001),
};



/****************************************************************************************************/
/*		Pn003 : 接通电源时的监视显示 [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_mondef = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x000C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.mondef),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0FFF),
};



/****************************************************************************************************/
/*		Pn004 : 伺服OFF&Gr.1故障时停机方式 [－]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_b_prm0_04 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x000E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.b_prm0_04),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0002),
};



/****************************************************************************************************/
/*		Pn005 : Gr.2故障时停机方式 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_b_prm0_05 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0010,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.b_prm0_05),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0001),
};



/****************************************************************************************************/
/*		Pn006 : 警告检出 [－]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_b_prm0_06 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0012,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.b_prm0_06),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x4123),
};



/****************************************************************************************************/
/*		Pn007 : 超程(OT)停机方式 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_b_prm0_07 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0014,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.b_prm0_07),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0012),
};



/****************************************************************************************************/
/*		Pn008 : 静止时,伺服Off时电磁制动器抱闸输出信号延时 [1ms]									*/
/****************************************************************************************************/
LONG	pncal_brktim( ULONG Cmd, ULONG Data, ULONG Digit )
{
ULONG ulwk;
		  ulwk = Prm.brktim;
		   Gprm.BkonDelayTime = (USHORT)ulwk;
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_brktim = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0016,
/* 处理函数指针					*/	pncal_brktim,
/* RAM地址						*/	&(Prm.brktim),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(2000),
};



/****************************************************************************************************/
/*		Pn009 : 旋转时,伺服off时电磁制动器抱闸输出信号延时 [1ms]									*/
/****************************************************************************************************/
LONG	pncal_brkwai( ULONG Cmd, ULONG Data, ULONG Digit )
{
ULONG ulwk;
		ulwk = Prm.brkwai;
		Gprm.BkonWaitTime = (USHORT)ulwk;
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_brkwai = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0018,
/* 处理函数指针					*/	pncal_brkwai,
/* RAM地址						*/	&(Prm.brkwai),
/* 下限値						*/	(USHORT)(100),
/* 上限値						*/	(USHORT)(2000),
};



/****************************************************************************************************/
/*		Pn00A : 旋转时,电磁制动器抱闸解除时电机速度设定 [rpm]										*/
/****************************************************************************************************/
LONG	pncal_brkspd( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  Gprm.BkonSpdLevel = KpiSpeedLevelCal( Prm.brkspd*10UL, 0 );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_brkspd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x001A,
/* 处理函数指针					*/	pncal_brkspd,
/* RAM地址						*/	&(Prm.brkspd),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn00B : 电磁制动器抱闸解除延时 [1ms]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_brkOnDly = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x001C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.brkOnDly),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(2000),
};



/****************************************************************************************************/
/*		Pn00C : 功能选择应用开关C [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_b_prm0_0C = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x001E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.b_prm0_0C),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0115),
};



/****************************************************************************************************/
/*		Pn00D : 功能选择应用开关D [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_b_prm0_0D = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0020,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.b_prm0_0D),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x2311),
};



/****************************************************************************************************/
/*		Pn00E : 功能选择应用开关E [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_b_prm0_0E = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0022,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.b_prm0_0E),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x4111),
};



/****************************************************************************************************/
/*		Pn00F : 功能选择应用开关F [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_b_prm0_F = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0024,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.b_prm0_F),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0000),
};



/****************************************************************************************************/
/*		Pn011 : 外部脉冲信号滤波时间 [12.5ns]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_PcmdFTime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0026,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PcmdFTime),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(4000),
};



/****************************************************************************************************/
/*		Pn012 : 外接制动电阻功率 [10W]																*/
/****************************************************************************************************/
LONG	pncal_regres( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalRegeneOverLoadLevel( );		/* 回生過負荷レベルの計算	   */
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_regres = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_WATTAGE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0028,
/* 处理函数指针					*/	pncal_regres,
/* RAM地址						*/	&(Prm.regres),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn013 : 外接制动电阻阻值 [Ω]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_regresvalue = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x002A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.regresvalue),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn014 : 驱动器上电使能延时时间 [ms]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_ServoOnDely = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x002C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ServoOnDely),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(6000),
};



/****************************************************************************************************/
/*		Pn015 : 电机过载警告值 [%]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_olwarlvl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x002E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.olwarlvl),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn016 : 电机过载检出基极电流降额设定 [%]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_mtbastrq_drt = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0030,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.mtbastrq_drt),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn017 : 选择单相电源输入时伺服单元过载检测电流降额百分比 [%]								*/
/****************************************************************************************************/
const	PRMDEF	pndef_snglph_base_drt = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0032,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.snglph_base_drt),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn019 : DB电阻功率 [10W]																	*/
/****************************************************************************************************/
LONG	pncal_dbres( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalDbrakeOverLoadLevel( );		/* ＤＢ過負荷系数的計算		 */
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_dbres = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_WATTAGE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0034,
/* 处理函数指针					*/	pncal_dbres,
/* RAM地址						*/	&(Prm.dbres),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn020 : 全闭环功能开关1 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_fcplsel = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0036,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.fcplsel),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x9112),
};



/****************************************************************************************************/
/*		Pn021 : 全闭环功能开关2 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_fcplsel2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0038,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.fcplsel2),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0121),
};



/****************************************************************************************************/
/*		Pn022 : 全闭环光学尺滤波时间 [ms]															*/
/****************************************************************************************************/
LONG	pncal_FensFiltTime( ULONG Cmd, ULONG Data, ULONG Digit )
{
		   KpxInitFullClosedMaFilter( );
		   return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_FensFiltTime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x003A,
/* 处理函数指针					*/	pncal_FensFiltTime,
/* RAM地址						*/	&(Prm.FensFiltTime),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(4000),
};



/****************************************************************************************************/
/*		Pn023 : 光学尺电子齿轮分子[N](低16位) [-]													*/
/****************************************************************************************************/
LONG	pncal_fcplsnl( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  IprmcalFullClosedEnc( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_fcplsnl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PPR },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x003C,
/* 处理函数指针					*/	pncal_fcplsnl,
/* RAM地址						*/	&(Prm.fcplsnl),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(0),
};



/****************************************************************************************************/
/*		Pn024 : 光学尺电子齿轮分子[N](高16位) [－]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_fcplsnh = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x003E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.fcplsnh),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(16384),
};



/****************************************************************************************************/
/*		Pn025 : 光学尺电子齿轮分母[M](低16位) [-]													*/
/****************************************************************************************************/
LONG	pncal_fcplsml( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  IprmcalFullClosedEnc( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_fcplsml = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PPR },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0040,
/* 处理函数指针					*/	pncal_fcplsml,
/* RAM地址						*/	&(Prm.fcplsml),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(0),
};



/****************************************************************************************************/
/*		Pn026 : 光学尺电子齿轮分母[M](高16位) [－]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_fcplsmh = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0042,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.fcplsmh),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(16384),
};



/****************************************************************************************************/
/*		Pn027 : 混合偏差过大设定值(低16位) [光学尺単位]												*/
/****************************************************************************************************/
LONG	pncal_fpgoverlv2l( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.fpgoverLevel = LONGOF( Prm.fpgoverlv2l, Prm.fpgoverlv2h );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_fpgoverlv2l = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0044,
/* 处理函数指针					*/	pncal_fpgoverlv2l,
/* RAM地址						*/	&(Prm.fpgoverlv2l),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0),
};



/****************************************************************************************************/
/*		Pn028 : 混合偏差过大设定值(高16位) [－]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_fpgoverlv2h = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0046,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.fpgoverlv2h),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(16384),
};



/****************************************************************************************************/
/*		Pn029 : 混合偏差清零设定(L) [光学尺单位]													*/
/****************************************************************************************************/
LONG	pncal_fpgoverclrl( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  Gprm.fpgclcLevel = LONGOF( Prm.fpgoverclrl, Prm.fpgoverclrh );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_fpgoverclrl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0048,
/* 处理函数指针					*/	pncal_fpgoverclrl,
/* RAM地址						*/	&(Prm.fpgoverclrl),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn02A : 混合偏差清零设定(H) [光学尺单位]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_fpgoverclrh = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x004A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.fpgoverclrh),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn02B : 半闭环 & 全闭环切换开关 [－]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_FenseSel = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x004C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.FenseSel),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0011),
};



/****************************************************************************************************/
/*		Pn02C : 全闭环方式2补偿偏差最小阈值 [－]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_Meth2ComV = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x004E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Meth2ComV),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn02D : 全闭环方式2补偿速度最大阈值 [rpm]													*/
/****************************************************************************************************/
LONG	pncal_FensSpdlv( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  Gprm.FenseSpdLevel = KpiSpeedLevelCal( Prm.FensSpdlv * 10, 0 );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_FensSpdlv = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0050,
/* 处理函数指针					*/	pncal_FensSpdlv,
/* RAM地址						*/	&(Prm.FensSpdlv),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn030 : 绝对位置限制单圈最大值(低16位) [－]													*/
/****************************************************************************************************/
LONG	pncal_SoftLimitMaxl( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  IprmAbsPosSoftLimit( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_SoftLimitMaxl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0052,
/* 处理函数指针					*/	pncal_SoftLimitMaxl,
/* RAM地址						*/	&(Prm.SoftLimitMaxl),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn031 : 绝对位置限制单圈最大值(高16位) [－]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_SoftLimitMaxh = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0054,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.SoftLimitMaxh),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn032 : 绝对位置限制多圈最大值 [－]															*/
/****************************************************************************************************/
LONG	pncal_SoftLimitMMax( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  IprmAbsPosSoftLimit( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_SoftLimitMMax = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0056,
/* 处理函数指针					*/	pncal_SoftLimitMMax,
/* RAM地址						*/	&(Prm.SoftLimitMMax),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn033 : 绝对位置限制单圈最小值(低16位) [－]													*/
/****************************************************************************************************/
LONG	pncal_SoftLimitMinl( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  IprmAbsPosSoftLimit( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_SoftLimitMinl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0058,
/* 处理函数指针					*/	pncal_SoftLimitMinl,
/* RAM地址						*/	&(Prm.SoftLimitMinl),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn034 : 绝对位置限制单圈最小值(高16位) [－]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_SoftLimitMinh = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x005A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.SoftLimitMinh),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn035 : 绝对位置限制多圈最小值 [－]															*/
/****************************************************************************************************/
LONG	pncal_SoftLimitMMin( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  IprmAbsPosSoftLimit( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_SoftLimitMMin = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x005C,
/* 处理函数指针					*/	pncal_SoftLimitMMin,
/* RAM地址						*/	&(Prm.SoftLimitMMin),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn036 : 绝对位置软限位滞环 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_SoftLimitDelta = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x005E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.SoftLimitDelta),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(30000),
};



/****************************************************************************************************/
/*		Pn039 : 伺服Off时减速时间 [ms]																*/
/****************************************************************************************************/
LONG	pncal_offdec( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalBaseSoftOffDec( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_offdec = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0060,
/* 处理函数指针					*/	pncal_offdec,
/* RAM地址						*/	&(Prm.offdec),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn040 : 绝对值编码器的使用方法 [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_absEncuse = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0062,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.absEncuse),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0021),
};



/****************************************************************************************************/
/*		Pn041 : 绝对值编码器电池欠压时的警报/警告选择 [－]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_absEncalm = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0064,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.absEncalm),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0001),
};



/****************************************************************************************************/
/*		Pn045 : 主回路（DC）欠电压时功能选择 [－]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_UvModeSel = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0066,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.UvModeSel),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0002),
};



/****************************************************************************************************/
/*		Pn046 : 主回路电压下降时转矩限制 [%]														*/
/****************************************************************************************************/
LONG	pncal_UvTrqLmt( ULONG Cmd, ULONG Data, ULONG Digit )
{
LONG	sx;
LONG	lwrk;

		Gprm.UvTrqLmt = KpiTorqueLevelCal( 100UL * Prm.UvTrqLmt, 0 );			/* [%] --> [2^24/MaxTrq]	*/
		lwrk = 0x1000000;													/* [%] --> [2^24/MaxTrq]	*/ /* CB396 *//*<V588>*/

		if ( Prm.UvTrqLmtOffFil != 0 )
		{
			Gprm.DeltaUvTrqLmt = MlibScalKxgain( (LONG)(lwrk - Gprm.UvTrqLmt), 1, KPI_SCANB_MS( Prm.UvTrqLmtOffFil ), &sx, -24 );	/* CB396 *//*<V588>*/
			if ( (Gprm.DeltaUvTrqLmt == 0) && (Prm.UvTrqLmt != pndef_UvTrqLmt.UpperLimit) )
			{
				Gprm.DeltaUvTrqLmt = 1;
			}
		}
		else
		{
			Gprm.DeltaUvTrqLmt = (LONG)(lwrk - Gprm.UvTrqLmt);
		}
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_UvTrqLmt = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0068,
/* 处理函数指针					*/	pncal_UvTrqLmt,
/* RAM地址						*/	&(Prm.UvTrqLmt),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn047 : 主回路电压下降时转矩限制解除时间 [ms]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_UvTrqLmtOffFil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x006A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.UvTrqLmtOffFil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn050 : 转矩限制方式选择 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_torqlimt = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x006C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.torqlimt),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0005),
};



/****************************************************************************************************/
/*		Pn051 : 内部正转转矩限制 [%]																*/
/****************************************************************************************************/
LONG	pncal_tlmtf( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.FwIntTrqLmt = KpiTorqueLevelCal( 100UL * Prm.tlmtf, 0 ); /* [%] --> [2^24/MaxTrq]	  */  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_tlmtf = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x006E,
/* 处理函数指针					*/	pncal_tlmtf,
/* RAM地址						*/	&(Prm.tlmtf),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(500),
};



/****************************************************************************************************/
/*		Pn052 : 内部反转转矩限制 [%]																*/
/****************************************************************************************************/
LONG	pncal_tlmtr( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.RvIntTrqLmt = KpiTorqueLevelCal( 100UL * Prm.tlmtr, 0 ); /* [%] --> [2^24/MaxTrq]	  */
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_tlmtr = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0070,
/* 处理函数指针					*/	pncal_tlmtr,
/* RAM地址						*/	&(Prm.tlmtr),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(500),
};



/****************************************************************************************************/
/*		Pn053 : 紧急停止转矩 [%]																	*/
/****************************************************************************************************/
LONG	pncal_emgtrq( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.EstopTrqLmt = KpiTorqueLevelCal( 100UL * Prm.emgtrq, 0 );	  /* [%] --> [2^24/MaxTrq]	  */
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_emgtrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0072,
/* 处理函数指针					*/	pncal_emgtrq,
/* RAM地址						*/	&(Prm.emgtrq),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(800),
};



/****************************************************************************************************/
/*		Pn054 : 外部正转转矩限制 [%]																*/
/****************************************************************************************************/
LONG	pncal_outlmtf( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.FwExtTrqLmt = KpiTorqueLevelCal( 100UL * Prm.outlmtf, 0 );	  /* [%] --> [2^24/MaxTrq]	  */
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_outlmtf = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0074,
/* 处理函数指针					*/	pncal_outlmtf,
/* RAM地址						*/	&(Prm.outlmtf),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(500),
};



/****************************************************************************************************/
/*		Pn055 : 外部反转转矩限制 [%]																*/
/****************************************************************************************************/
LONG	pncal_outlmtr( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.RvExtTrqLmt = KpiTorqueLevelCal( 100UL * Prm.outlmtr, 0 );	  /* [%] --> [2^24/MaxTrq]	  */
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_outlmtr = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0076,
/* 处理函数指针					*/	pncal_outlmtr,
/* RAM地址						*/	&(Prm.outlmtr),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(500),
};



/****************************************************************************************************/
/*		Pn056 : 飞车检测转矩阈值 [%]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_RunOverTorq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0078,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RunOverTorq),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(255),
};



/****************************************************************************************************/
/*		Pn057 : 飞车检测速度阈值 [%]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_RunOverSpd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x007A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RunOverSpd),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(200),
};



/****************************************************************************************************/
/*		Pn070 : 编码器分频脉冲数(4倍频前) [P/Rev]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_pgrat = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PPR },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x007C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.pgrat),
/* 下限値						*/	(USHORT)(35),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn076 : 串行编码器单圈分辨率调整 [－]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_SerEncSel = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x007E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.SerEncSel),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0051),
};



/****************************************************************************************************/
/*		Pn07F : 编码器多圈和故障清除 [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_EncErrClr = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.EncErrClr),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn080 : 485通信地址 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Address = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0080,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Address),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x007F),
};



/****************************************************************************************************/
/*		Pn081 : 485通信格式 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Mode = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0082,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Mode),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x1655),
};



/****************************************************************************************************/
/*		Pn082 : EtherCAT 站点别名 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_EtherCatAddr = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0084,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.EtherCatAddr),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn083 : EtherCAT 主机类型 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_EtherCatType = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0086,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.EtherCatType),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0001),
};



/****************************************************************************************************/
/*		Pn084 : EtherCAT 同步计数偏差上限 [－]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_SycnhErr = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0088,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.SycnhErr),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x000F),
};



/****************************************************************************************************/
/*		Pn085 : 通讯写入功能码是否存入Eeprom [－]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_ComSaveEeprom = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x008A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ComSaveEeprom),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0111),
};



/****************************************************************************************************/
/*		Pn086 : EtherCAT 配置 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_EtherCATConfig = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x008C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.EtherCATConfig),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0011),
};



/****************************************************************************************************/
/*		Pn087 : 485通讯寄存器地址映射开关 [－]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_addmapEn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x008E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.addmapEn),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x1111),
};



/****************************************************************************************************/
/*		Pn088 : 1#寄存器映射源地址 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_addmap1s = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0090,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.addmap1s),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x1FFF),
};



/****************************************************************************************************/
/*		Pn089 : 1#寄存器映射目的地址 [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_addmap1e = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0092,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.addmap1e),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x1FFF),
};



/****************************************************************************************************/
/*		Pn08A : 2#寄存器映射源地址 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_addmap2s = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0094,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.addmap2s),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x1FFF),
};



/****************************************************************************************************/
/*		Pn08B : 2#寄存器映射目的地址 [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_addmap2e = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0096,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.addmap2e),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x1FFF),
};



/****************************************************************************************************/
/*		Pn100 : 转动惯量比 [%]																		*/
/****************************************************************************************************/
LONG	pncal_jrate( ULONG Cmd, ULONG Data, ULONG Digit )
{
//	PcalBaseSpeedControl( Prm.loophz, Prm.pitime, 1 );
//	PcalBaseSpeedControl( Prm.loophz2, Prm.pitime2, 2 );
		PcalBaseSpeedControl( Prm.loophz, Prm.pitime, Prm.jrate, 1 );
		PcalBaseSpeedControl( Prm.loophz2, Prm.pitime2, Prm.jrate, 2 );
#if( MODELFOLLOW_CTRL != 0 ) /*<V043>*/
		PcalMfcModelControl( Prm.mdlgn, Prm.mdlzeta, Prm.mdlantfrq,
			  Prm.mdlresfrq, Prm.mdlvff, Prm.mdlptff, Prm.mdlntff, 0, 0);
		PcalMfcModelControl( Prm.mdlgn2, Prm.mdlzeta2, Prm.mdlantfrq,
			  Prm.mdlresfrq, Prm.mdlvff, Prm.mdlptff, Prm.mdlntff, 0, 1);
#endif
#if( DIDOVS != 0 )
		/*↓↓↓↓↓ <V221> ↓↓↓↓↓*/
		PcalDisturbObserver( Prm.loophz, Prm.dobgn, Prm.loophz2, Prm.dobgn2, Prm.dtrqgn, Prm.dlpfil, Prm.dobjgn, 0 ); // <V228>
		PcalDisturbObserver( Prm.loophz, Prm.dobgn, Prm.loophz2, Prm.dobgn2, Prm.dtrqgn, Prm.dlpfil, Prm.dobjgn, 1 ); // <V228>
		/*↑↑↑↑↑ <V221> ↑↑↑↑↑*/
#endif
#if( ATYPERES_CTRL != 0 )
		PcalResVibControl( );
#endif
		PcalVibrationDetectJGain( );
#if( SPDOVS_PHASECOMP != 0 )
		PcalEhSpeedObserver( );
#endif
		//PcalMotorLessTestMode( );		/* モータレステストモードパラメータ計算	  *//*<V245>*/
		PcalSpeedLimitGain( Prm.loophz, 1 );
		PcalSpeedLimitGain( Prm.loophz2, 2 );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_jrate = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0098,
/* 处理函数指针					*/	pncal_jrate,
/* RAM地址						*/	&(Prm.jrate),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(20000),
};



/****************************************************************************************************/
/*		Pn101 : 速度环比例增益 [0.1Hz]																*/
/****************************************************************************************************/
LONG	pncal_loophz( ULONG Cmd, ULONG Data, ULONG Digit )
{
#ifdef M3FSEL_COMPRM_ENABLE
		extern LONG pcal_m3_convert_Kv(ULONG Cmd, ULONG Value, ULONG Digit);
		pcal_m3_convert_Kv(Cmd, Data, Digit);
#endif

  PcalBaseSpeedControl( Prm.loophz, Prm.pitime, Prm.jrate, 1 ); 
#if ( ZANTEI_SPDOVS != 0 )
  PcalSpeedObserver( );
#endif
#if( DIDOVS != 0 ) /*↓↓↓↓↓ <V221> ↓↓↓↓↓*/
  PcalDisturbObserver( Prm.loophz, Prm.dobgn, Prm.loophz2, Prm.dobgn2, Prm.dtrqgn, Prm.dlpfil, Prm.dobjgn, 0 ); // <V228>
#endif /*↑↑↑↑↑ <V221> ↑↑↑↑↑*/
 PcalAtGseldKviSet( );
 RpiRegSetOnePrmTuningLevel( Prm.loophz );
 PcalSpeedLimitGain( Prm.loophz, 1 );

 /* 电流ループゲイン 速度ゲイン連動 <V073>  */
// PcalMicroDqAcrGain(MlibMAX(Prm.loophz, Prm.loophz2),Prm.KcGainRatio);

  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_loophz = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x009A,
/* 处理函数指针					*/	pncal_loophz,
/* RAM地址						*/	&(Prm.loophz),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(20000),
};



/****************************************************************************************************/
/*		Pn102 : 速度环积分时间常数 [0.01ms]															*/
/****************************************************************************************************/
LONG	pncal_pitime( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalBaseSpeedControl( Prm.loophz, Prm.pitime, Prm.jrate, 1 );
		PcalAtGseldKviSet( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_pitime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x009C,
/* 处理函数指针					*/	pncal_pitime,
/* RAM地址						*/	&(Prm.pitime),
/* 下限値						*/	(USHORT)(15),
/* 上限値						*/	(USHORT)(51200),
};



/****************************************************************************************************/
/*		Pn103 : 位置环比例增益 [0.1/s]																*/
/****************************************************************************************************/
LONG	pncal_posgn( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalBasePositionPControl( Prm.posgn, 1 );
		PcalZeroPositionControl( Prm.posgn, 1 ); /* ゼロクランプ位置制御ゲイン計算	 */
		PcalAtGseldKpSet( );
		PcalBaseSpeedFFControl( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_posgn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_SECINV },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x009E,
/* 处理函数指针					*/	pncal_posgn,
/* RAM地址						*/	&(Prm.posgn),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(20000),
};



/****************************************************************************************************/
/*		Pn104 : 第1第1转矩指令滤波器 [0.01ms]														*/
/****************************************************************************************************/
LONG	pncal_trqfil11( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalBaseTrqLpassFilter( Prm.trqfil11, 1 ); /* トルクフィルタＬＰＦパラメータ計算   */
		PcalAtGseldKlpfSet( );
#if( TUNINGLESS_CTRL != 0 )
		PcalTuningLessOnePrmCalc( );   /*<V108>*/
#endif
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_trqfil11 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00A0,
/* 处理函数指针					*/	pncal_trqfil11,
/* RAM地址						*/	&(Prm.trqfil11),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn105 : 第2速度环比例增益 [0.1Hz]															*/
/****************************************************************************************************/
LONG	pncal_loophz2( ULONG Cmd, ULONG Data, ULONG Digit )
{
//	PcalBaseSpeedControl( Prm.loophz2, Prm.pitime2, 2 );
		PcalBaseSpeedControl( Prm.loophz2, Prm.pitime2, Prm.jrate, 2 );	  /*<V108>*/
		PcalAtGseldKviSet( );
		PcalSpeedLimitGain( Prm.loophz2, 2 );

  /* 电流ループゲイン 速度ゲイン連動 <V073>  */
// PcalMicroDqAcrGain(MlibMAX(Prm.loophz, Prm.loophz2),Prm.KcGainRatio);

#if( DIDOVS != 0 ) /*<V043>*/
  /*↓↓↓↓↓ <V221> ↓↓↓↓↓*/
  PcalDisturbObserver( Prm.loophz, Prm.dobgn, Prm.loophz2, Prm.dobgn2, Prm.dtrqgn, Prm.dlpfil, Prm.dobjgn, 1 ); // <V228>
	/*↑↑↑↑↑ <V221> ↑↑↑↑↑*/
#endif

  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_loophz2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00A2,
/* 处理函数指针					*/	pncal_loophz2,
/* RAM地址						*/	&(Prm.loophz2),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(20000),
};



/****************************************************************************************************/
/*		Pn106 : 第2速度环积分时间常数 [0.01ms]														*/
/****************************************************************************************************/
LONG	pncal_pitime2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalBaseSpeedControl( Prm.loophz2, Prm.pitime2, Prm.jrate, 2 );	  /*<V108>*/
		PcalAtGseldKviSet( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_pitime2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00A4,
/* 处理函数指针					*/	pncal_pitime2,
/* RAM地址						*/	&(Prm.pitime2),
/* 下限値						*/	(USHORT)(15),
/* 上限値						*/	(USHORT)(51200),
};



/****************************************************************************************************/
/*		Pn107 : 第2位置环比例增益 [0.1/s]															*/
/****************************************************************************************************/
LONG	pncal_posgn2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalBasePositionPControl( Prm.posgn2, 2 );
		PcalZeroPositionControl( Prm.posgn2, 2 ); /* ゼロクランプ位置制御ゲイン計算	   */
		PcalAtGseldKpSet( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_posgn2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_SECINV },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00A6,
/* 处理函数指针					*/	pncal_posgn2,
/* RAM地址						*/	&(Prm.posgn2),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(20000),
};



/****************************************************************************************************/
/*		Pn108 : 第1第2转矩滤指令滤波器 [0.01ms]														*/
/****************************************************************************************************/
LONG	pncal_trqfil12( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalBaseTrqLpassFilter( Prm.trqfil12, 2 ); /* トルクフィルタＬＰＦパラメータ計算   */
		PcalAtGseldKlpfSet( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_trqfil12 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00A8,
/* 处理函数指针					*/	pncal_trqfil12,
/* RAM地址						*/	&(Prm.trqfil12),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn10A : 调整模式选择 [－]																	*/
/****************************************************************************************************/
LONG	pncal_tunmode( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  GainSel_Update( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_tunmode = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00AA,
/* 处理函数指针					*/	pncal_tunmode,
/* RAM地址						*/	&(Prm.tunmode),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0001),
};



/****************************************************************************************************/
/*		Pn10B : 刚性等级 [－]																		*/
/****************************************************************************************************/
LONG	pncal_rigidity( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  GainSel_Update( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_rigidity = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00AC,
/* 处理函数指针					*/	pncal_rigidity,
/* RAM地址						*/	&(Prm.rigidity),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(41),
};



/****************************************************************************************************/
/*		Pn10C : 插补模式选择 [－]																	*/
/****************************************************************************************************/
LONG	pncal_interpolation( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_interpolation = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00AE,
/* 处理函数指针					*/	pncal_interpolation,
/* RAM地址						*/	&(Prm.interpolation),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(2),
};



/****************************************************************************************************/
/*		Pn110 : 自动增益切换类方式选择开关 [－]														*/
/****************************************************************************************************/
LONG	pncal_gnsw1( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalGainChange(); 
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_gnsw1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00B0,
/* 处理函数指针					*/	pncal_gnsw1,
/* RAM地址						*/	&(Prm.gnsw1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0071),
};



/****************************************************************************************************/
/*		Pn112 : 增益切换过渡时间1 [ms]																*/
/****************************************************************************************************/
LONG	pncal_gnswfil1( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalAutoGainChange( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_gnswfil1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00B2,
/* 处理函数指针					*/	pncal_gnswfil1,
/* RAM地址						*/	&(Prm.gnswfil1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn113 : 增益切换过渡时间2 [ms]																*/
/****************************************************************************************************/
LONG	pncal_gnswfil2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalAutoGainChange( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_gnswfil2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00B4,
/* 处理函数指针					*/	pncal_gnswfil2,
/* RAM地址						*/	&(Prm.gnswfil2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn114 : 增益切换等待时间1 [ms]																*/
/****************************************************************************************************/
LONG	pncal_gnswwait1( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalAutoGainChange( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_gnswwait1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00B6,
/* 处理函数指针					*/	pncal_gnswwait1,
/* RAM地址						*/	&(Prm.gnswwait1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn115 : 增益切换等待时间2 [ms]																*/
/****************************************************************************************************/
LONG	pncal_gnswwait2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalAutoGainChange( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_gnswwait2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00B8,
/* 处理函数指针					*/	pncal_gnswwait2,
/* RAM地址						*/	&(Prm.gnswwait2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn116 : 速度阈值增益切换值																	*/
/****************************************************************************************************/
LONG	pncal_LowSpdLevel( ULONG Cmd, ULONG Data, ULONG Digit )
{
Gprm.LowSpdLevel = KpiSpeedLevelCal( Prm.LowSpdLevel * 10UL, 0 );
return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_LowSpdLevel = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00BA,
/* 处理函数指针					*/	pncal_LowSpdLevel,
/* RAM地址						*/	&(Prm.LowSpdLevel),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn117 : 速度阈值参考																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_SpdSwitch = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00BC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.SpdSwitch),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(2),
};



/****************************************************************************************************/
/*		Pn120 : 位置积分时间常数 [0.1ms]															*/
/****************************************************************************************************/
LONG	pncal_pitfil( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalBasePositionIControl( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_pitfil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00BE,
/* 处理函数指针					*/	pncal_pitfil,
/* RAM地址						*/	&(Prm.pitfil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(50000),
};



/****************************************************************************************************/
/*		Pn121 : 位置前馈增益 [%]																	*/
/****************************************************************************************************/
LONG	pncal_ffgn( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcaldPosRefFFGain();
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ffgn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00C0,
/* 处理函数指针					*/	pncal_ffgn,
/* RAM地址						*/	&(Prm.ffgn),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn122 : 位置前馈滤波时间 [0.01ms]															*/
/****************************************************************************************************/
LONG	pncal_fffil( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcaldPosRefFFFilter();
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_fffil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00C2,
/* 处理函数指针					*/	pncal_fffil,
/* RAM地址						*/	&(Prm.fffil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(6400),
};



/****************************************************************************************************/
/*		Pn123 : 速度前馈增益 [%]																	*/
/****************************************************************************************************/
LONG	pncal_sfgn( ULONG Cmd, ULONG Data, ULONG Digit )
{
			  PcalBaseSpeedFFControl( );
			  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_sfgn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00C4,
/* 处理函数指针					*/	pncal_sfgn,
/* RAM地址						*/	&(Prm.sfgn),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(500),
};



/****************************************************************************************************/
/*		Pn124 : 速度前馈滤波时间 [0.01ms]															*/
/****************************************************************************************************/
LONG	pncal_sffil( ULONG Cmd, ULONG Data, ULONG Digit )
{
			  SpdCtrl.P.KdPffFil = MlibPcalKf1gain( (ULONG)Prm.sffil*10, KPI_SACYCLENS, 0 );
			  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_sffil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00C6,
/* 处理函数指针					*/	pncal_sffil,
/* RAM地址						*/	&(Prm.sffil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(6400),
};



/****************************************************************************************************/
/*		Pn125 : 速度反馈滤波时间常数 [0.01ms]														*/
/****************************************************************************************************/
LONG	pncal_fbfil( ULONG Cmd, ULONG Data, ULONG Digit )
{
//	SpdCtrl.P.KVfbFil = MlibPcalKf1gain( Prm.fbfil*10UL, KPI_SACYCLEUS, 0 );
		SpdCtrl.P.KVfbFil = MlibPcalKf1gain( ((Prm.fbfil + Iprm.SpdFbLpassFil + 4)*10UL), KPI_SACYCLEUS, 0 ); /*<V423>*/
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_fbfil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x00C8,
/* 处理函数指针					*/	pncal_fbfil,
/* RAM地址						*/	&(Prm.fbfil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn130 : 速度环的控制方法(PI/IP) [－]														*/
/****************************************************************************************************/
LONG	pncal_gnmode( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalBitParamMSW();
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_gnmode = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00CA,
/* 处理函数指针					*/	pncal_gnmode,
/* RAM地址						*/	&(Prm.gnmode),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0114),
};



/****************************************************************************************************/
/*		Pn132 : 速度环P/PI切换条件(转矩指令) [%]													*/
/****************************************************************************************************/
LONG	pncal_mdswlv( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.MSWTrqLevel  = KpiTorqueLevelCal( 100UL * Prm.mdswlv, 0 ); /* [%] --> [2^24/MaxTrq] */
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mdswlv = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00CC,
/* 处理函数指针					*/	pncal_mdswlv,
/* RAM地址						*/	&(Prm.mdswlv),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(800),
};



/****************************************************************************************************/
/*		Pn133 : 速度环P/PI切换条件(速度指令) [rpm]													*/
/****************************************************************************************************/
LONG	pncal_mswrf( ULONG Cmd, ULONG Data, ULONG Digit )
{
	Gprm.MSWSpdLevel  = KpiSpeedLevelCal( Prm.mswrf*10UL, 0 );

  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mswrf = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00CE,
/* 处理函数指针					*/	pncal_mswrf,
/* RAM地址						*/	&(Prm.mswrf),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn134 : 速度环P/PI切换条件(加速度) [min-1/s]												*/
/****************************************************************************************************/
LONG	pncal_mswacc( ULONG Cmd, ULONG Data, ULONG Digit )
{
LONG kx,sx;
/*--------------------------------------------------------------------------------------------------*/
/*							  */
/*		 Prm.mswacc * Bprm.Knorspd * SCCYCLEUS				*/
/* MSWAccLevel = ---------------------------------------			  */
/*			1000000					  */
/*							  */
/* Prm.mswacc : [r/min/s]					   */
/* Bprm.Knorspd : [r/min,mm/s --> NorSpd]				   */
/*							  */
/*--------------------------------------------------------------------------------------------------*/

	 kx = MlibScalKxkskx( Prm.mswacc, Bprm.Knorspd, 1, &sx,	 0 );
	  kx = MlibPcalKxgain( kx, KPI_SCCYCLEUS, 1000000, &sx, -24 );
 Gprm.MSWAccLevel = kx;

 return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mswacc = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_ACCEL },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00D0,
/* 处理函数指针					*/	pncal_mswacc,
/* RAM地址						*/	&(Prm.mswacc),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(30000),
};



/****************************************************************************************************/
/*		Pn135 : 速度环P/PI切换条件(位置偏差) [指令単位]												*/
/****************************************************************************************************/
LONG	pncal_msplvl( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.MSWErrLevel = KpiPositionLevelCal( Prm.msplvl );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_msplvl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00D2,
/* 处理函数指针					*/	pncal_msplvl,
/* RAM地址						*/	&(Prm.msplvl),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn140 : A型抑振控制选择开关 [－]															*/
/****************************************************************************************************/
LONG	pncal_mfvibsw( ULONG Cmd, ULONG Data, ULONG Digit )
{
/*--------------------------------------------------------------------------------------------------*/
/* Ａ型制振制御選択																	   */
/*--------------------------------------------------------------------------------------------------*/
		PcalMFVibSupSel();
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mfvibsw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00D4,
/* 处理函数指针					*/	pncal_mfvibsw,
/* RAM地址						*/	&(Prm.mfvibsw),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0011),
};



/****************************************************************************************************/
/*		Pn141 : A型抑振增益修正 [%]																	*/
/****************************************************************************************************/
LONG	pncal_avibgn( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalResVibControl( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_avibgn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00D6,
/* 处理函数指针					*/	pncal_avibgn,
/* RAM地址						*/	&(Prm.avibgn),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn142 : A型频抑振频率 [0.1Hz]																*/
/****************************************************************************************************/
LONG	pncal_avibfrq( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalResVibControl( );
		RpiRegSetAtypeVibTuningFrequency( Prm.avibfrq );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_avibfrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00D8,
/* 处理函数指针					*/	pncal_avibfrq,
/* RAM地址						*/	&(Prm.avibfrq),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(30000),
};



/****************************************************************************************************/
/*		Pn143 : A型抑振阻尼增益 [%]																	*/
/****************************************************************************************************/
LONG	pncal_avibdamp( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalResVibControl( );
		RpiRegSetAtypeVibTuningGain( Prm.avibdamp );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_avibdamp = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00DA,
/* 处理函数指针					*/	pncal_avibdamp,
/* RAM地址						*/	&(Prm.avibdamp),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(300),
};



/****************************************************************************************************/
/*		Pn144 : A型抑振滤波时间常数1修 [0.01ms]														*/
/****************************************************************************************************/
LONG	pncal_avibfil1( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalResVibControl( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_avibfil1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00DC,
/* 处理函数指针					*/	pncal_avibfil1,
/* RAM地址						*/	&(Prm.avibfil1),
/* 下限値						*/	(USHORT)(-1000),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn145 : A型抑振滤波时间常数2修 [0.01ms]														*/
/****************************************************************************************************/
LONG	pncal_avibfil2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalResVibControl( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_avibfil2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00DE,
/* 处理函数指针					*/	pncal_avibfil2,
/* RAM地址						*/	&(Prm.avibfil2),
/* 下限値						*/	(USHORT)(-1000),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn146 : 第2中频抑振频率 [0.1Hz]																*/
/****************************************************************************************************/
LONG	pncal_pstbfrq( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( POSSTB_CTRL != 0 )	  /*<V043>*/
		PcalPosStbCtrl( );
#endif
//RpiRegSetPosStbTuningFrequency//( Prm.pstbfrq );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_pstbfrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00E0,
/* 处理函数指针					*/	pncal_pstbfrq,
/* RAM地址						*/	&(Prm.pstbfrq),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(30000),
};



/****************************************************************************************************/
/*		Pn147 : 第2中频抑振衰减增益 [%]																*/
/****************************************************************************************************/
LONG	pncal_pstbdamp( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( POSSTB_CTRL != 0 )	  /*<V043>*/
		PcalPosStbCtrl( );
#endif
// RpiRegSetPosStbTuningGain( //Prm.pstbdamp );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_pstbdamp = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00E2,
/* 处理函数指针					*/	pncal_pstbdamp,
/* RAM地址						*/	&(Prm.pstbdamp),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(300),
};



/****************************************************************************************************/
/*		Pn14A : II型陷波滤波器1频率 [Hz]															*/
/****************************************************************************************************/
LONG	pncal_Nntchfil1( ULONG Cmd, ULONG Data, ULONG Digit )
{
		   IINotchFilter1_NCF();
		   return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_Nntchfil1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00E4,
/* 处理函数指针					*/	pncal_Nntchfil1,
/* RAM地址						*/	&(Prm.Nntchfil1),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn14B : II型陷波滤波器1深度 [db]															*/
/****************************************************************************************************/
LONG	pncal_Nntchdamp1( ULONG Cmd, ULONG Data, ULONG Digit )
{
		   IINotchFilter1_DPH();
		   return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_Nntchdamp1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00E6,
/* 处理函数指针					*/	pncal_Nntchdamp1,
/* RAM地址						*/	&(Prm.Nntchdamp1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32),
};



/****************************************************************************************************/
/*		Pn14C : II型陷波滤波器2频率 [Hz]															*/
/****************************************************************************************************/
LONG	pncal_Nntchfil2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		   IINotchFilter2_NCF();
		   return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_Nntchfil2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00E8,
/* 处理函数指针					*/	pncal_Nntchfil2,
/* RAM地址						*/	&(Prm.Nntchfil2),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn14D : II型陷波滤波器2深度 [db]															*/
/****************************************************************************************************/
LONG	pncal_Nntchdamp2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		   IINotchFilter2_DPH();
		   return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_Nntchdamp2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00EA,
/* 处理函数指针					*/	pncal_Nntchdamp2,
/* RAM地址						*/	&(Prm.Nntchdamp2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32),
};



/****************************************************************************************************/
/*		Pn150 : 转矩类开关 [－]																		*/
/****************************************************************************************************/
LONG	pncal_tfuncsw( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( DIDOVS != 0 )
		PcalDisturbObserverSW();
#endif
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_tfuncsw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00EC,
/* 处理函数指针					*/	pncal_tfuncsw,
/* RAM地址						*/	&(Prm.tfuncsw),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x1111),
};



/****************************************************************************************************/
/*		Pn151 : 陷波滤波器调整开关 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_anotchsw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00EE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.anotchsw),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0101),
};



/****************************************************************************************************/
/*		Pn152 : 自动陷波共振检测灵敏度 [%]															*/
/****************************************************************************************************/
LONG	pncal_vibdetlvl( ULONG Cmd, ULONG Data, ULONG Digit )
{
		if( Kprm.AmpType == AMPTYPE_ROTARY ) /* 旋转型电机	 */
		{
			Gprm.VibCheckLevelForTunLess = KpiSpeedLevelCal( 200UL*Prm.vibdetlvl/100, 0 );
		}
		else if( Kprm.AmpType == AMPTYPE_LINEAR ) /* 直线电机	*/
		{
			Gprm.VibCheckLevelForTunLess = KpiSpeedLevelCal( 200UL*Prm.vibdetlvl/100, 0 );
		}
		/* 参数更改后需要清除最大最小值 */
		BpiResetMaxMinSpeedError( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_vibdetlvl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00F0,
/* 处理函数指针					*/	pncal_vibdetlvl,
/* RAM地址						*/	&(Prm.vibdetlvl),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(200),
};



/****************************************************************************************************/
/*		Pn153 : 陷波滤波器1频率 [Hz]																*/
/****************************************************************************************************/
LONG	pncal_ntchfil1( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  KpiPcalMicroNotchFilter2(						/* ２次ノッチフィルタのパラメータ計算  */
		   Prm.ntchfil1,							 /* 陷波滤波器频率	[Hz]			   */
		   Prm.ntchq1,								 /* 陷波滤波器Q值  [0.01]			*/
		   Prm.ntchdamp1,							 /* 陷波滤波器深度	[0.001]			 */
		   KPI_SACYCLENS/100,						 /* 陷波滤波器演算周期	[0.1us]			 */
		   (SHORT *)NotCh1Coeff );					 /* フィルタパラメータ設定先頭アドレス	*/

/*--------------------------------------------------------------------------------------------------*/
/* １段目ノッチフィルタ選択 (ASIC)	 */
/*--------------------------------------------------------------------------------------------------*/
		   if( Prm.ntchfil1>=50 && Prm.ntchfil1< 5000 )
		{
			  Notch_P.Notch1EnFlag = 1;
		}
		  else
		   {
			 Notch_P.Notch1EnFlag = 0;
		   }

		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ntchfil1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00F2,
/* 处理函数指针					*/	pncal_ntchfil1,
/* RAM地址						*/	&(Prm.ntchfil1),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn154 : 陷波滤波器1Q值 [0.01]																*/
/****************************************************************************************************/
LONG	pncal_ntchq1( ULONG Cmd, ULONG Data, ULONG Digit )
{
		KpiPcalMicroNotchFilter2(						/* ２次ノッチフィルタのパラメータ計算	  */
		 Prm.ntchfil1,								/* フィルタ周波数  [Hz]					 */
		 Prm.ntchq1,								 /* フィルタＱ定数	[0.01]				   */
		 Prm.ntchdamp1,								 /* フィルタ深さ   [0.001]				*/
		 KPI_SACYCLENS/100,							 /* フィルタ演算周期  [0.1us]			  */
		 (SHORT *)NotCh1Coeff );				  /* フィルタパラメータ設定先頭アドレス		*/
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ntchq1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00F4,
/* 处理函数指针					*/	pncal_ntchq1,
/* RAM地址						*/	&(Prm.ntchq1),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn155 : 陷波滤波器1深度 [0.001]																*/
/****************************************************************************************************/
LONG	pncal_ntchdamp1( ULONG Cmd, ULONG Data, ULONG Digit )
{
		KpiPcalMicroNotchFilter2(						/* ２次ノッチフィルタのパラメータ計算	  */
		 Prm.ntchfil1,								/* フィルタ周波数  [Hz]					 */
		 Prm.ntchq1,								 /* フィルタＱ定数	[0.01]				   */
		 Prm.ntchdamp1,								 /* フィルタ深さ   [0.001]				*/
		 KPI_SACYCLENS/100,							 /* フィルタ演算周期  [0.1us]			  */
		 (SHORT *)NotCh1Coeff );				  /* フィルタパラメータ設定先頭アドレス		*/
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ntchdamp1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	3,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00F6,
/* 处理函数指针					*/	pncal_ntchdamp1,
/* RAM地址						*/	&(Prm.ntchdamp1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn156 : 陷波频滤波2器率 [Hz]																*/
/****************************************************************************************************/
LONG	pncal_ntchfil2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  KpiPcalMicroNotchFilter2(							  /* ２次ノッチフィルタのパラメータ計算	  */
		 Prm.ntchfil2,										/* フィルタ周波数  [Hz]					*/
		 Prm.ntchq2,										/* フィルタＱ定数  [0.01]			  */
		 Prm.ntchdamp2,										/* フィルタ深さ [0.001]					*/
		 KPI_SACYCLENS/100,									/* フィルタ演算周期	 [0.1us]		 */
		 (SHORT *)NotCh2Coeff );							/* フィルタパラメータ設定先頭アドレス */
		 
/*--------------------------------------------------------------------------------------------------*/
/* 2段目ノッチフィルタ選択 (ASIC)	 */
/*--------------------------------------------------------------------------------------------------*/
		if( Prm.ntchfil2>=50 && Prm.ntchfil2< 5000 )
		{
				  Notch_P.Notch2EnFlag = 1;
		}
		else
		{
				  Notch_P.Notch2EnFlag = 0;
		}
		
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ntchfil2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00F8,
/* 处理函数指针					*/	pncal_ntchfil2,
/* RAM地址						*/	&(Prm.ntchfil2),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn157 : 陷波滤波器2Q值 [0.01]																*/
/****************************************************************************************************/
LONG	pncal_ntchq2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		KpiPcalMicroNotchFilter2(						/* ２次ノッチフィルタのパラメータ計算	  */
		 Prm.ntchfil2,									/* フィルタ周波数  [Hz]						*/
		 Prm.ntchq2,									/* フィルタＱ定数  [0.01]				  */
		 Prm.ntchdamp2,									/* フィルタ深さ	  [0.001]			   */
		 KPI_SACYCLENS/100,								/* フィルタ演算周期	 [0.1us]			 */
		 (SHORT *)NotCh2Coeff );						/* フィルタパラメータ設定先頭アドレス	  */
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ntchq2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00FA,
/* 处理函数指针					*/	pncal_ntchq2,
/* RAM地址						*/	&(Prm.ntchq2),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn158 : 陷波滤波器2深度 [0.001]																*/
/****************************************************************************************************/
LONG	pncal_ntchdamp2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		KpiPcalMicroNotchFilter2(						/* ２次ノッチフィルタのパラメータ計算	  */
		 Prm.ntchfil2,									/* フィルタ周波数  [Hz]						*/
		 Prm.ntchq2,									/* フィルタＱ定数  [0.01]				  */
		 Prm.ntchdamp2,									/* フィルタ深さ	  [0.001]			   */
		 KPI_SACYCLENS/100,								/* フィルタ演算周期	 [0.1us]			 */
		 (SHORT *)NotCh2Coeff );						/* フィルタパラメータ設定先頭アドレス	  */
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ntchdamp2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	3,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00FC,
/* 处理函数指针					*/	pncal_ntchdamp2,
/* RAM地址						*/	&(Prm.ntchdamp2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn159 : 陷波频滤波3器率 [Hz]																*/
/****************************************************************************************************/
LONG	pncal_ntchfil3( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  KpiPcalMicroNotchFilter2(							  /* ２次ノッチフィルタのパラメータ計算	  */
		 Prm.ntchfil3,										/* フィルタ周波数  [Hz]					*/
		 Prm.ntchq3,										/* フィルタＱ定数  [0.01]			  */
		 Prm.ntchdamp3,										/* フィルタ深さ [0.001]					*/
		 KPI_SACYCLENS/100,									/* フィルタ演算周期	 [0.1us]		 */
		 (SHORT *)NotCh3Coeff );							/* フィルタパラメータ設定先頭アドレス */
		 
/*--------------------------------------------------------------------------------------------------*/
/* 2段目ノッチフィルタ選択 (ASIC)	 */
/*--------------------------------------------------------------------------------------------------*/
		if( Prm.ntchfil3>=50 && Prm.ntchfil3< 5000 )
		{
				  Notch_P.Notch3EnFlag = 1;
		}
		else
		{
				  Notch_P.Notch3EnFlag = 0;
		}
		
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ntchfil3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x00FE,
/* 处理函数指针					*/	pncal_ntchfil3,
/* RAM地址						*/	&(Prm.ntchfil3),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn15A : 陷波滤波器3Q值 [0.01]																*/
/****************************************************************************************************/
LONG	pncal_ntchq3( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  KpiPcalMicroNotchFilter2(							  /* ２次ノッチフィルタのパラメータ計算	  */
		 Prm.ntchfil3,										/* フィルタ周波数  [Hz]					*/
		 Prm.ntchq3,										/* フィルタＱ定数  [0.01]			  */
		 Prm.ntchdamp3,										/* フィルタ深さ [0.001]					*/
		 KPI_SACYCLENS/100,									/* フィルタ演算周期	 [0.1us]		 */
		 (SHORT *)NotCh3Coeff );							/* フィルタパラメータ設定先頭アドレス */ 
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ntchq3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0100,
/* 处理函数指针					*/	pncal_ntchq3,
/* RAM地址						*/	&(Prm.ntchq3),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn15B : 陷波滤波器3深度 [0.001]																*/
/****************************************************************************************************/
LONG	pncal_ntchdamp3( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  KpiPcalMicroNotchFilter2(							  /* ２次ノッチフィルタのパラメータ計算	  */
		 Prm.ntchfil3,										/* フィルタ周波数  [Hz]					*/
		 Prm.ntchq3,										/* フィルタＱ定数  [0.01]			  */
		 Prm.ntchdamp3,										/* フィルタ深さ [0.001]					*/
		 KPI_SACYCLENS/100,									/* フィルタ演算周期	 [0.1us]		 */
		 (SHORT *)NotCh3Coeff );							/* フィルタパラメータ設定先頭アドレス */

  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ntchdamp3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	3,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0102,
/* 处理函数指针					*/	pncal_ntchdamp3,
/* RAM地址						*/	&(Prm.ntchdamp3),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn15C : 陷波频滤波4器率 [Hz]																*/
/****************************************************************************************************/
LONG	pncal_ntchfil4( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  KpiPcalMicroNotchFilter2(							  /* ２次ノッチフィルタのパラメータ計算	  */
		 Prm.ntchfil4,										/* フィルタ周波数  [Hz]					*/
		 Prm.ntchq4,										/* フィルタＱ定数  [0.01]			  */
		 Prm.ntchdamp4,										/* フィルタ深さ [0.001]					*/
		 KPI_SACYCLENS/100,									/* フィルタ演算周期	 [0.1us]		 */
		 (SHORT *)NotCh4Coeff );							/* フィルタパラメータ設定先頭アドレス */
		 
/*--------------------------------------------------------------------------------------------------*/
/* 2段目ノッチフィルタ選択 (ASIC)	 */
/*--------------------------------------------------------------------------------------------------*/
		if( Prm.ntchfil4>=50 && Prm.ntchfil4< 5000 )
		{
				  Notch_P.Notch4EnFlag = 1;
		}
		else
		{
				  Notch_P.Notch4EnFlag = 0;
		}
		
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ntchfil4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0104,
/* 处理函数指针					*/	pncal_ntchfil4,
/* RAM地址						*/	&(Prm.ntchfil4),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn15D : 陷波滤波器4Q值 [0.01]																*/
/****************************************************************************************************/
LONG	pncal_ntchq4( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  KpiPcalMicroNotchFilter2(							  /* ２次ノッチフィルタのパラメータ計算	  */
		 Prm.ntchfil4,										/* フィルタ周波数  [Hz]					*/
		 Prm.ntchq4,										/* フィルタＱ定数  [0.01]			  */
		 Prm.ntchdamp4,										/* フィルタ深さ [0.001]					*/
		 KPI_SACYCLENS/100,									/* フィルタ演算周期	 [0.1us]		 */
		 (SHORT *)NotCh4Coeff );							/* フィルタパラメータ設定先頭アドレス */

  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ntchq4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0106,
/* 处理函数指针					*/	pncal_ntchq4,
/* RAM地址						*/	&(Prm.ntchq4),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn15E : 陷波滤波器4深度 [0.001]																*/
/****************************************************************************************************/
LONG	pncal_ntchdamp4( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  KpiPcalMicroNotchFilter2(							  /* ２次ノッチフィルタのパラメータ計算	  */
		 Prm.ntchfil4,										/* フィルタ周波数  [Hz]					*/
		 Prm.ntchq4,										/* フィルタＱ定数  [0.01]			  */
		 Prm.ntchdamp4,										/* フィルタ深さ [0.001]					*/
		 KPI_SACYCLENS/100,									/* フィルタ演算周期	 [0.1us]		 */
		 (SHORT *)NotCh4Coeff );							/* フィルタパラメータ設定先頭アドレス */
		 
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ntchdamp4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	3,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0108,
/* 处理函数指针					*/	pncal_ntchdamp4,
/* RAM地址						*/	&(Prm.ntchdamp4),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn161 : 摩擦补偿增益 [%]																	*/
/****************************************************************************************************/
LONG	pncal_dobgn( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalDisturbObserver( Prm.loophz, Prm.dobgn, Prm.loophz2, Prm.dobgn2, Prm.dtrqgn, Prm.dlpfil, Prm.dobjgn, 0 );	// <V228>
		PcalAtGseldKsSet();
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_dobgn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x010A,
/* 处理函数指针					*/	pncal_dobgn,
/* RAM地址						*/	&(Prm.dobgn),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn162 : 第2摩擦补偿增益 [%]																	*/
/****************************************************************************************************/
LONG	pncal_dobgn2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalDisturbObserver( Prm.loophz, Prm.dobgn, Prm.loophz2, Prm.dobgn2, Prm.dtrqgn, Prm.dlpfil, Prm.dobjgn, 1 );	// <V228>
		PcalAtGseldKsSet();
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_dobgn2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x010C,
/* 处理函数指针					*/	pncal_dobgn2,
/* RAM地址						*/	&(Prm.dobgn2),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn163 : 摩擦补偿系数 [%]																	*/
/****************************************************************************************************/
LONG	pncal_dtrqgn( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalDisturbObserver( Prm.loophz, Prm.dobgn, Prm.loophz2, Prm.dobgn2, Prm.dtrqgn, Prm.dlpfil, Prm.dobjgn, 0 );	// <V228>
		PcalDisturbObserver( Prm.loophz, Prm.dobgn, Prm.loophz2, Prm.dobgn2, Prm.dtrqgn, Prm.dlpfil, Prm.dobjgn, 1 );	// <V228>
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_dtrqgn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x010E,
/* 处理函数指针					*/	pncal_dtrqgn,
/* RAM地址						*/	&(Prm.dtrqgn),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn164 : 摩擦补偿频率修正 [0.1Hz]															*/
/****************************************************************************************************/
LONG	pncal_dlpfil( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalDisturbObserver( Prm.loophz, Prm.dobgn, Prm.loophz2, Prm.dobgn2, Prm.dtrqgn, Prm.dlpfil, Prm.dobjgn, 0 );
		PcalDisturbObserver( Prm.loophz, Prm.dobgn, Prm.loophz2, Prm.dobgn2, Prm.dtrqgn, Prm.dlpfil, Prm.dobjgn, 1 );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_dlpfil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0110,
/* 处理函数指针					*/	pncal_dlpfil,
/* RAM地址						*/	&(Prm.dlpfil),
/* 下限値						*/	(USHORT)(-10000),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn165 : 摩擦补偿增益修正 [%]																*/
/****************************************************************************************************/
LONG	pncal_dobjgn( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalDisturbObserver( Prm.loophz, Prm.dobgn, Prm.loophz2, Prm.dobgn2, Prm.dtrqgn, Prm.dlpfil, Prm.dobjgn, 0 );
		PcalDisturbObserver( Prm.loophz, Prm.dobgn, Prm.loophz2, Prm.dobgn2, Prm.dtrqgn, Prm.dlpfil, Prm.dobjgn, 1 );
		PcalAtGseldKsSet();
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_dobjgn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0112,
/* 处理函数指针					*/	pncal_dobjgn,
/* RAM地址						*/	&(Prm.dobjgn),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn166 : 速度观测器开关 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_evoben = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0114,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.evoben),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1),
};



/****************************************************************************************************/
/*		Pn167 : 速度观测器增益 [Hz]																	*/
/****************************************************************************************************/
LONG	pncal_evobgn( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalEhSpeedObserver( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_evobgn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0116,
/* 处理函数指针					*/	pncal_evobgn,
/* RAM地址						*/	&(Prm.evobgn),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(500),
};



/****************************************************************************************************/
/*		Pn168 : 速度观测器惯量修正值 [%]															*/
/****************************************************************************************************/
LONG	pncal_evobjgn( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalEhSpeedObserver( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_evobjgn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0118,
/* 处理函数指针					*/	pncal_evobjgn,
/* RAM地址						*/	&(Prm.evobjgn),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn169 : 速度观测器滤波时间修正值 [0.01ms]													*/
/****************************************************************************************************/
LONG	pncal_evoblpf( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalEhSpeedObserver( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_evoblpf = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x011A,
/* 处理函数指针					*/	pncal_evoblpf,
/* RAM地址						*/	&(Prm.evoblpf),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn170 : 摩擦转矩补偿截止速度 [rpm]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_fricmaxspd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x011C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.fricmaxspd),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn171 : 摩擦转矩正向补偿系数 [%/100rpm]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_friccoefpos = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x011E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.friccoefpos),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn172 : 摩擦转矩反向补偿系数 [%/100rpm]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_friccoefneg = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0120,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.friccoefneg),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn175 : 免调整类控制开关 [－]																*/
/****************************************************************************************************/
LONG	pncal_DatLevel( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( TUNINGLESS_CTRL != 0 )
		PcalTuningLessOnePrmCalc( );
#endif
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_DatLevel = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0122,
/* 处理函数指针					*/	pncal_DatLevel,
/* RAM地址						*/	&(Prm.DatLevel),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x2911),
};



/****************************************************************************************************/
/*		Pn17A : 免调整扰动观测器增益 [0.1Hz]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_TunLessGain = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0124,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.TunLessGain),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn17B : 免调整惯量修正系数 [%]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_TunLessStiff = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0126,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.TunLessStiff),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn17C : 免调整扰动转矩低通滤波器时间常数 [0.01ms]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_TunLessTrqLpf = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0128,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.TunLessTrqLpf),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn17D : 免调整速度FB低通滤波器时间常数 [0.01ms]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_TunLessVfbLpf = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x012A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.TunLessVfbLpf),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn185 : 振动检测选择 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_vibsel = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x012C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.vibsel),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(2),
};



/****************************************************************************************************/
/*		Pn186 : 振动检测灵敏度 [%]																	*/
/****************************************************************************************************/
LONG	pncal_vibsens( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  Gprm.VibCheckLevel = KpiSpeedLevelCal( 30UL * Prm.vibnorm * Prm.vibsens / 100, 0 );
		  /* 設定レベルに変更が合った場合も最大最小をクリアする */
		  BpiResetMaxMinSpeedError( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_vibsens = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x012E,
/* 处理函数指针					*/	pncal_vibsens,
/* RAM地址						*/	&(Prm.vibsens),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(500),
};



/****************************************************************************************************/
/*		Pn187 : 振动检测值 [rpm]																	*/
/****************************************************************************************************/
LONG	pncal_vibnorm( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  Gprm.VibCheckLevel = KpiSpeedLevelCal( 30UL * Prm.vibnorm * Prm.vibsens / 100, 0 );
		  /* 設定レベルに変更が合った場合も最大最小をクリアする */
		  BpiResetMaxMinSpeedError( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_vibnorm = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0130,
/* 处理函数指针					*/	pncal_vibnorm,
/* RAM地址						*/	&(Prm.vibnorm),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn192 : 高级调谐过程中位置超调检出灵敏度(相对定位完成) [%]									*/
/****************************************************************************************************/
const	PRMDEF	pndef_ovserrdetlvl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0132,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ovserrdetlvl),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn193 : 探索最大增益时最大增益设置值 [0.1Hz]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_adatgmax = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0134,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.adatgmax),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(4000),
};



/****************************************************************************************************/
/*		Pn195 : 重力补偿值 [0.1%]																	*/
/****************************************************************************************************/
LONG	pncal_gcomptrq( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  GComptrq();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_gcomptrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0136,
/* 处理函数指针					*/	pncal_gcomptrq,
/* RAM地址						*/	&(Prm.gcomptrq),
/* 下限値						*/	(USHORT)(-1000),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn196 : 正向库伦摩擦补偿值 [0.1%]															*/
/****************************************************************************************************/
LONG	pncal_pqfrigcomp( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  PCombComptrq();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_pqfriqcomptrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0138,
/* 处理函数指针					*/	pncal_pqfrigcomp,
/* RAM地址						*/	&(Prm.pqfriqcomptrq),
/* 下限値						*/	(USHORT)(-1000),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn197 : 负向库伦摩擦补偿值 [0.1%]															*/
/****************************************************************************************************/
LONG	pncal_nqfrigcomp( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  NCombComptrq();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_nqfriqcomptrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x013A,
/* 处理函数指针					*/	pncal_nqfrigcomp,
/* RAM地址						*/	&(Prm.nqfriqcomptrq),
/* 下限値						*/	(USHORT)(-1000),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn198 : 粘性摩擦补偿值 [0.1%]																*/
/****************************************************************************************************/
LONG	pncal_vfrigcomp( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  VFrigComptrq();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_vfrigcomptrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x013C,
/* 处理函数指针					*/	pncal_vfrigcomp,
/* RAM地址						*/	&(Prm.vfrigcomptrq),
/* 下限値						*/	(USHORT)(-3000),
/* 上限値						*/	(USHORT)(3000),
};



/****************************************************************************************************/
/*		Pn199 : 补偿滞环速度 [rpm]																	*/
/****************************************************************************************************/
LONG	pncal_spdhys( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  HysSpd();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_spdhys = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x013E,
/* 处理函数指针					*/	pncal_spdhys,
/* RAM地址						*/	&(Prm.spdhys),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn200 : 位置指令源选择 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_prstsw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0140,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.prstsw),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0089),
};



/****************************************************************************************************/
/*		Pn201 : 外部脉冲输入类型 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_PulseType = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0142,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PulseType),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0004),
};



/****************************************************************************************************/
/*		Pn202 : 位置控制开关 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_posctrl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0144,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.posctrl),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0001),
};



/****************************************************************************************************/
/*		Pn203 : 指令脉冲输入倍率 [x1倍]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_MulFrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0146,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MulFrq),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn204 : 电子齿轮比分子(低16位) [－]															*/
/****************************************************************************************************/
LONG	pncal_ratb2l( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  KpxEgearCoeffDeal();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ratb2l = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0148,
/* 处理函数指针					*/	pncal_ratb2l,
/* RAM地址						*/	&(Prm.ratb2l),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0),
};



/****************************************************************************************************/
/*		Pn205 : 电子齿轮比分子(高16位) [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_ratb2h = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x014A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ratb2h),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(16384),
};



/****************************************************************************************************/
/*		Pn206 : 电子齿轮比分母(低16位) [－]															*/
/****************************************************************************************************/
LONG	pncal_rata2l( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  KpxEgearCoeffDeal();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_rata2l = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x014C,
/* 处理函数指针					*/	pncal_rata2l,
/* RAM地址						*/	&(Prm.rata2l),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(0),
};



/****************************************************************************************************/
/*		Pn207 : 电子齿轮比分母(高16位) [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_rata2h = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x014E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.rata2h),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(16384),
};



/****************************************************************************************************/
/*		Pn210 : 位置指令加减速滤波器偏置 [指令単位/s]												*/
/****************************************************************************************************/
LONG	pncal_expbias1( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalPcmdExpFilBias( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_expbias1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS_SPD },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0150,
/* 处理函数指针					*/	pncal_expbias1,
/* RAM地址						*/	&(Prm.expbias1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn211 : 位置指令低通滤波时间常数 [0.1ms]													*/
/****************************************************************************************************/
LONG	pncal_expfil( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalPcmdExpFilter( Prm.expfil, 1 );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_expfil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0152,
/* 处理函数指针					*/	pncal_expfil,
/* RAM地址						*/	&(Prm.expfil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(6550),
};



/****************************************************************************************************/
/*		Pn212 : 位置指令滑动平均滤波时间 [0.1ms]													*/
/****************************************************************************************************/
LONG	pncal_mafil( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalPcmdMoveAvergeFilter( Prm.mafil,1 );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mafil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0154,
/* 处理函数指针					*/	pncal_mafil,
/* RAM地址						*/	&(Prm.mafil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn220 : 齿隙补偿控制开关 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_cmctrlexsw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0156,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.cmctrlexsw),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0011),
};



/****************************************************************************************************/
/*		Pn221 : 齿隙补偿量(低16位) [0.1指令单位]													*/
/****************************************************************************************************/
LONG	pncal_blcm2l( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if ( SVFSEL_BLSH_COMMON_PROC )
		PcalBlshCompensateAmount( );
#endif
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_blcm2l = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0158,
/* 处理函数指针					*/	pncal_blcm2l,
/* RAM地址						*/	&(Prm.blcm2l),
/* 下限値						*/	(USHORT)(24288),
/* 上限値						*/	(USHORT)(41248),
};



/****************************************************************************************************/
/*		Pn222 : 齿隙补偿量(高16位) [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_blcm2h = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x015A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.blcm2h),
/* 下限値						*/	(USHORT)(-8),
/* 上限値						*/	(USHORT)(7),
};



/****************************************************************************************************/
/*		Pn223 : 齿隙补偿时间常数 [0.01ms]															*/
/****************************************************************************************************/
LONG	pncal_blfiltime( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if ( SVFSEL_BLSH_COMMON_PROC )
		PcalBlshCompensateTime( );
#endif
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_blfiltime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x015C,
/* 处理函数指针					*/	pncal_blfiltime,
/* RAM地址						*/	&(Prm.blfiltime),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn230 : 低频振动抑制选择 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_mdlsw_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x015E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.mdlsw_1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0002),
};



/****************************************************************************************************/
/*		Pn231 : 低频振动抑制功能自动调整选择 [－]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_mdlsw_2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0160,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.mdlsw_2),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0001),
};



/****************************************************************************************************/
/*		Pn232 : 低频振动检出灵敏度(相对定位完成) [0.1%]												*/
/****************************************************************************************************/
LONG	pncal_remdetw( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalRemVibrationMon( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_remdetw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0162,
/* 处理函数指针					*/	pncal_remdetw,
/* RAM地址						*/	&(Prm.remdetw),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(3000),
};



/****************************************************************************************************/
/*		Pn233 : 低频振动抑制1频率A [0.1Hz]															*/
/****************************************************************************************************/
LONG	pncal_mdlantfrq( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( MODELFOLLOW_CTRL != 0 )	/*<V043>*/

  PcalMfcModelControl( Prm.mdlgn, Prm.mdlzeta, Prm.mdlantfrq,

						  Prm.mdlresfrq, Prm.mdlvff, Prm.mdlptff, Prm.mdlntff, 0, 0);

#endif

	 RpiRegSetVibMfcTuningFrequency( Prm.mdlantfrq );

	 return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mdlantfrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0164,
/* 处理函数指针					*/	pncal_mdlantfrq,
/* RAM地址						*/	&(Prm.mdlantfrq),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(2500),
};



/****************************************************************************************************/
/*		Pn234 : 低频振动抑制1频率B [0.1Hz]															*/
/****************************************************************************************************/
LONG	pncal_mdlresfrq( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( MODELFOLLOW_CTRL != 0 )	/*<V043>*/

  PcalMfcModelControl( Prm.mdlgn, Prm.mdlzeta, Prm.mdlantfrq,

						  Prm.mdlresfrq, Prm.mdlvff, Prm.mdlptff, Prm.mdlntff, 0, 0);

#endif

	 return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mdlresfrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0166,
/* 处理函数指针					*/	pncal_mdlresfrq,
/* RAM地址						*/	&(Prm.mdlresfrq),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(2500),
};



/****************************************************************************************************/
/*		Pn235 : 低频振动抑制2频率 [0.1Hz]															*/
/****************************************************************************************************/
LONG	pncal_ff_frq( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( VIBSUPPRESS_FIL2 != 0 )	/*<V043>*/

  PcalPcmdAvffFilter( );

#endif

	 RpiRegSetMdlVibFreq2( Prm.ff_frq ) ;						 /* <V128> */

	 return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ff_frq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0168,
/* 处理函数指针					*/	pncal_ff_frq,
/* RAM地址						*/	&(Prm.ff_frq),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(2000),
};



/****************************************************************************************************/
/*		Pn236 : 低频振动抑制2补正 [%]																*/
/****************************************************************************************************/
LONG	pncal_ff_fil( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( VIBSUPPRESS_FIL2 != 0 )	/*<V043>*/

  PcalPcmdAvffFilter( );

#endif

	 RpiRegSetMdlVibFil2(Prm.ff_fil) ;									 /* <V128> */

	 return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_ff_fil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x016A,
/* 处理函数指针					*/	pncal_ff_fil,
/* RAM地址						*/	&(Prm.ff_fil),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn240 : 模型追踪控制选择 [－]																*/
/****************************************************************************************************/
LONG	pncal_mdlsw( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( MODELFOLLOW_CTRL != 0 )	/*<V043>*/

  PcalMfcModelControlSel();

#endif

#if( VIBSUPPRESS_FIL2 != 0 )	  /*<V043>*/

	PcalPcmdAvffFilterSel();

#endif

	return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mdlsw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x016C,
/* 处理函数指针					*/	pncal_mdlsw,
/* RAM地址						*/	&(Prm.mdlsw),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x1121),
};



/****************************************************************************************************/
/*		Pn241 : 模型追踪控制增益 [0.1/s]															*/
/****************************************************************************************************/
LONG	pncal_mdlgn( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( MODELFOLLOW_CTRL != 0 )	/*<V043>*/
		PcalMfcModelControl( Prm.mdlgn, Prm.mdlzeta, Prm.mdlantfrq,
								Prm.mdlresfrq, Prm.mdlvff, Prm.mdlptff, Prm.mdlntff, 0, 0);
#endif
		RpiRegSetOnePrmTuningFfLevel( Prm.mdlgn );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mdlgn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_SECINV },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x016E,
/* 处理函数指针					*/	pncal_mdlgn,
/* RAM地址						*/	&(Prm.mdlgn),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(20000),
};



/****************************************************************************************************/
/*		Pn242 : 模型追踪控制增益补正 [0.1%]															*/
/****************************************************************************************************/
LONG	pncal_mdlzeta( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( MODELFOLLOW_CTRL != 0 )	/*<V043>*/

  PcalMfcModelControl( Prm.mdlgn, Prm.mdlzeta, Prm.mdlantfrq,

						  Prm.mdlresfrq, Prm.mdlvff, Prm.mdlptff, Prm.mdlntff, 0, 0);

#endif

	 return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mdlzeta = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0170,
/* 处理函数指针					*/	pncal_mdlzeta,
/* RAM地址						*/	&(Prm.mdlzeta),
/* 下限値						*/	(USHORT)(500),
/* 上限値						*/	(USHORT)(2000),
};



/****************************************************************************************************/
/*		Pn243 : 模型追踪控制速度前馈增益 [0.1%]														*/
/****************************************************************************************************/
LONG	pncal_mdlvff( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( MODELFOLLOW_CTRL != 0 )	/*<V043>*/
		PcalMfcModelControl( Prm.mdlgn, Prm.mdlzeta, Prm.mdlantfrq,
								Prm.mdlresfrq, Prm.mdlvff, Prm.mdlptff, Prm.mdlntff, 0, 0);
#endif
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mdlvff = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0172,
/* 处理函数指针					*/	pncal_mdlvff,
/* RAM地址						*/	&(Prm.mdlvff),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn244 : 模型追踪控制偏置(正转方向) [0.1%]													*/
/****************************************************************************************************/
LONG	pncal_mdlptff( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( MODELFOLLOW_CTRL != 0 )	/*<V043>*/
		PcalMfcModelControl( Prm.mdlgn, Prm.mdlzeta, Prm.mdlantfrq,
								Prm.mdlresfrq, Prm.mdlvff, Prm.mdlptff, Prm.mdlntff, 0, 0);
#endif
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mdlptff = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0174,
/* 处理函数指针					*/	pncal_mdlptff,
/* RAM地址						*/	&(Prm.mdlptff),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn245 : 模型追踪控制偏置(反转方向) [0.1%]													*/
/****************************************************************************************************/
LONG	pncal_mdlntff( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( MODELFOLLOW_CTRL != 0 )	/*<V043>*/
		PcalMfcModelControl( Prm.mdlgn, Prm.mdlzeta, Prm.mdlantfrq,
								Prm.mdlresfrq, Prm.mdlvff, Prm.mdlptff, Prm.mdlntff, 0, 0);
#endif
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mdlntff = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0176,
/* 处理函数指针					*/	pncal_mdlntff,
/* RAM地址						*/	&(Prm.mdlntff),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn246 : 第2模型追踪控制增益 [0.1/s]															*/
/****************************************************************************************************/
LONG	pncal_mdlgn2( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( MODELFOLLOW_CTRL != 0 )	/*<V043>*/
		PcalMfcModelControl( Prm.mdlgn2, Prm.mdlzeta2, Prm.mdlantfrq,
								Prm.mdlresfrq, Prm.mdlvff, Prm.mdlptff, Prm.mdlntff, 0, 1);
#endif
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mdlgn2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_SECINV },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0178,
/* 处理函数指针					*/	pncal_mdlgn2,
/* RAM地址						*/	&(Prm.mdlgn2),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(20000),
};



/****************************************************************************************************/
/*		Pn247 : 第2模型追踪控制增益补正 [0.1%]														*/
/****************************************************************************************************/
LONG	pncal_mdlzeta2( ULONG Cmd, ULONG Data, ULONG Digit )
{
#if( MODELFOLLOW_CTRL != 0 )	/*<V043>*/
		PcalMfcModelControl( Prm.mdlgn2, Prm.mdlzeta2, Prm.mdlantfrq,
								Prm.mdlresfrq, Prm.mdlvff, Prm.mdlptff, Prm.mdlntff, 0, 1);
#endif
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_mdlzeta2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x017A,
/* 处理函数指针					*/	pncal_mdlzeta2,
/* RAM地址						*/	&(Prm.mdlzeta2),
/* 下限値						*/	(USHORT)(500),
/* 上限値						*/	(USHORT)(2000),
};



/****************************************************************************************************/
/*		Pn248 : 控制类开关 [－]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_mfctype = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x017C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.mfctype),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0011),
};



/****************************************************************************************************/
/*		Pn260 : NEAR信号宽度(低16位) [指令単位]														*/
/****************************************************************************************************/
LONG	pncal_nearlv2l( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.NearLevel = LONGOF( Prm.nearlv2l, Prm.nearlv2h );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_nearlv2l = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x017E,
/* 处理函数指针					*/	pncal_nearlv2l,
/* RAM地址						*/	&(Prm.nearlv2l),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(0),
};



/****************************************************************************************************/
/*		Pn261 : NEAR信号宽度(高16位) [－]															*/
/****************************************************************************************************/
LONG	pncal_nearlv2h( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.NearLevel = LONGOF( Prm.nearlv2l, Prm.nearlv2h );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_nearlv2h = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0180,
/* 处理函数指针					*/	pncal_nearlv2h,
/* RAM地址						*/	&(Prm.nearlv2h),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(16384),
};



/****************************************************************************************************/
/*		Pn262 : 位置到达范围(低16位) [指令単位]														*/
/****************************************************************************************************/
LONG	pncal_coinlv2l( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.CoinLevel = LONGOF( Prm.coinlv2l, Prm.coinlv2h );
		PcalRemVibrationMon( );
		PcalOverShootErrDetLvl( ); /* <V113> */
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_coinlv2l = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0182,
/* 处理函数指针					*/	pncal_coinlv2l,
/* RAM地址						*/	&(Prm.coinlv2l),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0),
};



/****************************************************************************************************/
/*		Pn263 : 位置到达范围(高16位) [－]															*/
/****************************************************************************************************/
LONG	pncal_coinlv2h( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.CoinLevel = LONGOF( Prm.coinlv2l, Prm.coinlv2h );
		PcalRemVibrationMon( );
		PcalOverShootErrDetLvl( ); /* <V113> */
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_coinlv2h = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0184,
/* 处理函数指针					*/	pncal_coinlv2h,
/* RAM地址						*/	&(Prm.coinlv2h),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(16384),
};



/****************************************************************************************************/
/*		Pn264 : 位置偏差最大容忍值(低16位) [指令単位]												*/
/****************************************************************************************************/
LONG	pncal_overlv2l( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.PerAlmLevel = LONGOF( Prm.overlv2l, Prm.overlv2h );
		Gprm.PerWrnLevel = MlibScalKxgain( Gprm.PerAlmLevel, Prm.overwrnlv, 100, NULL, -30 );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_overlv2l = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0186,
/* 处理函数指针					*/	pncal_overlv2l,
/* RAM地址						*/	&(Prm.overlv2l),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn265 : 位置偏差最大容忍值(高16位) [－]														*/
/****************************************************************************************************/
LONG	pncal_overlv2h( ULONG Cmd, ULONG Data, ULONG Digit )
{
	   Gprm.PerAlmLevel = LONGOF( Prm.overlv2l, Prm.overlv2h );
	   Gprm.PerWrnLevel = MlibScalKxgain( Gprm.PerAlmLevel, Prm.overwrnlv, 100, NULL, -30 );
	return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_overlv2h = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0188,
/* 处理函数指针					*/	pncal_overlv2h,
/* RAM地址						*/	&(Prm.overlv2h),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(16383),
};



/****************************************************************************************************/
/*		Pn266 : 位置偏差过大警告设定 [%]															*/
/****************************************************************************************************/
LONG	pncal_overwrnlv( ULONG Cmd, ULONG Data, ULONG Digit )
{
		Gprm.PerWrnLevel = MlibScalKxgain( Gprm.PerAlmLevel, Prm.overwrnlv, 100, NULL, -30 );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_overwrnlv = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x018A,
/* 处理函数指针					*/	pncal_overwrnlv,
/* RAM地址						*/	&(Prm.overwrnlv),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn267 : 伺服ON时位置偏差过大警报阀值 [指令単位]												*/
/****************************************************************************************************/
LONG	pncal_svonoverlv2l( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  Gprm.SvonPerAlmLevel = LONGOF( Prm.svonoverlv2l, Prm.svonoverlv2h );
		  Gprm.SvonPerWrnLevel = MlibScalKxgain( Gprm.SvonPerAlmLevel, Prm.svonoverwrnlv, 100, NULL, -30 );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_svonoverlv2l = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x018C,
/* 处理函数指针					*/	pncal_svonoverlv2l,
/* RAM地址						*/	&(Prm.svonoverlv2l),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn268 : 伺服ON时位置偏差过大警报阀值(高16位) [－]											*/
/****************************************************************************************************/
LONG	pncal_svonoverlv2h( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  Gprm.SvonPerAlmLevel = LONGOF( Prm.svonoverlv2l, Prm.svonoverlv2h );
		  Gprm.SvonPerWrnLevel = MlibScalKxgain( Gprm.SvonPerAlmLevel, Prm.svonoverwrnlv, 100, NULL, -30 );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_svonoverlv2h = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x018E,
/* 处理函数指针					*/	pncal_svonoverlv2h,
/* RAM地址						*/	&(Prm.svonoverlv2h),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(16383),
};



/****************************************************************************************************/
/*		Pn269 : 伺服ON时位置偏差过大警告阀值 [%]													*/
/****************************************************************************************************/
LONG	pncal_svonoverwrnlv( ULONG Cmd, ULONG Data, ULONG Digit )
{
	Gprm.SvonPerWrnLevel = MlibScalKxgain( Gprm.SvonPerAlmLevel, Prm.svonoverwrnlv, 100, NULL, -30 );
	return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_svonoverwrnlv = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0190,
/* 处理函数指针					*/	pncal_svonoverwrnlv,
/* RAM地址						*/	&(Prm.svonoverwrnlv),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn270 : 伺服ON时速度限制值 [min-1]															*/
/****************************************************************************************************/
LONG	pncal_svonspdlmtlv( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  Gprm.SvonSpdLmtLevel = KpiSpeedLevelCal( Prm.svonspdlmtlv*10UL, 0 );
		  Gprm.SvonSpdLmtValue = (Gprm.SvonSpdLmtLevel < 10)? 1 : (Gprm.SvonSpdLmtLevel / 10);
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_svonspdlmtlv = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0192,
/* 处理函数指针					*/	pncal_svonspdlmtlv,
/* RAM地址						*/	&(Prm.svonspdlmtlv),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn271 : 脉冲倍率选择开关 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_PulseSel = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0194,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PulseSel),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(3),
};



/****************************************************************************************************/
/*		Pn272 : 滞留脉冲清零模式 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_prstsw_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0196,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.prstsw_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(3),
};



/****************************************************************************************************/
/*		Pn273 : 位置偏差清除方式选择 [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_prstsw_2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0198,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.prstsw_2),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0002),
};



/****************************************************************************************************/
/*		Pn274 : 定位完成信号(/Coin)输出时序 [－]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_cmfilsw_3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x019A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.cmfilsw_3),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(2),
};



/****************************************************************************************************/
/*		Pn276 : 单向旋转多圈上限值 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_revlimit = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x019C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.revlimit),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(30000),
};



/****************************************************************************************************/
/*		Pn277 : 旋转圈数上限开启方向 [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_revovDir = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x019E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.revovDir),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0011),
};



/****************************************************************************************************/
/*		Pn278 : 单向旋转单圈上限值L [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_srevlimitL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01A0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.srevlimitL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn279 : 单向旋转单圈上限值H [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_srevlimitH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01A2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.srevlimitH),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn290 : 原点回归模式设定 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_orgmode = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01A4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.orgmode),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x33B4),
};



/****************************************************************************************************/
/*		Pn291 : 原点回归高速速度 [rpm]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_orgspdhight = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01A6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.orgspdhight),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(30000),
};



/****************************************************************************************************/
/*		Pn292 : 原点回归低速速度 [rpm]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_orgspdlow = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01A8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.orgspdlow),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(30000),
};



/****************************************************************************************************/
/*		Pn293 : 原点回归加减速时间 [ms]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_orgdecacc = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01AA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.orgdecacc),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(3000),
};



/****************************************************************************************************/
/*		Pn294 : 原点位置偏置L [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_orgoffsetL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01AC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.orgoffsetL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn295 : 原点位置偏置H [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_orgoffsetH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01AE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.orgoffsetH),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn296 : 绝对位置零点多圈值 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_orgMpos = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01B0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.orgMpos),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn297 : 绝对位置零点单圈值L [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_orgSposL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01B2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.orgSposL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn298 : 绝对位置零点单圈值H  [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_orgSposH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01B4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.orgSposH),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn299 : 原点回归超时设定 [ms]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_orgovtime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01B6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.orgovtime),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn29A : 原点回归多圈回归状态																*/
/****************************************************************************************************/
const	PRMDEF	pndef_orgstatus = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01B8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.orgstatus),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1),
};



/****************************************************************************************************/
/*		Pn300 : 速度指令源 [－]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_spdSource = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01BA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.spdSource),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(7),
};



/****************************************************************************************************/
/*		Pn301 : 速度指令方向 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_spdcmd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01BC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.spdcmd),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1),
};



/****************************************************************************************************/
/*		Pn302 : 速度指令低通滤波时间 [0.01ms]														*/
/****************************************************************************************************/
LONG	pncal_srfil( ULONG Cmd, ULONG Data, ULONG Digit )
{
		SpdCtrl.P.KVrfFil = MlibPcalKf1gain( Prm.srfil*10UL, Iprm.SvCycleUs, 0 );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_srfil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01BE,
/* 处理函数指针					*/	pncal_srfil,
/* RAM地址						*/	&(Prm.srfil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn304 : 内部速度0 [rpm]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_speed0 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01C0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.speed0),
/* 下限値						*/	(USHORT)(-10000),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn305 : 内部速度1 [rpm]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_speed1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01C2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.speed1),
/* 下限値						*/	(USHORT)(-10000),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn306 : 内部速度2 [rpm]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_speed2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01C4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.speed2),
/* 下限値						*/	(USHORT)(-10000),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn307 : 内部速度3 [rpm]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_speed3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01C6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.speed3),
/* 下限値						*/	(USHORT)(-10000),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn310 : 速度指令梯形加速时间 [ms]															*/
/****************************************************************************************************/
LONG	pncal_sfsacc( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalBaseSoftStartAcc( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_sfsacc = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01C8,
/* 处理函数指针					*/	pncal_sfsacc,
/* RAM地址						*/	&(Prm.sfsacc),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn311 : 速度指令梯形减速时间 [ms]															*/
/****************************************************************************************************/
LONG	pncal_sfsdec( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalBaseSoftStartDec( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_sfsdec = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01CA,
/* 处理函数指针					*/	pncal_sfsdec,
/* RAM地址						*/	&(Prm.sfsdec),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn312 : 速度指令梯形减速时间 [ms]															*/
/****************************************************************************************************/
LONG	pncal_sfsts( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalBaseSoftStartTs( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_sfsts = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01CC,
/* 处理函数指针					*/	pncal_sfsts,
/* RAM地址						*/	&(Prm.sfsts),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn313 : 零速箝位速度阀值 [rpm]																*/
/****************************************************************************************************/
LONG	pncal_clamp( ULONG Cmd, ULONG Data, ULONG Digit )
{
	Gprm.ZclampSpdLevel = KpiSpeedLevelCal( Prm.clamp*10UL, 0 );
	return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_clamp = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01CE,
/* 处理函数指针					*/	pncal_clamp,
/* RAM地址						*/	&(Prm.clamp),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn314 : 零速箝位补偿最大速度 [rpm]															*/
/****************************************************************************************************/
LONG	pncal_clampMaxSpd( ULONG Cmd, ULONG Data, ULONG Digit )
{
	Gprm.ZclampMaxSpd = KpiSpeedLevelCal( Prm.clampMaxSpd * 10UL, 0 );
	return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_clampMaxSpd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01D0,
/* 处理函数指针					*/	pncal_clampMaxSpd,
/* RAM地址						*/	&(Prm.clampMaxSpd),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn317 : 转动判断阈值 [rpm]																	*/
/****************************************************************************************************/
LONG	pncal_tgonlv( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  Gprm.TgonSpdLevel = KpiSpeedLevelCal( Prm.tgonlv * 10UL, 0 );
		  return( TRUE );  
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_tgonlv = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01D2,
/* 处理函数指针					*/	pncal_tgonlv,
/* RAM地址						*/	&(Prm.tgonlv),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn318 : 电机最高速度 [rpm]																	*/
/****************************************************************************************************/
LONG	pncal_MaxSpd( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  Iprm.MaxSpd = KpiSpeedLevelCal( Prm.MaxSpd * 10UL, 0 );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_MaxSpd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01D4,
/* 处理函数指针					*/	pncal_MaxSpd,
/* RAM地址						*/	&(Prm.MaxSpd),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn320 : 速度一致范围 [rpm]																	*/
/****************************************************************************************************/
LONG	pncal_vcmplv( ULONG Cmd, ULONG Data, ULONG Digit )
{
	Gprm.VcmpSpdLevel = KpiSpeedLevelCal( Prm.vcmplv*10UL, 0 );
	return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_vcmplv = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01D6,
/* 处理函数指针					*/	pncal_vcmplv,
/* RAM地址						*/	&(Prm.vcmplv),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn400 : 转矩控制开关1 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_b_prm400 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01D8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.b_prm400),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0047),
};



/****************************************************************************************************/
/*		Pn401 : 转矩指令2阶低通滤波器截止频率 [Hz]													*/
/****************************************************************************************************/
LONG	pncal_secfil( ULONG Cmd, ULONG Data, ULONG Digit )
{
	if( Prm.secfil >= 5000 )				/* フィルタ周波数 >= 5000Hz で無効					*/

	  {

		  Gprm.f.LpassFil2 = FALSE;			  /* ２次遅れフィルタ無効							  */

	   }

 /*----------------------------------------------------------------------------------------------*/

		PcalBaseTrqLpassFilter2( );					/* トルクフィルタＬＰＦ２パラメータ計算			*/

 /*----------------------------------------------------------------------------------------------*/

	  if( Prm.secfil < 5000 )				  /* フィルタ周波数 < 5000Hz で有効					  */

	   {

		   Gprm.f.LpassFil2 = TRUE;			   /* ２次遅れフィルタ有効							   */

		}

		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_secfil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01DA,
/* 处理函数指针					*/	pncal_secfil,
/* RAM地址						*/	&(Prm.secfil),
/* 下限値						*/	(USHORT)(100),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn402 : 转矩指令2阶低通滤波器Q値 [0.01]														*/
/****************************************************************************************************/
LONG	pncal_secq( ULONG Cmd, ULONG Data, ULONG Digit )
{
	PcalBaseTrqLpassFilter2( );					/* トルクフィルタＬＰＦ２パラメータ計算			*/
	return( TRUE ); 
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_secq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01DC,
/* 处理函数指针					*/	pncal_secq,
/* RAM地址						*/	&(Prm.secq),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn403 : 转矩控制开关2 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_trqcmddirtype = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01DE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.trqcmddirtype),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0001),
};



/****************************************************************************************************/
/*		Pn404 : 转矩指令滤波时间 [0.01ms]															*/
/****************************************************************************************************/
LONG	pncal_treffil( ULONG Cmd, ULONG Data, ULONG Digit )
{
		TrqFil.A.Ktrflpf = MlibPcalKf1gain( Prm.treffil*10UL, KPI_SACYCLEUS, 0 );
		TrqFil.P.Ktrflpf = MlibPcalKf1gain( Prm.treffil*10UL, KPI_SBCYCLEUS, 0 );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_treffil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01E0,
/* 处理函数指针					*/	pncal_treffil,
/* RAM地址						*/	&(Prm.treffil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn410 : 内部转矩指令1 [0.1%]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_intrqcmd1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01E2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.intrqcmd1),
/* 下限値						*/	(USHORT)(-5000),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn411 : 内部转矩指令2 [0.1%]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_intrqcmd2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01E4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.intrqcmd2),
/* 下限値						*/	(USHORT)(-5000),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn412 : 内部转矩指令3 [0.1%]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_intrqcmd3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01E6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.intrqcmd3),
/* 下限値						*/	(USHORT)(-5000),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn413 : 内部转矩指令4 [0.1%]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_intrqcmd4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01E8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.intrqcmd4),
/* 下限値						*/	(USHORT)(-5000),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn415 : 转矩控制模式时内部速度限制 [rpm]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_ntqspdlimt1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01EA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ntqspdlimt1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn416 : 转矩控制模式时内部速度限制 [rpm]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_ntqspdlimt2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01EC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ntqspdlimt2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn420 : 转矩到达设定值 [0.1%]																*/
/****************************************************************************************************/
LONG	pncal_torqcmd1( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  Gprm.TrqObjReach1 = KpiTorqueLevelCal( 10UL * Prm.torqcmd1, 1 );	  /* [0.1%] --> [15000/MaxTrq] */
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_torqcmd1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01EE,
/* 处理函数指针					*/	pncal_torqcmd1,
/* RAM地址						*/	&(Prm.torqcmd1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn421 : 转矩到达设定值 [0.1%]																*/
/****************************************************************************************************/
LONG	pncal_torqcmd2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  Gprm.TrqObjReach2 = KpiTorqueLevelCal( 10UL * Prm.torqcmd2, 1 );	  /* [0.1%] --> [15000/MaxTrq] */
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_torqcmd2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01F0,
/* 处理函数指针					*/	pncal_torqcmd2,
/* RAM地址						*/	&(Prm.torqcmd2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn422 : 转矩到达时间窗口 [ms]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_torqcmdtimewindow = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01F2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.torqcmdtimewindow),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn430 : 转矩控制开关1 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_trqcmddirtype1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01F4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.trqcmddirtype1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0011),
};



/****************************************************************************************************/
/*		Pn435 : Un00A监控滤波时间 [ms]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_monitortime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01F6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.monitortime),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(30000),
};



/****************************************************************************************************/
/*		Pn500 : 点动速度 [rpm]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_jogspd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	TRUE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01F8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.jogspd),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(3000),
};



/****************************************************************************************************/
/*		Pn502 : 程序JOG运行模式 [－]																*/
/****************************************************************************************************/
LONG	pncal_pjogsw( ULONG Cmd, ULONG Data, ULONG Digit )
{
		if( BoutV.CtrlMode.us[0] == CTRLMODE_PJOG && OpeReg.PjogState == 1 )
		{
		 return( FALSE );  /* プログラムＪＯＧ運転未完了  */
		}
		else
		{
		 PcalPjogSw();	 /* プログラムＪＯＧパラメータ計算 */
		 return( TRUE );
		}
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_pjogsw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01FA,
/* 处理函数指针					*/	pncal_pjogsw,
/* RAM地址						*/	&(Prm.pjogsw),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0005),
};



/****************************************************************************************************/
/*		Pn503 : 程序JOG移动距离 [指令単位]															*/
/****************************************************************************************************/
LONG	pncal_pjogdistl( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  if( BoutV.CtrlMode.us[0] == CTRLMODE_PJOG && OpeReg.PjogState == 1 )
		  {
		return( FALSE );  /* プログラムＪＯＧ運転未完了	 */
		  }
		  else
		  {
			  PcalPjogDistance();  /* プログラムＪＯＧパラメータ計算 */
			  return( TRUE );
		  }
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_pjogdistl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01FC,
/* 处理函数指针					*/	pncal_pjogdistl,
/* RAM地址						*/	&(Prm.pjogdistl),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(0),
};



/****************************************************************************************************/
/*		Pn504 : 程序JOG移动距离(高16位) [－]														*/
/****************************************************************************************************/
LONG	pncal_pjogdisth( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  if( BoutV.CtrlMode.us[0] == CTRLMODE_PJOG && OpeReg.PjogState == 1 )
		  {
		return( FALSE );  /* プログラムＪＯＧ運転未完了	 */
		  }
		  else
		  {
			  PcalPjogDistance();  /* プログラムＪＯＧパラメータ計算 */
			  return( TRUE );
		  }
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_pjogdisth = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x01FE,
/* 处理函数指针					*/	pncal_pjogdisth,
/* RAM地址						*/	&(Prm.pjogdisth),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(16384),
};



/****************************************************************************************************/
/*		Pn505 : 程序JOG加减速时间 [ms]																*/
/****************************************************************************************************/
LONG	pncal_pjogacctm( ULONG Cmd, ULONG Data, ULONG Digit )
{
		if( BoutV.CtrlMode.us[0] == CTRLMODE_PJOG && OpeReg.PjogState == 1 )
		{
		 return( FALSE );  /* プログラムＪＯＧ運転未完了  */
		}
		else
		{
		 PcalPjogAcctime();	 /* プログラムＪＯＧパラメータ計算 */
		 return( TRUE );
		}
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_pjogacctm = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0200,
/* 处理函数指针					*/	pncal_pjogacctm,
/* RAM地址						*/	&(Prm.pjogacctm),
/* 下限値						*/	(USHORT)(2),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn506 : 程序JOG等待时间 [ms]																*/
/****************************************************************************************************/
LONG	pncal_pjogwaittm( ULONG Cmd, ULONG Data, ULONG Digit )
{
		if( BoutV.CtrlMode.us[0] == CTRLMODE_PJOG && OpeReg.PjogState == 1 )
		{
		 return( FALSE );  /* プログラムＪＯＧ運転未完了  */
		}
		else
		{
		 PcalPjogWaitTime();  /* プログラムＪＯＧパラメータ計算 */
		 return( TRUE );
		}
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_pjogwaittm = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0202,
/* 处理函数指针					*/	pncal_pjogwaittm,
/* RAM地址						*/	&(Prm.pjogwaittm),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn507 : 程序JOG移动次数 [回]																*/
/****************************************************************************************************/
LONG	pncal_pjognum( ULONG Cmd, ULONG Data, ULONG Digit )
{
		if( BoutV.CtrlMode.us[0] == CTRLMODE_PJOG && OpeReg.PjogState == 1 )
		{
		 return( FALSE );  /* プログラムＪＯＧ運転未完了  */
		}
		else
		{
		 PcalPjogNum();	  /* プログラムＪＯＧパラメータ計算 */
		 return( TRUE );
		}
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_pjognum = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0204,
/* 处理函数指针					*/	pncal_pjognum,
/* RAM地址						*/	&(Prm.pjognum),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn508 : 程序JOG移动速度 [min-1]																*/
/****************************************************************************************************/
LONG	pncal_pjogrotspd( ULONG Cmd, ULONG Data, ULONG Digit )
{
		if( BoutV.CtrlMode.us[0] == CTRLMODE_PJOG && OpeReg.PjogState == 1 )
		{
		 return( FALSE );  /* プログラムＪＯＧ運転未完了  */
		}
		else
		{
		 PcalPjogRotspd();	/* プログラムＪＯＧパラメータ計算 */
		 return( TRUE );
		}
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_pjogrotspd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0206,
/* 处理函数指针					*/	pncal_pjogrotspd,
/* RAM地址						*/	&(Prm.pjogrotspd),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn510 : 电流内部信号触发																	*/
/****************************************************************************************************/
LONG	pncal_CurIntrig( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  InputCurSigParaReset();
		  return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_CurIntrig = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0208,
/* 处理函数指针					*/	pncal_CurIntrig,
/* RAM地址						*/	&(Prm.CurIntrig),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1),
};



/****************************************************************************************************/
/*		Pn511 : 电流内部信号类型																	*/
/****************************************************************************************************/
LONG	pncal_CurType( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  InputCurSigParaReset();
		  return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_CurType = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x020A,
/* 处理函数指针					*/	pncal_CurType,
/* RAM地址						*/	&(Prm.CurType),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1),
};



/****************************************************************************************************/
/*		Pn512 : 电流给定幅值 [0.1%]																	*/
/****************************************************************************************************/
LONG	pncal_CurAmp( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  InputCurSigParaReset();
		  return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_CurAmp = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x020C,
/* 处理函数指针					*/	pncal_CurAmp,
/* RAM地址						*/	&(Prm.CurAmp),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn513 : 电流给定频率 [Hz]																	*/
/****************************************************************************************************/
LONG	pncal_CurFreq( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  InputCurSigParaReset();
		  return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_CurFreq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x020E,
/* 处理函数指针					*/	pncal_CurFreq,
/* RAM地址						*/	&(Prm.CurFreq),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(4000),
};



/****************************************************************************************************/
/*		Pn514 : 电流给定偏移量 [0.1%]																*/
/****************************************************************************************************/
LONG	pncal_CurOffSet( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  InputCurSigParaReset();
		  return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_CurOffSet = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0210,
/* 处理函数指针					*/	pncal_CurOffSet,
/* RAM地址						*/	&(Prm.CurOffSet),
/* 下限値						*/	(USHORT)(-1000),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn515 : 速度内部信号触发																	*/
/****************************************************************************************************/
LONG	pncal_SpdIntrig( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  InputSpdSigParaReset();
		  return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_SpdIntrig = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0212,
/* 处理函数指针					*/	pncal_SpdIntrig,
/* RAM地址						*/	&(Prm.SpdIntrig),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1),
};



/****************************************************************************************************/
/*		Pn516 : 速度内部信号类型																	*/
/****************************************************************************************************/
LONG	pncal_SpdType( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  InputSpdSigParaReset();
		  return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_SpdType = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0214,
/* 处理函数指针					*/	pncal_SpdType,
/* RAM地址						*/	&(Prm.SpdType),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1),
};



/****************************************************************************************************/
/*		Pn517 : 速度给定幅值 [0.1rpm]																*/
/****************************************************************************************************/
LONG	pncal_SpdAmp( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  InputSpdSigParaReset();
		  return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_SpdAmp = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0216,
/* 处理函数指针					*/	pncal_SpdAmp,
/* RAM地址						*/	&(Prm.SpdAmp),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(30000),
};



/****************************************************************************************************/
/*		Pn518 : 速度给定频率 [Hz]																	*/
/****************************************************************************************************/
LONG	pncal_SpdFreq( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  InputSpdSigParaReset();
		  return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_SpdFreq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0218,
/* 处理函数指针					*/	pncal_SpdFreq,
/* RAM地址						*/	&(Prm.SpdFreq),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(6000),
};



/****************************************************************************************************/
/*		Pn519 : 速度给定偏移量 [0.1rpm]																*/
/****************************************************************************************************/
LONG	pncal_SpdOffSet( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  InputSpdSigParaReset();
		  return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_SpdOffSet = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x021A,
/* 处理函数指针					*/	pncal_SpdOffSet,
/* RAM地址						*/	&(Prm.SpdOffSet),
/* 下限値						*/	(USHORT)(-30000),
/* 上限値						*/	(USHORT)(30000),
};



/****************************************************************************************************/
/*		Pn520 : 堵转电流硬保护设定 [0.1%]															*/
/****************************************************************************************************/
LONG	pncal_CurLimtHard( ULONG Cmd, ULONG Data, ULONG Digit )
{
		 IprmcalMotorStall( );
		 return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_CurLimtHard = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x021C,
/* 处理函数指针					*/	pncal_CurLimtHard,
/* RAM地址						*/	&(Prm.CurLimtHard),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn521 : 堵转硬保护时间设定 [ms]																*/
/****************************************************************************************************/
LONG	pncal_LimtTHard( ULONG Cmd, ULONG Data, ULONG Digit )
{
		 IprmcalMotorStall( );
		 return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_LimtTHard = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x021E,
/* 处理函数指针					*/	pncal_LimtTHard,
/* RAM地址						*/	&(Prm.LimtTHard),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn522 : 堵转硬保护转速设定 [0.1rpm]															*/
/****************************************************************************************************/
LONG	pncal_SpdLimtHard( ULONG Cmd, ULONG Data, ULONG Digit )
{
		 IprmcalMotorStall( );
		 return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_SpdLimtHard = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0220,
/* 处理函数指针					*/	pncal_SpdLimtHard,
/* RAM地址						*/	&(Prm.SpdLimtHard),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn523 : 堵转电流软保护设定 [0.1%]															*/
/****************************************************************************************************/
LONG	pncal_CurLimtSoft( ULONG Cmd, ULONG Data, ULONG Digit )
{
		 IprmcalMotorStall( );
		 return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_CurLimtSoft = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0222,
/* 处理函数指针					*/	pncal_CurLimtSoft,
/* RAM地址						*/	&(Prm.CurLimtSoft),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn524 : 堵转软保护时间设定 [ms]																*/
/****************************************************************************************************/
LONG	pncal_LimtTSoft( ULONG Cmd, ULONG Data, ULONG Digit )
{
		 IprmcalMotorStall( );
		 return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_LimtTSoft = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0224,
/* 处理函数指针					*/	pncal_LimtTSoft,
/* RAM地址						*/	&(Prm.LimtTSoft),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn525 : 堵转软保护转速设定 [0.1rpm]															*/
/****************************************************************************************************/
LONG	pncal_SpdLimtSoft( ULONG Cmd, ULONG Data, ULONG Digit )
{
		 IprmcalMotorStall( );
		 return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_SpdLimtSoft = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0226,
/* 处理函数指针					*/	pncal_SpdLimtSoft,
/* RAM地址						*/	&(Prm.SpdLimtSoft),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn526 : 堵转保护开启																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_StallEn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0228,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.StallEn),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1),
};



/****************************************************************************************************/
/*		Pn527 : 预留参数7																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn527 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x022A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn527),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn528 : 预留参数8																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn528 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x022C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn528),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn529 : 预留参数9																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn529 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x022E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn529),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn530 : 预留参数10																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn530 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0230,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn530),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn531 : 预留参数11																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn531 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0232,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn531),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn532 : 预留参数12																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn532 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0234,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn532),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn533 : 预留参数13																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn533 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0236,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn533),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn534 : 预留参数14																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn534 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0238,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn534),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn535 : 预留参数15																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn535 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x023A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn535),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn536 : 预留参数16																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn536 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x023C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn536),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn537 : 预留参数17																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn537 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x023E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn537),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn538 : 预留参数18																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn538 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0240,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn538),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn539 : 预留参数19																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn539 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0242,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn539),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn540 : 预留参数20																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn540 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0244,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn540),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn541 : 预留参数21																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn541 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0246,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn541),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn542 : 预留参数22																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn542 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0248,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn542),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn543 : 预留参数23																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn543 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x024A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn543),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn544 : 预留参数24																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn544 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x024C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn544),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn545 : 预留参数25																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn545 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x024E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn545),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn546 : 预留参数26																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn546 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0250,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn546),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn547 : 预留参数27																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn547 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0252,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn547),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn548 : 预留参数28																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn548 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0254,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn548),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn549 : 预留参数29																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn549 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0256,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn549),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn550 : 预留参数30																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn550 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0258,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn550),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn551 : 预留参数31																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn551 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x025A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn551),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn552 : 预留参数32																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn552 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x025C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn552),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn553 : 预留参数33																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn553 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x025E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn553),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn554 : 预留参数34																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn554 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0260,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn554),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn555 : 预留参数35																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn555 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0262,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn555),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn556 : 预留参数36																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn556 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0264,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn556),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn557 : 预留参数37																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn557 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0266,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn557),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn558 : 预留参数38																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn558 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0268,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn558),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn559 : 预留参数39																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn559 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x026A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn559),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn560 : MIT_Volmax																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Volmax = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x026C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Volmax),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn561 : MIT_Volmin																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Volmin = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x026E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Volmin),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn562 : CAN超时时间																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_CANTimeOut = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0270,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.CANTimeOut),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn563 : MIT_Curmax																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Curmax = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0272,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Curmax),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn564 : MIT_Curmin																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Curmin = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0274,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Curmin),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn565 : 加速度设定																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_AccRads = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0276,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AccRads),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(2000),
};



/****************************************************************************************************/
/*		Pn566 : Kt转矩系数调整使能																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_KtSetEn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0278,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.KtSetEn),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1),
};



/****************************************************************************************************/
/*		Pn567 : Kt转矩系数修正值																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_KtSet = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x027A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.KtSet),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn568 : 位置环Kp [1e-5]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_KpPos = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x027C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.KpPos),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn569 : 位置环Kd [1e-5]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_KdPos = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x027E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.KdPos),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn570 : 速度环Kp [1e-5]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_KpSpd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0280,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.KpSpd),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn571 : 速度环Ki [1e-5]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_KiSpd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0282,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.KiSpd),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn572 : 电流环Kp [1e-4]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_KpCur = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0284,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.KpCur),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn573 : 电流环Ki [1e-1]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_KiCur = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0286,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.KiCur),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn574 : MIT_KpMax																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_KpMax = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0288,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_KpMax),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn575 : MIT_KpMin																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_KpMin = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x028A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_KpMin),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn576 : MIT_KdMax																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_KdMax = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x028C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_KdMax),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn577 : MIT_KdMin																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_KdMin = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x028E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_KdMin),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn578 : MIT_Trefmax																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Trefmax = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0290,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Trefmax),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn579 : MIT_Trefmin																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Trefmin = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0292,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Trefmin),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn580 : MIT_Posmax																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Posmax = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0294,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Posmax),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn581 : MIT_Posmin																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Posmin = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0296,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Posmin),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn582 : MIT_Spdmax																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Spdmax = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0298,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Spdmax),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn583 : MIT_Spdmin																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Spdmin = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x029A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Spdmin),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn584 : 电机编码器单圈调零补偿L																*/
/****************************************************************************************************/
const	PRMDEF	pndef_PosAOffSetL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x029C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PosAOffSetL),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn585 : 电机编码器单圈调零补偿H																*/
/****************************************************************************************************/
const	PRMDEF	pndef_PosAOffSetH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x029E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PosAOffSetH),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn586 : CAN协议选择																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_CANMIT = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02A0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.CANMIT),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1),
};



/****************************************************************************************************/
/*		Pn587 : MIT转矩前馈																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Trq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02A2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Trq),
/* 下限値						*/	(USHORT)(-1700),
/* 上限値						*/	(USHORT)(1700),
};



/****************************************************************************************************/
/*		Pn588 : MIT给定角度																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Sitam = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02A4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Sitam),
/* 下限値						*/	(USHORT)(-1257),
/* 上限値						*/	(USHORT)(1257),
};



/****************************************************************************************************/
/*		Pn589 : MIT给定角速度																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_WmRef = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02A6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_WmRef),
/* 下限値						*/	(USHORT)(-4400),
/* 上限値						*/	(USHORT)(4400),
};



/****************************************************************************************************/
/*		Pn58A : MIT位置输出滤波时间常数 [0.01ms]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_PosFil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02A8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_PosFil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn58B : MIT转矩指令滤波时间常数 [0.01ms]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Tref = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02AA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Tref),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn590 : MIT Kp系数																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Kp = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02AC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Kp),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(50000),
};



/****************************************************************************************************/
/*		Pn591 : MIT Kd系数																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_Kd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02AE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_Kd),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(500),
};



/****************************************************************************************************/
/*		Pn592 : 减速机分子																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_RateA = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02B0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_RateA),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn593 : 减速机分母																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_MIT_RateB = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02B2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MIT_RateB),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn594 : 负载编码器多圈调零补偿																*/
/****************************************************************************************************/
const	PRMDEF	pndef_MutiBOffSet = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02B4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MutiBOffSet),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn595 : 负载编码器单圈调零补偿L																*/
/****************************************************************************************************/
const	PRMDEF	pndef_PosBOffSetL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02B6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PosBOffSetL),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn596 : 负载编码器单圈调零补偿H																*/
/****************************************************************************************************/
const	PRMDEF	pndef_PosBOffSetH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02B8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PosBOffSetH),
/* 下限値						*/	(USHORT)(-32768),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn597 : ICHAUS上电故障开启																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn597 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02BA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn597),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1),
};



/****************************************************************************************************/
/*		Pn598 : 编码器上电检测延时时间																*/
/****************************************************************************************************/
const	PRMDEF	pndef_EncDelay = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02BC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.EncDelay),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn599 : 负载编码器单圈线性位置补偿方案														*/
/****************************************************************************************************/
const	PRMDEF	pndef_Pn599 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02BE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Pn599),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1),
};



/****************************************************************************************************/
/*		Pn600 : 开关量输入信号X滤波时间 [ms]														*/
/****************************************************************************************************/
LONG	pncal_XFilTime( ULONG Cmd, ULONG Data, ULONG Digit )
{
			  Gprm.XFilterTime = Prm.XFilTime * 4;
			  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_XFilTime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02C0,
/* 处理函数指针					*/	pncal_XFilTime,
/* RAM地址						*/	&(Prm.XFilTime),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(3000),
};



/****************************************************************************************************/
/*		Pn601 : 开关量1输入配置 [－]																*/
/****************************************************************************************************/
LONG	pncal_insel1( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  DISeqInput1Map_Init( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_insel1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02C2,
/* 处理函数指针					*/	pncal_insel1,
/* RAM地址						*/	&(Prm.insel1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0x112F),
};



/****************************************************************************************************/
/*		Pn602 : 开关量2输入配置 [－]																*/
/****************************************************************************************************/
LONG	pncal_insel2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  DISeqInput2Map_Init( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_insel2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02C4,
/* 处理函数指针					*/	pncal_insel2,
/* RAM地址						*/	&(Prm.insel2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0x112F),
};



/****************************************************************************************************/
/*		Pn603 : 开关量3输入配置 [－]																*/
/****************************************************************************************************/
LONG	pncal_insel3( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  DISeqInput3Map_Init( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_insel3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02C6,
/* 处理函数指针					*/	pncal_insel3,
/* RAM地址						*/	&(Prm.insel3),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0x112F),
};



/****************************************************************************************************/
/*		Pn604 : 开关量4输入配置 [－]																*/
/****************************************************************************************************/
LONG	pncal_insel4( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  DISeqInput4Map_Init( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_insel4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02C8,
/* 处理函数指针					*/	pncal_insel4,
/* RAM地址						*/	&(Prm.insel4),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0x112F),
};



/****************************************************************************************************/
/*		Pn611 : 开关量1输出配置 [－]																*/
/****************************************************************************************************/
LONG	pncal_outsel1( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  DISeqOutput1Map_Init( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_outsel1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02CA,
/* 处理函数指针					*/	pncal_outsel1,
/* RAM地址						*/	&(Prm.outsel1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0x112F),
};



/****************************************************************************************************/
/*		Pn612 : 开关量2输出配置 [－]																*/
/****************************************************************************************************/
LONG	pncal_outsel2( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  DISeqOutput2Map_Init( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_outsel2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02CC,
/* 处理函数指针					*/	pncal_outsel2,
/* RAM地址						*/	&(Prm.outsel2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0x112F),
};



/****************************************************************************************************/
/*		Pn620 : 模拟量AI1低通滤波时间 [0.01ms]														*/
/****************************************************************************************************/
LONG	pncal_AI1treffil( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  AI1LPFilterInit( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_AI1treffil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02CE,
/* 处理函数指针					*/	pncal_AI1treffil,
/* RAM地址						*/	&(Prm.AI1treffil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn621 : 模拟量AI2低通滤波时间 [0.01ms]														*/
/****************************************************************************************************/
LONG	pncal_AI2treffil( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  AI2LPFilterInit( );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_AI2treffil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02D0,
/* 处理函数指针					*/	pncal_AI2treffil,
/* RAM地址						*/	&(Prm.AI2treffil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn622 : 模拟量AI1硬件漂移矫正 [0.001V]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_AI1Offset = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	3,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02D2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AI1Offset),
/* 下限値						*/	(USHORT)(-5000),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn623 : 模拟量AI2硬件漂移矫正 [0.001V]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_AI2Offset = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	3,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02D4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AI2Offset),
/* 下限値						*/	(USHORT)(-5000),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn624 : 模拟量AI1增益 [%]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_AI1Gain = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02D6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AI1Gain),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(500),
};



/****************************************************************************************************/
/*		Pn625 : 模拟量AI2增益 [%]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_AI2Gain = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02D8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AI2Gain),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(500),
};



/****************************************************************************************************/
/*		Pn626 : 模拟量AI1零点阈值 [0.001V]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_AI1Zero = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	3,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02DA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AI1Zero),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn627 : 模拟量AI2零点阈值 [0.001V]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_AI2Zero = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	3,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02DC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AI2Zero),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn630 : 虚拟输入端子(X)状态给定 [－]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_VirDI = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02DE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.VirDI),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x01FF),
};



/****************************************************************************************************/
/*		Pn631 : 虚拟输出端子(Y)状态给定 [－]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_VirDO = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02E0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.VirDO),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x003F),
};



/****************************************************************************************************/
/*		Pn632 : EtherCat探针1(X5)滤波时间 [12.5ns]													*/
/****************************************************************************************************/
LONG	pncal_Trobe1Filtime( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  ASIC_WR( MREG_Addr0071, Prm.Trobe1Filtime );
			  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_Trobe1Filtime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02E2,
/* 处理函数指针					*/	pncal_Trobe1Filtime,
/* RAM地址						*/	&(Prm.Trobe1Filtime),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn633 : EtherCat探针2(X6)滤波时间 [12.5ns]													*/
/****************************************************************************************************/
LONG	pncal_Trobe2Filtime( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  ASIC_WR( MREG_Addr0072, Prm.Trobe2Filtime );
			  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_Trobe2Filtime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02E4,
/* 处理函数指针					*/	pncal_Trobe2Filtime,
/* RAM地址						*/	&(Prm.Trobe2Filtime),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn702 : 惯量辨识可动范围 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_AATDist = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02E6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AATDist),
/* 下限値						*/	(USHORT)(5),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn705 : 惯量辨识初始值 [%]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PnB24 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02E8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PnB24),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(20000),
};



/****************************************************************************************************/
/*		Pn706 : 惯量辨识中振动检出水平(旋转) [rpm]													*/
/****************************************************************************************************/
LONG	pncal_JstVibValve( ULONG Cmd, ULONG Data, ULONG Digit )
{
			Gprm.JstVibCheckLevel = KpiSpeedLevelCal( Prm.JstVibValve * 10UL, 0 );
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_JstVibValve = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x02EA,
/* 处理函数指针					*/	pncal_JstVibValve,
/* RAM地址						*/	&(Prm.JstVibValve),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn710 : 在线参数辨识开关 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_Estimatesw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Estimatesw),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0001),
};



/****************************************************************************************************/
/*		Pn711 : 在线参数辨识时间 [s]																*/
/****************************************************************************************************/
LONG	pncal_EstimateTime( ULONG Cmd, ULONG Data, ULONG Digit )
{
			  EstimateTimeUpdate();
			  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_EstimateTime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x02EC,
/* 处理函数指针					*/	pncal_EstimateTime,
/* RAM地址						*/	&(Prm.EstimateTime),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn712 : 在线参数辨识速度阈值 [rpm]															*/
/****************************************************************************************************/
LONG	pncal_EstimateSpd( ULONG Cmd, ULONG Data, ULONG Digit )
{
			  EstimateSpdUpdate();
			  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_EstimateSpd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x02EE,
/* 处理函数指针					*/	pncal_EstimateSpd,
/* RAM地址						*/	&(Prm.EstimateSpd),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(500),
};



/****************************************************************************************************/
/*		Pn713 : 在线参数辨识收敛增益 [Hz]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_EstimateGain = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x02F0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.EstimateGain),
/* 下限値						*/	(USHORT)(500),
/* 上限値						*/	(USHORT)(2000),
};



/****************************************************************************************************/
/*		Pn715 : 负载转矩观测器开关 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_TlObssw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02F2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.TlObssw),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0001),
};



/****************************************************************************************************/
/*		Pn716 : 负载转矩观测器惯量比 [%]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_TlObsIntero = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02F4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.TlObsIntero),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn717 : 负载转矩观测器粘滞摩擦系数 [×10^-4N·m/rad/s]										*/
/****************************************************************************************************/
const	PRMDEF	pndef_TlObsfriction = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02F6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.TlObsfriction),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(50000),
};



/****************************************************************************************************/
/*		Pn718 : 负载转矩观测器增益 [%]																*/
/****************************************************************************************************/
LONG	pncal_TlObsGain( ULONG Cmd, ULONG Data, ULONG Digit )
{
			  TLObs_Gain();
			  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_TlObsGain = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02F8,
/* 处理函数指针					*/	pncal_TlObsGain,
/* RAM地址						*/	&(Prm.TlObsGain),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn719 : 负载转矩观测器低通滤波器 [ms]														*/
/****************************************************************************************************/
LONG	pncal_TlObsLowfilt( ULONG Cmd, ULONG Data, ULONG Digit )
{
			  TLObs_TlFilo();
			  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_TlObsLowfilt = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x02FA,
/* 处理函数指针					*/	pncal_TlObsLowfilt,
/* RAM地址						*/	&(Prm.TlObsLowfilt),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn720 : 扫频开始频率 [Hz]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_swpminfrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x02FC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.swpminfrq),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn721 : 扫频结束频率 [Hz]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_swpmaxfrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x02FE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.swpmaxfrq),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn722 : 检出共振频率下限值 [Hz]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_detfrqlmt = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0300,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.detfrqlmt),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		Pn723 : 扫描转矩指令振幅 [%]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_ezffttrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0302,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ezffttrq),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(800),
};



/****************************************************************************************************/
/*		Pn724 : 与FFT相关的功能开关 [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_ezfftsw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0304,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ezfftsw),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x2742),
};



/****************************************************************************************************/
/*		Pn740 : 速度脉动补偿开关 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompSw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0306,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompSw),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0011),
};



/****************************************************************************************************/
/*		Pn741 : 速度脉动补偿有效速度 [rpm]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompSpd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0308,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompSpd),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		Pn742 : 速度脉动补偿增益 [%]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompGain = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x030A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompGain),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn743 : 速度脉动补偿第1成分频率(相对电角度) [-]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompFreq1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x030C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompFreq1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn744 : 速度脉动补偿第1成分振幅値 [0.1%]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompTrq1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x030E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompTrq1),
/* 下限値						*/	(USHORT)(-100),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn745 : 速度脉动补偿第1成分位相 [deg]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompPhase1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0310,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompPhase1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(360),
};



/****************************************************************************************************/
/*		Pn746 : 速度脉动补偿第2成分频率(相对电角度) [-]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompFreq2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0312,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompFreq2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn747 : 速度脉动补偿第2成分振幅値 [0.1%]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompTrq2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0314,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompTrq2),
/* 下限値						*/	(USHORT)(-100),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn748 : 速度脉动补偿第2成分位相 [deg]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompPhase2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0316,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompPhase2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(360),
};



/****************************************************************************************************/
/*		Pn749 : 速度脉动补偿第3成分频率(相对电角度) [-]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompFreq3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0318,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompFreq3),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn74A : 速度脉动补偿第3成分振幅値 [0.1%]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompTrq3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x031A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompTrq3),
/* 下限値						*/	(USHORT)(-100),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn74B : 速度脉动补偿第3成分位相 [deg]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompPhase3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x031C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompPhase3),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(360),
};



/****************************************************************************************************/
/*		Pn74C : 速度脉动补偿第4成分频率(相对电角度) [-]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompFreq4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x031E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompFreq4),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn74D : 速度脉动补偿第4成分振幅値 [0.1%]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompTrq4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0320,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompTrq4),
/* 下限値						*/	(USHORT)(-100),
/* 上限値						*/	(USHORT)(100),
};



/****************************************************************************************************/
/*		Pn74E : 速度脉动补偿第4成分位相 [deg]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_RippleCompPhase4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER2,
/* EEPROM地址					*/	0x0322,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RippleCompPhase4),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(360),
};



/****************************************************************************************************/
/*		Pn755 : 弱磁控制功能开关 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_WearkSw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0324,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.WearkSw),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0x0001),
};



/****************************************************************************************************/
/*		Pn756 : 弱磁控制回路比例增益 [Hz]															*/
/****************************************************************************************************/
LONG	pncal_kv( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalVFBKp( Prm.kv, Prm.tv );
		PcalVFBKi( Prm.kv );

  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_kv = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0326,
/* 处理函数指针					*/	pncal_kv,
/* RAM地址						*/	&(Prm.kv),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn757 : 弱磁控制回路积分时间常数 [us]														*/
/****************************************************************************************************/
LONG	pncal_tv( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalVFBKp( Prm.kv, Prm.tv );

  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_tv = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_US },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0328,
/* 处理函数指针					*/	pncal_tv,
/* RAM地址						*/	&(Prm.tv),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn758 : 弱磁控制回路积分极限 [%]															*/
/****************************************************************************************************/
LONG	pncal_idlim( ULONG Cmd, ULONG Data, ULONG Digit )
{

	 PcalVFBKiLim( );
	  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_idlim = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x032A,
/* 处理函数指针					*/	pncal_idlim,
/* RAM地址						*/	&(Prm.idlim),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(200),
};



/****************************************************************************************************/
/*		Pn759 : 弱磁控制电圧指令阈值 [%]															*/
/****************************************************************************************************/
LONG	pncal_vmax( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  PcalIdrefLimTerm1( Prm.vmax, Prm.vmaxid );
		  WeakenField.VMax = (ULONG)Prm.vmax * 8192 / 100;
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_vmax = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x032C,
/* 处理函数指针					*/	pncal_vmax,
/* RAM地址						*/	&(Prm.vmax),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(150),
};



/****************************************************************************************************/
/*		Pn75A : 弱磁控制时最大弱磁电流 [%]															*/
/****************************************************************************************************/
LONG	pncal_vmaxid( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalIdrefLimTerm1( Prm.vmax, Prm.vmaxid );

  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_vmaxid = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x032E,
/* 处理函数指针					*/	pncal_vmaxid,
/* RAM地址						*/	&(Prm.vmaxid),
/* 下限値						*/	(USHORT)(50),
/* 上限値						*/	(USHORT)(150),
};



/****************************************************************************************************/
/*		Pn75B : 弱磁控制时DC电压滤波时间 [0.1ms]													*/
/****************************************************************************************************/
LONG	pncal_vpnavg( ULONG Cmd, ULONG Data, ULONG Digit )
{
		WeakenField.VdcAvgCnt = ( KPI_SCANB_MS( Prm.vpnavg ) / 20 );

  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_vpnavg = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0330,
/* 处理函数指针					*/	pncal_vpnavg,
/* RAM地址						*/	&(Prm.vpnavg),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn77F : 外部电源检测开关 [-]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_poweroffchk = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0332,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.poweroffchk),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0x0111),
};



/****************************************************************************************************/
/*		Pn780 : 外部电源检测滤波时间 [ms]															*/
/****************************************************************************************************/
LONG	pncal_powerofffiltime( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PowerOffCheckTime();
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_powerofffiltime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0334,
/* 处理函数指针					*/	pncal_powerofffiltime,
/* RAM地址						*/	&(Prm.powerofffiltime),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn781 : 过压检测水平 [V]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_ovlvl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_VOLTAGE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0336,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ovlvl),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn782 : 再生电压阀值 [V]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_regonlvl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_VOLTAGE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0338,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.regonlvl),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn783 : 再生关闭滞环宽度 [V]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_regoffhys = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_VOLTAGE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x033A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.regoffhys),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(50),
};



/****************************************************************************************************/
/*		Pn784 : 主回路欠压检测值 [V]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_uvlvl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_VOLTAGE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x033C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.uvlvl),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn785 : 主回路欠压检测时间 [ms]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_uvfil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x033E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.uvfil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(2000),
};



/****************************************************************************************************/
/*		Pn786 : 主回路欠压警告检测值 [V]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_UvWrnLvl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_VOLTAGE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0340,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.UvWrnLvl),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		Pn788 : 电机最高转速微调 [100rpm]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_MaxspdTun = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0342,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MaxspdTun),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(2),
};



/****************************************************************************************************/
/*		Pn78E : ICMU编码器开关 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Icmu = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0344,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Icmu),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn78F : 磁编码器控制开关 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_PosJump = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0346,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PosJump),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn790 : 电机型号 [－]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_MotorNum = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0348,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MotorNum),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn791 : 编码器类型 [－]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_EncoderType = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x034A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.EncoderType),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(15),
};



/****************************************************************************************************/
/*		Pn792 : 编码器零位 [°]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_EncZeroPhase = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x034C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.EncZeroPhase),
/* 下限値						*/	(USHORT)(-360),
/* 上限値						*/	(USHORT)(360),
};



/****************************************************************************************************/
/*		Pn793 : 位置传感器分辨率 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_PosOutputs2l = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x034E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PosOutputs2l),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0),
};



/****************************************************************************************************/
/*		Pn794 : 位置传感器分辨率(高16位） [－]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_PosOutputs2h = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0350,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PosOutputs2h),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(256),
};



/****************************************************************************************************/
/*		Pn795 : 增量式编码器控制开关 [-]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_IncEncBit = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0352,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.IncEncBit),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0111),
};



/****************************************************************************************************/
/*		Pn79D : 厂家测试用标志 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_FaTestControl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_LINEAR | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.FaTestControl),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn79E : 整机/单板测试模式密匙 [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_Testpassword = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0354,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Testpassword),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn79F : 厂家密码 [－]																		*/
/****************************************************************************************************/
LONG	pncal_password( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  if( Prm.password == USR2_PASWRD )					  /* 用户2密码							*/
		  {
			  PopMsg.AccsLvl = ACCLVL_USER2;
			  SrlMsg.AccsLvl = ACCLVL_USER2;
			  UsbMsg.AccsLvl = ACCLVL_USER2;
			  OpeReg.AccLevel = REG_ACCLVL_USER2;
		  }
		  else if( Prm.password == SYS_PASWRD )				  /* 系统密码							*/
		  {
			  PopMsg.AccsLvl = ACCLVL_SYSTEM;
			  SrlMsg.AccsLvl = ACCLVL_SYSTEM;
			  UsbMsg.AccsLvl = ACCLVL_SYSTEM;
			  OpeReg.AccLevel = REG_ACCLVL_SYSTEM;
		  }
		  else												  /* 厂家测试模式时快速复位				*/
		  {
			  ;
		  }
		  /*----------------------------------------------------------------------------------------*/
		  if( Prm.password == 0x3767 && ( Iprm.FATest1 == 1 || Iprm.FATest2 == 1 ) )
		  {
			  RinV.f.SftRstReq = TRUE;
		  }
			  /*----------------------------------------------------------------------------------------*/
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_password = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_password,
/* RAM地址						*/	&(Prm.password),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn7A0 : SN低位 [－]																			*/
/****************************************************************************************************/
LONG	pncal_SnL( ULONG Cmd, ULONG Data, ULONG Digit )
{
SnWriteEn();
return (TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_SnL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_SnL,
/* RAM地址						*/	&(Prm.SnL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn7A1 : SN高位 [－]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_SnH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.SnH),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn800 : 内部位置指令设定 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_PrCmdSet = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0356,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PrCmdSet),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0215),
};



/****************************************************************************************************/
/*		Pn802 : 内部多段位置运行模式 [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_PrModeSet = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0358,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PrModeSet),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x1113),
};



/****************************************************************************************************/
/*		Pn803 : 多段位置终点路径 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_PrEndSet = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x035A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PrEndSet),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(15),
};



/****************************************************************************************************/
/*		Pn804 : 顺序运行起始路径 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_PrStartSet = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x035C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PrStartSet),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(15),
};



/****************************************************************************************************/
/*		Pn806 : Pr指令通讯参数 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PrCommSet = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x035E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PrCommSet),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		Pn810 : 路径1控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan1L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0360,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan1L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn811 : 路径1控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan1H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0362,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan1H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn812 : 路径1资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan2L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0364,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan2L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn813 : 路径1资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan2H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0366,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan2H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn814 : 路径2控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan3L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0368,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan3L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn815 : 路径2控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan3H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x036A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan3H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn816 : 路径2资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan4L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x036C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan4L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn817 : 路径2资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan4H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x036E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan4H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn818 : 路径3控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan5L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0370,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan5L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn819 : 路径3控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan5H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0372,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan5H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn81A : 路径3资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan6L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0374,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan6L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn81B : 路径3资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan6H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0376,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan6H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn81C : 路径4控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan7L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0378,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan7L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn81D : 路径4控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan7H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x037A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan7H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn81E : 路径4资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan8L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x037C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan8L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn81F : 路径4资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan8H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x037E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan8H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn820 : 路径5控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan9L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0380,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan9L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn821 : 路径5控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan9H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0382,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan9H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn822 : 路径5资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan10L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0384,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan10L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn823 : 路径5资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan10H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0386,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan10H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn824 : 路径6控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan11L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0388,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan11L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn825 : 路径6控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan11H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x038A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan11H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn826 : 路径6资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan12L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x038C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan12L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn827 : 路径6资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan12H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x038E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan12H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn828 : 路径7控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan13L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0390,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan13L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn829 : 路径7控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan13H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0392,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan13H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn82A : 路径7资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan14L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0394,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan14L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn82B : 路径7资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan14H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0396,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan14H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn82C : 路径8控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan15L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0398,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan15L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn82D : 路径8控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan15H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x039A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan15H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn82E : 路径8资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan16L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x039C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan16L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn82F : 路径8资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan16H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x039E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan16H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn830 : 路径9控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan17L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03A0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan17L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn831 : 路径9控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan17H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03A2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan17H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn832 : 路径9资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan18L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03A4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan18L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn833 : 路径9资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan18H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03A6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan18H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn834 : 路径10控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan19L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03A8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan19L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn835 : 路径10控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan19H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03AA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan19H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn836 : 路径10资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan20L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03AC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan20L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn837 : 路径10资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan20H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03AE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan20H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn838 : 路径11控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan21L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03B0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan21L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn839 : 路径11控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan21H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03B2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan21H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn83A : 路径11资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan22L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03B4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan22L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn83B : 路径11资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan22H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03B6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan22H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn83C : 路径12控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan23L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03B8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan23L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn83D : 路径12控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan23H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03BA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan23H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn83E : 路径12资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan24L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03BC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan24L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn83F : 路径12资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan24H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03BE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan24H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn840 : 路径13控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan25L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03C0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan25L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn841 : 路径13控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan25H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03C2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan25H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn842 : 路径13资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan26L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03C4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan26L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn843 : 路径13资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan26H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03C6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan26H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn844 : 路径14控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan27L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03C8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan27L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn845 : 路径14控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan27H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03CA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan27H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn846 : 路径14资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan28L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03CC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan28L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn847 : 路径14资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan28H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03CE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan28H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn848 : 路径15控制字L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan29L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03D0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan29L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn849 : 路径15控制字H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan29H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03D2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan29H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn84A : 路径15资料L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan30L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03D4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan30L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		Pn84B : 路径15资料H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_PathPlan30H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03D6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.PathPlan30H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		Pn890 : 加/减速时间(编号#0) [ms]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_AccDecT0 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03D8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AccDecT0),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65500),
};



/****************************************************************************************************/
/*		Pn891 : 加/减速时间(编号#1) [ms]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_AccDecT1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03DA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AccDecT1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65500),
};



/****************************************************************************************************/
/*		Pn892 : 加/减速时间(编号#2) [ms]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_AccDecT2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03DC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AccDecT2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65500),
};



/****************************************************************************************************/
/*		Pn893 : 加/减速时间(编号#3) [ms]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_AccDecT3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03DE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AccDecT3),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65500),
};



/****************************************************************************************************/
/*		Pn894 : 加/减速时间(编号#4) [ms]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_AccDecT4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03E0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AccDecT4),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65500),
};



/****************************************************************************************************/
/*		Pn895 : 加/减速时间(编号#5) [ms]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_AccDecT5 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03E2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AccDecT5),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65500),
};



/****************************************************************************************************/
/*		Pn896 : 加/减速时间(编号#6) [ms]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_AccDecT6 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03E4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AccDecT6),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65500),
};



/****************************************************************************************************/
/*		Pn897 : 加/减速时间(编号#7) [ms]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_AccDecT7 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03E6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.AccDecT7),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65500),
};



/****************************************************************************************************/
/*		Pn898 : 位置到达后延时时间(编号#0) [ms]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_DelayT0 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03E8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.DelayT0),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn899 : 位置到达后延时时间(编号#1) [ms]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_DelayT1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03EA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.DelayT1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn89A : 位置到达后延时时间(编号#2) [ms]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_DelayT2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03EC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.DelayT2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn89B : 位置到达后延时时间(编号#3) [ms]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_DelayT3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03EE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.DelayT3),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn89C : 位置到达后延时时间(编号#4) [ms]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_DelayT4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03F0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.DelayT4),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn89D : 位置到达后延时时间(编号#5) [ms]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_DelayT5 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03F2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.DelayT5),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn89E : 位置到达后延时时间(编号#6) [ms]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_DelayT6 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03F4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.DelayT6),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn89F : 位置到达后延时时间(编号#7) [ms]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_DelayT7 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03F6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.DelayT7),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(32767),
};



/****************************************************************************************************/
/*		Pn8A0 : 内部目标速度设定(编号#0) [0.1rpm]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_Spd0 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03F8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Spd0),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(60000),
};



/****************************************************************************************************/
/*		Pn8A1 : 内部目标速度设定(编号#1) [0.1rpm]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_Spd1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03FA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Spd1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(60000),
};



/****************************************************************************************************/
/*		Pn8A2 : 内部目标速度设定(编号#2) [0.1rpm]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_Spd2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03FC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Spd2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(60000),
};



/****************************************************************************************************/
/*		Pn8A3 : 内部目标速度设定(编号#3) [0.1rpm]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_Spd3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x03FE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Spd3),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(60000),
};



/****************************************************************************************************/
/*		Pn8A4 : 内部目标速度设定(编号#4) [0.1rpm]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_Spd4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0400,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Spd4),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(60000),
};



/****************************************************************************************************/
/*		Pn8A5 : 内部目标速度设定(编号#5) [0.1rpm]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_Spd5 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0402,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Spd5),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(60000),
};



/****************************************************************************************************/
/*		Pn8A6 : 内部目标速度设定(编号#6) [0.1rpm]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_Spd6 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0404,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Spd6),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(60000),
};



/****************************************************************************************************/
/*		Pn8A7 : 内部目标速度设定(编号#7) [0.1rpm]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_Spd7 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0406,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Spd7),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(60000),
};



/****************************************************************************************************/
/*		PnA00 : TPDO1映射组 [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0408,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA01 : TPDO1映射1L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1Map1L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x040A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1Map1L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA02 : TPDO1映射1H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1Map1H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x040C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1Map1H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA03 : TPDO1映射2L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1Map2L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x040E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1Map2L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA04 : TPDO1映射2H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1Map2H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0410,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1Map2H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA05 : TPDO1映射3L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1Map3L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0412,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1Map3L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA06 : TPDO1映射3H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1Map3H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0414,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1Map3H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA07 : TPDO1映射4L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1Map4L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0416,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1Map4L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA08 : TPDO1映射4H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1Map4H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0418,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1Map4H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA09 : TPDO1映射站号L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1StationL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x041A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1StationL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA0A : TPDO1映射站号H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1StationH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x041C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1StationH),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA0B : TPDO1传输类型 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1Type = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x041E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1Type),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA0C : TPDO1禁止时间 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1InTime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0420,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1InTime),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA0D : TPDO1事件时间 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo1EventTime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0422,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo1EventTime),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA10 : TPDO2映射组 [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0424,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA11 : TPDO2映射1L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2Map1L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0426,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2Map1L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA12 : TPDO2映射1H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2Map1H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0428,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2Map1H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA13 : TPDO2映射2L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2Map2L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x042A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2Map2L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA14 : TPDO2映射2H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2Map2H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x042C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2Map2H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA15 : TPDO2映射3L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2Map3L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x042E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2Map3L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA16 : TPDO2映射3H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2Map3H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0430,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2Map3H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA17 : TPDO2映射4L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2Map4L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0432,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2Map4L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA18 : TPDO2映射4H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2Map4H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0434,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2Map4H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA19 : TPDO2映射站号L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2StationL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0436,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2StationL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA1A : TPDO2映射站号H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2StationH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0438,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2StationH),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA1B : TPDO2传输类型 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2Type = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x043A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2Type),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA1C : TPDO2禁止时间 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2InTime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x043C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2InTime),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA1D : TPDO2事件时间 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo2EventTime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x043E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo2EventTime),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA20 : TPDO3映射组 [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0440,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA21 : TPDO3映射1L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3Map1L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0442,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3Map1L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA22 : TPDO3映射1H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3Map1H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0444,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3Map1H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA23 : TPDO3映射2L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3Map2L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0446,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3Map2L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA24 : TPDO3映射2H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3Map2H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0448,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3Map2H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA25 : TPDO3映射3L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3Map3L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x044A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3Map3L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA26 : TPDO3映射3H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3Map3H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x044C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3Map3H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA27 : TPDO3映射4L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3Map4L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x044E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3Map4L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA28 : TPDO3映射4H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3Map4H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0450,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3Map4H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA29 : TPDO3映射站号L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3StationL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0452,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3StationL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA2A : TPDO3映射站号H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3StationH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0454,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3StationH),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA2B : TPDO3传输类型 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3Type = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0456,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3Type),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA2C : TPDO3禁止时间 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3InTime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0458,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3InTime),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA2D : TPDO3事件时间 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo3EventTime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x045A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo3EventTime),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA30 : TPDO4映射组 [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x045C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA31 : TPDO4映射1L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4Map1L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x045E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4Map1L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA32 : TPDO4映射1H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4Map1H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0460,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4Map1H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA33 : TPDO4映射2L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4Map2L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0462,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4Map2L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA34 : TPDO4映射2H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4Map2H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0464,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4Map2H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA35 : TPDO4映射3L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4Map3L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0466,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4Map3L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA36 : TPDO4映射3H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4Map3H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0468,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4Map3H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA37 : TPDO4映射4L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4Map4L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x046A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4Map4L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA38 : TPDO4映射4H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4Map4H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x046C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4Map4H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA39 : TPDO4映射站号L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4StationL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x046E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4StationL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA3A : TPDO4映射站号H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4StationH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0470,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4StationH),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA3B : TPDO4传输类型 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4Type = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0472,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4Type),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA3C : TPDO4禁止时间 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4InTime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0474,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4InTime),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA3D : TPDO4事件时间 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_Tpdo4EventTime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0476,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Tpdo4EventTime),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA40 : RPDO1映射组 [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0478,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA41 : RPDO1映射1L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO1Map1L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x047A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO1Map1L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA42 : RPDO1映射1H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO1Map1H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x047C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO1Map1H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA43 : RPDO1映射2L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO1Map2L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x047E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO1Map2L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA44 : RPDO1映射2H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO1Map2H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0480,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO1Map2H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA45 : RPDO1映射3L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO1Map3L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0482,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO1Map3L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA46 : RPDO1映射3H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO1Map3H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0484,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO1Map3H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA47 : RPDO1映射4L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO1Map4L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0486,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO1Map4L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA48 : RPDO1映射4H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO1Map4H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0488,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO1Map4H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA49 : RPDO1映射站号L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO1StationL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x048A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO1StationL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA4A : RPDO1映射站号H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO1StationH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x048C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO1StationH),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA4B : RPDO1传输类型 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO1Type = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x048E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO1Type),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA50 : RPDO2映射组 [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0490,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO2),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA51 : RPDO2映射1L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO2Map1L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0492,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO2Map1L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA52 : RPDO2映射1H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO2Map1H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0494,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO2Map1H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA53 : RPDO2映射2L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO2Map2L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0496,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO2Map2L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA54 : RPDO2映射2H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO2Map2H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0498,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO2Map2H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA55 : RPDO2映射3L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO2Map3L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x049A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO2Map3L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA56 : RPDO2映射3H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO2Map3H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x049C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO2Map3H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA57 : RPDO2映射4L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO2Map4L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x049E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO2Map4L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA58 : RPDO2映射4H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO2Map4H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04A0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO2Map4H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA59 : RPDO2映射站号L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO2StationL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04A2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO2StationL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA5A : RPDO2映射站号H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO2StationH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04A4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO2StationH),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA5B : RPDO2传输类型 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO2Type = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04A6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO2Type),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA60 : RPDO3映射组 [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04A8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO3),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA61 : RPDO3映射1L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO3Map1L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04AA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO3Map1L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA62 : RPDO3映射1H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO3Map1H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04AC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO3Map1H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA63 : RPDO3映射2L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO3Map2L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04AE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO3Map2L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA64 : RPDO3映射2H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO3Map2H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04B0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO3Map2H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA65 : RPDO3映射3L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO3Map3L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04B2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO3Map3L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA66 : RPDO3映射3H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO3Map3H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04B4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO3Map3H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA67 : RPDO3映射4L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO3Map4L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04B6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO3Map4L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA68 : RPDO3映射4H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO3Map4H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04B8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO3Map4H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA69 : RPDO3映射站号L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO3StationL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04BA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO3StationL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA6A : RPDO3映射站号H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO3StationH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04BC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO3StationH),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA6B : RPDO3传输类型 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO3Type = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04BE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO3Type),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA70 : RPDO4映射组 [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04C0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO4),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA71 : RPDO4映射1L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO4Map1L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04C2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO4Map1L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA72 : RPDO4映射1H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO4Map1H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04C4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO4Map1H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA73 : RPDO4映射2L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO4Map2L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04C6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO4Map2L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA74 : RPDO4映射2H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO4Map2H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04C8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO4Map2H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA75 : RPDO4映射3L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO4Map3L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04CA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO4Map3L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA76 : RPDO4映射3H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO4Map3H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04CC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO4Map3H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA77 : RPDO4映射4L [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO4Map4L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04CE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO4Map4L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA78 : RPDO4映射4H [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO4Map4H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04D0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO4Map4H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA79 : RPDO4映射站号L [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO4StationL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04D2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO4StationL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA7A : RPDO4映射站号H [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO4StationH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04D4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO4StationH),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA7B : RPDO4传输类型 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_RPDO4Type = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04D6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.RPDO4Type),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA80 : EmcyEnL [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_EmcyEnL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04D8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.EmcyEnL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA81 : EmcyEnH [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_EmcyEnH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04DA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.EmcyEnH),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA82 : HeartConsumerL [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_HeartConsumerL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04DC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.HeartConsumerL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA83 : HeartConsumerH [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_HeartConsumerH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04DE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.HeartConsumerH),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA84 : HeartProducter [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_HeartProducter = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04E0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.HeartProducter),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA85 : Guardtime [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_Guardtime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04E2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Guardtime),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA86 : lifetime [-]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_lifetime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04E4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.lifetime),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA87 : CAN 控制寄存器 [-]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_CanControl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04E6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.CanControl),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnA88 : CAN 功能控制寄存器2 [-]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_CanControl2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04E8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.CanControl2),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB00 : CiA402控制模拟功能 [-]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_Cia402Test = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04EA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Cia402Test),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB02 : CAN速度转换系数L [-]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_CANSpdCoeffL = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04EC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.CANSpdCoeffL),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB03 : CAN速度转换系数H [-]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_CANSpdCoeffH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04EE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.CANSpdCoeffH),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		PnB04 : 预留 [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_B04 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04F0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.B04),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB05 : 预留 [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_B05 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04F2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.B05),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB06 : 预留 [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_B06 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04F4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.B06),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB07 : 预留 [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_B07 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04F6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.B07),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB08 : 预留 [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_B08 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04F8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.B08),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB09 : 预留 [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_B09 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04FA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.B09),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB0A : 预留 [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_B0A = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04FC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.B0A),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB0B : 预留 [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_B0B = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x04FE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.B0B),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB0C : 预留 [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_B0C = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0500,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.B0C),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB0D : 预留 [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_B0D = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0502,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.B0D),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB10 : [6040h]控制字 [-]																	*/
/****************************************************************************************************/
LONG	pncal_OBJ_6040( ULONG Cmd, ULONG Data, ULONG Digit )
{
		  Obj6040Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6040 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_OBJ_6040,
/* RAM地址						*/	&(Prm.OBJ_6040),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB11 : [605Ah]快速停机方式选择 [-]															*/
/****************************************************************************************************/
LONG	pncal_OBJ_605A( ULONG Cmd, ULONG Data, ULONG Digit )
{
	Obj605AUp();
	   return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_605A = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0504,
/* 处理函数指针					*/	pncal_OBJ_605A,
/* RAM地址						*/	&(Prm.OBJ_605A),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(7),
};



/****************************************************************************************************/
/*		PnB12 : [605Dh]暂停方式选择 [-]																*/
/****************************************************************************************************/
LONG	pncal_OBJ_605D( ULONG Cmd, ULONG Data, ULONG Digit )
{
	Obj605DUp();
	   return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_605D = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0506,
/* 处理函数指针					*/	pncal_OBJ_605D,
/* RAM地址						*/	&(Prm.OBJ_605D),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(3),
};



/****************************************************************************************************/
/*		PnB13 : [6060h]模式选择 [-]																	*/
/****************************************************************************************************/
LONG	pncal_OBJ_6060( ULONG Cmd, ULONG Data, ULONG Digit )
{
	Obj6060Up();
	   return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6060 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0508,
/* 处理函数指针					*/	pncal_OBJ_6060,
/* RAM地址						*/	&(Prm.OBJ_6060),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10),
};



/****************************************************************************************************/
/*		PnB14 : [6065h]位置偏差过大阈值L [User]														*/
/****************************************************************************************************/
LONG	pncal_OBJ_6065_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
	Obj6065Up();
	   return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6065_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x050A,
/* 处理函数指针					*/	pncal_OBJ_6065_L,
/* RAM地址						*/	&(Prm.OBJ_6065_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB15 : [6065h]位置偏差过大阈值H [User]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_6065_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x050C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_6065_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB16 : [6067h]位置到达阈值L [User]															*/
/****************************************************************************************************/
LONG	pncal_OBJ_6067_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6067Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6067_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x050E,
/* 处理函数指针					*/	pncal_OBJ_6067_L,
/* RAM地址						*/	&(Prm.OBJ_6067_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB17 : [6067h]位置到达阈值H [User]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_6067_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0510,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_6067_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB18 : [6068h]位置到达时间窗口L [ms]														*/
/****************************************************************************************************/
LONG	pncal_OBJ_6068_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6068Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6068_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0512,
/* 处理函数指针					*/	pncal_OBJ_6068_L,
/* RAM地址						*/	&(Prm.OBJ_6068_L),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnB19 : [6068h]位置到达时间窗口H [-]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_6068_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0514,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_6068_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB1A : [606Dh]速度到达阈值 [0.1rpm]														*/
/****************************************************************************************************/
LONG	pncal_OBJ_606D( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj606DUp();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_606D = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0516,
/* 处理函数指针					*/	pncal_OBJ_606D,
/* RAM地址						*/	&(Prm.OBJ_606D),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(30000),
};



/****************************************************************************************************/
/*		PnB1B : [606Eh]速度到达时间窗口 [ms]														*/
/****************************************************************************************************/
LONG	pncal_OBJ_606E( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj606EUp();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_606E = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0518,
/* 处理函数指针					*/	pncal_OBJ_606E,
/* RAM地址						*/	&(Prm.OBJ_606E),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnB1C : [606Fh]零速阈值 [0.1rpm]															*/
/****************************************************************************************************/
LONG	pncal_OBJ_606F( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj606FUp();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_606F = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x051A,
/* 处理函数指针					*/	pncal_OBJ_606F,
/* RAM地址						*/	&(Prm.OBJ_606F),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(30000),
};



/****************************************************************************************************/
/*		PnB1D : [6070h]零速时间窗口 [ms]															*/
/****************************************************************************************************/
LONG	pncal_OBJ_6070( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6070Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6070 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x051C,
/* 处理函数指针					*/	pncal_OBJ_6070,
/* RAM地址						*/	&(Prm.OBJ_6070),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnB20 : [6071h]目标转矩 [0.1%]																*/
/****************************************************************************************************/
LONG	pncal_OBJ_6071( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6071Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6071 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_OBJ_6071,
/* RAM地址						*/	&(Prm.OBJ_6071),
/* 下限値						*/	(USHORT)(-5000),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		PnB21 : [6072h]最大转矩 [0.1%]																*/
/****************************************************************************************************/
LONG	pncal_OBJ_6072( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6072Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6072 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x051E,
/* 处理函数指针					*/	pncal_OBJ_6072,
/* RAM地址						*/	&(Prm.OBJ_6072),
/* 下限値						*/	(USHORT)(-5000),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		PnB22 : [607Ah]目标位置L [User]																*/
/****************************************************************************************************/
LONG	pncal_OBJ_607A_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj607AUp();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_607A_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_OBJ_607A_L,
/* RAM地址						*/	&(Prm.OBJ_607A_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB23 : [607Ah]目标位置H [User]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_607A_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_607A_H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		PnB24 : [607Ch]原点偏置L [User]																*/
/****************************************************************************************************/
LONG	pncal_OBJ_607C_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj607CUp();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_607C_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0520,
/* 处理函数指针					*/	pncal_OBJ_607C_L,
/* RAM地址						*/	&(Prm.OBJ_607C_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB25 : [607Ch]原点偏置H [User]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_607C_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0522,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_607C_H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		PnB26 : [607Dh_01]软件绝对位置限制最小值L [User]											*/
/****************************************************************************************************/
LONG	pncal_OBJ_607D_01_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj607D_1Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_607D_01_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0524,
/* 处理函数指针					*/	pncal_OBJ_607D_01_L,
/* RAM地址						*/	&(Prm.OBJ_607D_01_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB27 : [607Dh_01]软件绝对位置限制最小值H [User]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_607D_01_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0526,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_607D_01_H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		PnB28 : [607Dh_02]软件绝对位置限制最大值L [User]											*/
/****************************************************************************************************/
LONG	pncal_OBJ_607D_02_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj607D_2Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_607D_02_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0528,
/* 处理函数指针					*/	pncal_OBJ_607D_02_L,
/* RAM地址						*/	&(Prm.OBJ_607D_02_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB29 : [607Dh_02]软件绝对位置限制最大值H [User]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_607D_02_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x052A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_607D_02_H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		PnB2A : [607Eh]指令极性 [-]																	*/
/****************************************************************************************************/
LONG	pncal_OBJ_607E( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj607EUp();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_607E = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x052C,
/* 处理函数指针					*/	pncal_OBJ_607E,
/* RAM地址						*/	&(Prm.OBJ_607E),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB2C : [607Fh]最大轮廓速度L [指令单位/s]													*/
/****************************************************************************************************/
LONG	pncal_OBJ_607F_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj607FUp();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_607F_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x052E,
/* 处理函数指针					*/	pncal_OBJ_607F_L,
/* RAM地址						*/	&(Prm.OBJ_607F_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB2D : [607Fh]最大轮廓速度H [指令单位/s]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_607F_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0530,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_607F_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB2E : [6080h]最大电机速度L [rpm]															*/
/****************************************************************************************************/
LONG	pncal_OBJ_6080_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6080Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6080_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0532,
/* 处理函数指针					*/	pncal_OBJ_6080_L,
/* RAM地址						*/	&(Prm.OBJ_6080_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB2F : [6080h]最大电机速度H [rpm]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_6080_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0534,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_6080_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB30 : [6081h]位置轮廓速度L [指令单位/s]													*/
/****************************************************************************************************/
LONG	pncal_OBJ_6081_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6081Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6081_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0536,
/* 处理函数指针					*/	pncal_OBJ_6081_L,
/* RAM地址						*/	&(Prm.OBJ_6081_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB31 : [6081h]位置轮廓速度H [指令单位/s]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_6081_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0538,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_6081_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB32 : [6083h]轮廓加速度L [指令单位/s2]													*/
/****************************************************************************************************/
LONG	pncal_OBJ_6083_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6083Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6083_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_ACCEL },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x053A,
/* 处理函数指针					*/	pncal_OBJ_6083_L,
/* RAM地址						*/	&(Prm.OBJ_6083_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB33 : [6083h]轮廓加速度H [指令单位/s2]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_6083_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_ACCEL },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x053C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_6083_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB34 : [6084h]轮廓减速度L [指令单位/s2]													*/
/****************************************************************************************************/
LONG	pncal_OBJ_6084_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6084Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6084_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_ACCEL },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x053E,
/* 处理函数指针					*/	pncal_OBJ_6084_L,
/* RAM地址						*/	&(Prm.OBJ_6084_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB35 : [6084h]轮廓减速度H [指令单位/s2]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_6084_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_ACCEL },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0540,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_6084_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB36 : [6085h]快速停机减速度L [指令单位/s2]												*/
/****************************************************************************************************/
LONG	pncal_OBJ_6085_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6085Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6085_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_ACCEL },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0542,
/* 处理函数指针					*/	pncal_OBJ_6085_L,
/* RAM地址						*/	&(Prm.OBJ_6085_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB37 : [6085h]快速停机减速度H [指令单位/s2]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_6085_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_ACCEL },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0544,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_6085_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB38 : [6087h]转矩斜坡时间L [ms]															*/
/****************************************************************************************************/
LONG	pncal_OBJ_6087_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6087Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6087_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0546,
/* 处理函数指针					*/	pncal_OBJ_6087_L,
/* RAM地址						*/	&(Prm.OBJ_6087_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB39 : [6087h]转矩斜坡时间H [ms]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_6087_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0548,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_6087_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB3A : [6091h_1]电机分辨率L [-]															*/
/****************************************************************************************************/
LONG	pncal_OBJ_6091_01_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6091_1Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6091_01_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x054A,
/* 处理函数指针					*/	pncal_OBJ_6091_01_L,
/* RAM地址						*/	&(Prm.OBJ_6091_01_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB3B : [6091h_1]电机分辨率H [-]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_6091_01_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x054C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_6091_01_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB3C : [6091h_2]轴分辨率L [-]																*/
/****************************************************************************************************/
LONG	pncal_OBJ_6091_02_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6091_2Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6091_02_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x054E,
/* 处理函数指针					*/	pncal_OBJ_6091_02_L,
/* RAM地址						*/	&(Prm.OBJ_6091_02_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB3D : [6091h_2]轴分辨率H [-]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_6091_02_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0550,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_6091_02_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB3E : [6098h]回零方式 [-]																	*/
/****************************************************************************************************/
LONG	pncal_OBJ_6098( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6098Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6098 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x0,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0552,
/* 处理函数指针					*/	pncal_OBJ_6098,
/* RAM地址						*/	&(Prm.OBJ_6098),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(35),
};



/****************************************************************************************************/
/*		PnB40 : [6099h_1]搜索减速点信号速度L [指令单位/s]											*/
/****************************************************************************************************/
LONG	pncal_OBJ_6099_01_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6099_1Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6099_01_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0554,
/* 处理函数指针					*/	pncal_OBJ_6099_01_L,
/* RAM地址						*/	&(Prm.OBJ_6099_01_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB41 : [6099h_1]搜索减速点信号速度H [指令单位/s]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_6099_01_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0556,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_6099_01_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB42 : [6099h_2]搜索原点信号速度L [指令单位/s]												*/
/****************************************************************************************************/
LONG	pncal_OBJ_6099_02_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj6099_2Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_6099_02_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0558,
/* 处理函数指针					*/	pncal_OBJ_6099_02_L,
/* RAM地址						*/	&(Prm.OBJ_6099_02_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB43 : [6099h_2]搜索原点信号速度H [指令单位/s]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_6099_02_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x055A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_6099_02_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB44 : [609Ah]回零加速度L [指令单位/s2]													*/
/****************************************************************************************************/
LONG	pncal_OBJ_609A_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj609AUp();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_609A_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_ACCEL },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x055C,
/* 处理函数指针					*/	pncal_OBJ_609A_L,
/* RAM地址						*/	&(Prm.OBJ_609A_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB45 : [609Ah]回零加速度H [指令单位/s2]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_609A_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_ACCEL },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x055E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_609A_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB46 : [60B0h]位置偏置L [指令单位]															*/
/****************************************************************************************************/
LONG	pncal_OBJ_60B0_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj60B0Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_60B0_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0560,
/* 处理函数指针					*/	pncal_OBJ_60B0_L,
/* RAM地址						*/	&(Prm.OBJ_60B0_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB47 : [60B0h]位置偏置H [指令单位]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_60B0_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0562,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_60B0_H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		PnB48 : [60B1h]转速偏置L [指令单位/s]														*/
/****************************************************************************************************/
LONG	pncal_OBJ_60B1_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj60B1Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_60B1_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0564,
/* 处理函数指针					*/	pncal_OBJ_60B1_L,
/* RAM地址						*/	&(Prm.OBJ_60B1_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB49 : [60B1h]转速偏置H [指令单位/s]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_60B1_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0566,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_60B1_H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		PnB4A : [60B2h]转矩偏置 [0.1%]																*/
/****************************************************************************************************/
LONG	pncal_OBJ_60B2_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj60B2Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_60B2_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0568,
/* 处理函数指针					*/	pncal_OBJ_60B2_L,
/* RAM地址						*/	&(Prm.OBJ_60B2_L),
/* 下限値						*/	(USHORT)(-5000),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		PnB4B : [60B2h]转矩偏置H [0.1%]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_60B2_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x056A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_60B2_H),
/* 下限値						*/	(USHORT)(-5000),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		PnB4C : [60B8h]探针功能 [-]																	*/
/****************************************************************************************************/
LONG	pncal_OBJ_60B8( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj60B8Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_60B8 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x056C,
/* 处理函数指针					*/	pncal_OBJ_60B8,
/* RAM地址						*/	&(Prm.OBJ_60B8),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB4E : [60C1h]插补位置绝对位置L [指令单位]													*/
/****************************************************************************************************/
LONG	pncal_OBJ_60C1_01_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj60C1_1Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_60C1_01_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x056E,
/* 处理函数指针					*/	pncal_OBJ_60C1_01_L,
/* RAM地址						*/	&(Prm.OBJ_60C1_01_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB4F : [60C1h]插补位置绝对位置H [指令单位]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_60C1_01_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REFPULS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0570,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_60C1_01_H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		PnB50 : [60C2_1h]插补周期值 [-]																*/
/****************************************************************************************************/
LONG	pncal_OBJ_60C2_01( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj60C2_1Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_60C2_01 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0572,
/* 处理函数指针					*/	pncal_OBJ_60C2_01,
/* RAM地址						*/	&(Prm.OBJ_60C2_01),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB51 : [60C2_2h]插补周期时间单位 [-]														*/
/****************************************************************************************************/
LONG	pncal_OBJ_60C2_02( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj60C2_2Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_60C2_02 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0574,
/* 处理函数指针					*/	pncal_OBJ_60C2_02,
/* RAM地址						*/	&(Prm.OBJ_60C2_02),
/* 下限値						*/	(USHORT)(-6),
/* 上限値						*/	(USHORT)(0),
};



/****************************************************************************************************/
/*		PnB52 : [60C5h]最大加速度L [指令单位/s2]													*/
/****************************************************************************************************/
LONG	pncal_OBJ_60C5_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj60C5Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_60C5_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_ACCEL },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0576,
/* 处理函数指针					*/	pncal_OBJ_60C5_L,
/* RAM地址						*/	&(Prm.OBJ_60C5_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB53 : [60C5h]最大加速度H [指令单位/s2]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_60C5_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_ACCEL },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0578,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_60C5_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB54 : [60C6h]最大减速度L [指令单位/s2]													*/
/****************************************************************************************************/
LONG	pncal_OBJ_60C6_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj60C6Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_60C6_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_ACCEL },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x057A,
/* 处理函数指针					*/	pncal_OBJ_60C6_L,
/* RAM地址						*/	&(Prm.OBJ_60C6_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB55 : [60C6h]最大减速度H [指令单位/s2]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_60C6_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_ACCEL },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x057C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_60C6_H),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB56 : [60E0h]正向转矩限制值 [0.1%]														*/
/****************************************************************************************************/
LONG	pncal_OBJ_60E0( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj60E0Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_60E0 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x057E,
/* 处理函数指针					*/	pncal_OBJ_60E0,
/* RAM地址						*/	&(Prm.OBJ_60E0),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		PnB57 : [60E1h]负向转矩限制值 [0.1%]														*/
/****************************************************************************************************/
LONG	pncal_OBJ_60E1( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj60E1Up();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_60E1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0580,
/* 处理函数指针					*/	pncal_OBJ_60E1,
/* RAM地址						*/	&(Prm.OBJ_60E1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		PnB58 : [60FFh]目标速度 L [指令单位/s]														*/
/****************************************************************************************************/
LONG	pncal_OBJ_60FF_L( ULONG Cmd, ULONG Data, ULONG Digit )
{
Obj60FFUp();
		  return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_OBJ_60FF_L = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_OBJ_60FF_L,
/* RAM地址						*/	&(Prm.OBJ_60FF_L),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnB59 : [60FFh]目标速度H [指令单位/s]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_OBJ_60FF_H = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	TRUE,
/* :1: 字的顺序					*/	1,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_ROTARY | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.OBJ_60FF_H),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		PnC00 : 高8位:编码器类型(4bit)|电机输入电压代码(4bit),低8位:电机类型 [－]					*/
/****************************************************************************************************/
const	PRMDEF	pndef_typm_e_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0582,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.typm_e_1.w),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnC01 : 编码器软件版本 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_encver_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0584,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.encver_1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnC02 : 电机容量 [W]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_motw_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_WATTAGE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0586,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.motw_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC03 : 高字节:位置数据点位置，低字节:编码器位数 [－]										*/
/****************************************************************************************************/
const	PRMDEF	pndef_bit_dp_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0588,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.bit_dp_1.w),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnC04 : 多回转限位，单圈为0 [Rev]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_limmlt_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REVOLUTION },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x058A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.limmlt_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC05 : 高8位: 最高转速，低8位: 额定转速 [100min-1]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_vrat_max_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x058C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.vrat_max_1.w),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnC06 : 高8位: 极数，低8位: OS检测水平 [%, -]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_oslv_pol_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x058E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.oslv_pol_1.w),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnC07 : 额定转矩 [0.01Nm] [0.01Nm]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_rattrq_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0590,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.rattrq_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC08 : 最大扭矩百分比 [%]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_maxtrq_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0592,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.maxtrq_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC09 : 电机额定电流 [0.1A]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_irat_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_CURRENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0594,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.irat_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC0A : 电机瞬时最大电流  [0.1A]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_imax_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_CURRENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0596,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.imax_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC0B : 电动势(EMF)常数 [0.1mV/min-1]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_emfcmp_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_VOLT_PER_SPD },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0598,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.emfcmp_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC0C : 转子惯量 [10-6kgm2]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_jmot_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x059A,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.jmot_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC0D : 电枢绕组电阻 [0.001Ω]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_motr_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	3,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_RESIST },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x059C,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.motr_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC0E : 电枢电感 [0.01mH]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_motl_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x059E,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.motl_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC0F : 电机过载检测的基极电流 [%]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_bastrq_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05A0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.bastrq_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC10 : 电机过载检测的中间电流 [%]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_midtrq_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05A2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.midtrq_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC11 : 电机中间电流运行时过载检测时间 [10s]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_midolt_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_SEC },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05A4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.midolt_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC12 : 电机过载检测的最大电流 [%]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_mtrq2_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05A6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.mtrq2_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC13 : 电机最大电流运行时过载检测时间 [s]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_mtolt2_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_SEC },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05A8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.mtolt2_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC14 : 相位补偿1(补偿值，启动速度) [deg,100min-1]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_phscmpM1_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05AA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.phscmpM1_1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnC15 : 极距 [0.1mm/180deg]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_ppitch_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05AC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ppitch_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC16 : q轴电感LQ0 [0.01mH]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_motlq0_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05AE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.motlq0_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC17 : q轴电感Lq1 [0.01mH]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_motlq1_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05B0,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.motlq1_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnC18 : 高8位：转子惯量指数，低8位：额定转矩指数 [10n]										*/
/****************************************************************************************************/
const	PRMDEF	pndef_exp_trat_jmot_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05B2,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.exp_trat_jmot_1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnC19 : 高8位：转速指数低，8位：额定输出指数 [10n]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_exp_motw_spd_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05B4,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.exp_motw_spd_1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnC1A : 全闭环编码器比特数, 位置数据点位置 [－]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_fbit_fdp_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05B6,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.fbit_fdp_1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnC1B : 编码器偏移角 [deg]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_poleoffset_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05B8,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.poleoffset_1),
/* 下限値						*/	(USHORT)(-360),
/* 上限値						*/	(USHORT)(360),
};



/****************************************************************************************************/
/*		PnC1C : 电机共振抑制陷波滤波器的频率  [Hz]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_motresfrq_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05BA,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.motresfrq_1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(2560),
};



/****************************************************************************************************/
/*		PnC1D : 相角修正值 [65536/360deg]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_phscmpM2_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05BC,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.phscmpM2_1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnC1E : Flag [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_flg_wf_1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x05BE,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.flg_wf_1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE00 : 驱动器型号 [－]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_drvno = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05C0 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.drvno),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE01 : 伺服驱动器功率 [W]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_ampw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_WATTAGE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05C1 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ampw),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnE02 : 伺服驱动器输入电压 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_VoltType = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05C2 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.VoltType),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x0005),
};



/****************************************************************************************************/
/*		PnE03 : 伺服驱动器额定电流(峰值) [0.1A]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_irats = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_CURRENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05C3 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.irats),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnE04 : 伺服驱动器最大电流(峰值) [0.1A]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_imaxs = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_CURRENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05C4 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.imaxs),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnE05 : 模块温度故障检测阀值 [0.1℃]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_TempOH = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05C5 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.TempOH),
/* 下限値						*/	(USHORT)(600),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		PnE06 : 高位:驱动器过载检测中间电流,低位:驱动器过载检测基极电流 [%]							*/
/****************************************************************************************************/
const	PRMDEF	pndef_ibs_md = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05C6 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ibs_md.w),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE07 : 高位:驱动器过载检测最大电流时间,低位:驱动器过载检测中间电流时间 [s]					*/
/****************************************************************************************************/
const	PRMDEF	pndef_imdt_mxt = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_SEC },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05C7 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.imdt_mxt.w),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE08 : 高位:电机过载检测中间电流微调,低位:电机过载检测基极电流微调 [%]						*/
/****************************************************************************************************/
const	PRMDEF	pndef_ratbt_mt = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05C8 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ratbt_mt.w),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE09 : 高位:过载检测最大电流微调,低位:电机中间电流运行时过载检测时间微调 [%]				*/
/****************************************************************************************************/
const	PRMDEF	pndef_ratmtt_2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05C9 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ratmtt_2.w),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE0A : 高位:OS检测水平微调,低位:电机最大电流运行时过载检测时间微调 [%]						*/
/****************************************************************************************************/
const	PRMDEF	pndef_ratmt2_os = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05CA | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ratmt2_os.w),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE0B : 内置再生制动电阻阻值 [Ω]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_reger = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_RESIST },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05CB | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.reger),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnE0C : 内置再生抵抗容量 [0.1%]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_wre = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05CC | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.wre),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnE0D : ＤＢ抵抗値 [mΩ]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_dbr = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_RESIST },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05CD | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.dbr),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnE0E : ＤＢ抵抗容量(默认) [0.1%]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_wdb = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05CE | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.wdb),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnE10 : P-N电压检测水平(硬件能检测到的最大电压) [V]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_pnvoltgn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_VOLTAGE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05CF | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.pnvoltgn),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(1000),
};



/****************************************************************************************************/
/*		PnE11 : P-N电压AD检测低通滤波器时间常数 [us]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_vdetadfil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05D0 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.vdetadfil),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		PnE12 : P-N电圧検出零調 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_pnzero = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05D1 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.pnzero),
/* 下限値						*/	(USHORT)(-50),
/* 上限値						*/	(USHORT)(50),
};



/****************************************************************************************************/
/*		PnE13 : P-N电圧検出增益 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_pngain = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05D2 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.pngain),
/* 下限値						*/	(USHORT)(-127),
/* 上限値						*/	(USHORT)(127),
};



/****************************************************************************************************/
/*		PnE14 : 主电路检测滤波器选择开关  [－]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_vdefilsw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05D3 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.vdefilsw),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x7777),
};



/****************************************************************************************************/
/*		PnE15 : 警报屏蔽1 [－]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_almmsk1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05D4 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.almmsk1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE16 : 警报屏蔽2 [－]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_almmsk2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05D5 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.almmsk2),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE17 : 单管参数 [1ms]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_MosPump = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05D6 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MosPump),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE1B : 系统开关1 [－]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_syssw1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05D7 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.syssw1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE1C : 系统开关2 [－]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_syssw2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05D8 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.syssw2),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE1D : 系统开关3 [－]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_syssw3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASENBL,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05D9 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.syssw3),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE1E : 串行编码器通讯失败容许次数 [－]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_spgfail = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05DA | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.spgfail),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE1F : 噪声抑制截止频率 [Hz]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_ifil = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05DB | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ifil),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		PnE20 : 电流环增益(D) [Hz]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_ignd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05DC | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ignd),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		PnE21 : 电流环增益(Q) [Hz]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_ignq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05DD | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ignq),
/* 下限値						*/	(USHORT)(10),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		PnE22 : 电流环积分时间常数(D)  [us]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_kid = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_US },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05DE | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.kid),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnE23 : 电流环积分时间常数(Q)  [us]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_kiq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_US },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05DF | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.kiq),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnE24 : 电流环积分限制值(D) [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_limintd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05E0 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.limintd),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnE25 : 电流环积分限制值(Q) [－]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_limintq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05E1 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.limintq),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnE28 : 电流检测增益1 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_shant1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05E2 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.shant1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(16384),
};



/****************************************************************************************************/
/*		PnE29 : 电压补偿增益  [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_vrevgn = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05E3 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.vrevgn),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		PnE2A : 载波频率 [Hz]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_pwmf = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05E4 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.pwmf),
/* 下限値						*/	(USHORT)(2000),
/* 上限値						*/	(USHORT)(20000),
};



/****************************************************************************************************/
/*		PnE2B : 死区补偿增益 | 死区时间 [0.1us]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_odt_c = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_US },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05E5 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.odt_c),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE2C : 电流预测增益 [V]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_ObsGain = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05E6 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ObsGain),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(10000),
};



/****************************************************************************************************/
/*		PnE32 : 驱动器过流保护滤波时间常数 [－]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_ad_prm3 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05E7 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ad_prm3),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnE33 : 驱动器过流保护值 [0.1A]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_ad_prm4 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05E8 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ad_prm4),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnE34 : 位相補償 [deg]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_phscmp = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05E9 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.phscmp),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnE39 : 多圈数据溢出计数器 [－]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_mtovcnt = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05EA | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.mtovcnt),
/* 下限値						*/	(USHORT)(0x8000),
/* 上限値						*/	(USHORT)(0x7FFF),
};



/****************************************************************************************************/
/*		PnE44 : 下位:i-P制御割合, 上位:暴走失控检测扭矩 [%]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_ipg_rwt = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05EB | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ipg_rwt),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnEA8 : 第2速度反馈滤波时间常数 [0.01ms]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_fbfil2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_MS },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05EC | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.fbfil2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnEE0 : 无电机测试功能假想马达速度															*/
/****************************************************************************************************/
const	PRMDEF	pndef_MLess_vrat_max = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05ED | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MLess_vrat_max),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnEE1 : 无电机测试功能假想马达ＯＳ検出阈值, 磁极数											*/
/****************************************************************************************************/
const	PRMDEF	pndef_MLess_oslv_pol = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05EE | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.MLess_oslv_pol),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnEE2 : 无电机测试功能假想马达转子惯量														*/
/****************************************************************************************************/
const	PRMDEF	pndef_Mless_jmot = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05EF | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Mless_jmot),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnEE3 : 无电机测试功能假想马达指数参数														*/
/****************************************************************************************************/
const	PRMDEF	pndef_Mless_exp_spd_jmot = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05F0 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Mless_exp_spd_jmot),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnEE4 : 无电机测试功能假想负载模型															*/
/****************************************************************************************************/
const	PRMDEF	pndef_Mless_PlantModel = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05F1 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Mless_PlantModel),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(3),
};



/****************************************************************************************************/
/*		PnEE5 : 无电机测试功能假想电机摩擦系数 [%/1000rpm]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_Dm = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05F2 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Dm),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(300),
};



/****************************************************************************************************/
/*		PnEE6 : 无电机测试功能假想负载摩擦系数 [%/1000rpm]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_Dl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05F3 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.Dl),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(300),
};



/****************************************************************************************************/
/*		PnEE7 : 无电机测试功能假想负载共振频率  [Hz]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_frml = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05F4 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.frml),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		PnEE8 : 无电机测试功能假想负载振动阻尼系数													*/
/****************************************************************************************************/
const	PRMDEF	pndef_ztrml = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	3,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05F5 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ztrml),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(2000),
};



/****************************************************************************************************/
/*		PnEE9 : 无电机测试功能假想机台惯量比														*/
/****************************************************************************************************/
const	PRMDEF	pndef_jbrate = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05F6 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.jbrate),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(20000),
};



/****************************************************************************************************/
/*		PnEEA : 无电机测试功能假想机台无阻尼振动频率 [Hz]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_fnb = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05F7 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.fnb),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		PnEEB : 无电机测试功能假想机台振动阻尼系数													*/
/****************************************************************************************************/
const	PRMDEF	pndef_zb = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	3,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05F8 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.zb),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(2000),
};



/****************************************************************************************************/
/*		PnEF3 : I/F加减速时间 [s]																	*/
/****************************************************************************************************/
LONG	pncal_VfAccTime( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalVfSoftStartAcc( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_VfAccTime = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05F9 | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_VfAccTime,
/* RAM地址						*/	&(Prm.VfAccTime),
/* 下限値						*/	(USHORT)(1),
/* 上限値						*/	(USHORT)(36000),
};



/****************************************************************************************************/
/*		PnEF4 : I/F设定频率 [Hz]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_VfSetFreq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05FA | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.VfSetFreq),
/* 下限値						*/	(USHORT)(-4000),
/* 上限値						*/	(USHORT)(4000),
};



/****************************************************************************************************/
/*		PnEF5 : I/F设定电流 [Vrms]																	*/
/****************************************************************************************************/
LONG	pncal_VfSetVolt( ULONG Cmd, ULONG Data, ULONG Digit )
{
		PcalVfVSet( );
		return( TRUE );
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_VfSetVolt = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x05FB | PRMDEF_NODEFTPRM,
/* 处理函数指针					*/	pncal_VfSetVolt,
/* RAM地址						*/	&(Prm.VfSetVolt),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(5000),
};



/****************************************************************************************************/
/*		PnEFE : 系统参数校验值 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_usrchk = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_READONLY,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0001,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(EepInfo.UsrChkSum),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnEFF : 用户参数校验值 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_syschk = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_RAM_EEPROM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_READONLY,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(EepInfo.SysChkSum),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnF00 : 高8位:编码器类型(4bit)|电机输入电压代码(4bit),低8位:电机类型 [－]					*/
/****************************************************************************************************/
const	PRMDEF	pndef_typm_e = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.typm_e.w),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnF01 : 编码器软件版本 [－]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_encver = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.encver),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnF02 : 电机容量 [W]																		*/
/****************************************************************************************************/
const	PRMDEF	pndef_motw = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_WATTAGE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.motw),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF03 : 高字节:位置数据点位置，低字节:编码器位数 [－]										*/
/****************************************************************************************************/
const	PRMDEF	pndef_bit_dp = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.bit_dp.w),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnF04 : 多回转限位，单圈为0 [Rev]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_limmlt = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_REVOLUTION },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.limmlt),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF05 : 高8位: 最高转速，低8位: 额定转速 [100min-1]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_vrat_max = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_ROT_SPEED },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.vrat_max.w),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnF06 : 高8位: 极数，低8位: OS检测水平 [%, -]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_oslv_pol = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.oslv_pol.w),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnF07 : 额定转矩 [0.01Nm] [0.01Nm]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_rattrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.rattrq),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF08 : 最大扭矩百分比 [%]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_maxtrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.maxtrq),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF09 : 电机额定电流 [0.1A]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_irat = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_CURRENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.irat),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF0A : 电机瞬时最大电流  [0.1A]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_imax = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_CURRENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.imax),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF0B : 电动势(EMF)常数 [0.1mV/min-1]														*/
/****************************************************************************************************/
const	PRMDEF	pndef_emfcmp = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_VOLT_PER_SPD },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.emfcmp),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF0C : 转子惯量 [10-6kgm2]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_jmot = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.jmot),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF0D : 电枢绕组电阻 [0.001Ω]																*/
/****************************************************************************************************/
const	PRMDEF	pndef_motr = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	3,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_RESIST },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.motr),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF0E : 电枢电感 [0.01mH]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_motl = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.motl),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF0F : 电机过载检测的基极电流 [%]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_bastrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.bastrq),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF10 : 电机过载检测的中间电流 [%]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_midtrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.midtrq),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF11 : 电机中间电流运行时过载检测时间 [10s]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_midolt = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_SEC },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.midolt),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF12 : 电机过载检测的最大电流 [%]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_mtrq2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_PERCENT },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.mtrq2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF13 : 电机最大电流运行时过载检测时间 [s]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_mtolt2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_TIME_SEC },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.mtolt2),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF14 : 相位补偿1(补偿值，启动速度) [deg,100min-1]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_phscmpM1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.phscmpM1),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnF15 : 极距 [0.1mm/180deg]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_ppitch = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	1,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.ppitch),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF16 : q轴电感LQ0 [0.01mH]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_motlq0 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.motlq0),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF17 : q轴电感Lq1 [0.01mH]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_motlq1 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	2,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.motlq1),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(65535),
};



/****************************************************************************************************/
/*		PnF18 : 高8位：转子惯量指数，低8位：额定转矩指数 [10n]										*/
/****************************************************************************************************/
const	PRMDEF	pndef_exp_trat_jmot = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.exp_trat_jmot),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnF19 : 高8位：转速指数低，8位：额定输出指数 [10n]											*/
/****************************************************************************************************/
const	PRMDEF	pndef_exp_motw_spd = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.exp_motw_spd),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnF1A : 全闭环编码器比特数, 位置数据点位置 [－]												*/
/****************************************************************************************************/
const	PRMDEF	pndef_fbit_fdp = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.fbit_fdp),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnF1B : 编码器偏移角 [deg]																	*/
/****************************************************************************************************/
const	PRMDEF	pndef_poleoffset = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_W_SIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.poleoffset),
/* 下限値						*/	(USHORT)(-360),
/* 上限値						*/	(USHORT)(360),
};



/****************************************************************************************************/
/*		PnF1C : 电机共振抑制陷波滤波器的频率  [Hz]													*/
/****************************************************************************************************/
const	PRMDEF	pndef_motresfrq = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEDEC,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_FREQ },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.motresfrq),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(2560),
};



/****************************************************************************************************/
/*		PnF1D : 相角修正值 [65536/360deg]															*/
/****************************************************************************************************/
const	PRMDEF	pndef_phscmpM2 = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.phscmpM2),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnF1E : Flag [-]																			*/
/****************************************************************************************************/
const	PRMDEF	pndef_flg_wf = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NEEDBOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_SYSTEM,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_dummy,
/* RAM地址						*/	&(Prm.flg_wf),
/* 下限値						*/	(USHORT)(0x0000),
/* 上限値						*/	(USHORT)(0xFFFF),
};



/****************************************************************************************************/
/*		PnF1F : 模拟量自动校准																		*/
/****************************************************************************************************/
LONG	pncal_AutoAIAdj( ULONG Cmd, ULONG Data, ULONG Digit )
{
if(Prm.AutoAIAdj&0x01)
{
	AdcV.AI12AutoAdj = 1;
	AdcV.AI12Type = 1;
}
return(TRUE);
}
/*--------------------------------------------------------------------------------------------------*/
const	PRMDEF	pndef_AutoAIAdj = {
/* 属性指定(Bitfield)			*/	{
/* :1: 是否为Long型				*/	FALSE,
/* :1: 字的顺序					*/	0,
/* :1: 调整参数?				*/	PRMDEF_NORMAL,
/* :1: 重新上电要/不要			*/	PRMDEF_NON_BOOT,
/* :1: 存储地方					*/	PRMDEF_ONLY_RAM,
/* :2: 表示時の底、				*/	DSPDEF_BASEHEX,
/* :1: 表示時の符号有無			*/	DSPDEF_NOSIGN,
/* :3: 小数点以下位数			*/	0,
/* :1: 小数点位置变更(LSM)		*/	FALSE,
/* :1: Read only				*/	PRMDEF_WRITABLE,
/* :1: 操作员输入调整			*/	FALSE,
/* :X: 预备						*/	0,
/* :8: FormatRev				*/	0x00,
/* :8: 单位						*/	UNIT_NONE },
/* 专用使用CHECK｜OPE表示选择	*/	KPI_CHKSPUSE_COMMON | KPI_LCDOPEDSPSEL_SETUP,
/* 访问等级						*/	ACCLVL_USER1,
/* EEPROM地址					*/	0x0000,
/* 处理函数指针					*/	pncal_AutoAIAdj,
/* RAM地址						*/	&(Prm.AutoAIAdj),
/* 下限値						*/	(USHORT)(0),
/* 上限値						*/	(USHORT)(0xFFFF),
};





/****************************************************************************************************/
/*																									*/
/*		参数管理表																					*/
/*																									*/
/****************************************************************************************************/
#if		OPENSW_PRMDEF >= 1
#pragma location =".PnPrmTbl"
#endif
CPRMTBL	PnPrmTbl[] = {
/*  Idx			  PrmNo   PrmDef																	*/
/*--------------------------------------------------------------------------------------------------*/
/*    0 */		{ 0x000, &pndef_b_prm0_0						},
/*    1 */		{ 0x001, &pndef_b_prm0_1						},
/*    2 */		{ 0x002, &pndef_motdir							},
/*    3 */		{ 0x003, &pndef_mondef							},
/*    4 */		{ 0x004, &pndef_b_prm0_04						},
/*    5 */		{ 0x005, &pndef_b_prm0_05						},
/*    6 */		{ 0x006, &pndef_b_prm0_06						},
/*    7 */		{ 0x007, &pndef_b_prm0_07						},
/*    8 */		{ 0x008, &pndef_brktim							},
/*    9 */		{ 0x009, &pndef_brkwai							},
/*   10 */		{ 0x00A, &pndef_brkspd							},
/*   11 */		{ 0x00B, &pndef_brkOnDly						},
/*   12 */		{ 0x00C, &pndef_b_prm0_0C						},
/*   13 */		{ 0x00D, &pndef_b_prm0_0D						},
/*   14 */		{ 0x00E, &pndef_b_prm0_0E						},
/*   15 */		{ 0x00F, &pndef_b_prm0_F						},
/*   16 */		{ 0x011, &pndef_PcmdFTime						},
/*   17 */		{ 0x012, &pndef_regres							},
/*   18 */		{ 0x013, &pndef_regresvalue						},
/*   19 */		{ 0x014, &pndef_ServoOnDely						},
/*   20 */		{ 0x015, &pndef_olwarlvl						},
/*   21 */		{ 0x016, &pndef_mtbastrq_drt					},
/*   22 */		{ 0x017, &pndef_snglph_base_drt					},
/*   23 */		{ 0x019, &pndef_dbres							},
/*   24 */		{ 0x020, &pndef_fcplsel							},
/*   25 */		{ 0x021, &pndef_fcplsel2						},
/*   26 */		{ 0x022, &pndef_FensFiltTime					},
/*   27 */		{ 0x023, &pndef_fcplsnl							},
/*   28 */		{ 0x024, &pndef_fcplsnh							},
/*   29 */		{ 0x025, &pndef_fcplsml							},
/*   30 */		{ 0x026, &pndef_fcplsmh							},
/*   31 */		{ 0x027, &pndef_fpgoverlv2l						},
/*   32 */		{ 0x028, &pndef_fpgoverlv2h						},
/*   33 */		{ 0x029, &pndef_fpgoverclrl						},
/*   34 */		{ 0x02A, &pndef_fpgoverclrh						},
/*   35 */		{ 0x02B, &pndef_FenseSel						},
/*   36 */		{ 0x02C, &pndef_Meth2ComV						},
/*   37 */		{ 0x02D, &pndef_FensSpdlv						},
/*   38 */		{ 0x030, &pndef_SoftLimitMaxl					},
/*   39 */		{ 0x031, &pndef_SoftLimitMaxh					},
/*   40 */		{ 0x032, &pndef_SoftLimitMMax					},
/*   41 */		{ 0x033, &pndef_SoftLimitMinl					},
/*   42 */		{ 0x034, &pndef_SoftLimitMinh					},
/*   43 */		{ 0x035, &pndef_SoftLimitMMin					},
/*   44 */		{ 0x036, &pndef_SoftLimitDelta					},
/*   45 */		{ 0x039, &pndef_offdec							},
/*   46 */		{ 0x040, &pndef_absEncuse						},
/*   47 */		{ 0x041, &pndef_absEncalm						},
/*   48 */		{ 0x045, &pndef_UvModeSel						},
/*   49 */		{ 0x046, &pndef_UvTrqLmt						},
/*   50 */		{ 0x047, &pndef_UvTrqLmtOffFil					},
/*   51 */		{ 0x050, &pndef_torqlimt						},
/*   52 */		{ 0x051, &pndef_tlmtf							},
/*   53 */		{ 0x052, &pndef_tlmtr							},
/*   54 */		{ 0x053, &pndef_emgtrq							},
/*   55 */		{ 0x054, &pndef_outlmtf							},
/*   56 */		{ 0x055, &pndef_outlmtr							},
/*   57 */		{ 0x056, &pndef_RunOverTorq						},
/*   58 */		{ 0x057, &pndef_RunOverSpd						},
/*   59 */		{ 0x070, &pndef_pgrat							},
/*   60 */		{ 0x076, &pndef_SerEncSel						},
/*   61 */		{ 0x07F, &pndef_EncErrClr						},
/*   62 */		{ 0x080, &pndef_Address							},
/*   63 */		{ 0x081, &pndef_Mode							},
/*   64 */		{ 0x082, &pndef_EtherCatAddr					},
/*   65 */		{ 0x083, &pndef_EtherCatType					},
/*   66 */		{ 0x084, &pndef_SycnhErr						},
/*   67 */		{ 0x085, &pndef_ComSaveEeprom					},
/*   68 */		{ 0x086, &pndef_EtherCATConfig					},
/*   69 */		{ 0x087, &pndef_addmapEn						},
/*   70 */		{ 0x088, &pndef_addmap1s						},
/*   71 */		{ 0x089, &pndef_addmap1e						},
/*   72 */		{ 0x08A, &pndef_addmap2s						},
/*   73 */		{ 0x08B, &pndef_addmap2e						},
/*   74 */		{ 0x100, &pndef_jrate							},
/*   75 */		{ 0x101, &pndef_loophz							},
/*   76 */		{ 0x102, &pndef_pitime							},
/*   77 */		{ 0x103, &pndef_posgn							},
/*   78 */		{ 0x104, &pndef_trqfil11						},
/*   79 */		{ 0x105, &pndef_loophz2							},
/*   80 */		{ 0x106, &pndef_pitime2							},
/*   81 */		{ 0x107, &pndef_posgn2							},
/*   82 */		{ 0x108, &pndef_trqfil12						},
/*   83 */		{ 0x10A, &pndef_tunmode							},
/*   84 */		{ 0x10B, &pndef_rigidity						},
/*   85 */		{ 0x10C, &pndef_interpolation					},
/*   86 */		{ 0x110, &pndef_gnsw1							},
/*   87 */		{ 0x112, &pndef_gnswfil1						},
/*   88 */		{ 0x113, &pndef_gnswfil2						},
/*   89 */		{ 0x114, &pndef_gnswwait1						},
/*   90 */		{ 0x115, &pndef_gnswwait2						},
/*   91 */		{ 0x116, &pndef_LowSpdLevel						},
/*   92 */		{ 0x117, &pndef_SpdSwitch						},
/*   93 */		{ 0x120, &pndef_pitfil							},
/*   94 */		{ 0x121, &pndef_ffgn							},
/*   95 */		{ 0x122, &pndef_fffil							},
/*   96 */		{ 0x123, &pndef_sfgn							},
/*   97 */		{ 0x124, &pndef_sffil							},
/*   98 */		{ 0x125, &pndef_fbfil							},
/*   99 */		{ 0x130, &pndef_gnmode							},
/*  100 */		{ 0x132, &pndef_mdswlv							},
/*  101 */		{ 0x133, &pndef_mswrf							},
/*  102 */		{ 0x134, &pndef_mswacc							},
/*  103 */		{ 0x135, &pndef_msplvl							},
/*  104 */		{ 0x140, &pndef_mfvibsw							},
/*  105 */		{ 0x141, &pndef_avibgn							},
/*  106 */		{ 0x142, &pndef_avibfrq							},
/*  107 */		{ 0x143, &pndef_avibdamp						},
/*  108 */		{ 0x144, &pndef_avibfil1						},
/*  109 */		{ 0x145, &pndef_avibfil2						},
/*  110 */		{ 0x146, &pndef_pstbfrq							},
/*  111 */		{ 0x147, &pndef_pstbdamp						},
/*  112 */		{ 0x14A, &pndef_Nntchfil1						},
/*  113 */		{ 0x14B, &pndef_Nntchdamp1						},
/*  114 */		{ 0x14C, &pndef_Nntchfil2						},
/*  115 */		{ 0x14D, &pndef_Nntchdamp2						},
/*  116 */		{ 0x150, &pndef_tfuncsw							},
/*  117 */		{ 0x151, &pndef_anotchsw						},
/*  118 */		{ 0x152, &pndef_vibdetlvl						},
/*  119 */		{ 0x153, &pndef_ntchfil1						},
/*  120 */		{ 0x154, &pndef_ntchq1							},
/*  121 */		{ 0x155, &pndef_ntchdamp1						},
/*  122 */		{ 0x156, &pndef_ntchfil2						},
/*  123 */		{ 0x157, &pndef_ntchq2							},
/*  124 */		{ 0x158, &pndef_ntchdamp2						},
/*  125 */		{ 0x159, &pndef_ntchfil3						},
/*  126 */		{ 0x15A, &pndef_ntchq3							},
/*  127 */		{ 0x15B, &pndef_ntchdamp3						},
/*  128 */		{ 0x15C, &pndef_ntchfil4						},
/*  129 */		{ 0x15D, &pndef_ntchq4							},
/*  130 */		{ 0x15E, &pndef_ntchdamp4						},
/*  131 */		{ 0x161, &pndef_dobgn							},
/*  132 */		{ 0x162, &pndef_dobgn2							},
/*  133 */		{ 0x163, &pndef_dtrqgn							},
/*  134 */		{ 0x164, &pndef_dlpfil							},
/*  135 */		{ 0x165, &pndef_dobjgn							},
/*  136 */		{ 0x166, &pndef_evoben							},
/*  137 */		{ 0x167, &pndef_evobgn							},
/*  138 */		{ 0x168, &pndef_evobjgn							},
/*  139 */		{ 0x169, &pndef_evoblpf							},
/*  140 */		{ 0x170, &pndef_fricmaxspd						},
/*  141 */		{ 0x171, &pndef_friccoefpos						},
/*  142 */		{ 0x172, &pndef_friccoefneg						},
/*  143 */		{ 0x175, &pndef_DatLevel						},
/*  144 */		{ 0x17A, &pndef_TunLessGain						},
/*  145 */		{ 0x17B, &pndef_TunLessStiff					},
/*  146 */		{ 0x17C, &pndef_TunLessTrqLpf					},
/*  147 */		{ 0x17D, &pndef_TunLessVfbLpf					},
/*  148 */		{ 0x185, &pndef_vibsel							},
/*  149 */		{ 0x186, &pndef_vibsens							},
/*  150 */		{ 0x187, &pndef_vibnorm							},
/*  151 */		{ 0x192, &pndef_ovserrdetlvl					},
/*  152 */		{ 0x193, &pndef_adatgmax						},
/*  153 */		{ 0x195, &pndef_gcomptrq						},
/*  154 */		{ 0x196, &pndef_pqfriqcomptrq					},
/*  155 */		{ 0x197, &pndef_nqfriqcomptrq					},
/*  156 */		{ 0x198, &pndef_vfrigcomptrq					},
/*  157 */		{ 0x199, &pndef_spdhys							},
/*  158 */		{ 0x200, &pndef_prstsw							},
/*  159 */		{ 0x201, &pndef_PulseType						},
/*  160 */		{ 0x202, &pndef_posctrl							},
/*  161 */		{ 0x203, &pndef_MulFrq							},
/*  162 */		{ 0x204, &pndef_ratb2l							},
/*  163 */		{ 0x205, &pndef_ratb2h							},
/*  164 */		{ 0x206, &pndef_rata2l							},
/*  165 */		{ 0x207, &pndef_rata2h							},
/*  166 */		{ 0x210, &pndef_expbias1						},
/*  167 */		{ 0x211, &pndef_expfil							},
/*  168 */		{ 0x212, &pndef_mafil							},
/*  169 */		{ 0x220, &pndef_cmctrlexsw						},
/*  170 */		{ 0x221, &pndef_blcm2l							},
/*  171 */		{ 0x222, &pndef_blcm2h							},
/*  172 */		{ 0x223, &pndef_blfiltime						},
/*  173 */		{ 0x230, &pndef_mdlsw_1							},
/*  174 */		{ 0x231, &pndef_mdlsw_2							},
/*  175 */		{ 0x232, &pndef_remdetw							},
/*  176 */		{ 0x233, &pndef_mdlantfrq						},
/*  177 */		{ 0x234, &pndef_mdlresfrq						},
/*  178 */		{ 0x235, &pndef_ff_frq							},
/*  179 */		{ 0x236, &pndef_ff_fil							},
/*  180 */		{ 0x240, &pndef_mdlsw							},
/*  181 */		{ 0x241, &pndef_mdlgn							},
/*  182 */		{ 0x242, &pndef_mdlzeta							},
/*  183 */		{ 0x243, &pndef_mdlvff							},
/*  184 */		{ 0x244, &pndef_mdlptff							},
/*  185 */		{ 0x245, &pndef_mdlntff							},
/*  186 */		{ 0x246, &pndef_mdlgn2							},
/*  187 */		{ 0x247, &pndef_mdlzeta2						},
/*  188 */		{ 0x248, &pndef_mfctype							},
/*  189 */		{ 0x260, &pndef_nearlv2l						},
/*  190 */		{ 0x261, &pndef_nearlv2h						},
/*  191 */		{ 0x262, &pndef_coinlv2l						},
/*  192 */		{ 0x263, &pndef_coinlv2h						},
/*  193 */		{ 0x264, &pndef_overlv2l						},
/*  194 */		{ 0x265, &pndef_overlv2h						},
/*  195 */		{ 0x266, &pndef_overwrnlv						},
/*  196 */		{ 0x267, &pndef_svonoverlv2l					},
/*  197 */		{ 0x268, &pndef_svonoverlv2h					},
/*  198 */		{ 0x269, &pndef_svonoverwrnlv					},
/*  199 */		{ 0x270, &pndef_svonspdlmtlv					},
/*  200 */		{ 0x271, &pndef_PulseSel						},
/*  201 */		{ 0x272, &pndef_prstsw_1						},
/*  202 */		{ 0x273, &pndef_prstsw_2						},
/*  203 */		{ 0x274, &pndef_cmfilsw_3						},
/*  204 */		{ 0x276, &pndef_revlimit						},
/*  205 */		{ 0x277, &pndef_revovDir						},
/*  206 */		{ 0x278, &pndef_srevlimitL						},
/*  207 */		{ 0x279, &pndef_srevlimitH						},
/*  208 */		{ 0x290, &pndef_orgmode							},
/*  209 */		{ 0x291, &pndef_orgspdhight						},
/*  210 */		{ 0x292, &pndef_orgspdlow						},
/*  211 */		{ 0x293, &pndef_orgdecacc						},
/*  212 */		{ 0x294, &pndef_orgoffsetL						},
/*  213 */		{ 0x295, &pndef_orgoffsetH						},
/*  214 */		{ 0x296, &pndef_orgMpos							},
/*  215 */		{ 0x297, &pndef_orgSposL						},
/*  216 */		{ 0x298, &pndef_orgSposH						},
/*  217 */		{ 0x299, &pndef_orgovtime						},
/*  218 */		{ 0x29A, &pndef_orgstatus						},
/*  219 */		{ 0x300, &pndef_spdSource						},
/*  220 */		{ 0x301, &pndef_spdcmd							},
/*  221 */		{ 0x302, &pndef_srfil							},
/*  222 */		{ 0x304, &pndef_speed0							},
/*  223 */		{ 0x305, &pndef_speed1							},
/*  224 */		{ 0x306, &pndef_speed2							},
/*  225 */		{ 0x307, &pndef_speed3							},
/*  226 */		{ 0x310, &pndef_sfsacc							},
/*  227 */		{ 0x311, &pndef_sfsdec							},
/*  228 */		{ 0x312, &pndef_sfsts							},
/*  229 */		{ 0x313, &pndef_clamp							},
/*  230 */		{ 0x314, &pndef_clampMaxSpd						},
/*  231 */		{ 0x317, &pndef_tgonlv							},
/*  232 */		{ 0x318, &pndef_MaxSpd							},
/*  233 */		{ 0x320, &pndef_vcmplv							},
/*  234 */		{ 0x400, &pndef_b_prm400						},
/*  235 */		{ 0x401, &pndef_secfil							},
/*  236 */		{ 0x402, &pndef_secq							},
/*  237 */		{ 0x403, &pndef_trqcmddirtype					},
/*  238 */		{ 0x404, &pndef_treffil							},
/*  239 */		{ 0x410, &pndef_intrqcmd1						},
/*  240 */		{ 0x411, &pndef_intrqcmd2						},
/*  241 */		{ 0x412, &pndef_intrqcmd3						},
/*  242 */		{ 0x413, &pndef_intrqcmd4						},
/*  243 */		{ 0x415, &pndef_ntqspdlimt1						},
/*  244 */		{ 0x416, &pndef_ntqspdlimt2						},
/*  245 */		{ 0x420, &pndef_torqcmd1						},
/*  246 */		{ 0x421, &pndef_torqcmd2						},
/*  247 */		{ 0x422, &pndef_torqcmdtimewindow				},
/*  248 */		{ 0x430, &pndef_trqcmddirtype1					},
/*  249 */		{ 0x435, &pndef_monitortime						},
/*  250 */		{ 0x500, &pndef_jogspd							},
/*  251 */		{ 0x502, &pndef_pjogsw							},
/*  252 */		{ 0x503, &pndef_pjogdistl						},
/*  253 */		{ 0x504, &pndef_pjogdisth						},
/*  254 */		{ 0x505, &pndef_pjogacctm						},
/*  255 */		{ 0x506, &pndef_pjogwaittm						},
/*  256 */		{ 0x507, &pndef_pjognum							},
/*  257 */		{ 0x508, &pndef_pjogrotspd						},
/*  258 */		{ 0x510, &pndef_CurIntrig						},
/*  259 */		{ 0x511, &pndef_CurType							},
/*  260 */		{ 0x512, &pndef_CurAmp							},
/*  261 */		{ 0x513, &pndef_CurFreq							},
/*  262 */		{ 0x514, &pndef_CurOffSet						},
/*  263 */		{ 0x515, &pndef_SpdIntrig						},
/*  264 */		{ 0x516, &pndef_SpdType							},
/*  265 */		{ 0x517, &pndef_SpdAmp							},
/*  266 */		{ 0x518, &pndef_SpdFreq							},
/*  267 */		{ 0x519, &pndef_SpdOffSet						},
/*  268 */		{ 0x520, &pndef_CurLimtHard						},
/*  269 */		{ 0x521, &pndef_LimtTHard						},
/*  270 */		{ 0x522, &pndef_SpdLimtHard						},
/*  271 */		{ 0x523, &pndef_CurLimtSoft						},
/*  272 */		{ 0x524, &pndef_LimtTSoft						},
/*  273 */		{ 0x525, &pndef_SpdLimtSoft						},
/*  274 */		{ 0x526, &pndef_StallEn							},
/*  275 */		{ 0x527, &pndef_Pn527							},
/*  276 */		{ 0x528, &pndef_Pn528							},
/*  277 */		{ 0x529, &pndef_Pn529							},
/*  278 */		{ 0x530, &pndef_Pn530							},
/*  279 */		{ 0x531, &pndef_Pn531							},
/*  280 */		{ 0x532, &pndef_Pn532							},
/*  281 */		{ 0x533, &pndef_Pn533							},
/*  282 */		{ 0x534, &pndef_Pn534							},
/*  283 */		{ 0x535, &pndef_Pn535							},
/*  284 */		{ 0x536, &pndef_Pn536							},
/*  285 */		{ 0x537, &pndef_Pn537							},
/*  286 */		{ 0x538, &pndef_Pn538							},
/*  287 */		{ 0x539, &pndef_Pn539							},
/*  288 */		{ 0x540, &pndef_Pn540							},
/*  289 */		{ 0x541, &pndef_Pn541							},
/*  290 */		{ 0x542, &pndef_Pn542							},
/*  291 */		{ 0x543, &pndef_Pn543							},
/*  292 */		{ 0x544, &pndef_Pn544							},
/*  293 */		{ 0x545, &pndef_Pn545							},
/*  294 */		{ 0x546, &pndef_Pn546							},
/*  295 */		{ 0x547, &pndef_Pn547							},
/*  296 */		{ 0x548, &pndef_Pn548							},
/*  297 */		{ 0x549, &pndef_Pn549							},
/*  298 */		{ 0x550, &pndef_Pn550							},
/*  299 */		{ 0x551, &pndef_Pn551							},
/*  300 */		{ 0x552, &pndef_Pn552							},
/*  301 */		{ 0x553, &pndef_Pn553							},
/*  302 */		{ 0x554, &pndef_Pn554							},
/*  303 */		{ 0x555, &pndef_Pn555							},
/*  304 */		{ 0x556, &pndef_Pn556							},
/*  305 */		{ 0x557, &pndef_Pn557							},
/*  306 */		{ 0x558, &pndef_Pn558							},
/*  307 */		{ 0x559, &pndef_Pn559							},
/*  308 */		{ 0x560, &pndef_MIT_Volmax						},
/*  309 */		{ 0x561, &pndef_MIT_Volmin						},
/*  310 */		{ 0x562, &pndef_CANTimeOut						},
/*  311 */		{ 0x563, &pndef_MIT_Curmax						},
/*  312 */		{ 0x564, &pndef_MIT_Curmin						},
/*  313 */		{ 0x565, &pndef_AccRads							},
/*  314 */		{ 0x566, &pndef_KtSetEn							},
/*  315 */		{ 0x567, &pndef_KtSet							},
/*  316 */		{ 0x568, &pndef_KpPos							},
/*  317 */		{ 0x569, &pndef_KdPos							},
/*  318 */		{ 0x570, &pndef_KpSpd							},
/*  319 */		{ 0x571, &pndef_KiSpd							},
/*  320 */		{ 0x572, &pndef_KpCur							},
/*  321 */		{ 0x573, &pndef_KiCur							},
/*  322 */		{ 0x574, &pndef_MIT_KpMax						},
/*  323 */		{ 0x575, &pndef_MIT_KpMin						},
/*  324 */		{ 0x576, &pndef_MIT_KdMax						},
/*  325 */		{ 0x577, &pndef_MIT_KdMin						},
/*  326 */		{ 0x578, &pndef_MIT_Trefmax						},
/*  327 */		{ 0x579, &pndef_MIT_Trefmin						},
/*  328 */		{ 0x580, &pndef_MIT_Posmax						},
/*  329 */		{ 0x581, &pndef_MIT_Posmin						},
/*  330 */		{ 0x582, &pndef_MIT_Spdmax						},
/*  331 */		{ 0x583, &pndef_MIT_Spdmin						},
/*  332 */		{ 0x584, &pndef_PosAOffSetL						},
/*  333 */		{ 0x585, &pndef_PosAOffSetH						},
/*  334 */		{ 0x586, &pndef_CANMIT							},
/*  335 */		{ 0x587, &pndef_MIT_Trq							},
/*  336 */		{ 0x588, &pndef_MIT_Sitam						},
/*  337 */		{ 0x589, &pndef_MIT_WmRef						},
/*  338 */		{ 0x58A, &pndef_MIT_PosFil						},
/*  339 */		{ 0x58B, &pndef_MIT_Tref						},
/*  340 */		{ 0x590, &pndef_MIT_Kp							},
/*  341 */		{ 0x591, &pndef_MIT_Kd							},
/*  342 */		{ 0x592, &pndef_MIT_RateA						},
/*  343 */		{ 0x593, &pndef_MIT_RateB						},
/*  344 */		{ 0x594, &pndef_MutiBOffSet						},
/*  345 */		{ 0x595, &pndef_PosBOffSetL						},
/*  346 */		{ 0x596, &pndef_PosBOffSetH						},
/*  347 */		{ 0x597, &pndef_Pn597							},
/*  348 */		{ 0x598, &pndef_EncDelay						},
/*  349 */		{ 0x599, &pndef_Pn599							},
/*  350 */		{ 0x600, &pndef_XFilTime						},
/*  351 */		{ 0x601, &pndef_insel1							},
/*  352 */		{ 0x602, &pndef_insel2							},
/*  353 */		{ 0x603, &pndef_insel3							},
/*  354 */		{ 0x604, &pndef_insel4							},
/*  355 */		{ 0x611, &pndef_outsel1							},
/*  356 */		{ 0x612, &pndef_outsel2							},
/*  357 */		{ 0x620, &pndef_AI1treffil						},
/*  358 */		{ 0x621, &pndef_AI2treffil						},
/*  359 */		{ 0x622, &pndef_AI1Offset						},
/*  360 */		{ 0x623, &pndef_AI2Offset						},
/*  361 */		{ 0x624, &pndef_AI1Gain							},
/*  362 */		{ 0x625, &pndef_AI2Gain							},
/*  363 */		{ 0x626, &pndef_AI1Zero							},
/*  364 */		{ 0x627, &pndef_AI2Zero							},
/*  365 */		{ 0x630, &pndef_VirDI							},
/*  366 */		{ 0x631, &pndef_VirDO							},
/*  367 */		{ 0x632, &pndef_Trobe1Filtime					},
/*  368 */		{ 0x633, &pndef_Trobe2Filtime					},
/*  369 */		{ 0x702, &pndef_AATDist							},
/*  370 */		{ 0x705, &pndef_PnB24							},
/*  371 */		{ 0x706, &pndef_JstVibValve						},
/*  372 */		{ 0x710, &pndef_Estimatesw						},
/*  373 */		{ 0x711, &pndef_EstimateTime					},
/*  374 */		{ 0x712, &pndef_EstimateSpd						},
/*  375 */		{ 0x713, &pndef_EstimateGain					},
/*  376 */		{ 0x715, &pndef_TlObssw							},
/*  377 */		{ 0x716, &pndef_TlObsIntero						},
/*  378 */		{ 0x717, &pndef_TlObsfriction					},
/*  379 */		{ 0x718, &pndef_TlObsGain						},
/*  380 */		{ 0x719, &pndef_TlObsLowfilt					},
/*  381 */		{ 0x720, &pndef_swpminfrq						},
/*  382 */		{ 0x721, &pndef_swpmaxfrq						},
/*  383 */		{ 0x722, &pndef_detfrqlmt						},
/*  384 */		{ 0x723, &pndef_ezffttrq						},
/*  385 */		{ 0x724, &pndef_ezfftsw							},
/*  386 */		{ 0x740, &pndef_RippleCompSw					},
/*  387 */		{ 0x741, &pndef_RippleCompSpd					},
/*  388 */		{ 0x742, &pndef_RippleCompGain					},
/*  389 */		{ 0x743, &pndef_RippleCompFreq1					},
/*  390 */		{ 0x744, &pndef_RippleCompTrq1					},
/*  391 */		{ 0x745, &pndef_RippleCompPhase1				},
/*  392 */		{ 0x746, &pndef_RippleCompFreq2					},
/*  393 */		{ 0x747, &pndef_RippleCompTrq2					},
/*  394 */		{ 0x748, &pndef_RippleCompPhase2				},
/*  395 */		{ 0x749, &pndef_RippleCompFreq3					},
/*  396 */		{ 0x74A, &pndef_RippleCompTrq3					},
/*  397 */		{ 0x74B, &pndef_RippleCompPhase3				},
/*  398 */		{ 0x74C, &pndef_RippleCompFreq4					},
/*  399 */		{ 0x74D, &pndef_RippleCompTrq4					},
/*  400 */		{ 0x74E, &pndef_RippleCompPhase4				},
/*  401 */		{ 0x755, &pndef_WearkSw							},
/*  402 */		{ 0x756, &pndef_kv								},
/*  403 */		{ 0x757, &pndef_tv								},
/*  404 */		{ 0x758, &pndef_idlim							},
/*  405 */		{ 0x759, &pndef_vmax							},
/*  406 */		{ 0x75A, &pndef_vmaxid							},
/*  407 */		{ 0x75B, &pndef_vpnavg							},
/*  408 */		{ 0x77F, &pndef_poweroffchk						},
/*  409 */		{ 0x780, &pndef_powerofffiltime					},
/*  410 */		{ 0x781, &pndef_ovlvl							},
/*  411 */		{ 0x782, &pndef_regonlvl						},
/*  412 */		{ 0x783, &pndef_regoffhys						},
/*  413 */		{ 0x784, &pndef_uvlvl							},
/*  414 */		{ 0x785, &pndef_uvfil							},
/*  415 */		{ 0x786, &pndef_UvWrnLvl						},
/*  416 */		{ 0x788, &pndef_MaxspdTun						},
/*  417 */		{ 0x78E, &pndef_Icmu							},
/*  418 */		{ 0x78F, &pndef_PosJump							},
/*  419 */		{ 0x790, &pndef_MotorNum						},
/*  420 */		{ 0x791, &pndef_EncoderType						},
/*  421 */		{ 0x792, &pndef_EncZeroPhase					},
/*  422 */		{ 0x793, &pndef_PosOutputs2l					},
/*  423 */		{ 0x794, &pndef_PosOutputs2h					},
/*  424 */		{ 0x795, &pndef_IncEncBit						},
/*  425 */		{ 0x79D, &pndef_FaTestControl					},
/*  426 */		{ 0x79E, &pndef_Testpassword					},
/*  427 */		{ 0x79F, &pndef_password						},
/*  428 */		{ 0x7A0, &pndef_SnL								},
/*  429 */		{ 0x7A1, &pndef_SnH								},
/*  430 */		{ 0x800, &pndef_PrCmdSet						},
/*  431 */		{ 0x802, &pndef_PrModeSet						},
/*  432 */		{ 0x803, &pndef_PrEndSet						},
/*  433 */		{ 0x804, &pndef_PrStartSet						},
/*  434 */		{ 0x806, &pndef_PrCommSet						},
/*  435 */		{ 0x810, &pndef_PathPlan1L						},
/*  436 */		{ 0x811, &pndef_PathPlan1H						},
/*  437 */		{ 0x812, &pndef_PathPlan2L						},
/*  438 */		{ 0x813, &pndef_PathPlan2H						},
/*  439 */		{ 0x814, &pndef_PathPlan3L						},
/*  440 */		{ 0x815, &pndef_PathPlan3H						},
/*  441 */		{ 0x816, &pndef_PathPlan4L						},
/*  442 */		{ 0x817, &pndef_PathPlan4H						},
/*  443 */		{ 0x818, &pndef_PathPlan5L						},
/*  444 */		{ 0x819, &pndef_PathPlan5H						},
/*  445 */		{ 0x81A, &pndef_PathPlan6L						},
/*  446 */		{ 0x81B, &pndef_PathPlan6H						},
/*  447 */		{ 0x81C, &pndef_PathPlan7L						},
/*  448 */		{ 0x81D, &pndef_PathPlan7H						},
/*  449 */		{ 0x81E, &pndef_PathPlan8L						},
/*  450 */		{ 0x81F, &pndef_PathPlan8H						},
/*  451 */		{ 0x820, &pndef_PathPlan9L						},
/*  452 */		{ 0x821, &pndef_PathPlan9H						},
/*  453 */		{ 0x822, &pndef_PathPlan10L						},
/*  454 */		{ 0x823, &pndef_PathPlan10H						},
/*  455 */		{ 0x824, &pndef_PathPlan11L						},
/*  456 */		{ 0x825, &pndef_PathPlan11H						},
/*  457 */		{ 0x826, &pndef_PathPlan12L						},
/*  458 */		{ 0x827, &pndef_PathPlan12H						},
/*  459 */		{ 0x828, &pndef_PathPlan13L						},
/*  460 */		{ 0x829, &pndef_PathPlan13H						},
/*  461 */		{ 0x82A, &pndef_PathPlan14L						},
/*  462 */		{ 0x82B, &pndef_PathPlan14H						},
/*  463 */		{ 0x82C, &pndef_PathPlan15L						},
/*  464 */		{ 0x82D, &pndef_PathPlan15H						},
/*  465 */		{ 0x82E, &pndef_PathPlan16L						},
/*  466 */		{ 0x82F, &pndef_PathPlan16H						},
/*  467 */		{ 0x830, &pndef_PathPlan17L						},
/*  468 */		{ 0x831, &pndef_PathPlan17H						},
/*  469 */		{ 0x832, &pndef_PathPlan18L						},
/*  470 */		{ 0x833, &pndef_PathPlan18H						},
/*  471 */		{ 0x834, &pndef_PathPlan19L						},
/*  472 */		{ 0x835, &pndef_PathPlan19H						},
/*  473 */		{ 0x836, &pndef_PathPlan20L						},
/*  474 */		{ 0x837, &pndef_PathPlan20H						},
/*  475 */		{ 0x838, &pndef_PathPlan21L						},
/*  476 */		{ 0x839, &pndef_PathPlan21H						},
/*  477 */		{ 0x83A, &pndef_PathPlan22L						},
/*  478 */		{ 0x83B, &pndef_PathPlan22H						},
/*  479 */		{ 0x83C, &pndef_PathPlan23L						},
/*  480 */		{ 0x83D, &pndef_PathPlan23H						},
/*  481 */		{ 0x83E, &pndef_PathPlan24L						},
/*  482 */		{ 0x83F, &pndef_PathPlan24H						},
/*  483 */		{ 0x840, &pndef_PathPlan25L						},
/*  484 */		{ 0x841, &pndef_PathPlan25H						},
/*  485 */		{ 0x842, &pndef_PathPlan26L						},
/*  486 */		{ 0x843, &pndef_PathPlan26H						},
/*  487 */		{ 0x844, &pndef_PathPlan27L						},
/*  488 */		{ 0x845, &pndef_PathPlan27H						},
/*  489 */		{ 0x846, &pndef_PathPlan28L						},
/*  490 */		{ 0x847, &pndef_PathPlan28H						},
/*  491 */		{ 0x848, &pndef_PathPlan29L						},
/*  492 */		{ 0x849, &pndef_PathPlan29H						},
/*  493 */		{ 0x84A, &pndef_PathPlan30L						},
/*  494 */		{ 0x84B, &pndef_PathPlan30H						},
/*  495 */		{ 0x890, &pndef_AccDecT0						},
/*  496 */		{ 0x891, &pndef_AccDecT1						},
/*  497 */		{ 0x892, &pndef_AccDecT2						},
/*  498 */		{ 0x893, &pndef_AccDecT3						},
/*  499 */		{ 0x894, &pndef_AccDecT4						},
/*  500 */		{ 0x895, &pndef_AccDecT5						},
/*  501 */		{ 0x896, &pndef_AccDecT6						},
/*  502 */		{ 0x897, &pndef_AccDecT7						},
/*  503 */		{ 0x898, &pndef_DelayT0							},
/*  504 */		{ 0x899, &pndef_DelayT1							},
/*  505 */		{ 0x89A, &pndef_DelayT2							},
/*  506 */		{ 0x89B, &pndef_DelayT3							},
/*  507 */		{ 0x89C, &pndef_DelayT4							},
/*  508 */		{ 0x89D, &pndef_DelayT5							},
/*  509 */		{ 0x89E, &pndef_DelayT6							},
/*  510 */		{ 0x89F, &pndef_DelayT7							},
/*  511 */		{ 0x8A0, &pndef_Spd0							},
/*  512 */		{ 0x8A1, &pndef_Spd1							},
/*  513 */		{ 0x8A2, &pndef_Spd2							},
/*  514 */		{ 0x8A3, &pndef_Spd3							},
/*  515 */		{ 0x8A4, &pndef_Spd4							},
/*  516 */		{ 0x8A5, &pndef_Spd5							},
/*  517 */		{ 0x8A6, &pndef_Spd6							},
/*  518 */		{ 0x8A7, &pndef_Spd7							},
/*  519 */		{ 0xA00, &pndef_Tpdo1							},
/*  520 */		{ 0xA01, &pndef_Tpdo1Map1L						},
/*  521 */		{ 0xA02, &pndef_Tpdo1Map1H						},
/*  522 */		{ 0xA03, &pndef_Tpdo1Map2L						},
/*  523 */		{ 0xA04, &pndef_Tpdo1Map2H						},
/*  524 */		{ 0xA05, &pndef_Tpdo1Map3L						},
/*  525 */		{ 0xA06, &pndef_Tpdo1Map3H						},
/*  526 */		{ 0xA07, &pndef_Tpdo1Map4L						},
/*  527 */		{ 0xA08, &pndef_Tpdo1Map4H						},
/*  528 */		{ 0xA09, &pndef_Tpdo1StationL					},
/*  529 */		{ 0xA0A, &pndef_Tpdo1StationH					},
/*  530 */		{ 0xA0B, &pndef_Tpdo1Type						},
/*  531 */		{ 0xA0C, &pndef_Tpdo1InTime						},
/*  532 */		{ 0xA0D, &pndef_Tpdo1EventTime					},
/*  533 */		{ 0xA10, &pndef_Tpdo2							},
/*  534 */		{ 0xA11, &pndef_Tpdo2Map1L						},
/*  535 */		{ 0xA12, &pndef_Tpdo2Map1H						},
/*  536 */		{ 0xA13, &pndef_Tpdo2Map2L						},
/*  537 */		{ 0xA14, &pndef_Tpdo2Map2H						},
/*  538 */		{ 0xA15, &pndef_Tpdo2Map3L						},
/*  539 */		{ 0xA16, &pndef_Tpdo2Map3H						},
/*  540 */		{ 0xA17, &pndef_Tpdo2Map4L						},
/*  541 */		{ 0xA18, &pndef_Tpdo2Map4H						},
/*  542 */		{ 0xA19, &pndef_Tpdo2StationL					},
/*  543 */		{ 0xA1A, &pndef_Tpdo2StationH					},
/*  544 */		{ 0xA1B, &pndef_Tpdo2Type						},
/*  545 */		{ 0xA1C, &pndef_Tpdo2InTime						},
/*  546 */		{ 0xA1D, &pndef_Tpdo2EventTime					},
/*  547 */		{ 0xA20, &pndef_Tpdo3							},
/*  548 */		{ 0xA21, &pndef_Tpdo3Map1L						},
/*  549 */		{ 0xA22, &pndef_Tpdo3Map1H						},
/*  550 */		{ 0xA23, &pndef_Tpdo3Map2L						},
/*  551 */		{ 0xA24, &pndef_Tpdo3Map2H						},
/*  552 */		{ 0xA25, &pndef_Tpdo3Map3L						},
/*  553 */		{ 0xA26, &pndef_Tpdo3Map3H						},
/*  554 */		{ 0xA27, &pndef_Tpdo3Map4L						},
/*  555 */		{ 0xA28, &pndef_Tpdo3Map4H						},
/*  556 */		{ 0xA29, &pndef_Tpdo3StationL					},
/*  557 */		{ 0xA2A, &pndef_Tpdo3StationH					},
/*  558 */		{ 0xA2B, &pndef_Tpdo3Type						},
/*  559 */		{ 0xA2C, &pndef_Tpdo3InTime						},
/*  560 */		{ 0xA2D, &pndef_Tpdo3EventTime					},
/*  561 */		{ 0xA30, &pndef_Tpdo4							},
/*  562 */		{ 0xA31, &pndef_Tpdo4Map1L						},
/*  563 */		{ 0xA32, &pndef_Tpdo4Map1H						},
/*  564 */		{ 0xA33, &pndef_Tpdo4Map2L						},
/*  565 */		{ 0xA34, &pndef_Tpdo4Map2H						},
/*  566 */		{ 0xA35, &pndef_Tpdo4Map3L						},
/*  567 */		{ 0xA36, &pndef_Tpdo4Map3H						},
/*  568 */		{ 0xA37, &pndef_Tpdo4Map4L						},
/*  569 */		{ 0xA38, &pndef_Tpdo4Map4H						},
/*  570 */		{ 0xA39, &pndef_Tpdo4StationL					},
/*  571 */		{ 0xA3A, &pndef_Tpdo4StationH					},
/*  572 */		{ 0xA3B, &pndef_Tpdo4Type						},
/*  573 */		{ 0xA3C, &pndef_Tpdo4InTime						},
/*  574 */		{ 0xA3D, &pndef_Tpdo4EventTime					},
/*  575 */		{ 0xA40, &pndef_RPDO1							},
/*  576 */		{ 0xA41, &pndef_RPDO1Map1L						},
/*  577 */		{ 0xA42, &pndef_RPDO1Map1H						},
/*  578 */		{ 0xA43, &pndef_RPDO1Map2L						},
/*  579 */		{ 0xA44, &pndef_RPDO1Map2H						},
/*  580 */		{ 0xA45, &pndef_RPDO1Map3L						},
/*  581 */		{ 0xA46, &pndef_RPDO1Map3H						},
/*  582 */		{ 0xA47, &pndef_RPDO1Map4L						},
/*  583 */		{ 0xA48, &pndef_RPDO1Map4H						},
/*  584 */		{ 0xA49, &pndef_RPDO1StationL					},
/*  585 */		{ 0xA4A, &pndef_RPDO1StationH					},
/*  586 */		{ 0xA4B, &pndef_RPDO1Type						},
/*  587 */		{ 0xA50, &pndef_RPDO2							},
/*  588 */		{ 0xA51, &pndef_RPDO2Map1L						},
/*  589 */		{ 0xA52, &pndef_RPDO2Map1H						},
/*  590 */		{ 0xA53, &pndef_RPDO2Map2L						},
/*  591 */		{ 0xA54, &pndef_RPDO2Map2H						},
/*  592 */		{ 0xA55, &pndef_RPDO2Map3L						},
/*  593 */		{ 0xA56, &pndef_RPDO2Map3H						},
/*  594 */		{ 0xA57, &pndef_RPDO2Map4L						},
/*  595 */		{ 0xA58, &pndef_RPDO2Map4H						},
/*  596 */		{ 0xA59, &pndef_RPDO2StationL					},
/*  597 */		{ 0xA5A, &pndef_RPDO2StationH					},
/*  598 */		{ 0xA5B, &pndef_RPDO2Type						},
/*  599 */		{ 0xA60, &pndef_RPDO3							},
/*  600 */		{ 0xA61, &pndef_RPDO3Map1L						},
/*  601 */		{ 0xA62, &pndef_RPDO3Map1H						},
/*  602 */		{ 0xA63, &pndef_RPDO3Map2L						},
/*  603 */		{ 0xA64, &pndef_RPDO3Map2H						},
/*  604 */		{ 0xA65, &pndef_RPDO3Map3L						},
/*  605 */		{ 0xA66, &pndef_RPDO3Map3H						},
/*  606 */		{ 0xA67, &pndef_RPDO3Map4L						},
/*  607 */		{ 0xA68, &pndef_RPDO3Map4H						},
/*  608 */		{ 0xA69, &pndef_RPDO3StationL					},
/*  609 */		{ 0xA6A, &pndef_RPDO3StationH					},
/*  610 */		{ 0xA6B, &pndef_RPDO3Type						},
/*  611 */		{ 0xA70, &pndef_RPDO4							},
/*  612 */		{ 0xA71, &pndef_RPDO4Map1L						},
/*  613 */		{ 0xA72, &pndef_RPDO4Map1H						},
/*  614 */		{ 0xA73, &pndef_RPDO4Map2L						},
/*  615 */		{ 0xA74, &pndef_RPDO4Map2H						},
/*  616 */		{ 0xA75, &pndef_RPDO4Map3L						},
/*  617 */		{ 0xA76, &pndef_RPDO4Map3H						},
/*  618 */		{ 0xA77, &pndef_RPDO4Map4L						},
/*  619 */		{ 0xA78, &pndef_RPDO4Map4H						},
/*  620 */		{ 0xA79, &pndef_RPDO4StationL					},
/*  621 */		{ 0xA7A, &pndef_RPDO4StationH					},
/*  622 */		{ 0xA7B, &pndef_RPDO4Type						},
/*  623 */		{ 0xA80, &pndef_EmcyEnL							},
/*  624 */		{ 0xA81, &pndef_EmcyEnH							},
/*  625 */		{ 0xA82, &pndef_HeartConsumerL					},
/*  626 */		{ 0xA83, &pndef_HeartConsumerH					},
/*  627 */		{ 0xA84, &pndef_HeartProducter					},
/*  628 */		{ 0xA85, &pndef_Guardtime						},
/*  629 */		{ 0xA86, &pndef_lifetime						},
/*  630 */		{ 0xA87, &pndef_CanControl						},
/*  631 */		{ 0xA88, &pndef_CanControl2						},
/*  632 */		{ 0xB00, &pndef_Cia402Test						},
/*  633 */		{ 0xB02, &pndef_CANSpdCoeffL					},
/*  634 */		{ 0xB03, &pndef_CANSpdCoeffH					},
/*  635 */		{ 0xB04, &pndef_B04								},
/*  636 */		{ 0xB05, &pndef_B05								},
/*  637 */		{ 0xB06, &pndef_B06								},
/*  638 */		{ 0xB07, &pndef_B07								},
/*  639 */		{ 0xB08, &pndef_B08								},
/*  640 */		{ 0xB09, &pndef_B09								},
/*  641 */		{ 0xB0A, &pndef_B0A								},
/*  642 */		{ 0xB0B, &pndef_B0B								},
/*  643 */		{ 0xB0C, &pndef_B0C								},
/*  644 */		{ 0xB0D, &pndef_B0D								},
/*  645 */		{ 0xB10, &pndef_OBJ_6040						},
/*  646 */		{ 0xB11, &pndef_OBJ_605A						},
/*  647 */		{ 0xB12, &pndef_OBJ_605D						},
/*  648 */		{ 0xB13, &pndef_OBJ_6060						},
/*  649 */		{ 0xB14, &pndef_OBJ_6065_L						},
/*  650 */		{ 0xB15, &pndef_OBJ_6065_H						},
/*  651 */		{ 0xB16, &pndef_OBJ_6067_L						},
/*  652 */		{ 0xB17, &pndef_OBJ_6067_H						},
/*  653 */		{ 0xB18, &pndef_OBJ_6068_L						},
/*  654 */		{ 0xB19, &pndef_OBJ_6068_H						},
/*  655 */		{ 0xB1A, &pndef_OBJ_606D						},
/*  656 */		{ 0xB1B, &pndef_OBJ_606E						},
/*  657 */		{ 0xB1C, &pndef_OBJ_606F						},
/*  658 */		{ 0xB1D, &pndef_OBJ_6070						},
/*  659 */		{ 0xB20, &pndef_OBJ_6071						},
/*  660 */		{ 0xB21, &pndef_OBJ_6072						},
/*  661 */		{ 0xB22, &pndef_OBJ_607A_L						},
/*  662 */		{ 0xB23, &pndef_OBJ_607A_H						},
/*  663 */		{ 0xB24, &pndef_OBJ_607C_L						},
/*  664 */		{ 0xB25, &pndef_OBJ_607C_H						},
/*  665 */		{ 0xB26, &pndef_OBJ_607D_01_L					},
/*  666 */		{ 0xB27, &pndef_OBJ_607D_01_H					},
/*  667 */		{ 0xB28, &pndef_OBJ_607D_02_L					},
/*  668 */		{ 0xB29, &pndef_OBJ_607D_02_H					},
/*  669 */		{ 0xB2A, &pndef_OBJ_607E						},
/*  670 */		{ 0xB2C, &pndef_OBJ_607F_L						},
/*  671 */		{ 0xB2D, &pndef_OBJ_607F_H						},
/*  672 */		{ 0xB2E, &pndef_OBJ_6080_L						},
/*  673 */		{ 0xB2F, &pndef_OBJ_6080_H						},
/*  674 */		{ 0xB30, &pndef_OBJ_6081_L						},
/*  675 */		{ 0xB31, &pndef_OBJ_6081_H						},
/*  676 */		{ 0xB32, &pndef_OBJ_6083_L						},
/*  677 */		{ 0xB33, &pndef_OBJ_6083_H						},
/*  678 */		{ 0xB34, &pndef_OBJ_6084_L						},
/*  679 */		{ 0xB35, &pndef_OBJ_6084_H						},
/*  680 */		{ 0xB36, &pndef_OBJ_6085_L						},
/*  681 */		{ 0xB37, &pndef_OBJ_6085_H						},
/*  682 */		{ 0xB38, &pndef_OBJ_6087_L						},
/*  683 */		{ 0xB39, &pndef_OBJ_6087_H						},
/*  684 */		{ 0xB3A, &pndef_OBJ_6091_01_L					},
/*  685 */		{ 0xB3B, &pndef_OBJ_6091_01_H					},
/*  686 */		{ 0xB3C, &pndef_OBJ_6091_02_L					},
/*  687 */		{ 0xB3D, &pndef_OBJ_6091_02_H					},
/*  688 */		{ 0xB3E, &pndef_OBJ_6098						},
/*  689 */		{ 0xB40, &pndef_OBJ_6099_01_L					},
/*  690 */		{ 0xB41, &pndef_OBJ_6099_01_H					},
/*  691 */		{ 0xB42, &pndef_OBJ_6099_02_L					},
/*  692 */		{ 0xB43, &pndef_OBJ_6099_02_H					},
/*  693 */		{ 0xB44, &pndef_OBJ_609A_L						},
/*  694 */		{ 0xB45, &pndef_OBJ_609A_H						},
/*  695 */		{ 0xB46, &pndef_OBJ_60B0_L						},
/*  696 */		{ 0xB47, &pndef_OBJ_60B0_H						},
/*  697 */		{ 0xB48, &pndef_OBJ_60B1_L						},
/*  698 */		{ 0xB49, &pndef_OBJ_60B1_H						},
/*  699 */		{ 0xB4A, &pndef_OBJ_60B2_L						},
/*  700 */		{ 0xB4B, &pndef_OBJ_60B2_H						},
/*  701 */		{ 0xB4C, &pndef_OBJ_60B8						},
/*  702 */		{ 0xB4E, &pndef_OBJ_60C1_01_L					},
/*  703 */		{ 0xB4F, &pndef_OBJ_60C1_01_H					},
/*  704 */		{ 0xB50, &pndef_OBJ_60C2_01						},
/*  705 */		{ 0xB51, &pndef_OBJ_60C2_02						},
/*  706 */		{ 0xB52, &pndef_OBJ_60C5_L						},
/*  707 */		{ 0xB53, &pndef_OBJ_60C5_H						},
/*  708 */		{ 0xB54, &pndef_OBJ_60C6_L						},
/*  709 */		{ 0xB55, &pndef_OBJ_60C6_H						},
/*  710 */		{ 0xB56, &pndef_OBJ_60E0						},
/*  711 */		{ 0xB57, &pndef_OBJ_60E1						},
/*  712 */		{ 0xB58, &pndef_OBJ_60FF_L						},
/*  713 */		{ 0xB59, &pndef_OBJ_60FF_H						},
/*  714 */		{ 0xC00, &pndef_typm_e_1						},
/*  715 */		{ 0xC01, &pndef_encver_1						},
/*  716 */		{ 0xC02, &pndef_motw_1							},
/*  717 */		{ 0xC03, &pndef_bit_dp_1						},
/*  718 */		{ 0xC04, &pndef_limmlt_1						},
/*  719 */		{ 0xC05, &pndef_vrat_max_1						},
/*  720 */		{ 0xC06, &pndef_oslv_pol_1						},
/*  721 */		{ 0xC07, &pndef_rattrq_1						},
/*  722 */		{ 0xC08, &pndef_maxtrq_1						},
/*  723 */		{ 0xC09, &pndef_irat_1							},
/*  724 */		{ 0xC0A, &pndef_imax_1							},
/*  725 */		{ 0xC0B, &pndef_emfcmp_1						},
/*  726 */		{ 0xC0C, &pndef_jmot_1							},
/*  727 */		{ 0xC0D, &pndef_motr_1							},
/*  728 */		{ 0xC0E, &pndef_motl_1							},
/*  729 */		{ 0xC0F, &pndef_bastrq_1						},
/*  730 */		{ 0xC10, &pndef_midtrq_1						},
/*  731 */		{ 0xC11, &pndef_midolt_1						},
/*  732 */		{ 0xC12, &pndef_mtrq2_1							},
/*  733 */		{ 0xC13, &pndef_mtolt2_1						},
/*  734 */		{ 0xC14, &pndef_phscmpM1_1						},
/*  735 */		{ 0xC15, &pndef_ppitch_1						},
/*  736 */		{ 0xC16, &pndef_motlq0_1						},
/*  737 */		{ 0xC17, &pndef_motlq1_1						},
/*  738 */		{ 0xC18, &pndef_exp_trat_jmot_1					},
/*  739 */		{ 0xC19, &pndef_exp_motw_spd_1					},
/*  740 */		{ 0xC1A, &pndef_fbit_fdp_1						},
/*  741 */		{ 0xC1B, &pndef_poleoffset_1					},
/*  742 */		{ 0xC1C, &pndef_motresfrq_1						},
/*  743 */		{ 0xC1D, &pndef_phscmpM2_1						},
/*  744 */		{ 0xC1E, &pndef_flg_wf_1						},
#if		OPENSW_PRMDEF >= 1
};
#pragma location =default
/*--------------------------------------------------------------------------------------------------*/
#pragma location =".PnPrmTbl2"
CPRMTBL	PnPrmTbl2[] = {
#endif
/*  745 */		{ 0xE00, &pndef_drvno							},
/*  746 */		{ 0xE01, &pndef_ampw							},
/*  747 */		{ 0xE02, &pndef_VoltType						},
/*  748 */		{ 0xE03, &pndef_irats							},
/*  749 */		{ 0xE04, &pndef_imaxs							},
/*  750 */		{ 0xE05, &pndef_TempOH							},
/*  751 */		{ 0xE06, &pndef_ibs_md							},
/*  752 */		{ 0xE07, &pndef_imdt_mxt						},
/*  753 */		{ 0xE08, &pndef_ratbt_mt						},
/*  754 */		{ 0xE09, &pndef_ratmtt_2						},
/*  755 */		{ 0xE0A, &pndef_ratmt2_os						},
/*  756 */		{ 0xE0B, &pndef_reger							},
/*  757 */		{ 0xE0C, &pndef_wre								},
/*  758 */		{ 0xE0D, &pndef_dbr								},
/*  759 */		{ 0xE0E, &pndef_wdb								},
/*  760 */		{ 0xE10, &pndef_pnvoltgn						},
/*  761 */		{ 0xE11, &pndef_vdetadfil						},
/*  762 */		{ 0xE12, &pndef_pnzero							},
/*  763 */		{ 0xE13, &pndef_pngain							},
/*  764 */		{ 0xE14, &pndef_vdefilsw						},
/*  765 */		{ 0xE15, &pndef_almmsk1							},
/*  766 */		{ 0xE16, &pndef_almmsk2							},
/*  767 */		{ 0xE17, &pndef_MosPump							},
/*  768 */		{ 0xE1B, &pndef_syssw1							},
/*  769 */		{ 0xE1C, &pndef_syssw2							},
/*  770 */		{ 0xE1D, &pndef_syssw3							},
/*  771 */		{ 0xE1E, &pndef_spgfail							},
/*  772 */		{ 0xE1F, &pndef_ifil							},
/*  773 */		{ 0xE20, &pndef_ignd							},
/*  774 */		{ 0xE21, &pndef_ignq							},
/*  775 */		{ 0xE22, &pndef_kid								},
/*  776 */		{ 0xE23, &pndef_kiq								},
/*  777 */		{ 0xE24, &pndef_limintd							},
/*  778 */		{ 0xE25, &pndef_limintq							},
/*  779 */		{ 0xE28, &pndef_shant1							},
/*  780 */		{ 0xE29, &pndef_vrevgn							},
/*  781 */		{ 0xE2A, &pndef_pwmf							},
/*  782 */		{ 0xE2B, &pndef_odt_c							},
/*  783 */		{ 0xE2C, &pndef_ObsGain							},
/*  784 */		{ 0xE32, &pndef_ad_prm3							},
/*  785 */		{ 0xE33, &pndef_ad_prm4							},
/*  786 */		{ 0xE34, &pndef_phscmp							},
/*  787 */		{ 0xE39, &pndef_mtovcnt							},
/*  788 */		{ 0xE44, &pndef_ipg_rwt							},
/*  789 */		{ 0xEA8, &pndef_fbfil2							},
/*  790 */		{ 0xEE0, &pndef_MLess_vrat_max					},
/*  791 */		{ 0xEE1, &pndef_MLess_oslv_pol					},
/*  792 */		{ 0xEE2, &pndef_Mless_jmot						},
/*  793 */		{ 0xEE3, &pndef_Mless_exp_spd_jmot				},
/*  794 */		{ 0xEE4, &pndef_Mless_PlantModel				},
/*  795 */		{ 0xEE5, &pndef_Dm								},
/*  796 */		{ 0xEE6, &pndef_Dl								},
/*  797 */		{ 0xEE7, &pndef_frml							},
/*  798 */		{ 0xEE8, &pndef_ztrml							},
/*  799 */		{ 0xEE9, &pndef_jbrate							},
/*  800 */		{ 0xEEA, &pndef_fnb								},
/*  801 */		{ 0xEEB, &pndef_zb								},
/*  802 */		{ 0xEF3, &pndef_VfAccTime						},
/*  803 */		{ 0xEF4, &pndef_VfSetFreq						},
/*  804 */		{ 0xEF5, &pndef_VfSetVolt						},
/*  805 */		{ 0xEFE, &pndef_usrchk							},
/*  806 */		{ 0xEFF, &pndef_syschk							},
/*  807 */		{ 0xF00, &pndef_typm_e							},
/*  808 */		{ 0xF01, &pndef_encver							},
/*  809 */		{ 0xF02, &pndef_motw							},
/*  810 */		{ 0xF03, &pndef_bit_dp							},
/*  811 */		{ 0xF04, &pndef_limmlt							},
/*  812 */		{ 0xF05, &pndef_vrat_max						},
/*  813 */		{ 0xF06, &pndef_oslv_pol						},
/*  814 */		{ 0xF07, &pndef_rattrq							},
/*  815 */		{ 0xF08, &pndef_maxtrq							},
/*  816 */		{ 0xF09, &pndef_irat							},
/*  817 */		{ 0xF0A, &pndef_imax							},
/*  818 */		{ 0xF0B, &pndef_emfcmp							},
/*  819 */		{ 0xF0C, &pndef_jmot							},
/*  820 */		{ 0xF0D, &pndef_motr							},
/*  821 */		{ 0xF0E, &pndef_motl							},
/*  822 */		{ 0xF0F, &pndef_bastrq							},
/*  823 */		{ 0xF10, &pndef_midtrq							},
/*  824 */		{ 0xF11, &pndef_midolt							},
/*  825 */		{ 0xF12, &pndef_mtrq2							},
/*  826 */		{ 0xF13, &pndef_mtolt2							},
/*  827 */		{ 0xF14, &pndef_phscmpM1						},
/*  828 */		{ 0xF15, &pndef_ppitch							},
/*  829 */		{ 0xF16, &pndef_motlq0							},
/*  830 */		{ 0xF17, &pndef_motlq1							},
/*  831 */		{ 0xF18, &pndef_exp_trat_jmot					},
/*  832 */		{ 0xF19, &pndef_exp_motw_spd					},
/*  833 */		{ 0xF1A, &pndef_fbit_fdp						},
/*  834 */		{ 0xF1B, &pndef_poleoffset						},
/*  835 */		{ 0xF1C, &pndef_motresfrq						},
/*  836 */		{ 0xF1D, &pndef_phscmpM2						},
/*  837 */		{ 0xF1E, &pndef_flg_wf							},
/*  838 */		{ 0xF1F, &pndef_AutoAIAdj						},
};
#if		OPENSW_PRMDEF >= 1
#pragma location =default
#endif
/*--------------------------------------------------------------------------------------------------*/
#if		OPENSW_PRMDEF >= 1
const	USHORT	PnPrmTblEntNum = (sizeof(PnPrmTbl)+sizeof(PnPrmTbl2))/sizeof(PnPrmTbl[0]);
#else
const	USHORT	PnPrmTblEntNum = sizeof(PnPrmTbl)/sizeof(PnPrmTbl[0]);
#endif







/***************************************** end of file **********************************************/
