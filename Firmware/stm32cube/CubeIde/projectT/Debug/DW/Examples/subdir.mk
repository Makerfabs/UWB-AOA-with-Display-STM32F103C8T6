################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DW/Examples/ds_twr_sts_sdc_initiator.c \
../DW/Examples/mac_802_15_4.c \
../DW/Examples/mac_802_15_8.c \
../DW/Examples/shared_functions.c 

OBJS += \
./DW/Examples/ds_twr_sts_sdc_initiator.o \
./DW/Examples/mac_802_15_4.o \
./DW/Examples/mac_802_15_8.o \
./DW/Examples/shared_functions.o 

C_DEPS += \
./DW/Examples/ds_twr_sts_sdc_initiator.d \
./DW/Examples/mac_802_15_4.d \
./DW/Examples/mac_802_15_8.d \
./DW/Examples/shared_functions.d 


# Each subdirectory must supply rules for building sources it contributes
DW/Examples/%.o DW/Examples/%.su DW/Examples/%.cyclo: ../DW/Examples/%.c DW/Examples/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/OSAL" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/OLED" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/APP" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/HAL" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/DW/Driver" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/DW/Examples" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/DW/PDoA" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/HAL/DW" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/HAL/DW/dw_twr" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/HAL/DW/dw_twr/examples" -O3 -ffunction-sections -fdata-sections -Wall -std=gnu11 -fexec-charset=GBK -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-DW-2f-Examples

clean-DW-2f-Examples:
	-$(RM) ./DW/Examples/ds_twr_sts_sdc_initiator.cyclo ./DW/Examples/ds_twr_sts_sdc_initiator.d ./DW/Examples/ds_twr_sts_sdc_initiator.o ./DW/Examples/ds_twr_sts_sdc_initiator.su ./DW/Examples/mac_802_15_4.cyclo ./DW/Examples/mac_802_15_4.d ./DW/Examples/mac_802_15_4.o ./DW/Examples/mac_802_15_4.su ./DW/Examples/mac_802_15_8.cyclo ./DW/Examples/mac_802_15_8.d ./DW/Examples/mac_802_15_8.o ./DW/Examples/mac_802_15_8.su ./DW/Examples/shared_functions.cyclo ./DW/Examples/shared_functions.d ./DW/Examples/shared_functions.o ./DW/Examples/shared_functions.su

.PHONY: clean-DW-2f-Examples

