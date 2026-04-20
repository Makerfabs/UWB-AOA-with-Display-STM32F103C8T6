################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../example/ds_twr_initiator.c \
../example/ds_twr_responder.c \
../example/example_selection.c \
../example/otp_write.c \
../example/read_dev_id.c \
../example/rx_send_resp.c \
../example/shared_functions.c \
../example/simple_rx.c \
../example/simple_rx_pdoa.c \
../example/simple_tx.c \
../example/simple_tx_pdoa.c \
../example/tx_timed_sleep.c \
../example/tx_wait_resp.c \
../example/tx_wait_resp_int.c 

OBJS += \
./example/ds_twr_initiator.o \
./example/ds_twr_responder.o \
./example/example_selection.o \
./example/otp_write.o \
./example/read_dev_id.o \
./example/rx_send_resp.o \
./example/shared_functions.o \
./example/simple_rx.o \
./example/simple_rx_pdoa.o \
./example/simple_tx.o \
./example/simple_tx_pdoa.o \
./example/tx_timed_sleep.o \
./example/tx_wait_resp.o \
./example/tx_wait_resp_int.o 

C_DEPS += \
./example/ds_twr_initiator.d \
./example/ds_twr_responder.d \
./example/example_selection.d \
./example/otp_write.d \
./example/read_dev_id.d \
./example/rx_send_resp.d \
./example/shared_functions.d \
./example/simple_rx.d \
./example/simple_rx_pdoa.d \
./example/simple_tx.d \
./example/simple_tx_pdoa.d \
./example/tx_timed_sleep.d \
./example/tx_wait_resp.d \
./example/tx_wait_resp_int.d 


# Each subdirectory must supply rules for building sources it contributes
example/%.o example/%.su example/%.cyclo: ../example/%.c example/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"E:/Users/22988/STM32CubeIDE/workspace_1.19.0/led_demo/TWR" -I"E:/Users/22988/STM32CubeIDE/workspace_1.19.0/led_demo/OSAL" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu11 -fexec-charset=GBK -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-example

clean-example:
	-$(RM) ./example/ds_twr_initiator.cyclo ./example/ds_twr_initiator.d ./example/ds_twr_initiator.o ./example/ds_twr_initiator.su ./example/ds_twr_responder.cyclo ./example/ds_twr_responder.d ./example/ds_twr_responder.o ./example/ds_twr_responder.su ./example/example_selection.cyclo ./example/example_selection.d ./example/example_selection.o ./example/example_selection.su ./example/otp_write.cyclo ./example/otp_write.d ./example/otp_write.o ./example/otp_write.su ./example/read_dev_id.cyclo ./example/read_dev_id.d ./example/read_dev_id.o ./example/read_dev_id.su ./example/rx_send_resp.cyclo ./example/rx_send_resp.d ./example/rx_send_resp.o ./example/rx_send_resp.su ./example/shared_functions.cyclo ./example/shared_functions.d ./example/shared_functions.o ./example/shared_functions.su ./example/simple_rx.cyclo ./example/simple_rx.d ./example/simple_rx.o ./example/simple_rx.su ./example/simple_rx_pdoa.cyclo ./example/simple_rx_pdoa.d ./example/simple_rx_pdoa.o ./example/simple_rx_pdoa.su ./example/simple_tx.cyclo ./example/simple_tx.d ./example/simple_tx.o ./example/simple_tx.su ./example/simple_tx_pdoa.cyclo ./example/simple_tx_pdoa.d ./example/simple_tx_pdoa.o ./example/simple_tx_pdoa.su ./example/tx_timed_sleep.cyclo ./example/tx_timed_sleep.d ./example/tx_timed_sleep.o ./example/tx_timed_sleep.su ./example/tx_wait_resp.cyclo ./example/tx_wait_resp.d ./example/tx_wait_resp.o ./example/tx_wait_resp.su ./example/tx_wait_resp_int.cyclo ./example/tx_wait_resp_int.d ./example/tx_wait_resp_int.o ./example/tx_wait_resp_int.su

.PHONY: clean-example

