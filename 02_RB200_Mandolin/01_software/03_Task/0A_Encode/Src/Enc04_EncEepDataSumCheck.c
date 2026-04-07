  
  
  
  
  
 #include "Enc04_EncEepDataSumCheck.h"
 
 
  
  
  
UCHAR EncEepExplain(void)
{
USHORT i;
USHORT Sumx ;
      
 	for( Sumx=0, i=0; i<(EncEepromDataNum -1); i++ )
	{
		Sumx += EncCodeV.ENCDataBuf[i];
	}
 	i = 4;
  
 	if( (EncCodeV.ENCDataBuf[1] == 0x55AA) && (Sumx == 0) )
	{
 	     
    	Prm.typm_e.w        = EncCodeV.ENCDataBuf[i++];
    	Prm.encver          = EncCodeV.ENCDataBuf[i++];
    	Prm.motw            = EncCodeV.ENCDataBuf[i++];
    	Prm.bit_dp.w        = EncCodeV.ENCDataBuf[i++];
    	Prm.limmlt          = EncCodeV.ENCDataBuf[i++];
    	Prm.vrat_max.w      = EncCodeV.ENCDataBuf[i++];
    	Prm.oslv_pol.w      = EncCodeV.ENCDataBuf[i++];
    	Prm.rattrq          = EncCodeV.ENCDataBuf[i++];
    	Prm.maxtrq          = EncCodeV.ENCDataBuf[i++];
    	Prm.irat            = EncCodeV.ENCDataBuf[i++];
    	Prm.imax            = EncCodeV.ENCDataBuf[i++];
    	Prm.emfcmp          = EncCodeV.ENCDataBuf[i++];
    	Prm.jmot            = EncCodeV.ENCDataBuf[i++];
    	Prm.motr            = EncCodeV.ENCDataBuf[i++];
    	Prm.motl            = EncCodeV.ENCDataBuf[i++];
    	Prm.bastrq          = EncCodeV.ENCDataBuf[i++];
    	Prm.midtrq          = EncCodeV.ENCDataBuf[i++];
    	Prm.midolt          = EncCodeV.ENCDataBuf[i++];
    	Prm.mtrq2           = EncCodeV.ENCDataBuf[i++];
    	Prm.mtolt2          = EncCodeV.ENCDataBuf[i++];
    	Prm.phscmpM1        = EncCodeV.ENCDataBuf[i++];
    	Prm.ppitch          = EncCodeV.ENCDataBuf[i++];
    	Prm.motlq0          = EncCodeV.ENCDataBuf[i++];
    	Prm.motlq1          = EncCodeV.ENCDataBuf[i++];
    	Prm.exp_trat_jmot   = EncCodeV.ENCDataBuf[i++];
    	Prm.exp_motw_spd    = EncCodeV.ENCDataBuf[i++];
    	Prm.fbit_fdp        = EncCodeV.ENCDataBuf[i++];
    	Prm.poleoffset      = EncCodeV.ENCDataBuf[i++];
    	Prm.motresfrq       = EncCodeV.ENCDataBuf[i++];
    	Prm.phscmpM2        = EncCodeV.ENCDataBuf[i++];
    	Prm.flg_wf          = EncCodeV.ENCDataBuf[i++];
		return (1);
	}
	else 
	{
	    return (0);
	}
}
 /***************************************************************************************************
                            读取当前调用的数据保存至尼康编码器写入的Buf中
                                 只是将当前F阻的参数写入到Eeprom中
****************************************************************************************************/
void EncEepBufPackage(void)
{
UCHAR i = 1;
USHORT Sumx;
    EncCodeV.ENCDataBuf[i++] = 0x55AA;               
    EncCodeV.ENCDataBuf[i++] = Prm.MotorNum;         
    EncCodeV.ENCDataBuf[i++] = Prm.EncoderType;      
    EncCodeV.ENCDataBuf[i++] = Prm.typm_e.w;         
    EncCodeV.ENCDataBuf[i++] = Prm.encver;           
    EncCodeV.ENCDataBuf[i++] = Prm.motw;             
    EncCodeV.ENCDataBuf[i++] = Prm.bit_dp.w;         
    EncCodeV.ENCDataBuf[i++] = Prm.limmlt;           
    EncCodeV.ENCDataBuf[i++] = Prm.vrat_max.w;       
    EncCodeV.ENCDataBuf[i++] = Prm.oslv_pol.w;       
    EncCodeV.ENCDataBuf[i++] = Prm.rattrq;           
    EncCodeV.ENCDataBuf[i++] = Prm.maxtrq;           
    EncCodeV.ENCDataBuf[i++] = Prm.irat;             
    EncCodeV.ENCDataBuf[i++] = Prm.imax;             
    EncCodeV.ENCDataBuf[i++] = Prm.emfcmp;           
    EncCodeV.ENCDataBuf[i++] = Prm.jmot;             
    EncCodeV.ENCDataBuf[i++] = Prm.motr;             
    EncCodeV.ENCDataBuf[i++] = Prm.motl;             
    EncCodeV.ENCDataBuf[i++] = Prm.bastrq;           
    EncCodeV.ENCDataBuf[i++] = Prm.midtrq;           
    EncCodeV.ENCDataBuf[i++] = Prm.midolt;           
    EncCodeV.ENCDataBuf[i++] = Prm.mtrq2;            
    EncCodeV.ENCDataBuf[i++] = Prm.mtolt2;           
    EncCodeV.ENCDataBuf[i++] = Prm.phscmpM1;         
    EncCodeV.ENCDataBuf[i++] = Prm.ppitch;           
    EncCodeV.ENCDataBuf[i++] = Prm.motlq0;           
    EncCodeV.ENCDataBuf[i++] = Prm.motlq1;           
    EncCodeV.ENCDataBuf[i++] = Prm.exp_trat_jmot;    
    EncCodeV.ENCDataBuf[i++] = Prm.exp_motw_spd;     
    EncCodeV.ENCDataBuf[i++] = Prm.fbit_fdp;         
    EncCodeV.ENCDataBuf[i++] = Prm.poleoffset;       
    EncCodeV.ENCDataBuf[i++] = Prm.motresfrq;        
    EncCodeV.ENCDataBuf[i++] = Prm.phscmpM2;         
    EncCodeV.ENCDataBuf[i++] = Prm.flg_wf;           
      
 	 
	for(; i < (EncEepromDataNum -1); i++)
	{
		EncCodeV.ENCDataBuf[i] = 0;
	}
      
 	for( Sumx=0, i=1; i<(EncEepromDataNum -1); i++ )
	{
		Sumx -= EncCodeV.ENCDataBuf[i];
	}
      
 	EncCodeV.ENCDataBuf[0] = Sumx;
}
