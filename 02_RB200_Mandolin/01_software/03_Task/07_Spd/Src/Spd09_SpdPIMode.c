  
  
  
  
  
 #include "Main.h"
 
  
  
  
void PcalBitParamMSW( void )
{
	UCHAR data;
 	data = Prm.gnmode & 0x0F;
	if( data <= 4 )
	{
		Gprm.MSW = data;
	}
	else
	{
		KpiSetParamError( &pndef_gnmode );
	}
}
 
