

#ifndef __BASE_DEF_H__
#define __BASE_DEF_H__


/****************************************************************************************************/
/*																									*/
/*		Basic Data Type Definition																	*/
/*																									*/
/****************************************************************************************************/
/*--------------------------------------------------------------------------------------------------*/
/*		Basic Data Type Definition																	*/
/*--------------------------------------------------------------------------------------------------*/

#define FLOAT_USE       1


#ifndef FALSE
#define FALSE                                     0
#endif

#ifndef TRUE
#define TRUE                                      1
#endif



typedef signed char				CHAR;
typedef unsigned char			UCHAR;
typedef short					SHORT;
typedef unsigned short			USHORT;
typedef long					LONG;
typedef unsigned long			ULONG;
typedef int						INT;
typedef unsigned int			UINT;

typedef unsigned int            BOOL;

typedef unsigned long long		ULLONG;
typedef long long               LLONG;

#define INT64                   LLONG
/*--------------------------------------------------------------------------------------------------*/
typedef volatile signed char	VCHAR;
typedef volatile unsigned char	VUCHAR;
typedef volatile short			VSHORT;
typedef volatile unsigned short	VUSHORT;
typedef volatile long			VLONG;
typedef volatile unsigned long	VULONG;
typedef volatile int			VINT;
typedef volatile unsigned int	VUINT;
/*--------------------------------------------------------------------------------------------------*/
typedef	const UCHAR				CUCHAR;
typedef	const USHORT			CUSHORT;
typedef	const ULONG				CULONG;
/*--------------------------------------------------------------------------------------------------*/
typedef	long					KMGAIN;				/* {k,s} Type for Mulgain()						*/
typedef	long					KSGAIN;				/* {k,s} Type for PcalKsksks()					*/
/*--------------------------------------------------------------------------------------------------*/
/*		Double Byte Data Type Definition															*/
/*--------------------------------------------------------------------------------------------------*/
typedef union
{
    USHORT	w;										/* Word											*/
    struct{
#if 0
        UCHAR l;                                    /* Low Byte                                     */
        UCHAR h;                                    /* High Byte                                    */
#else
        USHORT l : 8;                               /* Low Byte                                     */
        USHORT h : 8;                               /* High Byte                                    */
#endif
    } b;
/*--------------------------------------------------------------------------------------------------*/
	SHORT	Short;									/* signed   short								*/
	USHORT	Ushort;									/* unsigned short								*/
/*--------------------------------------------------------------------------------------------------*/
	CHAR	Char[2];								/* signed   char								*/
	UCHAR	Uchar[2];								/* unsigned char								*/
} DBYTEX;

/*--------------------------------------------------------------------------------------------------*/
/*		Double Word Data Type Definition															*/
/*--------------------------------------------------------------------------------------------------*/
typedef	union
{
	ULONG	dw;										/* Double Word									*/
	struct{ USHORT l; USHORT h;} w;					/* Low Word / High Word							*/
/*--------------------------------------------------------------------------------------------------*/
	LONG	Long;									/* signed   long								*/
	ULONG	Ulong;									/* unsigned long								*/
/*--------------------------------------------------------------------------------------------------*/
	SHORT	Short[2];								/* signed   short								*/
	USHORT	Ushort[2];								/* unsigned short								*/
/*--------------------------------------------------------------------------------------------------*/
} DWORDX;





/****************************************************************************************************/
/*																									*/
/*		Basic Constant Definition																	*/
/*																									*/
/****************************************************************************************************/
typedef enum { NG=-1,   OK=0   } OKNGX;

/*--------------------------------------------------------------------------------------------------*/
#define		ON				 1
#define		OFF				 0
/*--------------------------------------------------------------------------------------------------*/
//#define		HI				 1
//#define		LO				 0
/*--------------------------------------------------------------------------------------------------*/
//#define		BUSY			 1
//#define		FREE			 0
/*--------------------------------------------------------------------------------------------------*/
#define		WAIT			 1
#define		NOWAIT			 0
/*--------------------------------------------------------------------------------------------------*/
#ifndef		NULL
#define		NULL			((void *) 0)
#endif
/*--------------------------------------------------------------------------------------------------*/


/****************************************************************************************************/
/*																									*/
/*		Basic Macro Definition																		*/
/*																									*/
/****************************************************************************************************/
#define LONGOF( l, h )  (LONG)(((ULONG)h << 16) + (ULONG)l)
#define ULONGOF( l, h )  (ULONG)(((ULONG)h << 16) + (ULONG)l)
/*--------------------------------------------------------------------------------------------------*/
/*		Bit Operation Macro Definition																*/
/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
#define	GET_BITSDATA( Vaddr, StartBitno, MaskBits )\
		( ((((ULONG*)(Vaddr))[(StartBitno)>>5])>>((StartBitno)&0x1F)) & (MaskBits) )
/*--------------------------------------------------------------------------------------------------*/
#define	SET_BITSDATA( SetAddr, Vaddr, StartBitno, SetBits, MaskBits )\
		(((ULONG*)(SetAddr))[(StartBitno)>>5]) = ( (((SetBits)&(MaskBits))<<((StartBitno)&0x1F)) |\
			(((((ULONG*)(Vaddr))[(StartBitno)>>5])) & (~((MaskBits)<<((StartBitno)&0x1F)))) )

#endif






/***************************************** end of file **********************************************/
