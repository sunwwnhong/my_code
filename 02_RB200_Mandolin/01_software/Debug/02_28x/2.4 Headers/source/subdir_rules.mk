################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
02_28x/2.4\ Headers/source/f28p65x_globalvariabledefs.obj: ../02_28x/2.4\ Headers/source/f28p65x_globalvariabledefs.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --tmu_support=tmu1 --vcu_support=vcrc -O4 --opt_for_speed=5 --fp_mode=relaxed --include_path="C:/Users/V4962/Desktop/02_RB200_Mandolin_20260403/02_RB200_Mandolin/01_software" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="C:/Users/V4962/Desktop/02_RB200_Mandolin_20260403/02_RB200_Mandolin/01_software/02_28x/2.2 Device/Inc" --include_path="C:/Users/V4962/Desktop/02_RB200_Mandolin_20260403/02_RB200_Mandolin/01_software/02_28x/2.2 Device/Inc/inc" --include_path="C:/Users/V4962/Desktop/02_RB200_Mandolin_20260403/02_RB200_Mandolin/01_software/02_28x/2.3 Common/Inc" --include_path="C:/Users/V4962/Desktop/02_RB200_Mandolin_20260403/02_RB200_Mandolin/01_software/02_28x/2.4 Headers/include" --include_path="C:/Users/V4962/Desktop/02_RB200_Mandolin_20260403/02_RB200_Mandolin/01_software/03_Task/01_App/Inc" --include_path="C:/Users/V4962/Desktop/02_RB200_Mandolin_20260403/02_RB200_Mandolin/01_software/03_Task/02_User/Inc" --include_path="C:/Users/V4962/Desktop/02_RB200_Mandolin_20260403/02_RB200_Mandolin/01_software/03_Task/06_FPGA/Inc" --include_path="C:/Users/V4962/Desktop/02_RB200_Mandolin_20260403/02_RB200_Mandolin/01_software/03_Task/11_EtherCAT/Inc" --include_path="C:/Users/V4962/Desktop/02_RB200_Mandolin_20260403/02_RB200_Mandolin/01_software/03_Task/12_USB/Inc" --advice:performance=all --define=ccs_c2k --define=MotA_En --define=_F2838X --define=ETHERCAT_STACK --define=CPU1 --define=CPU2_En -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="02_28x/2.4 Headers/source/f28p65x_globalvariabledefs.d_raw" --obj_directory="02_28x/2.4 Headers/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


