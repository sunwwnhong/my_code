/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Mot06_MotorParamTable.c
* Version            : V0.1
* Date               : 2024
* Description        : 电机相关变量处理
***********************************************************************************************/
  
#include "Main.h"


#define MOTOR_PARA_EEPROM_WRITE                  ((Prm.syssw1 & 0x0080) == 0x0080)    /* 功能码开启STO

/*  电机参数表声明 */
#define NUM_INCMTR_TYPE 15
const USHORT MtrParaTable[][NUM_INCMTR_TYPE];
void MotTableMap(USHORT index);
 
  
/**********************************************************************************************/
/* Function_Name: KpxCheckAmpMotType*/
/* Description  : 伺服驱动器 & 伺服电机的型号检查
                  main函数调用
            功能：
            不匹配条件：（1）电机与驱动器的输入电压不一致
                        （2）电机与驱动器的容量差为4倍以上*/
/**********************************************************************************************/
void KpxCheckAmpMotType( void )
{
  
    /*  厂家测试模式时执行相关的操作 */
    if( Iprm.FATest1 == 1 || Iprm.FATest2 == 1 )        // 单板测试
    {
        return;
    }

    if( MencV.f.EncConnect != TRUE ) //  编码器没有连接时,数据可能异常,出现误报,优化
    {
        return;
    }

  
     if( Bprm.AmpOutVcode == 3 || Bprm.AmpOutVcode == 4 )
    {
    }
    else
    {
        if( Bprm.AmpOutVcode != Bprm.MotVcode )
        {
            if( (Prm.b_prm0_0E & 0x0010) == 0x0000 )
            {
                KPI_ALARMSET( ALM_UNMATCH );    // A.050 : Motor / servo capacity unmatched
                return;
            }
        }
    }

    if( Bprm.AmpMotWatRatio < 0x4000 || Bprm.AmpMotWatRatio > 0x40000 )
    {
        if( (Prm.almmsk1 & 0x0002) == 0x0000 )
            KPI_ALARMSET( ALM_UNMATCH );		// A.050 : Motor / servo capacity unmatched
    }
    return;
}
 
  
  
/**********************************************************************************************/
/* Function_Name: MotTableMap*/
/* Description  : 电机参数查表函数
                  电机参数初始化调用，根据电机型号查表得到电机参数*/
/**********************************************************************************************/
void MotTableMap(USHORT index)
{
USHORT i = 1;
    if( !MOTOR_PARA_EEPROM_WRITE )
    {
        Prm.typm_e.w        = MtrParaTable[i++][index];         // PnF00 : 高8位:编码器类型(4bit)|电机输入电压代码(4bit),低8位:电机类型
        Prm.encver          = MtrParaTable[i++][index];         // PnF01 : 编码器软件版本
        Prm.motw            = MtrParaTable[i++][index];         // PnF02 : 电机容量
        Prm.bit_dp.w        = MtrParaTable[i++][index];         // PnF03 : 高字节:位置数据点位置，低字节:编码器位数
        Prm.limmlt          = MtrParaTable[i++][index];         // PnF04 : 多回转限位，单圈为0
        Prm.vrat_max.w      = MtrParaTable[i++][index];         // PnF05 : 高8位: 最高转速，低8位: 额定转速
        Prm.oslv_pol.w      = MtrParaTable[i++][index];         // PnF06 : 高8位: 极数，低8位: OS检测水平
        Prm.rattrq          = MtrParaTable[i++][index];         // PnF07 : 额定转矩 [0.01Nm]
        Prm.maxtrq          = MtrParaTable[i++][index];         // PnF08 : 最大扭矩百分比
        Prm.irat            = MtrParaTable[i++][index];         // PnF09 : 电机额定电流 [0.1A]
        Prm.imax            = MtrParaTable[i++][index];         // PnF0A : 电机瞬时最大电流  [0.1A]
        Prm.emfcmp          = MtrParaTable[i++][index];         // PnF0B : 电动势(EMF)常数 [0.1mV/rpm]
        Prm.jmot            = MtrParaTable[i++][index];         // PnF0C : 转子惯量 [10-6kgm2]
        Prm.motr            = MtrParaTable[i++][index];         // PnF0D : 电枢绕组电阻 [0.001Ω]
        Prm.motl            = MtrParaTable[i++][index];         // PnF0E : 电枢电感 [0.01mH]
        Prm.bastrq          = MtrParaTable[i++][index];         // PnF0F : 电机过载检测的基极电流 [%]
        Prm.midtrq          = MtrParaTable[i++][index];         // PnF10 : 电机过载检测的中间电流 [%]
        Prm.midolt          = MtrParaTable[i++][index];         // PnF11 : 电机中间电流运行时过载检测时间 [10s]
        Prm.mtrq2           = MtrParaTable[i++][index];         // PnF12 : 电机过载检测的最大电流 [%]
        Prm.mtolt2          = MtrParaTable[i++][index];         // PnF13 : 电机最大电流运行时过载检测时间 [s]
        Prm.phscmpM1        = MtrParaTable[i++][index];         // PnF14 : 相位补偿1(补偿值，启动速度) [deg,100rpm]
        Prm.ppitch          = MtrParaTable[i++][index];         // PnF15 : 极距 [0.1mm/180deg]
        Prm.motlq0          = MtrParaTable[i++][index];         // PnF16 : q轴电感LQ0 [0.01mH]
        Prm.motlq1          = MtrParaTable[i++][index];         // PnF17 : q轴电感Lq1 [0.01mH]
        Prm.exp_trat_jmot   = MtrParaTable[i++][index];         // PnF18 : 高8位：转子惯量指数，低8位：额定转矩指数 [10n]
        Prm.exp_motw_spd    = MtrParaTable[i++][index];         // PnF19 : 高8位：转速指数低，8位：额定输出指数 [10n]
        Prm.fbit_fdp        = MtrParaTable[i++][index];         // PnF1A : 全闭环编码器比特数, 位置数据点位置
        Prm.poleoffset      = MtrParaTable[i++][index];         // PnF1B : 编码器偏移角 [deg]
        Prm.motresfrq       = MtrParaTable[i++][index];         // PnF1C : 电机共振抑制陷波滤波器的频率
        Prm.phscmpM2        = MtrParaTable[i++][index];         // PnF1D : 相角修正值 [65536/360deg]
        Prm.flg_wf          = MtrParaTable[i++][index];         // PnF1E : Flag [-]
    }
    else
    {
        Prm.typm_e.w        = Prm.typm_e_1.w;         // PnF00 : 高8位:编码器类型(4bit)|电机输入电压代码(4bit),低8位:电机类型
        Prm.encver          = Prm.encver_1;         // PnF01 : 编码器软件版本
        Prm.motw            = Prm.motw_1;         // PnF02 : 电机容量
        Prm.bit_dp.w        = Prm.bit_dp_1.w ;         // PnF03 : 高字节:位置数据点位置，低字节:编码器位数
        Prm.limmlt          = Prm.limmlt_1;         // PnF04 : 多回转限位，单圈为0
        Prm.vrat_max.w      = Prm.vrat_max_1.w;         // PnF05 : 高8位: 最高转速，低8位: 额定转速
        Prm.oslv_pol.w      = Prm.oslv_pol_1.w;         // PnF06 : 高8位: 极数，低8位: OS检测水平
        Prm.rattrq          = Prm.rattrq_1;         // PnF07 : 额定转矩 [0.01Nm]
        Prm.maxtrq          = Prm.maxtrq_1;         // PnF08 : 最大扭矩百分比
        Prm.irat            = Prm.irat_1;         // PnF09 : 电机额定电流 [0.1A]
        Prm.imax            = Prm.imax_1;         // PnF0A : 电机瞬时最大电流  [0.1A]
        Prm.emfcmp          = Prm.emfcmp_1;         // PnF0B : 电动势(EMF)常数 [0.1mV/rpm]
        Prm.jmot            = Prm.jmot_1;         // PnF0C : 转子惯量 [10-6kgm2]
        Prm.motr            = Prm.motr_1;         // PnF0D : 电枢绕组电阻 [0.001Ω]
        Prm.motl            = Prm.motl_1;         // PnF0E : 电枢电感 [0.01mH]
        Prm.bastrq          = Prm.bastrq_1;         // PnF0F : 电机过载检测的基极电流 [%]
        Prm.midtrq          = Prm.midtrq_1;         // PnF10 : 电机过载检测的中间电流 [%]
        Prm.midolt          = Prm.midolt_1;         // PnF11 : 电机中间电流运行时过载检测时间 [10s]
        Prm.mtrq2           = Prm.mtrq2_1;         // PnF12 : 电机过载检测的最大电流 [%]
        Prm.mtolt2          = Prm.mtolt2_1;         // PnF13 : 电机最大电流运行时过载检测时间 [s]
        Prm.phscmpM1        = Prm.phscmpM1_1;         // PnF14 : 相位补偿1(补偿值，启动速度) [deg,100rpm]
        Prm.ppitch          = Prm.ppitch_1;         // PnF15 : 极距 [0.1mm/180deg]
        Prm.motlq0          = Prm.motlq0_1;         // PnF16 : q轴电感LQ0 [0.01mH]
        Prm.motlq1          = Prm.motlq1_1;         // PnF17 : q轴电感Lq1 [0.01mH]
        Prm.exp_trat_jmot   = Prm.exp_trat_jmot_1;         // PnF18 : 高8位：转子惯量指数，低8位：额定转矩指数 [10n]
        Prm.exp_motw_spd    = Prm.exp_motw_spd_1;         // PnF19 : 高8位：转速指数低，8位：额定输出指数 [10n]
        Prm.fbit_fdp        = Prm.fbit_fdp_1;         // PnF1A : 全闭环编码器比特数, 位置数据点位置
        Prm.poleoffset      = Prm.poleoffset_1;         // PnF1B : 编码器偏移角 [deg]
        Prm.motresfrq       = Prm.motresfrq_1;         // PnF1C : 电机共振抑制陷波滤波器的频率
        Prm.phscmpM2        = Prm.phscmpM2_1;         // PnF1D : 相角修正值 [65536/360deg]
        Prm.flg_wf          = Prm.flg_wf_1;         // PnF1E : Flag [-]

    }
}

/***************************************************************************************************
                                            电机参数表
PnF18:转子惯量指数为10^(n),其中n是有符号的8位数,惯量PnF0C的单位为10^(-6),当惯量的量程不够表达时,则使用
      PnF的系数进行加大或缩小处理.
****************************************************************************************************/
const USHORT MtrParaTable[][NUM_INCMTR_TYPE] =
{

//科大J4 80mm    90mm    110mm   142mm    170mm   52mm    40mm      6408     8112     4310    10020-16  10020-27 U6836    U8567
{0x0001 ,0x0002 ,0x0003 ,0x0004  ,0x0005 ,0x0006 ,0x0007  ,0x0008  ,0x0009  ,0x000A  ,0x000B  ,0x000C  ,0x000D  ,0x000E  ,0x000F },
{0x146D ,0x246D ,0x246D ,0x246D  ,0x246D ,0x246D ,0x246D  ,0x246D  ,0x146D  ,0x146D  ,0x146D  ,0x146D  ,0x146D  ,0x146D  ,0x146D },      // 高8位:编码器类型(4bit)|电机输入电压代码(4bit),低8位:电机类型
{0x00   ,0      ,0x00   ,0x00    ,0x00   ,0x00   ,0x00    ,0x00    ,0x00    ,0x00    ,0x00    ,0x00    ,0x00    ,0x00    ,0x00   },      // 编码器软件版本
{500    ,189    ,387    ,648     ,1021   ,1000   ,63      ,37      ,270     ,505     ,130     ,800     ,1360    ,487     ,850    },      // 电机容量
{0x5010 ,0x5011 ,0x5011 ,0x5011  ,0x5011 ,0x5011 ,0x5011  ,0x5010  ,0x5010  ,0x5010  ,0x5010  ,0x5010  ,0x5010  ,0x5010  ,0x5010 },      // 高字节:位置数据点位置，低字节:编码器位数
{0x0000 ,0x0    ,0x0000 ,0x0000  ,0x0000 ,0x0000 ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000 },      // 多圈上限值，单圈为0
{0x2D1E ,0x3C1E ,0x3C1E ,0x321E  ,0x2319 ,0x1E14 ,0x3C1E  ,0x4132  ,0x3021  ,0x281C  ,0x231E  ,0x140F  ,0x1E19  ,0x2D1E  ,0x2D1E },      // 高8位: 最高转速，低8位: 额定转速
{0x100A ,0x140A ,0x140A ,0x140A  ,0x1A0A ,0x1A0A ,0x0E0A  ,0x140A  ,0x1C0A  ,0x2A0A  ,0x1C0A  ,0x2A0A  ,0x2A0A  ,0x140A  ,0x140A },      // 高8位: 极数，低8位: OS检测水平
{160    ,60     ,123    ,206     ,390    ,477    ,20      ,7       ,78      ,176     ,42      ,520     ,520     ,155     ,270    },      // 额定转矩 [0.01Nm]
{300    ,300    ,300    ,300     ,300    ,300    ,300     ,300     ,256     ,250     ,300     ,300     ,300     ,300     ,300    },      // 最大扭矩百分比
{165    ,89     ,141    ,191     ,311    ,354    ,49      ,17      ,81      ,150     ,42      ,226     ,382     ,170     ,334    },      // 电机额定电流
{501    ,219    ,424    ,566     ,933    ,1131   ,148     ,51      ,216     ,383     ,127     ,679     ,1372    ,509     ,1001   },      // 电机瞬时最大电流
{85     ,70     ,70     ,90      ,80     ,140    ,70      ,50      ,68      ,105     ,91      ,176     ,106     ,80      ,77     },      // 反电动势(EMF)常数
{66     ,15     ,58     ,97      ,208    ,380    ,4       ,2       ,33      ,67      ,14      ,92      ,102     ,68      ,123    },      // 转子惯量
{120    ,430    ,210    ,160     ,90     ,60     ,1800    ,4436    ,616     ,340     ,1930    ,166     ,56      ,144     ,55     },      // 电枢绕组电阻
{29     ,23     ,20     ,14      ,12     ,10     ,67      ,53      ,19      ,17      ,74      ,9       ,4       ,14      ,13     },      // 电枢电感
{115    ,115    ,115    ,115     ,115    ,115    ,115     ,115     ,115     ,115     ,115     ,115     ,115     ,115     ,115    },      // 电机过载检测的基极电流
{200    ,200    ,200    ,200     ,200    ,200    ,200     ,200     ,200     ,200     ,200     ,200     ,200     ,200     ,200    },      // 电机过载检测的中间电流
{60     ,60     ,60     ,60      ,60     ,60     ,60      ,60      ,60      ,60      ,60      ,60      ,60      ,60      ,60     },      // 电机中间电流运行时过载检测时间
{300    ,300    ,300    ,300     ,300    ,300    ,300     ,300     ,300     ,300     ,300     ,300     ,300     ,300     ,300    },      // 电机过载检测的最大电流
{8      ,8      ,8      ,8       ,8      ,8      ,8       ,8       ,8       ,8       ,8       ,8       ,8       ,8       ,8      },      // 电机最大电流运行时过载检测时间
{0      ,0      ,0      ,0       ,0      ,0      ,0       ,0       ,0       ,0       ,0       ,0       ,0       ,0       ,0      },      // 相位补偿1(补偿值，启动速度)
{0xFFFF ,0xFFFF ,0xFFFF ,0xFFFF  ,0xFFFF ,0xFFFF ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF },      // 极距
{0xFFFF ,0xFFFF ,0xFFFF ,0xFFFF  ,0xFFFF ,0xFFFF ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF },      // q轴电感LQ0
{0xFFFF ,0xFFFF ,0xFFFF ,0xFFFF  ,0xFFFF ,0xFFFF ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF  ,0xFFFF },      // q轴电感Lq1
{0x0000 ,0x0000 ,0x0000 ,0x0000  ,0x0000 ,0x0000 ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000 },      // 高8位：转子惯量指数，低8位：额定转矩指数
{0x0000 ,0x0000 ,0x0000 ,0x0000  ,0x0000 ,0x0000 ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000 },      // 高8位：转速指数低，8位：额定输出指数
{0x0000 ,0x0000 ,0x0000 ,0x0000  ,0x0000 ,0x0000 ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000  ,0x0000 },      // 全闭环编码器比特数, 位置数据点位置
{0      ,0      ,0      ,0       ,0      ,0      ,0       ,0       ,0       ,0       ,0       ,0       ,0       ,0       ,0      },      // 编码器偏移角
{0      ,0      ,0      ,0       ,0      ,0      ,0       ,0       ,0       ,0       ,0       ,0       ,0       ,0       ,0      },      // 电机共振抑制陷波滤波器的频率
{0      ,0      ,0      ,0       ,0      ,0      ,0       ,0       ,0       ,0       ,0       ,0       ,0       ,0       ,0      },      // 相角修正值
{0x0001 ,0x0001 ,0x0001 ,0x0001  ,0x0001 ,0x0001 ,0x0001  ,0x0001  ,0x0001  ,0x0001  ,0x0001  ,0x0001  ,0x0001  ,0x0001  ,0x0001 }
};

/*--------------------------------------------------------------------------------------------------*/
/*                                          End of The File                                         */
/*--------------------------------------------------------------------------------------------------*/
