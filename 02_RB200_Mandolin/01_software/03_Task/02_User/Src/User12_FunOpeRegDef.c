/****************************************************************************************************/
/*************** (C) COPYRIGHT 2024  Veichi Technology Co., Ltd*********************************
* File Name          : APL_ParaCode06_FunOpeRegDef.c
* Version            : V0.1
* Date               : 2024
* Description        : 操作寄存器：参数定义、管理、映射
***********************************************************************************************/
#include "Main.h"


ATXREG  AtxReg;
OPEREG	OpeReg;								        /* 操作寄存器									*/
SVTREG  SvtReg;
INERTIAREG InertiaReg;
/*--------------------------------------------------------------------------------------------------*/

#define TRCNUM  (sizeof(Trcbuf))

/*--------------------------------------------------------------------------------------------------*/

const	FORDEF	FunOpeRegDefTbl[] = {
/*{B,L,B,E,S,R,W,-},   Rno,  IniVal, Llimit, Ulimit,  VarAdr,					ReadFunc,			WriteFunc	*/
/*--------------------------------------------------------------------------------------------------*/
{ {0,0,1,1,0,1,0,0}, 0x0003, TRCNUM, 0x0000, 0xFFFF, &TrcReg.MaxAreaSize,       NULL,			    NULL						},
{ {0,0,1,1,0,1,1,0}, 0x0004, 0x2000, 0x0400, 0x2000, &TrcReg.AreaSize,			NULL,				RpxWriteTrcOpeRegister		}, /* 底层存储空间的大小     */
{ {1,0,1,1,0,1,1,0}, 0x0005, 0x0003, 0x0001, 0x0104, &TrcReg.TrcMode,			NULL,				RpxWriteTrcOpeRegister		}, /* 数据采样通道数       */
{ {0,0,1,1,0,1,1,0}, 0x0006, 0x0001, 0x0001, 0x0002, &TrcReg.DataSize,			NULL,				RpxWriteTrcOpeRegister		}, /* 数据类型 */
{ {0,0,1,1,0,1,1,0}, 0x0007, 0x0001, 0x0001, 0xFFFF, &TrcReg.SampIntv,			NULL,				RpxWriteTrcOpeRegister		}, /* 采样间隔 125us基准*/
{ {0,0,1,1,0,1,1,0}, 0x0008, 0x0101, 0x0000, 0xFFFF, &TrcReg.TrcSel[0],			NULL,				RpxWriteTrcOpeRegister		}, /* 通道1中选择*/
{ {0,0,1,1,0,1,1,0}, 0x0009, 0x0204, 0x0000, 0xFFFF, &TrcReg.TrcSel[1],			NULL,				RpxWriteTrcOpeRegister		}, /* 通道2中选择*/
{ {0,0,1,1,0,1,1,0}, 0x0010, 0x0305, 0x0000, 0xFFFF, &TrcReg.TrcSel[2],			NULL,				RpxWriteTrcOpeRegister		}, /* 通道3中选择*/
{ {0,0,1,1,0,1,1,0}, 0x0011, 0x0000, 0x0000, 0xFFFF, &TrcReg.TrcSel[3],			NULL,				RpxWriteTrcOpeRegister		}, /* 通道4中选择*/
{ {0,0,1,1,0,1,1,0}, 0x0020, 0x0000, 0x0000, 0xFFFF, &TrcReg.PtrgDnum,			NULL,				RpxWriteTrcOpeRegister		},
{ {0,0,1,1,0,1,1,0}, 0x0021, 0x0019, 0x0000, 0x007F, &TrcReg.TrgSel,			NULL,				RpxWriteTrcOpeRegister		},
{ {0,1,1,0,1,1,1,0}, 0x0022, 0x0003, 0x0000, 0xFFFF, &TrcReg.TrgLevel.w.l,		NULL,				RpxWriteTrcOpeRegister		},
{ {0,1,0,1,1,1,1,0}, 0x0023, 0x0000, 0x8000, 0x7FFF, &TrcReg.TrgLevel.w.h,		NULL,				RpxWriteTrcOpeRegister		},
{ {0,0,1,1,0,1,1,0}, 0x0024, 0x0000, 0x0000, 0xFFFF, &TrcReg.MTrgMode,			NULL,				RpxWriteTrcOpeRegister		},
{ {0,0,1,1,0,1,1,0}, 0x0025, 0x0000, 0x0000, 0xFFFF, &TrcReg.MTrgSel,			NULL,				RpxWriteTrcOpeRegister		},
{ {0,1,1,0,1,1,1,0}, 0x0026, 0x0000, 0x0000, 0xFFFF, &TrcReg.MTrgLevel.w.l,		NULL,				RpxWriteTrcOpeRegister		},
{ {0,1,0,1,1,1,1,0}, 0x0027, 0x0000, 0x8000, 0x7FFF, &TrcReg.MTrgLevel.w.h,		NULL,				RpxWriteTrcOpeRegister		},
{ {0,1,1,0,1,1,0,0}, 0x0028, 0x0000, 0x0000, 0xFFFF, &TrcReg.RngTrcIdx,			NULL,				NULL						},
{ {0,1,0,1,1,1,0,0}, 0x0029, 0x0000, 0x0000, 0xFFFF, &TrcReg.RngTrcCnt,			NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0030, 0x0000, 0x0000, 0xFFFF, &TrcReg.TrgPoint,			NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0031, 0x0000, 0x0000, 0xFFFF, &TrcReg.TrcState,			NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x0040, 0x0000, 0x0000, 0xFFFF, &TrcReg.InterEnc,			NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x0050, 0x0001, 0x0001, 0x0005, &TrcReg.TblMode,			NULL,				RpxWriteTdrvOpeRegister		},
{ {0,0,1,1,0,1,1,0}, 0x0051, 0x0000, 0x0000, 0xFFFF, &TrcReg.TblLimit,			NULL,				RpxWriteTdrvOpeRegister		},
{ {0,0,1,1,0,1,0,0}, 0x0052, 0x0000, 0x0000, 0xFFFF, &TrcReg.TblState,			NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x0053, 0x0000, 0x0000, 0xFF03, &TrcReg.TblFuncSel,		NULL,				RpxWriteTdrvOpeRegister		},
{ {0,0,1,1,0,1,1,0}, 0x0100, 0x0000, 0x0000, 0xFFFF, &OpeReg.OpeMode,			NULL,				NULL						},
{ {0,0,1,1,0,0,1,0}, 0x0101, 0x0000, 0x0000, 0xFFFF, &OpeReg.OpeCmd,			NULL,				NULL						},
{ {0,0,1,1,0,0,1,0}, 0x0102, 0x0000, 0x0000, 0xFFFF, &OpeReg.OpeEnd,			NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x0103, 0x0000, 0x0000, 0xFFFF, &OpeReg.AccLevel,			NULL,				RpxWriteFunRegAccLevel		},
{ {0,0,1,1,0,1,1,0}, 0x0104, 0x0000, 0x0000, 0xFFFF, &OpeReg.OpeMode2,			NULL,				NULL						},
{ {0,0,1,1,0,0,1,0}, 0x0105, 0x0000, 0x0000, 0xFFFF, &OpeReg.OpeCmd2,			NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x0106, 0x0000, 0x0000, 0xFFFF, &OpeReg.OpeModeTrc,		NULL,				NULL						},
{ {0,0,1,1,0,0,1,0}, 0x0107, 0x0000, 0x0000, 0xFFFF, &OpeReg.OpeCmdTrc,			NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x0108, 0x0001, 0x0001, 0xFFFF, &OpeReg.SafetyTime,		NULL,				RpxWriteFunRegSafetyTime	},
{ {0,0,1,1,0,1,1,0}, 0x0112, 0x0000, 0x0000, 0xFFFF, &OpeReg.AdatMode,			NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x0113, 0x0000, 0x0000, 0xFFFF, &OpeReg.AdatLevel,			NULL,				NULL						},
{ {0,1,1,0,1,1,1,0}, 0x0114, 0x0000, 0x0000, 0xFFFF, &OpeReg.AdatMovep.w.l,		NULL,				NULL						},
{ {0,1,0,1,1,1,1,0}, 0x0115, 0x0000, 0x8000, 0x7FFF, &OpeReg.AdatMovep.w.h,		NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0116, 0x0000, 0x0000, 0xFFFF, &OpeReg.AdatState,			NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0117, 0x0000, 0x0000, 0xFFFF, &OpeReg.VibmState,			NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x0120, 0x0000, 0x0000, 0xFFFF, &OpeReg.PrmWrtDis,			NULL,				NULL						},//RpxWriteFunRegPrmWrtDis		},
{ {0,0,1,1,0,1,1,0}, 0x0121, 0x0000, 0x0000, 0xFFFF, &OpeReg.PrmAccess,			NULL,				NULL						},//RpxWriteFunRegPrmAccess		},
{ {0,0,1,1,0,1,0,0}, 0x0131, 0x0000, 0x0000, 0xFFFF, &OpeReg.PjogState,			NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0134, 0x0000, 0x0000, 0xFFFF, &OpeReg.JogState,			NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x0150, 0x0002, 0x0000, 0x0003, &OpeReg.SpatMode,			NULL,				NULL						},//RpxWriteFunRegSpatMode		},
{ {0,0,1,1,0,1,1,0}, 0x0151, 0x0000, 0x0000, 0xFFFF, &OpeReg.SpatLevel,			NULL,				NULL						},//RpxWriteFunRegSpatLevel		},
{ {0,0,1,1,0,1,1,0}, 0x0152, 0x0000, 0x0000, 0xFFFF, &OpeReg.SpatFFLevel,		NULL,				NULL						},//RpxWriteFunRegSpatFFLevel	},
{ {0,0,1,1,0,1,0,0}, 0x0153, 0x0000, 0x0000, 0xFFFF, &OpeReg.SpatLvlChgState,	NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0154, 0x0000, 0x0000, 0xFFFF, &OpeReg.SpatANotchState,	NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0155, 0x0000, 0x0000, 0xFFFF, &OpeReg.SpatAresState,		NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x0160, 0x0000, 0x0000, 0xFFFF, &OpeReg.EzFftMode,			NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0161, 0x0000, 0x0000, 0xFFFF, &OpeReg.EzFftState,		NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x0162, 0x0000, 0x0000, 0xFFFF, &OpeReg.EzFftTrq,			NULL,				NULL						},//RpxWriteFunRegEzFftTrq		},
{ {0,0,1,1,0,1,1,0}, 0x0190, 0x0000, 0x0000, 0x0001, &OpeReg.AdatMode,			NULL,				NULL						},//RpxWriteFunRegAdatMode		},
{ {0,0,1,1,0,1,1,0}, 0x0191, 0x0001, 0x0001, 0x0003, &OpeReg.AdatLevel,			NULL,				NULL						},//RpxWriteFunRegAdatLevel		},
{ {0,1,1,0,1,1,1,0}, 0x0192, 0x0002, 0x0000, 0xFFFF, &OpeReg.AdatMovep.w.l,		NULL,				NULL						},//RpxWriteFunRegAdatMovep		},
{ {0,1,0,1,1,1,1,0}, 0x0193, 0x0000, 0x8000, 0x7FFF, &OpeReg.AdatMovep.w.h,		NULL,				NULL						},//RpxWriteFunRegAdatMovep		},
{ {0,0,1,1,0,1,0,0}, 0x0194, 0x0000, 0x0000, 0xFFFF, &OpeReg.AdatState,			NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x0195, 0x0002, 0x0001, 0x0003, &OpeReg.AdatFilType,		NULL,				NULL						},//RpxWriteFunRegAdatFilType	},
{ {0,0,1,1,0,1,1,0}, 0x0196, 0x0002, 0x0001, 0x0003, &OpeReg.AdatDefault,		NULL,				NULL						},//RpxWriteFunRegAdatFilType	},
{ {0,0,1,1,0,1,1,0}, 0x01A0, 0x0000, 0x0000, 0x0001, &OpeReg.AvibMode,			NULL,				NULL						},//RpxWriteFunRegAvibMode		},
{ {0,0,1,1,0,1,0,0}, 0x01A1, 0x0000, 0x0000, 0xFFFF, &OpeReg.AvibState,			NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x01A2, 0x0000, 0x0000, 0xFFFF, &OpeReg.AvibFreq,			NULL,				NULL						},//RpxWriteFunRegAvibFreq		},
{ {0,0,1,1,0,1,1,0}, 0x01A3, 0x0000, 0x0000, 0xFFFF, &OpeReg.AvibGain,			NULL,				NULL						},//RpxWriteFunRegAvibGain		},
{ {0,0,1,1,0,1,1,0}, 0x01B0, 0x0000, 0x0000, 0xFFFF, &OpeReg.MdlVibFreq,		NULL,				NULL						},//RpxWriteFunRegMdlVibFreq	},
{ {0,0,1,1,0,1,0,0}, 0x01B1, 0x0000, 0x0000, 0xFFFF, &OpeReg.MdlVibState,		NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x01B2, 0x0000, 0x0000, 0xFFFF, &OpeReg.MdlVibFreq2,		NULL,				NULL						},//RpxWriteFunRegMdlVibFreq2	},
{ {0,0,1,1,0,1,1,0}, 0x01B3, 0x0000, 0x0000, 0xFFFF, &OpeReg.MdlVibFil2,		NULL,				NULL						},//RpxWriteFunRegMdlVibFil2	},
{ {0,0,1,1,0,1,0,0}, 0x01B4, 0x0000, 0x0000, 0xFFFF, &OpeReg.MdlVibState2,		NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x01E0, 0x0004, 0x0001, 0x0004, &OpeReg.DatGnLevel,		NULL,				NULL						},//RpxWriteFunRegDATGainLevel	},
{ {0,0,1,1,0,1,1,0}, 0x01E1, 0x0001, 0x0000, 0x0002, &OpeReg.DatJratLevel,		NULL,				NULL						},//RpxWriteFunRegDATJratLevel	},
/*--------------------------------------------------------------------------------------------------*/
{ {0,0,1,1,0,1,1,0}, 0x01F0, 0x0001, 0x0000, 0x0003, &OpeReg.EeClrStatus,		NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x01F1, 0x0001, 0x0000, 0x0003, &OpeReg.EeWriteStatus,		NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x01F4, 0x0000, 0x0000, 0x0003, &OpeReg.EepromErStatus,	NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x01F5, 0x03E8, 0x0000, 0xFFFF, &OpeReg.PoleFineTorq,	    NULL,				NULL						},
{ {0,0,1,1,0,1,1,0}, 0x01F6, 0x0000, 0x0000, 0xFFFF, &OpeReg.PoleFineStatus,	NULL,				NULL						},
/*--------------------------------------------------------------------------------------------------*/
{ {0,0,1,1,0,1,0,0}, 0x0200, 0x0000, 0x0000, 0xFFFF, &AtxReg.VibmRf[0].Freq,	NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0201, 0x0000, 0x0000, 0xFFFF, &AtxReg.VibmRf[0].Amp,		NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0202, 0x0000, 0x0000, 0xFFFF, &AtxReg.VibmRf[1].Freq,	NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0203, 0x0000, 0x0000, 0xFFFF, &AtxReg.VibmRf[1].Amp,		NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0204, 0x0000, 0x0000, 0xFFFF, &AtxReg.VibmRf[2].Freq,	NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0205, 0x0000, 0x0000, 0xFFFF, &AtxReg.VibmRf[2].Amp,		NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0206, 0x0000, 0x0000, 0xFFFF, &AtxReg.VibmAf.Freq,		NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0207, 0x0000, 0x0000, 0xFFFF, &AtxReg.VibmAf.Amp,		NULL,				NULL						},
{ {0,0,1,1,0,1,0,0}, 0x0210, 0x0000, 0x0000, 0xFFFF, &AtxReg.EzFftDetf,			NULL,				NULL		                },
{ {0,0,1,1,0,1,0,0}, 0x0211, 0x0000, 0x0000, 0xFFFF, &AtxReg.EzFftFil1,			NULL,				NULL		                },
{ {0,0,1,1,0,1,0,0}, 0x0212, 0x0000, 0x0000, 0xFFFF, &AtxReg.EzFftFil2,			NULL,				NULL		                },
{ {0,0,1,1,0,1,0,0}, 0x0220, 0x0000, 0x0000, 0xFFFF, &AtxReg.Jrateid,			NULL,				NULL		                },
/*--------------------------------------------------------------------------------------------------*/
{ {0,0,1,1,0,1,1,0}, 0x0240, 0x0000, 0x0000, 0xFFFF, &InertiaReg.Flag,	        NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x0241, 0x0064, 0x0032, 0x01F4, &InertiaReg.Jog_Spd,	    NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x0242, 0x0032, 0x000A, 0x03E8, &InertiaReg.Jog_AccTm,	    NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x0243, 0x0000, 0x0000, 0x01F4, &InertiaReg.Trv_Max,	    NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x0244, 0x0000, 0xFE0C, 0x0000, &InertiaReg.Trv_Min,	    NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x0245, 0x0000, 0xFE0C, 0x01F4, &InertiaReg.Stroke_Bar,    NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x0246, 0x0000, 0x0000, 0x0003, &InertiaReg.Run_Mod,       NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x0247, 0x0002, 0x0002, 0x0004, &InertiaReg.Run_Cnt,       NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x0248, 0x0004, 0x0001, 0x0004, &InertiaReg.Turn_Num,      NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x0249, 0x0000, 0x0000, 0x4E20, &InertiaReg.Interia_Ratio, NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x024A, 0x0000, 0x0000, 0x4E20, &InertiaReg.Inria_RatioSet,NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x024B, 0x000D, 0x0000, 0x001F, &InertiaReg.Rigid_Grade,   NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x024C, 0x0000, 0x0000, 0x0003, &InertiaReg.Rig_Runmod,    NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x024D, 0x01F4, 0x0000, 0x09C4, &InertiaReg.Rig_MaxSpd,    NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x024E, 0x0028, 0x0000, 0x01F4, &InertiaReg.Rig_TurnNum,   NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x024F, 0x0032, 0x000A, 0x03E8, &InertiaReg.Rig_AccTm,     NULL,				NULL		                },

{ {0,0,1,1,0,1,1,0}, 0x0250, 0x0000, 0x0000, 0xFFFF, &InertiaReg.Rig_AdjTm,     NULL,				NULL		                },
{ {0,0,1,1,0,1,1,0}, 0x0251, 0x0000, 0x0000, 0xFFFF, &InertiaReg.Rig_OvShoot,   NULL,				NULL		                },

{ {0,0,1,1,0,1,1,0}, 0x0300, 0x0000, 0x0000, 0xFFFF, &SvtReg.EncType,           NULL,               NULL                        },
{ {0,0,1,1,0,1,1,0}, 0x0301, 0x0000, 0x0000, 0xFFFF, &SvtReg.RatTrq,            NULL,               NULL                        },


{ {0,0,1,1,0,1,1,0}, 0x03FF, 0x0001, 0x0000, 0xFFFF, &SvtReg.TurnSet,           NULL,               NULL                        },

//{ {0,0,0,0,0,0,0,0}, 0xFFFF, 0x0000, 0x0000, 0x0000, NULL, NULL },
};
const	USHORT	FunOpeRegDefTblEntNum = sizeof(FunOpeRegDefTbl)/sizeof(FunOpeRegDefTbl[0]);

/****************************************************************************************************/
/*                               The End of the file                                                */
/****************************************************************************************************/
