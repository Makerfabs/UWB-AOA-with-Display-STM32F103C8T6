################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ExampleDM/config_options.c \
../ExampleDM/ds_twr_responder.c \
../ExampleDM/ds_twr_sts_sdc_initiator.c 

OBJS += \
./ExampleDM/config_options.o \
./ExampleDM/ds_twr_responder.o \
./ExampleDM/ds_twr_sts_sdc_initiator.o 

C_DEPS += \
./ExampleDM/config_options.d \
./ExampleDM/ds_twr_responder.d \
./ExampleDM/ds_twr_sts_sdc_initiator.d 


# Each subdirectory must supply rules for building sources it contributes
ExampleDM/%.o ExampleDM/%.su ExampleDM/%.cyclo: ../ExampleDM/%.c ExampleDM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/22988/Desktop/标签/CubeIde/projectT/ExampleDM" -I"C:/Users/22988/Desktop/标签/CubeIde/projectT/TWR" -I"C:/Users/22988/Desktop/标签/CubeIde/projectT/OSAL" -I"C:/Users/22988/Desktop/标签/CubeIde/projectT/OLED" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu11 -fexec-charset=GBK -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ExampleDM

clean-ExampleDM:
	-$(RM) ./ExampleDM/config_options.cyclo ./ExampleDM/config_options.d ./ExampleDM/config_options.o ./ExampleDM/config_options.su ./ExampleDM/ds_twr_responder.cyclo ./ExampleDM/ds_twr_responder.d ./ExampleDM/ds_twr_responder.o ./ExampleDM/ds_twr_responder.su ./ExampleDM/ds_twr_sts_sdc_initiator.cyclo ./ExampleDM/ds_twr_sts_sdc_initiator.d ./ExampleDM/ds_twr_sts_sdc_initiator.o ./ExampleDM/ds_twr_sts_sdc_initiator.su

.PHONY: clean-ExampleDM

