################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/Sigfox/Crypto/sigfox_aes.c \
../Middlewares/Third_Party/Sigfox/Crypto/sigfox_data.c 

C_DEPS += \
./Middlewares/Third_Party/Sigfox/Crypto/sigfox_aes.d \
./Middlewares/Third_Party/Sigfox/Crypto/sigfox_data.d 

OBJS += \
./Middlewares/Third_Party/Sigfox/Crypto/sigfox_aes.o \
./Middlewares/Third_Party/Sigfox/Crypto/sigfox_data.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/Sigfox/Crypto/%.o Middlewares/Third_Party/Sigfox/Crypto/%.su: ../Middlewares/Third_Party/Sigfox/Crypto/%.c Middlewares/Third_Party/Sigfox/Crypto/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/SubGHz_Phy -I../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../Sigfox/App -I../Sigfox/Target -I../Middlewares/Third_Party/Sigfox/Crypto -I../Middlewares/Third_Party/Sigfox/Monarch -I../Middlewares/Third_Party/Sigfox/SigfoxLib -I../Middlewares/Third_Party/Sigfox/SigfoxLibTest -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-Sigfox-2f-Crypto

clean-Middlewares-2f-Third_Party-2f-Sigfox-2f-Crypto:
	-$(RM) ./Middlewares/Third_Party/Sigfox/Crypto/sigfox_aes.d ./Middlewares/Third_Party/Sigfox/Crypto/sigfox_aes.o ./Middlewares/Third_Party/Sigfox/Crypto/sigfox_aes.su ./Middlewares/Third_Party/Sigfox/Crypto/sigfox_data.d ./Middlewares/Third_Party/Sigfox/Crypto/sigfox_data.o ./Middlewares/Third_Party/Sigfox/Crypto/sigfox_data.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-Sigfox-2f-Crypto

