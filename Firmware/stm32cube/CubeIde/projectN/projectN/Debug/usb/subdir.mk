################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usb/Queue.c \
../usb/hw_config.c \
../usb/usb_desc.c \
../usb/usb_endp.c \
../usb/usb_istr.c \
../usb/usb_it.c \
../usb/usb_prop.c \
../usb/usb_pwr.c 

OBJS += \
./usb/Queue.o \
./usb/hw_config.o \
./usb/usb_desc.o \
./usb/usb_endp.o \
./usb/usb_istr.o \
./usb/usb_it.o \
./usb/usb_prop.o \
./usb/usb_pwr.o 

C_DEPS += \
./usb/Queue.d \
./usb/hw_config.d \
./usb/usb_desc.d \
./usb/usb_endp.d \
./usb/usb_istr.d \
./usb/usb_it.d \
./usb/usb_prop.d \
./usb/usb_pwr.d 


# Each subdirectory must supply rules for building sources it contributes
usb/%.o usb/%.su usb/%.cyclo: ../usb/%.c usb/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/22988/Desktop/CubeIde/project/OSAL" -I"C:/Users/22988/Desktop/CubeIde/project/OLED" -I"C:/Users/22988/Desktop/CubeIde/project/APP" -I"C:/Users/22988/Desktop/CubeIde/project/HAL" -I"C:/Users/22988/Desktop/CubeIde/project/DW/Driver" -I"C:/Users/22988/Desktop/CubeIde/project/DW/Examples" -I"C:/Users/22988/Desktop/CubeIde/project/DW/PDoA" -I"C:/Users/22988/Desktop/CubeIde/project/HAL/DW" -I"C:/Users/22988/Desktop/CubeIde/project/HAL/DW/dw_twe" -I"C:/Users/22988/Desktop/CubeIde/project/HAL/DW/dw_twe/examples" -I"C:/Users/22988/Desktop/CubeIde/project/usb" -I"C:/Users/22988/Desktop/CubeIde/project/usb/lib" -I"C:/Users/22988/Desktop/CubeIde/project/HAL/USB" -Os -ffunction-sections -fdata-sections -Wall -std=gnu11 -fexec-charset=GBK -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-usb

clean-usb:
	-$(RM) ./usb/Queue.cyclo ./usb/Queue.d ./usb/Queue.o ./usb/Queue.su ./usb/hw_config.cyclo ./usb/hw_config.d ./usb/hw_config.o ./usb/hw_config.su ./usb/usb_desc.cyclo ./usb/usb_desc.d ./usb/usb_desc.o ./usb/usb_desc.su ./usb/usb_endp.cyclo ./usb/usb_endp.d ./usb/usb_endp.o ./usb/usb_endp.su ./usb/usb_istr.cyclo ./usb/usb_istr.d ./usb/usb_istr.o ./usb/usb_istr.su ./usb/usb_it.cyclo ./usb/usb_it.d ./usb/usb_it.o ./usb/usb_it.su ./usb/usb_prop.cyclo ./usb/usb_prop.d ./usb/usb_prop.o ./usb/usb_prop.su ./usb/usb_pwr.cyclo ./usb/usb_pwr.d ./usb/usb_pwr.o ./usb/usb_pwr.su

.PHONY: clean-usb

