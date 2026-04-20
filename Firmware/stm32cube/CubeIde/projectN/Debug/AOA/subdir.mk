################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../AOA/deca_mutex.c \
../AOA/ds_twr_sts_sdc_responder.c \
../AOA/json_2pc.c \
../AOA/tag_list.c \
../AOA/uwb.c 

OBJS += \
./AOA/deca_mutex.o \
./AOA/ds_twr_sts_sdc_responder.o \
./AOA/json_2pc.o \
./AOA/tag_list.o \
./AOA/uwb.o 

C_DEPS += \
./AOA/deca_mutex.d \
./AOA/ds_twr_sts_sdc_responder.d \
./AOA/json_2pc.d \
./AOA/tag_list.d \
./AOA/uwb.d 


# Each subdirectory must supply rules for building sources it contributes
AOA/%.o AOA/%.su AOA/%.cyclo: ../AOA/%.c AOA/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/22988/Desktop/CubeIde/project/OSAL" -I"C:/Users/22988/Desktop/CubeIde/project/OLED" -I"C:/Users/22988/Desktop/CubeIde/project/APP" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu11 -fexec-charset=GBK -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-AOA

clean-AOA:
	-$(RM) ./AOA/deca_mutex.cyclo ./AOA/deca_mutex.d ./AOA/deca_mutex.o ./AOA/deca_mutex.su ./AOA/ds_twr_sts_sdc_responder.cyclo ./AOA/ds_twr_sts_sdc_responder.d ./AOA/ds_twr_sts_sdc_responder.o ./AOA/ds_twr_sts_sdc_responder.su ./AOA/json_2pc.cyclo ./AOA/json_2pc.d ./AOA/json_2pc.o ./AOA/json_2pc.su ./AOA/tag_list.cyclo ./AOA/tag_list.d ./AOA/tag_list.o ./AOA/tag_list.su ./AOA/uwb.cyclo ./AOA/uwb.d ./AOA/uwb.o ./AOA/uwb.su

.PHONY: clean-AOA

