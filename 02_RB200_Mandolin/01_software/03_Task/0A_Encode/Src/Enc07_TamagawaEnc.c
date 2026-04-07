  
  
  
  
  
 #include "Main.h"
#include "PM_tformat_include.h"
 
  
  
 SHORT TamagawaEeprom_DataReadDeal( void)
{
UCHAR i = 0;
USHORT RdataL;
USHORT RdataH;
    for(i = 0; i < EncEepromDataNum ;i++)
    {
        if( 0 == TFormat_ReadByte( 2 * i + 0 ))
        {
            return (-1);
        }
        RdataL = tformatData.eepromRdDataField;
         if( 0 == TFormat_ReadByte( 2 * i + 1 ))
        {
            return (-1);
        }
        RdataH = tformatData.eepromRdDataField;
         EncCodeV.ENCDataBuf[i] = (RdataH << 8) + RdataL;
         KlibWaitms( 2 );
	}
 	 
 	 
	if( 1 == EncEepExplain() )
    {
        return (1);
    }
	else
    {
        return (2);
    }
}
  
  
 UCHAR TamakawaMencClrStep(void)
{
UCHAR rc = 0;
	switch(EncCodeV.MEncClrStep)
	{
 	  	 
 		case 0:
            EncCodeV.MEncClrCnt = 0;
			EncCodeV.MEncClrStep ++;
			break;
 		 
 		case 1:
		  	if(EncCodeV.MEncClrCnt < 10)         
			{
		  	    EncErrorClr_Cmd( );
		  	    EncCodeV.MEncClrStep ++;
			}
			else
			{
			    EncCodeV.MEncClrStep = 3;
			}
	  		break;
 		 
 		case 2:
		    if( 1 == EncErrClr_Check( ) )
		    {
	            EncCodeV.MEncClrCnt ++;
	            EncCodeV.MEncClrStep = 1;
		    }
		    else
		    {
	            EncCodeV.MEncClrStep = 1;
		    }
 			break;
		case 3:
 			rc = 1;
			break;
		default:
			break;
	}
	return rc;
}
  
  
 void TamagawaEncWriteMnge(void)
{
uint16_t Data;
uint16_t Addr;
    switch(EncCodeV.ABSEncWriteStep)
    {
         case 0:
            if(EncCodeV.DataWriteToEeprom == 0x0001)
            {               
                EncCodeV.ABSEncWriteStep ++;     
            }
            break;
         case 1:
              
             EncEepBufPackage( );
             EncCodeV.ABSEncWriteCnt = 0;
            EncCodeV.ABSEncWriteDelyCnt = 0;
            EncCodeV.ABSEncWriteStep ++;                             
             break;
         case 2:
            if( EncCodeV.ABSEncWriteCnt < EncEepromDataNum)
            {
                 EncCodeV.ABSEncWriteDelyCnt = 0;
                Data = (EncCodeV.ENCDataBuf[EncCodeV.ABSEncWriteCnt]) & 0x00FF;
                Addr = 2UL * EncCodeV.ABSEncWriteCnt;
                TFormat_WriteByteCmd( Addr, Data);
                EncCodeV.ABSEncWriteStep += 1;
            }
            else
            {
 				EncCodeV.ABSEncWriteStep = 8;
             }
            break;
 		case 3:
            if(1 == TFormat_WriteByteCheck() )
            {
   				EncCodeV.ABSEncWriteDelyCnt = 0;
                EncCodeV.ABSEncWriteStep ++;
            }
            else
            {
                EncCodeV.ABSEncWriteStep =2;
            }
            break;
 		case 4:
		    if( ++EncCodeV.ABSEncWriteDelyCnt > 10 )
		    {
                EncCodeV.ABSEncWriteDelyCnt = 0;
                EncCodeV.ABSEncWriteStep ++;
		    }
		    break;
		case 5:
            Data = ((EncCodeV.ENCDataBuf[EncCodeV.ABSEncWriteCnt]) >> 8) & 0x00FF;
            Addr = 2UL * EncCodeV.ABSEncWriteCnt + 1;
		    TFormat_WriteByteCmd( Addr,Data);
			EncCodeV.ABSEncWriteStep ++;
			break;
 		case 6:
		    if(1 == TFormat_WriteByteCheck() )
            {
   				EncCodeV.ABSEncWriteDelyCnt = 0;
   				EncCodeV.ABSEncWriteStep ++;
            }
		    else
		    {
		        EncCodeV.ABSEncWriteStep = 5;                
		    }
            break;
         case 7:
            if( ++EncCodeV.ABSEncWriteDelyCnt > 10 )
            {
                EncCodeV.ABSEncWriteCnt += 1;                
                EncCodeV.ABSEncWriteStep = 2;
            }
            break;
         case 8:
            EncCodeV.DataWriteToEeprom = 0x0000;                  
			EncCodeV.ABSEncWriteStep = 0;
            break;
        default:
		  	EncCodeV.ABSEncWriteStep = 0;
            break;
    }
}
