/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Mot63_MulAxis_485.c
* Version            : V0.1
* Date               : 2024
* Description        : 485双轴通讯（非标准协议）
***********************************************************************************************/

  
#include "Main.h"
volatile USHORT MuxAxis_WriteBuf[ 8 ];

volatile USHORT MuxAxis_ReadBuf[ 16 ];     //双轴信息读取
  
volatile USHORT MulAxis_OffCnt = 0;
volatile USHORT MulAxis_ComEn  = 0;
  
/************************************************************************************/
/* Function_Name: MuxAxis485_Init                                                */
/* Description  : 485双轴通讯初始化
  调  用     :   上电初始化                                                             */
/************************************************************************************/
void MuxAxis485_Init( void )
{
USHORT i;
    for( i = 0; i < 8; i ++ )
    {
        MuxAxis_WriteBuf[ i ] = 0;
    }
    for( i = 0; i < 16; i ++ )
    {
        MuxAxis_ReadBuf[ i ] = 0;
    }
     MulAxis_OffCnt = 0;
    MulAxis_ComEn  = 0;
    return;
}
  
  
/************************************************************************************/
/* Function_Name: MuxAxis485_Write                                                */
/* Description  : 485双轴通讯寄存器写入
  调  用     :                                                                */
/************************************************************************************/
USHORT MuxAxis485_Write( LONG RegNo, LONG Number, USHORT *RdBuf )
{
USHORT i;
SHORT Addr = RegNo - 2000;
    if( Addr < 0 )
    {
        return 0;
    }
    if( (Addr + Number) > 8 )    
    {
        return 0;
    }
    for( i = 0; i < Number; i ++)
    {
        MuxAxis_WriteBuf[ Addr + i ] = RdBuf[ i ];
    }
 
    //MotB_SerOnOff   = MuxAxis_WriteBuf[ 3 ];
    //MotB_SpdDir     = MuxAxis_WriteBuf[ 5 ];
    //MotB_SpdCmd     = MuxAxis_WriteBuf[ 7 ];
      
    MulAxis_OffCnt = 0;
    MulAxis_ComEn  = 1;
    return 1;
}
  
  
/************************************************************************************/
/* Function_Name: MuxAxis485_Read                                                */
/* Description  : 485双轴通讯寄存器读取
  调  用     :                                                               */
/************************************************************************************/
USHORT MuxAxis485_Read( LONG RegNo, LONG Number, USHORT *RdBuf )
{
USHORT i;
SHORT Addr = RegNo - 1000;
     if( Addr < 0 )       
    {
        return 0;
    }
    if( (Addr + Number) > 15 )    
    {
        return 0;
    }
     MuxAxis_ReadBuf[ 0 ] = KpiMonCurrentCal1( CoutV.UnCrntDet ) * 10;        
    //MuxAxis_ReadBuf[ 1 ] = MotB_Iee;
     MuxAxis_ReadBuf[ 2 ] = KpiMonSpeedCal( CoutV.UnMotSpd );                 
    //MuxAxis_ReadBuf[ 3 ] = MotB_Spd;
     MuxAxis_ReadBuf[ 4 ] = BinK.UnDcVolt;                                    
    MuxAxis_ReadBuf[ 6 ] = MuxAxis_ReadBuf[ 4 ];
     MuxAxis_ReadBuf[ 5 ] = Alm.AlmWrnCode;                                   
    //MuxAxis_ReadBuf[ 7 ] = MotB_Errcode;
     for( i = 0; i < Number; i ++)
    {
        RdBuf[ 2 * i ]    = (MuxAxis_ReadBuf[ i ] >> 8) & 0x00FF;
        RdBuf[ 2 * i + 1] = MuxAxis_ReadBuf[ i ] & 0x00FF;
    }
      
    MulAxis_OffCnt = 0;
    MulAxis_ComEn  = 1;
    return 1;
}
  
  
/************************************************************************************/
/* Function_Name: MuxAxis485_SpdCmd                                                */
/* Description  : 485双轴速度指令发送
  调  用     :                                                               */
/************************************************************************************/
SHORT MuxAxis485_SpdCmd( void )
{
SHORT Spd;
#ifdef CPU1
    if( MuxAxis_WriteBuf [ 4 ] == 0 )
    {
        Spd = MuxAxis_WriteBuf [ 6 ];
    }
    else
    {
        Spd = -((SHORT)MuxAxis_WriteBuf [ 6 ]);
    }
     if( MuxAxis_WriteBuf [ 2 ] == 3 )
    {
        Spd = 0;
    }
 #endif
    return Spd;
}
  
  
/************************************************************************************/
/* Function_Name: MuxAxis485_ServoOnoff                                                */
/* Description  : 485双轴伺服使能命令
  调  用     :                                                               */
/************************************************************************************/
SHORT MuxAxis485_ServoOnoff( void )
{
#ifdef CPU1
    if( MuxAxis_WriteBuf [ 2 ] == 0 )
    {
        return 0;
    }
    else if( MuxAxis_WriteBuf [ 2 ] == 1 )
    {
        return 1;
    }
    else
    {
        return 1;
    }
#endif
}
  
  
/************************************************************************************/
/* Function_Name: MuxAxis485_LineOff                                                */
/* Description  : 双轴伺服通讯掉线判定
  调  用     :                                                               */
/************************************************************************************/
void MuxAxis485_LineOff( void )
{
#ifdef CPU1
    if( 3 != Prm.spdSource)
    {
        return;
    }
    if( 0 == MulAxis_ComEn )
    {
        MulAxis_OffCnt = 0;
        return;
    }
    MulAxis_OffCnt ++;
    if( MulAxis_OffCnt > 75 )
    {
        MuxAxis_WriteBuf [ 2 ] = 0;
        //MotB_SerOnOff = 0;
         MulAxis_ComEn = 0;
        MulAxis_OffCnt = 0;
         KPI_ALARMSET( ALM_CAN_MOFF );
    }
#endif
}
 
