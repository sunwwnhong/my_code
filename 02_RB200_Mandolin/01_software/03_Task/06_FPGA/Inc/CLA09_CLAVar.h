 
#ifndef CLA09_CLAVar_H
#define CLA09_CLAVar_H

/**********************************CLA电流环控制变量定义********************************************/
typedef struct
{
  
    float hm_3th;            
    float Cur_Coeff1;       // 电流环CLARK变换系数1
    float Cur_Coeff2;       // 电流环CLARK变换系数2
    float RxComp;           // 电阻补偿系数
    float LdComp;           // 电感补偿系数
    float LqComp;           // 电感补偿系数
    float EmfCompCoeff;     // 反电势补偿系数
    float DDidt;            // d轴电感补偿系数
    float QDidt;            // q轴电感补偿系数
    float VCompGain;        // 前馈解耦补偿增益
    float DQFilter;         // Ud Uq滤波系数
    float Cur_DKp;         // 电流环比例增益(D轴)
    float Cur_DKi;         // 电流环积分增益(D轴)
    float Cur_QKp;         // 电流环比例增益(Q轴)
    float Cur_QKi;         // 电流环积分增益(Q轴)
    float DQKiLimitMax;    // 积分环节正向最大电流输出  ->15000
    float DQKiLimitMin;    // 积分环节反向最大电流输出  ->15000

}ACRP;
 #ifdef CPU1
extern volatile ACRP Acr_P[2];
#endif

/**********************************CLA电流环PWM占空比参数定义********************************************/
typedef struct
{
    float UdcRatio;             // 母线电压利用率
    float PWMPeriod;            // PWM 周期值
    uint16_t PWMPeriodMax;      // PWM 周期最大限制值
    uint16_t PWMPeriodMax1;     // PWM 周期最大限制值1
    uint16_t PWMPeriodMin;      // PWM 周期最小限制值1
    uint16_t ADCSample;         // PWM 采样窗口转空比限制
}ACRPCom;
extern volatile ACRPCom ACRCom;

/**********************************CLA 电流采样变量定义********************************************/
typedef struct
{
    float AdcUZero;         //U相零点偏置
    float AdcVZero;         //V相零点偏置
    float AdcWZero;         //W相零点偏置
	float IUZero;
    float IVZero;
    float IWZero;

    uint16_t ZeroOk;
}ACR_I;
#ifdef CPU1
extern volatile ACR_I Acr_I[2];
#endif

/**********************************CLA矢量控制变量定义********************************************/
typedef struct ACRV
{
    float SinVal;       //矢量角度正弦值           0->1   0->2pi
    float CosVal;       //矢量角度余弦正弦值        0->1   0->2pi
    float MotWm;        //电机转速（反电势补偿用）    15000->Vmax
    float Id_Cmd;       //d轴电流指令            15000->Imax
    float Iq_Cmd;       //q轴电流指令            15000->Imax
    float hm3th;

    float UqCmd;        //VF控制下 q轴指令
    uint16_t VFtest;    //PnE1C控制位
    uint16_t PWMEn_Step; // 自举开启步骤
}ACRV;
 
extern volatile ACRV Acr_V;
extern volatile uint16_t ACR_Smachine;
extern volatile uint16_t ACR_Flag;           
#ifdef CPU1

/**********************************CLA矢量控制变量定义********************************************/
typedef struct
{
    struct
    {
        uint16_t PWMDir1    :1;     //EPWM计数器计数方向 0:正向 1:负向
        uint16_t PWMDir2    :1;
        uint16_t Resered    :14;
    }f;
    uint16_t Reserved;       
    float Iu;               //U相电流ADC采集(控制用)
    float Iv;               //V相电流ADC采集(控制用)
    float Iw;               //W相电流ADC采集(控制用)
    float Iuu;              //U相电流ADC采集(监控用)
    float Ivv;              //V相电流ADC采集(监控用)
    float Iww;              //W相电流ADC采集(监控用)
    float IdFbk;            //d轴电流反馈                    15000->Imax
    float IqFbk;            //q轴电流反馈                    15000->Imax
    float IdKiSum;          //d轴电流积分值                   15000->Imax
    float IqKiSum;          //q轴电流积分值                   15000->Imax
    float Vd;               //d轴电压给定                    [-8192,8192] -> [-Udc,Udc]
    float Vq;               //q轴电压给定                    [-8192,8192] -> [-Udc,Udc]
    float IdCmdOld;         //d轴电流指令上个周期值              15000->Imax
    float IqCmdOld;         //q轴电流指令上个周期值              15000->Imax
    int16_t PWMStatus;      //PWM限制状态(下三桥采样判定标志)
    uint16_t IGBTTemp;      //IGBT温度ADC采集值
    uint16_t Mot_Udc;       //母线电压ADC采集值
    uint16_t DriveType;     //功率判定ADC采集值
	uint16_t AIInput;
	uint16_t HallBSIN;
	uint16_t HallBCOS;
 }A2C_MotAVAR;
extern A2C_MotAVAR AMotVar[2];
 
/**********************************CLA辅助控制变量定义********************************************/
typedef struct
{
    uint16_t ACRUpdateErr;          //CLA负荷过大错误计数
    float ACRExeTime;               //CLA执行时间（us）
    uint16_t DspCoreTemp;           //芯片温度ADC采样值
    float Monitor1;
    float Monitor2;
    float Monitor3;
    float Monitor4;
    float Monitor5;
    uint32_t StartCnt;              //CLA启动计数值
    uint32_t EndCnt;                //CLA停止计数值
}CLA1_CPU1VAR;
extern CLA1_CPU1VAR A1ToC1V;
 
/**********************************CLA模块变量定义********************************************/
typedef struct
{
    float DQFilter;             //Ud、Uq滤波系数
    float Id_Fbk;               //d轴电流反馈        15000->Imax
    float Iq_Fbk;               //q轴电流反馈        15000->Imax
    float IdPiOut;              //d轴电流环PI输出
    float IqPiOut;              //q轴电流环PI输出
    float Vd;                   //d轴电压给定                    [-8192,8192] -> [-Udc,Udc]
    float Vq;                   //q轴电压给定                    [-8192,8192] -> [-Udc,Udc]
    float PWMStatus;            //PWM限制状态(下三桥采样判定标志)
    float Ia;                   //U相电流给定（死区补偿用）       15000->Imax
    float Ib;                   //V相电流给定（死区补偿用）       15000->Imax
    float Ic;                   //W相电流给定（死区补偿用）       15000->Imax
    float DQKiLimitMax;         // 积分环节正向最大电流输出  15000->Imax
    float DQKiLimitMin;         // 积分环节正向最小电流输出  15000->Imax
    float Id_Cmd;               // d轴电流指令           15000->Imax
    float Iq_Cmd;               // qd轴电流指令           15000->Imax
    float CosVal;               //矢量角度余弦值           0->1   0->2pi
    float SinVal;               //矢量角度正弦值           0->1   0->2pi
    float MotWm;                //电机转速（反电势补偿用）    15000->Vmax
    float UqCmd;                //VF控制下 q轴指令
    float hm3th;
    uint16_t VFtest;            //PnE1C控制位
}CLA_VARDef;


/**********************************CLA滤波模块变量定义********************************************/
typedef struct
{
    float DFilter[2];       //Ud滤波后值
    float QFilter[2];       //Uq滤波后值
    float DFilter1[2];
    float QFilter1[2];
}CLA_GVARDef;
extern CLA_GVARDef CLAV;
#endif
  
typedef struct
{
    uint16_t  RecivedSum;                        
    uint16_t  MbusDataLen;                       
    uint16_t  ReciveBuf[256];                    
}USBRECBUF;
extern USBRECBUF UsbRecBuf;
 typedef struct
{
    uint16_t  TransSum;                          
    uint16_t  SkipSum;                           
    uint16_t  MbusTrnLength;                     
    uint16_t  TransBuf[256];                     
}USBTRSBUF;
extern USBTRSBUF UsbTrsBuf;

/**********************************系统标志位定义********************************************/
typedef union
{
    uint16_t w;
    struct {
        uint16_t    SysInitFlg      :1;       // 0.系统初始化完成标志
        uint16_t    WritenEn        :1;       // 1.数据写入使能
        uint16_t    DTWriteEn       :1;       // 2.死区补偿表写入标志位
        uint16_t    FanOnOff        :1;       // 3.风扇控制
        uint16_t    DBOnOff         :1;       // 4.动态制动
        uint16_t    RelayOnOff      :1;       // 5.充电继电器
        uint16_t    BKOnOff         :1;       // 6.再生制动
        uint16_t    ServoOnOff      :1;       // 7.伺服使能
        uint16_t    Reserved        :8;
     } f;
} SYSTEMBITDEF;
extern SYSTEMBITDEF SysBitDef;

/**********************************系统标志位1定义********************************************/
typedef union
{
    uint16_t w;
    /*------------------------------------------------------------------------------------*/
    struct {
        uint16_t    EncZKick      :4;       // 0-3: 编码器Z信号 Kick
        uint16_t    EncZSel       :1;       // 4:编码器Z信号选择
        uint16_t    EncZWidth     :8;       // 5-12:编码器Z信号宽度
        uint16_t    MossfetEn     :1;       // 13: Mos管自举充电开关
        uint16_t    Reserved      :1;       // 14: Mos管状态开关
        uint16_t    VFEn          :1;       // 15:VF工作状态标志
    } f;
} SYSTEMBITDEF1;
extern SYSTEMBITDEF1 SysBitDef1;

/**********************************系统标志位2定义********************************************/
typedef union
{
    uint16_t w;
     struct {
        uint16_t    EncPowerEn      :1;          // 0.系统初始化完成标志
        uint16_t    STOEnFlag       :1;          // 1.STO使能开关
        uint16_t    AcrType         :1;          // 2.ACR 类型
        uint16_t    IFbkType        :1;          // 3.电流反馈方式
        uint16_t    NoiseFil        :1;          // 4.噪声抑制开关
        uint16_t    ZOutSel         :1;          // 5.Z输出信号选择
        uint16_t    PulseSel        :1;          // 6.高低速脉冲选择
        uint16_t    ACT244Lock      :1;          // 7.ACT244 封锁信号
        uint16_t    Reserved8       :1;
        uint16_t    FlahWrite       :1;          // 9: Flash 写入标志
        uint16_t    Error           :1;          // 10:伺服ARM标志
        uint16_t    IPMOC_Switch    :1;          // 11: 硬件过流保护选择开关
        uint16_t    Reserved        :4;
    } f;
} SYSTEMBITDEF2;
extern SYSTEMBITDEF2 SysBitDef2;

/**********************************系统状态变量声明********************************************/
typedef union
{
/*-------------------------------------------------------------------------------------*/

    uint16_t w;
    struct {
        uint16_t    BaseEnable      :1;             // 伺服驱动器使能
        uint16_t    PhaseReady      :1;             // 电角度初始化(磁极检出)完成与否
        uint16_t    EncRead         :1;             // 编码器是否准备好
        uint16_t    PhaseStudy      :1;             // 磁极位置辨识
        uint16_t    ServoOnOffStatus:2;             // 伺服使能状态
        uint16_t    EepromError     :1;             // Eeprom错误
        uint16_t    EncError        :1;             // 编码器故障
        uint16_t    PwmEn           :1;             // PWM发波
        uint16_t    MotBPwmEn       :1;             // PWM发波（轴2）
        uint16_t    MotA_OC         :1;             // OC过流状态
        uint16_t    MotB_OC         :1;             // OC过流状态（轴2）
        uint16_t    Spare0B         :1;
        uint16_t    Spare0C         :1;
        uint16_t    Spare0D         :1;
        uint16_t    Spare0E         :1;
        uint16_t    Spare0F         :1;
    } f;
} SINV;
extern SINV StateM_Var;

/**********************************轴2状态变量声明********************************************/
typedef union
{
    uint16_t w;
    struct {
        uint16_t    OC_Flg          :1;         // 伺服驱动器OC标志
        uint16_t    PwmEn           :1;         // 伺服驱动器PWM使能标志
        uint16_t    Spare0F         :14;
    } f;
} MOTB_STATUS;
extern MOTB_STATUS CPU12Var1;

/**********************************轴2指令变量声明********************************************/
typedef union
{
    uint16_t w;
    struct {
        uint16_t    ServoOnOff      :1;         // 伺服驱动器使能
        uint16_t    MossfetEn       :1;         // Mos管自举充电开关
        uint16_t    ACRP_Up         :1;         // 轴2升级标识
        uint16_t    MotlessEn       :1;         // 轴2运行标志
        uint16_t    EncError        :1;         // 轴2编码器故障
        uint16_t    ErrReset        :1;         // 轴2故障复位编码器故障
        uint16_t    Spare           :10;
    } f;
} MOTB_CMDSTATUS;
extern MOTB_CMDSTATUS CPU21Var1;
  
extern volatile uint16_t MotB_Udc_ADCSample;
extern volatile uint16_t MotB_IGBTTemp_ADCSample;
extern volatile uint16_t MotB_ICCoreTemp;
extern volatile float MotB_IqFbk;                          
extern volatile float MotB_IdFbk;                          
extern volatile float MotB_Qv;                             
extern volatile float MotB_Dv;                             
extern volatile float MotB_Iu;                             
extern volatile float MotB_Iv;                             
extern volatile float MotB_Iw;                             
extern volatile uint32_t MotA_InitSec;                     
//extern volatile float MotB_IuZero;
//extern volatile float MotB_IvZero;
//extern volatile float MotB_IwZero;
extern volatile uint16_t MotA_Pn080;                       
extern volatile uint16_t DriverType;                       
extern uint16_t DriverPowerType;                           
extern uint16_t MotA_PwmPeriod;                            
extern volatile ACRV MotB_AcrR_V;
extern volatile uint16_t MotB_EtherCATErrorCnt;
extern volatile uint16_t MotB_EtherCATErrorCode;
extern volatile uint16_t MotB_EtherCATErrorAddCode;

extern volatile uint16_t MotB_ErrFlag;
extern volatile uint16_t MotB_Iee;
extern volatile uint16_t MotB_Errcode;                   
extern volatile uint16_t MotB_Spd;                       
extern uint16_t MotB_SpdCmd;                             
extern uint16_t MotB_SpdDir;                             
extern uint16_t MotB_SerOnOff;                           
extern volatile uint16_t MotB_CmdValue;                  
  
extern uint16_t Eth_ReadPnKick;                          
extern uint16_t Eth_ReadUnKick;                          
extern uint16_t Eth_ReadAddr;                            
extern uint16_t Eth_ReadPnOkKick;                        
extern uint16_t Eth_ReadUnOkKick;                        
extern uint16_t Eth_ReadDataL;                           
extern uint16_t Eth_ReadDataH;                           
extern uint16_t Eth_WritePnKick;
extern uint16_t Eth_WriteAddr;                           
extern uint16_t Eth_WriteL;                              
extern uint16_t Eth_WriteH;

extern uint32_t EtherCatSyncTimeus;
extern uint32_t Var_SnNum;
extern uint16_t MotA_ErrFlag;
 
 
extern void CLAVar_Init( void );


extern void Err_OC_Reset( void );


 #endif
