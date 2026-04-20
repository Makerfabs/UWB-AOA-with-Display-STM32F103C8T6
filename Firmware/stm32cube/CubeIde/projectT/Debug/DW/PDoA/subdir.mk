################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DW/PDoA/example_info.c \
../DW/PDoA/json_2pc.c \
../DW/PDoA/tag_list.c \
../DW/PDoA/twr_task.c \
../DW/PDoA/uwb.c 

OBJS += \
./DW/PDoA/example_info.o \
./DW/PDoA/json_2pc.o \
./DW/PDoA/tag_list.o \
./DW/PDoA/twr_task.o \
./DW/PDoA/uwb.o 

C_DEPS += \
./DW/PDoA/example_info.d \
./DW/PDoA/json_2pc.d \
./DW/PDoA/tag_list.d \
./DW/PDoA/twr_task.d \
./DW/PDoA/uwb.d 


# Each subdirectory must supply rules for building sources it contributes
DW/PDoA/%.o DW/PDoA/%.su DW/PDoA/%.cyclo: ../DW/PDoA/%.c DW/PDoA/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/OSAL" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/OLED" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/APP" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/HAL" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/DW/Driver" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/DW/Examples" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/DW/PDoA" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/HAL/DW" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/HAL/DW/dw_twr" -I"D:/bobo/File/xwechat_files/wxid_7pcrj0jpswx422_e57e/msg/file/2026-04/CubeT/CubeT/CubeIde/projectT/HAL/DW/dw_twr/examples" -O3 -ffunction-sections -fdata-sections -Wall -std=gnu11 -fexec-charset=GBK -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-DW-2f-PDoA

clean-DW-2f-PDoA:
	-$(RM) ./DW/PDoA/example_info.cyclo ./DW/PDoA/example_info.d ./DW/PDoA/example_info.o ./DW/PDoA/example_info.su ./DW/PDoA/json_2pc.cyclo ./DW/PDoA/json_2pc.d ./DW/PDoA/json_2pc.o ./DW/PDoA/json_2pc.su ./DW/PDoA/tag_list.cyclo ./DW/PDoA/tag_list.d ./DW/PDoA/tag_list.o ./DW/PDoA/tag_list.su ./DW/PDoA/twr_task.cyclo ./DW/PDoA/twr_task.d ./DW/PDoA/twr_task.o ./DW/PDoA/twr_task.su ./DW/PDoA/uwb.cyclo ./DW/PDoA/uwb.d ./DW/PDoA/uwb.o ./DW/PDoA/uwb.su

.PHONY: clean-DW-2f-PDoA

