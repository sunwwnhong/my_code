################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
OBJ_SRCS += \
../03_Task/08_Cur/Src/Cur11_RipplComp.obj \
../03_Task/08_Cur/Src/Cur15_NotchFilter.obj \
../03_Task/08_Cur/Src/Cur18_WeakMagneticControl.obj \
../03_Task/08_Cur/Src/Cur19_PhaseCompGainCnt.obj \
../03_Task/08_Cur/Src/Cur22_FrictionComp.obj \
../03_Task/08_Cur/Src/Mot34_TuningLess.obj \
../03_Task/08_Cur/Src/Spd15_Estimate.obj \
../03_Task/08_Cur/Src/Spd16_LoadObserver.obj 

C_SRCS += \
../03_Task/08_Cur/Src/Cur00_Main.c \
../03_Task/08_Cur/Src/Cur01_TorqCtrl.c \
../03_Task/08_Cur/Src/Cur02_CurCmd.c \
../03_Task/08_Cur/Src/Cur03_CurSamp.c \
../03_Task/08_Cur/Src/Cur05_CurPID.c \
../03_Task/08_Cur/Src/Cur06_MotorDecoup.c \
../03_Task/08_Cur/Src/Cur09_MotorPhase.c \
../03_Task/08_Cur/Src/Cur10_TorqFilter.c \
../03_Task/08_Cur/Src/Cur12_TorqRefOut.c \
../03_Task/08_Cur/Src/Cur13_OverTorq.c \
../03_Task/08_Cur/Src/Cur14_ZeroPhase.c \
../03_Task/08_Cur/Src/Cur16_TrqLimit.c \
../03_Task/08_Cur/Src/Cur17_OLMonitor.c \
../03_Task/08_Cur/Src/Cur21_VF.c 

C_DEPS += \
./03_Task/08_Cur/Src/Cur00_Main.d \
./03_Task/08_Cur/Src/Cur01_TorqCtrl.d \
./03_Task/08_Cur/Src/Cur02_CurCmd.d \
./03_Task/08_Cur/Src/Cur03_CurSamp.d \
./03_Task/08_Cur/Src/Cur05_CurPID.d \
./03_Task/08_Cur/Src/Cur06_MotorDecoup.d \
./03_Task/08_Cur/Src/Cur09_MotorPhase.d \
./03_Task/08_Cur/Src/Cur10_TorqFilter.d \
./03_Task/08_Cur/Src/Cur12_TorqRefOut.d \
./03_Task/08_Cur/Src/Cur13_OverTorq.d \
./03_Task/08_Cur/Src/Cur14_ZeroPhase.d \
./03_Task/08_Cur/Src/Cur16_TrqLimit.d \
./03_Task/08_Cur/Src/Cur17_OLMonitor.d \
./03_Task/08_Cur/Src/Cur21_VF.d 

OBJS += \
./03_Task/08_Cur/Src/Cur00_Main.obj \
./03_Task/08_Cur/Src/Cur01_TorqCtrl.obj \
./03_Task/08_Cur/Src/Cur02_CurCmd.obj \
./03_Task/08_Cur/Src/Cur03_CurSamp.obj \
./03_Task/08_Cur/Src/Cur05_CurPID.obj \
./03_Task/08_Cur/Src/Cur06_MotorDecoup.obj \
./03_Task/08_Cur/Src/Cur09_MotorPhase.obj \
./03_Task/08_Cur/Src/Cur10_TorqFilter.obj \
./03_Task/08_Cur/Src/Cur12_TorqRefOut.obj \
./03_Task/08_Cur/Src/Cur13_OverTorq.obj \
./03_Task/08_Cur/Src/Cur14_ZeroPhase.obj \
./03_Task/08_Cur/Src/Cur16_TrqLimit.obj \
./03_Task/08_Cur/Src/Cur17_OLMonitor.obj \
./03_Task/08_Cur/Src/Cur21_VF.obj 

OBJS__QUOTED += \
"03_Task\08_Cur\Src\Cur00_Main.obj" \
"03_Task\08_Cur\Src\Cur01_TorqCtrl.obj" \
"03_Task\08_Cur\Src\Cur02_CurCmd.obj" \
"03_Task\08_Cur\Src\Cur03_CurSamp.obj" \
"03_Task\08_Cur\Src\Cur05_CurPID.obj" \
"03_Task\08_Cur\Src\Cur06_MotorDecoup.obj" \
"03_Task\08_Cur\Src\Cur09_MotorPhase.obj" \
"03_Task\08_Cur\Src\Cur10_TorqFilter.obj" \
"03_Task\08_Cur\Src\Cur12_TorqRefOut.obj" \
"03_Task\08_Cur\Src\Cur13_OverTorq.obj" \
"03_Task\08_Cur\Src\Cur14_ZeroPhase.obj" \
"03_Task\08_Cur\Src\Cur16_TrqLimit.obj" \
"03_Task\08_Cur\Src\Cur17_OLMonitor.obj" \
"03_Task\08_Cur\Src\Cur21_VF.obj" 

C_DEPS__QUOTED += \
"03_Task\08_Cur\Src\Cur00_Main.d" \
"03_Task\08_Cur\Src\Cur01_TorqCtrl.d" \
"03_Task\08_Cur\Src\Cur02_CurCmd.d" \
"03_Task\08_Cur\Src\Cur03_CurSamp.d" \
"03_Task\08_Cur\Src\Cur05_CurPID.d" \
"03_Task\08_Cur\Src\Cur06_MotorDecoup.d" \
"03_Task\08_Cur\Src\Cur09_MotorPhase.d" \
"03_Task\08_Cur\Src\Cur10_TorqFilter.d" \
"03_Task\08_Cur\Src\Cur12_TorqRefOut.d" \
"03_Task\08_Cur\Src\Cur13_OverTorq.d" \
"03_Task\08_Cur\Src\Cur14_ZeroPhase.d" \
"03_Task\08_Cur\Src\Cur16_TrqLimit.d" \
"03_Task\08_Cur\Src\Cur17_OLMonitor.d" \
"03_Task\08_Cur\Src\Cur21_VF.d" 

C_SRCS__QUOTED += \
"../03_Task/08_Cur/Src/Cur00_Main.c" \
"../03_Task/08_Cur/Src/Cur01_TorqCtrl.c" \
"../03_Task/08_Cur/Src/Cur02_CurCmd.c" \
"../03_Task/08_Cur/Src/Cur03_CurSamp.c" \
"../03_Task/08_Cur/Src/Cur05_CurPID.c" \
"../03_Task/08_Cur/Src/Cur06_MotorDecoup.c" \
"../03_Task/08_Cur/Src/Cur09_MotorPhase.c" \
"../03_Task/08_Cur/Src/Cur10_TorqFilter.c" \
"../03_Task/08_Cur/Src/Cur12_TorqRefOut.c" \
"../03_Task/08_Cur/Src/Cur13_OverTorq.c" \
"../03_Task/08_Cur/Src/Cur14_ZeroPhase.c" \
"../03_Task/08_Cur/Src/Cur16_TrqLimit.c" \
"../03_Task/08_Cur/Src/Cur17_OLMonitor.c" \
"../03_Task/08_Cur/Src/Cur21_VF.c" 


