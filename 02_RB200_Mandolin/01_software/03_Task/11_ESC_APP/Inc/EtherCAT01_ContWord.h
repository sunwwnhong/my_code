/*
 * EtherCAT15_ContWord.h
 *
 *  Created on: 2018年05月06日
 *      Author: zhuxc
 */

#ifndef EtherCAT15_ContWord_H
#define EtherCAT15_ContWord_H

/****************************************************************************************************/
/*																									*/
/*									Defines and Typedef												*/
/*																									*/
/****************************************************************************************************/


/*--------------------------------------------------------------------------------------------------*/
typedef	union
{
	USHORT w;
	/*----------------------------------------------------------------------------------------------*/
	struct {
				USHORT    Rdy2SwitchOn      	:1;				/* 0.伺服准备好						*/
				USHORT    SwitchOn        		:1;				/* 1.电源已接通状态					*/
				USHORT    OperationEnable       :1;				/* 2.伺服运行						*/
				USHORT    Fault        			:1;				/* 3.故障							*/
				USHORT    VoltEnabled         	:1;				/* 4.主回路电接通					*/
				USHORT    QuickStop      		:1;				/* 5.快速停机						*/
				USHORT    SwitchOnDisable       :1;				/* 6.通电允许运行					*/
				USHORT    Warning      			:1;				/* 7.警告							*/
				USHORT    ManufSpeci         	:1;				/* 8.厂家自定义						*/
				USHORT    Remote           		:1;				/* 9.远程控制                       */
				USHORT    TargetReach         	:1;				/* 10.目标到达						*/
				USHORT    InternalLimitActive	:1;				/* 11.内部限制有效					*/
                USHORT    ZeroSpd               :1;             /* 12.零速信号                      */
				USHORT    OperationModeSpeckfic	:1;				/* 13运行模式相关				    */
				USHORT    ManufSpecific         :1;				/* 14.厂家自定义					*/
				USHORT    HomeFind         		:1;				/* 15.原点已找到					*/
		} f;
        /*------------------------------------------------------------------------------------------*/
}STATUSWORD_STRUCT;

/*--------------------------------------------------------------------------------------------------*/
typedef	union
{
	USHORT w;
	/*----------------------------------------------------------------------------------------------*/
	struct {
				USHORT    SwitchOn      		:1;				/* 0.接通电源             			*/
				USHORT    EnableVoltage     	:1;          	/* 1.使能供电	                    */
				USHORT    QuickStop       		:1;             /* 2.紧急停止           			*/
				USHORT    EnableOper        	:1;             /* 3.使能运行                       */
				USHORT    OperationModeSpec1 	:3;           	/* 4-6运行模式相关                  */
				USHORT    FaultReset			:1;             /* 7.故障复位                     	*/
				USHORT    Halt					:1;             /* 8.暂停                     		*/
				USHORT    OperationModeSpec2	:1;             /* 9.运行模式相关                   */
				USHORT    Reverse1				:1;             /* 10.保留               			*/
				USHORT    OpenPosCtrl           :1;             /* 11.CAN开环轮廓位置模式            */
				USHORT    OpenPosMod            :1;             /* 12.开环轮廓位置所走的位置量计入位置模式    */
				USHORT    SoftReset             :1;             /* 13.软复位                         */
				USHORT    ManufactSpec			:2;             /* 14-15.厂家自定义                   */
		} f;
        /*------------------------------------------------------------------------------------------*/
}CONTROLWORD_STRUCT;

/*--------------------------------------------------------------------------------------------------*/
typedef	union
{
	USHORT w;
	/*----------------------------------------------------------------------------------------------*/
	struct {
				USHORT    NoReady      			:1;				/* 0.未准备好接通电源      			*/
				USHORT    NoSwitchOn     		:1;          	/* 1.不可接通电源	                */
				USHORT    RdySwitchOn       	:1;             /* 2.准备好接通电源           		*/
				USHORT    SwitchOn        		:1;             /* 3.已开始供电                     */
				USHORT    EnOperation 			:1;           	/* 4.可操作                 		*/
				USHORT    Fault					:1;             /* 5.出错                     		*/
				USHORT    Emergy				:1;             /* 6急停                     		*/
				USHORT    Reverse1				:9;             /* 保留               				*/
		} f;
        /*------------------------------------------------------------------------------------------*/
}STATEMACHINE_STRUCT;

extern UCHAR EtherCAT_ControlStatus;
extern void Ds402Status_ControlWordDeal(void);
extern UCHAR HaltEndFlag;

extern CONTROLWORD_STRUCT ControlWord;
extern STATUSWORD_STRUCT  StatusWord;

#endif
