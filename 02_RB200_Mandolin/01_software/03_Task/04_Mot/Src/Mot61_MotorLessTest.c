  
  
  
  
  
  
#include "Main.h"
 
 
  
  
 void ApiReadMotPrmMotorLessTestMode( void )
{
 	USHORT	ivcode;					                             
    USHORT  EncType;                                             
	USHORT	EncBitNo;				                             
    LONG	kx;
    LONG    sx;
 	 
      
     Prm.typm_e.b.l = 0;                                          
     if( ( Prm.VoltType & 0x000F ) == 0x01 ) 
    {
        ivcode = 0x01;                                           
    }
    else if( ( Prm.VoltType & 0x000F ) == 0x02 )
    {
        ivcode = 0x02;                                           
    }
    else if( ( Prm.VoltType & 0x000F ) == 0x03 )
    {
        ivcode = 0x03;                                           
    }
    else if( ( Prm.VoltType & 0x000F ) == 0x04 )
    {
        ivcode = 0x04;                                           
    }
     if( (Prm.b_prm0_0E & 0x0F00) == 0 )                          
    {
        EncType = 2;
    }
    else
    {
        EncType = 1;
    }
     Prm.typm_e.b.h = ( ivcode + (EncType << 4) ) << 8;
      
      
    Prm.motw = Prm.ampw;
      
      
    switch( (Prm.b_prm0_0E & 0xF000) >> 12 )                     
    {
        case 0:     EncBitNo = 16;  break;                       
        case 1:     EncBitNo = 17;  break;                                 
        case 2:     EncBitNo = 20;  break;                         
        case 3:     EncBitNo = 23;  break;                       
        default:	EncBitNo = 24;  break;                       
    }
    Prm.bit_dp.b.h = 0x00;
    Prm.bit_dp.b.l = EncBitNo;
     
      
     Prm.vrat_max.b.h = 60;                                       
    Prm.vrat_max.b.l = 30;                                       
      
      
    Prm.oslv_pol.b.h = 10;                                       
    Prm.oslv_pol.b.l = 10;                                       
      
 	 
 	 
 	 
 	kx = MlibScalKxgain( (LONG)Prm.motw, (60UL*C10POW7),  C2PAIE7, &sx, 0 );
	kx = MlibPcalKxgain( kx, 1, (Prm.vrat_max.b.l & 0x00FF), &sx, -24 );
 	Prm.rattrq = MlibLimitul( kx, 0xFFFF, 0x0000 );    
      
 	 
 	 
 	Prm.maxtrq = (((Prm.imaxs * 200UL)/Prm.irats) + 1) >> 1;
      
      
	Prm.irat = Prm.irats;						                     
      
      
	Prm.imax = Prm.imaxs;						                     
      
      
	Prm.emfcmp = 100;							                     
      
      
	Prm.jmot = Prm.Mless_jmot;					                     
      
      
	Prm.motr = 100;								                 
      
      
	Prm.motl = 50;								                         
      
      
	Prm.bastrq = Prm.ibs_md.b.l & 0x00FF;				                     
      
      
	Prm.midtrq = (Prm.ibs_md.b.h) * 10;			                     
      
      
	Prm.midolt = (Prm.imdt_mxt.b.l & 0x00FF) + 15;  		                     
      
      
 	kx = (LONG)(Prm.ratmtt_2.b.h) * (LONG)Prm.maxtrq / 100UL;
	Prm.mtrq2 = (USHORT)kx;
      
      
	Prm.mtolt2 = Prm.imdt_mxt.b.h;				                     
      
      
	Prm.phscmpM1 = 0;							                     
      
      
	Prm.ppitch = 225;							                     
      
      
	Prm.motlq0 = 50;							                     
      
      
	Prm.motlq1 = 50;							                     
      
      
                                                                      
	Prm.exp_trat_jmot = (Prm.Mless_exp_spd_jmot >> 8) << 8;
      
      
	Prm.exp_motw_spd = 0;					                     
 	Prm.exp_motw_spd |= (Prm.Mless_exp_spd_jmot & 0x00FF ) << 8;
      
      
 
 	 
 	Prm.poleoffset = 0;							                     
      
      
	Prm.motresfrq = 0;							                     
      
      
	Prm.phscmpM2 = 0;							                     
      
      
	Prm.flg_wf = 0;								                         
 }
 
  
  
 typedef	union
{
	LONG Long[2];
	struct{
		DWORDX	RxPosL;
		SHORT	RxPosH;
		SHORT	Dummy;
	} EncFormat;
} ENCODER_DATA;
 typedef	struct	{
		struct {
		UINT			SemiEncConnect		:1;
		UINT			FullEncConnect		:1;
		} f;
		LONG			dSemiModePos;
		LONG			dFullModePos;
		ENCODER_DATA	SencData;
		ENCODER_DATA	FencData;
} MOTOR_LESS;
 typedef	struct	{
		float	MdlKj;                       
		float	MdlKvp;                      
		float	MdlKvpM;                     
		float	MdlKt;
		float	Kqp;
		float	Kqi;
		float	Uqm;
		float	Rs;
		float	KLq;
		float	Kt;
		float	Ke;
		float	Fric;
         int     Load;
        float	MdlKjl;
        float	Dml;
        float	Kml;
        float	Fricl;
         int     Base;
        float	MdlKjb;
        float	Db;
        float	Kb;
 } MOTLESSMDLP;
typedef	struct	{
		MOTLESSMDLP	P;
		struct {
 		float	MotMdlSpdFbk;			             
		LONG	MotMdldPosFbk;			             
		LONG	MotMdlPosFbk;			             
		LONG	MechaMdldPosFbk;		             
		LONG	MechaMdlPosFbk;			             
		float	MotMdlpfbrem;			             
		float	MechaMdlpfbrem;			                     
         float   IqFbk;
        float   Pacout;
        float   Iacout;
        float   UqRef;
        float   UqRef1;
         float	SprTrq;
        float	Tml;
        float	LoadMdlSpdFbk;
         LONG	LoadMdlPosFbk;
        float	LoadMdlpfbrem;
 
        float	BaseTrq;
        float	BaseMdlSpdFbk;
         LONG	BaseMdldPosFbk;
        LONG	BaseMdlPosFbk;
        float	BaseMdlpfbrem;
         } V;
} MOTLESSMDL;
MOTLESSMDL	MotorLessMdl;
MOTOR_LESS	MotorLessTestDatas;
 #define	MDLCYCLE		0.0000625f
#define	MDLCYCLEUS		62.5f
#define	MDLCYCLE10US	6.25f
#define	MDLCYCLENS		62500.0f
#define	C10POW9			1000000000UL
  
#define C2PI            6.2831853f
#define	KPI_MACYCLENS	62500
 
  
  
  
void IprmMotorLessTestMode( void )
{
LONG	kx;
float   wrml;
float   wnb;
float   zeta;
float   tmp;
MOTLESSMDLP	wrkp;
 		wrkp.MdlKvp = MDLCYCLE * (float)Bprm.MotPulse / C2PI;
 		kx = Bprm.MotPulse;
 		wrkp.MdlKvpM = MDLCYCLE * (float)kx / C2PI;
 		wrkp.MdlKj = MDLCYCLENS/((float)Prm.jmot*(100+Prm.jrate));
         
		wrkp.MdlKt = (float)Prm.irat * Bprm.PerMaxTrq / 15000000.f;
         wrkp.KLq = (float)Prm.motl / 100000.0f;
         wrkp.Kqp = C2PI * (float)Prm.ignq * wrkp.KLq;
         wrkp.KLq = MDLCYCLE10US/(float)Prm.motl;
	    if( Prm.kiq == 0 )
	    {
	        wrkp.Kqi = 0.0f;
	    }
	    else
	    {
            wrkp.Kqi = wrkp.Kqp * MDLCYCLEUS / ((float)Prm.kiq);
	    }
  
  
                 wrkp.Uqm = 3111270.0f*5.7735e-005f;      
 
 	    wrkp.Kt = (float)Prm.rattrq / ((float)Prm.irat*10);
 		wrkp.Ke = 0.6666667f * wrkp.Kt;
 	    wrkp.Rs = Prm.motr/1000.0f;
         wrkp.Fric = (float)(Prm.rattrq * Prm.Dm) * 9.55e-7f;
      
     if( Prm.Mless_PlantModel & 0x2 )
    {
        wrkp.Load = 1;
    }
    else
    {
        wrkp.Load = 0;
    }
      
     wrml = (float)Prm.frml * C2PI;
      
      
    zeta = (float)Prm.ztrml / 100.0f;
     
    tmp = wrml * (float)Prm.jmot*(float)Prm.jrate / (100.0f+(float)Prm.jrate)*1e-7f;
    wrkp.Kml = MDLCYCLE * wrml *tmp;
    wrkp.Dml = 2 * zeta * tmp;
    wrkp.Fricl = (float)(Prm.rattrq * Prm.Dl) * 9.55e-7f;
    if(wrkp.Load == 1 && Prm.jrate != 0)
    {
        wrkp.MdlKj  = MDLCYCLENS/((float)Prm.jmot*100.0f);
        wrkp.MdlKjl = MDLCYCLENS/((float)Prm.jmot*(float)Prm.jrate);
    }
    else
    {
        wrkp.MdlKjl =  wrkp.MdlKj;
    }
     if( Prm.Mless_PlantModel & 0x1 )
    {
        wrkp.Base = 1;
    }
    else
    {
        wrkp.Base = 0;
    }
    wnb = (float)Prm.fnb * C2PI/10.0f;
    wrkp.Kb = wnb*(float)wnb*(float)Prm.jmot/1000.0f*(float)Prm.jbrate/10000.0f * MDLCYCLE;
    wrkp.Db = 2.0f*(float)Prm.zb/1000.0f*(float)wnb*(float)Prm.jmot/1000.0f*(float)Prm.jbrate/10000.0f;
    wrkp.MdlKjb =  MDLCYCLENS/((float)Prm.jmot* (float)Prm.jbrate * 100.0f);
     KPI_DI();
    MotorLessMdl.P = wrkp;
    KPI_EI();
     return;
}
  
  
  
float	FMlibLimitul( float u, float ulim, float llim )
{
		if( u > ulim )
		{
			return( ulim );
		}
		if( u < llim )
		{
			return( llim );
		}
		return( u );
}
 
  
  
 void ApxMotorLessTestModeMechaModel( LONG In )
{
float   IqRef;
float   IqErr;
float   UqRefx;
float   dIq;
float   Te;
float   SumTrq;
LONG	dBasePos;
 float	MotSpd;
LONG	dMotPos;
LONG	dFbPos;
float	MotAcc;
float	Bemf;
 float	tmp;
float	tmp1;
float	tmp2;
      
      
 	if( BinV.f.BaseEnable == FALSE )
 	{
 		MotorLessMdl.V.MotMdlpfbrem = 0;
 		MotorLessMdl.V.MechaMdlpfbrem = 0;
 		MotorLessMdl.V.MotMdlSpdFbk = 0;
 		MotorLessMdl.V.Iacout = 0;
 		MotorLessMdl.V.IqFbk = 0;
 	}
      
     tmp = MotorLessMdl.V.MotMdlSpdFbk * MotorLessMdl.P.MdlKvp + MotorLessMdl.V.MotMdlpfbrem;
	if(tmp >= 0.0f)
    {
        dMotPos = (LONG)(tmp + 0.5f);
    }
    else
    {
        dMotPos = (LONG)(tmp - 0.5f);
    }
    MotorLessMdl.V.MotMdlpfbrem = tmp - (float)dMotPos;
	MotorLessMdl.V.MotMdldPosFbk = dMotPos;
	MotorLessMdl.V.MotMdlPosFbk += dMotPos;
      
      
    tmp = MotorLessMdl.V.BaseMdlSpdFbk * MotorLessMdl.P.MdlKvpM + MotorLessMdl.V.BaseMdlpfbrem;
    if(tmp >= 0.0f)
    {
        dBasePos = (LONG)(tmp + 0.5f);
    }
    else
    {
        dBasePos = (LONG)(tmp - 0.5f);
    }
    MotorLessMdl.V.BaseMdlpfbrem = tmp - (float)dBasePos;
    MotorLessMdl.V.BaseMdldPosFbk = dBasePos;
    MotorLessMdl.V.BaseMdlPosFbk += MotorLessMdl.V.BaseMdldPosFbk;
      
      
    tmp = MotorLessMdl.V.MotMdlSpdFbk * MotorLessMdl.P.MdlKvpM + MotorLessMdl.V.MechaMdlpfbrem;
	if(tmp >= 0.0f)
    {
        dFbPos = (LONG)(tmp + 0.5f);
    }
    else
    {
        dFbPos = (LONG)(tmp - 0.5f);
    }
    MotorLessMdl.V.MechaMdlpfbrem = tmp - (float)dFbPos;
	MotorLessMdl.V.MechaMdldPosFbk = dFbPos-dBasePos;
	MotorLessMdl.V.MechaMdlPosFbk += MotorLessMdl.V.MechaMdldPosFbk;
      
      
    Bemf = MotorLessMdl.V.MotMdlSpdFbk * MotorLessMdl.P.Ke;
    UqRefx = MotorLessMdl.V.UqRef1 - Bemf;
      
      
    MotAcc = MotorLessMdl.V.IqFbk * MotorLessMdl.P.Rs;
    UqRefx = UqRefx - MotAcc;
      
      
    dIq = UqRefx * MotorLessMdl.P.KLq;
    MotorLessMdl.V.IqFbk = MotorLessMdl.V.IqFbk + dIq;
     IqRef = (float)In * MotorLessMdl.P.MdlKt;
      
      
    IqErr = IqRef - MotorLessMdl.V.IqFbk;
      
      
    MotorLessMdl.V.Pacout = IqErr * MotorLessMdl.P.Kqp;
      
      
    tmp = IqErr * MotorLessMdl.P.Kqi;
	MotorLessMdl.V.Iacout += tmp;
    MotorLessMdl.V.Iacout = FMlibLimitul( MotorLessMdl.V.Iacout, MotorLessMdl.P.Uqm, -MotorLessMdl.P.Uqm );
      
      
    UqRefx = MotorLessMdl.V.Pacout + MotorLessMdl.V.Iacout;
    MotorLessMdl.V.UqRef = FMlibLimitul( UqRefx, MotorLessMdl.P.Uqm, -MotorLessMdl.P.Uqm );
     MotorLessMdl.V.UqRef1 = MotorLessMdl.V.UqRef;
      
      
    Te = MotorLessMdl.V.IqFbk * MotorLessMdl.P.Kt;
      
      
    tmp = MotorLessMdl.V.MotMdlSpdFbk * MotorLessMdl.P.Fric;
      
      
    SumTrq = Te - tmp;
    SumTrq =  SumTrq - MotorLessMdl.V.Tml;
      
      
	MotAcc = SumTrq * MotorLessMdl.P.MdlKj;
    MotorLessMdl.V.MotMdlSpdFbk = MotorLessMdl.V.MotMdlSpdFbk + MotAcc;
	MotSpd = MotorLessMdl.V.MotMdlSpdFbk;
     if(MotorLessMdl.P.Load == 1)
    {
        tmp = MotSpd - MotorLessMdl.V.LoadMdlSpdFbk;
        tmp1 = tmp * MotorLessMdl.P.Dml;
        tmp2 = tmp * MotorLessMdl.P.Kml;
        MotorLessMdl.V.SprTrq += tmp2;
        MotorLessMdl.V.Tml = tmp1 + MotorLessMdl.V.SprTrq;
 
        tmp = MotorLessMdl.V.LoadMdlSpdFbk * MotorLessMdl.P.Fricl;
        SumTrq = MotorLessMdl.V.Tml - tmp;
        MotAcc = SumTrq * MotorLessMdl.P.MdlKjl;
        MotorLessMdl.V.LoadMdlSpdFbk = MotorLessMdl.V.LoadMdlSpdFbk + MotAcc;
    }
    else
    {
        MotorLessMdl.V.Tml = 0;
        MotorLessMdl.V.LoadMdlSpdFbk = MotorLessMdl.V.MotMdlSpdFbk;
    }
     if(MotorLessMdl.P.Base == 1)
    {
         tmp = MotorLessMdl.V.BaseMdlSpdFbk;
        tmp1 = tmp * MotorLessMdl.P.Db;
        tmp2 = tmp * MotorLessMdl.P.Kb;
        MotorLessMdl.V.BaseTrq += tmp2;
        SumTrq = tmp1 + MotorLessMdl.V.BaseTrq;
        SumTrq = -SumTrq - Te;
        MotAcc = SumTrq * MotorLessMdl.P.MdlKjb;
        MotorLessMdl.V.BaseMdlSpdFbk = MotorLessMdl.V.BaseMdlSpdFbk + MotAcc;
    }
    else
    {
        MotorLessMdl.V.BaseMdlSpdFbk = 0;
    }
  	BoutV.AmonMotorLessTestMdlSpd = (LONG)MotorLessMdl.V.MotMdlSpdFbk;
 
	return;
}
  
  
  
USHORT	LpxGetSencMotLessMturnData( USHORT PosH, ULONG PosL )
{
USHORT	Mturn;
         Mturn = 0;   
		return( Mturn );
}
  
  
  
void RmxReadMotorLessPosition( void )
{
LONG	dEncPos;
LONG	dMotPos;
LONG	RcvPosX;
LONG	LastMotPosX = MencV.MotPosX[0];
SHORT	Mturn;
      
  
  
  
  
     MotorLessTestDatas.dSemiModePos = MotorLessMdl.V.MotMdldPosFbk;
      
     dEncPos = (LONG)MotorLessTestDatas.dSemiModePos;
    MlibAdd6432( MotorLessTestDatas.SencData.Long, dEncPos, MotorLessTestDatas.SencData.Long );
     Mturn = LpxGetSencMotLessMturnData( MotorLessTestDatas.SencData.EncFormat.RxPosH,
										MotorLessTestDatas.SencData.EncFormat.RxPosL.dw);
  
  
  
  
     MencV.RxPosL[0].dw = MotorLessTestDatas.SencData.EncFormat.RxPosL.dw;
    MencV.RxPosH[0]    = MotorLessTestDatas.SencData.EncFormat.RxPosH; 
     RcvPosX = MencV.RxPosL[0].Long << MencP.MposSftR;
     MencV.RcvPosX[1]  = MencV.RcvPosX[0];
    MencV.RcvPosX[0]  = RcvPosX;
     MencV.MotPosX[1]  = MencV.RcvPosX[1];
    MencV.MotPosX[0]  = MencV.RcvPosX[0];
      
      
    RoutV.MencIncPulse = ((ULONG)RcvPosX) >> MencP.MposSftR;     
    RoutV.MencMultiTurn = Mturn;                                 
     
 
	dMotPos = (LONG)((LONG)((MencV.MotPosX[0]) - (LastMotPosX)) >> MencP.MposSftR);
    MencV.MotPos    = MencV.MotPos    + dMotPos;
    MencV.MotAbsPos = MencV.MotAbsPos + dMotPos;
     return;
}
  
  
