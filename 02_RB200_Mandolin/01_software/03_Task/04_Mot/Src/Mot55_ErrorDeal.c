/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name   : Mot55_ErrorDeal.c
* Version     : V0.1
* Date        : 2024
* Description : 故障警告管理、故障复位、故障标志位设置
***********************************************************************************************/
  
#include "Mot55_ErrorDeal.h"
 
 
typedef	struct	{
    VUCHAR	AlmSemaphore;
} LMNG;
#define  	KALMSEMA_STD	   1		    // 允许获取故障信号			 
#define  	KALMSEMA_RESET	   2	        // 正在复位故障信号

                KALM Kalm;
                ALM  Alm;
static volatile LMNG Lmng;
 
/*--------------------------------------------------------------------------------------------*/
/*                     故障信号获取/释放宏定义                                                */
/*--------------------------------------------------------------------------------------------*/
#define  	GET_SEMAPHORE( Sema )									\
				KPI_DI( );											\
				if( Sema != 0 )  								    \
				{													\
					KPI_EI( );										\
					return;  									    \
				}													\
				else												\
				{													\
					Sema = KALMSEMA_STD;							\
					KPI_EI( );										\
				}
#define  	FREE_SEMAPHORE( Sema )									\
				{													\
					Sema = 0;										\
				}
#define ALM_BITSET( data, bit )		(  data[(bit)>>5] |=  ((ULONG)1<<((bit)&0x1F)) )
#define ALM_BITCLR( data, bit )		(  data[(bit)>>5] &= ~((ULONG)1<<((bit)&0x1F)) )
#define ALM_BITCHK( data, bit )		( (data[(bit)>>5] &   ((ULONG)1<<((bit)&0x1F))) != 0 )
#define WRN_BITSET( data, bit )		(  data[(bit)>>5] |=  ((ULONG)1<<((bit)&0x1F)) )
#define WRN_BITCLR( data, bit )		(  data[(bit)>>5] &= ~((ULONG)1<<((bit)&0x1F)) )
#define WRN_BITCHK( data, bit )		( (data[(bit)>>5] &   ((ULONG)1<<((bit)&0x1F))) != 0 )

#define LPX_EXT_ALMID	0xffff              // 扩展故障码ID             
#define LPX_EXT_WRNID	0xfffe              // 扩展警告码ID         
  
/*------------------------------------------------------------------------------------*/
/*   报警位表宏操作 : Clear BitTbl, And BitTbl       Alarm bit table operation macro  */
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
/*   表宏操作 : Clear Tbl（清除）, And Table（置位）                                  */
/*------------------------------------------------------------------------------------*/
#define  	LPX_CLR_TBL01( tx, i )              \
				tx[ i ] = 0x00;
#define  	LPX_CLR_TBL02( tx, i )		        \
				LPX_CLR_TBL01( tx, i )		    \
				;							    \
				LPX_CLR_TBL01( tx, i + 1 )	    \
				;
#define  	LPX_CLR_TBL03( tx, i )			    \
				LPX_CLR_TBL02( tx, i )		    \
                ;						        \
LPX_CLR_TBL01( tx, i + 2 )													\
;
#define  	LPX_CLR_TBL04( tx, i )											\
				LPX_CLR_TBL02( tx, i )										\
;																			\
LPX_CLR_TBL02( tx, i + 2 )													\
;
#define  	LPX_CLR_TBL05( tx, i )											\
				LPX_CLR_TBL04( tx, i )										\
;																			\
LPX_CLR_TBL01( tx, i + 4 )													\
;
#define  	LPX_CLR_TBL06( tx, i )											\
				LPX_CLR_TBL04( tx, i )										\
;																			\
LPX_CLR_TBL02( tx, i + 4 )													\
;
#define  	LPX_CLR_TBL07( tx, i )											\
				LPX_CLR_TBL04( tx, i )										\
;																			\
LPX_CLR_TBL03( tx, i + 4 )													\
;
#define  	LPX_CLR_TBL08( tx, i )											\
				LPX_CLR_TBL04( tx, i )										\
;																			\
LPX_CLR_TBL04( tx, i + 4 )													\
;
 #define  	LPX_AND_TBL01( tx, ax, i )										\
				tx[ i ] &= ax[ i ];
#define  	LPX_AND_TBL02( tx, ax, i )										\
				LPX_AND_TBL01( tx, ax, i )									\
				;															\
				LPX_AND_TBL01( tx, ax, i + 1 )								\
				;
#define  	LPX_AND_TBL03( tx, ax, i )										\
				LPX_AND_TBL02( tx, ax, i )									\
;																			\
LPX_AND_TBL01( tx, ax, i + 2 )												\
;
#define  	LPX_AND_TBL04( tx, ax, i )										\
				LPX_AND_TBL02( tx, ax, i )									\
;																			\
LPX_AND_TBL02( tx, ax, i + 2 )												\
;
#define  	LPX_AND_TBL05( tx, ax, i )										\
				LPX_AND_TBL04( tx, ax, i )									\
;																			\
LPX_AND_TBL01( tx, ax, i + 4 )												\
;
#define  	LPX_AND_TBL06( tx, ax, i )										\
				LPX_AND_TBL04( tx, ax, i )									\
;																			\
LPX_AND_TBL02( tx, ax, i + 4 )												\
;
#define  	LPX_AND_TBL07( tx, ax, i )										\
				LPX_AND_TBL04( tx, ax, i )									\
;																			\
LPX_AND_TBL03( tx, ax, i + 4 )												\
;
#define  	LPX_AND_TBL08( tx, ax, i )										\
				LPX_AND_TBL04( tx, ax, i )									\
;																			\
LPX_AND_TBL04( tx, ax, i + 4 )												\
;
#if ALM_BITTBL_NUM == 4
#define  	LPX_CLR_AlmBitTbl( BitTbl )  		 LPX_CLR_TBL04 ( BitTbl, 0 )
#define  	LPX_AND_AlmBitTbl( BitTbl, AndTbl )   LPX_AND_TBL04 ( BitTbl, AndTbl, 0 )
#elif ALM_BITTBL_NUM == 5
#define  	LPX_CLR_AlmBitTbl( BitTbl )  		 LPX_CLR_TBL05 ( BitTbl, 0 )
#define  	LPX_AND_AlmBitTbl( BitTbl, AndTbl )   LPX_AND_TBL05 ( BitTbl, AndTbl, 0 )
#else
#error "***** Compile Error *****"
#endif

 /*-----------------------------------------------------------------------------------*/
 /*                      警告位表宏操作 : Clear BitTbl, And BitTbl                    */
 /*-----------------------------------------------------------------------------------*/
#if WRN_BITTBL_NUM == 2
#define  	LPX_CLR_WrnBitTbl( BitTbl )  		 LPX_CLR_TBL02 ( BitTbl, 0 )
#define  	LPX_AND_WrnBitTbl( BitTbl, AndTbl )   LPX_AND_TBL02 ( BitTbl, AndTbl, 0 )
#elif WRN_BITTBL_NUM == 3
#define  	LPX_CLR_WrnBitTbl( BitTbl )  		 LPX_CLR_TBL03 ( BitTbl, 0 )
#define  	LPX_AND_WrnBitTbl( BitTbl, AndTbl )   LPX_AND_TBL03 ( BitTbl, AndTbl, 0 )
#else
#error "***** Compile Error *****"
#endif
  
/************************************************************************************/
/* Function_Name: KriResetParamError                                                */
/* Description  : 复位参数错误(仅在线)
  调  用     :                                                                   */
/************************************************************************************/
void KriResetParamError( void )
{
 	Alm.PrmErrInfo.ErrFlag = FALSE;  						 
	return;
}
  
 /************************************************************************************/
 /* Function_Name: AlarmManager_Init                                                 */
 /* Description  : 初始化警报管理，以备初始化过程中发生的警报
      调  用     : Main函数调用                                                      */
 /************************************************************************************/
 void AlarmManager_Init( void )
{
	LONG   i;
	USHORT AlmDefCntx = AlmDefTblEntNum;		    //	故障个数			 
	USHORT WrnDefCntx = WrnDefTblEntNum;			//	警告个数			 
      
    /*------------------------------------------------------------------------------*/
    /*  故障/警报时相关变量清零处理                                 				*/
    /*------------------------------------------------------------------------------*/
 	MlibResetSHORTMemory( &Kalm, sizeof( Kalm ));
	MlibResetSHORTMemory( &Alm, sizeof( Alm ));
	MlibResetSHORTMemory( (void*)&Lmng, sizeof( Lmng ));

    // 初期设定警报表前指针初始设定
 	Kalm.AlmTrcSp = &Kalm.AlmTrc[ 0 ];

    // 故障 屏蔽位定义处理
 	for( i = 0; i < AlmDefCntx; i++ )
	{
		if( AlmDefTbl[ i ].AlmAttr & ALMDEF_ATTR_NOTRESET )
		{
			ALM_BITSET( Kalm.AlmRstMsk, i );    // 故障不可复位时,则置位不可复位标志位                
		}
	}

    // 警告 屏蔽位定义处理
 	for( i = 0; i < WrnDefCntx; i++ )
	{
        // 警告 是否可复位相应标志位
 		if( WrnDefTbl[ i ].AlmAttr & ALMDEF_ATTR_NOTRESET )
		{
			WRN_BITSET( Kalm.WrnRstMsk, i );    // 警告不可复位时,则置位不可复位标志位                 
		}

        // 驱动器、通信警告标志位
 		if( WrnDefTbl[ i ].AlmAttr & ALMDEF_ATTR_COMALARM )
		{
			WRN_BITSET( Kalm.ComWrnChk, i );
		}
		else
		{
			WRN_BITSET( Kalm.AmpWrnChk, i );
		}
	}
 	return;
}
 
/*******************************************************************************************/
/* Function_Name: KpiSetAlarm                                                              */
/* Description  : 故障设置处理
     调  用     : 宏定义中使用，#define KPI_ALARMSET( id )                                 */
/*******************************************************************************************/
volatile ULONG idOld = 0xFFFF;
void KpiSetAlarm( ULONG id )
{
	ALMTBL *AlmTblSp;				                     
	ALMDEF	AlmDefX;									 
	UCHAR	StopModeX;									 
	UCHAR	StopModeY;									 
      
    if( Alm.f.AlmFlag == 0 )
    {
        idOld = 0xFFFF;
    }

    // 通讯型机型更新相关的故障报文信息
    if( Kprm.f.EtherCATNet == 1 )
    {
        if( idOld != id )
        {
            ServoErrorUpdate( id );     //   紧急报文处理(EtherCat)                   
            idOld = id;
        }
    }
    if( Kprm.f.CanOpenNet == 1 )
    {
        if( idOld != id )
        {
            CanOpenEMCY_Update(id);     //   紧急报文处理( CanOpen )                 
            idOld = id;
        }
    }

    // 读取ID对应的报警信息(从表格中读取相的属性)
 	AlmDefX = AlmDefTbl[ id ];							 

    // 获取故障标志位Semaphore
 	KPI_DI( );											     
    if(Lmng.AlmSemaphore == 0)
    {
        Lmng.AlmSemaphore = KALMSEMA_STD;                
        KPI_EI( );                                       
    }
    else
    {
         if( Lmng.AlmSemaphore == KALMSEMA_STD )          
        {   
            // 当当前的故障处理在占用时,将当前的故障记录临时保存
            ALM_BITSET( Kalm.AlmSetx, id );              
 			StopModeX = AlmDefX.StopMode & 0x0F;		 
			if( StopModeX == 0x0F )
			{
                /*-------------------------------------------------------------------*/
                /* Iprm.StopMode = 0x0004 : 通过DB来停止电机,停止后DB保持            */
                /* Iprm.StopMode = 0x0005 : 通过DB来停止电机,然后接触DB              */
                /* Iprm.StopMode = 0x0006 : 不使用DB,将电机设为自由运行状态          */
                /*-------------------------------------------------------------------*/
 				StopModeX = Iprm.StopMode;               
			}
 			if( StopModeX > Alm.StopMode )				 
			{
				Alm.StopMode = StopModeX;	    //	Update StopMode		 
			}
             KPI_EI( );									 
			return;  								     
        }
 		else
		{
			KPI_EI( );									 
			return;  								     
		}
    }

    // 故障设置处理
 	if( Kalm.AlmCnt < KPX_ALMTBLMAX )	        // 故障记录个数				 
    {
		ALM_BITSET( Alm.AlmSet, id );			// 故障标记为记录处		 
 		AlmTblSp = &Kalm.AlmTbl[ Kalm.AlmCnt ]; // 故障登记         
		AlmTblSp->AlmId   = ( USHORT )id;		// 故障ID		 
		AlmTblSp->AlmDef  = AlmDefX;
        AlmTblSp->TmStamp = KnlV.TmStamp;       // 故障时间戳         
		Kalm.AlmCnt++;							// 故障登记计数器累加		 

        // 报警记录到故障记录表
 		if( ( AlmTblSp->AlmDef.AlmAttr & ALMDEF_ATTR_NOEEPROM ) == 0x00 )
		{
		    // 30s时间相同的故障不存储
			if( ( AlmTblSp->AlmDef.AlmCode != Kalm.AlmTrcSp->AlmDef.AlmCode )
				 || ( ( AlmTblSp->TmStamp - Kalm.AlmTrcSp->TmStamp ) >= 300))    
			{
				UCHAR	Idx   = Kalm.AlmTrcHdr.b.Idx;
				ALMTRC *AlmTrcSp = &Kalm.AlmTrc[ Idx ];
 				AlmTrcSp->OnFlag  = 1;
				AlmTrcSp->AlmDef  = AlmTblSp->AlmDef;
				AlmTrcSp->TmStamp = AlmTblSp->TmStamp;
				Kalm.AlmTrcSp	  = AlmTrcSp;
				Kalm.AlmTrcCnt.TrcAddCnt++;
 				Kalm.AlmTrcHdr.b.Idx = ( Idx >= ( KPX_ALMTRCMAX - 1 ) )? 0:( Idx + 1 );
				if( Kalm.AlmTrcHdr.b.Cnt < KPX_ALMTRCMAX )
				{
					Kalm.AlmTrcHdr.b.Cnt++;
				}
			}
		}
    }
     else
    {
        // 如果故障记录表已经满了，则取最近的一次故障记录值与当前的记录值进行比较处理 
         ALM_BITSET( Alm.AlmSet, id );
        AlmTblSp = &Kalm.AlmTbl[KPX_ALMTBLMAX - 1];     // 取故障记录中的最后一次记录           
         StopModeX = (AlmDefX.StopMode & 0x0F);         // 取最近一次的报警          
        if( StopModeX == 0x0F )
        {
            StopModeX = Iprm.StopMode;
        }
         StopModeY = (AlmTblSp->AlmDef.StopMode & 0x0F); 
        if( StopModeY == 0x0F )
        {
            StopModeY = Iprm.StopMode;
        }
         if( StopModeX > StopModeY )
        {
            AlmTblSp->AlmId   = (USHORT)id;
            AlmTblSp->AlmDef  = AlmDefX;
            AlmTblSp->TmStamp = KnlV.TmStamp;
        }    
    }
      
    Lmng.AlmSemaphore = 0;
}
  
  
/*************************************************************************************/
/* Function_Name: LpxSetAlarm                                                        */
/* Description  : 故障记录处理                                                       */
/*************************************************************************************/
/*  功   能    ：将等待登记的警报登记到警报登记表和警报历史记录表中
                     1) 在故障登记表中登记故障信息。                                                 
                     2) 在故障历史记录表中登记故障信息。                                                 
     调  用    : 检查故障设置位LPX_CHK_ALMSETX_BITS中调用                            */
/*************************************************************************************/
void LpxSetAlarm( ULONG  idx, ULONG  bitno )
{
	ALMTBL *AlmTblSp;							             
	ALMDEF	AlmDefX;										 
	UCHAR	StopModeX;										 
	UCHAR	StopModeY;										 
	ULONG	id = ( 32 * idx ) + bitno;						 
  
    // 读取故障定义信息
	AlmDefX = AlmDefTbl[ id ];								 
  
    // 故障登记处理
	if( Kalm.AlmCnt < KPX_ALMTBLMAX )		    // 检查故障登记号				 
	{
		Alm.AlmSet[ idx ] |= ( 1 << bitno );	// 故障登记标志设置			 
 		 
 		AlmTblSp		   = &Kalm.AlmTbl[ Kalm.AlmCnt ];	 
		AlmTblSp->AlmId    = ( USHORT )id;					 
		AlmTblSp->AlmDef   = AlmDefX;						 
		AlmTblSp->TmStamp  = KnlV.TmStamp;					 
		Kalm.AlmCnt++;										 
 		 
        // 故障历史表登记处理
		if( ( AlmTblSp->AlmDef.AlmAttr & ALMDEF_ATTR_NOEEPROM ) == 0x00 )
		{
			if( ( AlmTblSp->AlmDef.AlmCode != Kalm.AlmTrcSp->AlmDef.AlmCode )
				 || ( ( AlmTblSp->TmStamp - Kalm.AlmTrcSp->TmStamp ) >= 300  ) )
			{
				UCHAR	Idx   = Kalm.AlmTrcHdr.b.Idx;
				ALMTRC *AlmTrcSp = &Kalm.AlmTrc[ Idx ];
 				AlmTrcSp->OnFlag  = 1;
				AlmTrcSp->AlmDef  = AlmTblSp->AlmDef;
				AlmTrcSp->TmStamp = AlmTblSp->TmStamp;
				Kalm.AlmTrcSp	  = AlmTrcSp;
				Kalm.AlmTrcCnt.TrcAddCnt++;
 				Kalm.AlmTrcHdr.b.Idx = ( Idx >= ( KPX_ALMTRCMAX - 1 ) )? 0:( Idx + 1 );
				if( Kalm.AlmTrcHdr.b.Cnt < KPX_ALMTRCMAX )
				{
					Kalm.AlmTrcHdr.b.Cnt++;
				}
			}
		}
	}
  
    /*-------------------------------------------------------------------------------*/
    /*      当报警登记表满时，如果发生比最后登记的报警优先级更高的报警，为安全起见，
            要将高优先级报警信息覆盖到最后登记的报警信息中。                         */
    /*-------------------------------------------------------------------------------*/
 	else
	{
		Alm.AlmSet[ idx ] |= ( 1<<bitno );						//	设置故障登记标志
 		AlmTblSp		   = &Kalm.AlmTbl[ KPX_ALMTBLMAX - 1 ]; //	最终注册警报信息 
 		 
		StopModeX		   = ( AlmDefX.StopMode & 0x0F );
		if( StopModeX == 0x0F )
		{
			StopModeX = Iprm.StopMode;
		}
		StopModeY = ( AlmTblSp->AlmDef.StopMode & 0x0F );
		if( StopModeY == 0x0F )
		{
			StopModeY = Iprm.StopMode;
		}
 		if( StopModeX > StopModeY )
		{
			AlmTblSp->AlmId   = ( USHORT )id;
			AlmTblSp->AlmDef  = AlmDefX;
			AlmTblSp->TmStamp = KnlV.TmStamp;
		}
	}
 #ifdef MCCSW_SGDVM3

    // 故障属性设置，通信IF使用
 	if( AlmDefX.AlmAttrEx & ALMDEF_M3ATTR_CMDALM )
	{
		Alm.AlmExInfo.CmdAlm = TRUE;
	}
	else
		if( AlmDefX.AlmAttrEx & ALMDEF_M3ATTR_COMALM )
		{
			Alm.AlmExInfo.CommAlm = TRUE;
		}
		else
		{
			Alm.AlmExInfo.DevAlm = TRUE;
		}
#endif
 	return;
}
  
  
/*************************************************************************************/
/* Function_Name: Fun_KpiSetWarning                                                  */
/* Description  : 警告设置处理，在警告注册表中注册警告信息。
                   1) 设置警告状态标志。
                   2) 如果已登记到警告登录表中，则结束（return）。
                   3) 警告信号获取处理
                      禁止中断。
                      如果警告信号是忙的，则允许中断，什么都不做就结束。
                      如果警告信号是空的，则获得信号，允许中断。
                   4) 在警告登录表中登录警告信息。
                   5) 释放警告信号并结束。                                                            
    注     意   ：由于在发生警告时从每个用户调用该函数，因此多个警告
                  如果同时发生警告，则会影响每个扫描的处理时间。
                  因此，本函数仅限于所需最小限度的处理。                                             
    调     用   : 仅#define KPI_WARNINGSET( id )                                     */
/*************************************************************************************/
void KpiSetWarning( ULONG  id )
{
    ALMTBL *AlmTblSp;											 

    // 警告状态标志位设定
 	KPI_DI( );													 
	WRN_BITSET( Alm.WrnSts, id );								 
	KPI_EI( );													 

    // 检测警告是否已被登记
 	if( WRN_BITCHK( Alm.WrnSet, id ) )							 
	{
		return;  											 
	}

    // 警报信号获得:信号无法获得时，返回
 	KPI_DI( );													 
	if( Lmng.AlmSemaphore == 0 )								 
	{
		Lmng.AlmSemaphore = KALMSEMA_STD;						 
		KPI_EI( );												 
	}
	else
		if( Lmng.AlmSemaphore == KALMSEMA_STD )  			 
		{
			WRN_BITSET( Kalm.WrnSetx, id );  				 
			KPI_EI( );											 
			return;  										 
		}
		else													 
		{
			KPI_EI( );											 
			return;  										 
		}

    // 警告登记处理 : 最多5个
 	if( ( Kalm.AlmCnt < KPX_ALMTBLMAX ) && ( Kalm.WrnCnt < 5 ) )
	{
		WRN_BITSET( Alm.WrnSet, id );							 

        // 故障登记表登记处理
 		AlmTblSp		  = &Kalm.AlmTbl[ Kalm.AlmCnt ];		 
		AlmTblSp->AlmId   = ( USHORT )id;						 
		AlmTblSp->AlmDef  = WrnDefTbl[ id ];					 
		AlmTblSp->TmStamp = KnlV.TmStamp;						 
		Kalm.AlmCnt++;											 
		Kalm.WrnCnt++;											 
 		 
	}
#ifdef MCCSW_SGDVM3

    // 通信ＩＦ用(MECHATROLINK-Ⅲ)警告数据设定
 	if( AlmTblSp->AlmDef.AlmAttrEx & ALMDEF_M3ATTR_CMDALM )
	{
		Alm.AlmExInfo.CmdAlm = TRUE;
	}
	else
		if( AlmTblSp->AlmDef.AlmAttrEx & ALMDEF_M3ATTR_COMALM )
		{
			Alm.AlmExInfo.CommAlm = TRUE;
		}
		else
		{
			Alm.AlmExInfo.DevWrn = TRUE;
		}
#endif
  
 	FREE_SEMAPHORE( Lmng.AlmSemaphore );
	return;
 }
  
  
/*************************************************************************************/
/* Function_Name: KpiClearWarning                                                    */
/* Description  : 警告清除操作
     调  用     : 警告清除宏定义中调用，#KPI_WARNINGCLR( id )                        */
/*************************************************************************************/
#define SVFSEL_AUTOWRNCLR 1                                      
void KpiClearWarning( ULONG  id )
{
#if SVFSEL_AUTOWRNCLR == 1
	KPI_DI( );													 
	WRN_BITCLR( Alm.WrnSts, id );								 
	KPI_EI( );													 
#endif
	return;
 }
  
/*************************************************************************************/
/* Function_Name: LpxSetWarning                                                      */
/* Description  : 警告设置处理，在故障登记表中登记等待登记的故障。
     调  用     : 检查警告设置位中调用，#LPX_CHK_WRNSETX_BITS                        */
/*************************************************************************************/
void LpxSetWarning( ULONG  idx, ULONG  bitno )
{
	ALMTBL *AlmTblSp;											 
	ULONG	id = ( 32 * idx ) + bitno;
  
    // 故障登记流程
	if( ( Kalm.AlmCnt < KPX_ALMTBLMAX ) && ( Kalm.WrnCnt < 5 ) )
	{
		Alm.WrnSet[ idx ] |= ( 1<<bitno );						 

        // 向故障表登记警报的登记流程
 		AlmTblSp		   = &Kalm.AlmTbl[ Kalm.AlmCnt ];		 
		AlmTblSp->AlmId    = ( USHORT )id;						 
		AlmTblSp->AlmDef   = WrnDefTbl[ id ];					 
		AlmTblSp->TmStamp  = KnlV.TmStamp;						 
		Kalm.AlmCnt++;											 
		Kalm.WrnCnt++;											 
 		 
	}
 #ifdef MCCSW_SGDVM3

    // 通信 IF（MECHATROLINK-Ⅲ）的警告数据设置
 	if( AlmTblSp->AlmDef.AlmAttrEx & ALMDEF_M3ATTR_CMDALM )
	{
		Alm.AlmExInfo.CmdAlm = TRUE;
	}
	else
		if( AlmTblSp->AlmDef.AlmAttrEx & ALMDEF_M3ATTR_COMALM )
		{
			Alm.AlmExInfo.CommAlm = TRUE;
		}
		else
		{
			Alm.AlmExInfo.DevWrn = TRUE;
		}
#endif
 	return;
}
 
  
/**************************************************************************************/
/* Function_Name: LpxInitAlmTraceTable                                                */
/* Description  : 故障历史记录表初始化	
     调  用     : AlarmManager( )调用                                                 */
/**************************************************************************************/
void LpxInitAlmTraceTable( void )
{
	LONG	i;
	ALMTBL *AlmTblSp;
  
 	if( Kalm.AlmTrcHdr.b.Cnt > KPX_ALMTRCMAX )
	{
		Kalm.AlmTrcHdr.w = 0x0000;
	}
	if( Kalm.AlmTrcHdr.b.Idx > ( KPX_ALMTRCMAX - 1 ) )
	{
		Kalm.AlmTrcHdr.w = 0x0000;
	}
	if( Kalm.AlmTrcHdr.b.Idx > Kalm.AlmTrcHdr.b.Cnt )
	{
		Kalm.AlmTrcHdr.w = 0x0000;
	}

    // 故障历史记录前存储指针的初始设置
 	i = ( Kalm.AlmTrcHdr.b.Idx == 0 )? ( KPX_ALMTRCMAX - 1 ):( Kalm.AlmTrcHdr.b.Idx - 1 );
 	Kalm.AlmTrcSp = &Kalm.AlmTrc[ i ];
 	if( Kalm.AlmTrcHdr.b.Cnt == 0 )
	{
		Kalm.AlmTrcSp->AlmDef.AlmCode = 0x0000;
	}

    // 将初始化过程中的故障信息存储在Trace中
 	Kalm.AlmTrcCnt.TrcAddCnt = 0;					 
	Kalm.AlmTrcCnt.EepWrtCnt = 0;					 
	Kalm.AlmEepBuf.TrcHdr	 = Kalm.AlmTrcHdr;		 

    // 故障历史记录表添加本次上电初始化发生的故障
#if 1
	for( i = 0; i < Kalm.AlmCnt; i++ )
	{
		AlmTblSp = &Kalm.AlmTbl[ i ];
		if( ( AlmTblSp->AlmDef.AlmAttr & ALMDEF_ATTR_NOEEPROM ) == 0x00 )
		{
		    // 连续发生相同故障时，需间隔1小时保存
			if( ( AlmTblSp->AlmDef.AlmCode != Kalm.AlmTrcSp->AlmDef.AlmCode )
				 || ( ( AlmTblSp->TmStamp - Kalm.AlmTrcSp->TmStamp >= 36000 )))	 
			{
				UCHAR	Idx   = Kalm.AlmTrcHdr.b.Idx;
				ALMTRC *AlmTrcSp = &Kalm.AlmTrc[ Idx ];
 				AlmTrcSp->OnFlag  = 1;
				AlmTrcSp->AlmDef  = AlmTblSp->AlmDef;
				AlmTrcSp->TmStamp = AlmTblSp->TmStamp;
				Kalm.AlmTrcSp	  = AlmTrcSp;
				Kalm.AlmTrcCnt.TrcAddCnt++;
 				Kalm.AlmTrcHdr.b.Idx = ( Idx >= ( KPX_ALMTRCMAX - 1 ) )? 0:( Idx + 1 );
				if( Kalm.AlmTrcHdr.b.Cnt < KPX_ALMTRCMAX )
				{
					Kalm.AlmTrcHdr.b.Cnt++;
				}
			}
		}
	}
#endif
 	return;
}
  
  
/**************************************************************************************/
/*                                  故障管理处理                                      */
/**************************************************************************************/
/*  功 能 ： 通过周期性（2msCycle）监控报警登记表，执行以下过程：                     */
/*          1) 发生故障时的StopMode设置                                               */
/*          2) 设置故障标志/警告标志                                                  */
/*          3) 故障代码输出数据的创建                                                 */
/*          4) 向报警历史的EEPROM写入请求处理                                         */
/**************************************************************************************/
/*------------------------------------------------------------------------------------*/
/*   检查故障设置位  检查这1组故障是否有在等待而没有记录的，如有则每次只记录最低一位  */
/*------------------------------------------------------------------------------------*/
#define  	LPX_CHK_ALMSETX_BITS( i )																\
				{																					\
					ULONG	ulwk0;																	\
					ulwk0 = Kalm.AlmSetx[ i ] & ( Kalm.AlmSetx[ i ] ^ Alm.AlmSet[ i ] );			\
					if( ulwk0 != 0 )																\
					{																				\
						LpxSetAlarm( i, MlibSrhbiton( ulwk0, SRH_FROM_LSB ) );						\
					}																				\
				}

// 检查警告设置位
 #define  	LPX_CHK_WRNSETX_BITS( i )								                                \
				{													                                \
					ULONG	ulwk0;									                                \
					ulwk0 = Kalm.WrnSetx[ i ] & ( Kalm.WrnSetx[ i ] ^ Alm.WrnSet[ i ] );	        \
					if( ulwk0 != 0 )								                                \
					{												                                \
						LpxSetWarning( i, MlibSrhbiton( ulwk0, SRH_FROM_LSB ) );	                \
					}												                                \
				}

 // 设置警告信息 (警告ID/警告定义)
 #define  	LPX_SET_WARNING_INFO( i )								                                \
				{													                                \
					AlmWrk.WrnId = ( USHORT )( MlibSrhbiton( Alm.WrnSts[ i ], SRH_FROM_LSB ) + ( 32 * i ) );		  \
					AlmWrk.WrnDef = WrnDefTbl[ AlmWrk.WrnId ];		                                \
				}

 // Check AmpWarning/ComWarning
 #define  	LPX_CHK_AMPCOM_WARNING( i )  						            \
				{													        \
					if( Alm.WrnSts[ i ] & Kalm.AmpWrnChk[ i ] )             \
					{												        \
						AlmWrk.AmpWarning = TRUE;					        \
					}												        \
					if( Alm.WrnSts[ i ] & Kalm.ComWrnChk[ i ] )             \
					{												        \
						AlmWrk.ComWarning = TRUE;					        \
					}												        \
				}

 
/***********************************************************************************/
/*      AlmWrk Variable Definition                                                 */
/***********************************************************************************/
typedef	struct
{
    USHORT AlmId;			//	 < Alarm ID >								 
    USHORT WrnId;			//	 < Warning ID >								 
    ALMDEF AlmDef;	        //	 < Alarm Definition Data >										 
    ALMDEF WrnDef;			//	 < Warning Definition Data >								 
    UCHAR  StopMode;  		//	 < Stop Mode >							 
    UCHAR  AmpWarning;		//	 < Amp Warning Flag >								 
    UCHAR  ComWarning;		//	 < Communication Warning Flag >								 
} ALMWRK;
  
  
 /************************************************************************************/
 /* Function_Name: GetAlarmSemaphore                                                 */
 /* Description  : 故障信号获取
                      等待标志: 0x00 (NOWAIT) : 如果不能获得信号量，立即返回
                   0x01 (WAIT):在无限循环中等待，直到可以获得信号量
 
                      取    值：0x00 (FALSE)  : 信号获取失败                 
                                0x01 (TRUE)   : 信号获取成功                                        
      调  用     :                                                                   */
 /************************************************************************************/
 LONG GetAlarmSemaphore( LONG  id, LONG	wait )
{
  
    // 信号获取循环
	while( 1 ) 
	{
		if( Lmng.AlmSemaphore == 0 )							 
		{
			Lmng.AlmSemaphore = ( UCHAR )id;					 
			return ( TRUE );									 
		}
        
        // 检查等待标志
		if( wait == NOWAIT )									 
		{
			return ( FALSE );									 
		}
	}
}
  
 /************************************************************************************/
 /* Function_Name: FreeAlarmSemaphore                                                */
 /* Description  : 故障信号释放
      调  用     :                                                                   */
 /************************************************************************************/
 void FreeAlarmSemaphore( void )
{
	Lmng.AlmSemaphore = 0;										 
	return;
}
  
 /*************************************************************************************/
 /* Function_Name: LpxNotResetAlmClear                                                */
 /* Description  : 从故障登记表中重置指定故障
      调  用     :                                                                    */
 /*************************************************************************************/
 USHORT LpxNotResetAlmClear( void )
{
  
	if( Alm.Appl.AlmResetFlg == TRUE )
		ALM_BITCLR( Alm.AlmSet, Alm.Appl.ResetAlmId );
	return ( Alm.Appl.ResetAlmId );
}
  
  
/*****************************************************************************************/
/* Function_Name: LpxResetAlarmTable                                                     */
/* Description  : 清除当前警报
     调  用     : APL_KpiResetAlarmTable_API()和ScanC警报处理函数中警报清除IO口有效时处理*/
/*****************************************************************************************/
void LpxResetAlarmTable( void )
{
	LONG	i,
			j,
			k;
	UCHAR	Attrx;
	UCHAR	StopModeX;
	UCHAR	StopModeY  = 0;
	UCHAR	MencDataNG = 0;
	ALMTBL *pFirstAlm  = NULL;
	ALMTBL *pFirstWrn  = NULL;
  
    // 故障注册&注册表重置
	LPX_CLR_AlmBitTbl( Kalm.AlmSetx );
	LPX_AND_AlmBitTbl( Alm.AlmSet, Kalm.AlmRstMsk );

    // 警告注册&注册表重置
 	LPX_CLR_WrnBitTbl( Kalm.WrnSetx );
	LPX_AND_WrnBitTbl( Alm.WrnSts, Kalm.WrnRstMsk );
	LPX_AND_WrnBitTbl( Alm.WrnSet, Kalm.WrnRstMsk );

    // 重置故障表
 	for( i = j = k = 0; i < Kalm.AlmCnt; i++ )					 
	{
		Attrx = Kalm.AlmTbl[ i ].AlmDef.AlmAttr;				 
 		if( Attrx & ALMDEF_ATTR_NOTRESET )				 
 			 
		{
			if( i != j )										 
			{
				Kalm.AlmTbl[ j ] = Kalm.AlmTbl[ i ];			 
 			}
 			StopModeX = Kalm.AlmTbl[ j ].AlmDef.StopMode & 0x0F;
			if( StopModeX == 0x0F )
			{
				StopModeX = Iprm.StopMode;
			}
			if( StopModeX > StopModeY )
			{
				StopModeY = StopModeX;
			}
 			if( Attrx & ALMDEF_ATTR_WARNING )
			{
				k++;											 
 				if( pFirstWrn == NULL )
				{
					pFirstWrn = &Kalm.AlmTbl[ j ];				 
				}
			}
			else
			{
				if( pFirstAlm == NULL )
				{
					pFirstAlm = &Kalm.AlmTbl[ j ];				 
 																 
				}
			}
 			j++;										 
		}
	}

    // 重置报警管理信息
 	Kalm.AlmCnt   = ( UCHAR )j;								 
	Kalm.WrnCnt   = ( UCHAR )k;								 
 	Alm.StopMode	 = StopModeY;							 
	Alm.f.MencDataNG = MencDataNG;							 
  
    // 故障状态标志复位
 	for( i = 0; i < KPX_ALMTRCMAX; i++ )
	{
		if( ( Kalm.AlmTrc[ i ].AlmDef.AlmAttr & ALMDEF_ATTR_NOTRESET ) == 0x00 )
		{
			Alm.f.ErrResetFlg = 1;                               
			Kalm.AlmTrc[ i ].OnFlag = 0x00;				         
		}
	}
 
	ALM_BITCLR( Alm.AlmSet, ALM_CAN_MOFF );
	ALM_BITCLR( Alm.AlmSet, ALM_CAN_COMTOV );
	ALM_BITCLR( Alm.AlmSet, ALM_CAN_CONFLIC );
 	return;
 }
  
/********************************************************************************/
/* Function_Name:  KpiAlarmManager                                              */
/* Description  : 故障、警告管理模块                                            */
/********************************************************************************/
void KpiAlarmManager( void )
{
ULONG  i;
ALMWRK AlmWrk;

    // 使用前,相关变量清零处理
    MlibResetLONGMemory( & AlmWrk, sizeof ( AlmWrk ) / 2 );
  
    // 获取告警信号：无法获得信号时，在宏内返回 
    GET_SEMAPHORE( Lmng.AlmSemaphore );

    // 外部端子故障复位处理(沿触发) :
    if( CoutK.f.AlmRst && (Kalm.AlmRstLast == FALSE) )
	{
		Lmng.AlmSemaphore = KALMSEMA_RESET;
		LpxResetAlarmTable( );
		FREE_SEMAPHORE( Lmng.AlmSemaphore );
		Kalm.AlmRstLast = TRUE;
		return;
	}   

    // 告警复位处理
    if( Kprm.f.StandardType )
    {
        if( DIDOVar.DISt.AlmReset && (Kalm.AlmRstLast == FALSE) )
        {
    #ifdef MCCSW_SGDVM3
            Alm.f.NetCmdAlmRst = FALSE;
     #endif
            Lmng.AlmSemaphore = KALMSEMA_RESET;
            LpxResetAlarmTable( );
            FREE_SEMAPHORE( Lmng.AlmSemaphore );
            Kalm.AlmRstLast = TRUE;
            DIDOVar.DISt.AlmReset = FALSE;
            return;
        }
        Kalm.AlmRstLast = ( DIDOVar.DISt.AlmReset )? TRUE:FALSE;
    }
  
 
/*-----------------------------------------------------------------------------------*/
/*  检查和登记 故障等待注册位表                                                      */
/*  检查这5组故障是否有在等待而没有记录的，如有则每次只记录最低一位？？？            */
/*-----------------------------------------------------------------------------------*/
 #if ALM_BITTBL_NUM == 4
	LPX_CHK_ALMSETX_BITS( 0 );							 
	LPX_CHK_ALMSETX_BITS( 1 );							 
	LPX_CHK_ALMSETX_BITS( 2 );							 
	LPX_CHK_ALMSETX_BITS( 3 );							 
#elif ALM_BITTBL_NUM == 5
	LPX_CHK_ALMSETX_BITS( 0 );							 
	LPX_CHK_ALMSETX_BITS( 1 );							 
	LPX_CHK_ALMSETX_BITS( 2 );							 
	LPX_CHK_ALMSETX_BITS( 3 );							 
	LPX_CHK_ALMSETX_BITS( 4 );							 
#else
	#error "***** Compile Error *****"
#endif    

/*-----------------------------------------------------------------------------------*/
/*  检查和登记 警告等待注册位表                                                      */
/*  检查这3组警告是否有在等待而没有记录的，如有则每次只记录最低一位？？？            */
/*-----------------------------------------------------------------------------------*/
 #if WRN_BITTBL_NUM == 2
	LPX_CHK_WRNSETX_BITS( 0 );							 
	LPX_CHK_WRNSETX_BITS( 1 );							 
 #elif WRN_BITTBL_NUM == 3
	LPX_CHK_WRNSETX_BITS( 0 );							 
	LPX_CHK_WRNSETX_BITS( 1 );							 
	LPX_CHK_WRNSETX_BITS( 2 );							 
 #else
	#error "***** Compile Error *****"
#endif    

    // 故障登记表的检查处理
 	for( i = 0; i < Kalm.AlmCnt; i++ )
	{
		ULONG ulwk0,
			  ulwk1;
		ulwk0 = Kalm.AlmTbl[ i ].AlmDef.AlmAttr;
		ulwk1 = Kalm.AlmTbl[ i ].AlmDef.StopMode & 0x0F;

        // 过载故障信息处理
 		if( ( ulwk0 & ALMDEF_ATTR_WARNING ) == 0x00 )			 
		{    
			Alm.AlmOLInfo |= ( ( Kalm.AlmTbl[ i ].AlmDef.StopMode >> 4 ) & 0x07 );
		}
 		 
        // 故障信息处理
		if( ( ulwk0 & ALMDEF_ATTR_WARNING ) == 0x00 )
		{
			if( AlmWrk.AlmDef.AlmCode == 0x0000 )
			{
				AlmWrk.AlmId  = Kalm.AlmTbl[ i ].AlmId;
				AlmWrk.AlmDef = Kalm.AlmTbl[ i ].AlmDef;
			}
		}
 		 
 		else
			if( Kalm.AlmTbl[ i ].AlmId == LPX_EXT_WRNID )
			{
				if( AlmWrk.WrnDef.AlmCode == 0x0000 )
				{
					AlmWrk.WrnId  = Kalm.AlmTbl[ i ].AlmId;
					AlmWrk.WrnDef = Kalm.AlmTbl[ i ].AlmDef;
				}
				if( ulwk0 & ALMDEF_ATTR_COMALARM )      // 通讯类故障
				{
					AlmWrk.ComWarning = TRUE;
				}
				else                                    // 驱动器本体故障
				{
					AlmWrk.AmpWarning = TRUE;
				}
			}

        // 停止模式处理
 		if( ulwk1 == 0x0F )
		{
			ulwk1 = Iprm.StopMode;                      // Pn006.0:发生警报时的停止方法         
		}
 		if( ulwk1 > AlmWrk.StopMode )				    // 优先级检查			 
		{
			AlmWrk.StopMode = ( UCHAR )ulwk1;			// 更新停机方式		 
		}
 	}    
  
 	FREE_SEMAPHORE( Lmng.AlmSemaphore );

/*--------------------------------------------------------------------------------*/
/*      检查处理警告：WrnSts[]位                                                  */
/*--------------------------------------------------------------------------------*/
#if WRN_BITTBL_NUM == 2
	if( Alm.WrnSts[ 0 ] != 0x0000 )
	{
		LPX_SET_WARNING_INFO( 0 );
	}
	else
		if( Alm.WrnSts[ 1 ] != 0x0000 )
		{
			LPX_SET_WARNING_INFO( 1 );
		}
 #elif WRN_BITTBL_NUM == 3
	if( Alm.WrnSts[ 0 ] != 0x0000 )
	{
		LPX_SET_WARNING_INFO( 0 );
	}
	else
		if( Alm.WrnSts[ 1 ] != 0x0000 )
		{
			LPX_SET_WARNING_INFO( 1 );
		}
		else
			if( Alm.WrnSts[ 2 ] != 0x0000 )
			{
				LPX_SET_WARNING_INFO( 2 );
			}
 #else
	#error "***** Compile Error *****"
#endif    

/*--------------------------------------------------------------------------------*/
/*      警告检查处理 : 驱动器 / 通讯 警告                                         */
/*--------------------------------------------------------------------------------*/
#if WRN_BITTBL_NUM == 2
	LPX_CHK_AMPCOM_WARNING( 0 );								 
	LPX_CHK_AMPCOM_WARNING( 1 );								 
#elif WRN_BITTBL_NUM == 3
	LPX_CHK_AMPCOM_WARNING( 0 );								 
	LPX_CHK_AMPCOM_WARNING( 1 );								 
	LPX_CHK_AMPCOM_WARNING( 2 );								 
 #else
	#error "***** Compile Error *****"
#endif
 	Alm.f.AmpWarning = AlmWrk.AmpWarning;
	Alm.f.ComWarning = AlmWrk.ComWarning;
  
 	KPI_DI( );                                                   
	if( AlmWrk.StopMode > Alm.StopMode )	// 检查处理警告					 
	{															 
 		Alm.StopMode = AlmWrk.StopMode;     // 选择停机模式优先级最高者作为最终停机模式			     
	}
	KPI_EI( );													 

    /*-------------------------------------------------------------------------------*/
    /*      报警标志相关设置                                                         */
    /*-------------------------------------------------------------------------------*/
 	Alm.AlmCode = AlmWrk.AlmDef.AlmCode;
 	if( Alm.AlmCode == 0x0000 )  			// 无故障				     
	{
		Alm.f.AlmFlag  = FALSE;  							     
		Alm.f.AlmReady = TRUE;								     
		Alm.AlmWrnCode = AlmWrk.WrnDef.AlmCode;  			     
	}
	else														 
	{
		Alm.f.AlmFlag  = TRUE;									 
		Alm.f.AlmReady = FALSE;  							     
		Alm.AlmWrnCode = AlmWrk.AlmDef.AlmCode;  			     
	}
 	if( AlmWrk.WrnDef.AlmCode != 0x0000 )       
	{
		Alm.f.WrnFlag = TRUE;									 
	}
	else
	{
		Alm.f.WrnFlag = FALSE;									 
	}
 
    /*---------------------------------------------------------------------------------*/
    /*      创建警告码输出数据的过程                                                   */
    /*---------------------------------------------------------------------------------*/
	if( Alm.OpWrnCode != 0x0000 )								 
	{
		if( ++Alm.OpWrnTimer >= KPI_SCANC_MS( 100 ) )			 
		{
			Alm.OpWrnTimer = 0;  							     
			Alm.OpWrnCode  = AlmWrk.WrnDef.AlmCode;  		     
		}
	}
	else														 
	{
		Alm.OpWrnTimer = 0;  								     
		Alm.OpWrnCode  = AlmWrk.WrnDef.AlmCode;  			     
	}    

/*-----------------------------------------------------------------------------------*/
/*      EEPROM过载信息写入处理                                                       */
/*-----------------------------------------------------------------------------------*/
 #if 1
	if( Alm.AlmOLInfo != Kalm.AlmEepBuf.OLInfo )
	{
		if( KriChkEepromQueue( EEPQUEID_ALARMOLINF ) > 0 )
		{
			Kalm.AlmEepBuf.OLInfo = Alm.AlmOLInfo;
			KriAddEepromQueue( Alm.AlmOLInfo, &Kalm.AlmEepBuf.OLInfo, EEPQUEID_ALARMOLINF );
		}
	}
#endif
/*-----------------------------------------------------------------------------------*/
/*      故障历史EEPROM写入请求处理                                                   */
/*-----------------------------------------------------------------------------------*/
 	if( ( Kalm.AlmEepRst == FALSE ) && ( Kalm.AlmTrcCnt.TrcAddCnt != Kalm.AlmTrcCnt.EepWrtCnt ) )
	{
		if( KriChkEepromQueue( EEPQUEID_ALARMTRACE ) > 0 )
		{
			Kalm.AlmTrcCnt.EepWrtCnt++;
			i = Kalm.AlmEepBuf.TrcHdr.b.Idx;
 			Kalm.AlmEepBuf.TrcHdr.b.Idx = ( i >= ( KPX_ALMTRCMAX - 1 ) )? 0:( UCHAR )( i + 1 );
			if( Kalm.AlmEepBuf.TrcHdr.b.Cnt < KPX_ALMTRCMAX )
			{
				Kalm.AlmEepBuf.TrcHdr.b.Cnt++;
			}
 			Kalm.AlmEepBuf.AlmCode = Kalm.AlmTrc[ i ].AlmDef.AlmCode;
			Kalm.AlmEepBuf.TmStamp = Kalm.AlmTrc[ i ].TmStamp;
			KriAddEepromQueue( i, &Kalm.AlmEepBuf, EEPQUEID_ALARMTRACE );
		}
	}
 	return;    
}
  
/************************************************************************************/
/* Function_Name: KpiGetAlarmTraceInfo                                              */
/* Description  : 获取故障历史信息        	
     调  用     : Fn000中调用                                                       */
/************************************************************************************/
LONG KpiGetAlarmTraceInfo( ALMINF  *AlmInfo, LONG  MaxInfo )
{
	LONG i,
		 j;
  
    // 没有故障时,直接退出处理
	if( Kalm.AlmTrcHdr.b.Cnt == 0 )
	{
		return ( 0 );
	}

    // 获取警报进程处理
 	GetAlarmSemaphore( KALMSEMA_STD, WAIT );	    // 获取故障信号				 
 	j = Kalm.AlmTrcHdr.b.Idx - 1;
	if( j < 0 )
	{
		j += KPX_ALMTRCMAX;
	}
	if( MaxInfo > Kalm.AlmTrcHdr.b.Cnt )
	{
		MaxInfo = Kalm.AlmTrcHdr.b.Cnt;
	}
 	for( i = 0; i < MaxInfo; i++ )
	{
		AlmInfo[ i ].OnFlag  = Kalm.AlmTrc[ j ].OnFlag;
		AlmInfo[ i ].AlmCode = Kalm.AlmTrc[ j ].AlmDef.AlmCode;
		AlmInfo[ i ].TmStamp = Kalm.AlmTrc[ j ].TmStamp;
		if( --j < 0 )
		{
			j += KPX_ALMTRCMAX;
		}
	}
 	FreeAlarmSemaphore( );										 
	return ( MaxInfo );
 }
  
/*************************************************************************************/
/* Function_Name: KpiResetAlarmTable                                                 */
/* Description  : 重置故障表
     调  用     :                                                                    */
/*************************************************************************************/
void KpiResetAlarmTable( void )
{
 	GetAlarmSemaphore( KALMSEMA_RESET, WAIT );					 
 	LpxResetAlarmTable( );										 
 	FreeAlarmSemaphore( );										 
 	MencV.MstErrCnt = 0;
 	Err_OC_Reset();
 	return;
 }
 
  
/************************************************************************************/
/* Function_Name: KpiSetParamError                                                  */
/* Description  : 参数设置错误（在线/离线共享）
     调  用     :                                                                   */
/************************************************************************************/
void KpiSetParamError( CPRMDEF	*PrmDef )
{
	LONG i;
  
	if( Alm.PrmErrInfo.ErrCount == 0 )
	{
		KPI_ALARMSET( ALM_PRM );							 
		Alm.PrmErrInfo.ErrCount = 1;						 
		if( PrmDef != NULL )								 
		{
			for( i = 0; i < PNPRMTBL_ENTNUM; i++ )		     
			{
				if( PnPrmTbl[ i ].PrmDefPtr == PrmDef )
				{
					Alm.PrmErrInfo.ErrPrmNo = PnPrmTbl[ i ].PnNo;
						break;
				}
			}
		}
	}
	else 
		if( Alm.PrmErrInfo.ErrCount < 0xFF )
		{
			++Alm.PrmErrInfo.ErrCount;						 
		}
 	return;
}

/**************************************************************************************/
/* Function_Name: KpiGetOtherAlarmChk                                                 */
/* Description  : 
     调  用     :                                                                     */
/**************************************************************************************/
UCHAR	KpiGetOtherAlarmChk( USHORT Id )
{
USHORT	i;
 	for(i=0; i<ALM_BITTBL_NUM; i++)
	{
		if( Alm.AlmSet[i] != 0 )
		{
			if( ( i != (Id >> 5) ) || ( (Alm.AlmSet[i] & (ULONG)(~(1<<((Id)&0x1F)))) != 0 ) )
			{
				return( TRUE );
			}
		}
	}
 	return( FALSE );
}
 
 
/*************************************************************************************/
/* Function_Name: KpiWarningMask                                                     */
/* Description  : 警告屏蔽处理		Pn008
     调  用     :                                                                    */
/*************************************************************************************/
void KpiWarningMask( ULONG	id )
{
 	KPI_DI( );													 
	WRN_BITSET( Alm.WrnSetMsk, id );    // 警告注册掩码标志设置							 
	KPI_EI( );													 
	return;
}
 
  
/*************************************************************************************/
/* Function_Name: KpiSetWarningMask                                                  */
/* Description  : 警告屏蔽处理(Set/Clear)	初始化由Pn008设置
     调  用     :                                                                    */
/*************************************************************************************/
void KpiSetWarningMask( ULONG  id, ULONG  flag )
{
 	if( flag == 0 )  											 
	{
		KPI_DI( );												 
		WRN_BITCLR( Alm.WrnSetMsk, id );						 
		KPI_EI( );												 
	}
	else														 
	{
		KPI_DI( );												 
		WRN_BITSET( Alm.WrnSetMsk, id );						 
		KPI_EI( );												 
	}
	return;
}
 
  
/************************************************************************************/
/* Function_Name: AlarmManager                                                      */
/* Description  : 警报管理开始处理
     调  用     : (Main函数初始化时调用)                                            */
/************************************************************************************/
void AlarmManager(void)
{
    LpxInitAlmTraceTable();                              
}
 
  
/*************************************************************************************/
/* Function_Name: Fun_KpiResetAlarmTrace                                             */
/* Description  : 清除警报历史记录 仅Fn001辅助功能
     调  用     : Fn001辅助功能中调用                                                */
/*************************************************************************************/
void KpiResetAlarmTrace( void )
{
  
    // Reset Checked               已复位检查
	if( ( Kalm.AlmTrcHdr.w == 0 ) && ( Kalm.AlmEepBuf.TrcHdr.w == 0 ) )
	{
		return;
	}

    // 重置故障历史表
 	GetAlarmSemaphore( KALMSEMA_STD, WAIT );			 
 	Kalm.AlmEepRst				  = TRUE;	    // EEPROM警报历史备份数据清除中Flag			 
	Kalm.AlmTrcCnt.TrcAddCnt	  = 0;			// 警报历史登录计数器清零		 
	Kalm.AlmTrcCnt.EepWrtCnt	  = 0;			// 警报历史EEPROM写入计数器清零		 
	Kalm.AlmTrcHdr.w			  = 0x0000;  	// 警报历史报头清零		 
	Kalm.AlmEepBuf.TrcHdr.w  	  = 0x0000;  	// EEPROM写入Buf标志清零		 
	Kalm.AlmTrcSp				  = &Kalm.AlmTrc[ KPX_ALMTRCMAX - 1 ];
                                                // 警报历史上次保存指针
 	Kalm.AlmTrcSp->AlmDef.AlmCode = 0x0000;  	// 警报历史上次存储警报代码清零		 
	FreeAlarmSemaphore( );						// 警报信号释放		 

    // EEPROM历史故障备份数据清除
 	KpxResetEepromAlmTrc( );							 
    KpxResetEepromAlmMon( );
      
    MlibResetLONGMemory( &CoutV.AlmLtMon, sizeof(CoutV.AlmLtMon) / 2 );
      
    // EEPROM故障历史表复位中Flag 
	Kalm.AlmEepRst = FALSE;  							 
	return;
}
 
/****************************************************************************************************/
/* Function_Name: KpiGetAlarmTraceAlmCode                                                           */
/* Description  : 获取故障历史故障码
	注   意     : 由于报警历史记录是随着报警的发生而顺序更新的，为了确保采集报警历史记录信息的完整性，
                  需要对报警历史记录缓冲区进行锁存（缓冲区复制）。不过，通常情况下由于报警和报警历史
                  信息采集时序重叠的概率较小，而且报警历史信息的使用是为监控，因此锁存处理将被省略  */
/****************************************************************************************************/
USHORT KpiGetAlarmTraceAlmCode( LONG  Index )
{
	LONG i;
  
    // 检查索引值
	if( Index >= Kalm.AlmTrcHdr.b.Cnt )
	{
		return ( 0 );
	}

    // 获取故障码
 	i = Kalm.AlmTrcHdr.b.Idx - 1  - Index;
	if( i < 0 )
	{
		i += KPX_ALMTRCMAX;
	}
	return ( Kalm.AlmTrc[ i ].AlmDef.AlmCode );
 }
 
  
  
/****************************************************************************************************/
/* Function_Name: KpiGetAlarmTraceTmStamp                                                           */
/* Description  : 获取故障历史记录时间戳                                                            */
/****************************************************************************************************/
/*	注 意 : 由于报警历史记录是随着报警的发生而顺序更新的，为了确保采集报警历史记录信息的完整性，需要
            对报警历史记录缓冲区进行锁存（缓冲区复制）。不过，通常情况下，由于警报和警报历史记录信息
            的获取时序重叠的概率较小，而且警报历史记录信息的使用是为了监控，因此锁存处理将被省略。  */
/****************************************************************************************************/
ULONG KpiGetAlarmTraceTmStamp( LONG  Index )
{
	LONG i;
  
    // 检查索引值
	if( Index >= Kalm.AlmTrcHdr.b.Cnt )
	{
		return ( 0 );
	}

    // 获取时间戳
 	i = Kalm.AlmTrcHdr.b.Idx - 1  - Index;
	if( i < 0 )
	{
		i += KPX_ALMTRCMAX;
	}
	return ( Kalm.AlmTrc[ i ].TmStamp );
}


/*************************************************************************************/
/*  低压伺服警告 or 故障信号显示                                                     */
/*************************************************************************************/
USHORT ServoARMCnt = 0;
void ErrFlag_Update( void )
{
     if( Alm.f.AlmFlag == 1 )
    {
#ifdef CPU1
        KPX_MOTA_ERROR_LED_ON( );
#endif
    }
     else if( Alm.f.WrnFlag == 1  || CoutV.f.Seq.ServoReady == 0 || CinV.f.Sv.Pot || CinV.f.Sv.Not )
    {
        ServoARMCnt ++;
        if( ServoARMCnt == 2 )
        {
#ifdef CPU1
            KPX_MOTA_ERROR_LED_OFF( );
#endif
        }
        else if( ServoARMCnt == 150 )
        {
#ifdef CPU1
            KPX_MOTA_ERROR_LED_ON( );
#endif
        }
        else if( ServoARMCnt > 300 )
        {
            ServoARMCnt = 0;
        }
    }
     else
    {
#ifdef CPU1
        KPX_MOTA_ERROR_LED_OFF( );
#endif
        ServoARMCnt = 0;
    }
}

/*******************************************File End*******************************************/

