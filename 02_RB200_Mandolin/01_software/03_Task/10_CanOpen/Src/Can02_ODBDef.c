/****************************************************************************************************/
/*																									*/
/*                           Copyright (C) ××× Electric Corporation                                 */
/*                                  版权所有 · All right Reserved                                   */
/*											2017 ~													*/
/****************************************************************************************************/
/*																									*/
/*																									*/
/*		Can02_ODBDef.c : CANOpen 对象字典相关定义  											    	*/
/*																									*/
/*																									*/
/****************************************************************************************************/
#include "Main.h"

ODATTRSTRUCT OD_AttrVar;                                /* 对象字典属性定义                         */
union ODUnion ODDatArr[DS402_ODNum];                    /* 对象字典对应值                           */
void ODB_Init( void );
void ODB_Cia402_Init( void );

/****************************************************************************************************/
/*函数名：MaxCheck                                                                                  */
/*函数功能  :计算对象字典最小值                                                                     */
/*      对象字典的bit9 -- bit15为对象字典的范围  根据对象字典范围计算最大值                         */
/****************************************************************************************************/
ULONG MaxCheck(USHORT ODRang)
{
    ULONG RtnData = 0;
    switch(ODRang)
    {
        case RANG0:           //0 -- 2^8
            RtnData = 0x000000FF;
            break;
        case RANG1:           //-2^7 -- 2^7
            RtnData = 0x0000007F;
            break;
        case RANG2:           //0 -- 2^16
            RtnData = 0x0000FFFF;
            break;
        case RANG3:           //-2^15 -- 2^15
            RtnData = 0x00007FFF;
            break;
        case RANG4:           //0 -- 2^32
            RtnData = 0xFFFFFFFF;
            break;
        case RANG5:           //-2^31 -- 2^31
            RtnData = 0x7FFFFFFF;
            break;
        case RANG6:           //1 -- 1
            RtnData = 1;
            break;
        case RANG7:           //2 -- 2
            RtnData = 2;
            break;
        case RANG8:           //5 -- 5
            RtnData = 5;
            break;
        case RANG9:           //0 -- 4
            RtnData = 4;
            break;
        case RAN10:           //0 -- 3000
            RtnData = 3000;
            break;
        case RAN11:           //0 -- 2000
            RtnData = 2000;
            break;
        case RAN12:           //-3000 -- 3000
            RtnData = 3000;
            break;
        case RAN13:           //0 -- 35
            RtnData = 35;
            break;
        case RAN14:           //0 -- 500
            RtnData = 500;
            break;
        case RAN15:           //-128 -- 63
            RtnData = 63;
            break;
        case RAN16:           //-5000 -- 5000
            RtnData = 5000;
            break;
        case RAN17:             //0  -- 3000
            RtnData = 3000;
            break;
        case RAN18:             //17 -- 17
            RtnData = 17;
            break;
        default:
            RtnData = 0;
            break;
        }
        return RtnData;
}

/****************************************************************************************************/
/*函数名：MinCheck                                                                                  */
/*函数功能  :计算对象字典最小值                                                                     */
/*      对象字典的bit9 -- bit15为对象字典的范围  根据对象字典范围计算最大值                         */
/****************************************************************************************************/
LONG MinCheck(USHORT ODRang)
{
    LONG RtnData = 0;
    switch(ODRang)
    {
    case RANG0:           //0 -- 2^8
        RtnData = 0;
        break;
    case RANG1:           //-2^7-1 -- 2^7
        RtnData = -128;
        break;
    case RANG2:           //0 -- 2^16
        RtnData = 0;
        break;
    case RANG3:           //-2^15-1 -- 2^15
        RtnData = -32768;
        break;
    case RANG4:           //0 -- 2^32
        RtnData = 0;
        break;
    case RANG5:           //-2^31-1 -- 2^31
        RtnData = -2147483648;
        break;
    case RANG6:           //1 -- 1
        RtnData = 1;
        break;
    case RANG7:           //2 -- 2
        RtnData = 2;
        break;
    case RANG8:           //5 -- 5
        RtnData = 5;
        break;
    case RANG9:           //0 -- 4
        RtnData = 0;
        break;
    case RAN10:           //0 -- 3000
        RtnData = 0;
        break;
    case RAN11:           //0 -- 2000
        RtnData = 0;
        break;
    case RAN12:           //-3000 -- 3000
        RtnData = -3000;
        break;
    case RAN13:              //0 -- 35
        RtnData = 0;
        break;
    case RAN14:              //0 -- 500
        RtnData = 0;
        break;
    case RAN15:              //-128 -- 63
        RtnData = -128;
        break;
    case RAN16:             //-5000 -- 5000
        RtnData = -5000;
        break;
    case RAN17:             //0  -- 3000
        RtnData = 0;
    case RAN18:             //17 -- 17
        RtnData = 17;
        break;
    default:
        RtnData = 0;
        break;
    }
    return RtnData;
}

/****************************************************************************************************/
/*  DS301 & DS402 对象字典初始默认值                                                                */
/****************************************************************************************************/
void DB_InitialValue(void)
{
USHORT i;
    for(i = 0;i < DS402_ODNum;i++)
    {
        if( i == OD_6063 || i == OD_6064 )
        {
            ;
        }
        else
        {
            ODDatArr[i].all = ((ULONG)ObjectDictionaryAttriub[i][1] << 16) + ObjectDictionaryAttriub[i][2];
        }
    }
    if(CIA402_ETH_PRM_TEST)
    {
        ODB_Cia402_Init( );
    }


    if(CAN_EXFUNC0_0_EN)                         /* 使用功能码映射PDO  20240819  */
    {
        ODB_Init( );
    }
    for(i = 0;i < DS402_ODNum;i++ )
    {
        ODB_Update(i);                                              /* 更新相应映射对象             */
        CanVar.PosCalFlg= 0;        
    }
    
   /*-----------------------------------------------------------------------------------------------*/
    ODDatArr[Drive_Mode_Support].all      = 0x0000006D;               /* 对象字典【0x6502】         */
    ODDatArr[Motor_Rated_Current_MA].all  = Prm.irat * 100;           /* 对象字典【0x6075】         */
    ODDatArr[Motor_Rated_Torque_MNM].all  = Prm.rattrq * 10;          /* 对象字典【0x6076】         */
    ODDatArr[Max_Motor_Speed_RPM].all     = (Prm.vrat_max.b.h) * 100; /* 对象字典【0x6080】         */
    
    
    /*----------------------------------------------------------------------------------------------*/
    /* CanOpen轮廓速度模式兼容早期产品，加减速的默认值需要进行相应的调整    @2021.03.20             */
    /*----------------------------------------------------------------------------------------------*/
#if 1
    if( ( Prm.Mode & 0xF000 ) == 0x1000 )
    {
        ODDatArr[ Profile_Acceleration ].all = 200;
        ODDatArr[ Profile_Deceleration ].all = 200;
    }
#endif
    
}
/****************************************************************************************************/
/*  DS301 & DS402 对象字典初始默认值                                                                */
/****************************************************************************************************/
void DB1000_InitialValue( void )
{
USHORT i;
    for(i = 0;i < DS301_ODNum;i++)
    {
        ODDatArr[i].all = ((ULONG)ObjectDictionaryAttriub[i][1] << 16) + ObjectDictionaryAttriub[i][2];
    }
    if(CAN_EXFUNC0_0_EN)                         /* 使用功能码映射PDO  20240819  */
    {
        ODB_Init( );
    }
    for(i = 0;i < DS301_ODNum;i++ )
    {
        ODB_Update(i);                                              /* 更新相应映射对象             */
    }
}


/****************************************************************************************************/
/*  DS301 & DS402 属性表                                                                            */
/****************************************************************************************************/
const USHORT ObjectDictionaryAttriub[][3] = {
/*--------------------------------------------------------------------------------------------------*/
/*  Word1:对象字典类型|数据字节数|数据范围|访问类型|映射属性|数据类型                               */
/*  Word2:Default Data HightWord                                                                    */
/*  Word3:Default Data LowWord                                                                      */
/*--------------------------------------------------------------------------------------------------*/
//1000对象字典 0x20192
{ODVAL|BYTE4|RANG4|RO|MAPN|U32,0x0402,0x0192},  //00     1000_00_20  DeviceType_OD
{ODVAL|BYTE1|RANG0|RO|MAPY|U08,0x0000,0x0000},  //       1001_00_08  ErrorRegister_OD
{ODARR|BYTE1|RANG9|RW|MAPN|U08,0x0000,0x0000},  //       1003_00_08  Predefine ErrorCode
{ODVAL|BYTE4|RANG4|RO|MAPN|U32,0x0000,0x0000},  //       1003_01_20  Predefine ErrorCode1
{ODVAL|BYTE4|RANG4|RO|MAPN|U32,0x0000,0x0000},  //       1003_02_20  Predefine ErrorCode2
{ODVAL|BYTE4|RANG4|RO|MAPN|U32,0x0000,0x0000},  //05     1003_03_20  Predefine ErrorCode3
{ODVAL|BYTE4|RANG4|RO|MAPN|U32,0x0000,0x0000},  //       1003_04_20  Predefine ErrorCode4
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0080},  //       1005_00_20  SYNC COB ID
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1006_00_20  SYNC Period
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //       100C_00_10  Guard Time
{ODVAL|BYTE1|RANG0|RW|MAPN|U08,0x0000,0x0000},  //10     100D_00_08  Life Time
{ODARR|BYTE1|RANG6|RO|MAPN|U08,0x0000,0x0001},  //       1010_00_08  Store parameter number
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0001},  //       1010_01_20  Save All
{ODARR|BYTE1|RANG6|RO|MAPN|U08,0x0000,0x0001},  //       1011_00_08  Restore Default
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0001},  //       1011_01_20  Restore Default All
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x8000,0x0081},  //15     1014_00_20  EMCY COB ID
{ODARR|BYTE1|RANG6|RO|MAPN|U08,0x0000,0x0001},  //       1016_00_08  consumer HeartBeat entry
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1016_01_20  consumer HeartBeat time
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //       1017_00_10  Producer HeartBeat time
{ODARR|BYTE1|RANG8|RO|MAPN|U08,0x0000,0x0003},  //       1018_00_08  Identity Object entry
{ODVAL|BYTE4|RANG4|RO|MAPN|U32,0xF000,0x02B5},  //20     1018_01_20  Producer Vender ID
{ODVAL|BYTE4|RANG4|RO|MAPN|U32,0x0000,0x0006},  //       1018_02_20  Product code
{ODVAL|BYTE4|RANG4|RO|MAPN|U32,0x0000,0x0002},  //       1018_03_20  Revision Number
{ODVAL|BYTE4|RANG4|RO|MAPN|U32,0x0000,0x0002},  //       1019_00_20  Sn Number
{ODARR|BYTE1|RANG6|RO|MAPN|U08,0x0000,0x0001},  //       1029_00_08  Error behaver entry
{ODVAL|BYTE1|RANG0|RO|MAPN|U08,0x0000,0x0000},  //       1029_01_08  Communication Error
{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0002},  //25     1200_00_08  SDO Parameter entry
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0600},  //       1200_01_20  SDO recerive COB ID
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0580},  //27     1200_02_20  SDO Transfer COB ID
//----------------------------------28个对象字典----------------------------------------------------

//PDO接收对象字典配置--------------------------------------------------------------------------------
{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0002},  //28     1400_00_08  PDO1 Receive entry
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x8000,0x0201},  //       1400_01_20  PDO1 Receive COB ID
{ODVAL|BYTE1|RANG0|RW|MAPN|U08,0x0000,0x00FF},  //30     1400_02_08  PDO1 Receive Type
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0002},  //       1401_00_08  PDO2 Receive entry
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x8000,0x0301},  //       1401_01_20  PDO2 Receive COB ID
{ODVAL|BYTE1|RANG0|RW|MAPN|U08,0x0000,0x00FF},  //       1401_02_08  PDO2 Receive Type
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0002},  //       1402_00_08  PDO3 Receive entry
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x8000,0x0401},  //35     1402_01_20  PDO3 Receive COB ID
{ODVAL|BYTE1|RANG0|RW|MAPN|U08,0x0000,0x00FF},  //       1402_02_08  PDO3 Receive Type
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0002},  //       1403_00_08  PDO4 Receive entry
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x8000,0x0501},  //       1403_01_20  PDO4 Receive COB ID
{ODVAL|BYTE1|RANG0|RW|MAPN|U08,0x0000,0x00FF},  //       1403_02_08  PDO4 Receive Type
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG9|RW|MAPN|U08,0x0000,0x0001},  //40     1600_00_08  PDO1 Receive mapping num
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x6040,0x0010},  //       1600_01_20  PDO1 Receive mapping1
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1600_02_20  PDO1 Receive mapping2
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1600_03_20  PDO1 Receive mapping3
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1600_04_20  PDO1 Receive mapping4
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG9|RW|MAPN|U08,0x0000,0x0002},  //45     1601_00_08  PDO2 Receive mapping num
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x6040,0x0010},  //       1601_01_20  PDO2 Receive mapping1
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x6060,0x0008},  //       1601_02_20  PDO2 Receive mapping2
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1601_03_20  PDO2 Receive mapping3
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1601_04_20  PDO2 Receive mapping4
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG9|RW|MAPN|U08,0x0000,0x0002},  //50     1602_00_08  PDO3 Receive mapping num
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x6040,0x0010},  //       1602_01_20  PDO3 Receive mapping1
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x607A,0x0020},  //       1602_02_20  PDO3 Receive mapping2
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1602_03_20  PDO3 Receive mapping3
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1602_04_20  PDO3 Receive mapping4
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG9|RW|MAPN|U08,0x0000,0x0002},  //55     1603_00_08  PDO4 Receive mapping num
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x6040,0x0010},  //       1603_01_20  PDO4 Receive mapping1
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x60FF,0x0020},  //       1603_02_20  PDO4 Receive mapping2
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1603_03_20  PDO4 Receive mapping3
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //59     1603_04_20  PDO4 Receive mapping4
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG8|RO|MAPN|U08,0x0000,0x0005},  //60     1800_00_08  PDO1 Transfer entry
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x8000,0x0181},  //       1800_01_20  PDO1 Transfer COB ID
{ODVAL|BYTE1|RANG0|RW|MAPN|U08,0x0000,0x00FF},  //       1800_02_08  PDO1 Transfer Type
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //       1800_03_10  PDO1 Inhibit time
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //       1800_04_10  Rsv
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //65     1800_05_10  PDO1 Event timer
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG8|RO|MAPN|U08,0x0000,0x0005},  //       1801_00_08  PDO2 Transfer entry
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x8000,0x0281},  //       1801_01_20  PDO2 Transfer COB ID
{ODVAL|BYTE1|RANG0|RW|MAPN|U08,0x0000,0x00FF},  //       1801_02_08  PDO2 Transfer Type
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //       1801_03_10  PDO2 Inhibit time
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //70     1801_04_10  Rsv
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //       1801_05_10  PDO2 Event timer
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG8|RO|MAPN|U08,0x0000,0x0005},  //       1802_00_08  PDO3 Transfer entry
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x8000,0x0381},  //       1802_01_20  PDO3 Transfer COB ID
{ODVAL|BYTE1|RANG0|RW|MAPN|U08,0x0000,0x00FF},  //       1802_02_08  PDO3 Transfer Type
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //75     1802_03_10  PDO3 Inhibit time
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //       1802_04_10  Rsv
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //       1802_05_10  PDO3 Event timer
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG8|RO|MAPN|U08,0x0000,0x0005},  //       1803_00_08  PDO4 Transfer entry
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x8000,0x0481},  //       1803_01_20  PDO4 Transfer COB ID
{ODVAL|BYTE1|RANG0|RW|MAPN|U08,0x0000,0x00FF},  //80     1803_02_08  PDO4 Transfer Type
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //       1803_03_10  PDO4 Inhibit time
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //       1803_04_10  Rsv
{ODVAL|BYTE2|RANG2|RW|MAPN|U16,0x0000,0x0000},  //       1803_05_10  PDO4 Event timer
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG9|RW|MAPN|U08,0x0000,0x0001},  //       1A00_00_08 PDO1 Transfer mapping num
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x6041,0x0010},  //85     1A00_01_20 PDO1 Transfer mapping1
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1A00_02_20 PDO1 Transfer mapping2
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1A00_03_20 PDO1 Transfer mapping3
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1A00_04_20 PDO1 Transfer mapping4
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG9|RW|MAPN|U08,0x0000,0x0002},  //       1A01_00_08 PDO2 Transfer mapping num
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x6041,0x0010},  //90     1A01_01_20 PDO2 Transfer mapping1
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x6061,0x0008},  //       1A01_02_20 PDO2 Transfer mapping2
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1A01_03_20 PDO2 Transfer mapping3
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1A01_04_20 PDO2 Transfer mapping4
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG9|RW|MAPN|U08,0x0000,0x0002},  //       1A02_00_08 PDO3 Transfer mapping num
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x6041,0x0010},  //95     1A02_01_20 PDO3 Transfer mapping1
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x6064,0x0020},  //       1A02_02_20 PDO3 Transfer mapping2
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1A02_03_20 PDO3 Transfer mapping3
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1A02_04_20 PDO3 Transfer mapping4
/*--------------------------------------------------------------------------------------------------*/
{ODARR|BYTE1|RANG9|RW|MAPN|U08,0x0000,0x0002},  //       1A03_00_08 PDO4 Transfer mapping num
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x6041,0x0010},  //100    1A03_01_20 PDO4 Transfer mapping1
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x606C,0x0020},  //       1A03_02_20 PDO4 Transfer mapping2
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //       1A03_03_20 PDO4 Transfer mapping3
{ODVAL|BYTE4|RANG4|RW|MAPN|U32,0x0000,0x0000},  //103    1A03_04_20 PDO4 Transfer mapping4
//-------------------------------36个对象字典--------------------------------------------------------

//6000对象字典---------------------------------------------------------------------------------------
{ODVAL|BYTE2|RANG2|RO|MAPY|U16,0x0000,0x0000},  //104    603F_00_10 Error Code
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0000},  //105    6040_00_10 Control Word
{ODVAL|BYTE2|RANG2|RO|MAPY|U16,0x0000,0x0000},  //       6041_00_10 Status Word
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0002},  //       605A_00_10 Quick stop option code
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0000},  //       605B_00_10 Shut Down Option
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0001},  //       605D_00_10 Halt option code
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0000},  //110    605E_00_10 Fault Action

{ODVAL|BYTE1|RANG0|RW|MAPY|U08,0x0000,0x0001},  //       6060_00_08 Operation Mode
{ODVAL|BYTE1|RANG0|RO|MAPY|U08,0x0000,0x0000},  //112    6061_00_08 Operation Mode Display
{ODVAL|BYTE4|RANG5|RO|MAPY|S32,0x0000,0x0000},  //       6062_00_20 Position Demand Value(mm)
{ODVAL|BYTE4|RANG5|RO|MAPY|S32,0x0000,0x0000},  //       6063_00_20 Position Actual Value(pulse)
{ODVAL|BYTE4|RANG5|RO|MAPY|S32,0x0000,0x0000},  //       6064_00_20 Position Actual Value(ms)
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0000,0x2710},  //       6065_00_20 Following Error Window(mm)
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0000,0x0064},  //117    6067_00_20 Position Window(mm) 
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0000},  //       6068_00_10 Position Window Time(ms)
{ODVAL|BYTE4|RANG5|RO|MAPY|S32,0x0000,0x0000},  //       606B_00_10 Velocity Demand Value(puu/s)
{ODVAL|BYTE4|RANG5|RO|MAPY|S32,0x0000,0x0000},  //       606C_00_10 Velocity Actual Value(puu/s)
{ODVAL|BYTE2|RAN10|RW|MAPY|U16,0x0000,0x0064},  //       606D_00_10 Velocity Window(0.1rpm)
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0000},  //122    606E_00_10 Velocity Window Time(ms)
{ODVAL|BYTE2|RAN11|RW|MAPY|U16,0x0000,0x0064},  //       606F_00_10 Zero Velocity Threshold(0.1ms)

{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0000},  //       6070_00_10 Zero Velocity Time(ms)
{ODVAL|BYTE2|RAN12|RW|MAPY|S16,0x0000,0x0000},  //       6071_00_10 Target Torque(0.1%)
{ODVAL|BYTE2|RAN17|RW|MAPY|S16,0x0000,0x0BB8},  //       6072_00_10 Max Torque(0.1%)
{ODVAL|BYTE2|RANG3|RO|MAPY|S16,0x0000,0x0000},  //127    6074_00_10 Torque Demand Value(0.1%)
{ODVAL|BYTE4|RANG4|RO|MAPY|U32,0x0000,0x0000},  //       6075_00_20 Motor Rated Current(mA)
{ODVAL|BYTE4|RANG4|RO|MAPY|U32,0x0000,0x0000},  //       6076_00_20 Motor Rated Torque(mNm)
{ODVAL|BYTE2|RANG3|RO|MAPY|S16,0x0000,0x0000},  //       6077_00_10 Torque Actual Value(0.1%)
{ODVAL|BYTE2|RANG4|RO|MAPY|S16,0x0000,0x0000},  //       6078_00_10 Current Actual Value(mA)
{ODVAL|BYTE2|RANG2|RO|MAPY|U16,0x0000,0x0000},  //       6079_00_10 DcVolt_Actual_Value
{ODVAL|BYTE4|RANG5|RW|MAPY|S32,0x0000,0x0000},  //       607A_00_20 Target Position(pulse)
{ODVAL|BYTE4|RANG5|RW|MAPY|S32,0x0000,0x0000},  //133    607C_00_20 Homing Offset(pulse)
{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0002},  //       607D_00_20 Software Position Limit Entry
{ODVAL|BYTE4|RANG5|RW|MAPY|S32,0x8000,0x0000},  //       607D_01_20 Min Softwart Position Limit(pulse)
{ODVAL|BYTE4|RANG5|RW|MAPY|S32,0x7FFF,0xFFFF},  //136    607D_02_20 Max Softwart Position Limit(pulse)
{ODVAL|BYTE1|RANG1|RW|MAPY|S08,0x0000,0x0000},  //       607E_00_08 Polarity
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x3200,0x0000},  //138    607F_00_20 Max Profile Velocity(pps)

{ODVAL|BYTE4|RANG4|RO|MAPY|U32,0x0000,0x1388},  //       6080_00_20 Max Motor Speed(rpm)
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0000,0x0000},  //       6081_00_20 Profile Velocity(pps)
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0500,0x0000},  //       6083_00_10 Profile Acceleration(puu/s2)
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0500,0x0000},  //       6084_00_10 Profile Deceleration(puu/s2)
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x7FFF,0xFFFF},  //143    6085_00_20 Quick Stop Deceleration(ms)
{ODVAL|BYTE2|RANG3|RW|MAPY|S16,0x0000,0x0000},  //       6086_00_10 Motion Profile Type
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0000,0x03E8},  //       6087_00_10 Torque Slope(ms)
{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0002},  //       6091_00_08 Position Factor Entry
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0000,0x0001},  // 147   6091_01_10 Position Factor Numerator
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0000,0x0001},  //       6091_02_10 Position Factor Divisor

{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0002},  //       6093_00_08 Position Factor Entry
{ODVAL|BYTE4|RANG4|RW|MAPY|U16,0x0000,0x0001},  //       6093_01_10 Position Factor Numerator
{ODVAL|BYTE4|RANG4|RW|MAPY|U16,0x0000,0x0001},  // 151   6093_02_10 Position Factor Divisor
{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0002},  //       6094_00_08 Velocity Encoder Factor Entry
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0000,0x0001},  //       6094_01_20 Velocity Encoder Factor Numerator
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0000,0x0001},  //       6094_02_20 Velocity Encoder Factor Divisor
{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0002},  //       6095_00_08 Velocity Encoder Factor1 Entry
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0000,0x0001},  // 156   6095_01_20 Velocity Encoder Factor1 Numerator
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0000,0x0001},  //       6095_02_20 Velocity Encoder Factor1 Divisor
{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0002},  //       6097_00_08 Acceleration Factor Entry
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0000,0x0001},  //       6097_01_20 Acceleration Factor Numerator
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0000,0x0001},  //       6097_02_20 Acceleration Factor Divisor

{ODVAL|BYTE1|RAN13|RW|MAPY|U08,0x0000,0x0001},  //161    6098_00_08 Homing Method
{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0002},  //       6099_00_08 Homing Speed Entry
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x01AA,0xAAAA},  //       6099_01_10 Search Switch Speed(pps)
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0055,0x5555},  //       6099_02_10 Search Zero Speed(pps)
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0500,0x0000},  //       609A_00_10 Homing Acceleration(puu/s2) 

{ODVAL|BYTE4|RANG5|RW|MAPY|S32,0x0000,0x0000},  //166    60B0_00_20 Position Offset
{ODVAL|BYTE4|RANG5|RW|MAPY|S32,0x0000,0x0000},  //       60B1_00_20 Speed Offset
{ODVAL|BYTE2|RANG3|RW|MAPY|S16,0x0000,0x0000},  //       60B2_00_10 Torque Offset

//--------------------------------------------------------------------------------------

{ODVAL|BYTE2|RANG3|RW|MAPY|S16,0x0000,0x0000},  // 169   60B8_00_10 TouchProbe_Fun
{ODVAL|BYTE2|RANG3|RW|MAPY|S16,0x0000,0x0000},  //       60B9_00_10 TouchProbe_Sts
{ODVAL|BYTE4|RANG5|RW|MAPY|S32,0x0000,0x0000},  //       60BA_00_20 TouchProbePos1_PVal
{ODVAL|BYTE4|RANG5|RW|MAPY|S32,0x0000,0x0000},  //       60BB_00_20 TouchProbePos1_NVal
{ODVAL|BYTE4|RANG5|RW|MAPY|S32,0x0000,0x0000},  //       60BC_00_20 TouchProbePos2_PVal
{ODVAL|BYTE4|RANG5|RW|MAPY|S32,0x0000,0x0000},  //       60BD_00_20 TouchProbePos2_NVal

//--------------------------------------------------------------------------------------

{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0000},  //175    60C0_00_10 Interpolation Select
{ODARR|BYTE1|RANG9|RO|MAPN|U08,0x0000,0x0001},  //       60C1_00_08 Interpolation Data Record Entry
{ODVAL|BYTE4|RANG5|RW|MAPY|S32,0x0000,0x0000},  //       60C1_01_10 Position Command Low Word(mm)
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0000},  //       60C1_02_10 Position Command High Word(mm)
{ODVAL|BYTE2|RANG3|RW|MAPY|S16,0x0000,0x0000},  //       60C1_03_10 Velocity(rpm)
{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0002},  //       60C2_00_08 Interpolation Period Entry
{ODVAL|BYTE1|RANG0|RW|MAPY|U08,0x0000,0x0002},  //       60C2_01_08 Interpolation Period Unit
{ODVAL|BYTE1|RAN15|RW|MAPY|S08,0x0000,0x00FD},  //182    60C2_02_08 Interpolation Period Index
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x7FFF,0xFFFF},  //       60C5_00_20 Max Acceleration(p/ms) 
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x7FFF,0xFFFF},  //       60C6_00_20 Max Deceleration(p/ms)
{ODVAL|BYTE2|RAN17|RW|MAPY|U16,0x0000,0x0BB8},  //       60E0_00_10 Positive torque limit(0.1%)
{ODVAL|BYTE2|RAN17|RW|MAPY|U16,0x0000,0x0BB8},  //       60E1_00_10 Negtive torque limit(0.1%)
{ODARR|BYTE1|RANG6|RW|MAPN|U08,0x0000,0x0000},  //187    60E6_00_08 Actual pos calculate

{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0000},  //188    60F2_00_10 Position Option Code
{ODVAL|BYTE4|RANG5|RO|MAPY|S32,0x0000,0x0000},  //       60F4_00_20 Following Error Actual Value(mm)
{ODVAL|BYTE4|RANG5|RO|MAPY|S32,0x0000,0x0000},  //       60FC_00_20 Positon Demand Value(mm)
{ODVAL|BYTE4|RANG4|RO|MAPY|U32,0x0000,0x0000},  //       60FD_00_20 Digital Input
{ODARR|BYTE1|RANG7|RO|MAPN|U08,0x0000,0x0001},  //192    60FE_00_08 Digital Output Entry
{ODVAL|BYTE4|RANG4|RO|MAPY|U32,0x0000,0x0000},  //       60FE_01_20 Physical Digital Output
{ODVAL|BYTE4|RANG4|RW|MAPY|U32,0x0000,0x0000},  //       60FE_02_20 Physical Digital Output RW
{ODVAL|BYTE4|RANG5|RW|MAPY|S32,0x0000,0x0000},  //       60FF_00_10 Target Velocity(pps) 
												  
{ODARR|BYTE1|RAN18|RO|MAPN|U08,0x0000,0x0011},  //196    6100_00_08 MIT Mode Entry
{ODVAL|BYTE2|RANG3|RW|MAPY|S16,0x0000,0x0000},  //197    6100_01_10 [Pn587] MIT Torque feedforward
{ODVAL|BYTE2|RANG3|RW|MAPY|S16,0x0000,0x0000},  //198    6100_02_10 [Pn588] MIT Given angle
{ODVAL|BYTE2|RANG3|RW|MAPY|S16,0x0000,0x0000},  //199    6100_03_10 [Pn589] MIT Given angular velocity
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0000},  //200    6100_04_10 [Pn58A] MIT Position Output Filter Time Constant
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0000},  //201    6100_05_10 [Pn58B] MIT Torque Output Filter Time Constant
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0000},  //202    6100_06_10 [Pn590] MIT Kp Set
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0000},  //203    6100_07_10 [Pn591] MIT Kd Set
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0065},  //204    6100_08_10 [Pn592] Reducer Numerator
{ODVAL|BYTE2|RANG2|RW|MAPY|U16,0x0000,0x0001},  //205    6100_09_10 [Pn593] Reducer Denominator
{ODVAL|BYTE2|RANG3|RO|MAPY|S16,0x0000,0x0000},  //206    6100_0A_10 [Un160] MIT Torque feedforward Un
{ODVAL|BYTE2|RANG3|RO|MAPY|S16,0x0000,0x0000},  //207    6100_0B_10 [Un161] MIT Given angle Un
{ODVAL|BYTE2|RANG3|RO|MAPY|S16,0x0000,0x0000},  //208    6100_0C_10 [Un162] MIT Given angular velocity Un
{ODVAL|BYTE2|RANG2|RO|MAPY|U16,0x0000,0x0000},  //209    6100_0D_10 [Un163] MIT Kp Un
{ODVAL|BYTE2|RANG2|RO|MAPY|U16,0x0000,0x0000},  //210    6100_0E_10 [Un164] MIT Kd Un
{ODVAL|BYTE2|RANG3|RO|MAPY|S16,0x0000,0x0000},  //211    6100_0F_10 [Un165] MIT Angular Feedback
{ODVAL|BYTE2|RANG3|RO|MAPY|S16,0x0000,0x0000},  //212    6100_10_10 [Un166] MIT Angular velocity feedback
{ODVAL|BYTE2|RANG3|RO|MAPY|S16,0x0000,0x0000},  //	     6100_11_10 [Un167] MIT Torque feedback

{ODVAL|BYTE2|RANG2|RO|MAPY|U16,0x0000,0x006D},  //214    6502_00_10 Drive Mode Support
};


const USHORT ADDR100X[]={OD_1000,OD_1001,OD_NULL,OD_1003,OD_NULL,OD_1005,OD_1006,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_100C,OD_100D,OD_NULL,OD_NULL};
const USHORT ADDR101X[]={OD_1010,OD_1011,OD_NULL,OD_NULL,OD_1014,OD_NULL,OD_1016,OD_1017,OD_1018,OD_1019,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR102X[]={OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_1029,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR120X[]={OD_1200,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR140X[]={OD_1400,OD_1401,OD_1402,OD_1403,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR160X[]={OD_1600,OD_1601,OD_1602,OD_1603,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR180X[]={OD_1800,OD_1801,OD_1802,OD_1803,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR1A0X[]={OD_1A00,OD_1A01,OD_1A02,OD_1A03,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR603X[]={OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_603F};
const USHORT ADDR604X[]={OD_6040,OD_6041,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR605X[]={OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_605A,OD_NULL,OD_NULL,OD_605D,OD_NULL,OD_NULL};
const USHORT ADDR606X[]={OD_6060,OD_6061,OD_6062,OD_6063,OD_6064,OD_6065,OD_NULL,OD_6067,OD_6068,OD_NULL,OD_NULL,OD_606B,OD_606C,OD_606D,OD_606E,OD_606F};
const USHORT ADDR607X[]={OD_6070,OD_6071,OD_6072,OD_NULL,OD_6074,OD_6075,OD_6076,OD_6077,OD_6078,OD_6079,OD_607A,OD_NULL,OD_607C,OD_607D,OD_607E,OD_607F};
const USHORT ADDR608X[]={OD_6080,OD_6081,OD_NULL,OD_6083,OD_6084,OD_6085,OD_6086,OD_6087,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR609X[]={OD_NULL,OD_6091,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_6098,OD_6099,OD_609A,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR60AX[]={OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR60BX[]={OD_60B0,OD_60B1,OD_60B2,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_60B8,OD_60B9,OD_60BA,OD_60BB,OD_60BC,OD_60BD,OD_NULL,OD_NULL};
const USHORT ADDR60CX[]={OD_60C0,OD_60C1,OD_60C2,OD_NULL,OD_NULL,OD_60C5,OD_60C6,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR60DX[]={OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR60EX[]={OD_60E0,OD_60E1,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_60E6,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR60FX[]={OD_NULL,OD_NULL,OD_60F2,OD_NULL,OD_60F4,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_60FC,OD_60FD,OD_60FE,OD_60FF};
const USHORT ADDR610X[]={OD_6100,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};
const USHORT ADDR650X[]={OD_NULL,OD_NULL,OD_6502,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL,OD_NULL};


//*************************************************************************************************
//
// 对象字典初始值设置
//
//*************************************************************************************************
void ODB_Init( void )
{
    // TPDO1
    ODDatArr[ PDO1_Trans_Map_Num ].all      = Prm.Tpdo1;
    ODDatArr[ PDO1_Trans_Map1 ].all         = ULONGOF( Prm.Tpdo1Map1L, Prm.Tpdo1Map1H );
    ODDatArr[ PDO1_Trans_Map2 ].all         = ULONGOF( Prm.Tpdo1Map2L, Prm.Tpdo1Map2H );
    ODDatArr[ PDO1_Trans_Map3 ].all         = ULONGOF( Prm.Tpdo1Map3L, Prm.Tpdo1Map3H );
    ODDatArr[ PDO1_Trans_Map4 ].all         = ULONGOF( Prm.Tpdo1Map4L, Prm.Tpdo1Map4H );
    
    ODDatArr[ PDO1_Trans_COB_ID ].all       = ULONGOF( Prm.Tpdo1StationL, Prm.Tpdo1StationH );
    ODDatArr[ PDO1_Trans_Type ].all         = Prm.Tpdo1Type;
    ODDatArr[ PDO1_Trans_Inhibt_Time ].all  = Prm.Tpdo1InTime;
    ODDatArr[ PDO1_Trans_Event_Time ].all   = Prm.Tpdo1EventTime;
      
    // TPDO2
    ODDatArr[ PDO2_Trans_Map_Num ].all      = Prm.Tpdo2;
    ODDatArr[ PDO2_Trans_Map1 ].all         = ULONGOF( Prm.Tpdo2Map1L, Prm.Tpdo2Map1H );
    ODDatArr[ PDO2_Trans_Map2 ].all         = ULONGOF( Prm.Tpdo2Map2L, Prm.Tpdo2Map2H );
    ODDatArr[ PDO2_Trans_Map3 ].all         = ULONGOF( Prm.Tpdo2Map3L, Prm.Tpdo2Map3H );
    ODDatArr[ PDO2_Trans_Map4 ].all         = ULONGOF( Prm.Tpdo2Map4L, Prm.Tpdo2Map4H );
    ODDatArr[ PDO2_Trans_COB_ID ].all       = ULONGOF( Prm.Tpdo2StationL, Prm.Tpdo2StationH );
    ODDatArr[ PDO2_Trans_Type ].all         = Prm.Tpdo2Type;
    ODDatArr[ PDO2_Trans_Inhibt_Time ].all  = Prm.Tpdo2InTime;
    ODDatArr[ PDO2_Trans_Event_Time ].all   = Prm.Tpdo2EventTime;

    // TPDO3
    ODDatArr[ PDO3_Trans_Map_Num ].all      = Prm.Tpdo3;
    ODDatArr[ PDO3_Trans_Map1 ].all         = ULONGOF( Prm.Tpdo3Map1L, Prm.Tpdo3Map1H );
    ODDatArr[ PDO3_Trans_Map2 ].all         = ULONGOF( Prm.Tpdo3Map2L, Prm.Tpdo3Map2H );
    ODDatArr[ PDO3_Trans_Map3 ].all         = ULONGOF( Prm.Tpdo3Map3L, Prm.Tpdo3Map3H );
    ODDatArr[ PDO3_Trans_Map4 ].all         = ULONGOF( Prm.Tpdo3Map4L, Prm.Tpdo3Map4H );
    ODDatArr[ PDO3_Trans_COB_ID ].all       = ULONGOF( Prm.Tpdo3StationL, Prm.Tpdo3StationH );
    ODDatArr[ PDO3_Trans_Type ].all         = Prm.Tpdo3Type;
    ODDatArr[ PDO3_Trans_Inhibt_Time ].all  = Prm.Tpdo3InTime;
    ODDatArr[ PDO3_Trans_Event_Time ].all   = Prm.Tpdo3EventTime;
    
    // TPDO4
    ODDatArr[ PDO4_Trans_Map_Num ].all      = Prm.Tpdo4;
    ODDatArr[ PDO4_Trans_Map1 ].all         = ULONGOF( Prm.Tpdo4Map1L, Prm.Tpdo4Map1H );
    ODDatArr[ PDO4_Trans_Map2 ].all         = ULONGOF( Prm.Tpdo4Map2L, Prm.Tpdo4Map2H );
    ODDatArr[ PDO4_Trans_Map3 ].all         = ULONGOF( Prm.Tpdo4Map3L, Prm.Tpdo4Map3H );
    ODDatArr[ PDO4_Trans_Map4 ].all         = ULONGOF( Prm.Tpdo4Map4L, Prm.Tpdo4Map4H );
    ODDatArr[ PDO4_Trans_COB_ID ].all       = ULONGOF( Prm.Tpdo4StationL, Prm.Tpdo4StationH );
    
    ODDatArr[ PDO4_Trans_Type ].all         = Prm.Tpdo4Type;
    ODDatArr[ PDO4_Trans_Inhibt_Time ].all  = Prm.Tpdo4InTime;
    ODDatArr[ PDO4_Trans_Event_Time ].all   = Prm.Tpdo4EventTime;
    
    //RPDO1
    ODDatArr[ PDO1_Receive_Map_Num ].all      = Prm.RPDO1;
    ODDatArr[ PDO1_Receive_Map1 ].all         = ULONGOF( Prm.RPDO1Map1L, Prm.RPDO1Map1H );
    ODDatArr[ PDO1_Receive_Map2 ].all         = ULONGOF( Prm.RPDO1Map2L, Prm.RPDO1Map2H );
    ODDatArr[ PDO1_Receive_Map3 ].all         = ULONGOF( Prm.RPDO1Map3L, Prm.RPDO1Map3H );
    ODDatArr[ PDO1_Receive_Map4 ].all         = ULONGOF( Prm.RPDO1Map4L, Prm.RPDO1Map4H );
    
    ODDatArr[ PDO1_Receive_COB_ID ].all       = ULONGOF( Prm.RPDO1StationL, Prm.RPDO1StationH );
    ODDatArr[ PDO1_Receive_Type ].all         = Prm.RPDO1Type;
    
    //RPDO2
    ODDatArr[ PDO2_Receive_Map_Num ].all      = Prm.RPDO2;
    ODDatArr[ PDO2_Receive_Map1 ].all         = ULONGOF( Prm.RPDO2Map1L, Prm.RPDO2Map1H );
    ODDatArr[ PDO2_Receive_Map2 ].all         = ULONGOF( Prm.RPDO2Map2L, Prm.RPDO2Map2H );
    ODDatArr[ PDO2_Receive_Map3 ].all         = ULONGOF( Prm.RPDO2Map3L, Prm.RPDO2Map3H );
    ODDatArr[ PDO2_Receive_Map4 ].all         = ULONGOF( Prm.RPDO2Map4L, Prm.RPDO2Map4H );
    
    ODDatArr[ PDO2_Receive_COB_ID ].all       = ULONGOF( Prm.RPDO2StationL, Prm.RPDO2StationH );
    ODDatArr[ PDO2_Receive_Type ].all         = Prm.RPDO2Type;    

    //RPDO3
    ODDatArr[ PDO3_Receive_Map_Num ].all      = Prm.RPDO3;
    ODDatArr[ PDO3_Receive_Map1 ].all         = ULONGOF( Prm.RPDO3Map1L, Prm.RPDO3Map1H );
    ODDatArr[ PDO3_Receive_Map2 ].all         = ULONGOF( Prm.RPDO3Map2L, Prm.RPDO3Map2H );
    ODDatArr[ PDO3_Receive_Map3 ].all         = ULONGOF( Prm.RPDO3Map3L, Prm.RPDO3Map3H );
    ODDatArr[ PDO3_Receive_Map4 ].all         = ULONGOF( Prm.RPDO3Map4L, Prm.RPDO3Map4H );
    
    ODDatArr[ PDO3_Receive_COB_ID ].all       = ULONGOF( Prm.RPDO3StationL, Prm.RPDO3StationH );
    ODDatArr[ PDO3_Receive_Type ].all         = Prm.RPDO3Type;
    
    //RPDO4
    ODDatArr[ PDO4_Receive_Map_Num ].all      = Prm.RPDO4;
    ODDatArr[ PDO4_Receive_Map1 ].all         = ULONGOF( Prm.RPDO4Map1L, Prm.RPDO4Map1H );
    ODDatArr[ PDO4_Receive_Map2 ].all         = ULONGOF( Prm.RPDO4Map2L, Prm.RPDO4Map2H );
    ODDatArr[ PDO4_Receive_Map3 ].all         = ULONGOF( Prm.RPDO4Map3L, Prm.RPDO4Map3H );
    ODDatArr[ PDO4_Receive_Map4 ].all         = ULONGOF( Prm.RPDO4Map4L, Prm.RPDO4Map4H );
    
    ODDatArr[ PDO4_Receive_COB_ID ].all       = ULONGOF( Prm.RPDO4StationL, Prm.RPDO4StationH );
    ODDatArr[ PDO4_Receive_Type ].all         = Prm.RPDO4Type;
    
    
    ODDatArr[ EMCY_COB_ID ].all               = ULONGOF( Prm.EmcyEnL, Prm.EmcyEnH );
    ODDatArr[ Consumer_HeartBeat_Time ].all   = ULONGOF( Prm.HeartConsumerL, Prm.HeartConsumerH );
    
    ODDatArr[ Producer_HeartBeat_Time ].all   = Prm.HeartProducter;
    ODDatArr[ Guard_Time ].all                = Prm.Guardtime;
    ODDatArr[ Life_Time ].all                 = Prm.lifetime;
    
    ODDatArr[ Serial_Num ].all   = SystemVar.SnNum;
}

void ODB_Cia402_Init( void )
{
    ODDatArr[ Quick_stop_option_code ].all  = (SHORT)Prm.OBJ_605A;
    ODDatArr[ Halt_option_code ].all        = (SHORT)Prm.OBJ_605D;
    ODDatArr[ Follow_Error_Window_MM ].all  = ULONGOF( Prm.OBJ_6065_L, Prm.OBJ_6065_H );
    ODDatArr[ Position_Window_MM ].all      = ULONGOF( Prm.OBJ_6067_L, Prm.OBJ_6067_H );
    ODDatArr[ Position_Window_Time_MS ].all = ULONGOF( Prm.OBJ_6068_L, Prm.OBJ_6068_H );
    ODDatArr[ Velocity_Window_RPM ].all     = (SHORT)Prm.OBJ_606D;
    ODDatArr[ Velocity_Window_Time_MS ].all = (SHORT)Prm.OBJ_606E;
    ODDatArr[ Zero_Velocity_Threshold ].all = (SHORT)Prm.OBJ_606F;
    ODDatArr[ Zero_Velocity_Time_MS ].all   = (SHORT)Prm.OBJ_6070;
    ODDatArr[ Max_Torque ].all              = (SHORT)Prm.OBJ_6072;
    //ODDatArr[Targe_Position_MM ].all        = ULONGOF( Prm.OBJ_607A_L, Prm.OBJ_607A_H );
    ODDatArr[Homing_Offset_MM ].all         = ULONGOF( Prm.OBJ_607C_L, Prm.OBJ_607C_H );
    ODDatArr[Min_Soft_Posi_Limit ].all      = ULONGOF( Prm.OBJ_607D_01_L, Prm.OBJ_607D_01_H );
    ODDatArr[Max_Soft_Posi_Limit ].all      = ULONGOF( Prm.OBJ_607D_02_L, Prm.OBJ_607D_02_H);
    ODDatArr[Polarity ].all                 = (SHORT)Prm.OBJ_607E;
    ODDatArr[Max_Profile_Velocity ].all     = ULONGOF( Prm.OBJ_607F_L, Prm.OBJ_607F_H);
    ODDatArr[Profile_Velocity_RPM ].all     = ULONGOF( Prm.OBJ_6081_L, Prm.OBJ_6081_H);
    ODDatArr[Profile_Acceleration ].all     = ULONGOF( Prm.OBJ_6083_L, Prm.OBJ_6083_H);
    ODDatArr[Profile_Deceleration ].all     = ULONGOF( Prm.OBJ_6084_L, Prm.OBJ_6084_H );
    ODDatArr[Quick_Stop_Deceleration ].all  = ULONGOF( Prm.OBJ_6085_L, Prm.OBJ_6085_H );
    ODDatArr[Torque_Slope_MS ].all          = ULONGOF( Prm.OBJ_6087_L, Prm.OBJ_6087_H );
    ODDatArr[ Position_Factor_Numer].all    = ULONGOF( Prm.OBJ_6091_01_L, Prm.OBJ_6091_01_H);
    ODDatArr[ Position_Factor_Divisor].all  = ULONGOF( Prm.OBJ_6091_02_L, Prm.OBJ_6091_02_H );
    ODDatArr[ Homing_Method].all            = (SHORT)Prm.OBJ_6098;
    ODDatArr[ Search_Switch_Spd].all        = LONGOF( Prm.OBJ_6099_01_L, Prm.OBJ_6099_01_H );
    ODDatArr[ Search_Zero_Spd].all          = LONGOF( Prm.OBJ_6099_02_L, Prm.OBJ_6099_02_H );
    ODDatArr[ Homing_Acceleration].all      = LONGOF( Prm.OBJ_609A_L, Prm.OBJ_609A_H );
    ODDatArr[ Postion_Offset].all           = LONGOF( Prm.OBJ_60B0_L, Prm.OBJ_60B0_H );
    ODDatArr[ Spd_Offset].all               = LONGOF( Prm.OBJ_60B1_L, Prm.OBJ_60B1_H );
    ODDatArr[ Torque_Offset].all            = (SHORT) Prm.OBJ_60B2_L;
    ODDatArr[ TouchProbe_Fun].all           = (SHORT)Prm.OBJ_60B8;
    ODDatArr[ Position_CMD_Lowword].all     = LONGOF( Prm.OBJ_60C1_01_L, Prm.OBJ_60C1_01_H );
    ODDatArr[ Interpolation_Period_Unit].all= (SHORT)Prm.OBJ_60C2_01;
    ODDatArr[ Interpolation_Period_Index].all= (SHORT)Prm.OBJ_60C2_02;
    ODDatArr[ Max_Acceleration].all         = LONGOF( Prm.OBJ_60C5_L, Prm.OBJ_60C5_H );
    ODDatArr[ Max_Deceleration].all         = LONGOF( Prm.OBJ_60C6_L, Prm.OBJ_60C6_H );
    ODDatArr[ Positive_torque_limit].all    = (SHORT)Prm.OBJ_60E0;
    ODDatArr[ Negtive_torque_limit].all     = (SHORT)Prm.OBJ_60E1;
    ODDatArr[ Target_Velocity_RPM].all      = LONGOF( Prm.OBJ_60FF_L, Prm.OBJ_60FF_H );
    
    ODDatArr[ MIT_PosO_FTC].all             = (SHORT)Prm.MIT_PosFil;
    ODDatArr[ MIT_TorqueO_FTC].all          = (SHORT)Prm.MIT_Tref;
    ODDatArr[ MIT_Red_Num].all              = (SHORT)Prm.MIT_RateA;
    ODDatArr[ MIT_Red_Den].all              = (SHORT)Prm.MIT_RateB;
}


