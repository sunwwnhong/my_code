 #include "MlibSvc.h"
 
 #define	CCSW_HsMulgain			0
 void	MlibAdd6432( LONG *a, LONG  b, LONG *x );
void	MlibAdd6464( LONG *a, LONG *b, LONG *x );
void	MlibSub6432( LONG *a, LONG  b, LONG *x );
void	MlibSub6464( LONG *a, LONG *b, LONG *x );
void	MlibMul3232( LONG  a, LONG  b, LONG *x );
void	MlibMulu32u32( ULONG a, ULONG b, ULONG *x );
#define	ADD6432( a, b, xx )		*(INT64*)xx = *(INT64*)(a) + (INT64)(b)
#define	ADD6464( a, b, xx )		*(INT64*)xx = *(INT64*)(a) + *(INT64*)(b)
#define	SUB6432( a, b, xx )		*(INT64*)xx = *(INT64*)(a) - (INT64)(b)
#define	SUB6464( a, b, xx )		*(INT64*)xx = *(INT64*)(a) - *(INT64*)(b)
#define	MUL3232( a, b, xx )		*(INT64*)xx = ((INT64)(a))*((INT64)(b))
#define	MULU32U32( a, b, xx )	*(INT64*)xx = ((INT64)(ULONG)(a))*((INT64)(ULONG)(b))
#undef	KPI_DI
#define	KPI_DI( )				 
#undef	KPI_EI
#define	KPI_EI( )				 
  
  
  
  
  
  
  
  
  
 
  
  
  
  
  
  
  
 
 
 
 #define LPX_ABS( u )	(((u)>=0) ? (u) : -(u))
 
 #define	SCUP31_SXINC( x, s, wk )\
		wk=0x00008000; if( (ULONG)x <  (ULONG)wk ){ x=(x<<16); s=s+16;}\
		wk=(wk<<8)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 8); s=s+ 8;}\
		wk=(wk<<4)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 4); s=s+ 4;}\
		wk=(wk<<2)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 2); s=s+ 2;}\
		wk=(wk<<1)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 1); s=s+ 1;}
#define	SCUP31_SXDEC( x, s, wk )\
		wk=0x00008000; if( (ULONG)x <  (ULONG)wk ){ x=(x<<16); s=s-16;}\
		wk=(wk<<8)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 8); s=s- 8;}\
		wk=(wk<<4)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 4); s=s- 4;}\
		wk=(wk<<2)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 2); s=s- 2;}\
		wk=(wk<<1)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 1); s=s- 1;}
#define	SCUP23_SXINC( x, s, wk )\
		wk=0x00000080; if( (ULONG)x <  (ULONG)wk ){ x=(x<<16); s=s+16;}\
		wk=(wk<<8)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 8); s=s+ 8;}\
		wk=(wk<<4)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 4); s=s+ 4;}\
		wk=(wk<<2)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 2); s=s+ 2;}\
		wk=(wk<<1)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 1); s=s+ 1;}
#define	SCUP23_SXDEC( x, s, wk )\
		wk=0x00000080; if( (ULONG)x <  (ULONG)wk ){ x=(x<<16); s=s-16;}\
		wk=(wk<<8)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 8); s=s- 8;}\
		wk=(wk<<4)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 4); s=s- 4;}\
		wk=(wk<<2)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 2); s=s- 2;}\
		wk=(wk<<1)   ; if( (ULONG)x <  (ULONG)wk ){ x=(x<< 1); s=s- 1;}
#define	SCDN15_SXINC( x, s, wk )\
		wk=0x40000000; if( (ULONG)x >= (ULONG)wk ){ x=(x>>16); s=s+16;}\
		wk=(wk>>8)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 8); s=s+ 8;}\
		wk=(wk>>4)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 4); s=s+ 4;}\
		wk=(wk>>2)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 2); s=s+ 2;}\
		wk=(wk>>1)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 1); s=s+ 1;}
#define	SCDN15_SXDEC( x, s, wk )\
		wk=0x40000000; if( (ULONG)x >= (ULONG)wk ){ x=(x>>16); s=s-16;}\
		wk=(wk>>8)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 8); s=s- 8;}\
		wk=(wk>>4)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 4); s=s- 4;}\
		wk=(wk>>2)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 2); s=s- 2;}\
		wk=(wk>>1)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 1); s=s- 1;}
#define	SCDN23_SXINC( x, s, wk )\
		wk=0x40000000; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 8); s=s+ 8;}\
		wk=(wk>>4)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 4); s=s+ 4;}\
		wk=(wk>>2)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 2); s=s+ 2;}\
		wk=(wk>>1)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 1); s=s+ 1;}
#define	SCDN23_SXDEC( x, s, wk )\
		wk=0x40000000; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 8); s=s- 8;}\
		wk=(wk>>4)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 4); s=s- 4;}\
		wk=(wk>>2)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 2); s=s- 2;}\
		wk=(wk>>1)   ; if( (ULONG)x >= (ULONG)wk ){ x=(x>> 1); s=s- 1;}
 
 LONG	XasmDIVUA( LONG ax, LONG bx, LONG rep )
{
LONG	i,kx;
		ax = (ax<<1);
		for( kx=0,i=0; i<(rep-1); i++ )
		{
			if( (ULONG)ax >= (ULONG)bx )
			{
				kx = kx + 1;
				ax = (ULONG)ax - (ULONG)bx;
			}
			kx = (kx<<1); ax = (ax<<1);
		}
		if( (ULONG)ax >= (ULONG)bx ){ kx = kx + 1;}
		return( kx );
}
LONG	XasmDIVUB( LONG ax, LONG bx, LONG rep )
{
LONG	i,kx;
		ax = (ax<<1);
		for( kx=0,i=0; i<rep; i++ )
		{
			kx = (kx<<1);
			if( (ULONG)ax >= (ULONG)bx )
			{
				kx = kx + 1;
				ax = (ULONG)ax - (ULONG)bx;
			}
			ax = (ax<<1);
		}
		if( (ULONG)ax >= (ULONG)bx ){ kx = kx + 1;}
		return( kx );
}
LONG	XasmDIVUXA( LONG ax, LONG bx, LONG *sx, LONG rep )
{
LONG	i,kx;
		if( (ULONG)ax < (ULONG)bx )
		{
			ax = (ax<<1); *sx = *sx + 1;
		}
		for( kx=0,i=0; i<(rep-1); i++ )
		{
			if( (ULONG)ax >= (ULONG)bx )
			{
				kx = kx + 1;
				ax = (ULONG)ax - (ULONG)bx;
			}
			kx = (kx<<1); ax = (ax<<1);
		}
		if( (ULONG)ax >= (ULONG)bx ){ kx = kx + 1;}
		*sx = *sx + rep - 1;
		return( kx );
}
LONG	XasmDIVUXB( LONG ax, LONG bx, LONG *sx, LONG rep )
{
LONG	i,kx;
		if( (ULONG)ax < (ULONG)bx )
		{
			ax = (ax<<1); *sx = *sx + 1;
		}
		for( kx=0,i=0; i<rep; i++ )
		{
			kx = (kx<<1);
			if( (ULONG)ax >= (ULONG)bx )
			{
				kx = kx + 1;
				ax = (ULONG)ax - (ULONG)bx;
			}
			ax = (ax<<1);
		}
		if( (ULONG)ax >= (ULONG)bx ){ kx = kx + 1;}
		*sx = *sx + rep - 1;
		return( kx );
}
LONG	XasmMulhigh32down( LONG a, LONG b )
{
LONG	xx[2];
		MUL3232( a, b, xx );
		return( xx[1] );
}
 
 
 
 LONG	MlibLimitul( LONG u, LONG ulim, LONG llim )
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
 float   FlibLimitul( float u, float ulim, float llim )
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
 
#ifdef RunRAM
#pragma CODE_SECTION(MlibMulgain, ".TI.ramfunc");
#endif
 LONG	MlibMulgain( LONG u, LONG k )
{
LONG	x;
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
 		MUL3232( u, kx, xx );
		x = (xx[1] >> sx);
		if( x > 0 )
		{
			return(  0x01000000 );
		}
		else if( x < -1 )
		{
			return( -0x01000000 );
		}
		else
		{
			return( (xx[1]<<(24-sx)) + (((((ULONG)xx[0]>>sx)>>7)+1)>>1) );
		}
 }
 
 
 LONG	MlibMulgain27( LONG u, LONG k )
{
LONG	x;
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
 		MUL3232( u, kx, xx );
		x = ((xx[1]>>sx)>>2);
		if( x > 0 )
		{
			return(  0x04000000 );
		}
		else if( x < -1 )
		{
			return( -0x04000000 );
		}
		else
		{
			return( (xx[1]<<(24-sx)) + (((((ULONG)xx[0]>>sx)>>7)+1)>>1) );
		}
 }
 
 
 LONG	MlibMulgain29( LONG u, LONG k )
{
LONG	x;
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
 		MUL3232( u, kx, xx );
		x = ((xx[1]>>sx)>>4);
		if( x > 0 )
		{
			return(  0x0FFFFFFF );
		}
		else if( x < -1 )
		{
			return( -0x10000000 );
		}
		else
		{
			x = (xx[1]<<(24-sx)) + (((((ULONG)xx[0]>>sx)>>7)+1)>>1);
			if( x > 0x0FFFFFFF ){ x = 0x0FFFFFFF;}
			return( x );
		}
 }
 
 
 LONG	MlibMulgain30( LONG u, LONG k )
{
LONG	x;
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
 		MUL3232( u, kx, xx );
		x = ((xx[1]>>sx)>>5);
		if( x > 0 )
		{
			return(  0x1FFFFFFF );
		}
		else if( x < -1 )
		{
			return( -0x20000000 );
		}
		else
		{
			x = (xx[1]<<(24-sx)) + (((((ULONG)xx[0]>>sx)>>7)+1)>>1);
			if( x > 0x1FFFFFFF ){ x = 0x1FFFFFFF;}
			return( x );
		}
 }
 
 
 LONG	MlibMulgain32( LONG u, LONG k )
{
LONG	x;
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
 		MUL3232( u, kx, xx );
		x = ((xx[1]>>sx)>>7);
		if( x > 0 )
		{
			return(  0x7FFFFFFF );
		}
		else if( x < -1 )
		{
			return(  0x80000000 );
		}
		else
		{
			x = (xx[1]<<(24-sx)) + (((((ULONG)xx[0]>>sx)>>7)+1)>>1);
			if( (xx[1]>=0)&&(x<0) ) return( 0x7fffffff );
			return( x );
		}
 }
 
 
 LONG	MlibMulgainSx48( LONG u, LONG k )
{
LONG	x;
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
 		MUL3232( u, kx, xx );
		if( sx <= 24 )
		{
			if( (xx[1]>>sx) > 0 )
			{
				return(  0x01000000 );
			}
			else if( (xx[1]>>sx) < -1 )
			{
				return( -0x01000000 );
			}
			else
			{
				return( (xx[1]<<(24-sx)) + (((((ULONG)xx[0]>>sx)>>7)+1)>>1) );
			}
		}
		else
		{
			x = (((xx[1]>>(sx-25))+1)>>1);
			if( x >= 0x01000000 )
			{
				return(  0x01000000 );
			}
			else if( x <= -0x01000000 )
			{
				return( -0x01000000 );
			}
			else
			{
				return( x );
			}
		}
 }
 
 
 LONG	MlibMulgainNolim( LONG u, LONG k )
{
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
 		MUL3232( u, kx, xx );
		return( (xx[1]<<(24-sx)) + (((((ULONG)xx[0]>>sx)>>7)+1)>>1) );
 }
 
  
  
  
LONG	MlibIntegral( LONG u, LONG k, LONG iu[2] )
{
LONG	x;
LONG	xx[2];
LONG	carry;
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
  
 		MUL3232( u, kx, xx );
		x = (xx[1] >> sx);
  
 		if( x > 0 )
		{
			iu[1] = iu[1] + (LONG)0x02000000;
		}
		else if( x < -1 )
		{
			iu[1] = iu[1] - (LONG)0x02000000;
		}
		else
		{
			carry = ( (ULONG)(iu[0]+(xx[0]<<(25-sx))) < (ULONG)iu[0] );
			iu[0] = iu[0] + (xx[0]<<(25-sx));
			iu[1] = iu[1] + (xx[1]<<(25-sx)) + (((ULONG)xx[0]>>sx)>>7) + carry;
		}
  
 		if( iu[1] >= (LONG)0x02000000 )
		{
			iu[0] = 0;
			iu[1] = 0x02000000;
		}
		else if( iu[1] < (LONG)-0x02000000 )
		{
			iu[0] =  0;
			iu[1] = -0x02000000;
		}
		return( ((iu[1]+1)>>1) );
 }
 
  
  
 float   flibIntegral( float u, float k, float *iu )
{
float ax;
  
         ax = (u * k);
  
  
        *iu = *iu + ax;
  
         if( *iu >= 33554432.0f )
        {
            *iu = 33554432.0f;
        }
        else if( *iu < -33554432.0f)
        {
            *iu =  -33554432.0f;
        }
        return( *iu );
}
 
 LONG	MlibKrMulgain( LONG u, LONG k, LONG r )
{
LONG	x;
LONG	kr[2];
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
 		MULU32U32( r, 1759218604, xx );
		MUL3232( kx, xx[1], kr );
		kr[1] = ((kr[1]+2)>>2);
		MUL3232( u, kr[1], xx );
		x = (xx[1]<<(31-sx)) + (((ULONG)xx[0]>>sx)>>1);
		if( (xx[1]>>sx) > 0 )
		{
			return(  0x01000000 );
		}
		else if( (xx[1]>>sx) < -1 )
		{
			return( -0x01000000 );
		}
		else if( x > 0x02000000 )
		{
			return(  0x01000000 );
		}
		else if( x < -0x02000000 )
		{
			return( -0x01000000 );
		}
		return( (x + 1)>>1 );
}
 
 
 LONG	MlibKrMulgain27( LONG u, LONG k, LONG r )
{
LONG	x;
LONG	kr[2];
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
 		MULU32U32( r, 1759218604, xx );
		MUL3232( kx, xx[1], kr );
		kr[1] = ((kr[1]+2)>>2);
		MUL3232( u, kr[1], xx );
		x = (xx[1]<<(31-sx)) + (((ULONG)xx[0]>>sx)>>1);
		if( (xx[1]>>sx) > 0 )
		{
			return(  0x04000000 );
		}
		else if( (xx[1]>>sx) < -1 )
		{
			return( -0x04000000 );
		}
		else if( x > 0x08000000 )
		{
			return(  0x04000000 );
		}
		else if( x < -0x08000000 )
		{
			return( -0x04000000 );
		}
		return( (x + 1)>>1 );
}
 
 
 LONG	MlibKrIntegral( LONG u, LONG k, LONG r, LONG iu[2] )
{
LONG	x;
LONG	kr[2];
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
 		MULU32U32( r, 1759218604, xx );
		MUL3232( kx, xx[1], kr );
		kr[1] = ((kr[1]+2)>>2);
		MUL3232( u, kr[1], xx );
		x = (xx[1]<<(31-sx)) + (((ULONG)xx[0]>>sx)>>1);
		if( (xx[1]>>sx) > 0 )
		{
			iu[1] = iu[1] + (LONG)0x02000000;
		}
		else if( (xx[1]>>sx) < -1 )
		{
			iu[1] = iu[1] - (LONG)0x02000000;
		}
		else if( x >= 0x02000000 )
		{
			iu[1] = iu[1] + (LONG)0x02000000;
		}
		else if( x < -0x02000000 )
		{
			iu[1] = iu[1] - (LONG)0x02000000;
		}
		else
		{
			iu[0] = iu[0] + (xx[0]<<(31-sx));
			iu[1] = iu[1] + x + ((ULONG)iu[0] < (ULONG)(xx[0]<<(31-sx)));
		}
		if( iu[1] >= (LONG)0x02000000 )
		{
			iu[0] = 0;
			iu[1] = 0x02000000;
		}
		else if( iu[1] < (LONG)-0x02000000 )
		{
			iu[0] =  0;
			iu[1] = -0x02000000;
		}
		return( ((iu[1]+1)>>1) );
}
 
 
 LONG	MlibSymMulgain( LONG u, LONG k )
{
LONG	x;
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
 		MUL3232( u, kx, xx );
		x = (xx[1] >> sx);
		if( x > 0 )
		{
			return(  0x01000000 );
		}
		else if( x < -1 )
		{
			return( -0x01000000 );
		}
		else
		{
			xx[1] = (xx[1] << (24-sx));
			xx[0] = (xx[0]==0)? xx[0] : (xx[0] + x);
			xx[0] = ((((ULONG)xx[0]>>sx) + 0x0080)>>8);
			return( xx[1] + xx[0] );
		}
 }
 
 
 LONG	MlibSymMulgainNolim( LONG u, LONG k )
{
LONG	x;
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
 		MUL3232( u, kx, xx );
		x = (xx[1] >> 31);
		xx[1] = (xx[1] << (24-sx));
		xx[0] = (xx[0]==0)? xx[0] : (xx[0] + x);
		xx[0] = ((((ULONG)xx[0]>>sx) + 0x0080)>>8);
		return( xx[1] + xx[0] );
 }
 
 
 LONG	MlibSymIntegral( LONG u, LONG k, LONG iu[2] )
{
LONG	x;
LONG	xx[2];
LONG	carry;
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
 		MUL3232( u, kx, xx );
		x = (xx[1] >> sx);
		if( x > 0 )
		{
			iu[1] = iu[1] + (LONG)0x02000000;
		}
		else if( x < -1 )
		{
			iu[1] = iu[1] - (LONG)0x02000000;
		}
		else
		{
			carry = ( (ULONG)(iu[0]+(xx[0]<<(25-sx))) < (ULONG)iu[0] );
			iu[0] = iu[0] + (xx[0]<<(25-sx));
			iu[1] = iu[1] + (xx[1]<<(25-sx)) + (((ULONG)xx[0]>>sx)>>7) + carry;
		}
		if( iu[1] >= (LONG)0x02000000 )
		{
			iu[0] = 0;
			iu[1] = 0x02000000;
		}
		else if( iu[1] < (LONG)-0x02000000 )
		{
			iu[0] =  0;
			iu[1] = -0x02000000;
		}
		x = (iu[1] >= 0)? 1 : ((iu[0] != 0)? 1 : 0);
		return( ((iu[1]+x)>>1) );
 }
 
 
 LONG	MlibPfbkxremLim( LONG u, LONG k, LONG *pfbrem )
{
LONG	x;
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = ((ULONG)k)>>24;
LONG	remx = *pfbrem;
 		MUL3232( u, kx, xx );
 		if( sx <= 24 )
		{
			if( (xx[1]>>sx) > 0 )
			{
				*pfbrem = 0;
				return(  0x01000000 );
			}
			else if( (xx[1]>>sx) < -1 )
			{
				*pfbrem = 0;
				return( -0x01000000 );
			}
			else
			{
				x = (xx[1]<<(24-sx)) + ((((ULONG)xx[0])>>sx)>>8);
				remx = remx + (((ULONG)xx[0]<<(24-sx))>>8);
			}
		}
		else
		{
			x = xx[1]>>(sx-24);
			if( x >= 0x01000000 )
			{
				*pfbrem = 0;
				return(  0x01000000 );
			}
			else if( x <= -0x01000000 )
			{
				*pfbrem = 0;
				return( -0x01000000 );
			}
			else
			{
				remx = remx + (((ULONG)xx[1]<<(56-sx))>>8) + (((((ULONG)xx[0]>>(sx-24))>>7)+1)>>1);
			}
		}
		if( remx >= (LONG)0x00800000 )
		{
			x = x + 1;
			remx = remx - (LONG)0x00800000;
			remx = remx - (LONG)0x00800000;
		}
		*pfbrem = remx;
		return( x );
 }
 
 
 LONG	MlibPfbkxremNolim( LONG u, LONG k, LONG *pfbrem )
{
LONG	x;
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = ((ULONG)k)>>24;
LONG	remx = *pfbrem;
 		MUL3232( u, kx, xx );
 		if( sx <= 24 )
		{
			x = (xx[1]<<(24-sx)) + ((((ULONG)xx[0])>>sx)>>8);
			remx = remx + (((ULONG)xx[0]<<(24-sx))>>8);
		}
		else
		{
			x = xx[1]>>(sx-24);
			remx = remx + (((ULONG)xx[1]<<(56-sx))>>8) + (((((ULONG)xx[0]>>(sx-24))>>7)+1)>>1);
		}
		if( remx >= (LONG)0x00800000 )
		{
			x = x + 1;
			remx = remx - (LONG)0x00800000;
			remx = remx - (LONG)0x00800000;
		}
		*pfbrem = remx;
		return( x );
 }
 
 
 LONG	MlibMulkprem( LONG u, LONG k, LONG pfbrem )
{
LONG	x;
LONG	xx1[2];
LONG	xx2[2];
LONG	carry;
LONG	kx = (k<<8);
LONG	sx = ((ULONG)k)>>24;
 		MUL3232( u,      kx, xx1 );
		MUL3232( pfbrem, kx, xx2 );
 		x = (xx2[1]<<8) + ((ULONG)xx2[0]>>24);
		carry  = ( (ULONG)xx1[0] < (ULONG)x );
		xx1[0] = (ULONG)xx1[0] - (ULONG)x;
		xx1[1] = xx1[1] - (xx2[1]>>24) - carry;
 		if( (xx1[1]>>sx) > 0 )
		{
			return(  0x01000000 );
		}
		else if( (xx1[1]>>sx) < -1 )
		{
			return( -0x01000000 );
		}
		else
		{
			return( (xx1[1]<<(24-sx)) + (((((ULONG)xx1[0]>>sx)>>7)+1)>>1) );
		}
 }
 
 
 LONG	MlibMulkxBiasrem( LONG u, LONG k, LONG *rem, LONG bias )
{
LONG	x;
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
LONG	kb = (bias<<8);
LONG	sb = (((ULONG)bias)>>24);
 		MUL3232( u, kx, xx );
		*rem = *rem + ((ULONG)(xx[0]<<(24-sx))>>8);
		x = (xx[1]<<(24-sx)) + (((ULONG)xx[0]>>sx)>>8);
		if( *rem >= 0x00800000 )
		{
			x = x + 1;
			*rem = *rem - 0x01000000;
		}
		if( u >= 0 )
		{
			x = x + (((ULONG)kb>>sb)>>8);
			*rem = *rem + ((ULONG)(kb<<(24-sb))>>8);
			if( *rem >= 0x00800000 )
			{
				x = x + 1;
				*rem = *rem - 0x01000000;
			}
		}
		else
		{
			x = x - (((ULONG)kb>>sb)>>8);
			*rem = *rem - ((ULONG)(kb<<(24-sb))>>8);
			if( *rem < -0x00800000 )
			{
				x = x - 1;
				*rem = *rem + 0x01000000;
			}
		}
		return( x );
 }
 
 LONG	MlibMulkxBiasremOld( LONG u, LONG k, LONG *rem, LONG bias )
{
LONG	x;
LONG	xx[2];
LONG	kx = (k<<8);
LONG	sx = (((ULONG)k)>>24);
LONG	kb = (bias<<8);
LONG	sb = (((ULONG)bias)>>24);
 		MUL3232( u, kx, xx );
		*rem = *rem + ((ULONG)(xx[0]<<(24-sx))>>8);
		x = (xx[1]<<(24-sx)) + (((ULONG)xx[0]>>sx)>>8);
		if( u >= 0 )
		{
			x = x + (((ULONG)kb>>sb)>>8);
			*rem = *rem + ((ULONG)(kb<<(24-sb))>>8);
			if( *rem >= 0x00800000 )
			{
				x = x + 1;
				*rem = *rem - 0x00800000;
				*rem = *rem - 0x00800000;
			}
		}
		else
		{
			x = x - (((ULONG)kb>>sb)>>8);
			*rem = *rem - ((ULONG)(kb<<(24-sb))>>8);
			if( *rem >= 0x00800000 )
			{
				x = x + 1;
				*rem = *rem - 0x00800000;
				*rem = *rem - 0x00800000;
			}
		}
		return( x );
 }
 LONG	MlibKrLpfilter1( LONG u, LONG k, LONG r, LONG x )
{
LONG	kr;
LONG	wk1;
LONG	xx[2];
 		if( k == 0 )
		{
			return( u );
		}
		MULU32U32( r, 1759218604, xx );
		MUL3232( k, xx[1], xx );
		kr = (xx[1]<<4) + ((((ULONG)xx[0]>>27)+1)>>1);
		if( (((ULONG)xx[1]>>28) != 0) || ((ULONG)kr > (ULONG)0x01000000) )
		{
			kr = 0x01000000;
		}
		MUL3232( (u-x), kr, xx );
		wk1 = (xx[1]<<8) + (((((ULONG)xx[0])>>23)+1)>>1);
		if( wk1 == 0 )
		{
			return( x + ((u-x)>0) - ((u-x)<0) );
		}
		else
		{
			return( x + wk1 );
		}
 }
 
  
  
 LONG	MlibHpfilter1( LONG u, LONG k, LONG *z )
{
LONG	wk1;
LONG	xx[2];
 		if( k == 0 )
		{
			*z = 0;
			return( u );
		}
		MUL3232( (u-*z), k, xx );
		wk1 = (xx[1]<<8) + (((((ULONG)xx[0])>>23)+1)>>1);
		if( wk1 == 0 )
		{
			*z = *z + ((u-*z)>0) - ((u-*z)<0);
		}
		else
		{
			*z = *z + wk1;
		}
		return( u - *z );
 }
 LONG	MlibLpfilter2( LONG u, LONG k[2], LONG z[3] )
{
LONG	wk1;
LONG	wk2;
LONG	xx[2];
LONG	carry;
LONG	kx,sx;
 		if( k[0] == 0 )
		{
			z[0] = 0;
			z[1] = 0;
			z[2] = 0;
			return( u );
		}
		wk1 = u - ((z[2]+1)>>1) - z[0];
		MUL3232( wk1, k[0], xx );
		wk2 = (xx[1]<<8) + (((((ULONG)xx[0])>>23)+1)>>1);
		if( wk2==0 )
		{
			z[0] = z[0] + (wk1>0) - (wk1<0);
		}
		else
		{
			z[0] = z[0] + wk2;
		}
		kx = (k[1]<<8);
		sx = (((ULONG)k[1])>>24);
		MUL3232( z[0], kx, xx );
		carry = ( (ULONG)(z[1]+(xx[0]<<(25-sx))) < (ULONG)z[1] );
		z[1] = z[1] + (xx[0]<<(25-sx));
		z[2] = z[2] + (xx[1]<<(25-sx)) + (((ULONG)xx[0]>>sx)>>7) + carry;
		return( ((z[2]+1)>>1) );
 }
 
 
 LONG	MlibNxfilter2( LONG u, LONG k[3], LONG z[3] )
{
LONG	wk1;
LONG	wk2;
LONG	xx[2];
LONG	carry;
LONG	kx,sx;
 		if( k[0] == 0 )
		{
			z[0] = 0;
			z[1] = 0;
			z[2] = 0;
			return( u );
		}
		wk1 = u - ((z[2]+1)>>1) - z[0];
		MUL3232( wk1, k[0], xx );
		wk2 = (xx[1]<<8) + (((((ULONG)xx[0])>>23)+1)>>1);
		if( wk2==0 )
		{
			z[0] = z[0] + (wk1>0) - (wk1<0);
		}
		else
		{
			z[0] = z[0] + wk2;
		}
		kx = (k[1]<<8);
		sx = (((ULONG)k[1])>>24);
		MUL3232( z[0], kx, xx );
		carry = ( (ULONG)(z[1]+(xx[0]<<(25-sx))) < (ULONG)z[1] );
		z[1] = z[1] + (xx[0]<<(25-sx));
		z[2] = z[2] + (xx[1]<<(25-sx)) + (((ULONG)xx[0]>>sx)>>7) + carry;
		wk1 = ((z[2]+1)>>1);
		MUL3232( u-wk1-z[0], k[2], xx );
		wk2 = (xx[1]<<8) + (((((ULONG)xx[0])>>23)+1)>>1) + wk1;
		return( wk2 );
 }
 
 
 LONG	MlibLaufilter(
		LONG	u,
		LONG	z,
		LONG	dz )
{
LONG	x;
 		if( dz == 0 )
		{
			x = u;
		}
		else if( u > z )
		{
			x = z + dz;
			if( x > u ){ x = u;}
		}
		else
		{
			x = z - dz;
			if( x < u ){ x = u;}
		}
		return( x );
 }
 
 
 
 LONG	MlibPcalKxgain( LONG a, LONG b, LONG c, LONG *psx, LONG smax )
{
LONG	wk;
LONG	kx;
LONG	sx;
LONG	sy;
LONG	sign;
LONG	x,xx[2];
 		sx = (psx != NULL)? (*psx) : 0;
		if( (a==0)||(b==0)||(c==0) )
		{
			if( psx != NULL ){ *psx = 0;}
			return( 0 );
		}
		sign = 0;
		if( a < 0 ){ a=-a; sign=sign^0x01;}
		if( b < 0 ){ b=-b; sign=sign^0x01;}
		if( c < 0 ){ c=-c; sign=sign^0x01;}
		MULU32U32( a, b, xx );
		if( xx[1] > 0 )  
		{
			sy = 32;
			x  = xx[1];
			SCUP31_SXDEC( x, sy, wk );
			x = x + (((ULONG)xx[0])>>(sy));
			sx = sx - sy;
		}
		else if( xx[0] > 0 )
		{
			x  = xx[0];
			SCUP31_SXINC( x, sx, wk );
		}
		else
		{
			sx = sx - 1;
			x  = (((ULONG)xx[0])>>1);
		}
		SCUP31_SXDEC( c, sx, wk );
		kx = XasmDIVUXA( x, c, &sx, 24 );
		if( smax == 0 )
		{
			if( sign ){ kx = -kx;}
		}
		else if( smax > 0 )
		{
			kx = kx>>1; sx = sx - 1;
			if( (sx-smax)>31 ){ kx = 0;}
			if(  sx < 0      ){ kx=0x007FFFFF; sx=0;}
			if(  sx > smax   ){ kx=(kx>>(sx-smax)); sx=smax;}
			if(  sign != 0   ){ kx = -kx;}
			kx = (sx<<24) + (kx&0x00FFFFFF);
		}
		else if( smax == -1 )
		{
			kx = kx>>1; sx = sx - 1;
			if( (sx > 127) || (sx < -128) )
			{
				kx = sx = 0;
			}
			if( sign != 0 ){ kx = -kx;}
			kx = (sx<<24) + (kx&0x00FFFFFF);
		}
		else if( (smax == -2) && CCSW_HsMulgain )
		{
			sx = sx - 16;
			if( sx == 0 )      { kx = kx;        }
			else if( sx >= 24 ){ kx = 0;         }
			else if( sx <= -8 ){ kx = 0x7FFFFFFF;}
			else if( sx >= 0  ){ kx = kx>>sx;    }
			else               { kx = kx<<(-sx); }
			sx = 16;
			if( sign != 0 ){ kx = -kx;}
		}
		else if( smax == -24 )
		{
			if( sx < 0 )      { kx = 0x01000000;}
			else if( sx > 32 ){	kx = 0;         }
			else if( sx == 0 ){	kx = kx; 	}
			else   { kx = (((kx>>(sx-1))+1)>>1);}
			sx = 0;
			if( sign != 0  ){ kx = -kx;}
		}
		else
		{
			kx = kx << 6; sx = sx + 6;
			if( sx < 0 )      { kx = 0x40000000;}
			else if( sx > 32 ){	kx = 0;         }
			else if( sx == 0 ){	kx = kx; 	}
			else   { kx = (((kx>>(sx-1))+1)>>1);}
			sx = 0;
			if( sign != 0  ){ kx = -kx;}
		}
		if( psx != NULL ){ *psx = sx;}
		return( kx );
 }
 
 
 LONG	MlibPcalKskxkx( LONG ksa, LONG b, LONG c, LONG *psx, LONG smax )
{
LONG	a;
LONG	kx,sx;
 		a  = ((ksa<<8)>>8);
		sx = (ksa>>24);
		if( psx != NULL )
		{
			*psx += sx;
			kx = MlibPcalKxgain( a, b, c, psx, smax );
		}
		else
		{
			kx = MlibPcalKxgain( a, b, c, &sx, smax );
		}
		return( kx );
 }
 
 
 LONG	MlibPcalKxkskx( LONG a, LONG ksb, LONG c, LONG *psx, LONG smax )
{
LONG	b;
LONG	kx,sx;
 		b  = ((ksb<<8)>>8);
		sx = (ksb>>24);
		if( psx != NULL )
		{
			*psx += sx;
			kx = MlibPcalKxgain( a, b, c, psx, smax );
		}
		else
		{
			kx = MlibPcalKxgain( a, b, c, &sx, smax );
		}
		return( kx );
 }
 
 
 LONG	MlibPcalKxkxks( LONG a, LONG b, LONG ksc, LONG *psx, LONG smax )
{
LONG	c;
LONG	kx,sx;
 		c  = ((ksc<<8)>>8);
		sx = -(ksc>>24);
		if( psx != NULL )
		{
			*psx += sx;
			kx = MlibPcalKxgain( a, b, c, psx, smax );
		}
		else
		{
			kx = MlibPcalKxgain( a, b, c, &sx, smax );
		}
		return( kx );
 }
 
 
 LONG	MlibPcalKskskx( LONG ksa, LONG ksb, LONG c, LONG *psx, LONG smax )
{
LONG	a,b;
LONG	kx,sx;
 		a  = ((ksa<<8)>>8);
		b  = ((ksb<<8)>>8);
		sx = (ksa>>24) + (ksb>>24);
		if( psx != NULL )
		{
			*psx += sx;
			kx = MlibPcalKxgain( a, b, c, psx, smax );
		}
		else
		{
			kx = MlibPcalKxgain( a, b, c, &sx, smax );
		}
		return( kx );
 }
 
 
 LONG	MlibPcalKxksks( LONG a, LONG ksb, LONG ksc, LONG *psx, LONG smax )
{
LONG	b,c;
LONG	kx,sx;
 		b  = ((ksb<<8)>>8);
		c  = ((ksc<<8)>>8);
		sx = (ksb>>24) - (ksc>>24);
		if( psx != NULL )
		{
			*psx += sx;
			kx = MlibPcalKxgain( a, b, c, psx, smax );
		}
		else
		{
			kx = MlibPcalKxgain( a, b, c, &sx, smax );
		}
		return( kx );
 }
 
 
 LONG	MlibPcalKsksks( LONG ksa, LONG ksb, LONG ksc, LONG *psx, LONG smax )
{
LONG	a,b,c;
LONG	kx,sx;
 		a  = ((ksa<<8)>>8);
		b  = ((ksb<<8)>>8);
		c  = ((ksc<<8)>>8);
		sx = (ksa>>24) + (ksb>>24) - (ksc>>24);
		if( psx != NULL )
		{
			*psx += sx;
			kx = MlibPcalKxgain( a, b, c, psx, smax );
		}
		else
		{
			kx = MlibPcalKxgain( a, b, c, &sx, smax );
		}
		return( kx );
 }
 
 
 LONG	MlibScalKxgain( LONG a, LONG b, LONG c, LONG *psx, LONG smax )
{
LONG	kx;
 		if( psx != NULL ){ *psx = 0;}
		kx = MlibPcalKxgain( a, b, c, psx, smax );
		return( kx );
 }
 
 
 LONG	MlibScalKskxkx( LONG ksa, LONG b, LONG c, LONG *psx, LONG smax )
{
LONG	a;
LONG	kx,sx;
 		a  = ((ksa<<8)>>8);
		sx = (ksa>>24);
		if( psx != NULL )
		{
			*psx = sx;
			kx = MlibPcalKxgain( a, b, c, psx, smax );
		}
		else
		{
			kx = MlibPcalKxgain( a, b, c, &sx, smax );
		}
		return( kx );
 }
 
 
 LONG	MlibScalKxkskx( LONG a, LONG ksb, LONG c, LONG *psx, LONG smax )
{
LONG	b;
LONG	kx,sx;
 		b  = ((ksb<<8)>>8);
		sx = (ksb>>24);
		if( psx != NULL )
		{
			*psx = sx;
			kx = MlibPcalKxgain( a, b, c, psx, smax );
		}
		else
		{
			kx = MlibPcalKxgain( a, b, c, &sx, smax );
		}
		return( kx );
 }
 
 
 LONG	MlibScalKxkxks( LONG a, LONG b, LONG ksc, LONG *psx, LONG smax )
{
LONG	c;
LONG	kx,sx;
 		c  = ((ksc<<8)>>8);
		sx = -(ksc>>24);
		if( psx != NULL )
		{
			*psx = sx;
			kx = MlibPcalKxgain( a, b, c, psx, smax );
		}
		else
		{
			kx = MlibPcalKxgain( a, b, c, &sx, smax );
		}
		return( kx );
 }
 
 
 LONG	MlibScalKskskx( LONG ksa, LONG ksb, LONG c, LONG *psx, LONG smax )
{
LONG	a,b;
LONG	kx,sx;
 		a  = ((ksa<<8)>>8);
		b  = ((ksb<<8)>>8);
		sx = (ksa>>24) + (ksb>>24);
		if( psx != NULL )
		{
			*psx = sx;
			kx = MlibPcalKxgain( a, b, c, psx, smax );
		}
		else
		{
			kx = MlibPcalKxgain( a, b, c, &sx, smax );
		}
		return( kx );
 }
 
 
 LONG	MlibScalKxksks( LONG a, LONG ksb, LONG ksc, LONG *psx, LONG smax )
{
LONG	b,c;
LONG	kx,sx;
 		b  = ((ksb<<8)>>8);
		c  = ((ksc<<8)>>8);
		sx = (ksb>>24) - (ksc>>24);
		if( psx != NULL )
		{
			*psx = sx;
			kx = MlibPcalKxgain( a, b, c, psx, smax );
		}
		else
		{
			kx = MlibPcalKxgain( a, b, c, &sx, smax );
		}
		return( kx );
 }
 
 
 LONG	MlibScalKsksks( LONG ksa, LONG ksb, LONG ksc, LONG *psx, LONG smax )
{
LONG	a,b,c;
LONG	kx,sx;
 		a  = ((ksa<<8)>>8);
		b  = ((ksb<<8)>>8);
		c  = ((ksc<<8)>>8);
		sx = (ksa>>24) + (ksb>>24) - (ksc>>24);
		if( psx != NULL )
		{
			*psx = sx;
			kx = MlibPcalKxgain( a, b, c, psx, smax );
		}
		else
		{
			kx = MlibPcalKxgain( a, b, c, &sx, smax );
		}
		return( kx );
 }
 
 
 LONG	MlibPcalKxaddx( LONG ka, LONG sa, LONG kb, LONG sb, LONG *psx )
{
LONG	kx;
LONG	ds;
 		ds = sa - sb;
		if( ka ==   0 ){ *psx = sb; return( kb );}
		if( kb ==   0 ){ *psx = sa; return( ka );}
		if( ds >=  32 ){ *psx = sb; return( kb );}
		if( ds <= -32 ){ *psx = sa; return( ka );}
		if( ds < 0 ){ kb = (kb>>(-ds));}
		if( ds > 0 ){ ka = (ka>>ds); sa = sb;}
		kx = ka + kb;
		if( ((ka>0)&&(kb>0)&&(kx<=0)) || ((ka<0)&&(kb<0)&&(kx>=0)) )
		{
			kx = (ka>>1) + (kb>>1); sa--;
		}
		if( kx == 0 ){ sa = 0;}
		*psx = sa;
		return( kx );
 }
 
 
 LONG	MlibPcalKxsubx( LONG ka, LONG sa, LONG kb, LONG sb, LONG *psx )
{
LONG	kx;
LONG	ds;
 		ds = sa - sb;
		if( (ka == 0) || (ds >= 32)  )
		{
			if( kb == 0x80000000 )
			{
				kb = kb >> 1; sb--;
			}
			*psx = sb; return( -kb );
		}
		if( kb ==   0 ){ *psx = sa; return(  ka );}
		if( ds <= -32 ){ *psx = sa; return(  ka );}
		if( ds < 0 ){ kb = (kb>>(-ds));}
		if( ds > 0 ){ ka = (ka>>ds); sa = sb;}
		kx = ka - kb;
		if( ((ka>0)&&(kb<0)&&(kx<=0)) || ((ka<0)&&(kb>0)&&(kx>=0)) )
		{
			kx = (ka>>1) - (kb>>1); sa--;
		}
		if( kx == 0 ){ sa = 0;}
		*psx = sa;
		return( kx );
 }
 
 
 LONG	MlibPcalKxmulx( LONG a, LONG b, LONG c, LONG *psx )
{
LONG	kx;
LONG	sx;
LONG	wk;
LONG	sign;
LONG	xx[2];
LONG	yy[2];
LONG	zz[2];
LONG	xxx[3];
 		if( (a==0)||(b==0)||(c==0) )
		{
			*psx = 0;
			return( 0 );
		}
		sign = 0;
		if( a < 0 ) { a = -a; sign =  1;}
		if( b < 0 ) { b = -b; sign += 1;}
		if( c < 0 ) { c = -c; sign += 1;}
		MULU32U32( (ULONG)a,     (ULONG)b, (ULONG*)xx );
		MULU32U32( (ULONG)xx[0], (ULONG)c, (ULONG*)yy );
		MULU32U32( (ULONG)xx[1], (ULONG)c, (ULONG*)zz );
		xxx[0] = yy[0];
		xxx[1] = zz[0] + yy[1];
		xxx[2] = zz[1];
		if( ((ULONG)xxx[1]<(ULONG)zz[0])||((ULONG)xxx[1]<(ULONG)yy[1]) )
		{
			xxx[2] = xxx[2] + 1;
		}
		if( xxx[2] != 0 )
		{
			sx = 0;
			kx = xxx[2];
			SCUP31_SXINC( kx, sx, wk );
			kx = kx + (((ULONG)xxx[1])>>(32-sx));
			sx = sx - 64;
		}
		else if( xxx[1] != 0 )
		{
			if( xxx[1] < 0 )
			{
				sx = -33;
				kx = (((ULONG)xxx[1])>>1);
			}
			else
			{
				sx = 0;
				kx = xxx[1];
				SCUP31_SXINC( kx, sx, wk );
				kx = kx + ((((ULONG)xxx[0])>>(31-sx))>>1);
				sx = sx - 32;
			}
		}
		else
		{
			if( xxx[0] < 0 )
			{
				sx = -1;
				kx = (((ULONG)xxx[0])>>1);
			}
			else
			{
				sx = 0;
				kx = xxx[0];
				SCUP31_SXINC( kx, sx, wk );
			}
		}
		*psx = *psx + sx;
		if( sign & 0x01 )
		{
			return( -kx );
		}
		else
		{
			return(  kx );
		}
 }
 
 
 LONG	MlibPcalKxdivx( LONG ka, LONG sa, LONG kb, LONG sb, LONG smax )
{
LONG	kx;
LONG	sx;
LONG	wk;
LONG	sign;
 		if( (ka==0)||(kb==0) )
		{
			return( 0 );
		}
		sign = 0;
		if( ka < 0 ) { ka = -ka; sign =  1;}
		if( kb < 0 ) { kb = -kb; sign += 1;}
		sx = sa - sb;
		SCUP31_SXINC( ka, sx, wk );
		SCUP31_SXDEC( kb, sx, wk );
		kx = XasmDIVUXA( ka, kb, &sx, 23 );
		if( (sx-smax)>31 ){ kx = 0;}
		if( sx > smax    ){ kx=(kx>>(sx-smax)); sx=smax;}
		if( sx < 0       ){ kx=0x007FFFFF;      sx=0;   }
		if( sign & 0x01  ){ kx = -kx;}
		kx = (sx<<24) + (kx&0x00FFFFFF);
		return( kx );
 }
 
 
 LONG	MlibPcalKf1gain(
		LONG	tx,
		LONG	ts,
		LONG	insel	)
{
LONG	kx;
LONG	ax;
LONG	bx;
ULONG	xx[2];
 		if( (tx == 0) || (ts == 0) )
		{
			return( 0 );
		}
		if( (insel & 0x0F) == 0x00 )
		{
			ax = ts;
			bx = ts + tx;
		}
		else if( (insel & 0xF0) == 0x00 )
		{
			MULU32U32( ts, tx, xx );
			if( xx[1] > 0x00 ){ return( 0 );}
			if( xx[0] >= 0x10000000 ){ ax = (xx[0]>>2); bx = ax +  397887;}
			else                     { ax = (xx[0]<<2); bx = ax + 6366198;}
		}
		else if( ts >= 1000 )
		{
			MULU32U32( ts, tx, xx );
			if( xx[1] > 0xFF ){ return( 0 );}
			bx = (1591549431 >> 2);
			if(      xx[1] > 0x0F ){ ax = (xx[0]>>10) + (xx[1]<<22); bx = ax + (bx>>8);}
			else if( xx[1] > 0x00 ){ ax = (xx[0]>> 6) + (xx[1]<<26); bx = ax + (bx>>4);}
			else                   { ax = (xx[0]>> 2)              ; bx = ax + (bx>>0);}
		}
		else
		{
			return( 0 );
		}
		kx = XasmDIVUB( ax, bx, 24 );
		return( kx );
 }
 #if (FLOAT_USE == 1)
  
  
  
  
  
  
 float   FlibPcalKf1gain(
        LONG    tx,          
        LONG    ts,          
        LONG    insel   )    
{
    long    Klpf;
    float   fKlpf;
     Klpf = MlibPcalKf1gain( tx, ts, insel );
    fKlpf = (float)Klpf / (float)( 1UL << 24 );
     return( fKlpf );
}
#endif  
 
 void	MlibPcalKf2gain(
		LONG	hz,
		LONG	dx,
		LONG	ts,
		LONG	kf[2],
		LONG	insel	)
{
LONG	sx;
LONG	ax,as;
LONG	bx,bs;
LONG	kx[2];
LONG	kunit = ((insel & 0xF0)==0)? 1 : 1000;
 		if( (hz == 0) || (ts == 0) || ((insel & 0xF0)&&(ts < 1000)) )
		{
			kf[0] = kf[1] = 0;
			return;
		}
		if( dx <    50 ){ dx =    50;}
		if( dx > 10000 ){ dx = 10000;}
		as = bs = 0;
		ax = MlibPcalKxmulx( ts,    hz,        dx, &as ) >> 1;
		bx = MlibPcalKxmulx( kunit, 795774715, 1,  &bs ) >> 1;
		if( as > bs ){ ax = ax >> (as - bs);}
		if( bs > as ){ bx = bx >> (bs - as);}
		kx[0] = XasmDIVUB( ax, (ax+bx), 24 );
		as = bs = 0;
		ax = MlibPcalKxmulx( ts,    hz, 100000,    &as );
		bx = MlibPcalKxmulx( kunit, dx, 318309886, &bs );
		sx = as - bs;
		kx[1] = XasmDIVUXB( ax, bx, &sx, 23 );
		if( (sx-24) > 31 ){ kx[1] = 0; sx = 24;}
		else if( sx > 24 ){ kx[1] = (kx[1]>>(sx-24)); sx = 24;}
		if( kx[1] == 0   ){ kx[1] = 1;}
		kx[1] = kx[1] + (sx<<24);
		kf[0] = kx[0];
		kf[1] = kx[1];
		return;
 }
 
 
 void	MlibPcalKnf2gain(
		LONG	hz,
		LONG	qx,
		LONG	kn,
		LONG	ts,
		LONG	kf[3],
		LONG	insel	)
{
LONG	sx;
LONG	ax,as;
LONG	bx,bs;
LONG	kx[3];
LONG	xx[2];
LONG	qxshl;
LONG	kunit = ((insel & 0xF0)==0)? 1 : 1000;
 		if( (hz == 0) || (ts == 0) || ((insel & 0xF0)&&(ts < 1000)) )
		{
			kf[0] = kf[1] = kf[2] = 0;
			return;
		}
		if( (insel & 0x0F) == 0x00 )
		{
			if( qx <    50 ){ qx =    50;}
			if( qx > 10000 ){ qx = 10000;}
			qxshl = 0;
		}
		else
		{
			if( qx <    50 ){ qx =    50;}
			if( qx > 10000 ){ qx = 10000;}
			qx = (500000<<12)/qx;
			qxshl = 12;
		}
		if( kn > 10000 ){ kn = 10000;}
		as = 0; bs = qxshl;
		ax = MlibPcalKxmulx( ts,    hz, 100000,    &as ) >> 1;
		bx = MlibPcalKxmulx( kunit, qx, 159154943, &bs ) >> 1;
		if( as > bs ){ ax = ax >> (as - bs);}
		if( bs > as ){ bx = bx >> (bs - as);}
		kx[0] = XasmDIVUB( ax, (ax+bx), 24 );
		as = qxshl; bs = 0;
		ax = MlibPcalKxmulx( ts,    hz,         qx, &as );
		bx = MlibPcalKxmulx( kunit, 1591549431, 1,  &bs );
		sx = as - bs;
		kx[1] = XasmDIVUXB( ax, bx, &sx, 23 );
		if( (sx-24) > 31 ){ kx[1] = 0; sx = 24;}
		else if( sx > 24 ){ kx[1] = (kx[1]>>(sx-24)); sx = 24;}
		if( kx[1] == 0   ){ kx[1] = 1;}
		kx[1] = kx[1] + (sx<<24);
		MULU32U32( (kn<<16), 1099511628, (ULONG*)xx );
		kx[2] = xx[1];
		kf[0] = kx[0];
		kf[1] = kx[1];
		kf[2] = kx[2];
		return;
 }
 
 
 
 LONG	MlibPcmdIpfil( LONG pcmdin, LONG shift, LONG index, PIPFV *pipfvar )
{
LONG	x;
LONG	outx;
 		if( shift == 0 )
		{
			return( pcmdin );
		}
 		if( index == 0 )
		{
			pipfvar->cmdx = pcmdin;
		}
 		x = pipfvar->cmdx + pipfvar->remx;
		outx = (x >> shift);
		pipfvar->remx = x - (outx << shift);
 		return( outx );
 }
 
 
 LONG	MlibPcmdMafil( LONG pcmdin, LONG pmafnum, PMAFV *pmafvar, LONG *pmafbuf )
{
LONG	subx;
LONG	outx;
 		if( pmafnum <= 1 )
		{
			pmafvar->zcntx = (pcmdin != 0)? 1 : 0;
			return( pcmdin );
		}
		subx = pmafvar->ksub * pmafbuf[pmafvar->idx];
		pmafbuf[pmafvar->idx] = pcmdin;
		if( ++pmafvar->idx >= pmafnum )
		{
			pmafvar->idx = 0;
			pmafvar->ksub = 1;
		}
		pmafvar->sumx = pmafvar->sumx - subx + pcmdin;
 #if(FLOAT_USE == 1)
		outx = (float)(pmafvar->sumx + pmafvar->remx) / (float)pmafnum;
#else
        outx = (pmafvar->sumx + pmafvar->remx)/pmafnum;
#endif
 		pmafvar->remx = (pmafvar->sumx + pmafvar->remx) - (pmafnum * outx);
		if( pcmdin != 0 )
		{
			pmafvar->zcntx = (USHORT)pmafnum;
		}
		else if( pmafvar->zcntx > 0 )
		{
			--pmafvar->zcntx;
		}
 		return( outx );
 }
 
 
 LONG	MlibPcmdImafil( LONG pcmdin, LONG shift, LONG index, PIMFV *pimfvar )
{
LONG	x;
LONG	outx;
 		if( shift == 0 )
		{
			pimfvar->zcntx = (pcmdin != 0)? 1 : 0;
			return( pcmdin );
		}
		if( index == 0 )
		{
			pimfvar->oldpcmd = pimfvar->newpcmd;
			pimfvar->newpcmd = pcmdin;
			if( pcmdin != 0 )
			{
				pimfvar->zcntx = (2 << shift);
			}
		}
		pimfvar->sumx = pimfvar->sumx + (pimfvar->newpcmd - pimfvar->oldpcmd);
		x = pimfvar->sumx + pimfvar->remx;
		outx = (x >> (2*shift));
		pimfvar->remx = x - (outx << (2*shift));
		if( pimfvar->zcntx > 0 )
		{
			--pimfvar->zcntx;
		}
 		return( outx );
 }
 
 
 LONG	MlibPcmdExpfil( LONG pcmdin, LONG kexp, LONG pbias, PEXFV *pexfvar )
{
LONG	outx;
LONG	xx[2];
LONG	kx = (kexp<<8);
LONG	sx = (((ULONG)kexp)>>24);
 		if( kexp == 0 )
		{
			pexfvar->sumx = 0;
			return( pcmdin );
		}
 		pexfvar->sumx = pexfvar->sumx + pcmdin;
 		MUL3232( pexfvar->sumx, kx, xx );
		outx = (xx[1]<<(24-sx)) + (((((ULONG)xx[0]>>sx)>>7)+1)>>1);
		if( pexfvar->sumx > pbias )
		{
			outx = outx + pbias;
			if( outx > pexfvar->sumx ){ outx = pexfvar->sumx;}
		}
		else if( pexfvar->sumx < -pbias )
		{
			outx = outx - pbias;
			if( outx < pexfvar->sumx ){ outx = pexfvar->sumx;}
		}
		else
		{
			outx = pexfvar->sumx;
		}
 		if( (outx==0)&&(pexfvar->sumx!=0) )
		{
			outx = (pexfvar->sumx > 0)? 1 : -1;
		}
 		pexfvar->sumx = pexfvar->sumx - outx;
		return( outx );
 }
 
 
 LONG	MlibPcmdLpfil1( LONG pcmdin, LONG kf, LONG *z )
{
LONG	x;
LONG	xx[2];
 		if( kf == 0 )
		{
			*z = 0;
			return( pcmdin );
		}
 		*z = *z + pcmdin;
 		MUL3232( *z, kf, xx );
		x  = (xx[1]<<8) + (((((ULONG)xx[0])>>23)+1)>>1);
 		if( (x==0) && (*z!=0) )
		{
			x = (*z>0)? 1 : -1;
		}
 		*z = *z - x;
		return( x );
}
 
 
 LONG	MlibPcmdLpfil2( LONG pcmdin, LONG kf[2], LONG z[2] )
{
LONG	x;
LONG	xx[2];
LONG	kx,sx;
 		if( kf[0] == 0 )
		{
			z[0] = z[1] = 0;
			return( pcmdin );
		}
 		z[0] = z[0] + pcmdin;
 		MUL3232( (z[0]-z[1]), kf[0], xx );
		x = (xx[1]<<8) + (((((ULONG)xx[0])>>23)+1)>>1);
		if( (x==0) && (z[1]!=z[0]) )
		{
			x = (z[0]>z[1]) - (z[0]<z[1]);
		}
		z[1] = z[1] + x;
 		kx = (kf[1]<<8);
		sx = (((ULONG)kf[1])>>24);
		MUL3232( z[1], kx, xx );
		x = (xx[1]<<(24-sx)) + (((((ULONG)xx[0]>>sx)>>7)+1)>>1);
		if( (x==0) && (z[0]!=0) )
		{
			x = (z[0] > 0)? 1 : -1;
		}
		z[0] = z[0] - x;
 		return( x );
 }
 
 
 LONG	MlibPcmdNxfil2( LONG pcmdin, LONG kf[3], LONG z[3] )
{
LONG	x,rv;
LONG	xx[2];
LONG	kx,sx;
 		if( kf[0] == 0 )
		{
			z[0] = z[1] = z[2] = 0;
			return( pcmdin );
		}
 		z[0] = z[0] + pcmdin;
 		MUL3232( (z[0]-z[1]), kf[0], xx );
		x = (xx[1]<<8) + (((((ULONG)xx[0])>>23)+1)>>1);
		if( (x==0) && (z[1]!=z[0]) )
		{
			x = (z[0]>z[1]) - (z[0]<z[1]);
		}
		z[1] = z[1] + x;
 		kx = (kf[1]<<8);
		sx = (((ULONG)kf[1])>>24);
		MUL3232( z[1], kx, xx );
		x = (xx[1]<<(24-sx)) + (((((ULONG)xx[0]>>sx)>>7)+1)>>1);
		if( (x==0) && (z[0]!=0) )
		{
			x = (z[0] > 0)? 1 : -1;
		}
		z[0] = z[0] - x;
 		MUL3232( z[1], kf[2], xx );
		x  = z[1] - ((xx[1]<<8) + (((((ULONG)xx[0])>>23)+1)>>1));
		rv = pcmdin - (x - z[2]);
		z[2] = x;
 		return( rv );
 }
 
 
 LONG	MlibPcmdEgear( LONG pcmda, EGEAR *egear, LONG *pcmdrem )
{
LONG	pcmdb;
LONG	wk1[2];
LONG	wk2[2];
 		MUL3232( pcmda, egear->k1, wk1 );
		MUL3232( pcmda, egear->k2, wk2 );
		pcmdb = wk1[0] + (wk2[1]<<1) + ((ULONG)wk2[0]>>31);
 		MUL3232( pcmda, egear->b, wk1 );
		MUL3232( pcmdb, egear->a, wk2 );
		*pcmdrem = *pcmdrem + ((ULONG)wk1[0] - (ULONG)wk2[0]);
 		if( *pcmdrem <  0                 ){ --pcmdb; *pcmdrem += egear->a;}
		if( *pcmdrem >= egear->a          ){ ++pcmdb; *pcmdrem -= egear->a;}
		if( *pcmdrem >= ((egear->a+1)>>1) ){ ++pcmdb; *pcmdrem -= egear->a;}
		return( pcmdb );
}
 LONG    FlibPcmdEgear( LONG pcmda, EGEAR *egear, LONG *pcmdrem )
{
    double df1,df2;
    LONG    outgr;               
    float Remain = (float)(*pcmdrem);
            df1 = (double )pcmda * egear->fb;
            df2 = df1 + Remain;
            outgr = (long)(df2 * egear->Reca);
            df1 = (double)outgr * egear->fa;
            *pcmdrem = (LONG)(df2 - df1);
            return( outgr );
}
 
  
  
  
LONG	MlibEgearRvscnv( LONG inpls, EGEAR *egear, LONG *plsrem )
{      
LONG	outgr;
LONG	wk1[2];
LONG	wk2[2];
  
  
		MUL3232( inpls, egear->g1, wk1 );
		MUL3232( inpls, egear->g2, wk2 );
		outgr = wk1[0] + (wk2[1]<<1) + ((ULONG)wk2[0]>>31);
  
  
		MUL3232( inpls, egear->a, wk1 );
		MUL3232( outgr, egear->b, wk2 );
		*plsrem = *plsrem + ((ULONG)wk1[0] - (ULONG)wk2[0]);
  
  
		if( *plsrem <  0                 ){ --outgr; *plsrem += egear->b;}
		if( *plsrem >= egear->b          ){ ++outgr; *plsrem -= egear->b;}
		if( *plsrem >= ((egear->b+1)>>1) ){ ++outgr; *plsrem -= egear->b;}
 		return( outgr );
 }
  
  
  
LONG flibEgearRvscnv( LONG inpls, EGEAR *egear, LONG *plsrem )
{
double df1,df2;
LONG    outgr;               
float Remain = (float)(*plsrem);
        df1 = (double )inpls * egear->fa;
        df2 = df1 + Remain;
        outgr = (long)(df2 * egear->Recb);
        df1 = (double)outgr * egear->fb;
        *plsrem = (LONG)(df2 - df1);
        return( outgr );
}
 
 
  
  
 void	MlibPcalKegear( LONG a, LONG b, EGEAR *egear )
{
ULONG	k1,k2;
ULONG	g1,g2;
  
  
		k1 = b/a;								 
		k2 = XasmDIVUA( (b%a), a, 31 );			 
  
  
		g1 = a/b;								 
		g2 = XasmDIVUA( (a%b), b, 31 );			 
  
  
		egear->a  = a;
		egear->b  = b;
		egear->k1 = k1;
		egear->k2 = k2;
		egear->g1 = g1;
		egear->g2 = g2;
 		egear->Reca = (double)1 / (double)a;
		egear->Recb = (double)1 / (double)b;
		egear->fa = (float)a;
		egear->fb = (float)b;
 		egear->adivb = (float)a / (float)b;
		egear->bdiva = (float)b / (float)a;
 		return;
 }
 
 
 
 
LONG	MlibPerrcalx( LONG pcmdx, LONG pfbkx, LONG per64[2] )
{
LONG	perrx;
LONG	carry;
LONG	perrchk;
 		perrx = pcmdx - pfbkx;
		carry = (((ULONG)(per64[0]+perrx)) < ((ULONG)(per64[0])));
 		per64[0] = per64[0] + (perrx);
		per64[1] = per64[1] + (perrx>>31) + carry;
 		perrchk = (per64[1]<<2) + (((ULONG)per64[0])>>30);
		if( perrchk >  0 ){ return(  0x3FFFFFFF );}
		if( perrchk < -1 ){ return( -0x40000000 );}
 		return( per64[0] );
 }
 
 
 void	MlibAposRg64iv( LONG inipos0, LONG inipos1, EGEAR *egear, APOSRG *aposrg )
{
LONG	i;
LONG	sign;
LONG	carry;
LONG	xx[4];
LONG	y0,y1;
LONG	b = egear->b;
 		if( inipos1 >= 0 )
		{
			sign = 0;
		}
		else
		{
			sign = 1;
			inipos0 = (~inipos0) + 1;
			inipos1 = (~inipos1) + (inipos0 == 0);
		}
		MULU32U32( (ULONG)inipos0, (ULONG)egear->a, (ULONG*)&xx[0] );
		MULU32U32( (ULONG)inipos1, (ULONG)egear->a, (ULONG*)&xx[2] );
		carry = ( (ULONG)xx[2] > ((ULONG)xx[2]+(ULONG)xx[1]) );
		xx[2] = xx[2] + xx[1];
		xx[3] = xx[3] + carry;
		for( y1=0,i=0; i<32; i++ )
		{
			y1 = (y1<<1);
			xx[3] = (xx[3]<<1) + ((ULONG)xx[2]>>31);
			xx[2] = (xx[2]<<1);
			if( (ULONG)xx[3] >= (ULONG)b )
			{
				y1 = y1 + 1;
				xx[3] = (ULONG)xx[3] - (ULONG)b;
			}
		}
		for( y0=0,i=0; i<32; i++ )
		{
			y0 = (y0<<1);
			xx[3] = (xx[3]<<1) + ((ULONG)xx[0]>>31);
			xx[0] = (xx[0]<<1);
			if( (ULONG)xx[3] >= (ULONG)b )
			{
				y0 = y0 + 1;
				xx[3] = (ULONG)xx[3] - (ULONG)b;
			}
		}
		if( xx[3] >= ((b+1)>>1) )
		{
			xx[3] = xx[3] - b;
			y0    = y0 + 1;
			y1    = y1 + (y0==0);
		}
		if( sign != 0 )
		{
			y0 = (~y0) + 1;
			y1 = (~y1) + (y0 == 0);
			xx[3] = -xx[3];
		}
		aposrg->dposix  = 0;
		aposrg->aposrem = xx[3];
		aposrg->apos[0] = y0;
		aposrg->apos[1] = y1;
 		return;
 }
 
 
 void	MlibAposRg64dp( LONG dposin, EGEAR *egear, APOSRG *aposrg, LONG *latchpos )
{
LONG	carry;
LONG	wk1[2];
LONG	wk2[2];
LONG	dposix;
LONG	aposrem = aposrg->aposrem;
 		MUL3232( egear->g1, dposin, &wk1[0] );
		MUL3232( egear->g2, dposin, &wk2[0] );
		dposix = wk1[0] + (wk2[1]<<1) + ((ULONG)wk2[0]>>31);
		MUL3232( egear->a, dposin, &wk1[0] );
		MUL3232( egear->b, dposix, &wk2[0] );
		aposrem = aposrem + ((ULONG)wk1[0] - (ULONG)wk2[0]);
		if( aposrem <  0                 ){ --dposix; aposrem += egear->b;}
		if( aposrem >= egear->b          ){ ++dposix; aposrem -= egear->b;}
		if( aposrem >= ((egear->b+1)>>1) ){ ++dposix; aposrem -= egear->b;}
		if( latchpos == NULL )
		{
			aposrg->dposix  = dposix;
			aposrg->aposrem = aposrem;
			aposrg->apos[0] = aposrg->apos[0] + dposix;
			carry = ((ULONG)aposrg->apos[0] < (ULONG)dposix)? 1 : 0;
			aposrg->apos[1] = aposrg->apos[1] + (dposix>>31) + carry;
		}
		else
		{
			latchpos[0] = aposrg->apos[0] + dposix;
			carry = ((ULONG)latchpos[0] < (ULONG)aposrg->apos[0])? 1 : 0;
			latchpos[1] = aposrg->apos[1] + (dposix>>31) + carry;
		}
		return;
 }
 
  
  
  
  
  
  
  
LONG	MlibIpcalPcmdMaker(
		KSGAIN	ksosvp,					 
		LONG	maxspdm,				 
		LONG	maxspdi,				 
		LONG	pcmd64f,				 
		PCMKP	*pcmkprm	)			 
{
LONG	kx,sx;
ULONG	xx[2];
ULONG	yy[2];
  
  
		sx = (ksosvp >> 24) + 1;
		kx = ((ksosvp << 8 ) >> 7);
		if( sx > 16 )
		{
			kx = (kx >> (sx - 16));
			sx = 16;
		}
  
  
		MULU32U32( (kx << 8), maxspdm, xx );
  
  
		MULU32U32( (kx << 8), maxspdi, yy );
  
  
		pcmkprm->osvpm   = kx;
		pcmkprm->maxvpm  = xx[1];
		pcmkprm->maxipv  = yy[1];
		pcmkprm->pshlx   = (UCHAR)( sx & 0x00FF);
		pcmkprm->pcmd64f = (UCHAR)(pcmd64f & 0x00FF);
 		return( TRUE );
 }
 
  
  
 LONG	MlibPcalaPcmdMaker(
		LONG	maxspd,					 
		LONG	acctime,				 
		LONG	dectime,				 
		LONG	scantime,				 
		PCMKP	*pcmkprm	)			 
{
LONG	maxvp;
ULONG	xx[2];
PCMKP	wkprm;
  
  
		MULU32U32( (pcmkprm->osvpm << 8), maxspd, xx );
		maxvp = (xx[1] > 0)? xx[1] : 0;
  
 		wkprm.vpacc = MlibScalKxgain( maxvp, scantime, acctime, NULL, -24 );
		if( wkprm.vpacc <= 0 )
        {
            wkprm.vpacc = 1;
        }
  
 		wkprm.vpdec = MlibScalKxgain( maxvp, scantime, dectime, NULL, -24 );
		if( wkprm.vpdec <= 0 )
        {
            wkprm.vpdec = 1;
        }
  
  
  
 		wkprm.vpamx = wkprm.vpacc / wkprm.vpdec;
		wkprm.vparx = wkprm.vpacc - ( wkprm.vpamx * wkprm.vpdec );
		if( wkprm.vpamx & 0x0001 )
		{
			wkprm.vpapx = (( wkprm.vpamx + 1 ) >> 1) * ( wkprm.vpacc + wkprm.vparx );
		}
		else
		{
			wkprm.vpapx =  ( wkprm.vpamx + 1 ) * (( wkprm.vpacc+wkprm.vparx ) >> 1);
		}
  
 		KPI_DI( );
		pcmkprm->vpacc  = wkprm.vpacc;
		pcmkprm->vpdec  = wkprm.vpdec;
		pcmkprm->vpamx  = wkprm.vpamx;
		pcmkprm->vparx  = wkprm.vparx;
		pcmkprm->vpapx  = wkprm.vpapx;
		pcmkprm->maxspd = maxspd;
		KPI_EI( );
 		return( TRUE );
 }
 
 LONG	MlibPcalaPcmdMkrIP(
		LONG	iptimes,
		LONG	maxspd,
		LONG	ipacctm,
		LONG	ipdectm,
		LONG	scantime,
		PCMKP	*pcmkprm	)
{
LONG	xx[2];
LONG	kx,sx,sy;
LONG	ipmaxacc;
LONG	ipstpdec;
LONG	IPcycle = scantime * iptimes;
 		sx = pcmkprm->pshlx + 24;
		kx = MlibPcalKxmulx( maxspd, pcmkprm->osvpm, IPcycle, &sx );
		MUL3232( pcmkprm->maxipv, iptimes, &xx[0] );
		xx[0] = ((xx[1]<<(31-pcmkprm->pshlx))<<1) + ((ULONG)xx[0]>>pcmkprm->pshlx);
		if( ipacctm <= 0 )
		{
			ipmaxacc = xx[0];
		}
		else
		{
			sy = sx;
			ipmaxacc = MlibPcalKxgain( kx, iptimes, ipacctm, &sy, -24 );
			if( ipmaxacc <= 0 ){ ipmaxacc = 1;}
		}
		if( ipdectm <= 0 )
		{
			ipstpdec = xx[0];
		}
		else
		{
			sy = sx;
			ipstpdec = MlibPcalKxgain( kx, iptimes, ipdectm, &sy, -24 );
			if( ipstpdec <= 0 ){ ipstpdec = 1;}
		}
		KPI_DI( );
		pcmkprm->iptimes  = (USHORT)iptimes;
		pcmkprm->ipmaxspd = xx[0];
		pcmkprm->ipmaxacc = ipmaxacc;
		pcmkprm->ipstpdec = ipstpdec;
		KPI_EI( );
		return( TRUE );
 }
 
 LONG	MlibPcalbPcmdMaker(
		LONG	accrate,
		LONG	decrate,
		LONG	scantime,
		PCMKP	*pcmkprm,
		LONG	insel		)
{
LONG	kx,sx;
PCMKP	wkprm;
LONG	kunit = ((insel & 0xF0)==0)? 1 : 1000;
 		sx = pcmkprm->pshlx; kx = MlibPcalKxmulx( kunit, kunit, 100000000, &sx );
		sx = -sx;			 kx = MlibPcalKxgain( scantime, scantime, kx, &sx, -1 );
		wkprm.vpacc = MlibScalKskxkx( kx, accrate, 1, NULL, -24 );
		if( wkprm.vpacc <= 0 ){ wkprm.vpacc = 1;}
		wkprm.vpdec = MlibScalKskxkx( kx, decrate, 1, NULL, -24 );
		if( wkprm.vpdec <= 0 ){ wkprm.vpdec = 1;}
		wkprm.vpamx = wkprm.vpacc / wkprm.vpdec;
		wkprm.vparx = wkprm.vpacc - (wkprm.vpamx*wkprm.vpdec);
		if( wkprm.vpamx & 0x0001 )
		{
			wkprm.vpapx = ((wkprm.vpamx+1)>>1)*(wkprm.vpacc+wkprm.vparx);
		}
		else
		{
			wkprm.vpapx = (wkprm.vpamx+1)*((wkprm.vpacc+wkprm.vparx)>>1);
		}
		KPI_DI( );
		pcmkprm->vpacc = wkprm.vpacc;
		pcmkprm->vpdec = wkprm.vpdec;
		pcmkprm->vpamx = wkprm.vpamx;
		pcmkprm->vparx = wkprm.vparx;
		pcmkprm->vpapx = wkprm.vpapx;
		KPI_EI( );
		return( TRUE );
 }
 
 LONG	MlibPcalbPcmdMkrIP(
		LONG	iptimes,
		LONG	ipaccrt,
		LONG	ipdecrt,
		LONG	scantime,
		PCMKP	*pcmkprm,
		LONG	insel		)
{
LONG	xx[2];
LONG	kx,sx,sy;
LONG	ipmaxacc;
LONG	ipstpdec;
LONG	IPcycle = scantime * iptimes;
LONG	kunit = ((insel & 0xF0)==0)? 1 : 1000;
 		sx = 0;   kx = MlibPcalKxmulx( kunit, kunit, 100000000, &sx );
		sx = -sx; kx = MlibPcalKxgain( IPcycle, IPcycle, kx, &sx, 0 );
		MUL3232( pcmkprm->maxipv, iptimes, &xx[0] );
		xx[0] = ((xx[1]<<(31-pcmkprm->pshlx))<<1) + ((ULONG)xx[0]>>pcmkprm->pshlx);
		if( ipaccrt <= 0 )
		{
			ipmaxacc = xx[0];
		}
		else
		{
			sy = sx;
			ipmaxacc = MlibPcalKxgain( kx, ipaccrt, 1, &sy, -24 );
			if( ipmaxacc <= 0 ){ ipmaxacc = 1;}
		}
		if( ipdecrt <= 0 )
		{
			ipstpdec = xx[0];
		}
		else
		{
			sy = sx;
			ipstpdec = MlibPcalKxgain( kx, ipdecrt, 1, &sy, -24 );
			if( ipstpdec <= 0 ){ ipstpdec = 1;}
		}
		KPI_DI( );
		pcmkprm->iptimes  = (USHORT)iptimes;
		pcmkprm->ipmaxspd = xx[0];
		pcmkprm->ipmaxacc = ipmaxacc;
		pcmkprm->ipstpdec = ipstpdec;
		KPI_EI( );
		return( TRUE );
 }
 
 void	MlibRstPcmdMaker(
		LONG	pcmdset0,
		LONG	pcmdset1,
		PCMKPV	*pcmdmkr	)
{
 		KPI_DI( );
		pcmdmkr->V.vpx        = 0;
		pcmdmkr->V.vpxrem     = 0;
		pcmdmkr->V.ipvpi      = 0;
		pcmdmkr->V.ipvpx      = 0;
		pcmdmkr->V.ipremi     = 0;
		pcmdmkr->V.ipremx     = 0;
		pcmdmkr->V.calendf    = 0;
		pcmdmkr->V.cmderrf    = 0;
		pcmdmkr->V.pcmkmode   = 0;
		pcmdmkr->V.modechgf   = 0;
		pcmdmkr->V.pcmdout[0] = pcmdset0;
		pcmdmkr->V.pcmdout[1] = pcmdset1;
		KPI_EI( );
		return;
 }
 
 #define	LPX_EQ64( a, b )	( (a[1] == b[1]) && (a[0] == b[0]) )
#define	LPX_GT64( a, b )	( (a[1] >  b[1]) || ((a[1] == b[1])&&((ULONG)a[0] >  (ULONG)b[0])) )
#define	LPX_LT64( a, b )	( (a[1] <  b[1]) || ((a[1] == b[1])&&((ULONG)a[0] <  (ULONG)b[0])) )
LONG	MlibIpTposLimit(
		LONG	*tpos,
		LONG	*lmtpos,
		LONG	lmtdir,
		PCMKPV	*pcmdmkr	)
{
LONG	carry;
LONG	x1,x2;
LONG	px64[2];
PCMKP	*pcmkprm = &pcmdmkr->P;
PCMKV	*pcmkvar = &pcmdmkr->V;
 		if( pcmkvar->pcmkmode != PCMKMODE_IPA )
		{
			MUL3232( pcmkvar->vpx, (pcmkprm->iptimes<<1), &px64[0] );
			x1 = ((px64[1]<<(31-pcmkprm->pshlx))<<1) + ((ULONG)px64[0]>>pcmkprm->pshlx);
			pcmkvar->ipvpi = (x1 + 1) >> 1;
		}
		pcmkvar->avp = (pcmkvar->ipvpi >= 0) ? pcmkvar->ipvpi : -pcmkvar->ipvpi;
		pcmkvar->n   = pcmkvar->avp / pcmkprm->ipstpdec;
		pcmkvar->rem = pcmkvar->avp - pcmkvar->n * pcmkprm->ipstpdec;
		if( ((pcmkvar->n+1)&0x01) == 0x00 )
		{
			MUL3232( ((pcmkvar->n + 1)>>1), (pcmkvar->avp + pcmkvar->rem), &px64[0] );
		}
		else
		{
			MUL3232( (pcmkvar->n + 1), ((pcmkvar->avp + pcmkvar->rem)>>1), &px64[0] );
		}
		if( pcmkvar->ipvpi >= 0 )
		{
			pcmkvar->ipstopx[0] = pcmkvar->pcmdout[0] + px64[0];
			carry = ((ULONG)pcmkvar->ipstopx[0] < (ULONG)px64[0]);
			pcmkvar->ipstopx[1] = pcmkvar->pcmdout[1] + px64[1] + carry;
		}
		else
		{
			pcmkvar->ipstopx[0] = pcmkvar->pcmdout[0] - px64[0];
			carry = ((ULONG)pcmkvar->pcmdout[0] < (ULONG)px64[0]);
			pcmkvar->ipstopx[1] = pcmkvar->pcmdout[1] - px64[1] - carry;
		}
		px64[0] = lmtpos[0] - pcmkvar->ipstopx[0];
		carry = ((ULONG)lmtpos[0] < (ULONG)pcmkvar->ipstopx[0]);
		px64[1] = lmtpos[1] - pcmkvar->ipstopx[1] - carry;
 		if( LPX_EQ64( tpos, pcmkvar->pcmdout ) )
		{
			return( FALSE );
		}
		else if( lmtdir == IPTPOSLMT_PSIDE )
		{
			if( pcmkvar->ipvpi < 0 )
			{
				if( LPX_GT64( tpos, lmtpos ) )
				{
					tpos[0] = lmtpos[0];
					tpos[1] = lmtpos[1];
					return( TRUE );
				}
				return( FALSE );
			}
			if( (px64[1] > 0) || ((px64[1]==0)&&(px64[0]<0)) )
			{
				return( FALSE );
			}
		}
		else
		{
			if( pcmkvar->ipvpi > 0 )
			{
				if( LPX_LT64( tpos, lmtpos ) )
				{
					tpos[0] = lmtpos[0];
					tpos[1] = lmtpos[1];
					return( TRUE );
				}
				return( FALSE );
			}
			px64[0] = ~px64[0] + 1;
			px64[1] = ~px64[1] + (px64[0]==0);
			if( (px64[1] > 0) || ((px64[1]==0)&&(px64[0]<0)) )
			{
				return( FALSE );
			}
		}
 		if( px64[0] > pcmkvar->n )
		{
			if( px64[0] <= (pcmkvar->avp + pcmkprm->ipstpdec) )
			{
				x1 = pcmkprm->ipstpdec - pcmkvar->rem;
				x2 = x1 * (pcmkvar->n + 1);
				if( px64[0] <= x2 )
				{
					pcmkvar->avp += (px64[0]/(pcmkvar->n + 1));
				}
				else
				{
					pcmkvar->avp += x1 + ((px64[0] - x2)/(pcmkvar->n + 2));
				}
			}
			else
			{
				x1 = pcmkvar->avp;
				x2 = (4*x1) + (10UL*pcmkprm->ipstpdec);
				if( px64[0] >= x2 )
				{
					px64[0] -= x2; x1 += 4*pcmkprm->ipstpdec;
				}
				x2 = x1 + pcmkprm->ipstpdec;
				if( px64[0] >= x2 )
				{
					px64[0] -= x2; x1 = x2;
				}
				x2 = x1 + pcmkprm->ipstpdec;
				if( px64[0] >= x2 )
				{
					px64[0] -= x2; x1 = x2;
				}
				x2 = x1 + pcmkprm->ipstpdec;
				if( px64[0] >= x2 )
				{
					px64[0] -= x2; x1 = x2;
				}
				x2 = x1 + pcmkprm->ipstpdec;
				if( px64[0] >  x2 )
				{
					pcmkvar->avp = x1;
					return( FALSE );
				}
				else
				{
					pcmkvar->avp = x1;
				}
			}
		}
		else if( px64[0] < 0 )
		{
			if( px64[0] <= -pcmkvar->avp )
			{
				pcmkvar->avp -= pcmkprm->ipstpdec;
				if( pcmkvar->avp < 0 ){ pcmkvar->avp = 0;}
			}
			else if( px64[0] <= -((pcmkvar->n + 1)*pcmkvar->rem) )
			{
				pcmkvar->avp -= pcmkprm->ipstpdec - ((px64[0] + pcmkvar->avp)/pcmkvar->n);
			}
			else
			{
				pcmkvar->avp -= ((pcmkvar->n - px64[0])/(pcmkvar->n+1));
			}
		}
 		x1 = (lmtdir == IPTPOSLMT_PSIDE)? pcmkvar->avp : -pcmkvar->avp;
		px64[0] = pcmkvar->pcmdout[0] + x1;
		carry = ((ULONG)px64[0] < (ULONG)x1);
		px64[1] = pcmkvar->pcmdout[1] + (x1>>31) + carry;
 		if( lmtdir == IPTPOSLMT_PSIDE )
		{
			if( LPX_GT64( px64, lmtpos ) )
			{
				px64[0] = lmtpos[0];
				px64[1] = lmtpos[1];
			}
			if( LPX_GT64( tpos, px64 ) )
			{
				tpos[0] = px64[0];
				tpos[1] = px64[1];
				return( TRUE );
			}
		}
		else
		{
			if( LPX_LT64( px64, lmtpos ) )
			{
				px64[0] = lmtpos[0];
				px64[1] = lmtpos[1];
			}
			if( LPX_LT64( tpos, px64 ) )
			{
				tpos[0] = px64[0];
				tpos[1] = px64[1];
				return( TRUE );
			}
		}
		return( FALSE );
}
 
  
  
  
LONG	MlibPcmdMaker(
		LONG	pcmdin0,				 
		LONG	pcmdin1,				 
		LONG	pcmdspd,				 
		PCMKPV	*pcmdmkr,				 
		ULONG	pcmkmode	)			 
{
LONG	carry;							 
LONG	px64[2];						 
LONG	per64[2];						 
LONG	pex64[2];						 
LONG	pex,x1,x2;						 
PCMKP	*pcmkprm = &pcmdmkr->P;			 
PCMKV	*pcmkvar = &pcmdmkr->V;			 
  
  
		pcmkvar->modechgf = ((pcmkmode & 0xFF) != pcmkvar->pcmkmode)? TRUE : FALSE;
		pcmkvar->pcmkmode = (UCHAR)pcmkmode;
  
 		switch( pcmkmode )
		{
            case PCMKMODE_IPA  : goto PCMDMAKER_INTERPOLATE;
            case PCMKMODE_IPB  : goto PCMDMAKER_INTERPOLATE;
              
            case PCMKMODE_POS  : goto PCMDMAKER_POSITIONING;
             
            case PCMKMODE_FEED : goto PCMDMAKER_CONSPD_FEED;
            default            : goto PCMDMAKER_DECSPD_STOP;
		}
  
  
  
PCMDMAKER_POSITIONING:
  
 		if( pcmkvar->modechgf )
		{
			pcmkvar->vpxrem = 0;
			pcmkvar->cmderrf = FALSE;
		}
  
 		pcmkvar->maxvp = XasmMulhigh32down( (pcmkprm->osvpm << 4), (LPX_ABS(pcmdspd) << 4) );
  
 		if( pcmkprm->pcmd64f )
		{
			per64[0] = pcmdin0 - pcmkvar->pcmdout[0];
			carry = ((ULONG)pcmdin0 < (ULONG)pcmkvar->pcmdout[0]);
			per64[1] = pcmdin1 - pcmkvar->pcmdout[1] - carry;
			if( (per64[1]>>(30-pcmkprm->pshlx)) > 0 )
			{
				per64[1] =  0x3FFFFFFF;
			}
			else if( (per64[1]>>(30-pcmkprm->pshlx)) < -1 )
			{
				per64[1] = -0x3FFFFFFF;
			}
			else
			{
				x1       = (((ULONG)per64[0]>>(31-pcmkprm->pshlx))>>1);
				carry    = ((ULONG)(per64[0]<<pcmkprm->pshlx) < (ULONG)pcmkvar->vpxrem);
				per64[0] = (per64[0]<<pcmkprm->pshlx) - pcmkvar->vpxrem;
				per64[1] = (per64[1]<<pcmkprm->pshlx) + x1 - (pcmkvar->vpxrem>>31) - carry;
			}
		}
		else
		{   
              
              
			x1       = pcmdin0 - pcmkvar->pcmdout[0];
			carry    = ((ULONG)(x1<<pcmkprm->pshlx) < (ULONG)pcmkvar->vpxrem);
			per64[0] = (x1<<pcmkprm->pshlx) - pcmkvar->vpxrem;
			per64[1] = ((x1>>(31-pcmkprm->pshlx))>>1) - (pcmkvar->vpxrem>>31) - carry;
		}
 		if( per64[1] >  0 ) goto PCMDMAKER_POS_VPCHK;            
		if( per64[1] < -1 ) goto PCMDMAKER_POS_VPCHK;            
		if( (per64[1]^per64[0]) < 0 ) goto PCMDMAKER_POS_VPCHK;
          
 		if( (-pcmkprm->vpdec <= per64[0]) && (per64[0] <= pcmkprm->vpdec) )
		{
			x1 = per64[0] - pcmkvar->vpx;
			if( (x1 >= -pcmkprm->vpdec) && (x1 <= pcmkprm->vpdec) )
			{
				pcmkvar->vpx = per64[0];
				pcmkvar->calendf = (per64[0]==0)? TRUE : FALSE;      
				goto PCMDMAKER_POS_END00;
			}
		}
 PCMDMAKER_POS_VPCHK:
 		pcmkvar->calendf = FALSE;                                    
          
          
		pcmkvar->avp = ( pcmkvar->vpx > 0 ) ? pcmkvar->vpx : -pcmkvar->vpx;
          
          
		if( pcmkvar->avp >= (pcmkvar->maxvp + pcmkprm->vpdec) )
		{
			if( pcmkvar->vpx > 0 )
			{
				pcmkvar->vpx = pcmkvar->vpx - pcmkprm->vpdec;
			}
			else
			{
				pcmkvar->vpx = pcmkvar->vpx + pcmkprm->vpdec;
			}
			goto PCMDMAKER_POS_END00;
		}
          
          
		pcmkvar->n   = pcmkvar->avp / pcmkprm->vpdec;
		pcmkvar->rem = pcmkvar->avp - pcmkvar->n * pcmkprm->vpdec;
		if( (( pcmkvar->n+1 ) & 0x01) == 0x00 )
		{
			MUL3232( ((pcmkvar->n + 1)>>1), (pcmkvar->avp + pcmkvar->rem), &px64[0] );  
		}
		else
		{
			MUL3232( (pcmkvar->n + 1), ((pcmkvar->avp + pcmkvar->rem)>>1), &px64[0] );  
		}
 		if( (pcmkvar->vpx >= 0) && (per64[1] >= 0) && ((per64[1]|per64[0]) != 0) )      
		{
			pex64[0] = per64[0] - px64[0];
			pex64[1] = per64[1] - px64[1] - ((ULONG)per64[0] < (ULONG)px64[0]);
			x1 = pex64[0]^pex64[1];
 			if( ( x1 >= 0 )&&(( pex64[1]==0 )||( pex64[1]==-1 )) )
			{
				pex = pex64[0];
			}
 			else if( pex64[1] >= 0 )
			{
                  
 				pcmkvar->vpx = pcmkvar->vpx + pcmkprm->vpacc;
				if( pcmkvar->vpx > pcmkvar->maxvp )                  
                {
                    pcmkvar->vpx = pcmkvar->maxvp;
                }
				goto PCMDMAKER_POS_END00;
			}
 			else
			{
				pcmkvar->vpx = pcmkvar->vpx - pcmkprm->vpdec;
				if( pcmkvar->vpx < -pcmkvar->maxvp ){ pcmkvar->vpx = -pcmkvar->maxvp;}
				goto PCMDMAKER_POS_END00;
			}
		}
 		else if( (pcmkvar->vpx <= 0) && (per64[1] < 0) )                                 
		{
			pex64[0] = per64[0] + px64[0];
			pex64[1] = per64[1] + px64[1] + ((ULONG)pex64[0] < (ULONG)per64[0]);
			x1 = pex64[0]^pex64[1];
			if( ( x1 >= 0 )&&(( pex64[1]==0 )||( pex64[1]==-1 )) )
			{
				pex = (pex64[0]==0x80000000) ? 0x7FFFFFFF : -pex64[0];
			}
			else if( pex64[1] >= 0 )
			{
				pcmkvar->vpx = pcmkvar->vpx + pcmkprm->vpdec;
				if( pcmkvar->vpx > pcmkvar->maxvp )
                {
                    pcmkvar->vpx = pcmkvar->maxvp;
                }
				goto PCMDMAKER_POS_END00;
			}
			else
			{
				pcmkvar->vpx = pcmkvar->vpx - pcmkprm->vpacc;
				if( pcmkvar->vpx < -pcmkvar->maxvp )
                {
                    pcmkvar->vpx = -pcmkvar->maxvp;
                }
				goto PCMDMAKER_POS_END00;
			}
		}
		else if( (pcmkvar->vpx < 0) && (per64[1] >= 0) )
		{
			pcmkvar->vpx = pcmkvar->vpx + pcmkprm->vpdec;
			if( pcmkvar->vpx > pcmkvar->maxvp )
            {
                pcmkvar->vpx = pcmkvar->maxvp;
            }
			goto PCMDMAKER_POS_END00;
		}
		else
		{
			pcmkvar->vpx = pcmkvar->vpx - pcmkprm->vpdec;
			if( pcmkvar->vpx < -pcmkvar->maxvp )
            {
                pcmkvar->vpx = -pcmkvar->maxvp;
            }
			goto PCMDMAKER_POS_END00;
		}
 		if( pex > pcmkvar->n )
		{
			x1 = pcmkprm->vparx + pcmkvar->rem - pcmkprm->vpdec;
			x2 = pcmkprm->vpapx + pcmkprm->vpamx*pcmkvar->avp + pcmkvar->n*pcmkprm->vparx + ((x1>0)?x1:0);
			if( pex >= x2 )
			{
				pcmkvar->avp = pcmkvar->avp + pcmkprm->vpacc;
			}
			else if( pex >= (pcmkvar->avp + pcmkprm->vpdec) )
			{
				if( pex >= (8L *pcmkvar->avp + 36L*pcmkprm->vpdec) )
				{
					pex = pex - (8L*pcmkvar->avp + 36L*pcmkprm->vpdec);
					pcmkvar->avp = pcmkvar->avp + 8L*pcmkprm->vpdec;
				}
				if( pex >= (4L*pcmkvar->avp + 10L*pcmkprm->vpdec) )
				{
					pex = pex - (4L*pcmkvar->avp + 10L*pcmkprm->vpdec);
					pcmkvar->avp = pcmkvar->avp + 4L*pcmkprm->vpdec;
				}
				if( pex >= (2L*pcmkvar->avp + 3L*pcmkprm->vpdec) )
				{
					pex = pex - (2L*pcmkvar->avp + 3L*pcmkprm->vpdec);
					pcmkvar->avp = pcmkvar->avp + 2L*pcmkprm->vpdec;
				}
				if( pex >= (pcmkvar->avp + pcmkprm->vpdec) )
				{
					pcmkvar->avp = pcmkvar->avp + pcmkprm->vpdec;
				}
			}
			else if( pex > ((pcmkvar->n + 1)*(pcmkprm->vpdec - pcmkvar->rem)) )
			{
				pcmkvar->avp = pcmkvar->avp + pcmkprm->vpdec;
				pcmkvar->avp = pcmkvar->avp - (pcmkvar->avp - pex + pcmkvar->n + 1)/(pcmkvar->n + 2);
			}
			else
			{
				pcmkvar->avp = pcmkvar->avp + pex/(pcmkvar->n + 1);
			}
		}
		else if( pex < 0 )
		{
			if( pex <= -pcmkvar->avp )
			{
				pcmkvar->avp = pcmkvar->avp - pcmkprm->vpdec;
			}
			else if( pex <= -(pcmkvar->n + 1)*pcmkvar->rem )
			{
				pcmkvar->avp = pcmkvar->avp - pcmkprm->vpdec + (pex + pcmkvar->avp)/pcmkvar->n;
			}
			else
			{
				pcmkvar->avp = pcmkvar->avp - (pcmkvar->n - pex)/(pcmkvar->n + 1);
			}
		}
 		x1 = ( pcmkvar->avp > pcmkvar->maxvp )? pcmkvar->maxvp : pcmkvar->avp;
		pcmkvar->vpx = ( per64[1] >= 0 )? x1 : -x1;
 PCMDMAKER_POS_END00:
		if( 1 )
		{
			x1 = pcmkvar->vpx + pcmkvar->vpxrem;
			x2 = (x1>=0)? (x1>>pcmkprm->pshlx) : -((-x1)>>pcmkprm->pshlx);
			pcmkvar->vpxrem = x1 - (x2<<pcmkprm->pshlx);
		}
		else
		{
			x2 = pcmkvar->vpx >> pcmkprm->pshlx;
			pcmkvar->vpxrem += pcmkvar->vpx - (x2<<pcmkprm->pshlx);
			if( pcmkvar->vpx >= 0 )
			{
				if( pcmkvar->vpxrem > 0 )
				{
					x2 += 1;
					pcmkvar->vpxrem -= (1<<pcmkprm->pshlx);
				}
			}
			else
			{
				if( pcmkvar->vpxrem >= (1<<pcmkprm->pshlx) )
				{
					x2 += 1;
					pcmkvar->vpxrem -= (1<<pcmkprm->pshlx);
				}
			}
		}
          
 		pcmkvar->pcmdout[0] = pcmkvar->pcmdout[0] + x2;
		carry = ((ULONG)pcmkvar->pcmdout[0] < (ULONG)x2);
		pcmkvar->pcmdout[1] = pcmkvar->pcmdout[1] + (x2>>31) + carry;
 		return( x2 );
 
 PCMDMAKER_INTERPOLATE:
		if( pcmkvar->modechgf )
		{
			MUL3232( pcmkvar->vpx, (pcmkprm->iptimes<<1), &px64[0] );
			x1 = ((px64[1]<<(31-pcmkprm->pshlx))<<1) + ((ULONG)px64[0]>>pcmkprm->pshlx);
			pcmkvar->ipvpi = (x1 + 1) >> 1;
		}
		if( pcmkmode == PCMKMODE_IPA )
		{
			per64[0] = pcmdin0 - pcmkvar->pcmdout[0];
			if( per64[0] > pcmkprm->ipmaxspd )
			{
				pcmkvar->cmderrf = TRUE;
				per64[0] = pcmkprm->ipmaxspd;
			}
			else if( per64[0] < -pcmkprm->ipmaxspd )
			{
				pcmkvar->cmderrf = TRUE;
				per64[0] = -pcmkprm->ipmaxspd;
			}
			else
			{
				pcmkvar->cmderrf = FALSE;
			}
			if( 0 )
			{
				x1 = per64[0] - pcmkvar->ipvpi;
				if( x1 > pcmkprm->ipmaxacc )
				{
					pcmkvar->cmderrf = TRUE;
					per64[0] = pcmkvar->ipvpi + pcmkprm->ipmaxacc;
				}
				else if( x1 < -pcmkprm->ipmaxacc )
				{
					pcmkvar->cmderrf = TRUE;
					per64[0] = pcmkvar->ipvpi - pcmkprm->ipmaxacc;
				}
			}
			if( per64[0] == 0 )
			{
				pcmkvar->ipvpi   = 0;
				pcmkvar->ipvpx   = 0;
				pcmkvar->ipremi  = 0;
				pcmkvar->ipremx  = 0;
				pcmkvar->vpx     = 0;
				pcmkvar->vpxrem  = 0;
				pcmkvar->calendf = (pcmkvar->cmderrf == FALSE)? TRUE : FALSE;
				return( 0 );
			}
			else
			{
				pcmkvar->ipvpi   = per64[0];
				pcmkvar->ipvpx   = per64[0] / (LONG)pcmkprm->iptimes;
				pcmkvar->ipremi  = per64[0] - (pcmkvar->ipvpx * pcmkprm->iptimes);
				pcmkvar->ipremx  = 0;
				pcmkvar->calendf = FALSE;
			}
		}
		x2 = pcmkvar->ipvpx;
		if( pcmkvar->ipremi > 0 )
		{
			pcmkvar->ipremx += pcmkvar->ipremi;
			if( pcmkvar->ipremx > 0 )
			{
				x2 = x2 + 1;
				pcmkvar->ipremx -= (LONG)pcmkprm->iptimes;
			}
		}
		else if( pcmkvar->ipremi < 0 )
		{
			pcmkvar->ipremx += pcmkvar->ipremi;
			if( pcmkvar->ipremx < 0 )
			{
				x2 = x2 - 1;
				pcmkvar->ipremx += (LONG)pcmkprm->iptimes;
			}
		}
		pcmkvar->vpx = (x2<<pcmkprm->pshlx);
		pcmkvar->vpxrem = 0;
		pcmkvar->pcmdout[0] = pcmkvar->pcmdout[0] + x2;
		carry = ((ULONG)pcmkvar->pcmdout[0] < (ULONG)x2);
		pcmkvar->pcmdout[1] = pcmkvar->pcmdout[1] + (x2>>31) + carry;
		return( x2 );
 
 PCMDMAKER_CONSPD_FEED:
		pcmkvar->cmderrf = FALSE;
		pcmdspd = XasmMulhigh32down( (pcmkprm->osvpm << 4), (pcmdspd << 4) );
		if( pcmkvar->vpx >= 0 )
		{
			x1 = ( pcmdspd >= pcmkvar->vpx )? pcmkprm->vpacc : pcmkprm->vpdec;
		}
		else
		{
			x1 = ( pcmdspd <= pcmkvar->vpx )? pcmkprm->vpacc : pcmkprm->vpdec;
		}
		if( pcmkvar->vpx >= pcmdspd )
		{
			pcmkvar->vpx = pcmkvar->vpx - x1;
			if( pcmkvar->vpx <= pcmdspd )
			{
				pcmkvar->vpx = pcmdspd;
				pcmkvar->calendf = TRUE;
			}
			else
			{
				pcmkvar->calendf = FALSE;
			}
		}
		else
		{
			pcmkvar->vpx = pcmkvar->vpx + x1;
			if( pcmkvar->vpx >= pcmdspd )
			{
				pcmkvar->vpx = pcmdspd;
				pcmkvar->calendf = TRUE;
			}
			else
			{
				pcmkvar->calendf = FALSE;
			}
		}
		x1 = pcmkvar->vpx + pcmkvar->vpxrem;
		x2 = (x1>=0)? (x1>>pcmkprm->pshlx) : -((-x1)>>pcmkprm->pshlx);
		pcmkvar->vpxrem = x1 - (x2<<pcmkprm->pshlx);
		pcmkvar->pcmdout[0] = pcmkvar->pcmdout[0] + x2;
		carry = ((ULONG)pcmkvar->pcmdout[0] < (ULONG)x2);
		pcmkvar->pcmdout[1] = pcmkvar->pcmdout[1] + (x2>>31) + carry;
		return( x2 );
 PCMDMAKER_DECSPD_STOP:
		pcmkvar->cmderrf = FALSE;
		if( pcmkvar->vpx >= 0 )
		{
			pcmkvar->vpx = pcmkvar->vpx - pcmkprm->vpdec;
			if( pcmkvar->vpx <= 0 )
			{
				pcmkvar->vpx = 0;
				pcmkvar->calendf = TRUE;
			}
			else
			{
				pcmkvar->calendf = FALSE;
			}
		}
		else
		{
			pcmkvar->vpx = pcmkvar->vpx + pcmkprm->vpdec;
			if( pcmkvar->vpx >= 0 )
			{
				pcmkvar->vpx = 0;
				pcmkvar->calendf = TRUE;
			}
			else
			{
				pcmkvar->calendf = FALSE;
			}
		}
		x1 = pcmkvar->vpx + pcmkvar->vpxrem;
		x2 = (x1>=0)? (x1>>pcmkprm->pshlx) : -((-x1)>>pcmkprm->pshlx);
		pcmkvar->vpxrem = x1 - (x2<<pcmkprm->pshlx);
		pcmkvar->pcmdout[0] = pcmkvar->pcmdout[0] + x2;
		carry = ((ULONG)pcmkvar->pcmdout[0] < (ULONG)x2);
		pcmkvar->pcmdout[1] = pcmkvar->pcmdout[1] + (x2>>31) + carry;
		return( x2 );
 }
 
 
 
 LONG	MlibAbs32( LONG u )
{
LONG	x;
 		x = (u >= 0)? u : -u;
 		return( x );
 }
 
 
void	MlibAdd6432( LONG *a, LONG b, LONG *x )
{
 		ADD6432( a, b, x );
 		return;
 }
 
 
 void	MlibAdd6464( LONG *a, LONG *b, LONG *x )
{
 		ADD6464( a, b, x );
 		return;
 }
 
 
 void	MlibSub6432( LONG *a, LONG b, LONG *x )
{
 		SUB6432( a, b, x );
 		return;
 }
 
 
 void	MlibSub6464( LONG *a, LONG *b, LONG *x )
{
 		SUB6464( a, b, x );
 		return;
 }
 
LONG	MlibErr6464( LONG *a, LONG *b )
{
LONG	errchk;
LONG	err64[2];
 		MlibSub6464( a, b, err64 );
		if( err64[1] >  0 ){ return(  0x3FFFFFFF );}
		if( err64[1] < -1 ){ return( -0x40000000 );}
 		errchk = (err64[1]<<2) + (((ULONG)err64[0])>>30);
		if( errchk   >  0 ){ return(  0x3FFFFFFF );}
		if( errchk   < -1 ){ return( -0x40000000 );}
		return( err64[0] );
 }
 
 
 LONG	MlibSatAdd24( LONG a, LONG b )
{
LONG	x;
 		x = a + b;
 		if( (a>0)&&(b>0)&&(x<=0) ){ return( 0x01000000 );}
		if( (a<0)&&(b<0)&&(x>=0) ){ return( 0xFF000000 );}
 		if( x > (LONG)0x01000000 ){ return( 0x01000000 );}
		if( x < (LONG)0xFF000000 ){ return( 0xFF000000 );}
 		return( x );
 }
 
LONG	MlibSatAdd28( LONG a, LONG b )
{
LONG	x;
 		x = a + b;
 		if( (a>0)&&(b>0)&&(x<=0) ){ return( 0x10000000 );}
		if( (a<0)&&(b<0)&&(x>=0) ){ return( 0xF0000000 );}
 		if( x > (LONG)0x10000000 ){ return( 0x10000000 );}
		if( x < (LONG)0xF0000000 ){ return( 0xF0000000 );}
 		return( x );
 }
 
 
 LONG	MlibSatAdd32( LONG a, LONG b )
{
LONG	x;
 		x = a + b;
 		if( (a>0)&&(b>0)&&(x<=0) ){ return( 0x7FFFFFFF );}
		if( (a<0)&&(b<0)&&(x>=0) ){ return( 0x80000000 );}
 		return( x );
 }
 
 
 ULONG	MlibSatAddu32( ULONG a, ULONG b )
{
ULONG	x;
 		x = a + b;
 		if( x < a ){ return( 0xFFFFFFFF );}
 		return( x );
 }
 
 
 void	MlibMul3232( LONG a, LONG b, LONG *x )
{
 		MUL3232( a, b, x );
		return;
 }
 
 
 void	MlibMulu32u32( ULONG a, ULONG b, ULONG *x )
{
 		MULU32U32( a, b, x );
		return;
 }
 
 
 LONG	MlibMulhigh32( LONG a, LONG b )
{
LONG	xx[2];
 		MUL3232( a, b, xx );
		xx[1] = xx[1] + ((ULONG)xx[0]>>31);
 		return( xx[1] );
 }
 
 
 ULONG	MlibMulhighu32( ULONG a, ULONG b )
{
ULONG	xx[2];
 		MULU32U32( a, b, xx );
		xx[1] = xx[1] + ((ULONG)xx[0]>>31);
 		return( xx[1] );
 }
 USHORT	MlibSqrtu32( ULONG a )
{
ULONG	i;
ULONG	x,y;
 		for( x=y=i=0; i<16; i++ )
		{
			x = ((x<<2)|(a>>30));
			a = (a<<2);
			y = (y<<1);
			if( x > y )
			{
				x = x - y - 1;
				y = y + 2;
			}
		}
		if( (x<<1) > y )
		{
			y = y + 2;
		}
		y = y>>1;
		y = (y > 0xFFFF)? 0xFFFF : y;
 		return( (USHORT)y );
 }
 
LONG	MlibSrhbiton( ULONG data, ULONG dir )
{
LONG	BitNo = 0;
 		if( data == 0 )
		{
			return( -1 );
		}
		else if( dir == SRH_FROM_LSB )
		{
			if( (data & 0xFFFF) == 0 ){ BitNo += 16; data = data>>16;}
			if( (data & 0x00FF) == 0 ){ BitNo +=  8; data = data>>8 ;}
			if( (data & 0x000F) == 0 ){ BitNo +=  4; data = data>>4 ;}
			if( (data & 0x0003) == 0 ){ BitNo +=  2; data = data>>2 ;}
			if( (data & 0x0001) == 0 ){ BitNo +=  1;}
		}
		else
		{
			if( (data & 0xFFFF0000) != 0 ){ BitNo += 16; data = data>>16;}
			if( (data & 0x0000FF00) != 0 ){ BitNo +=  8; data = data>>8 ;}
			if( (data & 0x000000F0) != 0 ){ BitNo +=  4; data = data>>4 ;}
			if( (data & 0x0000000C) != 0 ){ BitNo +=  2; data = data>>2 ;}
			if( (data & 0x00000002) != 0 ){ BitNo +=  1;}
		}
		return( BitNo );
 }
 
 
 void	MlibSetCRC16( USHORT *Dbuf, LONG Length )
{
LONG	i;
ULONG	a = 0xFFFF;
ULONG	b = 0xA001;
 		for( i = 0; i < (Length - 2); i++ )
		{
			a = a ^ (ULONG)Dbuf[i];
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
		}
		Dbuf[Length-2] = a & 0x00FF;
		Dbuf[Length-1] = (a >> 8) & 0x00FF;
		return;
}
 
LONG	MlibChkCRC16( USHORT *Dbuf, LONG Length )
{
LONG	i;
ULONG	a = 0xFFFF;
ULONG	b = 0xA001;
 		for( i=0; i < Length - 2; i++ )
		{
			a = a ^ (ULONG)Dbuf[i];
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
			a = (a & 0x01)? ((a>>1)^b) : (a>>1);
		}
		if ( (Dbuf[Length - 2] ==  (a & 0x00FF)) && (Dbuf[Length - 1] == ((a>>8) & 0x00FF)) )
		{
			return ( OK );
		}
		else
		{
			return ( NG );
		}
}
