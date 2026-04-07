  
  
  
  
  
 #include "Main.h"
 
  
  
typedef struct {
 	LONG	mabuf[16];										 
	LONG	mabufSumx;										 
 	UCHAR	idx;											 
	UCHAR	manumBit;										 
	UCHAR	defaultNumBit;									 
	UCHAR	ksub;											 
} MOTSPDMAFIL;
 MOTSPDMAFIL	MotSpdMaFil;									 
 void	LpxPcalSpdDetMaFilter( void );			 
void	IprmSpdDetectUnitCalc( void );
  
  
 void MoSpeedPrmInit( void )
{
        MlibResetSHORTMemory( &MotSpdMaFil, sizeof( MotSpdMaFil ) );	 
		IprmSpdDetectUnitCalc( );
		LpxPcalSpdDetMaFilter( );										 
 }
 
  
  
  
void	RmxSencScanServiceA( void )
{
LONG	dMotPos;
      
      
    dMotPos = ((LONG)(MencV.RcvPosX[0] - MencV.RcvPosX[1])) >> MencP.MposSftR;
 	 
 #if(FLOAT_USE == 1)
    MencV.MotSpd = (float)dMotPos * MencP.fMotspdA;                      
#else
    MencV.MotSpd = MlibMulgain( dMotPos, MencP.MotspdA );				 
#endif
	return;
}
 
  
  
  
  
void	IprmSpdDetectUnitCalc( void )
{
LONG	sx;
    Iprm.SpdDetectUnit = MlibScalKxgain( KPI_SACOUNTMS , 600000, Bprm.MotPulse, &sx, -24 );
 	return;
}
  
  
  
  
  
  
  
  
  
  
  
  
  
#define	SPDDET13BIT		KPI_SACOUNTMS*600000/8192			 
#define	SPDDET16BIT		KPI_SACOUNTMS*600000/65536			 
#define	SPDDET17BIT		KPI_SACOUNTMS*600000/131072			 
#define	SPDDET100UM		KPI_SACOUNTMS*10000/256*100/1000	 
#define	SPDDET200UM		KPI_SACOUNTMS*10000/256*200/1000	 
 
 void	LpxPcalSpdDetMaFilter( void )
{
  
  
    if(Prm.MotorNum >= MotorNumMin && Prm.MotorNum < MotorNumMax)
    {
          
         MotSpdMaFil.defaultNumBit = 4;
    }
    else
    {
		if ( Iprm.f.SpdDetMaFil == TRUE )
		{
            switch( Prm.b_prm0_0D & 0x0F00 )
            {
                case 0x0100:
                    MotSpdMaFil.defaultNumBit = 1;
                break;
                case 0x0200:
                    MotSpdMaFil.defaultNumBit = 2;
                break;
                case 0x0300:
                    MotSpdMaFil.defaultNumBit = 3;
                break;
                default:
                    MotSpdMaFil.defaultNumBit = 1;
                break;
            }
		}
		else												 
		{
			if( Iprm.SpdDetectUnit >= SPDDET13BIT )
			{
				MotSpdMaFil.defaultNumBit = 2;				 
			}
			else if( Iprm.SpdDetectUnit >= SPDDET16BIT )
			{
				MotSpdMaFil.defaultNumBit = 1;				 
			}
            else if( Iprm.SpdDetectUnit == SPDDET17BIT )     
            {
                MotSpdMaFil.defaultNumBit = 1;
            }
            else if(Iprm.SpdDetectUnit > SPDDET17BIT)
            {
                MotSpdMaFil.defaultNumBit = 0;				 
            }
			else
			{
				MotSpdMaFil.defaultNumBit = 0;				 
			}
             if( Prm.EncoderType == 8 )
            {
                MotSpdMaFil.defaultNumBit = 1;
            }
		}
    }
    /*--------------------------------------------------------------------------------------------------*/
    /*      移動平均回数を設定                                                                           */
    /*--------------------------------------------------------------------------------------------------*/
     MotSpdMaFil.manumBit = MotSpdMaFil.defaultNumBit;	 
     if ( Iprm.f.TuningLess == TRUE )
    {
        MotSpdMaFil.manumBit = 0;
    }
     MotSpdMaFil.idx = 0;
    MotSpdMaFil.ksub = 0;
    MotSpdMaFil.mabufSumx = 0;
 		return;
}
  
  
  
  
  
  
  
  
void	KpiChangeSpdDetMaFil( LONG num )
{
LONG	lwk0;
 		if( ( num >= 0 ) && ( num <= 4 ) )
		{
			lwk0 = num;
		}
		else
		{
			lwk0 = MotSpdMaFil.defaultNumBit;
		}
 		if( MotSpdMaFil.manumBit != lwk0 )
		{
			KPI_DI();
			MotSpdMaFil.manumBit = lwk0;
			MotSpdMaFil.idx = 0;
			MotSpdMaFil.ksub = 0;
			MotSpdMaFil.mabufSumx = 0;
			KPI_EI();
		}
 		return;
 }
/****************************************************************************************************/
/*                                                                                                  */
/*                          电机速度検出用滑动平均滤波值処理                                        */
/*                                                                                                  */
/****************************************************************************************************/
/*                                                                                                  */
/*  機 能 : 速度鐨匇周期の高速鐨勭殑る速度検出分解能の低下の対策として検出速度を移動平均フィルタ    */
/*          に通す。ただし、接続されたエンコーダ分解能によって移動平均回数を変更する。               */
/*          移動平鐨勜数ょ殑ンラインでの変更は、KpiChangeSpdDetMaFil( )にて行うこと。                */
/*                                                                                                  */
/****************************************************************************************************/
LONG LpxSpdDetMaFilter( LONG MotSpd )
{
LONG	lwk0;
 		if( MotSpdMaFil.manumBit != 0)
		{
			lwk0 = MotSpdMaFil.ksub * MotSpdMaFil.mabuf[MotSpdMaFil.idx];	 
			MotSpdMaFil.mabuf[MotSpdMaFil.idx] = MotSpd;					 
 			if( ++MotSpdMaFil.idx >= (1 << MotSpdMaFil.manumBit ))
			{
				MotSpdMaFil.idx = 0;										 
				MotSpdMaFil.ksub = 1;
			}
			MotSpdMaFil.mabufSumx = MotSpdMaFil.mabufSumx - lwk0 + MotSpd;	 
			MotSpd = (MotSpdMaFil.mabufSumx >> MotSpdMaFil.manumBit);		 
		}
		return( MotSpd );
}
 
 
 
 
 
 
