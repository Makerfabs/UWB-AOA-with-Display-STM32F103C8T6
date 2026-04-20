################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include OSAL/subdir.mk
-include OLED/subdir.mk
-include HAL/DW/dw_twr/subdir.mk
-include HAL/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include DW/PDoA/subdir.mk
-include DW/Examples/subdir.mk
-include DW/Driver/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include APP/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := projectT
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
projectT.elf \

MAP_FILES += \
projectT.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
projectT.list \

OBJCOPY_HEX += \
projectT.hex \


# All Target
all: main-build

# Main-build Target
main-build: projectT.elf secondary-outputs

# Tool invocations
projectT.elf projectT.map: $(OBJS) $(USER_OBJS) D:\bobo\File\xwechat_files\wxid_7pcrj0jpswx422_e57e\msg\file\2026-04\CubeT\CubeT\CubeIde\projectT\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "projectT.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\bobo\File\xwechat_files\wxid_7pcrj0jpswx422_e57e\msg\file\2026-04\CubeT\CubeT\CubeIde\projectT\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="projectT.map" -Wl,--gc-sections -static -L"D:\bobo\File\xwechat_files\wxid_7pcrj0jpswx422_e57e\msg\file\2026-04\CubeT\CubeT\CubeIde\projectT\Core\Src" --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

projectT.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "projectT.list"
	@echo 'Finished building: $@'
	@echo ' '

projectT.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "projectT.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout projectT.elf projectT.hex projectT.list projectT.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
