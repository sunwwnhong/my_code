/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : CLA06_IcHaus.c
* Version            : V0.1
* Date               : 2024
* Description        : ICHaus编码器接口函数
*                     （位置获取采用SCANA循环获取，EEPROM与寄存器操作采用阻塞操作方式）
***********************************************************************************************/


#include "Main.h"

//0x0A:连续读取角度寄存器
USHORT icMu_Status_A = 0;               // ICMU电机端芯片状态（参考MencV.EncStatus位定义）
USHORT icMu_Status_B = 0;               // ICMU负载端芯片状态（参考MencV.EncStatus位定义）
USHORT icMuPosA[10];                    // ICMU电机位置接收数据（0xA6）
USHORT icMuPosB[10];                    // ICMU负载位置接收数据（0xA6）

USHORT icMu_SPI_Fault = 0;              // ICMU芯片SPI通讯状态（0：正常 1：异常）

USHORT MEncWriteErrCnt = 0;             // ICMU芯片写入错误计数

ULONG MultiPos_A = 0;                   // ICMU电机端芯片多圈获取值
ULONG MultiPos_B = 0;                   // ICMU负载端芯片多圈获取值
ULONG icMu_Pos_A = 0;                   // ICMU电机端芯片单圈获取值
ULONG icMu_Pos_B = 0;                   // ICMU负载端芯片单圈获取值
ULONG icMu_Pos_B_Ori = 0;                   // ICMU负载端芯片单圈获取值
LONG icMu_Pos_B_Err = 0;                   // ICMU负载端芯片单圈获取值


void icMuPosWrite_Cmd_MT( uint32_t base );
void icMuPosWrite_Cmd_ST( uint32_t base );
USHORT icMuRegistRead( USHORT add, uint32_t base );




StructTypeEepromRWPage1integral         stEepromintegral ;      //积分补偿数据结构体

StructTypeEepromMotEnc    MotEncCompData ;

typedef struct
{
    uint8_t PosValue[3];                /* 位置信息                         */
    uint8_t Bit;                        /* 编码器精度                        */
    uint8_t LpfLev;                     /* 编码器滤波等级                  */
    uint8_t LpfLevLd;                     /* 编码器滤波等级                  */
    /*----------------------------------------------------------------------------------------------*/
}  POS_VAR_DEF;

POS_VAR_DEF PosV;       /*暂时未用*/

void icMuDataReciveA( void );




/**********************************************************************************************/
/* Function_Name: icMuBankSw         */
/* Description  : iCHaus切换BANK操作
               调用：写入编码器EEPROM时调用
               输入：
               输出：   */
/**********************************************************************************************/
void icMuBankSw( USHORT bank, uint32_t base)
{
    USHORT Len = 0;
    USHORT i;
    USHORT Buff[16];

    USHORT DataTmp1 = 0;
    /*iCHaus切换BANK状态获取 0：切换BANK中 1:状态判定中 2：切换完成 3：切换失败*/
    USHORT Sts = 0;
    /* 切换完成后返回，该过程采用阻塞方案处理，在写入过程中需要屏蔽其他中断 */
    while(Sts != 2)
    {
        /*IDLE状态下，写入BANK号*/
        if(Sts == 0)
        {
            //等待SPI空闲
            while(SPI_isBusy(base));

            //发送 0xD2 0x40(BANKSEL) 0xXX(BANK号) Write REGISTER
            Buff[ 0 ] = 0xD200;
            Buff[ 1 ] = 0x4000;
            Buff[ 2 ] = (bank) << 8 ;

            for(i = 0; i < 3; i++)
            {
               SPI_writeDataNonBlocking(base, Buff[ i ]);
            }

            KlibWaitus(50);

            //等待SPI空闲
            while(SPI_isBusy(base));

            //获取数据后，切换至状态 1，对当前切换状态进行判定
            Len = SPI_getRxFIFOStatus(base);
            if( Len != 0 )
            {
                for( i = 0; i < Len; i++ )
                {
                    Buff[ i ] = SPI_readDataNonBlocking(base);
                }
            }
            Sts = 1;
        }
        else if(Sts == 1)
        {
            //发送 0xAD REGISTER status/data 获取icHaus状态
            while(SPI_isBusy(base));
            SPI_writeDataNonBlocking(base, 0xAD00);
            SPI_writeDataNonBlocking(base, 0x0000);
            KlibWaitus(50);

            while(SPI_isBusy(base));
            //获取返回状态
            Len = SPI_getRxFIFOStatus(base);
            if( Len != 0 )
            {
                for( i = 0; i < Len; i++ )
                {
                    Buff[ i ] = SPI_readDataNonBlocking(base);
                }
            }

            DataTmp1 = Buff[ 1 ];

            /*iCHaus状态判定*/
            if((DataTmp1 & 0x02) == 0x02)
            {
                //总线忙
                MEncWriteErrCnt++;
                if(MEncWriteErrCnt > 100 )
                {
                    icMu_SPI_Fault = 1;
                    MEncWriteErrCnt = 0;
                    Sts = 2;            //  TODO: Sts =3
                }
            }
            else
            {
                //----------------------------------
                if((DataTmp1 & 0x04) == 0x04)
                {
                    //数据请求失败,重新再请求一次
                    MEncWriteErrCnt++;
                    if(MEncWriteErrCnt > 100 )
                    {
                        icMu_SPI_Fault = 1;
                        MEncWriteErrCnt = 0;
                        Sts = 2;        //  TODO: Sts =3
                    }
                }
                else
                {
                    //----------------------------------
                    if((DataTmp1 & 0x88) != 0x00)
                    {
                        //错误,对应错误处理措施
                        MEncWriteErrCnt++;
                        if(MEncWriteErrCnt > 100 )
                        {
                            icMu_SPI_Fault = 1;
                            MEncWriteErrCnt = 0;
                            Sts = 2;        //  TODO: Sts =3
                        }
                    }
                    else
                    {
                        //数据有效
                        Sts = 2;            //  TODO: Sts =2
                        MEncWriteErrCnt = 0;
                    }
                }
            }
        }
    }
    //  TODO: Sts故障状态待调试
    if(Sts == 3)
    {
        icMu_SPI_Fault = 1;
    }
}

/**********************************************************************************************/
/* Function_Name: icMuDataRead         */
/* Description  : icMu数据读取
               调用：上电读取编码器EEPROM时调用
               输入：
               输出：   */
/**********************************************************************************************/
USHORT icMuDataRead( USHORT add, uint32_t base )
{
    USHORT Len = 0;
    USHORT i;
    USHORT Buff[16];

    USHORT Sts = 0;
    USHORT datatmp = 0;
    USHORT DataTmp1 = 0;

    /*iCHaus切换BANK状态获取 0：切换BANK中 1:状态判定中 2：切换完成 3：切换失败*/
    while(Sts != 2 )
    {
        /*IDLE状态下，写入BANK号*/
        if(Sts == 0)
        {
            //发送 0x97 0xXX(BANK号) Read REGISTER
            Buff[ 0 ] = 0x9700;
            Buff[ 1 ] = (add & 0x3f) << 8 ;

            while(SPI_isBusy(base));

            SPI_writeDataNonBlocking(base, Buff[ 0 ]);
            SPI_writeDataNonBlocking(base, Buff[ 1 ]);

            KlibWaitus(50);
            while(SPI_isBusy(base));
            //获取数据后，切换至状态 1，对当前切换状态进行判定
            Len = SPI_getRxFIFOStatus(base);
            if( Len != 0 )
            {
                for( i = 0; i < Len; i++ )
                {
                    Buff[ i ] = SPI_readDataNonBlocking(base);
                }
            }
            Sts = 1;
        }
        else if(Sts == 1)
        {
            //发送 0xAD REGISTER status/data 获取icHaus状态
            while(SPI_isBusy(base));
            SPI_writeDataNonBlocking(base, 0xAD00);
            SPI_writeDataNonBlocking(base, 0x0000);
            SPI_writeDataNonBlocking(base, 0x0000);

            KlibWaitus(50);

            while(SPI_isBusy(base));

            //获取返回状态
            Len = SPI_getRxFIFOStatus(base);
            if( Len != 0 )
            {
                for( i = 0; i < Len; i++ )
                {
                    Buff[ i ] = SPI_readDataNonBlocking(base);
                }
            }
            DataTmp1 = Buff[1];

            /*iCHaus状态判定*/
            if((DataTmp1 & 0x02) == 0x02)
            {
                //总线忙
                MEncWriteErrCnt++;
                if(MEncWriteErrCnt > 100 )
                {
                    icMu_SPI_Fault = 1;
                    MEncWriteErrCnt = 0;
                    Sts = 2;
                }
            }
            else
            {
                //----------------------------------
                if((DataTmp1 & 0x04) == 0x04)
                {
                    //数据请求失败,重新再请求一次
                    MEncWriteErrCnt++;
                    if(MEncWriteErrCnt > 100 )
                    {
                        icMu_SPI_Fault = 1;
                        MEncWriteErrCnt = 0;
                        Sts = 2;
                    }
                }
                else
                {
                    //----------------------------------
                    if((DataTmp1 & 0x88) != 0x00)
                    {
                        //错误,对应错误处理措施
                        MEncWriteErrCnt++;
                        if(MEncWriteErrCnt > 100 )
                        {
                            icMu_SPI_Fault = 1;
                            MEncWriteErrCnt = 0;
                            Sts = 2;
                        }
                    }
                    else
                    {
                        //数据有效
                        Sts = 2;
                        MEncWriteErrCnt = 0;
                        datatmp = Buff[ 2 ];
                    }
                }
            }
        }
    }
    return datatmp;
}


USHORT icMuRegistRead( USHORT add, uint32_t base )
{
    USHORT Len = 0;
    USHORT i;
    USHORT Buff[16];

    USHORT Sts = 0;
    USHORT datatmp = 0;
    USHORT DataTmp1 = 0;

    /*iCHaus切换BANK状态获取 0：切换BANK中 1:状态判定中 2：切换完成 3：切换失败*/
    while(Sts != 2 )
    {
        /*IDLE状态下，写入BANK号*/
        if(Sts == 0)
        {
            //发送 0x97 0xXX(BANK号) Read REGISTER
            Buff[ 0 ] = 0x9700;
            Buff[ 1 ] = add << 8 ;

            while(SPI_isBusy(base));

            SPI_writeDataNonBlocking(base, Buff[ 0 ]);
            SPI_writeDataNonBlocking(base, Buff[ 1 ]);

            KlibWaitus(50);
            while(SPI_isBusy(base));
            //获取数据后，切换至状态 1，对当前切换状态进行判定
            Len = SPI_getRxFIFOStatus(base);
            if( Len != 0 )
            {
                for( i = 0; i < Len; i++ )
                {
                    Buff[ i ] = SPI_readDataNonBlocking(base);
                }
            }
            Sts = 1;
        }
        else if(Sts == 1)
        {
            //发送 0xAD REGISTER status/data 获取icHaus状态
            while(SPI_isBusy(base));
            SPI_writeDataNonBlocking(base, 0xAD00);
            SPI_writeDataNonBlocking(base, 0x0000);
            SPI_writeDataNonBlocking(base, 0x0000);

            KlibWaitus(50);

            while(SPI_isBusy(base));

            //获取返回状态
            Len = SPI_getRxFIFOStatus(base);
            if( Len != 0 )
            {
                for( i = 0; i < Len; i++ )
                {
                    Buff[ i ] = SPI_readDataNonBlocking(base);
                }
            }
            DataTmp1 = Buff[1];

            /*iCHaus状态判定*/
            if((DataTmp1 & 0x02) == 0x02)
            {
                //总线忙
                MEncWriteErrCnt++;
                if(MEncWriteErrCnt > 100 )
                {
                    icMu_SPI_Fault = 1;
                    MEncWriteErrCnt = 0;
                    Sts = 2;
                }
            }
            else
            {
                //----------------------------------
                if((DataTmp1 & 0x04) == 0x04)
                {
                    //数据请求失败,重新再请求一次
                    MEncWriteErrCnt++;
                    if(MEncWriteErrCnt > 100 )
                    {
                        icMu_SPI_Fault = 1;
                        MEncWriteErrCnt = 0;
                        Sts = 2;
                    }
                }
                else
                {
                    //----------------------------------
                    if((DataTmp1 & 0x88) != 0x00)
                    {
                        //错误,对应错误处理措施
                        MEncWriteErrCnt++;
                        if(MEncWriteErrCnt > 100 )
                        {
                            icMu_SPI_Fault = 1;
                            MEncWriteErrCnt = 0;
                            Sts = 2;
                        }
                    }
                    else
                    {
                        //数据有效
                        Sts = 2;
                        MEncWriteErrCnt = 0;
                        datatmp = Buff[ 2 ];
                    }
                }
            }
        }
    }
    return datatmp;
}
/**********************************************************************************************/
/* Function_Name: icMuDataWrite         */
/* Description  : icMu数据写入
               输入：
               输出：   */
/**********************************************************************************************/
void icMuDataWrite( USHORT add , USHORT data, uint32_t base )
{
    USHORT Len = 0;
    USHORT i;
    USHORT Buff[16];

    USHORT Sts = 0;
    USHORT DataTmp1 = 0;

    while (Sts != 2)
    {
        //发送 0xD2 0xXX(地址) 0xxx（数据） Write REGISTER
        if(Sts == 0)
        {
            Buff[ 0 ] = 0xD200;
            Buff[ 1 ] = (add & 0x3f) << 8 ;
            Buff[ 2 ] = data << 8 ;

            while(SPI_isBusy(base));

            SPI_writeDataNonBlocking(base, Buff[ 0 ]);
            SPI_writeDataNonBlocking(base, Buff[ 1 ]);
            SPI_writeDataNonBlocking(base, Buff[ 2 ]);

            KlibWaitus(50);
            while(SPI_isBusy(base));

            //获取数据后，切换至状态 1，对当前切换状态进行判定
            Len = SPI_getRxFIFOStatus(base);
            if( Len != 0 )
            {
                for( i = 0; i < Len; i++ )
                {
                    Buff[ i ] = SPI_readDataNonBlocking(base);
                }
            }
            Sts = 1;
        }
        else if (Sts == 1)
        {
            //发送 0xAD REGISTER status/data 获取icHaus状态
            while(SPI_isBusy(base));
            SPI_writeDataNonBlocking(base, 0xAD00);
            SPI_writeDataNonBlocking(base, 0x0000);
            KlibWaitus(50);

            while(SPI_isBusy(base));

            //获取返回状态
            Len = SPI_getRxFIFOStatus(base);
            if( Len != 0 )
            {
                for( i = 0; i < Len; i++ )
                {
                    Buff[ i ] = SPI_readDataNonBlocking(base);
                }
            }

            DataTmp1 = Buff[1];

            if((DataTmp1 & 0x02) == 0x02)
            {
                //总线忙
                MEncWriteErrCnt++;
                if(MEncWriteErrCnt > 100 )
                {
                    icMu_SPI_Fault = 1;
                    MEncWriteErrCnt = 0;
                    Sts = 2;
                }

            }
            else
            {
                //----------------------------------
                if((DataTmp1 & 0x04) == 0x04)
                {
                    //数据请求失败,重新再请求一次
                    MEncWriteErrCnt++;
                    if(MEncWriteErrCnt > 100 )
                    {
                        icMu_SPI_Fault = 1;
                        MEncWriteErrCnt = 0;
                        Sts = 2;
                    }
                }
                else
                {
                    //----------------------------------
                    if((DataTmp1 & 0x88) != 0x00)
                    {
                        //错误,对应错误处理措施
                        MEncWriteErrCnt++;
                        if(MEncWriteErrCnt > 100 )
                        {
                            icMu_SPI_Fault = 1;
                            MEncWriteErrCnt = 0;
                            Sts = 2;
                        }
                    }
                    else
                    {
                        //数据有效
                        MEncWriteErrCnt = 0;
                        Sts = 2;
                    }
                }
            }

        }
    }
}
/**********************************************************************************************/
/* Function_Name: icMuLPFParaWrite         */
/* Description  : iCHaus滤波系数写入（暂未用，通过iCMu上位机写入）
               调用：
               输入：
               输出：   */
/**********************************************************************************************/
void icMuLPFParaWrite(void )
{
    PosV.LpfLev = (Prm.PosJump & 0xF000) >> 12;
    icMuBankSw(0x00,SPIA_BASE);
    icMuDataWrite(0x0e,(0xe8+PosV.LpfLev),SPIA_BASE);

//    if( (Prm.fcplsel & 0x000F) == 0x01)
//    {
//        PosV.LpfLevLd = (Prm.Icmu & 0x000F) ;
//        icMuBankSw(0x00,SPIB_BASE);
//        icMuDataWrite(0x0e,(0xe8+PosV.LpfLevLd),SPIB_BASE);
//    }
}

UCHAR MU_Status0;
UCHAR MU_Status1;
UCHAR MU150_Status0;
UCHAR MU150_Status1;

USHORT icMu_PowerUp_Fault = 0;              // ICMU芯片SPI通讯状态（0：正常 1：异常）
USHORT icMu150_PowerUp_Fault = 0;              // ICMU芯片SPI通讯状态（0：正常 1：异常）

void icMuStatusRead( void )
{
    UCHAR Status0,Status1;

    //icMuDataReciveA();

//    icMuBankSw(0x00,SPIA_BASE);   //切换至BANK5,编码数据存储在BANK中,准备读取
    MU_Status0 = icMuRegistRead(0x76,SPIA_BASE);
    MU_Status1 = icMuRegistRead(0x77,SPIA_BASE);


    if( ((MU_Status0 & 0x0f) == 0) && ((MU_Status1 & 0x7f) == 0))
    {
        icMu_PowerUp_Fault = 0;
    }
    else
        icMu_PowerUp_Fault = 1;

    //KlibWaitms(5000);

//    //icMuBankSw(0x00,SPIB_BASE);   //切换至BANK5,编码数据存储在BANK中,准备读取
//    if( (Prm.fcplsel & 0x000F) == 0x01)
//    {
//        MU150_Status0 = icMuRegistRead(0x76,SPIB_BASE);
//        MU150_Status1 = icMuRegistRead(0x77,SPIB_BASE);
//
//
//        if( ((MU150_Status0 & 0x0f) == 0) && ((MU150_Status1 & 0x7f) == 0))
//        {
//            icMu150_PowerUp_Fault = 0;
//        }
//        else
//            icMu150_PowerUp_Fault = 1;
//    }
//    AinK.Monitor2 = (MU150_Status0 << 8) + MU150_Status1;

}


UCHAR EEPROM_Data_Rd[64];
UCHAR EEPROM_Data_Wr[64];

/**********************************************************************************************/
/* Function_Name: icMuEEPROMRead         */
/* Description  : 上电EEPROM读取（BANK区域可存放32个byte数据，超出范围切换至下一个BANK）
               输入：
               输出：   */
/**********************************************************************************************/
void icMuEEPROMRead( uint32_t base )
{
    USHORT i;
    USHORT addr;
    USHORT dataH,dataL;
    icMuBankSw(0x05, base);   //切换至BANK5,编码数据存储在BANK中,准备读取

    //循环读取BANK5的所有数据
    for(i=0 ; i<32;i++)
    {

        addr = (i<< 1);
        dataL = (icMuDataRead(addr,base) & 0xff);
        dataH = (icMuDataRead(addr+1,base) & 0xff);
        EncCodeV.ENCDataBuf[i] = (dataH << 8) + dataL;
    }

    icMuBankSw(0x06,base);   //切换至BANK6,编码数据存储在BANK中,准备读取

    //循环读取BANK6的所有数据
    for(i=32 ; i<EncEepromDataNum ;i++)
    {

        addr = ((i-32)<< 1);
        dataL = (icMuDataRead(addr,base) & 0xff);
        dataH = (icMuDataRead(addr+1,base) & 0xff);
        EncCodeV.ENCDataBuf[i] = (dataH << 8) + dataL;
    }
}

/**********************************************************************************************/
/* Function_Name: icMuEEPROMWrite         */
/* Description  : EEPROM写入（BANK区域可存放32个byte数据，超出范围切换至下一个BANK）
               输入：
               输出：   */
/**********************************************************************************************/
void icMuEEPROMWrite(void)
{
    USHORT i;
    USHORT addr;

    icMuDataReciveA();      //执行EERPROM操作前，需要先读取MU的位置数据

    //写入数据打包
    EncEepBufPackage();

    //切换至BANK5,编码数据存储在BANK中,准备写入
    icMuBankSw(0x05,SPIA_BASE);

    //写入EEPROM数据
    for(i=0 ;i< 32; i++)
    {
        //EEPROM_Data_Wr[i] = i;
        addr = (i<< 1);
        icMuDataWrite(addr,EncCodeV.ENCDataBuf[i]& 0xff,SPIA_BASE);
        icMuDataWrite((addr+1),EncCodeV.ENCDataBuf[i] >> 8,SPIA_BASE);
    }

    //切换至BANK6,编码数据存储在BANK中,准备写入
    icMuBankSw(0x06,SPIA_BASE);

    //写入EEPROM数据
    for(i=32 ;i< EncEepromDataNum; i++)
    {
        //EEPROM_Data_Wr[i] = i;
        addr = ((i-32)<< 1);
        icMuDataWrite(addr,EncCodeV.ENCDataBuf[i]& 0xff,SPIA_BASE);
        icMuDataWrite((addr+1),EncCodeV.ENCDataBuf[i] >> 8,SPIA_BASE);
    }
    EncCodeV.DataWriteToEeprom = 0x0000;        //EEPROM写入完成标志

}

/**********************************************************************************************/
/* Function_Name: icMuPosAWrite_Cmd_ST         */
/* Description  : 电机端 单圈位置获取指令 0xA6
               输入：
               输出：   */
/**********************************************************************************************/
void icMuPosWrite_Cmd_ST( uint32_t base )
{
    SPI_writeDataNonBlocking(base, 0xA600);
    SPI_writeDataNonBlocking(base, 0x0000);
    SPI_writeDataNonBlocking(base, 0x0000);
    SPI_writeDataNonBlocking(base, 0x0000);
}

/**********************************************************************************************/
/* Function_Name: icMuPosAWrite_Cmd_MT         */
/* Description  : 电机端 单圈+多圈位置获取指令 0xA6
               输入：
               输出：   */
/**********************************************************************************************/
void icMuPosWrite_Cmd_MT( uint32_t base )
{
    SPI_writeDataNonBlocking(base, 0xA600);
    SPI_writeDataNonBlocking(base, 0x0000);
    SPI_writeDataNonBlocking(base, 0x0000);
    SPI_writeDataNonBlocking(base, 0x0000);
    SPI_writeDataNonBlocking(base, 0x0000);
    SPI_writeDataNonBlocking(base, 0x0000);
}

/**********************************************************************************************/
/* Function_Name: icMuDataReciveA         */
/* Description  : 电机端 单圈+多圈位置获取，SCANA周期循环获取，并发送0xA6指令
               输入：
               输出：   */
/**********************************************************************************************/
void icMuDataReciveA( void )
{
   USHORT i,Len;

   USHORT rData[10] = {0,0,0,0,0,0,0,0,0,0};
   /* 角度寄存器读取 */
   Len = SPI_getRxFIFOStatus(SPIA_BASE);
   if( Len != 0)
   {
       /* 0xA6数据接收 */
       for( i = 0; i < Len; i ++)
       {
           rData[ i ] = SPI_readDataNonBlocking(SPIA_BASE);
           if(i >= 1 )
           {
               icMuPosA[ i-1 ] = rData[ i ];
           }
       }

       /* 根据是否配置多圈芯片，进行位置数据解析 */
       if(MOTOR_PVL_EN)
       {
           if( Prm.bit_dp.b.l == 20)
           {
                icMu_Pos_A = (((ULONG)icMuPosA[2] << 16)  + ((ULONG)icMuPosA[3] << 8) + \
                                icMuPosA[4]) >> 4;
           }
           else if( Prm.bit_dp.b.l == 17)
            {
               icMu_Pos_A = (((ULONG)icMuPosA[2] << 16)  + ((ULONG)icMuPosA[3] << 8) + \
                                        icMuPosA[4]) >> 7;
            }
            if(MOTOR_MULTI_EN)
                MultiPos_A = (((ULONG)icMuPosA[0] << 8)  + ((ULONG)icMuPosA[1] ));
            else
                MultiPos_A = 0;
       }
       else
       {
           if( Prm.bit_dp.b.l == 20)
           {
                icMu_Pos_A = (((ULONG)icMuPosA[0] << 16)  + ((ULONG)icMuPosA[1] << 8) + \
                                icMuPosA[2]) >> 4;
           }

           else if( Prm.bit_dp.b.l == 17)
           {
               icMu_Pos_A = (((ULONG)icMuPosA[0] << 16)  + ((ULONG)icMuPosA[1] << 8) + \
                                                   icMuPosA[2]) >> 7;
           }
       }

   }
   else /* 未检测到有效长度，认为当前接收超时  */
   {
       icMu_Status_A |= 0x0100;     /*** 接收超时 ***/
   }
}

/**********************************************************************************************/
/* Function_Name: icMuPosAGet         */
/* Description  : 电机端 单圈+多圈位置获取，SCANA周期循环获取，并发送0xA6指令
               输入：
               输出：   */
/**********************************************************************************************/
USHORT icMuPosAGet( void )
{
    icMu_Status_A = 0;

    /* 上位机校准开启时，不进行采集 */
    if(Iprm.iCHausAdj)
    {
        if( ( Prm.b_prm0_0 & 0x000F ) == 0x0007)
        {
            icMu_Pos_A = 0;
            icMu_Status_A = 0;
            return 0;
        }
    }

    if(SPI_isBusy(SPIA_BASE))
    {

        icMu_Status_A |= 0x0100;    /*** 接收超时 ***/
        return 0;
    }
    // 获取位置指令(先接收，再发送，利用SCANA的循环周期，避免SPI发送后阻塞等待)
    icMuDataReciveA();

    // 发送位置指令，多圈芯片与单圈芯片发送字节数存在差异（0xA6 ）
    if(MOTOR_PVL_EN)    
        icMuPosWrite_Cmd_MT(SPIA_BASE);
    else    
        icMuPosWrite_Cmd_ST(SPIA_BASE);

    //HWREG( GPIODATA_BASE + GPIO_O_GPETOGGLE )   = 1UL << 17;
    return 1;
}


//########################################################################################
// Function Name:   IntegralComp
// Version:         V1.0
// Input:           none
// Output:          none
// Description:     积分补偿处理

// History:
//########################################################################################
uint32_t IntegralComp( int32_t a)
{
    uint32_t   i;
    uint16_t   j;
    int32_t    z;
    int32_t    delax;
    int32_t    tmp ;
    int32_t   position;
    int32_t   integral,integral_next;



    i = a & 0x07FFFF  ;       // 对位置高
    //j = i >> 15;              // 查表index ,分为16段
    j = i >> 12;              // 查表index ,分为128段


    integral = stEepromintegral.Page1integral[j];
    integral_next = stEepromintegral.Page1integral[j+1];

    //delax = a & 0x007FFF;     // 提取低15位
    delax = a & 0x000FFF;     // 提取低16位

    //根据当前位置所在的区间范围进行线性补偿
    //z = (stEepromintegral.STDIFF.Page1integral[j].w)+((((stEepromintegral.STDIFF.Page1integral[j+1].w ) - (stEepromintegral.STDIFF.Page1integral[j].w))* (delax))>> 15);
    z = integral + (((integral_next - integral ) * (delax))>> 12);

    tmp = (int32_t)(a) + z;

    position  = (uint32_t)tmp & 0x7ffff;

    return( position );

}


//########################################################################################
// Function Name:   IntegralComp
// Version:         V1.0
// Input:           none
// Output:          none
// Description:     积分补偿处理

// History:
//########################################################################################
uint32_t IntegralComp_64( int32_t a)
{
    uint32_t   i;
    uint16_t   j;
    int32_t    z;
    int32_t    delax;
    int32_t    tmp ;
    int32_t   position;
    int32_t   integral,integral_next;

    i = a & 0x07FFFF  ;       // 对位置高
    //j = i >> 15;              // 查表index ,分为16段
    j = i >> 13;              // 查表index ,分为64段

    integral = (LONG)stEepromintegral.Page1integral[j];
    integral_next = (LONG)stEepromintegral.Page1integral[j+1];

    //delax = a & 0x007FFF;     // 提取低15位
    delax = a & 0x001FFF;     // 提取低14位

    //根据当前位置所在的区间范围进行线性补偿
    //z = (stEepromintegral.STDIFF.Page1integral[j].w)+((((stEepromintegral.STDIFF.Page1integral[j+1].w ) - (stEepromintegral.STDIFF.Page1integral[j].w))* (delax))>> 15);
    z = integral + (((integral_next - integral ) * (delax))>> 13);

    tmp = (int32_t)(a) + z;

    position  = (uint32_t)tmp & 0x7ffff;

    return( position );

}

//########################################################################################
// Function Name:   IntegralComp
// Version:         V1.0
// Input:           none
// Output:          none
// Description:     积分补偿处理

// History:
//########################################################################################
uint32_t IntegralComp12( uint32_t a)
{
    uint32_t   i;
    uint16_t   j;
    int32_t    z;
    int32_t    delax;
    int32_t    tmp ;
    int32_t   position;
    int32_t   integral,integral_next;



    i = a & 0x00FFFF  ;       // 对位置高
    j = (uint32_t)(i / 5461.3f);              // 查表index ,分为12段


    integral = (SHORT)MotEncCompData.MotorEncComp[j];
    integral_next = (SHORT)MotEncCompData.MotorEncComp[j+1];

    delax = a & 0x000FFF;     // 提取低14位

    //根据当前位置所在的区间范围进行线性补偿
    z = integral + (((integral_next - integral ) * (delax))>> 12);

    tmp = (int32_t)(a) + z;

    position  = (uint32_t)tmp & 0xffff;

    return( position );

}

/**********************************************************************************************/
/* Function_Name: icMuPosBGet         */
/* Description  : 负载端 单圈+多圈位置获取，SCANA周期循环获取，并发送0xA6指令
               输入：
               输出：   */
/**********************************************************************************************/
void icMuPosBGet( void )
{
USHORT i,Len;
USHORT rData[10] = {0,0,0,0,0,0,0,0,0,0};

    icMu_Status_B = 0;

    /* 上位机校准开启时，不进行采集 */
    if(Iprm.iCHausAdj)
    {
         if( ( Prm.b_prm0_0 & 0x000F ) == 0x0007)
        {
            icMu_Pos_B = 0;
            icMu_Status_B = 0;
            return;
        }
    }

     if(SPI_isBusy(SPIB_BASE))
     {
         icMu_Status_B |= 0x0100;
         return;
     }

     // 获取位置指令(先接收，再发送，利用SCANA的循环周期，避免SPI发送后阻塞等待)
    Len = SPI_getRxFIFOStatus(SPIB_BASE);
    if( Len != 0)
    {
        for( i = 0; i < Len; i ++)
        {
            rData[ i ] = SPI_readDataNonBlocking(SPIB_BASE);
            if(i >= 1 )
           {
               icMuPosB[ i-1 ] = rData[ i ];
           }
        }
        if(LOAD_PVL_EN)
        {
            icMu_Pos_B_Ori = (((ULONG)icMuPosB[2] << 16)  + ((ULONG)icMuPosB[3] << 8) + \
                            icMuPosB[4]) >> 5;

            if( POS_COMPENS_ENABLE )
                icMu_Pos_B = IntegralComp(icMu_Pos_B_Ori);
            else if( POS_COMPENS_64_ENABLE )
                icMu_Pos_B = IntegralComp_64(icMu_Pos_B_Ori);
            else
                icMu_Pos_B = icMu_Pos_B_Ori;


            icMu_Pos_B_Err = (LONG)icMu_Pos_B_Ori - (LONG)icMu_Pos_B;

            if (icMu_Pos_B_Err > 262143 )
            {
                icMu_Pos_B_Err = icMu_Pos_B_Err - 524288;

            }
            else if(icMu_Pos_B_Err < -262143 )
            {
                icMu_Pos_B_Err = icMu_Pos_B_Err + 524288;
            }

//            AinK.Monitor3 = icMu_Pos_B_Err;
//            AinK.Monitor4 = icMu_Pos_B_Ori;
//            AinK.Monitor5 = icMu_Pos_B;

            if(LOAD_MULTI_EN)
                MultiPos_B = (((ULONG)icMuPosB[0] << 8)  + ((ULONG)icMuPosB[1] ));
            else
                MultiPos_B = 0;
        }
        else
        {
            icMu_Pos_B = (((ULONG)icMuPosB[0] << 16)  + ((ULONG)icMuPosB[1] << 8) + \
                            icMuPosB[2]) >> 5;
        }
    }
    else
    {
        icMu_Status_B |= 0x0100;    /*** 接收超时 ***/
    }

    // 发送位置指令，多圈芯片与单圈芯片发送字节数存在差异（0xA6 ）
    if(LOAD_PVL_EN) 
        icMuPosWrite_Cmd_MT( SPIB_BASE );
    else    
        icMuPosWrite_Cmd_ST( SPIB_BASE );
    
}

USHORT PrePulCnt = 0;
/**********************************************************************************************/
/* Function_Name: icHausPrePulOutPut         */
/* Description  : icHaus Pre复位操作
               输入：
               输出：   */
/**********************************************************************************************/
void icHausPrePulOutPut(void)
{
    /* 复位操作开启后，强制将Pre位置1，持续 200ms后 清零*/
    if(Prm.b_prm0_0C == 1)
    {
        HWREG( GPIODATA_BASE + GPIO_O_GPASET )   = 1UL << 19;
        PrePulCnt++;
    }
    if((PrePulCnt >= 100) && (Prm.b_prm0_0C == 1))
    {
        HWREG( GPIODATA_BASE + GPIO_O_GPACLEAR )   = 1UL << 19;
        PrePulCnt = 0;
        Prm.b_prm0_0C = 0;

    }
}

/**********************************************************************************************/
/* Function_Name: icHaus_Comm_Erro         */
/* Description  : icHaus通讯异常判定
               输入：
               输出：   */
/**********************************************************************************************/
void icHaus_Comm_Erro(void)
{
    if(icMu_SPI_Fault)
    {
        KPI_ALARMSET( ALM_PG2 );
        icMu_SPI_Fault = 0;
    }
    if(Prm.Pn597 == 1)
    {
        if(icMu_PowerUp_Fault || icMu150_PowerUp_Fault)
        {
            KPI_ALARMSET( ALM_PG5 );
        }
    }
}
