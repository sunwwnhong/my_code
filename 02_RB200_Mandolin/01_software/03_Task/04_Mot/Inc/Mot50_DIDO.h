/*
 * Mot50_DIDO.h
 *
 *  Created on: 2017年7月25日
 *      Author: zhuxc
 */
 #ifndef Mot50_DIDO_H
#define Mot50_DIDO_H


#define NUM_DIGITALIN_CHANNEL           4
#define NUM_DIGITALOUT_CHANNEL          2
#define NUM_DIGITALOUT_ETHERCAT_CHANNEL 3


  
#define	KPX_MON_HWSIN00( x )		x.f.SI0
#define	KPX_MON_HWSIN01( x )		x.f.SI1
#define	KPX_MON_HWSIN02( x )		x.f.SI2
#define	KPX_MON_HWSIN03( x )		x.f.SI3
#define	KPX_MON_HWSIN04( x )		x.f.SI4
#define	KPX_MON_HWSIN05( x )		x.f.SI5
#define	KPX_MON_HWSIN06( x )		x.f.SI6
#define	KPX_MON_HWSIN07( x )		x.f.SI7
#define	KPX_MON_HWSIN08( x )		x.f.SI8
  
  
#define	KPX_MON_HWSOUT00( x )		x.f.SO0
#define	KPX_MON_HWSOUT01( x )		x.f.SO1
#define	KPX_MON_HWSOUT02( x )		x.f.SO2
#define	KPX_MON_HWSOUT03( x )		x.f.SO3
#define	KPX_MON_HWSOUT04( x )		x.f.SO4
#define	KPX_MON_HWSOUT05( x )		x.f.SO5
#define	KPX_MON_HWSOUT06( x )		0
#define	KPX_MON_HWSOUT07( x )		0
 
  
 typedef	union	{					 
		struct	{						 
 		UINT	Rsv0 			:1;		 
		UINT	SI0 			:1;		 
		UINT	SI1			    :1;		 
		UINT	SI2 			:1;		 
		UINT	SI3 			:1;		 
		UINT	SI4 			:1;		 
		UINT	SI5 			:1;		 
		UINT	SI6 			:1;		 
		UINT	SI7 			:1;		 
		UINT	SI8 			:1;		 
		UINT	RsvA 			:1;		 
		UINT	RsvB 			:1;		 
		UINT	RsvC 			:1;		         
		UINT	RsvD 			:1;		 
		UINT	RsvE 			:1;		         
		UINT	RsvF 			:1;		 
 		} f;
 		ULONG	dw;						 
} HWSIN;
 typedef	union	{
		struct	{
		UINT	SO0			:1;          
		UINT	SO1	 		:1;          
		UINT	SO2		    :1;          
		UINT	SO3 		:1;          
		UINT	SO4			:1;          
		UINT	SO5 		:1;          
		UINT	SO6 		:1;          
		UINT	SO7 		:1;          
		UINT	SO8			:1;          
		UINT	SO9			:1;          
		UINT	Reserved0A	:1;
		UINT	Reserved0B	:1;
		UINT	Reserved0C	:1;
		UINT	Reserved0D	:1;
		UINT	Reserved0E	:1;
		UINT	Reserved0F	:1;
		UINT	Reserved10	:1;
		UINT	Reserved11	:1;
		UINT	Reserved12	:1;
		UINT	Reserved13	:1;
		UINT	Reserved14	:1;
		UINT	Reserved15	:1;
		UINT	Reserved16	:1;
		UINT	Reserved17	:1;
		UINT	Reserved18	:1;
		} f;
		ULONG	dw;
} HWSOUT;
 typedef struct{
        UINT	ServoOn			:1;      
        UINT	Pot             :1;	     
		UINT	Not             :1;	     
        UINT	AlmReset		:1;      
        UINT    EnbPCtrl        :1;      
        UINT	TlimitSel	    :1;      
		UINT	Spare		    :1;      
        UINT	SpdD            :1;	     
		UINT	SpdA            :1;	     
		UINT	SpdB            :1;	     
        UINT	Csel            :1;      
        UINT	Zclamp          :1;	     
        UINT    Inhibit         :1;	     
        UINT    Gsel1           :1;	     
        UINT    TrqSign         :1;	       
        UINT    Psel            :1;	     
} DIST;
 typedef	struct {
        USHORT DigitInNew;               
        USHORT DigitInOld;               
        USHORT DigitInFilCnt[ NUM_DIGITALIN_CHANNEL ];
        USHORT DigitInSetStatus[ NUM_DIGITALIN_CHANNEL];
        USHORT DigitOutSetStatus[NUM_DIGITALOUT_CHANNEL];
        USHORT DigitInFilter;
        HWSIN DigitStatus;               
        HWSIN DigitStatusMon;
        USHORT DigitInSignal;            
        DIST    DISt;                    
        USHORT ServoOnDelay;             
} DIGIT_DIDO;
 #define KeyNum 4                                                 
  
 #define	DigitInFilter( out, oldin, newin ) \
		{ out = (((oldin | newin) & out ) | (oldin & newin)); oldin = newin;}
 #define	KPI_SI0BITNO		1
#define	KPI_SI1BITNO		2
#define	KPI_SI2BITNO		3
#define	KPI_SI3BITNO		4
#define	KPI_SI4BITNO		5
#define	KPI_SI5BITNO		6
#define	KPI_SI6BITNO		7
#define KPI_SI7BITNO        8
#define KPI_SI8BITNO        9   
 #define KPI_SINHIBITNO		1		 
#define KPI_SINLOBITNO		0		 
  
#define KPX_SINPUTBITX( In, Imap )	((((In>>Imap.b.l)^Imap.b.h) & 0x01)? TRUE : FALSE)
#define KPI_SINANDBITS				0x3FE0    
#define KPI_SINSETBITS				0x0000
#define	KPI_SIN_START( x )	{ x.dw = DIDOVar.DigitStatus.dw;}
#define	KPI_SIN_SVON( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Svon    )     
#define	KPI_SIN_POT( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Pot     )     
#define	KPI_SIN_NOT( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Not     )     
#define	KPI_SIN_ALMRST( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.AlmRst  )     
#define	KPI_SIN_PCON( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Pcon    )     
#define	KPI_SIN_TlimitSel( x )		KPX_SINPUTBITX( x.dw, Iprm.Imap.TlimitSel)    
 #define	KPI_SIN_SPDD( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.SpdD    )     
#define	KPI_SIN_SPDA( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.SpdA    )     
#define	KPI_SIN_SPDB( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.SpdB    )     
#define	KPI_SIN_CSEL( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Csel    )     
#define	KPI_SIN_CSEL2( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Csel2   )     
#define	KPI_SIN_CTrig( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.CTrig   )             
#define	KPI_SIN_ZCLAMP( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Zclamp  )     
#define	KPI_SIN_INHIBIT( x )		KPX_SINPUTBITX( x.dw, Iprm.Imap.Inhibit )     
#define	KPI_SIN_GAINSEL0( x )		KPX_SINPUTBITX( x.dw, Iprm.Imap.Gsel1   )     
#define	KPI_SIN_GAINSEL1( x )		KPX_SINPUTBITX( x.dw, Iprm.Imap.Gsel2   )     
#define	KPI_TRQ_SIGN( x )		    KPX_SINPUTBITX( x.dw, Iprm.Imap.TrqSign )     
#define	KPI_SIN_PSEL( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Psel    )     
#define KPI_SIN_CLR( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.CLR     )     
#define	KPI_SIN_TORQA( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.TORQA   )     
#define	KPI_SIN_TORQB( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.TORQB   )     
#define	KPI_SIN_TCTRG( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.TCTRG   )     
#define	KPI_SIN_TSPDLIMIT( x )		KPX_SINPUTBITX( x.dw, Iprm.Imap.SPDLIMIT   )      
#define	KPI_SIN_BKSEL( x )		    KPX_SINPUTBITX( x.dw, Iprm.Imap.BKSel   )     
 #define	KPI_SIN_JOGP( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.JOGP   )             
#define	KPI_SIN_JOGN( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.JOGN   )     
 #define	KPI_SIN_EMST( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.EmcyStop)     
 #define	KPI_SIN_TMONTRG( x )		KPX_SINPUTBITX( x.dw, Iprm.Imap.TmonTrg)      
         
  
 #define KPI_SIN_CTRG( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.CTRG   )      
#define KPI_SIN_POS0( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.POS0   )      
#define KPI_SIN_POS1( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.POS1   )      
#define KPI_SIN_POS2( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.POS2   )              
#define KPI_SIN_POS3( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.POS3   )              
#define KPI_SIN_POS4( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.POS4   )             
#define KPI_SIN_POS5( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.POS5   )              
#define KPI_SIN_ORGEN( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.ORGEN   )     
#define KPI_SIN_ORGS( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.ORGS   )          

#define KPI_SIN_ExFault( x )        KPX_SINPUTBITX( x.dw, Iprm.Imap.ExFault   )             // 外部故障信号
#define KPI_SIN_FUN30( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun30   )          
#define KPI_SIN_FUN31( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun31   )       
#define KPI_SIN_FUN32( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun32   )       
#define KPI_SIN_FUN33( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun33   )       
#define KPI_SIN_FUN34( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun34   )       
#define KPI_SIN_FUN35( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun35   )       
#define KPI_SIN_FUN36( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun36   )       
#define KPI_SIN_FUN37( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun37   )               
#define KPI_SIN_FUN38( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun38   )               
#define KPI_SIN_FUN39( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun39   )               
#define KPI_SIN_FUN3A( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun3A   )              
#define KPI_SIN_FUN3B( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun3B   )               
#define KPI_SIN_FUN3C( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun3C   )               
#define KPI_SIN_FUN3D( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun3D   )               
#define KPI_SIN_FUN3E( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun3E   )               
#define KPI_SIN_FUN3F( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Fun3F   )               
 /*
#define	KPI_SIN_DEC( x )			KPX_SINPUTBITX( x.dw, DIDOVar.Imap.Dec 	)
#define	KPI_SIN_SEN( x )			(CinK.hw[0].f.Seni == TRUE || Iprm.Imap.Sen == 1)? TRUE : FALSE;
#define	KPI_SIN_PDET( x )			KPX_SINPUTBITX( x.dw, Iprm.Imap.Pdet    )
#define	KPI_SIN_CYCLEST( x )		KPX_SINPUTBITX( x.dw, Iprm.Imap.CycleSt )
*/
#define KPX_SOUTPUTBITX( Out, Omap )	((Out)? Omap : 0x0000)
#define	KPI_SOUT_SVREADY( x, y )	{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Svrdy  );}
#define	KPI_SOUT_COIN( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Coin   );}
#define	KPI_SOUT_VCMP( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Vcmp   );}
#define	KPI_SOUT_TGON( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Tgon   );}
#define	KPI_SOUT_CLT( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Clt    );}
#define	KPI_SOUT_VLT( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Vlt    );}
#define	KPI_SOUT_BRAKE( x, y )		{ x.dw |= KPX_SOUTPUTBITX( (( y == FALSE)? TRUE : FALSE) , Iprm.Omap.Bk );}
#define	KPI_SOUT_WARNING( x, y )	{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Warn   );}      
#define	KPI_SOUT_NEAR( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Near   );}
#define	KPI_SOUT_PSELA( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.PselA  );}
#define	KPI_SOUT_ALARM( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Alarm  );}
#define KPI_SOUT_TORREACH( x, y )   { x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.TorReach  );}
#define KPI_SOUT_EtherCatY1(x,y)    { x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.EtherCatY1  );}
#define KPI_SOUT_EtherCatY2(x,y)    { x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.EtherCatY2  );}
#define KPI_SOUT_JOGP(x,y)          { x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.JOGP  );}
#define KPI_SOUT_JOGN(x,y)          { x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.JOGN  );}

#define	KPI_SOUT_CMDOK( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.CMDOK  );}
#define	KPI_SOUT_TPOS( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.TPOS  );}
#define	KPI_SOUT_MCOK( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.MCOK  );}
#define KPI_SOUT_STO( x, y )        { x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.STO  );}
#define KPI_SOUT_ORGC( x, y )       { x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.ORGC  );}

#define	KPI_SOUT_Fun20( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun20  );}
#define	KPI_SOUT_Fun21( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun21  );}
#define	KPI_SOUT_Fun22( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun22  );}
#define	KPI_SOUT_Fun23( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun23  );}
#define	KPI_SOUT_Fun24( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun24  );}
#define	KPI_SOUT_Fun25( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun25  );}
#define	KPI_SOUT_Fun26( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun26  );}
#define	KPI_SOUT_Fun27( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun27  );}
#define	KPI_SOUT_Fun28( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun28  );}
#define	KPI_SOUT_Fun29( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun29  );}
#define	KPI_SOUT_Fun2A( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun2A  );}
#define	KPI_SOUT_Fun2B( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun2B  );}
#define	KPI_SOUT_Fun2C( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun2C  );}
#define	KPI_SOUT_Fun2D( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun2D  );}
#define	KPI_SOUT_Fun2E( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun2E  );}
#define	KPI_SOUT_Fun2F( x, y )		{ x.dw |= KPX_SOUTPUTBITX( y, Iprm.Omap.Fun2F  );}
  
 
extern DIGIT_DIDO DIDOVar;
extern void ReadDIStatus(void);
extern UCHAR KeyValueFeedBack(void);
extern ULONG KpiMonInputSignal( void );
extern ULONG KpiMonOutputSignal( void );
extern void User20_DIDO_Init( void );
extern void ScanCinputAptIf( void );
extern void	LpxBoutputAptIf( void );
extern void	LpxCoutputAptIf( void );
extern void YOutPutToFPGA( void );
extern void DISeqInput1Map_Init( void );
extern void DISeqInput2Map_Init( void );
extern void DISeqInput3Map_Init( void );
extern void DISeqInput4Map_Init( void );
 extern void DISeqOutput1Map_Init( void );
extern void DISeqOutput2Map_Init( void );
 
 
 
#endif
