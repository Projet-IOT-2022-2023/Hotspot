################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sigfox/Target/mcu_api.c \
../Sigfox/Target/mn_api.c \
../Sigfox/Target/radio_board_if.c \
../Sigfox/Target/rf_api.c \
../Sigfox/Target/se_nvm.c \
../Sigfox/Target/sgfx_credentials.c 

C_DEPS += \
./Sigfox/Target/mcu_api.d \
./Sigfox/Target/mn_api.d \
./Sigfox/Target/radio_board_if.d \
./Sigfox/Target/rf_api.d \
./Sigfox/Target/se_nvm.d \
./Sigfox/Target/sgfx_credentials.d 

OBJS += \
./Sigfox/Target/mcu_api.o \
./Sigfox/Target/mn_api.o \
./Sigfox/Target/radio_board_if.o \
./Sigfox/Target/rf_api.o \
./Sigfox/Target/se_nvm.o \
./Sigfox/Target/sgfx_credentials.o 


# Each subdirectory must supply rules for building sources it contributes
Sigfox/Target/%.o Sigfox/Target/%.su: ../Sigfox/Target/%.c Sigfox/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/SubGHz_Phy -I../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../Sigfox/App -I../Sigfox/Target -I../Middlewares/Third_Party/Sigfox/Crypto -I../Middlewares/Third_Party/Sigfox/Monarch -I../Middlewares/Third_Party/Sigfox/SigfoxLib -I../Middlewares/Third_Party/Sigfox/SigfoxLibTest -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Sigfox-2f-Target

clean-Sigfox-2f-Target:
	-$(RM) ./Sigfox/Target/mcu_api.d ./Sigfox/Target/mcu_api.o ./Sigfox/Target/mcu_api.su ./Sigfox/Target/mn_api.d ./Sigfox/Target/mn_api.o ./Sigfox/Target/mn_api.su ./Sigfox/Target/radio_board_if.d ./Sigfox/Target/radio_board_if.o ./Sigfox/Target/radio_board_if.su ./Sigfox/Target/rf_api.d ./Sigfox/Target/rf_api.o ./Sigfox/Target/rf_api.su ./Sigfox/Target/se_nvm.d ./Sigfox/Target/se_nvm.o ./Sigfox/Target/se_nvm.su ./Sigfox/Target/sgfx_credentials.d ./Sigfox/Target/sgfx_credentials.o ./Sigfox/Target/sgfx_credentials.su

.PHONY: clean-Sigfox-2f-Target

