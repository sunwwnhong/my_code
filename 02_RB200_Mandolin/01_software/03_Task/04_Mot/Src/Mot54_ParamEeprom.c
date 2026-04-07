/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : Mot54_ParamEeprom.c
* Version            : V0.1
* Date               : 2024
* Description        : EEP实现部分
***********************************************************************************************/
#include "Main.h"
 
/*** EEP中的ms等待函数 ***/
#define	EEP_WAIT_MS( ms, xscan )	KPI_SCANC_MS( ms - (xscan * KPI_SCCYCLEMS) )
  
LONG	GetEepromSemaphore( LONG wait );			 
void	FreeEepromSemaphore( void );				 
LONG	KriChkEepromQueue( ULONG queid );
void	KpxCheckEepromAllData( USHORT* bufx );
 
#define     EEPI2C_START        1
#define		EEPI2C_CONTINUE     0
#define		WAIT			    1
#define		NOWAIT			    0
#define	EEP_TWR					10

/*** 1）对于Pn组参数，其单个参数是按照16bit组织的。这主要是因为ModbusRTU协议中寄存器的大小就是16bit，
所以这里使用16bit作为参数的组织单元。对于32bit的参数，采用通过两个Pn参数组合而成，也就是两
个16bit单元组合而成，这两个组合单元的访问地址必须是相邻的
     2）所有访问EEP的Pn组参数（除了PE组），其16bit单元存放的EEP对应32bit，
高16bit存储的是出厂默认值；相邻两个Pn参数的EEP地址相差2。对于PE组参数，其存放的EEP对应16bit，
所以PE组参数在EEP中是没有额外单元存储出厂默认值的，相邻两个PE参数的EEP地址相差1
     3）这里的LWD_EEPADR表示32bit参数的低字EEP地址，HWD_EEPADR代表的是32bit参数的高字EEP地址 ***/

#define	ORG_EEPADR( pDef )		( (pDef)->EepromAddr )      // EEP的原始地址
#define	GET_EEPADR( pDef )		( (pDef)->EepromAddr & PRMDEF_EEPADRMSK )   // EEP的使用地址
#define	LWD_EEPADR( EepAdr )	( EepAdr & PRMDEF_EEPADRMSK )           // 32bit数据EEP的低字地址
#define	HWD_EEPADR( EepAdr )	( LWD_EEPADR( EepAdr ) + ((EepAdr & PRMDEF_NODEFTPRM)? 1 : 2) ) // 32bit数据EEP的高字地址
  
#define		SCANCPRMQUEMAX      4
/*** SCANC-EEP队列FIFO结构体：头尾计数器（大小2*SCANCPRMQUEMAX）;
写入参数属性变量数组（大小SCANCPRMQUEMAX）：地址，访问权限，长度，数据 ***/
typedef	struct {
    VUSHORT AddIdx;                 // SCANC-EEP队列FIFO的头变量
    VUSHORT WrtIdx;                 // SCANC-EEP队列FIFO的尾变量
    PWQENT  PrmEnt[SCANCPRMQUEMAX]; // SCANC-EEP队列FIFO数组
} CPRMQUE;
  
#define		ROUNDPRMQUEMAX      16
typedef	struct {
    VUSHORT AddIdx;                 // ROUND-EEP队列FIFO的头变量
    VUSHORT WrtIdx;                 // ROUND-EEP队列FIFO的尾变量
    PWQENT  PrmEnt[ROUNDPRMQUEMAX]; // ROUND-EEP队列FIFO数组
} RPRMQUE;
 EEPWQUE	EepromQueue;
static	CPRMQUE	ScanCPrmQue;
static	RPRMQUE	RoundPrmQue;
EEPINF	Eephdr;
EEPINF	EepInfo;
  
#define     EEWTYPE_TSTAMP      0   // Time Stamp
#define     EEWTYPE_ALMTRC      1   // Alarm Trace Data
#define     EEWTYPE_ALMTOL      2   // Alarm Trace Data & OL Info.
#define     EEWTYPE_USRPRM      3   // User Parameter
#define     EEWTYPE_SYSPRM      4   // System Parameter
#define     EEWTYPE_PRMCOPY     5   // Parameter Copy
#define     EEWTYPE_ALMMON      6   // Latched Monitor at Alarm
#define     EEWTYPE_OPTID       7   // ID of Option Card Connection
#define     EEWTYPE_DEFAULT     0xFF// Default
 
EEPMNG	EepMsg;
/*** 伺服驱动器类型结构体 ***/
typedef struct	{
    USHORT          SvNo;           // 伺服驱动器编号代码
    const USHORT    (*DriverTabDefIndex)[Param_Sum]; // 伺服驱动器对应的参数表格
} DriverTableStruct;
#define Driver_Sum                    9			// 伺服驱动器的总数量,根据实际调整
  
/*** RB200 默认参数表 ***/  
extern  const USHORT DriverTabDef_001E[Param_Sum];
extern  const USHORT DriverTabDef_002E[Param_Sum];
extern  const USHORT DriverTabDef_003E[Param_Sum];
extern  const USHORT DriverTabDef_004E[Param_Sum];
extern  const USHORT DriverTabDef_005E[Param_Sum];
extern  const USHORT DriverTabDef_006E[Param_Sum];
extern  const USHORT DriverTabDef_007E[Param_Sum];
extern  const USHORT DriverTabDef_008E[Param_Sum];
extern  const USHORT DriverTabDef_001B[Param_Sum];
/*** 伺服驱动器类型结构体数组 ***/ 
const DriverTableStruct DriverTabDefIndex[Driver_Sum] = {     
                                                        { 0x001E, &DriverTabDef_001E },
                                                        { 0x002E, &DriverTabDef_002E },
                                                        { 0x003E, &DriverTabDef_003E },
                                                        { 0x004E, &DriverTabDef_004E },
                                                        { 0x005E, &DriverTabDef_005E },
                                                        { 0x006E, &DriverTabDef_006E },
                                                        { 0x007E, &DriverTabDef_007E },
                                                        { 0x008E, &DriverTabDef_008E },
                                                        { 0x001B, &DriverTabDef_001B },
};
  
/*** EEP周期性写入过程状态枚举定义 ***/
enum	SWEQ_STEP_DEF {
		STEP_START		= 0,
 		STEP_GNLWR01	,
		STEP_GNLWR02	,
		STEP_GNLWR03	,
 		STEP_AOLWR01	,
		STEP_AOLWR02	,
 		STEP_ALMWR01	,
		STEP_ALMWR02	,
		STEP_ALMWR03	,
 		STEP_PRMRD01	,
		STEP_PRMRD02	,
		STEP_PRMWR01	,
		STEP_PRMWR02	,
		STEP_PRMWR03	,
		STEP_PRMWR11	,
		STEP_PRMWR12	,
		STEP_PRMWR13	,
		STEP_PRMWRS1	,
		STEP_PRMWRS2	,
#if ( EEPROM_COM_TYPE == EEPROM_COM_I2C )
		STEP_PRMWRS1_I2C,	 
#endif
 		STEP_PCOPY01	,
		STEP_PCOPY02	,
		STEP_PCOPY03	,
 		STEP_ALMON01	,
		STEP_ALMON02	,
		STEP_ALMON03	,
 		STEP_OPTID01	,	 
		STEP_OPTID02	,	 
		STEP_OPTID03	,	 
 		STEP_WRITEND	,
};
  
  
/**********************************************************************************************/
/* Function_Name: WriteEepromEnable         */
/* Description  : 写EEP使能
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
void	WriteEepromEnable( void )
{
	KPX_EepromWP_Enable;      // 关闭硬件写保护
	return;
}
  
/**********************************************************************************************/
/* Function_Name: WriteEepromDisable         */
/* Description  : 写EEP禁止
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
void	WriteEepromDisable( void )
{
	KPX_EepromWP_Disable;      // 使能硬件写保护
	return;
}
 
  
/**********************************************************************************************/
/* Function_Name: ReadEepromWord         */
/* Description  : 读取eep对应地址的字
                  调用：需要时调用
                  输入：
                  输出：   */
/**********************************************************************************************/
USHORT	ReadEepromWord( ULONG ParamAddr)
{
USHORT	Data;
/*** 这里ParamAddr是按照16bit为单元编址，而eep的物理地址是字节地址.由于AT24C64D是8K字节eep。
   所以这里，16bit单元地址最大4K，也就是4095；最后乘以二，对应到物理字节地址 ***/
ULONG	Eaddr = 2 * (ParamAddr & PRMDEF_EEPADRMSK);

    /*** 从eep读取一个字，其中是读取两个连续字节，并且第二个字节地址自动递增 ***/
    if(ReadEepromOneWord(Eaddr))
    {
          
    }
    Data = EepromReadValue();
 	return( (USHORT)Data );
}

/**********************************************************************************************/
/* Function_Name: KriReadEepromWord         */
/* Description  : 读取eep对应地址的字，包装ReadEepromWord函数
                  调用：暂未调用
                  输入：
                  输出：   */
/**********************************************************************************************/
USHORT	KriReadEepromWord( USHORT eeadr )
{
    return( ReadEepromWord( eeadr ));
}
 
  
/**********************************************************************************************/
/* Function_Name: InitReadEepromWord         */
/* Description  : 读取eep对应地址的字，包装ReadEepromWord函数
                  调用：ParamReadEepromAllData函数中
                  输入：
                  输出：   */
/**********************************************************************************************/
USHORT	InitReadEepromWord( USHORT ParamAddr )
{
    return( ReadEepromWord( ParamAddr));
}
  
  
/**********************************************************************************************/
/* Function_Name: KriChkEepromQueue         */
/* Description  : EEPROM的写入队列剩余单元查询
                  调用：各个队列数据写入时，先调用此函数查找队列剩余可写入单元数。
                  输入：队列类型
                  输出：队列空余数量     */
/**********************************************************************************************/
LONG	KriChkEepromQueue( ULONG queid )
{
    LONG	i;
    USHORT	flagx = EepromQueue.ReqFlag & (1 << queid); 
    LONG    Buff1,Buff2;

    /*** 判断是否在合理的队列范围内 ***/
	if( queid >= EEPQUEID_DEF_NUMBER )
	{
		return( 0 );
	}
	switch( queid )
	{
        case EEPQUEID_TIMESTAMP:	// Time Stamp
        case EEPQUEID_ALARMTRACE:	// Alarm Trace Data 
        case EEPQUEID_ALARMMON:		// Latched Mmonitor at Alarm
        case EEPQUEID_ALARMOLINF:	// Alarm OL Info
        case EEPQUEID_OPTID:		// ID of Option Card Connection
             if( flagx == 0x0000 )  
             {
                return( 1 );        // 写入EEP完成，则队列为空，剩余长度为1（总长度也是1）
             }
             break;
             
        case EEPQUEID_WRPRM_SCANC:	
             /*** 这里是一个循环FIFO，FIFO头尾计数周期：2 * SCANCPRMQUEMAX；填入序列1个数据，头+1，
             取出序列（也就是写入EEP）1个数据，尾+1。头减尾delt，就是待写入个数（已缓冲个数） ***/
             Buff1 = (LONG)ScanCPrmQue.AddIdx;
             Buff2 = (LONG)ScanCPrmQue.WrtIdx;
             i = Buff1 - Buff2;
             /*** 若delt为负，delt+2 * SCANCPRMQUEMAX便是待写入个数（已缓冲个数）；头尾的
             计数周期是2 * SCANCPRMQUEMAX ***/
             if( i < 0 )
             {
                i = i + (2 * SCANCPRMQUEMAX);
             }
             /*** 实际的FIFO物理单元长度是SCANCPRMQUEMAX，所以剩余的物理单元个数是SCANCPRMQUEMAX - i；
             若为负，则物理单元已满 ***/
             return( SCANCPRMQUEMAX - i );
        case EEPQUEID_WRPRM_ROUND:
			/*** 类似EEPQUEID_WRPRM_SCANC ***/
            Buff1 = (LONG)RoundPrmQue.AddIdx;
            Buff2 = (LONG)RoundPrmQue.WrtIdx;	// 这里有错误，应该为 RoundPrmQue
            i = Buff1 - Buff2;
            if( i < 0 )
            {
                i = i + (2 * ROUNDPRMQUEMAX);
            }
            return( ROUNDPRMQUEMAX - i );
        default:
            break;
    }
    return( 0 );
}
  
/**********************************************************************************************/
/* Function_Name: LookUpDrvNum         */ 
/* Description  : 根据驱动器编码代码，查找驱动器参数数组index
                  调用：ParamReadEepromAllData函数中
                  输入：驱动器编码代码
                  输出：找到与否，找到情况下输出index结果 	*/
/**********************************************************************************************/
LONG LookUpDrvNum(USHORT DrvNo, USHORT* FindIdx)
{
    USHORT i;
    /*** 根据伺服驱动器编号代码，通过循环方式，索引对应等级的默认驱动器参数数组index：FindIdx ***/
    for(i = 0; i < Driver_Sum; i++)
    {
        if(DriverTabDefIndex[i].SvNo == DrvNo)
        {
            *FindIdx = i;
            return(1);   // 找到对应的驱动器编号，则返回1和index
        }
    }
    return(0); // 没找到则返回0
}
 
/**********************************************************************************************/
/* Function_Name: WriteEepromAllData         */ 
/* Description  : 向eep中写入所有参数
                  调用：ParamReadEepromAllData函数中
                  输入：写入数据数组首地址
                  输出： 	*/
/**********************************************************************************************/
LONG	WriteEepromAllData( USHORT *Buff )
{

//@20260314 syhu 修改初始化参数EEPROM处理，0x720以后的数据(校准数据、故障记录)将不清零，保证校准数据一直存储在EEPROM.
USHORT DataPageNum      = ( EEPADR_RSVD << 1 ) >> 5;
uint16_t PageAddress      = 0;
USHORT i,j;
uint16_t DataBuf[32];
USHORT WriteNum = 0;
    KPX_EepromWP_Enable;
    for( i = 0; i < DataPageNum ; i ++ )
    {
        WriteNum    = i * 16;
        PageAddress = i * 32;
        for( j = 0; j < 16 ; j++ )
        {
            DataBuf[ 2 * j + 0 ]    = ( Buff[ WriteNum + j ] & 0xFF);
            DataBuf[ 2 * j + 1 ]    = ((Buff[ WriteNum + j ] >> 8) & 0xFF);
        }
         WriteEepromOnePage( PageAddress,DataBuf);          
        KlibWaitms( 10 );
    }
    KPX_EepromWP_Disable;
    return( TRUE );
}
 
 
  
  
  
void ReadEepromAllData( USHORT *Buff )
{
USHORT DataPageNum      = ( Param_Sum << 1 ) >> 5;                       
uint16_t PageAddress      = 0;
USHORT i,j;
uint16_t DataBuf[32];
USHORT ReadNum = 0;
    for( i = 0; i < DataPageNum ; i ++ )
    {
        ReadNum    = i * 16;
        PageAddress = i * 32;
         ReadEepromOnePage( PageAddress,DataBuf);
         for( j = 0; j < 16 ; j++ )
        {
            Buff[ ReadNum + j ] = ((DataBuf[ j * 2 + 1 ]) << 8) + (DataBuf[ j * 2]);
        }
 
        KlibWaitms( 1 );
    }
    return;
}
 

 /**********************************************************************************************/
/* Function_Name: ParamReadEepromAllData         */ 
/* Description  : 从EEP中读取全部参数
                  调用：InitParameterFromEeprom函数中
                  输入：
                  输出： 	*/
/**********************************************************************************************/
 
void ParamReadEepromAllData( void )
{
CPRMDEF	*PrmDefPx;
USHORT	*Buff_x = NULL;
USHORT  *Buff_y = NULL;
USHORT	Prm_Version;                                             
USHORT	PrmDrvType_Init;                                         
USHORT	PrmDrvType_Set;                                          
USHORT	LookUpID;
USHORT  DataTmp = 0;
USHORT  ReadNum = 0;
USHORT  i,j;
  
  
      
#if 0
    KlibWaitms(50);                                        
#endif    
     ReadNum = 0;
/*** 驱动器参数更新的机理:  
     1.伺服驱动器的软件版本有更新后,需要重新调用相应的参数表;
     2.伺服驱动器的功率等级代码有更改后,需要重新调用相应的参数表数据。
***/
VersionRd:
    DataTmp = InitReadEepromWord(EEPADR_YFMTID);           // 读取ARM版本
    KlibWaitms(5);
    Prm_Version = InitReadEepromWord(EEPADR_YFMTID); 
    KlibWaitms(5);
    if( Prm_Version != DataTmp )	// 若连续两次读取不相等，持续读取10次。
    {
        ReadNum ++;
        if( ReadNum < 10 )
        {
            goto VersionRd;
        }
    }
    else
    {
        ReadNum ++;
        if( Prm_Version == 0 )   // 若连续两次读取相等，但等于0，则持续读取10次。
        {
            if( ReadNum < 10 )
            {
                goto VersionRd;
            }
        }
    }
     ReadNum = 0;
PowerGrade:
    DataTmp = InitReadEepromWord(EEPADR_TYPEID);         // 初始驱动器型号编码  
    KlibWaitms(5);
    PrmDrvType_Init = InitReadEepromWord(EEPADR_TYPEID); 
    KlibWaitms(5);
    if( PrmDrvType_Init != DataTmp )
    {
        ReadNum ++;
        if( ReadNum < 10 )       // 若连续两次读取不相等，持续读取10次。
        {
            goto PowerGrade;
        }
    }
     ReadNum = 0;
DriveGrade:
    DataTmp = InitReadEepromWord(pndef_drvno.EepromAddr);         // PnE00 : 设置驱动器型号(功率等级)
    KlibWaitms(5);
    PrmDrvType_Set = InitReadEepromWord(pndef_drvno.EepromAddr); 
    KlibWaitms(5);
    if( PrmDrvType_Set != DataTmp )
    {
        ReadNum ++;
        if( ReadNum < 10 )       // 若连续两次读取不相等，持续读取10次。
        {
            goto DriveGrade;
        }
    }
      
      
	/*** 若参数版本和arm版本不相等，则参数指针采用033A功率等级 ***/
    if(ARM_Version != Prm_Version)
    {
        Buff_x = (USHORT*)&DriverTabDef_001E[0];
    }
    /*** 若初始驱动器型号编码和设置驱动器型号不相等，则根据设置驱动器型号索引对应功率的默认参数数组index ***/
    else if(PrmDrvType_Init != PrmDrvType_Set)
    {
		/*** 若没找到index，则参数指针采用011A功率等级 ***/
        if(0 == LookUpDrvNum(PrmDrvType_Set, &LookUpID))
        {    
             Buff_x = (USHORT*)&DriverTabDef_001E[0];
        }
		/*** 若找到对应功率等级index，则参数指针采用对应等级的默认参数 ***/
        else
        {
            Buff_x = (USHORT*)&DriverTabDefIndex[LookUpID].DriverTabDefIndex[0];
        }
    }
     else
    {
    }
      
    StateM_Var.f.EepromError = 0;
	/*** 若读取版本号不一致，或驱动器型号不对等，需要更新，则重新写入eep，并报警 ***/
    if( Buff_x != NULL)
    {
        WriteEepromAllData(Buff_x);			// 向eep中写入所有参数
        KPI_ALARMSET( ALM_EEPROM2 );		// 参数格式化异常: 版本号不匹配
        StateM_Var.f.EepromError = 1;		// EEP错误标志置一
    }
      
	/*** 到此，前期处理结束；读取所有eep数据 ***/
    ReadEepromAllData( Buff_y );
      
	/*** 将读取到的eep信息数据赋值给eep信息结构体变量 ***/
	Eephdr.SysChkSum = Buff_y[ EEPADR_HEADER + 0 ]; // 系统校验和
	Eephdr.UsrChkSum = Buff_y[ EEPADR_HEADER + 1 ]; // 用户校验和
	Eephdr.DefChkSum = Buff_y[ EEPADR_HEADER + 2 ]; // 默认用户校验和
	Eephdr.SvTypeId  = Buff_y[ EEPADR_HEADER + 3 ]; // 驱动器型号编码 
	Eephdr.YecFmtId  = Buff_y[ EEPADR_HEADER + 4 ]; // EEP中存储的ARM版本
	Eephdr.VenderId  = Buff_y[ EEPADR_HEADER + 5 ];	// 暂未使用
	EepInfo = Eephdr;

    /*** 将读取数据赋值给和eep属性封装为一个结构体的对应功能码变量
    对整个功能码表，进行遍历，找出可访问eep的参数，并读取其结果到功能码变量。
    不访问eep的功能码是没有eep地址分配的 ***/
	for(i = 0;i < PNPRMTBL_ENTNUM;i ++)
    {
        PrmDefPx = PnPrmTbl[i].PrmDefPtr;
        if( PrmDefPx->Attr.Place == PRMDEF_RAM_EEPROM )
        {
            j = PrmDefPx->EepromAddr & PRMDEF_EEPADRMSK;
            *PrmDefPx->RamPtr = Buff_y[ j ];
        }
    }
    
#if 1
    Kalm.AlmTrcHdr.w = Buff_y[ EEPADR_ALMTRC ]; // 索引
    /*** 故障记录从Eeprom中读取 ***/
    for( i=0; i < KPX_ALMTBLMAX; i++ )
    {
        /*** 长度31，最开始地址不适用，后面刚好30个。存放10组，每组3个 ***/
        Kalm.AlmTrc[i].OnFlag = 0x00;
        Kalm.AlmTrc[i].AlmDef.AlmAttr  = 0x00;
        Kalm.AlmTrc[i].AlmDef.StopMode = 0x00;
        /*** 故障发生时的故障代码 ***/
        Kalm.AlmTrc[i].AlmDef.AlmCode  = Buff_y[ EEPADR_ALMTRC+(3*i)+1 ];
        /*** 故障发生时的时间 
        TmStamp本身是long型，这里分成了两个USHORT，分别读取合成TmStamp。***/
        ((USHORT*)&Kalm.AlmTrc[i].TmStamp)[0] = Buff_y[ EEPADR_ALMTRC+(3*i)+2 ];
        ((USHORT*)&Kalm.AlmTrc[i].TmStamp)[1] = Buff_y[ EEPADR_ALMTRC+(3*i)+3 ];    
    }
#endif
    for( i = 0 ; i < Param_ALMMON; i++ )
    {
        ((USHORT*)&CoutV.AlmLtMon)[i] = Buff_y[ EEPADR_ALMMON + i ];
    }
	
	/*** SN码获取 ***/
    SnRead();

    /*** 编码器校准数据获取 ***/
    CompensateRead();
	/*** 时间戳的恢复处理
    长度2，最开始地址开始。TmStamp本身是long型，这里分成了两个USHORT，分别读取合成TmStamp ***/
      
      
#if 0
    ((USHORT*)&KnlV.TmStamp)[0] = InitReadEepromWord(EEPADR_TSTAMP + 0);
    ((USHORT*)&KnlV.TmStamp)[1] = InitReadEepromWord(EEPADR_TSTAMP + 1);
#else
    ((USHORT*)&KnlV.TmStamp)[0] = Buff_y[EEPADR_TSTAMP + 0];
    ((USHORT*)&KnlV.TmStamp)[1] = Buff_y[EEPADR_TSTAMP + 1];
#endif
     EepMsg.WrEepTmStamp = KnlV.TmStamp;    
      
 #if 1
	/*** EEP读取结果进行求和校验 ***/
    KpxCheckEepromAllData(Buff_y);
#endif
}
  

/**********************************************************************************************/
/* Function_Name: APL_CheckEepromAllData         */ 
/* Description  : 从EEP中读取的所有数据的合理性检查
                  调用：ParamReadEepromAllData函数中，在读取函数末尾进行读取求和校验检查
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void	KpxCheckEepromAllData( USHORT* bufx )
{
    LONG	i;
    LONG	Pidx;
    USHORT	Sumx;
    CPRMDEF	*pPrmDef;
    
	for( Sumx=0, i=0; i < PNPRMTBL_ENTNUM; i++ )
	{
		pPrmDef = PnPrmTbl[i].PrmDefPtr;
        /*** 读取用户参数：参数段EEP中的访问等级小于系统级的参数(除PE系统参数组外的其他参数组) ***/
		if( (pPrmDef->Attr.Place == PRMDEF_RAM_EEPROM) &&
			(pPrmDef->AccessLevel < ACCLVL_SYSTEM) && (pPrmDef->RamPtr != NULL) )
		{
			Pidx = GET_EEPADR( pPrmDef );
			Sumx += bufx[ Pidx + 0 ];       // 求和
		}
	}
    /*** Sumx自加EEPADR_USRCHK用户求和校验字，若为0，则用户参数校验通过 ***/
	Sumx += bufx[EEPADR_USRCHK];
	if( Sumx != 0 )
	{
		KPI_ALARMSET( ALM_EEPROM1 );        // 非0，报警用户参数和校验异常
	}

    /*** 读取系统参数：（初始段，参数段，空白段）EEP参数，并求和。 ***/
	for( Sumx = 0,i = EEPADR_SUMSTR; i <= EEPADR_SUMEND; i++ )
	{
		Sumx += bufx[i];
	}
	if( Sumx != 0x0000 )
	{
		KPI_ALARMSET( ALM_EEPROM3 );        // 求和不通过，报警系统和校验异常。	
	}
}
  
/**********************************************************************************************/
/* Function_Name: APL_GetEepromSemaphore         */ 
/* Description  : 获取eep信号量
                  调用：根据需要调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
LONG	GetEepromSemaphore( LONG wait )
{
    #if 0
	if( KlibCheckDI() )
	{
		if( EepMsg.EepSemaphore == 0 )			
		{
			EepMsg.EepSemaphore = 1;			
			return( TRUE );						
		}
		else if( wait == NOWAIT )				
		{
			return( FALSE );					
		}
		else									
		{
			return( FALSE );					
		}
	}
    #endif
	{
		if( EepMsg.EepSemaphore == 0 )		// Check EEPROM Semaphore
		{
			EepMsg.EepSemaphore = 1;		// Get EEPROM Semaphore
			return( TRUE );					// Return True
		}
		if( wait == NOWAIT )				// Check WaitFlag	
		{
			return( FALSE );				// Return False	
		}
        return FALSE;                           
	}
}

/**********************************************************************************************/
/* Function_Name: FreeEepromSemaphore         */ 
/* Description  : 释放eep信号量
                  调用：根据需要调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void FreeEepromSemaphore( void )
{
		EepMsg.EepSemaphore = 0;					         
		return;
}
 
  
  
/**********************************************************************************************/
/* Function_Name: APL_InitParameterFromEeprom         */ 
/* Description  : 从eep中初始化整个参数系统
                  调用：初始化调用一次
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void InitParameterFromEeprom( void )
{
	/*** 复位各个EEP写入队列 ***/
    MlibResetLONGMemory( &EepromQueue, sizeof( EepromQueue ) / 2 );
    MlibResetLONGMemory( &ScanCPrmQue, sizeof( ScanCPrmQue ) / 2 );
    MlibResetLONGMemory( &RoundPrmQue, sizeof( RoundPrmQue ) / 2 );
    MlibResetLONGMemory( (void*)&EepMsg, sizeof( EepMsg ) / 2 );
 #if 1
	/*** 初始化时，完成EepromQueue.WrtInfo[EEPQUEID_TIMESTAMP]的赋值，后续不会进行 ***/
    EepromQueue.WrtInfo[EEPQUEID_TIMESTAMP].Type  = EEWTYPE_TSTAMP;
    EepromQueue.WrtInfo[EEPQUEID_TIMESTAMP].Eaddr = EEPADR_TSTAMP;
    EepromQueue.WrtInfo[EEPQUEID_TIMESTAMP].WdNum = 2;
    EepromQueue.WrtInfo[EEPQUEID_TIMESTAMP].WdAdr = (USHORT*)&EepMsg.WrEepTmStamp;    
#endif
     ParamReadEepromAllData();	// 从EEP中读取全部参数
}

/**********************************************************************************************/
/* Function_Name: PanOperReadEepromPrm         */ 
/* Description  : 键盘操作时,功能码的读取处理
                  参数结构体指针读取eep中的数据并返回
                  调用：暂未调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
ULONG PanOperReadEepromPrm( CPRMDEF *prmdef )
{
    USHORT	eepadr;
    USHORT	eepadrx;
    USHORT	rdata[2];
    
	if( prmdef->Attr.Place == PRMDEF_ONLY_RAM )
	{
		return( 0x0000 );                       // 不访问EEP的参数，直接返回
	}
	GetEepromSemaphore( WAIT );	
    /*** 32bit数据读取 ***/
	if( prmdef->Attr.IsLong ) 
	{
		eepadr   = ORG_EEPADR( prmdef );		// 获取参数eep地址
		eepadrx  = LWD_EEPADR( eepadr  );		// 32bit数据EEP的低字地址
		rdata[0] = ReadEepromWord( eepadrx);	// 32bit数据低字数据读取
		eepadrx  = HWD_EEPADR( eepadr );		// 32bit数据EEP的高字地址
		rdata[1] = ReadEepromWord( eepadrx);	// 32bit数据高字数据读取
	}
    /*** 16bit数据读取 ***/
	else
	{
		eepadrx  = GET_EEPADR( prmdef );        // 获取参数eep地址	
		rdata[0] = ReadEepromWord( eepadrx );   // 16bit数据读取
		rdata[1] = 0x0000;
	}
	FreeEepromSemaphore( );
    
	return( *(ULONG*)rdata );                   // 返回读取结果
}

/**********************************************************************************************/
/* Function_Name: LpxAddScanCWritePrmQueue         */ 
/* Description  : 将待写入EEP的数据加入写入序列ScanCPrmQue
                  调用：KriAddEepromQueue函数（写入队列函数）中调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
LONG LpxAddScanCWritePrmQueue( ULONG wdata, PRMDEF *prmdef )
{
    LONG	i;
    PWQENT	PrmAdd;
    LONG    Buff1,Buff2;
    
	if( prmdef->Attr.Place == PRMDEF_ONLY_RAM )
	{
		return( FALSE );
	}
    
    Buff1 = (LONG)ScanCPrmQue.AddIdx;
    Buff2 = (LONG)ScanCPrmQue.WrtIdx;
	i = Buff1 - Buff2;          // 已填入序列的待写入数据个数
	if( i < 0 )
    {
        i = i + (2 * SCANCPRMQUEMAX); // /FIFO的头尾周期是2 * SCANCPRMQUEMAX
    }

    /*** 待写入数据个数大于等于SCANCPRMQUEMAX，说明物理序列已经填满，
    因为实际的物理FIFO长度是SCANCPRMQUEMAX ***/
	if( i >= SCANCPRMQUEMAX )
	{
		return( FALSE );
	}

    /*** PrmAdd是参数加入eep序列的参数属性变量：地址，访问权限，长度，数据 ***/
	PrmAdd.Type  = (prmdef->AccessLevel < ACCLVL_SYSTEM)? EEWTYPE_USRPRM : EEWTYPE_SYSPRM;
	PrmAdd.WdNum = (prmdef->Attr.IsLong == TRUE)? 3 : 2;
	PrmAdd.Eaddr = ORG_EEPADR( prmdef );
	PrmAdd.Wdata = wdata;

    /*** 加入序列，因为头尾长度是实际FIFO长度的两倍，所以这里进行了处理 ***/
	if( ScanCPrmQue.AddIdx < SCANCPRMQUEMAX )
	{
		ScanCPrmQue.PrmEnt[ScanCPrmQue.AddIdx] = PrmAdd;
	}
	else
	{
		ScanCPrmQue.PrmEnt[ScanCPrmQue.AddIdx - SCANCPRMQUEMAX] = PrmAdd;
	}
	if( ScanCPrmQue.AddIdx < (2 * SCANCPRMQUEMAX - 1) )
	{
		ScanCPrmQue.AddIdx++;
	}
	else
	{
		ScanCPrmQue.AddIdx = 0;
	}
	return( TRUE );
}

/**********************************************************************************************/
/* Function_Name: LpxAddRoundWritePrmQueue         */ 
/* Description  : 将待写入EEP的数据加入写入序列RoundPrmQue
                  调用：各队列有数据需要存储EEP时先调用此函数，将数据填入队列
                  输入：
                  输出： 	*/
/**********************************************************************************************/
LONG LpxAddRoundWritePrmQueue( ULONG wdata, PRMDEF *prmdef, ULONG wtype )
{
    LONG	i;
    PWQENT	PrmAdd;
    LONG    Buff1,Buff2;
    
	if( prmdef->Attr.Place == PRMDEF_ONLY_RAM )
	{
		return( FALSE );
	}
    Buff1 = (LONG)RoundPrmQue.AddIdx;
    Buff2 = (LONG)RoundPrmQue.WrtIdx;
	i = Buff1 - Buff2;
	if( i < 0 )
    {
        i = i + ( 2 * ROUNDPRMQUEMAX ); // FIFO的头尾周期是2 * SCANCPRMQUEMAX
    }
    // 队列溢出判断
	if( i >= ROUNDPRMQUEMAX )
	{
		return( FALSE );
	}


	PrmAdd.Type = (prmdef->AccessLevel < ACCLVL_SYSTEM)? EEWTYPE_USRPRM : EEWTYPE_SYSPRM;
	
	PrmAdd.WdNum = (prmdef->Attr.IsLong == TRUE)? 3 : 2;
	PrmAdd.Eaddr = ORG_EEPADR( prmdef );
	PrmAdd.Wdata = wdata;
    /*** 加入序列，因为头尾长度是实际FIFO长度的两倍，所以这里进行了处理 ***/
	if( RoundPrmQue.AddIdx < ROUNDPRMQUEMAX )
	{
		RoundPrmQue.PrmEnt[RoundPrmQue.AddIdx] = PrmAdd;
	}
	else
	{
		RoundPrmQue.PrmEnt[RoundPrmQue.AddIdx - ROUNDPRMQUEMAX] = PrmAdd;
	}
	if( RoundPrmQue.AddIdx < (2*ROUNDPRMQUEMAX - 1) )
	{
		RoundPrmQue.AddIdx++;
	}
	else
	{
		RoundPrmQue.AddIdx = 0;
	}
	return( TRUE );
}

/**********************************************************************************************/
/* Function_Name: KriAddEepromQueue         */ 
/* Description  : 将待写入数据填入各eep队列
                  调用：KriAddEepromQueue函数（写入队列函数）中调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
LONG KriAddEepromQueue( ULONG wdata, void *prmdef, ULONG queid )
{
    USHORT	flagx = ( 1 << queid );

    /*** 序列合法性检查 ***/
	if( queid >= EEPQUEID_DEF_NUMBER )
	{
		return( FALSE );
	}

    /*** Pn参数通过EEPQUEID_WRPRM_SCANC和EEPQUEID_WRPRM_ROUND两个情况下进行写入;
    报警的当前和历史信息，通过EEPQUEID_ALARMOLINF、EEPQUEID_ALARMTRACE、EEPQUEID_ALARMMON，
    进行写入，统一采用EepromQueue.WrtInfo结构体数组进行。***/
    switch( queid )
    {
        /*** EepromQueue.WrtInfo[EEPQUEID_TIMESTAMP]在初始化赋值，后续不会进行赋值 ***/
		case EEPQUEID_TIMESTAMP: // 上电时间	
			 if( (EepromQueue.ReqFlag & flagx) != 0 ) // 仅写一次处理
			 {
			 	return( FALSE );
			 }
			 break;
             
		case EEPQUEID_ALARMOLINF:// 故障状态	
			 if( (EepromQueue.ReqFlag & flagx) != 0 ) // 仅写一次处理
			 {
			 	return( FALSE );
			 }
			 EepromQueue.WrtInfo[queid].Type  = EEWTYPE_ALMTOL;
			 EepromQueue.WrtInfo[queid].Eaddr = EEPADR_ALMOLI;
			 EepromQueue.WrtInfo[queid].WdNum = 1;
			 EepromQueue.WrtInfo[queid].WdAdr = prmdef;
			 break;
		case EEPQUEID_ALARMTRACE:// 警报历史记录 Un820~42
			 if( (EepromQueue.ReqFlag & flagx) != 0 ) // 仅写一次处理
			 {
			 	return( FALSE );
			 }
			 EepromQueue.WrtInfo[queid].Type  = EEWTYPE_ALMTRC;
			 EepromQueue.WrtInfo[queid].Eaddr = (USHORT)(EEPADR_ALMTRC + 1 + (3*wdata) + 2);
			 EepromQueue.WrtInfo[queid].WdNum = 4;
			 EepromQueue.WrtInfo[queid].WdAdr = prmdef;
			 break;
		case EEPQUEID_WRPRM_SCANC:// Pn参数Scanc写入	
			 if( LpxAddScanCWritePrmQueue( wdata, prmdef ) != TRUE )
			 {
				return( FALSE );
			 }
			 break;
		case EEPQUEID_WRPRM_ROUND:// Pn参数Round写入	
			 if( LpxAddRoundWritePrmQueue( wdata, prmdef, EEWTYPE_DEFAULT ) != TRUE )
			 {
				return( FALSE );
			 }
			 break;
		case EEPQUEID_ALARMMON:	  // 当前警报记录 Un800~18
			 if( (EepromQueue.ReqFlag & flagx) != 0 ) // 仅写一次处理
			 {
			 	return( FALSE );
			 }
			 EepromQueue.WrtInfo[queid].Type = EEWTYPE_ALMMON;
			 EepromQueue.WrtInfo[queid].Eaddr = EEPADR_ALMMON;
			 EepromQueue.WrtInfo[queid].WdNum = wdata;
			 EepromQueue.WrtInfo[queid].WdAdr = prmdef;
			 break;
		default:
			 return( FALSE );
	}
    
	EepromQueue.ReqFlag |= flagx; // 仅写一次处理；同时对应序列标志置一。
	return( TRUE );
}

/**********************************************************************************************/
/* Function_Name: LpxGetScanCWritePrmQueue         */ 
/* Description  : 按照FIFO原则，获取ScanCPrmQue写入缓存序列中的一个写入数据结构体，赋值给
                  eep直接写入结构体EepromQueue
                  调用：KpxScanWriteEepromQueue 中调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
LONG LpxGetScanCWritePrmQueue( void )
{
    PWQENT	*Getpx;
    ULONG	i = ScanCPrmQue.WrtIdx;

    /*** 若头尾两者相等，说明待写入缓存已经写入完成，返回 ***/
	if( ScanCPrmQue.AddIdx == i )
	{
		return( FALSE );
	}
    
    /*** 获取写入数据的结构体指针 ***/
	if( i < SCANCPRMQUEMAX )
	{
		Getpx = &ScanCPrmQue.PrmEnt[i];
	}
	else
	{
		Getpx = &ScanCPrmQue.PrmEnt[i-SCANCPRMQUEMAX];
	}

    /*** 将获取的结构体数据，赋值到EepromQueue结构体 ***/
	EepromQueue.Type  = Getpx->Type;
	EepromQueue.WdNum = Getpx->WdNum;
	EepromQueue.Eaddr = Getpx->Eaddr;
	EepromQueue.Wdata.dw = Getpx->Wdata;

    /*** ScanCPrmQue的写入尾加1 ***/
	if( ++i >= (2*SCANCPRMQUEMAX) )
	{
		ScanCPrmQue.WrtIdx = 0;
	}
	else
	{
		ScanCPrmQue.WrtIdx = (USHORT)i;
	}
	return( TRUE );
}

#define		EEPI2C_RD_SEND_ADDR			0
#define		EEPI2C_RD_SEND_READ_CMD		1
#define		EEPI2C_RD_STOP				2



/**********************************************************************************************/
/* Function_Name: ReadScanEepromI2CWord         */ 
/* Description  : EEPROM中读取数据字（随机读取）
                  将eep的word读取过程分为三个阶段执行，这和eep文件中的合在一起的读取过程完全一致;
                  这样做的好处是：分为三个阶段，各阶段之间可以执行其他任务，以便降低主循环堵塞时间
                  调用：KpxScanWriteEepromQueue 中调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
LONG ReadScanEepromI2CWord( ULONG eaddr, LONG Start )
{
    LONG rc = FALSE;
    ULONG Eaddr = eaddr<<1; // word地址，而eep地址是字节编址的，所以乘2
    
	if( Start == EEPI2C_START )
	{
		EepMsg.I2CReadStep = EEPI2C_RD_SEND_ADDR; // 若为开始阶段，则发送地址开始。
	}
 	switch( EepMsg.I2CReadStep)
	{
         case EEPI2C_RD_SEND_ADDR:    // 读取过程功能码地址发送。
            if( ReadEepromOneWord( Eaddr ) == 0 )
            {
                EepMsg.I2CReadStep = EEPI2C_RD_STOP;
            }
            else
            {
                EepMsg.I2CReadStep = EEPI2C_RD_SEND_ADDR;
            }
            break;
         case EEPI2C_RD_SEND_READ_CMD:    
			// 地址发送完成后，读取对应地址数据。
            EepMsg.I2CReadStep = EEPI2C_RD_STOP;
            break;
         case EEPI2C_RD_STOP:
            EepMsg.I2CData = EepromReadValue( );	// 获取读取结果
            EepMsg.I2CReadStep = EEPI2C_RD_SEND_ADDR;	// 回到读取过程地址发送阶段
            rc = TRUE;
            break;
         default:
            EepMsg.I2CReadStep = EEPI2C_RD_SEND_ADDR;
            break;
 	}
	return( rc);
}
  
  
/**********************************************************************************************/
/* Function_Name: APL_GetRoundWritePrmQueue         */ 
/* Description  : 按照FIFO原则，获取RoundPrmQue写入缓存序列中的一个写入数据结构体，赋值给
                  eep直接写入结构体EepromQueue
                  调用：KpxScanWriteEepromQueue 中调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
 LONG	LpxGetRoundWritePrmQueue( void )
{
    PWQENT	*Getpx;
    ULONG	i = RoundPrmQue.WrtIdx;

    /*** 若头尾两者相等，说明待写入缓存已经写入完成，返回 ***/
	if( RoundPrmQue.AddIdx == i )
	{
		return( FALSE );
	}
    
    /*** 获取写入数据的结构体指针 ***/
	if( i < ROUNDPRMQUEMAX )
	{
		Getpx = &RoundPrmQue.PrmEnt[i];
	}
	else
	{
		Getpx = &RoundPrmQue.PrmEnt[i-ROUNDPRMQUEMAX];
	}
    
    /*** 将获取的结构体数据，赋值到EepromQueue结构体 ***/
	EepromQueue.Type  = Getpx->Type;
	EepromQueue.WdNum = Getpx->WdNum;
	EepromQueue.Eaddr = Getpx->Eaddr;
	EepromQueue.Wdata.dw = Getpx->Wdata;
    
    /*** RoundPrmQue的写入尾加1 ***/
	if( ++i >= (2*ROUNDPRMQUEMAX) )
	{
		RoundPrmQue.WrtIdx = 0;
	}
	else
	{
		RoundPrmQue.WrtIdx = (USHORT)i;
	}
	return( TRUE );
}

#define		EEPI2C_WR_SEND_ADDR			0
#define		EEPI2C_WR_SEND_WORDL		1
#define		EEPI2C_WR_SEND_WORDH		2
#define		EEPI2C_WR_STOP				3

/**********************************************************************************************/
/* Function_Name: WriteScanEepromI2CWord         */ 
/* Description  : EEPROM中写入数据字（随机写入）
                  eep的word写入过程分为三个阶段执行，这和eep文件中的合在一起的写入过程完全一致;
                  这样做的好处是：分为三个阶段，各阶段之间可以执行其他任务，以便降低主循环堵塞时间
                  调用：KpxScanWriteEepromQueue 中调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
LONG WriteScanEepromI2CWord( ULONG eaddr, USHORT wdata, LONG Start )
{
LONG	rc = FALSE;
ULONG	Eaddr = eaddr << 1;		// word地址，而eep地址是字节编址的，所以乘2
 	if( Start == EEPI2C_START )
	{
		EepMsg.I2CWriteStep = EEPI2C_WR_SEND_ADDR;	// 若为开始阶段，则发送地址开始。
	}
 	switch( EepMsg.I2CWriteStep)
	{
         case EEPI2C_WR_SEND_ADDR:    
                EepMsg.I2CWriteStep = EEPI2C_WR_SEND_WORDL;	// 写入过程功能码地址发送。
            break;
         case EEPI2C_WR_SEND_WORDL:
                WriteEepromOneWord( Eaddr, wdata );			// 写入数据
                EepMsg.I2CWriteStep = EEPI2C_WR_SEND_WORDH;
            break;
        case EEPI2C_WR_SEND_WORDH:
                EepMsg.I2CWriteStep = EEPI2C_WR_STOP;
            break;  
         case EEPI2C_WR_STOP:
				// 向Eeprom写入停止位字节
                EepMsg.I2CWriteStep = EEPI2C_WR_SEND_ADDR;
                rc = TRUE;
            break;
         default:
            EepMsg.I2CWriteStep = EEPI2C_WR_SEND_ADDR;
		break;
 	}
	return(rc);
}

/**********************************************************************************************/
/* Function_Name: WriteEepromWord         */ 
/* Description  : 使用合在一起的方法写入数据到eep目标地址
                  调用：需要时调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void WriteEepromWord( ULONG eaddr, USHORT wdata, LONG wait )
{
	ULONG	Eaddr = eaddr<<1;		// word地址，而eep地址是字节编址的，所以乘2
     KPX_EepromWP_Enable;
     KlibWaitms( 1 );                                           
     while(WriteEepromOneWord(Eaddr,wdata));    	// 向Eeprom写入一个字(用于初始化过程,速度较慢)  
     KlibWaitms( 8 );
     KPX_EepromWP_Disable;
 	 return;
}
 
/**********************************************************************************************/
/* Function_Name: KriWriteEepromWord         */ 
/* Description  : 使用合在一起的方法写入数据到eep目标地址
                  调用：暂无调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
LONG	KriWriteEepromWord( USHORT eeadr, USHORT wdata )
{
	WriteEepromEnable( );
	WriteEepromWord( eeadr, wdata, WAIT ); // 使用合在一起的方法写入数据到eep目标地址
	WriteEepromDisable( );
	return( TRUE );
}

/**********************************************************************************************/
/* Function_Name: LpxReadEepromData         */ 
/* Description  : 使用合在一起的方法从eep目标地址读取多个连续地址数据
                  调用：需要时调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void LpxReadEepromData( USHORT EepAdr, USHORT* RdBufx, LONG RdNumx )
{
    LONG i;
    
	GetEepromSemaphore( WAIT );								
	for( i = 0; i < RdNumx; i++ )
	{
		RdBufx[i] = ReadEepromWord( (EepAdr+i) ); // 读取eep对应地址的字		
	}
	FreeEepromSemaphore( );									
	return;
}

/**********************************************************************************************/
/* Function_Name: LpxWriteEepromData         */ 
/* Description  : 使用合在一起的方法向eep目标地址写入多个连续地址数据
                  调用：暂未调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void LpxWriteEepromData( USHORT EepAdr, USHORT* WrBufx, LONG WrNumx )
{
    LONG i;
    
	GetEepromSemaphore( WAIT );								
	WriteEepromEnable( );									
	for( i = 0; i < WrNumx; i++ )
	{
		WriteEepromWord( (EepAdr+i), WrBufx[i], WAIT );	// 使用合在一起的方法写入数据到eep目标地址	
	}
	WriteEepromDisable( );									
	FreeEepromSemaphore( );									
	return;
}

/**********************************************************************************************/
/* Function_Name: KriReadEepromEngInfo         */ 
/* Description  : 从eeprom读工程参数
                  调用：需要时调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
LONG KriReadEepromEngInfo( LONG StrNo, LONG Number, USHORT *ReadBuf, LONG *ErrNum )
{
	return( TRUE );
}

/**********************************************************************************************/
/* Function_Name: KriWriteEepromEngInfo         */ 
/* Description  : 工程参数写入eeprom
                  调用：需要时调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
LONG KriWriteEepromEngInfo( LONG StrNo, LONG Number, USHORT *WriteBuf, LONG *ErrNum )
{
    return TRUE;
}

/**********************************************************************************************/
/* Function_Name: TmStampSaveEn         */ 
/* Description  : 设置时间戳保存标志位
                  调用：需要时调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void TmStampSaveEn( void )
{
    EepMsg.WrEepTmStampReq = TRUE;               
}

/**********************************************************************************************/
/* Function_Name: KpxScanWriteEepromQueue         */ 
/* Description  : 扫描所需要写的eeprom队列，并写入至eep中。
                  调用：主循环2ms任务中调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void KpxScanWriteEepromQueue( void )
{
    USHORT	uswk = 0;
    USHORT	EepAdrX = 0;
    UCHAR   DataTmp = 0;
    USHORT  DataTmp16 = 0;

    /*** 主回路断电时,控制回路也断电,在此情况下,EEprom的操作需要进行短暂等待延时处理 ***/
	if( CoutK.f.PowerOnEep == TRUE )	// Check Power ON					
	{
		EepMsg.PowerOffTime = 0;		// Clear PowerOffTime					
		EepMsg.WrEepStartOk = TRUE;		// EEPROM存储可以进行					
	}
	else if( EepMsg.PowerOffTime < KPI_SCANC_MS( 10 ) ) // PowerOffTime < 10ms以内	
	{
		EepMsg.PowerOffTime++;								
		EepMsg.WrEepStartOk = TRUE;						// EEPROM存储可以进行
		if( KnlV.TmStamp != EepMsg.WrEepTmStamp )		// 检查填写时间戳
		{
			EepMsg.WrEepTmStamp = KnlV.TmStamp;         // 写入数据设定
			KriAddEepromQueue( 0,NULL,EEPQUEID_TIMESTAMP ); // 时间戳写入EEPROM队列请求	
		}
	}
	else if( EepMsg.PowerOffTime < KPI_SCANC_MS( 200 ) )// 10ms <= PowerOffTime < 200ms	
	{
		EepMsg.PowerOffTime++;
		EepMsg.WrEepStartOk = FALSE;                    // EEPROM存储禁止
	}
	else                                                // 200ms < PowerOffTime	
	{
		EepMsg.WrEepStartOk = TRUE;                     // 主回路断电时可以进行Eeprom操作
    }

    /*** 其它特定请求时,将时间戳写入到Eeprom中 ***/
	if(EepMsg.WrEepTmStampReq == TRUE)	// 产生软件复位时,发送时间戳写入请求
	{
		EepMsg.WrEepStartOk = TRUE;			            // EEPROM存储可以进行				
		if( KnlV.TmStamp != EepMsg.WrEepTmStamp )		// 检查填写时间戳	
		{
			EepMsg.WrEepTmStamp = KnlV.TmStamp;			// 写入数据设定	
			KriAddEepromQueue( 0,NULL,EEPQUEID_TIMESTAMP );	// 时间戳写入EEPROM队列请求	
		}
		EepMsg.WrEepTmStampReq = FALSE ;                // 复位请求标志					
	}

    /*** EEPROM Write Sequence ***/
	switch( EepMsg.WrEepQueStep )
	{
        case STEP_START: // 步骤0：写请求检查，并开始写作
            if( EepMsg.WrEepStartOk != TRUE )   // 数据写入是否允许：不允许，退出。
                { break;}
            if( EepromQueue.ReqFlag == 0x0000 ) // 检查写入请求：无请求，退出。
                { break;}
            if( GetEepromSemaphore( NOWAIT ) != TRUE ) // 获取写入开始信号：未获取，退出 
                { break;}
            
            EepMsg.WrEepQueWait = 0;
            /*** 找出EepromQueue.ReqFlag的从lsb向上的第一个非0bit位置 ***/
            EepMsg.QueId = (UCHAR)MlibSrhbiton( EepromQueue.ReqFlag, SRH_FROM_LSB );

            /*** 判断哪个队列产生相应的写入Eeprom 请求 ***/
            switch( EepMsg.QueId )
            {
                case EEPQUEID_TIMESTAMP:	// Time Stamp                      
                    EepromQueue.Type  = EepromQueue.WrtInfo[EepMsg.QueId].Type;
                    EepromQueue.WdNum = EepromQueue.WrtInfo[EepMsg.QueId].WdNum;
                    EepromQueue.WdCnt = 0;
                    EepromQueue.Eaddr = EepromQueue.WrtInfo[EepMsg.QueId].Eaddr;
                    EepromQueue.Wdata.Ushort[0] = EepromQueue.WrtInfo[EepMsg.QueId].WdAdr[0];

                    WriteEepromEnable( ); // 写入EEP使能
                    /*** 写入第一阶段，发送数据0，状态EEPI2C_START，完成地址发送 ***/
                    WriteScanEepromI2CWord( EepromQueue.Eaddr, 0, EEPI2C_START );
                    
                    EepMsg.WrEepQueStep = STEP_GNLWR01;
                break;
                
                case EEPQUEID_ALARMOLINF:   // Alarm OL Info                    
                    EepromQueue.Type  = EepromQueue.WrtInfo[EepMsg.QueId].Type;
                    EepromQueue.WdNum = EepromQueue.WrtInfo[EepMsg.QueId].WdNum;
                    EepromQueue.WdCnt = 0;
                    EepromQueue.Eaddr = EepromQueue.WrtInfo[EepMsg.QueId].Eaddr;
                    EepromQueue.Wdata.Ushort[0] = EepromQueue.WrtInfo[EepMsg.QueId].WdAdr[0];
                    
                    WriteEepromEnable( ); // 写入EEP使能			
                    /*** 写入第一阶段，发送数据0，状态EEPI2C_START，完成地址发送 ***/
                    WriteScanEepromI2CWord( EepromQueue.Eaddr, 0, EEPI2C_START );
                    EepMsg.WrEepQueStep = STEP_AOLWR01;			
                break;
                
                case EEPQUEID_ALARMTRACE:	// Alarm Trace Data                   
                    EepromQueue.Type  = EepromQueue.WrtInfo[EepMsg.QueId].Type;
                    EepromQueue.WdNum = EepromQueue.WrtInfo[EepMsg.QueId].WdNum;
                    EepromQueue.WdCnt = EepromQueue.WdNum - 1;
                    EepromQueue.Eaddr = EepromQueue.WrtInfo[EepMsg.QueId].Eaddr;
                    EepromQueue.Wdata.Ushort[0] = EepromQueue.WrtInfo[EepMsg.QueId].WdAdr[EepromQueue.WdCnt];
                    
                    WriteEepromEnable( ); // 写入EEP使能
                    /*** 写入第一阶段，发送数据0，状态EEPI2C_START，完成地址发送 ***/
                    WriteScanEepromI2CWord( EepromQueue.Eaddr, 0, EEPI2C_START );
                    EepMsg.WrEepQueStep = STEP_ALMWR01;			
                break;      
                
                case EEPQUEID_WRPRM_SCANC:  // ScanC Write Parameter                    
                    if( LpxGetScanCWritePrmQueue( ) == TRUE )	// 检查写入队列是否写入完成
                    {
                        EepromQueue.WdCnt = 0;
                        /*** 读取第一阶段，状态EEPI2C_START，完成地址发送；参数是先读、判断、再写 ***/
                        ReadScanEepromI2CWord( EepromQueue.Eaddr, EEPI2C_START );
                        EepMsg.WrEepQueStep = STEP_PRMRD01;
                    }
                    else // 队列写入完成，无需写入，释放写入信号，并复位写入请求。
                    {
                        FreeEepromSemaphore( );		            // Free EEPROM Semaphore
                        DataTmp = EepMsg.QueId;
                        EepromQueue.ReqFlag &= ~(1 << DataTmp); // Reset Request Flag 
                    }
                break;
                    
                case EEPQUEID_WRPRM_ROUND:  // Round Write Parameter
                    if( LpxGetRoundWritePrmQueue( ) == TRUE )   // 检查写入队列是否写入完成
                    {
                            EepromQueue.WdCnt = 0;
                            /*** 读取第一阶段，状态EEPI2C_START，完成地址发送；参数是先读、判断、再写 ***/
                            ReadScanEepromI2CWord( EepromQueue.Eaddr, EEPI2C_START );
                            EepMsg.WrEepQueStep = STEP_PRMRD01;
                    }
                    else // 队列写入完成，无需写入，释放写入信号，并复位写入请求。
                    {
                         FreeEepromSemaphore( );
                         DataTmp = ~(1<<EepMsg.QueId);
                         EepromQueue.ReqFlag &= DataTmp;                    
                    }
                break;
                    
                case EEPQUEID_ALARMMON:     // 故障监控
                      EepromQueue.Type  = EepromQueue.WrtInfo[EepMsg.QueId].Type;
                      EepromQueue.WdNum = EepromQueue.WrtInfo[EepMsg.QueId].WdNum;
                      EepromQueue.WdCnt = 0;
                      EepromQueue.Eaddr = EepromQueue.WrtInfo[EepMsg.QueId].Eaddr;
                      EepromQueue.Wdata.Ushort[0] = EepromQueue.WrtInfo[EepMsg.QueId].WdAdr[0];

                      WriteEepromEnable( ); // 写入EEP使能
                      /*** 写入第一阶段，发送数据0，状态EEPI2C_START，完成地址发送 ***/
                      WriteScanEepromI2CWord( EepromQueue.Eaddr, 0, EEPI2C_START );
                      EepMsg.WrEepQueStep = STEP_ALMON01;
                      break;               
                default:                    // 非法序列：释放写入信号，并复位写入请求。
                    FreeEepromSemaphore( );							
                    DataTmp = ~(1<<EepMsg.QueId);
                    EepromQueue.ReqFlag &= DataTmp;		             
                    break;
            }
            break;
            
	case STEP_GNLWR01: // Time Stamp  
         /*** 写入数据和EEPI2C_CONTINUE ***/
		 if( WriteScanEepromI2CWord(EepromQueue.Eaddr, EepromQueue.Wdata.Ushort[0], EEPI2C_CONTINUE) == TRUE )
		 {
			 EepMsg.WrEepQueWait = 0;
			 EepMsg.WrEepQueStep = STEP_GNLWR02;
		 }
		 break;
         
	case STEP_GNLWR02: // Time Stamp  
	     /*** 等待eep内部写入完成，手册推荐最大5ms，这里10-4 = 6ms ***/
		 if( EepMsg.WrEepQueWait++ >= EEP_WAIT_MS(EEP_TWR, 2 )) 
		 {
			EepMsg.WrEepQueWait = 0;
			EepMsg.WrEepQueStep = STEP_GNLWR03;
		 }
		 break;
         
	case STEP_GNLWR03: // Time Stamp  
	    /*** WdNum总的写入字数，WdCnt实际写入字数；这里完成持续写入 ***/
		if( ++EepromQueue.WdCnt >= EepromQueue.WdNum )			
		{
			EepMsg.WrEepQueStep = STEP_WRITEND;	 // 总字数写入完成，跳到：写入结束状态STEP_WRITEND				
		}
		else    // 总字数未写入完成，准备下个写入字的地址和内容，并发送地址
		{
			EepMsg.WrEepQueStep = STEP_GNLWR01;					
			++EepromQueue.Eaddr; // 连续字地址，地址加1	
			/*** 得到下个地址的字内容 ***/
			EepromQueue.Wdata.Ushort[0] = EepromQueue.WrtInfo[EepMsg.QueId].WdAdr[EepromQueue.WdCnt];
			/*** 写入第一阶段，发送数据0，状态EEPI2C_START，完成地址发送 ***/
			WriteScanEepromI2CWord( EepromQueue.Eaddr, 0, EEPI2C_START );		
		}
		break;
        
	case STEP_AOLWR01: // Alarm OL Info 
	     /*** 写入数据和EEPI2C_CONTINUE ***/
		 if( WriteScanEepromI2CWord(EepromQueue.Eaddr, EepromQueue.Wdata.Ushort[0], EEPI2C_CONTINUE) == TRUE )
		 {
			 EepMsg.WrEepQueWait = 0;
			 EepMsg.WrEepQueStep = STEP_AOLWR02;
		 }
		 break;
         
	case STEP_AOLWR02: // Alarm OL Info 
	     /*** 等待eep内部写入完成，手册推荐最大5ms，这里10-4 = 6ms ***/
		 if( EepMsg.WrEepQueWait++ >= EEP_WAIT_MS(EEP_TWR, 2 ))	
		 {														
			EepMsg.WrEepQueWait = 0;    						
			EepMsg.WrEepQueStep = STEP_WRITEND;	// EEPQUEID_ALARMOLINF仅仅需要写入1个字。所以这里直接结束					
		 }														
		 break; 
         
	case STEP_ALMWR01: // Alarm Trace Data
	     /*** 写入数据和EEPI2C_CONTINUE ***/
		 if( WriteScanEepromI2CWord(EepromQueue.Eaddr, EepromQueue.Wdata.Ushort[0], EEPI2C_CONTINUE) == TRUE )
		 {
			 EepMsg.WrEepQueWait = 0;
			 EepMsg.WrEepQueStep = STEP_ALMWR02;
		 }
		 break;
         
	case STEP_ALMWR02: // Alarm Trace Data
	     /*** 等待eep内部写入完成，手册推荐最大5ms，这里10-4 = 6ms ***/
		 if( EepMsg.WrEepQueWait++ >= EEP_WAIT_MS(EEP_TWR, 2 ))	
		 {														
			EepMsg.WrEepQueWait = 0;							
			EepMsg.WrEepQueStep = STEP_ALMWR03;					
		 }														
		 break;
         
	case STEP_ALMWR03: // Alarm Trace Data
	    /*** Alarm Trace Data下：WdCnt = EepromQueue.WdNum - 1;，WdCnt是从最大写入个数往下递减的 ***/
		if( --EepromQueue.WdCnt < 0 )							
		{
			EepMsg.WrEepQueStep = STEP_WRITEND; // 总字数写入完成，跳到：写入结束状态STEP_WRITEND					
		}
		else // 总字数未写入完成，准备下个写入字的地址和内容，并发送地址
		{
			EepMsg.WrEepQueStep = STEP_ALMWR01;
            /*** 这里地址是递减写入的，WdCnt为0是常规记录之外，地址为EEPADR_ALMTRC ***/
            DataTmp16 = (EepromQueue.WdCnt == 0) ? EEPADR_ALMTRC : (--EepromQueue.Eaddr);
			EepromQueue.Eaddr = DataTmp16;
            /*** 得到下个地址的字内容 ***/
			EepromQueue.Wdata.Ushort[0] = EepromQueue.WrtInfo[EepMsg.QueId].WdAdr[EepromQueue.WdCnt];
            /*** 写入第一阶段，发送数据0，状态EEPI2C_START，完成地址发送 ***/
			WriteScanEepromI2CWord( EepromQueue.Eaddr, 0, EEPI2C_START );
		}
		break;
        
    case STEP_PCOPY01: // Round Write Parameter
        /*** 本次是读取数据阶段,读取状态为EEPI2C_CONTINUE。第一阶段，已经完成地址发送 ***/
        if( ReadScanEepromI2CWord(EepromQueue.Eaddr, EEPI2C_CONTINUE) == TRUE )
        {
            /*** 判断写入数据和读取数据是否相等。相等则不用写入，否则写入 ***/
            uswk = EepMsg.I2CData;								
            if( uswk != EepromQueue.Wdata.Ushort[0] )			
            {
                WriteEepromEnable( );	// 写使能
                /*** 写入第一阶段，发送数据0，状态EEPI2C_START，完成地址发送 ***/
                WriteScanEepromI2CWord( EepromQueue.Eaddr, 0, EEPI2C_START );
                EepMsg.WrEepQueStep = STEP_PCOPY02;				
            }
            else
            {
                EepMsg.WrEepQueStep = STEP_WRITEND;	// 无需写入，跳到：写入结束状态STEP_WRITEND			
            }
        }
        break;
    case STEP_PCOPY02: // Round Write Parameter
        /*** 写入数据和EEPI2C_CONTINUE ***/
        if( WriteScanEepromI2CWord(EepromQueue.Eaddr, EepromQueue.Wdata.Ushort[0], EEPI2C_CONTINUE) == TRUE )
        {
            EepMsg.WrEepQueWait = 0;
            EepMsg.WrEepQueStep = STEP_PCOPY03;
        }
        break;
        
    case STEP_PCOPY03: // Round Write Parameter
        /*** 等待eep内部写入完成，手册推荐最大5ms，这里10-4 = 6ms ***/
        if( EepMsg.WrEepQueWait++ >= EEP_WAIT_MS(EEP_TWR, 2 ))	
        {														
            EepMsg.WrEepQueWait = 0;							
            EepMsg.WrEepQueStep = STEP_WRITEND;	 // 这里仅需写入一个字，写入1个字。所以这里直接结束				
        }
        break;
        
    case STEP_ALMON01: // 故障监控
        /*** 写入数据和EEPI2C_CONTINUE ***/
        if( WriteScanEepromI2CWord(EepromQueue.Eaddr, EepromQueue.Wdata.Ushort[0],EEPI2C_CONTINUE) == TRUE )
        {
          EepMsg.WrEepQueWait = 0;
          EepMsg.WrEepQueStep = STEP_ALMON02;
        }
        break;
    case STEP_ALMON02: // 故障监控
        /*** 等待eep内部写入完成，手册推荐最大5ms，这里10-4 = 6ms ***/
        if( EepMsg.WrEepQueWait++ >= EEP_WAIT_MS(EEP_TWR, 2) )
        {
          EepMsg.WrEepQueWait = 0;
          EepMsg.WrEepQueStep = STEP_ALMON03;
        }
        break;
    case STEP_ALMON03: // 故障监控
        /*** WdNum总的写入字数，WdCnt实际写入字数；这里完成持续写入 ***/
        if( ++EepromQueue.WdCnt >= EepromQueue.WdNum )
        {
          EepMsg.WrEepQueStep = STEP_WRITEND;   // 总字数写入完成，跳到：写入结束状态STEP_WRITEND
        }
        else    // 总字数未写入完成，准备下个写入字的地址和内容，并发送地址
        {
          EepMsg.WrEepQueStep = STEP_ALMON01;
          ++EepromQueue.Eaddr; // 连续字地址，地址加1	
          /*** 得到下个地址的字内容 ***/
          EepromQueue.Wdata.Ushort[0] = EepromQueue.WrtInfo[EepMsg.QueId].WdAdr[EepromQueue.WdCnt];
          /*** 写入第一阶段，发送数据0，状态EEPI2C_START，完成地址发送 ***/
          WriteScanEepromI2CWord( EepromQueue.Eaddr, 0, EEPI2C_START );
        }
        break;  
        
    case STEP_PRMRD01: // Round Write Parameter
		
        /*** 本次是读取数据阶段,读取状态为EEPI2C_CONTINUE。第一阶段，已经完成地址发送 ***/
        /*** 这里的EepAdrX地址是0，但是上一阶段已经发送了地址，这里仅读取数据，所以地址无关 ***/
        EepAdrX = LWD_EEPADR( EepromQueue.Eaddr );
		if( ReadScanEepromI2CWord( EepAdrX, EEPI2C_CONTINUE ) == TRUE ) 
        {
            EepromQueue.ChkSumx[0] =  EepMsg.I2CData;			    
            EepromQueue.ChkSumx[0] -= EepromQueue.Wdata.Ushort[0];
            /*** 写入字时WdNum为2，双字WdNum为3 ***/
            if( EepromQueue.WdNum <= 2 )
            {
                /*** 判断写入数据和读取数据是否相等。相等则不用写入，否则写入 ***/
                if( EepromQueue.ChkSumx[0] == 0 )				    
                    EepMsg.WrEepQueStep = STEP_WRITEND;	// 无需写入，跳到：写入结束状态STEP_WRITEND		    
                else
                {
                    WriteEepromEnable( ); // 写使能		
                    /*** 写入第一阶段，发送数据0，状态EEPI2C_START，完成地址发送 ***/
                    WriteScanEepromI2CWord( EepromQueue.Eaddr, 0, EEPI2C_START );
                    EepMsg.WrEepQueStep = STEP_PRMWR01;	// 跳入到单个字写入-STEP_PRMWR01	    
                }
            } 
            else // 双字写入												    
            {
                EepAdrX = HWD_EEPADR( EepromQueue.Eaddr );	   // 得到高字地址
                /*** 读取双字的高字第一阶段，状态EEPI2C_START，完成地址发送；参数是先读、判断、再写 ***/
                ReadScanEepromI2CWord( EepAdrX, EEPI2C_START );	    
                EepMsg.WrEepQueStep = STEP_PRMRD02;	    // 跳入到高字数据读取阶段-STEP_PRMRD02				    
            }
        }
        break;
        
	case STEP_PRMRD02: // Round Write Parameter
	    /*** 本次是读取双字高字数据阶段,读取状态为EEPI2C_CONTINUE。第一阶段，已经完成地址发送 ***/
		EepAdrX = HWD_EEPADR( EepromQueue.Eaddr );  
		if( ReadScanEepromI2CWord( EepAdrX, EEPI2C_CONTINUE ) == TRUE )
		{
			 EepromQueue.ChkSumx[1] =  EepMsg.I2CData;
			 EepromQueue.ChkSumx[1] -= EepromQueue.Wdata.Ushort[1];
             /*** 判断双字低字写入数据和读取数据是否相等。相等则不用写入，否则写入 ***/
			 if( EepromQueue.ChkSumx[0] != 0 )
			 {
				WriteEepromEnable( ); // 写使能	
				/*** 写入第一阶段，发送数据0，状态EEPI2C_START，完成地址发送 ***/
				WriteScanEepromI2CWord( EepromQueue.Eaddr, 0, EEPI2C_START );
				EepMsg.WrEepQueStep = STEP_PRMWR01;   // 跳入到单个字写入-STEP_PRMWR01	
			 }
			 else // 双字低字写入数据和读取数据相等
			 {
			    /*** 判断双字高字写入数据和读取数据是否相等。相等则不用写入，否则写入 ***/
				if( EepromQueue.ChkSumx[1] == 0 )
				{
					EepMsg.WrEepQueStep = STEP_WRITEND;// 高字相等，且低字相等，直接结束写入
				}
				else // 高字不相等，写入高字
				{
					WriteEepromEnable( ); // 写使能
					EepAdrX = HWD_EEPADR( EepromQueue.Eaddr ); // 取高字地址
					/*** 写入第一阶段，发送数据0，状态EEPI2C_START，完成地址发送 ***/
					WriteScanEepromI2CWord( EepAdrX, 0, EEPI2C_START );
					EepMsg.WrEepQueStep = STEP_PRMWR11;
				}
			 }
		}
		break;            
    case STEP_PRMWR01: // Round Write Parameter
        EepAdrX = LWD_EEPADR( EepromQueue.Eaddr ); // 获取低字地址	
        /*** 本次是读取数据阶段,读取状态为EEPI2C_CONTINUE。第一阶段，已经完成地址发送 ***/
        if( WriteScanEepromI2CWord(EepAdrX, EepromQueue.Wdata.Ushort[0],EEPI2C_CONTINUE) == TRUE )
        {
            EepMsg.WrEepQueWait = 0;
            EepMsg.WrEepQueStep = STEP_PRMWR02;
        }
        break;
    case STEP_PRMWR02: // Round Write Parameter
        /*** 等待eep内部写入完成，手册推荐最大5ms，这里10-4 = 6ms ***/
        if( EepMsg.WrEepQueWait++ >= EEP_WAIT_MS(EEP_TWR, 2 ))	
        {														
            EepMsg.WrEepQueWait = 0;							
            EepMsg.WrEepQueStep = STEP_PRMWR03;					
        }														
        break;
    case STEP_PRMWR03: // Round Write Parameter
        /*** 写入字时WdNum为2，双字WdNum为3 ***/
        if( EepromQueue.WdNum <= 2 )							
        {
            EepMsg.WrEepQueStep = STEP_PRMWRS1;					
        }
        else // 双字
        {
            EepMsg.WrEepQueStep = STEP_PRMWR11;					
            EepAdrX = HWD_EEPADR( EepromQueue.Eaddr );	// 取高字地址	
            /*** 写入第一阶段，发送数据0，状态EEPI2C_START，完成地址发送 ***/
            WriteScanEepromI2CWord( EepAdrX, 0, EEPI2C_START );	
        }
        break;
    case STEP_PRMWR11: // Round Write Parameter
        /*** 写入双字高字数据和EEPI2C_CONTINUE ***/
		EepAdrX = HWD_EEPADR( EepromQueue.Eaddr );	
        if( WriteScanEepromI2CWord(EepAdrX, EepromQueue.Wdata.Ushort[1], EEPI2C_CONTINUE) == TRUE )
        {
            EepMsg.WrEepQueWait = 0;
            EepMsg.WrEepQueStep = STEP_PRMWR12;
        }
        break;
    case STEP_PRMWR12: // Round Write Parameter
        /*** 等待eep内部写入完成，手册推荐最大5ms，这里10-4 = 6ms ***/
        if( EepMsg.WrEepQueWait++ >= EEP_WAIT_MS(EEP_TWR, 2 ))	
        {														
            EepMsg.WrEepQueWait = 0;							
            EepMsg.WrEepQueStep = STEP_PRMWR13;					
        }														
        break;
    case STEP_PRMWR13: // Round Write Parameter
        /*** 计算数据双字写入情况下，新旧值只差 ***/
        EepromQueue.ChkSumx[0] += EepromQueue.ChkSumx[1];		
        if( EepromQueue.ChkSumx[0] != 0 )      					
            EepMsg.WrEepQueStep = STEP_PRMWRS1;		// 若差值不为0，进行求和校验字更新				
        else
            EepMsg.WrEepQueStep = STEP_WRITEND;		// 若差值为0，写入结束			
        break;
    case STEP_PRMWRS1: // Round Write Parameter
        /*** 求和校验更新 ***/
        if( EepromQueue.Type == EEWTYPE_USRPRM ) // 用户参数组数据				
        {
            Eephdr.UsrChkSum += EepromQueue.ChkSumx[0];	// 更新用户求和校验		
            EepInfo.UsrChkSum = Eephdr.UsrChkSum;
            /*** 准备求和校验新数据写入 ***/
            EepromQueue.Eaddr = EEPADR_USRCHK;
            EepromQueue.Wdata.Ushort[0] = Eephdr.UsrChkSum;
        }
        else // 系统参数													
        {
            Eephdr.SysChkSum += EepromQueue.ChkSumx[0];	// 更新系统求和校验			
            EepInfo.SysChkSum = Eephdr.SysChkSum;
            /*** 准备求和校验新数据写入 ***/
            EepromQueue.Eaddr = EEPADR_SYSCHK;					
            EepromQueue.Wdata.Ushort[0] = Eephdr.SysChkSum;		
        }
        /*** 写入第一阶段，发送数据0，状态EEPI2C_START，完成地址发送 ***/
        WriteScanEepromI2CWord( EepromQueue.Eaddr, 0, EEPI2C_START );
        EepMsg.WrEepQueStep = STEP_PRMWRS1_I2C;
        break;
	case STEP_PRMWRS1_I2C:	// Round Write Parameter
	     /*** 写入数据和EEPI2C_CONTINUE ***/
		 if( WriteScanEepromI2CWord(EepromQueue.Eaddr, EepromQueue.Wdata.Ushort[0], EEPI2C_CONTINUE) == TRUE )
		 {
			 EepMsg.WrEepQueWait = 0;
			 EepMsg.WrEepQueStep = STEP_PRMWRS2;
		 }
		 break;
	case STEP_PRMWRS2: // Round Write Parameter
	    /*** 等待eep内部写入完成，手册推荐最大5ms，这里10-4 = 6ms ***/
		 if( EepMsg.WrEepQueWait++ >= EEP_WAIT_MS(EEP_TWR, 2 ))	
		 {														
			EepMsg.WrEepQueWait = 0;							
			EepMsg.WrEepQueStep = STEP_WRITEND;					
		 }														
		 break;
	case STEP_WRITEND: // 写入完成
		 WriteEepromDisable( );  // 写禁止
		 FreeEepromSemaphore( ); // 释放写信号
		 switch( EepMsg.QueId )
		 {
            case EEPQUEID_WRPRM_SCANC:
                DataTmp = ScanCPrmQue.AddIdx;
                if( ScanCPrmQue.WrtIdx == DataTmp)
                {
                    DataTmp = ~(1<<EepMsg.QueId);  // 若待写入序列写入完成，则清除写入标志
                    EepromQueue.ReqFlag &= DataTmp;             
                }
                break;
            case EEPQUEID_WRPRM_ROUND:                          
                DataTmp = RoundPrmQue.AddIdx;
                if( RoundPrmQue.WrtIdx == DataTmp)
                {
                    DataTmp = ~(1<<EepMsg.QueId);  // 若待写入序列写入完成，则清除写入标志
                    EepromQueue.ReqFlag &= DataTmp;	            
                }
                break;
            default:                               // 其他情况，均为一次写入，直接清除写入标志
                    DataTmp = ~(1<<EepMsg.QueId);
                    EepromQueue.ReqFlag &= DataTmp;             
                break;
        }
        EepMsg.WrEepQueStep = STEP_START;		   // 返回起始阶段				
        break;
	default: 
		 EepMsg.WrEepQueStep = STEP_START;         // 返回起始阶段
		 break;      
    }
    return;
}

/**********************************************************************************************/
/* Function_Name: KriReadEepromPrm         */ 
/* Description  : 通过参数结构体指针读取eep中的数据并返回
                  调用：需要时调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
ULONG KriReadEepromPrm( CPRMDEF *prmdef )
{
    USHORT	eepadr;
    USHORT	eepadrx;
    USHORT	rdata[2];
    
	if( prmdef->Attr.Place == PRMDEF_ONLY_RAM )
	{
		return( 0x0000 ); // 只读，直接返回
	}
	GetEepromSemaphore( WAIT );
    
	if( prmdef->Attr.IsLong )
	{
		eepadr   = ORG_EEPADR( prmdef );
		eepadrx  = LWD_EEPADR( eepadr  );
		rdata[0] = ReadEepromWord( eepadrx ); // 读取32bit低字
		eepadrx  = HWD_EEPADR( eepadr );
		rdata[1] = ReadEepromWord( eepadrx ); // 读取32bit高字
	}
	else
	{
		eepadrx  = GET_EEPADR( prmdef );
		rdata[0] = ReadEepromWord( eepadrx ); // 读取16bit字
		rdata[1] = 0x0000;
	}
	FreeEepromSemaphore( );
	return( *(ULONG*)rdata );
}

/**********************************************************************************************/
/* Function_Name: KpxResetEepromAlmTrc         */ 
/* Description  : 复位故障历史记录到0
                  调用：需要时调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void KpxResetEepromAlmTrc( void )
{
    USHORT	i;
    
	GetEepromSemaphore( WAIT );
	WriteEepromEnable( );   // 写使能
	for( i=0; i < Param_ALMTRC; i++ )
	{
		WriteEepromWord( EEPADR_ALMTRC + i, 0x0000, WAIT ); // 连续对故障历史记录区域写0
	}
	KPI_DI( );
	EepromQueue.ReqFlag &= (~(1<<EEPQUEID_ALARMTRACE)); // 清除故障写入请求
	KPI_EI( );
	WriteEepromDisable( );
	FreeEepromSemaphore( );
	return;
}

/**********************************************************************************************/
/* Function_Name: KpxResetEepromAlmMon         */ 
/* Description  : 复位当前故障记录到0
                  调用：需要时调用
                  输入：
                  输出： 	*/
/**********************************************************************************************/
void KpxResetEepromAlmMon( void )
{
USHORT	i;
	GetEepromSemaphore( WAIT );
	WriteEepromEnable( );
	for( i=0; i < Param_ALMMON; i++ )
	{
		WriteEepromWord( EEPADR_ALMMON + i, 0x0000, WAIT ); // 连续对当前故障记录区域写0
	}
	WriteEepromDisable( );
	FreeEepromSemaphore( );
	return;
 }
  
  
