/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
*
* File Name 		 : APL_MotDrv01_SpdCtrl.h
*
* Version			 : V0.1
* Date				 : 2024
***********************************************************************************************/

#ifndef Pos18_MIT_H
#define Pos18_MIT_H



typedef struct
{
    USHORT   KpValCmd;                                  //
    USHORT   KdValCmd;                                  //
    SHORT   AngleCmd;                                   //
    SHORT   AngleCmdSin;                                   //
    SHORT   VelCmd;                                     //0.01rad/s
    SHORT   TorqCmd;                                    //

    SHORT   AngleCmdFil;                                //0.01rad
    LONG    VelFed1;                                    //0.01rad/s                                   //
    LONG    AngleFeb;                                   //
    LONG    VelFeb;                                     //0.001rad/s
    LONG    TorqFeb;                                    //0.001rad/s
    LONG    CurFeb;                                    //

    float  PosCtrNm;
    float  PosCtrAout;
    float  TrqTn;


    float  Kt;
    float  GR;

    float  PosFilt;
    float  TrefFilt;

    SHORT  Effcient;
    LONG   TrqNm;

    LONG   TrqMIT;
    LONG   TrqWm;
    LONG   TrqRefo;
    LONG   TrqRefitl;
    LONG   TrqSitam;
    LONG   MRPulseLSitam;

}MITSTRUCT;

extern MITSTRUCT MIT;


extern LONG	APL_MITCtr_ScanA( void );
extern LONG MIT_SpeedLevelCal( LONG  Speed );
extern LONG MIT_CurrentLevelCal( float  I );
extern void MIT_Fedback_Mon(void);
extern void MIT_Init(void);

extern void MIT_Para_Update( void );

#endif
