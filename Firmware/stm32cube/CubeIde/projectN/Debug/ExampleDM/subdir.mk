################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ExampleDM/config_options.c \
../ExampleDM/ds_twr_sts_sdc_responder.c \
../ExampleDM/example_selection.c \
../ExampleDM/otp_write.c \
../ExampleDM/shared_functions.c 

OBJS += \
./ExampleDM/config_options.o \
./ExampleDM/ds_twr_sts_sdc_responder.o \
./ExampleDM/example_selection.o \
./ExampleDM/otp_write.o \
./ExampleDM/shared_functions.o 

C_DEPS += \
./ExampleDM/config_options.d \
./ExampleDM/ds_twr_sts_sdc_responder.d \
./ExampleDM/example_selection.d \
./ExampleDM/otp_write.d \
./ExampleDM/shared_functions.d 


# Each subdirectory must supply rules for building sources it contributes
ExampleDM/%.o ExampleDM/%.su ExampleDM/%.cyclo: ../ExampleDM/%.c ExampleDM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/22988/Desktop/CubeIde/project/ExampleDM" -I"C:/Users/22988/Desktop/CubeIde/project/TWR" -I"C:/Users/22988/Desktop/CubeIde/project/OSAL" -I"C:/Users/22988/Desktop/CubeIde/project/OLED" -I"C:/Users/22988/Desktop/CubeIde/project/APP" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu11 -fexec-charset=GBK -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ExampleDM

clean-ExampleDM:
	-$(RM) ./ExampleDM/config_options.cyclo ./ExampleDM/config_options.d ./ExampleDM/config_options.o ./ExampleDM/config_options.su ./ExampleDM/ds_twr_sts_sdc_responder.cyclo ./ExampleDM/ds_twr_sts_sdc_responder.d ./ExampleDM/ds_twr_sts_sdc_responder.o ./ExampleDM/ds_twr_sts_sdc_responder.su ./ExampleDM/example_selection.cyclo ./ExampleDM/example_selection.d ./ExampleDM/example_selection.o ./ExampleDM/example_selection.su ./ExampleDM/otp_write.cyclo ./ExampleDM/otp_write.d ./ExampleDM/otp_write.o ./ExampleDM/otp_write.su ./ExampleDM/shared_functions.cyclo ./ExampleDM/shared_functions.d ./ExampleDM/shared_functions.o ./ExampleDM/shared_functions.su

.PHONY: clean-ExampleDM

