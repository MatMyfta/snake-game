################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1011/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./field.o" \
"./graphics.o" \
"./main.o" \
"./snake.o" \
"./system_msp432p401r.o" \
"./LcdDriver/Crystalfontz128x128_ST7735.o" \
"./LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.o" \
"./gcc/startup_msp432p401r_gcc.o" \
-Wl,-T"../msp432p401r.lds" \
$(GEN_CMDS__FLAG) \
"C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/driverlib/ccs/msp432p4xx_driverlib.lib" \
-l:grlib.a \
-l:arm_cortexM4lf_math.a \
-l:"ti/display/lib/display.am4fg" \
-l:"ti/grlib/lib/gcc/m4f/grlib.a" \
-l:"third_party/spiffs/lib/gcc/m4f/spiffs.a" \
-l:"ti/drivers/lib/drivers_msp432p401x.am4fg" \
-l:"third_party/fatfs/lib/gcc/m4f/fatfs.a" \
-l:"ti/devices/msp432p4xx/driverlib/gcc/msp432p4xx_driverlib.a" \
-lgcc \
-lc \
-lm \
-lnosys \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include LcdDriver/subdir_vars.mk
-include gcc/subdir_vars.mk
-include subdir_rules.mk
-include LcdDriver/subdir_rules.mk
-include gcc/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
snake_proj.out \

EXE_OUTPUTS__QUOTED += \
"snake_proj.out" \

BIN_OUTPUTS += \
snake_proj.hex \

BIN_OUTPUTS__QUOTED += \
"snake_proj.hex" \


# All Target
all: $(OBJS) $(LDS_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "snake_proj.out"

# Tool invocations
snake_proj.out: $(OBJS) $(LDS_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: GNU Linker'
	"C:/ti/ccs1011/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-gcc-9.2.1.exe" -mfpu=fpv4-sp-d16 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -D__MSP432P401R__ -DDeviceFamily_MSP432P401x -ffunction-sections -fdata-sections -g -gdwarf-3 -gstrict-dwarf -Wall -mcpu=cortex-m4 -Wl,-Map,"snake_proj.map" -static -Wl,--gc-sections -L"C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source" -L"C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/grlib/lib/gcc/m4f" -L"C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/DSP_Lib/lib/gcc/m4f" -L"C:/ti/simplelink_msp432p4_sdk_3_40_01_02/source" -L"C:/ti/ccs1011/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/arm-none-eabi/lib/thumb/v7e-m/fpv4-sp/hard" -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nano.specs -o"snake_proj.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

snake_proj.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: GNU Objcopy Utility'
	"C:/ti/ccs1011/ccs/tools/compiler/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-objcopy.exe"  $(EXE_OUTPUTS__QUOTED) "snake_proj.hex"
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "field.o" "graphics.o" "main.o" "snake.o" "system_msp432p401r.o" "LcdDriver\Crystalfontz128x128_ST7735.o" "LcdDriver\HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.o" "gcc\startup_msp432p401r_gcc.o" 
	-$(RM) "field.d" "graphics.d" "main.d" "snake.d" "system_msp432p401r.d" "LcdDriver\Crystalfontz128x128_ST7735.d" "LcdDriver\HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.d" "gcc\startup_msp432p401r_gcc.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

