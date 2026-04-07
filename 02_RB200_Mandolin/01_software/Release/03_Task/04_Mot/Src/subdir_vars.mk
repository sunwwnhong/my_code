################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
OBJ_SRCS += \
../03_Task/04_Mot/Src/Mot21_VibCheck.obj \
../03_Task/04_Mot/Src/Mot22_GainSel.obj \
../03_Task/04_Mot/Src/Mot23_GainTable.obj \
../03_Task/04_Mot/Src/Mot26_TurnLib.obj \
../03_Task/04_Mot/Src/Mot27_SvcDataTrace.obj \
../03_Task/04_Mot/Src/Mot28_OnlineFFT.obj \
../03_Task/04_Mot/Src/Mot29_DtraceMngr.obj \
../03_Task/04_Mot/Src/Mot30_DtraceExe.obj \
../03_Task/04_Mot/Src/Mot31_TableExe.obj \
../03_Task/04_Mot/Src/Mot32_JatOffLine.obj \
../03_Task/04_Mot/Src/Mot33_AutoNotchSet.obj 

C_SRCS += \
../03_Task/04_Mot/Src/Mot00_Main.c \
../03_Task/04_Mot/Src/Mot01_ScanA.c \
../03_Task/04_Mot/Src/Mot02_ScanB.c \
../03_Task/04_Mot/Src/Mot03_ScanC.c \
../03_Task/04_Mot/Src/Mot05_Round.c \
../03_Task/04_Mot/Src/Mot05_VarDef.c \
../03_Task/04_Mot/Src/Mot06_MotorParamTable.c \
../03_Task/04_Mot/Src/Mot07_MotorParamCal.c \
../03_Task/04_Mot/Src/Mot08_BaseParamCalc.c \
../03_Task/04_Mot/Src/Mot09_StateMachine.c \
../03_Task/04_Mot/Src/Mot10_ServoControl.c \
../03_Task/04_Mot/Src/Mot12_MoSenclf.c \
../03_Task/04_Mot/Src/Mot13_MoSpeedlf.c \
../03_Task/04_Mot/Src/Mot14_MRev.c \
../03_Task/04_Mot/Src/Mot15_Voltage.c \
../03_Task/04_Mot/Src/Mot16_Temperature.c \
../03_Task/04_Mot/Src/Mot17_MakeMonitorData.c \
../03_Task/04_Mot/Src/Mot35_MotorRunOver.c \
../03_Task/04_Mot/Src/Mot36_MotorStall.c \
../03_Task/04_Mot/Src/Mot38_AI12Deal.c \
../03_Task/04_Mot/Src/Mot39_RegPowerProtect.c \
../03_Task/04_Mot/Src/Mot40_ALMDeal.c \
../03_Task/04_Mot/Src/Mot41_ServoStatus.c \
../03_Task/04_Mot/Src/Mot42_ABSReq.c \
../03_Task/04_Mot/Src/Mot43_DBBrakeProtect.c \
../03_Task/04_Mot/Src/Mot50_DIDO.c \
../03_Task/04_Mot/Src/Mot51_PanOper.c \
../03_Task/04_Mot/Src/Mot53_ParamMngr.c \
../03_Task/04_Mot/Src/Mot54_ParamEeprom.c \
../03_Task/04_Mot/Src/Mot55_ErrorDeal.c \
../03_Task/04_Mot/Src/Mot56_STO.c \
../03_Task/04_Mot/Src/Mot59_FactoryTest.c \
../03_Task/04_Mot/Src/Mot60_InformationCheck.c \
../03_Task/04_Mot/Src/Mot61_MotorLessTest.c \
../03_Task/04_Mot/Src/Mot62_DriveType.c \
../03_Task/04_Mot/Src/Mot63_MulAxis_485.c \
../03_Task/04_Mot/Src/Mot64_SerialNum.c 

C_DEPS += \
./03_Task/04_Mot/Src/Mot00_Main.d \
./03_Task/04_Mot/Src/Mot01_ScanA.d \
./03_Task/04_Mot/Src/Mot02_ScanB.d \
./03_Task/04_Mot/Src/Mot03_ScanC.d \
./03_Task/04_Mot/Src/Mot05_Round.d \
./03_Task/04_Mot/Src/Mot05_VarDef.d \
./03_Task/04_Mot/Src/Mot06_MotorParamTable.d \
./03_Task/04_Mot/Src/Mot07_MotorParamCal.d \
./03_Task/04_Mot/Src/Mot08_BaseParamCalc.d \
./03_Task/04_Mot/Src/Mot09_StateMachine.d \
./03_Task/04_Mot/Src/Mot10_ServoControl.d \
./03_Task/04_Mot/Src/Mot12_MoSenclf.d \
./03_Task/04_Mot/Src/Mot13_MoSpeedlf.d \
./03_Task/04_Mot/Src/Mot14_MRev.d \
./03_Task/04_Mot/Src/Mot15_Voltage.d \
./03_Task/04_Mot/Src/Mot16_Temperature.d \
./03_Task/04_Mot/Src/Mot17_MakeMonitorData.d \
./03_Task/04_Mot/Src/Mot35_MotorRunOver.d \
./03_Task/04_Mot/Src/Mot36_MotorStall.d \
./03_Task/04_Mot/Src/Mot38_AI12Deal.d \
./03_Task/04_Mot/Src/Mot39_RegPowerProtect.d \
./03_Task/04_Mot/Src/Mot40_ALMDeal.d \
./03_Task/04_Mot/Src/Mot41_ServoStatus.d \
./03_Task/04_Mot/Src/Mot42_ABSReq.d \
./03_Task/04_Mot/Src/Mot43_DBBrakeProtect.d \
./03_Task/04_Mot/Src/Mot50_DIDO.d \
./03_Task/04_Mot/Src/Mot51_PanOper.d \
./03_Task/04_Mot/Src/Mot53_ParamMngr.d \
./03_Task/04_Mot/Src/Mot54_ParamEeprom.d \
./03_Task/04_Mot/Src/Mot55_ErrorDeal.d \
./03_Task/04_Mot/Src/Mot56_STO.d \
./03_Task/04_Mot/Src/Mot59_FactoryTest.d \
./03_Task/04_Mot/Src/Mot60_InformationCheck.d \
./03_Task/04_Mot/Src/Mot61_MotorLessTest.d \
./03_Task/04_Mot/Src/Mot62_DriveType.d \
./03_Task/04_Mot/Src/Mot63_MulAxis_485.d \
./03_Task/04_Mot/Src/Mot64_SerialNum.d 

OBJS += \
./03_Task/04_Mot/Src/Mot00_Main.obj \
./03_Task/04_Mot/Src/Mot01_ScanA.obj \
./03_Task/04_Mot/Src/Mot02_ScanB.obj \
./03_Task/04_Mot/Src/Mot03_ScanC.obj \
./03_Task/04_Mot/Src/Mot05_Round.obj \
./03_Task/04_Mot/Src/Mot05_VarDef.obj \
./03_Task/04_Mot/Src/Mot06_MotorParamTable.obj \
./03_Task/04_Mot/Src/Mot07_MotorParamCal.obj \
./03_Task/04_Mot/Src/Mot08_BaseParamCalc.obj \
./03_Task/04_Mot/Src/Mot09_StateMachine.obj \
./03_Task/04_Mot/Src/Mot10_ServoControl.obj \
./03_Task/04_Mot/Src/Mot12_MoSenclf.obj \
./03_Task/04_Mot/Src/Mot13_MoSpeedlf.obj \
./03_Task/04_Mot/Src/Mot14_MRev.obj \
./03_Task/04_Mot/Src/Mot15_Voltage.obj \
./03_Task/04_Mot/Src/Mot16_Temperature.obj \
./03_Task/04_Mot/Src/Mot17_MakeMonitorData.obj \
./03_Task/04_Mot/Src/Mot35_MotorRunOver.obj \
./03_Task/04_Mot/Src/Mot36_MotorStall.obj \
./03_Task/04_Mot/Src/Mot38_AI12Deal.obj \
./03_Task/04_Mot/Src/Mot39_RegPowerProtect.obj \
./03_Task/04_Mot/Src/Mot40_ALMDeal.obj \
./03_Task/04_Mot/Src/Mot41_ServoStatus.obj \
./03_Task/04_Mot/Src/Mot42_ABSReq.obj \
./03_Task/04_Mot/Src/Mot43_DBBrakeProtect.obj \
./03_Task/04_Mot/Src/Mot50_DIDO.obj \
./03_Task/04_Mot/Src/Mot51_PanOper.obj \
./03_Task/04_Mot/Src/Mot53_ParamMngr.obj \
./03_Task/04_Mot/Src/Mot54_ParamEeprom.obj \
./03_Task/04_Mot/Src/Mot55_ErrorDeal.obj \
./03_Task/04_Mot/Src/Mot56_STO.obj \
./03_Task/04_Mot/Src/Mot59_FactoryTest.obj \
./03_Task/04_Mot/Src/Mot60_InformationCheck.obj \
./03_Task/04_Mot/Src/Mot61_MotorLessTest.obj \
./03_Task/04_Mot/Src/Mot62_DriveType.obj \
./03_Task/04_Mot/Src/Mot63_MulAxis_485.obj \
./03_Task/04_Mot/Src/Mot64_SerialNum.obj 

OBJS__QUOTED += \
"03_Task\04_Mot\Src\Mot00_Main.obj" \
"03_Task\04_Mot\Src\Mot01_ScanA.obj" \
"03_Task\04_Mot\Src\Mot02_ScanB.obj" \
"03_Task\04_Mot\Src\Mot03_ScanC.obj" \
"03_Task\04_Mot\Src\Mot05_Round.obj" \
"03_Task\04_Mot\Src\Mot05_VarDef.obj" \
"03_Task\04_Mot\Src\Mot06_MotorParamTable.obj" \
"03_Task\04_Mot\Src\Mot07_MotorParamCal.obj" \
"03_Task\04_Mot\Src\Mot08_BaseParamCalc.obj" \
"03_Task\04_Mot\Src\Mot09_StateMachine.obj" \
"03_Task\04_Mot\Src\Mot10_ServoControl.obj" \
"03_Task\04_Mot\Src\Mot12_MoSenclf.obj" \
"03_Task\04_Mot\Src\Mot13_MoSpeedlf.obj" \
"03_Task\04_Mot\Src\Mot14_MRev.obj" \
"03_Task\04_Mot\Src\Mot15_Voltage.obj" \
"03_Task\04_Mot\Src\Mot16_Temperature.obj" \
"03_Task\04_Mot\Src\Mot17_MakeMonitorData.obj" \
"03_Task\04_Mot\Src\Mot35_MotorRunOver.obj" \
"03_Task\04_Mot\Src\Mot36_MotorStall.obj" \
"03_Task\04_Mot\Src\Mot38_AI12Deal.obj" \
"03_Task\04_Mot\Src\Mot39_RegPowerProtect.obj" \
"03_Task\04_Mot\Src\Mot40_ALMDeal.obj" \
"03_Task\04_Mot\Src\Mot41_ServoStatus.obj" \
"03_Task\04_Mot\Src\Mot42_ABSReq.obj" \
"03_Task\04_Mot\Src\Mot43_DBBrakeProtect.obj" \
"03_Task\04_Mot\Src\Mot50_DIDO.obj" \
"03_Task\04_Mot\Src\Mot51_PanOper.obj" \
"03_Task\04_Mot\Src\Mot53_ParamMngr.obj" \
"03_Task\04_Mot\Src\Mot54_ParamEeprom.obj" \
"03_Task\04_Mot\Src\Mot55_ErrorDeal.obj" \
"03_Task\04_Mot\Src\Mot56_STO.obj" \
"03_Task\04_Mot\Src\Mot59_FactoryTest.obj" \
"03_Task\04_Mot\Src\Mot60_InformationCheck.obj" \
"03_Task\04_Mot\Src\Mot61_MotorLessTest.obj" \
"03_Task\04_Mot\Src\Mot62_DriveType.obj" \
"03_Task\04_Mot\Src\Mot63_MulAxis_485.obj" \
"03_Task\04_Mot\Src\Mot64_SerialNum.obj" 

C_DEPS__QUOTED += \
"03_Task\04_Mot\Src\Mot00_Main.d" \
"03_Task\04_Mot\Src\Mot01_ScanA.d" \
"03_Task\04_Mot\Src\Mot02_ScanB.d" \
"03_Task\04_Mot\Src\Mot03_ScanC.d" \
"03_Task\04_Mot\Src\Mot05_Round.d" \
"03_Task\04_Mot\Src\Mot05_VarDef.d" \
"03_Task\04_Mot\Src\Mot06_MotorParamTable.d" \
"03_Task\04_Mot\Src\Mot07_MotorParamCal.d" \
"03_Task\04_Mot\Src\Mot08_BaseParamCalc.d" \
"03_Task\04_Mot\Src\Mot09_StateMachine.d" \
"03_Task\04_Mot\Src\Mot10_ServoControl.d" \
"03_Task\04_Mot\Src\Mot12_MoSenclf.d" \
"03_Task\04_Mot\Src\Mot13_MoSpeedlf.d" \
"03_Task\04_Mot\Src\Mot14_MRev.d" \
"03_Task\04_Mot\Src\Mot15_Voltage.d" \
"03_Task\04_Mot\Src\Mot16_Temperature.d" \
"03_Task\04_Mot\Src\Mot17_MakeMonitorData.d" \
"03_Task\04_Mot\Src\Mot35_MotorRunOver.d" \
"03_Task\04_Mot\Src\Mot36_MotorStall.d" \
"03_Task\04_Mot\Src\Mot38_AI12Deal.d" \
"03_Task\04_Mot\Src\Mot39_RegPowerProtect.d" \
"03_Task\04_Mot\Src\Mot40_ALMDeal.d" \
"03_Task\04_Mot\Src\Mot41_ServoStatus.d" \
"03_Task\04_Mot\Src\Mot42_ABSReq.d" \
"03_Task\04_Mot\Src\Mot43_DBBrakeProtect.d" \
"03_Task\04_Mot\Src\Mot50_DIDO.d" \
"03_Task\04_Mot\Src\Mot51_PanOper.d" \
"03_Task\04_Mot\Src\Mot53_ParamMngr.d" \
"03_Task\04_Mot\Src\Mot54_ParamEeprom.d" \
"03_Task\04_Mot\Src\Mot55_ErrorDeal.d" \
"03_Task\04_Mot\Src\Mot56_STO.d" \
"03_Task\04_Mot\Src\Mot59_FactoryTest.d" \
"03_Task\04_Mot\Src\Mot60_InformationCheck.d" \
"03_Task\04_Mot\Src\Mot61_MotorLessTest.d" \
"03_Task\04_Mot\Src\Mot62_DriveType.d" \
"03_Task\04_Mot\Src\Mot63_MulAxis_485.d" \
"03_Task\04_Mot\Src\Mot64_SerialNum.d" 

C_SRCS__QUOTED += \
"../03_Task/04_Mot/Src/Mot00_Main.c" \
"../03_Task/04_Mot/Src/Mot01_ScanA.c" \
"../03_Task/04_Mot/Src/Mot02_ScanB.c" \
"../03_Task/04_Mot/Src/Mot03_ScanC.c" \
"../03_Task/04_Mot/Src/Mot05_Round.c" \
"../03_Task/04_Mot/Src/Mot05_VarDef.c" \
"../03_Task/04_Mot/Src/Mot06_MotorParamTable.c" \
"../03_Task/04_Mot/Src/Mot07_MotorParamCal.c" \
"../03_Task/04_Mot/Src/Mot08_BaseParamCalc.c" \
"../03_Task/04_Mot/Src/Mot09_StateMachine.c" \
"../03_Task/04_Mot/Src/Mot10_ServoControl.c" \
"../03_Task/04_Mot/Src/Mot12_MoSenclf.c" \
"../03_Task/04_Mot/Src/Mot13_MoSpeedlf.c" \
"../03_Task/04_Mot/Src/Mot14_MRev.c" \
"../03_Task/04_Mot/Src/Mot15_Voltage.c" \
"../03_Task/04_Mot/Src/Mot16_Temperature.c" \
"../03_Task/04_Mot/Src/Mot17_MakeMonitorData.c" \
"../03_Task/04_Mot/Src/Mot35_MotorRunOver.c" \
"../03_Task/04_Mot/Src/Mot36_MotorStall.c" \
"../03_Task/04_Mot/Src/Mot38_AI12Deal.c" \
"../03_Task/04_Mot/Src/Mot39_RegPowerProtect.c" \
"../03_Task/04_Mot/Src/Mot40_ALMDeal.c" \
"../03_Task/04_Mot/Src/Mot41_ServoStatus.c" \
"../03_Task/04_Mot/Src/Mot42_ABSReq.c" \
"../03_Task/04_Mot/Src/Mot43_DBBrakeProtect.c" \
"../03_Task/04_Mot/Src/Mot50_DIDO.c" \
"../03_Task/04_Mot/Src/Mot51_PanOper.c" \
"../03_Task/04_Mot/Src/Mot53_ParamMngr.c" \
"../03_Task/04_Mot/Src/Mot54_ParamEeprom.c" \
"../03_Task/04_Mot/Src/Mot55_ErrorDeal.c" \
"../03_Task/04_Mot/Src/Mot56_STO.c" \
"../03_Task/04_Mot/Src/Mot59_FactoryTest.c" \
"../03_Task/04_Mot/Src/Mot60_InformationCheck.c" \
"../03_Task/04_Mot/Src/Mot61_MotorLessTest.c" \
"../03_Task/04_Mot/Src/Mot62_DriveType.c" \
"../03_Task/04_Mot/Src/Mot63_MulAxis_485.c" \
"../03_Task/04_Mot/Src/Mot64_SerialNum.c" 


