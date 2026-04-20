################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TWR/deca_mutex.c \
../TWR/uwb.c 

OBJS += \
./TWR/deca_mutex.o \
./TWR/uwb.o 

C_DEPS += \
./TWR/deca_mutex.d \
./TWR/uwb.d 


# Each subdirectory must supply rules for building sources it contributes
TWR/%.o TWR/%.su TWR/%.cyclo: ../TWR/%.c TWR/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/22988/Desktop/标签/CubeIde/projectT/ExampleDM" -I"C:/Users/22988/Desktop/标签/CubeIde/projectT/TWR" -I"C:/Users/22988/Desktop/标签/CubeIde/projectT/OSAL" -I"C:/Users/22988/Desktop/标签/CubeIde/projectT/OLED" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu11 -fexec-charset=GBK -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-TWR

clean-TWR:
	-$(RM) ./TWR/deca_mutex.cyclo ./TWR/deca_mutex.d ./TWR/deca_mutex.o ./TWR/deca_mutex.su ./TWR/uwb.cyclo ./TWR/uwb.d ./TWR/uwb.o ./TWR/uwb.su

.PHONY: clean-TWR

