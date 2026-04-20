################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DW/Driver/deca_mutex.c 

OBJS += \
./DW/Driver/deca_mutex.o 

C_DEPS += \
./DW/Driver/deca_mutex.d 


# Each subdirectory must supply rules for building sources it contributes
DW/Driver/%.o DW/Driver/%.su DW/Driver/%.cyclo: ../DW/Driver/%.c DW/Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/project/project/OSAL" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/project/project/OLED" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/project/project/APP" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/project/project/HAL" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/project/project/DW/Driver" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/project/project/DW/Examples" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/project/project/DW/PDoA" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/project/project/HAL/DW" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/project/project/HAL/DW/dw_twe" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/project/project/HAL/DW/dw_twe/examples" -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/project/project/US" -Oz -ffunction-sections -fdata-sections -Wall -std=gnu11 -fexec-charset=GBK -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-DW-2f-Driver

clean-DW-2f-Driver:
	-$(RM) ./DW/Driver/deca_mutex.cyclo ./DW/Driver/deca_mutex.d ./DW/Driver/deca_mutex.o ./DW/Driver/deca_mutex.su

.PHONY: clean-DW-2f-Driver

