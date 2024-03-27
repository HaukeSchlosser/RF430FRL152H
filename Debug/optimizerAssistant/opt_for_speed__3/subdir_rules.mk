################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-msp430_20.2.4.LTS/bin/cl430" -vmsp -O3 --opt_for_speed=3 --use_hw_mpy=none --include_path="C:/ti/ccs1011/ccs/ccs_base/msp430/include" --include_path="C:/Users/HBHugo/workspace_v10/Blink_LED" --include_path="C:/ti/ccs1011/ccs/tools/compiler/ti-cgt-msp430_20.2.4.LTS/include" --advice:power=all --define=__RF430FRL152H__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


