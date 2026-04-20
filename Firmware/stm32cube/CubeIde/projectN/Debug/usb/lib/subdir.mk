################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usb/lib/usb_core.c \
../usb/lib/usb_int.c \
../usb/lib/usb_mem.c \
../usb/lib/usb_regs.c \
../usb/lib/usb_sil.c 

OBJS += \
./usb/lib/usb_core.o \
./usb/lib/usb_int.o \
./usb/lib/usb_mem.o \
./usb/lib/usb_regs.o \
./usb/lib/usb_sil.o 

C_DEPS += \
./usb/lib/usb_core.d \
./usb/lib/usb_int.d \
./usb/lib/usb_mem.d \
./usb/lib/usb_regs.d \
./usb/lib/usb_sil.d 


# Each subdirectory must supply rules for building sources it contributes
usb/lib/%.o usb/lib/%.su usb/lib/%.cyclo: ../usb/lib/%.c usb/lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/22988/Desktop/CubeIde/project/OSAL" -I"C:/Users/22988/Desktop/CubeIde/project/OLED" -I"C:/Users/22988/Desktop/CubeIde/project/APP" -I"C:/Users/22988/Desktop/CubeIde/project/HAL" -I"C:/Users/22988/Desktop/CubeIde/project/DW/Driver" -I"C:/Users/22988/Desktop/CubeIde/project/DW/Examples" -I"C:/Users/22988/Desktop/CubeIde/project/DW/PDoA" -I"C:/Users/22988/Desktop/CubeIde/project/HAL/DW" -I"C:/Users/22988/Desktop/CubeIde/project/HAL/DW/dw_twe" -I"C:/Users/22988/Desktop/CubeIde/project/HAL/DW/dw_twe/examples" -I"C:/Users/22988/Desktop/CubeIde/project/usb" -I"C:/Users/22988/Desktop/CubeIde/project/usb/lib" -I"C:/Users/22988/Desktop/CubeIde/project/HAL/USB" -Os -ffunction-sections -fdata-sections -Wall -std=gnu11 -fexec-charset=GBK -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-usb-2f-lib

clean-usb-2f-lib:
	-$(RM) ./usb/lib/usb_core.cyclo ./usb/lib/usb_core.d ./usb/lib/usb_core.o ./usb/lib/usb_core.su ./usb/lib/usb_int.cyclo ./usb/lib/usb_int.d ./usb/lib/usb_int.o ./usb/lib/usb_int.su ./usb/lib/usb_mem.cyclo ./usb/lib/usb_mem.d ./usb/lib/usb_mem.o ./usb/lib/usb_mem.su ./usb/lib/usb_regs.cyclo ./usb/lib/usb_regs.d ./usb/lib/usb_regs.o ./usb/lib/usb_regs.su ./usb/lib/usb_sil.cyclo ./usb/lib/usb_sil.d ./usb/lib/usb_sil.o ./usb/lib/usb_sil.su

.PHONY: clean-usb-2f-lib

