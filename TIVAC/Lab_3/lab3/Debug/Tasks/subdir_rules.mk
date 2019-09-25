################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Tasks/task2b.obj: ../Tasks/task2b.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/Jett/Documents/CPE 403/Tiva_C_Labs/lab3" --include_path="C:/ti/tivaware_c_series_2_1_4_178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GE6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Tasks/task2b.d_raw" --obj_directory="Tasks" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


