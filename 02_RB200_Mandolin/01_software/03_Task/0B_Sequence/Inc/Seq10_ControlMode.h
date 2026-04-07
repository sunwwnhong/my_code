/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
*
* File Name          : Seq10_ControlMode.h
*
* Version            : V0.1
* Date               : 2024
***********************************************************************************************/

 #ifndef Seq10_ControlMode_H
#define Seq10_ControlMode_H

 #if SVFSEL_NETIF_SCANA_CYCLE != 0
	#define BPI_GET_BASE_CTRLMODE( )	AoutV.CtrlMode.b.cm
	#define BPI_GET_BASE_CTRLMODELST( )	AoutV.CtrlModeLst.b.cm
#else
	#define BPI_GET_BASE_CTRLMODE( )	BoutV.CtrlMode.b.cm
	#define BPI_GET_BASE_CTRLMODELST( )	BoutV.CtrlModeLst.b.cm
#endif
 extern USHORT LpxCselControlMode( void );
extern void LpxServoControlMode( void );  
extern void	LpxControlModeManager( void );
 
#endif
