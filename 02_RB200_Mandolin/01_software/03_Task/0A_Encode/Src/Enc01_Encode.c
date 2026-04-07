/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name 		 : Enc01_Encode.c
* Version			 : V0.1
* Date				 : 2024
* Description		 : 编码器EEP中(或程序中)读取写入数据，进行编码器和电机的参数配置
***********************************************************************************************/
#include "Enc01_Encode.h"
 
ENC_STRUCT_DEF EncCodeV;
 
SHORT IcHaus_DataReadDeal( void)
{
    icMuEEPROMRead(SPIA_BASE);

    if( 1 == EncEepExplain() )
    {
        return (1);
    }
    else
    {
        return (2);
    }
}
  
/**********************************************************************************************/
/* Function_Name: MotorEncType_Init         */ 
/* Description  : 根据电机编号，完成编码器配置和编码器EEP数据读取
                  调用：初始化调用一次
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void MotorEncType_Init(void)
{
    SHORT EncReadStatus = 0;
  
    MlibResetLONGMemory( &MencP, sizeof(MencP) / 2);        // 电机编码器相关参数清零			 
    MlibResetLONGMemory( &MencV, sizeof(MencV) / 2 );       // 电机编码器相关变量清零
    MencV.f.EncConnect = 1;     // 置位编码器连接标志                                      

    /*** 获取Prm.b_prm0_0中的电机类型设定字段：0、旋转电机，1、直线电机，2、虚拟电机 ***/
    if( ((Prm.b_prm0_0 >> 12) & 0x000F ) == 0x0002 )
    {
        ApiReadMotPrmMotorLessTestMode();
        return; // 若电机类型为虚拟电机，则读取虚拟测试模式下的电机编码器参数。并函数返回
    }

    /*** 绝对式编码器 ***/
    if(Prm.EncoderType == 11)
    {
        if( (Prm.MotorNum & 0x1000) == 0x1000 )
        {
            //校准模式和IF模式下，无法有效读取电机参数，参考电机代码进行初始化配置
            if(((Prm.PosJump & 0x01) == 0x01) && \
                    ((Prm.b_prm0_0 & 0x000F) == 0x07) )
            {
                MotTableMap( (Prm.MotorNum - 0x1000) );
                return;
            }

            icMuLPFParaWrite();
            icMuStatusRead();

            //其他模式下，上电读取ICHAUS匹配EEPROM的电机参数，并进行累计和校验
            EncReadStatus = IcHaus_DataReadDeal( );
            if( EncReadStatus != 1 )
            {

                KPI_ALARMSET( ALM_PG2 );    // 读取失败，报警编码器EEP中数据异常
                MencV.f.EncConnect = 0;     // 编码器状态切换为：未连接
                MotTableMap( (Prm.MotorNum - 0x1000) );           // 读取默认电机编码器参数组0
                Prm.EncoderType = 11;
                FencV.FencPulseNo = 524288;         // 负载端位数强制为19位
                FencP.MotPulseNo = FencV.FencPulseNo;
            }
            else
            {
                if(((Prm.PosJump & 0x01) == 0x01) || \
                        ((Prm.b_prm0_0 & 0x000F) == 0x07) )
                {
                    //MotTableMap( (Prm.MotorNum - 0x1000) );
                    return;
                }
                Prm.EncoderType = 11;
                FencV.FencPulseNo = 524288;         // 负载端位数强制为19位
                FencP.MotPulseNo = FencV.FencPulseNo;
            }
        }
    }
    else if(Prm.EncoderType == 13)
    {

        /*** 绝对式编码器 ***/
        if( (Prm.MotorNum & 0x01000) == 0x01000 )
        {
            //校准模式和IF模式下，无法有效读取电机参数，参考电机代码进行初始化配置
            if((Prm.b_prm0_0 & 0x000F) == 0x07 )
            {
                MotTableMap( (Prm.MotorNum - 0x1000) );
                return;
            }

            //其他模式下，上电读取ICHAUS匹配EEPROM的电机参数，并进行累计和校验
            EncReadStatus = 1;                //TODO
            if( EncReadStatus != 1 )
            {

                KPI_ALARMSET( ALM_PG2 );    // 读取失败，报警编码器EEP中数据异常
                MencV.f.EncConnect = 0;     // 编码器状态切换为：未连接
                MotTableMap( (Prm.MotorNum - 0x1000) );           // 读取默认电机编码器参数组0
                Prm.EncoderType = 13;
            }
            else
            {
                MotTableMap( (Prm.MotorNum - 0x1000) );
                Prm.EncoderType = 13;
                //执行位置指令获取，为下一个周期获取位置信息做准备

            }
        }
    }
   	 
 	else
	{
		MotTableMap( 0 );		        // 读取默认电机编码器参数组0						 
	 	KPI_ALARMSET( ALM_SCL_ERR );    // 电机编号不存在                 
        MencV.f.EncConnect = 0;         // 编码器状态切换为：未连接                         
	}
}
  
  
/**********************************************************************************************/
/* Function_Name: MEncClrDeal         */ 
/* Description  : 多圈绝对值数据清除
                  调用：主循环2ms任务中调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void MEncClrDeal(void)
{
    /*** Pn07F : 编码器多圈和故障清除，有清除命令并且伺服未使能下，执行清除 ***/
    if( Prm.EncErrClr == 1 && StateM_Var.f.BaseEnable == 0 )
    {
        Prm.EncErrClr = 0; // 命令自动清除，单次有效
        EncCodeV.MEncClrStep = 0;
        EncCodeV.MEncClrCmd = 1;                             
    }
   	 
 	if( EncCodeV.MEncClrCmd == 0 )
	{
		return; // 清除命令为0，返回
	}
      
    BpxEdgeClrSvcPositionManager( );
 	 
	if(MencP.FATypeCode == 0x01)    // 多摩川编码器
	{
 	  	EncCodeV.MEncClrStatus = TamakawaMencClrStep(); // 多摩川编码器多圈清除
	}
	else
	{
 	}
 	 
 	if(EncCodeV.MEncClrStatus != 0)
    {
		EncCodeV.MEncClrCmd = 0;    // EncCodeV.MEncClrStatus一旦等于1，表示多圈清除完成，清零清除指令
    }
}
  
 /**********************************************************************************************/
 /* Function_Name: MotorInfWriteToEnc         */ 
 /* Description  : 电机信息写入编码器Eeprom  
                   调用：主循环2ms任务中调用
                   输入：
                   输出：     */
 /**********************************************************************************************/
 void MotorInfWriteToEnc(void)
{
    if(EncCodeV.DataWriteToEeprom == 0x0000)
    {
        return;
    }
 	 
 	switch(Prm.EncoderType)
    {
    	case 2:      
        case 3:      
		  	TamagawaEncWriteMnge();
		  	break;
        case 11:
            icMuEEPROMWrite();
            break;
         case 9:
            break;
 #if 0
        case 4:      
        case 5:      
        case 6:      
        case 7:      
        case 8:      
         default:     
            KPI_ALARMSET( ALM_PRM );							           
            break;
#endif
    }
}
