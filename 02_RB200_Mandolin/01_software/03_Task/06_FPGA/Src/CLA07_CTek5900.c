  
  
  
#include "Main.h"


CONNTEK_VAR CTek_V;

USHORT CTek5900_Status = 0;
LONG  CTek5900_Pos    = 0;
ULONG  CTek5900_PosOri = 0;
LONG  CTek5900_Comp = 0;

volatile USHORT CTek5900_StatusV = 0;
uint16_t KTM59CaliStatus;

LOADCOMPENS_VAR CompensLD;
void CompensateWriteEnable();

#define EEPADR_COMPENS_DATA       0x0728

//-----------------------------------  编码器角度读取指令   ----------------------------------------
const USHORT CTek5900_PosWCmd[5] ={0x2300,0x0000,0x0000,0x0000,0x0000};


 

//-----------------------------------    编码器角度读取   ----------------------------------------
void CTek5900_PosWrite_Cmd( void )
{
    USHORT i;

    for(i = 0; i < 5; i++)
    {
        SPI_writeDataNonBlocking(SPIB_BASE, CTek5900_PosWCmd[i]);
    }
}

 
/*************************************************************/
/*KTM5900-SPIB读编码器位置
 *
 * @20250725 yjp 未核*/
/***********************************************************/
  USHORT KTH5900[5];
  USHORT rData[10] = {0,0,0,0,0,0,0,0,0,0};
void CTek5900_PosRead( void )
{
USHORT i,Len;
ULONG  PosTmp;


    CTek5900_Status = 0;

    Len = SPI_getRxFIFOStatus(SPIB_BASE);
    if( Len != 0)
    {
        for( i = 0; i < Len; i ++)
        {
            rData[ i ] = SPI_readDataNonBlocking(SPIB_BASE);
        }
        KTH5900[0]= rData[ 0 ];
        KTH5900[1]= rData[ 1 ];
        KTH5900[2]= rData[ 2 ];
        KTH5900[3]= rData[ 3 ];
        KTH5900[4]= rData[ 4 ];
     //    if(Crc_Table(KTH5900,3)== KTH5900[3])
        {
//             CTek5900_Pos = ((((ULONG)KTH5900[ 0 ]) << 16) | ((ULONG)(KTH5900[ 1 ]) << 8) | (KTH5900[2])) >> 7;
            CTek5900_PosOri = (((ULONG)KTH5900[ 0 ] << 16) | ((ULONG)KTH5900[ 1 ] << 8) | (ULONG)KTH5900[2]) >> 5;
            if(Prm.Pn534)
                CTek5900_PosOri = FencV.FencPulseNo - CTek5900_PosOri - 1;

			if( POS_COMPENS_ENABLE )
                CTek5900_Comp = IntegralComp(CTek5900_PosOri);
            else
                CTek5900_Comp = CTek5900_PosOri;
			//AinK.Monitor1 = CTek5900_Comp;
            CTek5900_StatusV = (KTH5900[3] & 0xC);
         }
//  //      else
//        {
//            CTek5900_Status |= 0x0100;
//        }

        PosTmp = (CTek5900_Comp + FencV.FencPulseNo - ULONGOF( Prm.PosBOffSetL, Prm.PosBOffSetH )) & 0x7FFFF;
        CTek5900_Pos = PosTmp;
    }
    else
    {
        CTek5900_Status |= 0x0100;
    }
    LoadEncCompensateRun();

    CTek5900_PosWrite_Cmd();

}

/*************************************************************/
/*KTM5900-SPIB写寄存器指令
 * 参考文件：KTM5900_24bit绝对角度磁性编码器_1.5
 *
 * @20250725 yjp 主循环内已核，波形正确，发送指令正确 */
/***********************************************************/
uint16_t CTek5900_WriteReg(uint16_t data, uint16_t Addr, uint32_t base)
{
    uint16_t Len = 0;
    uint16_t i = 0;
    uint16_t safe_word;

    //写指令操作
    uint16_t SpiTxBuf[4] = {0,0,0,0};
    uint16_t SpiRxBuf[8] = {0,0,0,0,0,0,0,0};

    SpiTxBuf[0] = CTek_5900WR_CMD;                // 写指令
    SpiTxBuf[1] = (Addr & 0x0F00);                // 写地址 高4位
    SpiTxBuf[2] = ((Addr & 0xFF) << 8);    //(0xFF00 & (Addr << 8));         // 写地址 低8位
    SpiTxBuf[3] = ((data & 0xFF) << 8);                // 写数据

    while(SPI_isBusy(base));

    //指令发送
    for(i = 0; i < 4; i++)
    {
        SPI_writeDataNonBlocking( base, SpiTxBuf[ i ] );
    }

    /* @20250728 yjp 修改原先的读写顺序，发送指令后把移位寄存器到RxBuf数据直接读走，
     * 后续调用readreg函数能直接读到上一帧写命令的返回值，避免后续要调用两次read，
     * 提升代码效率。
     * @20250728 yjp 考虑删除读的操作，这里读取出来的数据没有参考意义，反倒浪费资源，
     * 如果删除要考虑FIFO数据对齐
     */
    while(SPI_isBusy(base));
    Len = SPI_getRxFIFOStatus(base);
    if( Len != 0 )
    {
        for( i = 0; i < Len; i++ )
        {
            SpiRxBuf[ i ] = SPI_readDataNonBlocking(base);
        }

        // 反馈返回数据
        safe_word = SpiRxBuf[0]  + (SpiRxBuf[1] << 8);
    }

    while(SPI_isBusy(base));

    return safe_word;
}


/*************************************************************/
/*KTM5900-SPIB读寄存器指令
 * 参考文件：KTM5900_24bit绝对角度磁性编码器_1.5
 *
 * @20250725 yjp 主循环内已核，波形正确，读取正确 */
/***********************************************************/
uint16_t CTek5900_ReadReg(uint16_t Addr, uint32_t base)
{
    uint16_t Len = 0;
    uint16_t i = 0;
    uint16_t SpiTxBuf[4] = {0,0,0,0};
    uint16_t SpiRxBuf[8] = {0,0,0,0,0,0,0,0};

    //目标寄存器读地址
    SpiTxBuf[0] = CTek_5900RD_CMD;                // 写指令
    SpiTxBuf[1] = (Addr & 0x0F00);                // 写地址 高4位
    SpiTxBuf[2] = ((Addr & 0xFF) << 8);           //(0xFF00 & (Addr << 8));         // 写地址 低8位
    SpiTxBuf[3] = 0x0000;                         // 忽略

    /*@20250728 yjp 删除原来一次连续发两次数据的操作，
     * 原因：原来的想法是通过两次命令读来获取返回值，但忽视了帧间隔要求；
     * 直接写到TxFIFO里面会导致两帧之间连续，CSN保持时间不够
     * 且为了增加延迟，原来采用的阻塞延时100us，不合适
     */
    for(i = 0; i < 4; i++)
    {
        SPI_writeDataNonBlocking( base, SpiTxBuf[ i ] );
    }

    //等待反馈数据
    while(SPI_isBusy(base));
    Len = SPI_getRxFIFOStatus(base);
    if( Len != 0 )
    {
        for( i = 0; i < Len; i++ )
        {
            SpiRxBuf[ i ] = SPI_readDataNonBlocking(base);
        }
    }

    while(SPI_isBusy(base));

    return SpiRxBuf[1];
}

ULONG CTek5900_PosOriLast  = 0;
void LoadEncCompensateRun()
{
    LONG delta;
    USHORT i;

    if((Prm.AutoAIAdj & 0x80) == 0x80)
    {
        CompensLD.Enable = 1;
    }
    else
    {
        CTek5900_PosOriLast = CTek5900_PosOri;
        return;
    }

    if( CompensLD.Enable )
    {
        //起点开始做混合误差记录
        if(Prm.Pn527 == 1)
        {
            //起点开始做混合误差记录
            delta = MlibABS ((LONG)CTek5900_PosOri - (LONG)CTek5900_PosOriLast);

            if( delta >= (FencV.FencPulseNo >> 1)  && (CoutV.UnMotSpd > 167772)) //要求起始速度在最大转速1%以上开始
            {
                CompensLD.Start = 1;
            }

            //记录128段的混合误差平均值
            if( CompensLD.Start )
            {
                CompensLD.StartCnt ++;
                CompensLD.Sector = CTek5900_PosOri / 4096;
                CompensLD.Count[CompensLD.Sector] ++;
                CompensLD.Sum[CompensLD.Sector] += (AinK.MixUserErr >> 3);
                CompensLD.Record[CompensLD.Sector] = CompensLD.Sum[CompensLD.Sector] / CompensLD.Count[CompensLD.Sector];
            }

            //运行完成1圈，结束64段的混合误差数据记录
            if( CompensLD.Start  && (delta >= (FencV.FencPulseNo >> 1) ) && (CompensLD.StartCnt >= 200))
            {
                CompensLD.Start = 0;
                CompensLD.FirstRec = CompensLD.Record[0];
                for(i = 0; i< 128; i++)
                {
                    CompensLD.FinalRecord[i] = CompensLD.Record[i] - CompensLD.FirstRec;
                    CompensLD.Record[i] = 0;
                    CompensLD.Sum[i] = 0;
                    CompensLD.Count[i] = 0;
                    CompensLD.StartCnt = 0;
                    CompensLD.RecSum += CompensLD.FinalRecord[i];
                }
                CompensLD.FirstRec = 0;
                CompensLD.FinalRecord[128] = 0;
                CompensLD.Enable = 0;
                Prm.AutoAIAdj = 0;
            }
        }
        else
        {

            delta = MlibABS ((LONG)CTek5900_PosOri - (LONG)CTek5900_PosOriLast);

            if( delta >= (FencV.FencPulseNo >> 1)  && ((CoutV.UnMotSpd) > 167772)) //要求起始速度在最大转速1%以上开始
            {
                CompensLD.Start = 1;
            }


            //记录64段的混合误差平均值
            if( (CompensLD.Start == 1)  )
            {
                  CompensLD.StartCnt ++;
                  if( CTek5900_PosOri > (4096UL * (ULONG)CompensLD.Sector))
                  {
                      CompensLD.Record[CompensLD.Sector] = (AinK.MixUserErr >> 3);
                      CompensLD.Sector++;
                  }
            }

            if( (CompensLD.Start == 1) && (delta >= (FencV.FencPulseNo >> 1) ) && (CompensLD.StartCnt >= 200))
            {
                  CompensLD.FirstRec = CompensLD.Record[0];
                  CompensLD.Start = 0;
                  CompensLD.Sector = 0;
                  for(i = 0; i< 128; i++)
                  {
                      CompensLD.FinalRecord[i] = CompensLD.Record[i] - CompensLD.FirstRec;
                      CompensLD.Record[i] = 0;
                      CompensLD.Sum[i] = 0;
                      CompensLD.StartCnt = 0;
                      CompensLD.RecSum += CompensLD.FinalRecord[i];
                  }
                  CompensLD.FirstRec = 0;
                  CompensLD.FinalRecord[128] = 0;
                  CompensLD.Enable = 0;
                  Prm.AutoAIAdj = 0;
            }

        }
    }
    CTek5900_PosOriLast = CTek5900_PosOri;
}

void CompensateWriteEnable()
{
    if((Prm.AutoAIAdj & 0x100) == 0x100)
    {
        CompensLD.WriteEn = 1;
    }
    else
    {
        CompensLD.WriteStep = 0;
        CompensLD.WriteNum = 0;
        return;
    }

    if( CompensLD.WriteEn )
    {
        USHORT Temp;
        switch (CompensLD.WriteStep)
        {
            case 0:
                if(CompensLD.WriteNum <= 130)
                {
                    GetEepromSemaphore( WAIT );
                    WriteEepromEnable( );
                    WriteEepromWord( (EEPADR_COMPENS_DATA + CompensLD.WriteNum), CompensLD.FinalRecord[CompensLD.WriteNum], WAIT );
                    WriteEepromDisable( );
                    FreeEepromSemaphore( );
                    CompensLD.WriteStep ++;
                }
                else
                {
                    CompensLD.WriteStep = 99;
                }
                break;
            case 10:
                CompensLD.WriteNum ++;
                CompensLD.WriteStep = 0;
                break;

            case 99:
                GetEepromSemaphore( WAIT );
                WriteEepromEnable( );
                Temp = (CompensLD.RecSum & 0xffff);
                WriteEepromWord( (EEPADR_COMPENS_DATA -2), Temp , WAIT );
                WriteEepromDisable( );
                FreeEepromSemaphore( );
                CompensLD.WriteStep ++;
                break;

            case 109:
                GetEepromSemaphore( WAIT );
                WriteEepromEnable( );
                Temp = (CompensLD.RecSum >> 16);
                WriteEepromWord( (EEPADR_COMPENS_DATA -1),Temp , WAIT );
                WriteEepromDisable( );
                FreeEepromSemaphore( );
                CompensLD.WriteStep ++;
                break;

            case 119:

                CompensLD.WriteNum = 0;
                CompensLD.WriteEn = 0;
                CompensLD.RecSum = 0;
                Prm.AutoAIAdj = 0;
                CompensLD.WriteStep = 0;
                break;

            default:
                CompensLD.WriteStep ++;
                break;
        }
    }
}


void CompensateRead(void)
{
    USHORT i;
    LONG Tmp;
    stEepromintegral.CheckSum = 0;
    for(i = 0; i< 129; i++)
    {
        Tmp= (SHORT)(ReadEepromWord(EEPADR_COMPENS_DATA + i));
        stEepromintegral.Page1integral[i] = Tmp * 8;
        stEepromintegral.CheckSum += Tmp;
    }
    stEepromintegral.SumL = ReadEepromWord(EEPADR_COMPENS_DATA -2);
    stEepromintegral.SumH = ReadEepromWord(EEPADR_COMPENS_DATA -1);
    stEepromintegral.CheckSumL = (USHORT)(stEepromintegral.CheckSum & 0xffff);
    stEepromintegral.CheckSumH = (USHORT)(stEepromintegral.CheckSum >> 16);

    if( (stEepromintegral.SumL != stEepromintegral.CheckSumL) || (stEepromintegral.SumH != stEepromintegral.CheckSumL))
    {
        if( (Prm.fcplsel & 0x000F == 0x0001) )
        {
            KPI_ALARMSET( ALM_EEPROM3 );
        }
    }


}

/*===========================================
@ Func: CTek5900PosBResret
@ Note: 位置标零
============================================*/
USHORT CTek5900_PosResetEn = 0;
USHORT CTek5900_PosResetStep = 0;

void CTek5900PosBResret(void)
{
    if(((Prm.AutoAIAdj & 0x20) == 0x20) && Kprm.f.FencUse )
    {
        CTek5900_PosResetEn = 1;
    }


    if( CTek5900_PosResetEn && (CTek5900_PosResetStep  == 0))
    {
        if ( Kprm.f.FencUseFlag )
        {
            Prm.MutiBOffSet = 0;
            Prm.PosBOffSetL = CTek5900_Comp & 0xFFFF;
            Prm.PosBOffSetH = CTek5900_Comp >> 16;
        }

        CTek5900_PosResetStep = 1;
    }
    switch( CTek5900_PosResetStep )
    {
        /*------------------------------------------------------------------------------------------*/
        case 0:
        break;
        /*------------------------------------------------------------------------------------------*/
        case 1:
            (void)RpiFunPrmNvmemUpdate( &pndef_MutiBOffSet );                  /* 32位数据一次写入     */
            CTek5900_PosResetStep  ++;
        break;
        case 20:
            (void)RpiFunPrmNvmemUpdate( &pndef_PosBOffSetL );                   /* 16位数据一次写入     */
            CTek5900_PosResetStep  ++;
        break;
        case 40:
            (void)RpiFunPrmNvmemUpdate( &pndef_PosBOffSetH );                   /* 16位数据一次写入     */
            CTek5900_PosResetStep  ++;
        break;
        case 60:
            if(Kprm.f.FencUseFlag)
            {
                CTek5900_PosResetStep  = 100;
            }
            else
            {
                (void)RpiFunPrmNvmemUpdate( &pndef_PosAOffSetL );                   /* 16位数据一次写入     */
                CTek5900_PosResetStep  ++;
            }
        break;
        case 80:
            (void)RpiFunPrmNvmemUpdate( &pndef_PosAOffSetH );                   /* 16位数据一次写入     */
            CTek5900_PosResetStep  ++;
        break;
        case 100:
            CTek5900_PosResetStep  = 0;
            CTek5900_PosResetEn  = 0;
            Prm.AutoAIAdj = 0;
        break;
        /*------------------------------------------------------------------------------------------*/
        default:
            CTek5900_PosResetStep ++;
        break;
    }
}




