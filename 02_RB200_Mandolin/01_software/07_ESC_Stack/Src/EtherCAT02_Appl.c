/*
* This source file is part of the EtherCAT Slave Stack Code licensed by Beckhoff Automation GmbH & Co KG, 33415 Verl, Germany.
* The corresponding license agreement applies. This hint shall not be removed.
*/

/**
\addtogroup CiA402appl CiA402 Sample Application
@{
*/

/**
\file cia402appl.c
\author EthercatSSC@beckhoff.com
\brief Implementation
This file contains all ciA402 specific functions

\version 5.12

<br>Changes to version V5.11:<br>
V5.12 COE3: update entry access right handling<br>
<br>Changes to version V5.10:<br>
V5.11 ECAT11: create application interface function pointer, add eeprom emulation interface functions<br>
<br>Changes to version V5.01:<br>
V5.10 CIA402 1: Update complete access handling for 0xF030<br>
V5.10 ECAT6: Add "USE_DEFAULT_MAIN" to enable or disable the main function<br>
<br>Changes to version V5.0:<br>
V5.01 ESC2: Add missed value swapping<br>
<br>Changes to version V4.40:<br>
V5.0 CIA402 1: Syntax bugfix in dummy motion controller<br>
V5.0 CIA402 2: Handle 0xF030/0xF050 in correlation do PDO assign/mapping objects<br>
V5.0 CIA402 3: Trigger dummy motion controller if valid mode of operation is set.<br>
V5.0 CIA402 4: Change Axes structure handling and resources allocation.<br>
V5.0 ECAT2: Create generic application interface functions. Documentation in Application Note ET9300.<br>
<br>Changes to version V4.30:<br>
V4.40 CoE 6: add AL Status code to Init functions<br>
V4.40 CIA402 2: set motion control trigger depending on "Synchronisation", "mode of operation" and "cycle time"<br>
V4.40 CIA402 1: change behaviour and name of bit12 of the status word (0x6041) (WG CIA402 24.02.2010)<br>
V4.30 : create file (state machine; handling state transition options; input feedback)
*/

/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"
#include "applInterface.h"
#include "EtherCAT03_ObjDef.h"

#define _CiA402_
#include "EtherCAT02_Appl.h"
#undef _CiA402_

#include "EtherCAT08_2000Rw.h"

/*--------------------------------------------------------------------------------------
------
------    local types and defines
------
--------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    local variables and constants
------
-----------------------------------------------------------------------------------------*/


typedef struct
{
    UINT16 byteFlag;
    UINT32 Address;
}PDOMAP_ATTRIBUTE;

PDOMAP_ATTRIBUTE PDO1AXX_MapAddr[40];
PDOMAP_ATTRIBUTE PDO16XX_MapAddr[40];

INT16 AddressNum = 0;           //@20250521 计算PDO16XX_MapAddr.Address的个数

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param     index                 index of the requested object.
 \param     subindex                subindex of the requested object.
 \param     dataSize                received data size of the SDO Download
 \param     pObjEntry            handle to the dictionary object returned by
                                     OBJ_GetObjectHandle which was called before
 \param    pData                    Pointer to the buffer where the written data can be copied from
 \param    bCompleteAccess    Indicates if a complete write of all subindices of the
                                     object shall be done or not

 \return    result of the write operation (0 (success) or an abort code (ABORTIDX_.... defined in
            sdosrv.h))

 \brief    This function writes "Configured Modules" Object 0xF030
*////////////////////////////////////////////////////////////////////////////////////////

UINT8 Write0xF030( UINT16 index, UINT8 subindex, UINT32 dataSize, UINT16 MBXMEM * pData, UINT8 bCompleteAccess )
{

    UINT16 i = subindex;
    UINT16 maxSubindex = sConfiguredModuleIdentList.u16SubIndex0;
    OBJCONST TSDOINFOENTRYDESC OBJMEM *pEntry;
    /* lastSubindex is used for complete access to make loop over the requested entries
       to be read, we initialize this variable with the requested subindex that only
       one loop will be done for a single access */
    UINT8 lastSubindex = subindex;

    if ( bCompleteAccess )
    {
        if ( subindex == 0 )
        {
            /* we change the subindex 0 */
            maxSubindex = (UINT8) pData[0];
        }

        /* we write until the maximum subindex */
        lastSubindex = (UINT8)maxSubindex;
    }
    else
        if (subindex > maxSubindex)
        {
            /* the maximum subindex is reached */
            return ABORTIDX_SUBINDEX_NOT_EXISTING;
        }
    else
    {
        /* we check the write access for single accesses here, a complete write access
           is allowed if at least one entry is writable (in this case the values for the
            read only entries shall be ignored) */
        /* we get the corresponding entry description */
        pEntry = &asEntryDesc0xF030[subindex];

        /* check if we have write access (bits 3-5 (PREOP, SAFEOP, OP) of ObjAccess)
           by comparing with the actual state (bits 1-3 (PREOP, SAFEOP, OP) of AL Status) */
/*ECATCHANGE_START(V5.12) COE3*/
        if (0 == (((UINT8) ((pEntry->ObjAccess & ACCESS_WRITE) >> 2)) & (nAlStatus & STATE_MASK) ))
/*ECATCHANGE_END(V5.12) COE3*/
        {
            /* we don't have write access */
            if ( (pEntry->ObjAccess & ACCESS_WRITE) == 0 )
            {
                /* it is a read only entry */
                return ABORTIDX_READ_ONLY_ENTRY;
            }
            else
            {
                /* we don't have write access in this state */
                return ABORTIDX_IN_THIS_STATE_DATA_CANNOT_BE_READ_OR_STORED;
            }
        }
    }

        /* we use the standard write function */
        for (i = subindex; i <= lastSubindex; i++)
        {
            /* we have to copy the entry */
            if (i == 0)
            {
                /*check if the value for subindex0 is valid */
                if(MAX_AXES < (UINT8) pData[0])
                {
                    return ABORTIDX_VALUE_TOO_GREAT;
                }

                sConfiguredModuleIdentList.u16SubIndex0 =  pData[0];

                /* we increment the destination pointer by 2 because the subindex 0 will be
                    transmitted as UINT16 for a complete access */
                pData++;
            }
            else
            {
                UINT32 CurValue = sConfiguredModuleIdentList.aEntries[(i-1)];
                UINT16 MBXMEM *pVarPtr = (UINT16 MBXMEM *) &sConfiguredModuleIdentList.aEntries[(i-1)];

                pVarPtr[0] = pData[0];
                pVarPtr[1] = pData[1];
                pData += 2;

                /*Check if valid value was written*/
                if((sConfiguredModuleIdentList.aEntries[(i-1)] != (UINT32)CSV_CSP_MODULE_ID)
                && (sConfiguredModuleIdentList.aEntries[(i-1)] != (UINT32)CSP_MODULE_ID)
                && (sConfiguredModuleIdentList.aEntries[(i-1)] != (UINT32)CSV_MODULE_ID)
                && (sConfiguredModuleIdentList.aEntries[(i-1)] != 0))
                {
                    /*write previous value*/
                    sConfiguredModuleIdentList.aEntries[(i-1)] = CurValue;

                    /*reset subindex 0 (if required)*/
                    if(sConfiguredModuleIdentList.aEntries[(i-1)] != 0)
                    {
                        sConfiguredModuleIdentList.u16SubIndex0 = i;
                    }
                    else
                    {
                        /*current entry is 0 => set subindex0 value i-1*/
                        sConfiguredModuleIdentList.u16SubIndex0 = (i-1);
                    }


                    return ABORTIDX_VALUE_EXCEEDED;
                }
           }
        }

        /*Update PDO assign objects and 0xF010 (Module Profile List)*/
        {
        UINT8 cnt = 0;

        /*Update 0xF010.0 */
        sModuleProfileInfo.u16SubIndex0 = sConfiguredModuleIdentList.u16SubIndex0;
        
        /*Update PDO assign SI0*/
        sRxPDOassign.u16SubIndex0 = sConfiguredModuleIdentList.u16SubIndex0;
        sTxPDOassign.u16SubIndex0 = sConfiguredModuleIdentList.u16SubIndex0;

        for (cnt = 0 ; cnt < sConfiguredModuleIdentList.u16SubIndex0; cnt++)
        {
            /*all Modules have the same profile number*/
            sModuleProfileInfo.aEntries[cnt] = DEVICE_PROFILE_TYPE;

            switch(sConfiguredModuleIdentList.aEntries[cnt])
            {
                case CSV_CSP_MODULE_ID:
                    sRxPDOassign.aEntries[cnt] = (0x1600 +(0x10*cnt));
                    sTxPDOassign.aEntries[cnt] = (0x1A00 +(0x10*cnt));
                break;
                case CSP_MODULE_ID:
                    sRxPDOassign.aEntries[cnt] = (0x1601 +(0x10*cnt));
                    sTxPDOassign.aEntries[cnt] = (0x1A01 +(0x10*cnt));
                break;
                case CSV_MODULE_ID:
                    sRxPDOassign.aEntries[cnt] = (0x1602 +(0x10*cnt));
                    sTxPDOassign.aEntries[cnt] = (0x1A02 +(0x10*cnt));
                break;
                default:
                    sRxPDOassign.aEntries[cnt] = 0;
                    sTxPDOassign.aEntries[cnt] = 0;

                    sModuleProfileInfo.aEntries[cnt] = 0;
                break;
            }
        }
        }

    return 0;
}

/*-----------------------------------------------------------------------------------------
------
------    generic functions
------
-----------------------------------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    The function is called when an error state was acknowledged by the master

*////////////////////////////////////////////////////////////////////////////////////////

void    APPL_AckErrorInd(UINT16 stateTrans)
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from INIT to PREOP when
           all general settings were checked to start the mailbox handler. This function
           informs the application about the state transition, the application can refuse
           the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from PREEOP to INIT
           to stop the mailbox handler. This functions informs the application
           about the state transition, the application cannot refuse
           the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param    pIntMask    pointer to the AL Event Mask which will be written to the AL event Mask
                        register (0x204) when this function is succeeded. The event mask can be adapted
                        in this function
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from PREOP to SAFEOP when
             all general settings were checked to start the input handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
            The return code NOERROR_INWORK can be used, if the application cannot confirm
            the state transition immediately, in that case the application need to be complete 
            the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartInputHandler(UINT16 *pIntMask)
{
    UINT32 Sync0CycleTime = 0;
    if(sConfiguredModuleIdentList.u16SubIndex0 == 0)
    {
        /* Object 0xF030 was not written before 
        * => update object 0xF010 (Module profile list) and 0xF050 (Detected Module List)*/
    
        UINT8 cnt = 0;


        /*Update 0xF010.0 */
        sModuleProfileInfo.u16SubIndex0 = sRxPDOassign.u16SubIndex0;

        /*Update 0xF050.0*/
        sDetectedModuleIdentList.u16SubIndex0 = sRxPDOassign.u16SubIndex0;
        
        for (cnt = 0 ; cnt < sRxPDOassign.u16SubIndex0; cnt++)
        {
            /*all Modules have the same profile number*/
            sModuleProfileInfo.aEntries[cnt] = DEVICE_PROFILE_TYPE;

            switch((sRxPDOassign.aEntries[cnt] & 0x000F)) //get only identification of the PDO mapping object
            {
                case 0x0:   //csv/csp PDO selected
                    sDetectedModuleIdentList.aEntries[cnt] = CSV_CSP_MODULE_ID;
                break;
                case 0x1:   //csp PDO selected
                    sDetectedModuleIdentList.aEntries[cnt] = CSP_MODULE_ID;
                break;
                case 0x2:   //csv PDO selected
                    sDetectedModuleIdentList.aEntries[cnt] = CSV_MODULE_ID;
                break;

            }
            
        }
    }

    HW_EscReadDWord(Sync0CycleTime, ESC_DC_SYNC0_CYCLETIME_OFFSET);
    Sync0CycleTime = SWAPDWORD(Sync0CycleTime);

    /*Init CiA402 structure if the device is in SM Sync mode
    the CiA402 structure will be Initialized after calculation of the Cycle time*/
    if(bDcSyncActive == TRUE)
    {
        Sync0CycleTime = Sync0CycleTime / 1000; //get cycle time in us
    }

    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from SAFEOP to PREEOP
             to stop the input handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopInputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from SAFEOP to OP when
             all general settings were checked to start the output handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from OP to SAFEOP
             to stop the output handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

//*************************************************************************************************
//
//PDO 映射 子索引检测
//
//*************************************************************************************************
USHORT PDOMapCheck( USHORT Index,USHORT SubIndex )
{
    //---------------------------------------------------------------------------------------------
    if( Index == 0x607D || Index == 0x6091 || Index == 0x6099 || Index == 0x60C1 || Index == 0x60C2 || Index == 0x60FE)
    {
        if( SubIndex == 0x0001 )
        {
            return 2;
        }
        else if( SubIndex == 0x0002 )
        {
            return 4;
        }
        else
        {
            return 0;
        }
    }
    else if( Index == 0x6100 )
    {
        return ( (USHORT)SubIndex << 1 );
    }
    //---------------------------------------------------------------------------------------------
    else
    {
        return 0;
    }
}

//*************************************************************************************************
//
//缓存PDO映射对象的数据的地址
//
//*************************************************************************************************
void PDOMap_Addr_Buffer( void )
{
    USHORT i = 0;
    USHORT j = 0;
    USHORT k = 0;
    const TOBJECT  * pObjEntry_PDO;
    USHORT  Index;
    USHORT  SubIndex;
    USHORT  DataLength;
    USHORT  AxisNum = 0;

    for( i = 0; i < 40; i ++ )
    {
        PDO1AXX_MapAddr[ i ].Address = 0;
        PDO16XX_MapAddr[ i ].Address = 0;
        PDO1AXX_MapAddr[ i ].byteFlag = 0;
        PDO16XX_MapAddr[ i ].byteFlag = 0;
    }

    //---------------------------------------------------------------------------------------------
    for(AxisNum = 0; AxisNum < sTxPDOassign.u16SubIndex0; AxisNum++)
    {
        switch (sTxPDOassign.aEntries[ AxisNum ])
        {
            case 0x1A00:
                for( i = 0; i < sTPDO1Map.u16SubIndex0; i++)
                {
                    Index = sTPDO1Map.aEntries[i] >> 16;                         //索引
                    SubIndex    = ( sTPDO1Map.aEntries[i] & 0xFF00 ) >> 8;       //子索引
                    DataLength = ( sTPDO1Map.aEntries[i] & 0x00FF ) >> 3;         //长度
                    pObjEntry_PDO = OBJ_GetObjectHandle(Index);
                    USHORT *pdata = (USHORT *) pObjEntry_PDO->pVarPtr;
                    if( Index != 0 )
                    {
                        //-------------------------------------------------------------------------
                        // 对于带子索引的对象字典时,在PDO映射时存在问题,需要对带子索引的对象字典进行特殊处理
                        // 带有子索引的对象字典的第一个子索引为子索引的对象,不对其进行映射
                        //-------------------------------------------------------------------------
                        if( (Index & 0xF000)!= 0x2000 )
                        {
                            if( SubIndex != 0)
                            {
                                //子索引
                                SubIndex =  PDOMapCheck( Index, SubIndex );
                            }
                            else
                            {
                                SubIndex = 0;
                            }
                            //-------------------------------------------------------------------------
                            if( DataLength == 1 )
                            {
                                PDO1AXX_MapAddr[k].byteFlag = 1;
                                PDO1AXX_MapAddr[k].Address = (UINT32)( pdata )+ 0 + SubIndex;
                                k++;
                            }
                            else if( DataLength == 2 )
                            {
                                PDO1AXX_MapAddr[k].byteFlag = 0;
                                PDO1AXX_MapAddr[k].Address = (UINT32)( pdata )+ 0 + SubIndex;
                                k++;
                            }
                            else
                            {
                                for( j = 0; j < (DataLength >> 1); j++ )
                                {
                                    PDO1AXX_MapAddr[k].byteFlag = 0;
                                    PDO1AXX_MapAddr[k].Address = (UINT32)( pdata )+ j + SubIndex;
                                    k++;
                                }
                            }
                        }
                        else
                        {

                            pdata = (USHORT *)UnMonTblAddress(Index, SubIndex);
                            //-------------------------------------------------------------------------
                            if( DataLength == 1 )
                            {
                                PDO1AXX_MapAddr[k].byteFlag = 1;
                                PDO1AXX_MapAddr[k].Address = (UINT32)( pdata );
                                k++;
                            }
                            else if( DataLength == 2 )
                            {
                                PDO1AXX_MapAddr[k].byteFlag = 0;
                                PDO1AXX_MapAddr[k].Address = (UINT32)( pdata );
                                k++;
                            }
                            else
                            {
                                for( j = 0; j < (DataLength >> 1); j++ )
                                {
                                    PDO1AXX_MapAddr[k].byteFlag = 0;
                                    PDO1AXX_MapAddr[k].Address = (UINT32)( pdata )+ j;
                                    k++;
                                }
                            }
                        }
                    }
                }
                break;
            case 0x1A10:
                for( i = 0; i < sTPDO2Map.u16SubIndex0; i++)
                {
                    Index = sTPDO2Map.aEntries[i] >> 16;                         //索引
                    SubIndex    = ( sTPDO2Map.aEntries[i] & 0xFF00 ) >> 8;       //子索引
                    DataLength = ( sTPDO2Map.aEntries[i] & 0x0FF ) >> 3;         //长度
                    pObjEntry_PDO = OBJ_GetObjectHandle(Index);
                    USHORT *pdata = (USHORT *) pObjEntry_PDO->pVarPtr;
                    if( Index != 0 )
                    {
                        //-------------------------------------------------------------------------
                        // 对于带子索引的对象字典时,在PDO映射时存在问题,需要对带子索引的对象字典进行特殊处理
                        // 带有子索引的对象字典的第一个子索引为子索引的对象,不对其进行映射
                        // 2018.08.07 下同
                        //-------------------------------------------------------------------------

                        if( (Index & 0xF000)!= 0x2000 )
                        {
                            if( SubIndex != 0)
                            {
                                //子索引
                                SubIndex =  PDOMapCheck( Index, SubIndex );
                            }
                            else
                            {
                                SubIndex = 0;
                            }

                            //-------------------------------------------------------------------------
                            if( DataLength == 1 )
                            {
                                PDO1AXX_MapAddr[k].byteFlag = 1;
                                PDO1AXX_MapAddr[k].Address = (UINT32)( pdata )+ 0x00001000 + SubIndex;
                                k++;
                            }
                            else if( DataLength == 2 )
                            {
                                PDO1AXX_MapAddr[k].byteFlag = 0;
                                PDO1AXX_MapAddr[k].Address = (UINT32)( pdata )+ 0x00001000 + SubIndex;
                                k++;
                            }
                            else
                            {

                                for( j = 0; j < (DataLength >> 1); j++ )
                                {
                                    PDO1AXX_MapAddr[k].byteFlag = 0;
                                    PDO1AXX_MapAddr[k].Address = (UINT32)( pdata )+ j + 0x00001000 + SubIndex;
                                    k++;
                                }
                            }
                        }
                        else
                        {
                            pdata = (USHORT *)UnMonTblAddress(Index, SubIndex);
                            //-------------------------------------------------------------------------
                            if( DataLength == 1 )
                            {
                                PDO1AXX_MapAddr[k].byteFlag = 1;
                                PDO1AXX_MapAddr[k].Address = (UINT32)( pdata )+ 0x00001000 ;
                                k++;
                            }
                            else if( DataLength == 2 )
                            {
                                PDO1AXX_MapAddr[k].byteFlag = 0;
                                PDO1AXX_MapAddr[k].Address = (UINT32)( pdata )+ 0x00001000 ;
                                k++;
                            }
                            else
                            {

                                for( j = 0; j < (DataLength >> 1); j++ )
                                {
                                    PDO1AXX_MapAddr[k].byteFlag = 0;
                                    PDO1AXX_MapAddr[k].Address = (UINT32)( pdata )+ j + 0x00001000 ;
                                    k++;
                                }
                            }

                        }
                    }
                }
                break;
            default:
                break;
        }
    }
    k = 0;
    /*----------------------------------------------------------------------------------------------*/
    for(AxisNum = 0; AxisNum < sRxPDOassign.u16SubIndex0; AxisNum++)
    {
        switch( sRxPDOassign.aEntries[AxisNum] )
        {
            case 0x1600:
                    for( i = 0; i < sRPDO1Map.u16SubIndex0; i++)
                    {
                        Index = sRPDO1Map.aEntries[i] >> 16;                         //索引
                        SubIndex    = ( sRPDO1Map.aEntries[i] & 0xFF00 ) >> 8;       //子索引
                        DataLength = ( sRPDO1Map.aEntries[i] & 0x00FF ) >> 3;        //长度
                        pObjEntry_PDO = OBJ_GetObjectHandle(Index);
                        USHORT *pdata = (USHORT *) pObjEntry_PDO->pVarPtr;
                        if( Index != 0 )
                        {

                            if( (Index & 0xF000)!= 0x2000 )
                            {
                                if( SubIndex != 0)
                                {
                                    //子索引
                                    SubIndex = PDOMapCheck( Index, SubIndex );
                                }
                                else
                                {
                                    SubIndex = 0;
                                }
                                //-------------------------------------------------------------------------
                                if( DataLength == 1 )
                                {
                                    PDO16XX_MapAddr[k].byteFlag = 1;
                                    PDO16XX_MapAddr[k].Address = (UINT32)( pdata )+ 0 + SubIndex;
                                    k++;
                                }
                                else if(DataLength == 2 )
                                {
                                    PDO16XX_MapAddr[k].byteFlag = 0;
                                    PDO16XX_MapAddr[k].Address = (UINT32)( pdata )+ 0 + SubIndex;
                                    k++;
                                }
                                else
                                {
                                    for( j = 0; j < (DataLength >> 1); j++ )
                                    {
                                        PDO16XX_MapAddr[k].byteFlag = 0;
                                        PDO16XX_MapAddr[k].Address = (UINT32)( pdata )+ j + SubIndex;
                                        k++;
                                    }
                                }
                            }
                            else
                            {
                                pdata = UnPnTblAddress(Index, SubIndex);
//                                *pdata = (USHORT *) pObjEntry_PDO->pVarPtr;
                                //-------------------------------------------------------------------------
                                if( DataLength == 1 )
                                {
                                    PDO16XX_MapAddr[k].byteFlag = 1;
                                    PDO16XX_MapAddr[k].Address = (UINT32)( pdata );
                                    k++;
                                }
                                else if(DataLength == 2 )
                                {
                                    PDO16XX_MapAddr[k].byteFlag = 0;
                                    PDO16XX_MapAddr[k].Address = (UINT32)( pdata );
                                    k++;
                                }
                                else
                                {
                                    for( j = 0; j < (DataLength >> 1); j++ )
                                    {
                                        PDO16XX_MapAddr[k].byteFlag = 0;
                                        PDO16XX_MapAddr[k].Address = (UINT32)( pdata )+ j ;
                                        k++;
                                    }
                                }
                            }
                        }
                    }
                 break;
            case 0x1610:
                    for( i = 0; i < sRPDO2Map.u16SubIndex0; i++)
                    {
                        Index = sRPDO2Map.aEntries[i] >> 16;                         //索引
                        SubIndex    = ( sRPDO2Map.aEntries[i] & 0xFF00 ) >> 8;       //子索引
                        DataLength = ( sRPDO2Map.aEntries[i] & 0x0FF ) >> 3;         //长度
                        pObjEntry_PDO = OBJ_GetObjectHandle(Index);
                        USHORT *pdata = (USHORT *) pObjEntry_PDO->pVarPtr;
                        if( Index != 0 )
                        {
                            if( SubIndex != 0)
                            {
                                //子索引
                                SubIndex = PDOMapCheck( Index, SubIndex );
                            }
                            else
                            {
                                SubIndex = 0;
                            }
                            if( (Index & 0xF000)!= 0x2000 )
                            {
                                //-------------------------------------------------------------------------
                                if( DataLength == 1 )
                                {
                                    PDO16XX_MapAddr[k].byteFlag = 1;
                                    PDO16XX_MapAddr[k].Address = (UINT32)( pdata )+ 0 + SubIndex;
                                    k++;
                                }
                                else if(DataLength == 2 )
                                {
                                    PDO16XX_MapAddr[k].byteFlag = 0;
                                    PDO16XX_MapAddr[k].Address = (UINT32)( pdata )+ 0 + SubIndex;
                                    k++;
                                }
                                else
                                {
                                    for( j = 0; j < (DataLength >> 1); j++ )
                                    {
                                        PDO16XX_MapAddr[k].byteFlag = 0;
                                        PDO16XX_MapAddr[k].Address = (UINT32)( pdata )+ j + SubIndex;
                                        k++;
                                    }
                                }
                            }
                            else
                            {
                                pdata = UnPnTblAddress(Index, SubIndex);
                                //-------------------------------------------------------------------------
                                if( DataLength == 1 )
                                {
                                    PDO16XX_MapAddr[k].byteFlag = 1;
                                    PDO16XX_MapAddr[k].Address = (UINT32)( pdata );
                                    k++;
                                }
                                else if(DataLength == 2 )
                                {
                                    PDO16XX_MapAddr[k].byteFlag = 0;
                                    PDO16XX_MapAddr[k].Address = (UINT32)( pdata );
                                    k++;
                                }
                                else
                                {
                                    for( j = 0; j < (DataLength >> 1); j++ )
                                    {
                                        PDO16XX_MapAddr[k].byteFlag = 0;
                                        PDO16XX_MapAddr[k].Address = (UINT32)( pdata )+ j ;
                                        k++;
                                    }
                                }
                            }
                        }
                    }
                 break;
            default:
                  break;
        }
    }
    AddressNum = k;         //@20250521 计算PDO16XX_MapAddr.Address的个数
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0(ALSTATUSCODE_NOERROR), NOERROR_INWORK
\param      pInputSize  pointer to save the input process data length
\param      pOutputSize  pointer to save the output process data length

\brief    This function calculates the process data sizes from the actual SM-PDO-Assign
            and PDO mapping
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GenerateMapping(UINT16* pInputSize,UINT16* pOutputSize)
{
    UINT16 result = ALSTATUSCODE_NOERROR;
    UINT16 PDOAssignEntryCnt = 0;
    UINT16 u16cnt = 0;
    UINT16 InputSize = 0;
    UINT16 OutputSize = 0;

    if (sRxPDOassign.u16SubIndex0 > MAX_AXES)
    {
        return ALSTATUSCODE_NOVALIDOUTPUTS;
    }
    /*Scan object 0x1C12 RXPDO assign*/
    for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        switch ((sRxPDOassign.aEntries[PDOAssignEntryCnt] & 0x00FF))    //mask Axis type (supported modes)
        {
            case 0x0000:
                for(u16cnt =0 ; u16cnt < sRPDO1Map.u16SubIndex0;u16cnt++)
                {
                    OutputSize +=(UINT16)(sRPDO1Map.aEntries[u16cnt] & 0xFF);
                }
                break;
            case 0x0010:
                for(u16cnt =0 ; u16cnt < sRPDO2Map.u16SubIndex0;u16cnt++)
                {
                    OutputSize +=(UINT16)(sRPDO2Map.aEntries[u16cnt] & 0xFF);
                }
                break;
        }
    }

    OutputSize = OutputSize >> 3;

    if(result == 0)
    {
        /*Scan Object 0x1C13 TXPDO assign*/
        for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
        {
            switch ((sTxPDOassign.aEntries[PDOAssignEntryCnt] & 0x00FF))    //mask Axis type (supported modes)
            {
                case 0x0000:
                    for(u16cnt =0 ; u16cnt < sTPDO1Map.u16SubIndex0;u16cnt++)
                    {
                        InputSize +=(UINT16)(sTPDO1Map.aEntries[u16cnt] & 0xFF);
                    }
                    break;
                case 0x0010:
                    for(u16cnt =0 ; u16cnt < sTPDO2Map.u16SubIndex0;u16cnt++)
                    {
                        InputSize +=(UINT16)(sTPDO2Map.aEntries[u16cnt] & 0xFF);
                    }
                    break;
            }
        }
        
        InputSize = InputSize >> 3;
    }
    //---------------------------------------------------------------------------------------------
    PDOMap_Addr_Buffer( );      // PDO 映射
    //---------------------------------------------------------------------------------------------
    *pInputSize = InputSize;
    *pOutputSize = OutputSize;
    return result;
}






#ifdef RunRAM
#pragma CODE_SECTION(APPL_InputMapping, ".TI.ramfunc");
#endif
/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to input process data
\brief      This function will copies the inputs from the local memory to the ESC memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_InputMapping(UINT16* pData)
{
    UINT8 InByteBuf[ 68 ];
    UINT16 DataBuf;
    UINT16 ByteAddr = 0;
    UINT16 *localpdata;
    UINT16 j;

    UINT16 len = (nPdInputSize + 1) >> 1;

    for( j = 0; j < len; j++ )
    {
        localpdata = (UINT16 *)(PDO1AXX_MapAddr[ j ].Address);
        DataBuf = *localpdata;
        if( PDO1AXX_MapAddr[j].byteFlag == 0 )
        {
            InByteBuf[ ByteAddr + 0] = DataBuf & 0x00FF;
            InByteBuf[ ByteAddr + 1] = (DataBuf >> 8) & 0x00FF;
            ByteAddr += 2;
        }
        else
        {
            InByteBuf[ ByteAddr + 0] = DataBuf & 0x00FF;
            ByteAddr += 1;
        }
    }
    for( j = 0; j < len; j++ )
    {
        *pData++ = InByteBuf[ 2 * j + 0 ] + (((UINT16)InByteBuf[ 2 * j + 1 ]) << 8);
    }
}

#ifdef RunRAM
#pragma CODE_SECTION(APPL_OutputMapping, ".TI.ramfunc");
#endif
/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to output process data

\brief    This function will copies the outputs from the ESC memory to the local memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_OutputMapping(UINT16* pData)
{
    UINT16 j = 0;
//    UINT8 *pTmpData = (UINT8 *)pData;

    UINT8 OutByteBuf[ 68 ];
    UINT16 DataBuf;

    UINT16 *pdata;

    UINT16 ByteAddr = 0;

    UINT16 len = ( nPdOutputSize + 1 ) >> 1;

    for( j = 0; j < len; j++ )
    {
        DataBuf = *(pData + j);
        OutByteBuf[ 2 * j + 0] = DataBuf & 0x00FF;
        OutByteBuf[ 2 * j + 1] = (DataBuf >> 8) & 0x00FF;
    }

    for( j = 0; j < AddressNum; j++)
    {
        pdata = (UINT16 *)(PDO16XX_MapAddr[ j ].Address);

        if( PDO16XX_MapAddr[j].byteFlag == 0 )
        {
            *pdata = OutByteBuf[ ByteAddr + 0 ] + (((UINT16)OutByteBuf[ ByteAddr + 1 ]) << 8);
            ByteAddr += 2;
        }
        else
        {
            *pdata = OutByteBuf[ ByteAddr ];
            ByteAddr += 1;
        }
    }
}



