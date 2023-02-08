################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sigfox/App/app_sigfox.c \
../Sigfox/App/sgfx_app.c 

C_DEPS += \
./Sigfox/App/app_sigfox.d \
./Sigfox/App/sgfx_app.d 

OBJS += \
./Sigfox/App/app_sigfox.o \
./Sigfox/App/sgfx_app.o 


# Each subdirectory must supply rules for building sources it contributes
Sigfox/App/%.o Sigfox/App/%.su: ../Sigfox/App/%.c Sigfox/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -I../Utilities/trace/adv_trace -I../Utilities/misc -I../Utilities/sequencer -I../Utilities/timer -I../Utilities/lpm/tiny_lpm -I../Middlewares/Third_Party/SubGHz_Phy -I../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../Sigfox/App -I../Sigfox/Target -I../Middlewares/Third_Party/Sigfox/Crypto -I../Middlewares/Third_Party/Sigfox/Monarch -I../Middlewares/Third_Party/Sigfox/SigfoxLib -I../Middlewares/Third_Party/Sigfox/SigfoxLibTest -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Sigfox-2f-App

clean-Sigfox-2f-App:
	-$(RM) ./Sigfox/App/app_sigfox.d ./Sigfox/App/app_sigfox.o ./Sigfox/App/app_sigfox.su ./Sigfox/App/sgfx_app.d ./Sigfox/App/sgfx_app.o ./Sigfox/App/sgfx_app.su

.PHONY: clean-Sigfox-2f-App

