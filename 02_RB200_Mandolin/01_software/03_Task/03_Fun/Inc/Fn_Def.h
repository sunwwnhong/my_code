  
  
  
  
  
  
  
 
#ifndef Fn_Def_H
#define Fn_Def_H
  
  
  
  
  
  
#define FUNDEF_VERSION			0x0001			 
#define FUNTBL_VERSION			0x0001			 
 
  
  
 
  
 typedef struct	{
	UCHAR	ParaRun;							 
	UCHAR	ParaTrc;							 
	UCHAR	ExeDisable;							 
	UCHAR	ChkSpUse;							 
	UCHAR	AccessLevel;						 
	UCHAR	SName[12];							 
 	LONG	(*FuncBgnPtr)(FUNEXE *);			 
	LONG	(*FuncExePtr)(FUNEXE *);			 
	void	(*FuncEndPtr)(FUNEXE *, UCHAR);		 
 	void	(*FuncInitPtr)(void);				 
} FUNDEF;
 typedef const FUNDEF CFUNDEF;					 
  
 typedef struct	{
	USHORT	FnNo;								 
	USHORT	FnMode;								 
	CFUNDEF	*FunDefPtr;							 
} FUNTBL;
typedef const FUNTBL CFUNTBL;					 
  
  
  
  
LONG	FunNoInitProcess( FUNEXE * );			 
LONG	FunExeDummy( FUNEXE * );				 
void	FunEndDummy( FUNEXE *, UCHAR );			 
extern  const FUNTBL FnFunTbl[];
 extern  const USHORT FnFunTblEntNum;
 #define FNFUNTBL_ENTNUM		FnFunTblEntNum
 
#endif
