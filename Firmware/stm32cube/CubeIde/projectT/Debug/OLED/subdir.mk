################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../OLED/OLED_I2C.c 

OBJS += \
./OLED/OLED_I2C.o 

C_DEPS += \
./OLED/OLED_I2C.d 


# Each subdirectory must supply rules for building sources it contributes
OLED/%.o OLED/%.su OLED/%.cyclo: ../OLED/%.c OLED/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/OSAL" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/OLED" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/APP" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/HAL" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/DW/Driver" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/DW/Examples" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/DW/PDoA" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/HAL/DW" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/HAL/DW/dw_twr" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/HAL/DW/dw_twr/examples" -O3 -ffunction-sections -fdata-sections -Wall -std=gnu11 -fexec-charset=GBK -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-OLED

clean-OLED:
	-$(RM) ./OLED/OLED_I2C.cyclo ./OLED/OLED_I2C.d ./OLED/OLED_I2C.o ./OLED/OLED_I2C.su

.PHONY: clean-OLED

