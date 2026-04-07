/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : User10_MonMngr.c
* Version            : V0.1
* Date               : 2024
* Description        : 监控功能码操作管理
***********************************************************************************************/

#include "Main.h"

/*** UnMonTbl[] : 键盘操作使用，UnRegTbl[] : USB通讯使用 ***/
/*** 监视器管理用变量定义 ***/
typedef struct {                            /*** 监视器管理用变量定义 ***/
    USHORT  UnMonTblEntNum;                 // Un监视表登录个数；键盘用
    USHORT  UnRegTblEntNum;                 // Un寄存器表注册个数；通讯用
} MONMNGP;
/*--------------------------------------------------------------------------------------------------*/
MONMNGP MonMngP;
/*--------------------------------------------------------------------------------------------------*/



/****************************************************************************************************/
LONG    RpiMonRead( MONDEF  *UnDefPtr,  ULONG   *ResData,   UCHAR   CheckType   );
LONG    LpxMonCheckAttrIdx( LONG    Index,  UCHAR   CheckType   );
USHORT  RpxMonSearchIdxOp(  USHORT  SrchNo, USHORT  BaseIndex   );
LONG    LpxMonCheckAttrMdef(        MONDEF  *MondefPtr,     UCHAR   CheckType   );
void    RpxMonClearVarIdx(USHORT    Index       );

/**********************************************************************************************/
/* Function_Name: RpxInitMonManager         */
/* Description  : 监控功能码初始化处理
                  调用：初始化调用一次
                  输入：
                  输出：   */
/**********************************************************************************************/
void    RpxInitMonManager( void )
{

/*--------------------------------------------------------------------------------------------------*/
/*      Set Table Entry Number                                                                      */
/*--------------------------------------------------------------------------------------------------*/
        MonMngP.UnMonTblEntNum = UNMONTBL_ENTNUM;       /* Set UnMonTbl Entry Number                */
        MonMngP.UnRegTblEntNum = UNREGTBL_ENTNUM;       /* Set UnRegTbl Entry Number                */
/*--------------------------------------------------------------------------------------------------*/
        return;

}

/**********************************************************************************************/
/* Function_Name: RpxMonClearVarIdx         */
/* Description  : 根据索引号，复位清零索引号指定的监视器变量
                  调用：键盘操作中调用
                  输入：监视器管理表索引号
                  输出：   */
/**********************************************************************************************/
void    RpxMonClearVarIdx(  USHORT  Index   )
{
MONDEF  *UnDefPtr;

        // 根据索引号，获取监视变量结构体指针
        UnDefPtr = (MONDEF *)UnMonTbl[Index].MonDefPtr;
        if(UnDefPtr->ValClr == MONDEF_CLR_ENABLE)
        {
            // 若监视变量是可清零的，进行复位清零处理
            *(ULONG *)UnDefPtr->Var.Ulong = 0;
        }
        return;

}

/**********************************************************************************************/
/* Function_Name: RpiMonRead         */
/* Description  : 监视器数据读取处理(定义指定)
                  调用：键盘操作中调用
            输入：UnDefPtr：监控功能码指针，ResData：监控功能码读取数据，CheckType：错误检测类型
            输出：ResData：监控功能码读取数据，读取状态     */
/**********************************************************************************************/
LONG    RpiMonRead( MONDEF *UnDefPtr, ULONG *ResData, UCHAR CheckType )
{
LONG    rc;

        /*** 访问属性检查 ***/
        rc = LpxMonCheckAttrMdef( UnDefPtr, CheckType );
        if( rc != OK ){ return( rc );}

        /*** 获取监视数据，通过调用附带函数，其函数返回值为监视数据 ***/
        *ResData = UnDefPtr->FuncPtr( UnDefPtr );
        return(OK);
}

/**********************************************************************************************/
/* Function_Name: RpxMonSearchIdxOp         */ 
/* Description  : 根据功能码编号来进行相关的索引查找
                  调用：键盘操作中调用
                  输入：SrchNo：监控功能码编号，BaseIndex：搜索开始索引号
                  输出：   */
/**********************************************************************************************/
  USHORT    RpxMonSearchIdxOp( USHORT   SrchNo, USHORT  BaseIndex   )
{
LONG    rc;
LONG    idx;
LONG    idx_sv;

        if( (0xF000 & SrchNo) == 0xF000 )
        {
            SrchNo = 0;
        }
        else    // 访问寄存器地址范围检查，大于最大范围，则等于最大值
        {
            if( SrchNo > UnMonTbl[MonMngP.UnMonTblEntNum - 1].UnNo )
            {
                SrchNo = UnMonTbl[MonMngP.UnMonTblEntNum - 1].UnNo;
            }
        }

        /*** 前向索引 ***/
        if( SrchNo >= UnMonTbl[BaseIndex].UnNo )
        {
            for( idx = idx_sv = BaseIndex; idx < (LONG)MonMngP.UnMonTblEntNum; idx++ )
            {
                /*** 在有可选参数的情况下，在此进行检索处理 ***/
                rc = LpxMonCheckAttrIdx( idx, MCHK_DEF | MCHK_ACCS_LVL );   // 功能码属性检查：访问等级等检查
                if( rc != OK ){ continue;}
            /*--------------------------------------------------------------------------------------*/
                if( UnMonTbl[idx].UnNo > MONDEF_MAX_UnNO )
                {
                    return( (USHORT)idx_sv );   // 检索index功能码编号大于最大编号，则返回当前idx_sv
                }
                else if( UnMonTbl[idx].UnNo == SrchNo )
                {
                    return( (USHORT)idx );      // 检索index功能码编号等于目标编号。则返回检索index
                }
                else if( UnMonTbl[idx].UnNo > SrchNo )
                {
                    return( (USHORT)idx );      // 检索index功能码编号大于目标编号。则返回检索index
                }
                else
                {
                    idx_sv = idx;               // 检索index功能码编号小于目标编号。idx_sv = idx
                }
            }
        }

        /*** 前后索引 ***/
        else
        {
            for( idx = idx_sv = BaseIndex; idx >= 0; idx-- )
            {
                /*** 在有可选参数的情况下，在此进行检索处理 ***/
                rc = LpxMonCheckAttrIdx( idx, MCHK_DEF | MCHK_ACCS_LVL );   // 功能码属性检查：访问等级等检查
                if( rc != OK ){ continue;}
            /*--------------------------------------------------------------------------------------*/
                if( UnMonTbl[idx].UnNo == SrchNo )
                {
                    return( (USHORT)idx );  // 检索index功能码编号等于目标编号。则返回检索index
                }
                else if( UnMonTbl[idx].UnNo < SrchNo )
                {
                    return( (USHORT)idx );  // 检索index功能码编号小于目标编号。则返回检索index
                }
                else
                {
                    idx_sv = idx;           // 检索index功能码编号大于目标编号。idx_sv = idx
                }
            }
        }
/*--------------------------------------------------------------------------------------------------*/
        return( (USHORT)idx_sv );

}

/**********************************************************************************************/
/* Function_Name: LpxMonCheckAttrIdx         */ 
/* Description  : 根据由CheckType决定的条件，检查指定的监视变量是否妥当
                  调用：需要时调用
                  输入：Index：监视变量表index，CheckType：检查类型
                  输出：检查状态   */
/**********************************************************************************************/
LONG    LpxMonCheckAttrIdx( LONG    Index, UCHAR    CheckType   )
{
        LONG    rc = OK ;

        /*** 索引合法性检查 ***/
        if( Index >= (LONG)MonMngP.UnMonTblEntNum )
        {
            return( MERR_NO );
		}
/*--------------------------------------------------------------------------------------------------*/
        /*** 监视功能码属性检查 ***/
        rc = LpxMonCheckAttrMdef((MONDEF *)UnMonTbl[Index].MonDefPtr, CheckType) ;
/*--------------------------------------------------------------------------------------------------*/
        return(rc);

}

/**********************************************************************************************/
/* Function_Name: LpxMonCheckAttrMdef         */ 
/* Description  : 根据由CheckType决定的条件，检查指定的监视变量是否妥当
                  调用：需要时调用
                  输入：MondefPtr：监视变量结构体指针，CheckType：检查类型
                  输出：检查状态   */
/**********************************************************************************************/
LONG    LpxMonCheckAttrMdef( MONDEF *MondefPtr,  UCHAR  CheckType       )
{
  
//     // 待完善
//      if( CheckType & MCHK_ACCS_LVL )
//      {
//          if( (MondefPtr->AccessLevel) > Access.level )
//          {
//              return( MERR_LEVEL );
//          }
//      }

        if( CheckType & MCHK_MTR_TYPE )     // 专用检查
        {
            //if(( MondefPtr->ChkSpUse & Bprm.ChkSpUse) == 0x00 )
            if(( MondefPtr->ChkSpUse & KPI_CHKSPUSE_COMMON ) == 0x00)
            {
                return( MERR_CHKSPUSE );

            }
        }

        return(OK);
}


/**********************************************************************************************/
/* Function_Name: LpxMonSearchRegIdx         */ 
/* Description  : 根据RegNo来获取查找监控功能码对应的表格中索引号index，并检查监控功能码属性
                  调用：需要时调用
                  输入：RegNo：寄存器编号，FindIndex：索引搜索结果，CheckType：错误检查类型
                  输出：FindIndex：搜索结果索引，检查状态  */
/**********************************************************************************************/
#define MREGERR_NO      0x0011

LONG    LpxMonSearchRegIdx( LONG    RegNo, USHORT   *FindIndex, UCHAR   CheckType   )
{
LONG    i,w;
LONG    EntNum = MonMngP.UnRegTblEntNum;    // 通讯用Un寄存器总个数

        /*** 设置搜索开始索引 
        注意：这里的初始值计算是每次进行的，而Fn、机型信息的索引初始值是在初始化完成的，那样更优化 ***/

        /*** 二分查找基点;这个基点采用的是数组index的二进制最高位对应数字 ***/
        w = (1UL << MlibSrhbiton( EntNum - 1, SRH_FROM_MSB ));  // 分割宽度初始值设定

        /*** 若编号小于对应功能码编号，则i = 0，后续在0和基点间采用二分法不断逼近目标值；若大于，
        则i = EntNum-w，后续在EntNum-w和EntNum之间采用二分法不断逼近目标。由于基点肯定是大于等于
        EntNum/2的，所以在Rno >= FunOpeRegDefTbl[w].Rno情况下，在EntNum-w和EntNum之间采用二分法
        肯定是可以逼近目标的。 ***/
        i = ( RegNo >= UnRegTbl[w].UnNo )? (EntNum - w) : 0;    // 搜索开始索引设置
        
        /*** 监视器表格检索：此方法效率更高一些，比较好的二分法实现方式 ***/
        for( w = w>>1; w > 0; w = w>>1 )
        {
            if( RegNo >= UnRegTbl[i+w].UnNo ){ i = i + w;}
        }
        
        /*** 检索结果处理 ***/
        if( RegNo != UnRegTbl[i+w].UnNo )
        {
            return( MREGERR_NO );       // 编号不一致，错误返回
        }
        else
        {
            *FindIndex = (USHORT)i;     // 检索结果索引存储
        }

        /*** 监控属性检查:访问等级检查 ***/
        if( LpxMonCheckAttrMdef( (MONDEF *)UnRegTbl[i].MonDefPtr, CheckType ) == OK )
        {
            return( OK );
        }
        else
        {
            return( MREGERR_NO );
        }

}

/**********************************************************************************************/
/* Function_Name: LpxReadMonRegister         */ 
/* Description  : 监视器寄存器读取
                  调用：需要时调用
                  输入：FindIndex：寄存器表index，ResData：读取结果指针，CheckType：错误检查类型
                  输出：ResData：读取结果，读取状态  */
/**********************************************************************************************/
LONG    LpxReadMonRegister( USHORT  FindIndex, ULONG    *ResData, UCHAR CheckType   )
{
    MONDEF  *UnDefPtr;
    LONG    rc;

        /*** index合法性检查 ***/
        if( FindIndex >= MonMngP.UnRegTblEntNum )
        {
            return( REGIF_REGNOERR );
        }

        /*** 访问属性检查 ***/
        rc = LpxMonCheckAttrMdef( (MONDEF *)UnRegTbl[FindIndex].MonDefPtr, CheckType ) ;
        /*** 检查不通过，若仅仅是MERR_CHKSPUSE错误，返回0数据，否则返回错误 ***/
        if( rc != OK)
        {
            if( rc != MERR_CHKSPUSE)    return( REGIF_REGNOERR );
            *ResData = 0 ;
            return( OK );
        }

        UnDefPtr = (MONDEF *)UnRegTbl[FindIndex].MonDefPtr;
        *ResData = UnDefPtr->FuncPtr( UnDefPtr );   // 监视器数据运算函数，返回读取结果
        return( OK );

}



/**********************************************************************************************/
/* Function_Name: RpxReadMonRegister         */ 
/* Description  : 监视器寄存器读取函数
                  调用：需要时调用
                  输入：RegNo：寄存器编号，Number：读取个数，RdBuf：读取结果指针，Hmsg：访问句柄
                  输出：RdBuf：读取结果，读取状态    */
/**********************************************************************************************/
LONG    RpxReadMonRegister( LONG    RegNo, LONG Number, USHORT  *RdBuf, HMSGIF  Hmsg )
{
    LONG    i;
    LONG    j;
    ULONG   UnData;
    USHORT  FindIndex;

        /*** 根据RegNo来获取查找监控功能码对应的表格中索引号index，并检查监控功能码属性 ***/
        if( LpxMonSearchRegIdx( (RegNo & 0x0FFF), &FindIndex, MCHK_ACCS_LVL ) != OK )
        {
            Hmsg->ErrRno = (USHORT)RegNo;           // 异常寄存器编号
            return( REGIF_REGNOERR );
		}

        /*** 从指定寄存器号读取指定尺寸 ***/
        for( i = 0, j = 0; i < Number; j++ )
        {
//          if( LpxReadMonRegister( (USHORT)(FindIndex+j), &UnData, MCHK_ACCS_LVL ) != OK )             /* <V040> */

            /*** 监视器寄存器读取 ***/
            if( LpxReadMonRegister( (USHORT)(FindIndex+j), &UnData, MCHK_DEF | MCHK_ACCS_LVL ) != OK )  /* <V040> */
            {
                Hmsg->ErrRno = (USHORT)(RegNo + i);
                return( REGIF_REGNOERR );           // 寄存器号异常
			}
            /***
            监视寄存器是按照16/32bit进行组织的，根据参数地址访问16/32bit数据。32bit数据占用的是1个
            寄存器地址，而之前的Pn和Fn都采用的2个寄存器地址。参数属性中的IsLong用来表征是32bit还是
            16bit，这里由于没有使用两个16bit参数表征一个32bit参数，自然没有了完整性检验的问题。
            modbusRTU的地址表征的是16bit数据单元地址，这样便和监视寄存器32bit地址表征单元大小不一致
            。鉴于这种组织方式，也就自然没有了每次读写时的连续地址检验。因为地址无法连续。
            Un组参数：对32bit寄存器，读取完成后形成应答数据时，是根据Pn087中32bit寄存器高低位配置，
            来确定两个字的排放位置。
            ***/
            if( UnRegTbl[FindIndex+j].MonDefPtr->IsLong != TRUE )
            {
                RdBuf[i++] = (UnData >> 8) & 0x00FF;
                RdBuf[i++] = UnData & 0x00FF;
            }
        /*------------------------------------------------------------------------------------------*/
        /*      LONG Register                                                                       */
        /*------------------------------------------------------------------------------------------*/
            else
            {
                /*** 32bit数据，地址还是加1，但是数据个数是加2，相当于一个地址可以对应16或32bit ***/
                if( (i+1) < Number )
                {
                    if( ( Prm.addmapEn & 0xF000 ) == 0x0000 )
                    {
                        RdBuf[2*i+0] = (USHORT)( (UnData >> 8 ) & 0x00FF);
                        RdBuf[2*i+1] = (USHORT)( (UnData >> 0 ) & 0x00FF);

                        RdBuf[2*i+2] = (USHORT)( (UnData >> 24) & 0x00FF);
                        RdBuf[2*i+3] = (USHORT)( (UnData >> 16) & 0x00FF);
                    }
                    else
                    {
                        RdBuf[2*i+2] = (USHORT)( (UnData >> 8 ) & 0x00FF);
                        RdBuf[2*i+3] = (USHORT)( (UnData >> 0 ) & 0x00FF);

                        RdBuf[2*i+0] = (USHORT)( (UnData >> 24) & 0x00FF);
                        RdBuf[2*i+1] = (USHORT)( (UnData >> 16) & 0x00FF);
                    }
                    
                    i = i + 2;
                }
                else
                {
                    Hmsg->ErrRno = (USHORT)(RegNo + i);
                    return( REGIF_DAMTHERR );       // 数据匹配异常(LONG边界)
                }
            }
        }
/*--------------------------------------------------------------------------------------------*/
        return(OK);
}


/**********************************************************************************************/
/* Function_Name: RpiMonSearch         */ 
/* Description  : 根据功能码编号来进行相关的索引查找
                  调用：键盘操作中调用
                  输入：SrchNo：监控功能码编号， BaseIndex：搜索开始索引号，
                        FindIndex：索引搜索结果，CheckType：错误检查类型
                  输出：FindIndex：索引搜索结果，检索状态  */
/**********************************************************************************************/
LONG    RpiMonSearch( USHORT    SrchNo, USHORT  BaseIndex, USHORT *FindIndex, UCHAR CheckType )
{
    LONG    rc;
    LONG    idx;
    LONG    idx_sv;

    /*** 向前检索 ***/
    if( SrchNo >= UnMonTbl[BaseIndex].UnNo )
    {
        for( idx = idx_sv = BaseIndex; idx < (LONG)MonMngP.UnMonTblEntNum; idx++ )
        {
            /*** 在有可选参数的情况下，在此进行检索处理 ***/
            rc = LpxMonCheckAttrIdx( idx, MCHK_DEF | CheckType );   // 功能码属性检查
            if( rc != OK ){ continue;}
        /*--------------------------------------------------------------------------------------*/
            if( UnMonTbl[idx].UnNo == SrchNo )
            {
                *FindIndex = (USHORT)idx;   // 检索index功能码编号等于目标编号。则返回检索index
                return( OK );
            }
            else if( UnMonTbl[idx].UnNo > SrchNo )
            {
                *FindIndex = (USHORT)idx;   // 检索index功能码编号大于目标编号。则返回检索index 
                return( MERR_NO );
            }
            else
            {
                idx_sv = idx;               // 检索index功能码编号小于目标编号。idx_sv = idx
            }
        }
    }

    /*** 向后检索 ***/
    else
    {
        for( idx = idx_sv = BaseIndex; idx >= 0; idx-- )
        {
            /*** 在有可选参数的情况下，在此进行检索处理 ***/
            rc = LpxMonCheckAttrIdx( idx, MCHK_DEF | CheckType );   // 功能码属性检查
            if( rc != OK ){ continue;}
        /*--------------------------------------------------------------------------------------*/
            if( UnMonTbl[idx].UnNo == SrchNo )
            {
                *FindIndex = (USHORT)idx;   // 检索index功能码编号等于目标编号。则返回检索index
                return( OK );
            }
            else if( UnMonTbl[idx].UnNo < SrchNo )
            {
                *FindIndex = (USHORT)idx;   // 检索index功能码编号小于目标编号。则返回检索index
                return( MERR_NO );
            }
            else
            {
                idx_sv = idx;               // 检索index功能码编号大于目标编号。idx_sv = idx
            }
        }
    }
/*--------------------------------------------------------------------------------------------------*/
    *FindIndex = (USHORT)idx_sv;
    return( MERR_NO );
}



/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/
