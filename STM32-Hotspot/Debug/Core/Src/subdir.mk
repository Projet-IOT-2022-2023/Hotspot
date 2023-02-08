################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Anemometer.c \
../Core/Src/CAda.c \
../Core/Src/RTCLib.c \
../Core/Src/bme680.c \
../Core/Src/bme680Interface.c \
../Core/Src/main.c \
../Core/Src/rn2483.c \
../Core/Src/stm32wlxx_hal_msp.c \
../Core/Src/stm32wlxx_hal_timebase_tim.c \
../Core/Src/stm32wlxx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32wlxx.c 

CPP_SRCS += \
../Core/Src/MLX90640_API.cpp \
../Core/Src/MLX90640_I2C_Driver.cpp 

C_DEPS += \
./Core/Src/Anemometer.d \
./Core/Src/CAda.d \
./Core/Src/RTCLib.d \
./Core/Src/bme680.d \
./Core/Src/bme680Interface.d \
./Core/Src/main.d \
./Core/Src/rn2483.d \
./Core/Src/stm32wlxx_hal_msp.d \
./Core/Src/stm32wlxx_hal_timebase_tim.d \
./Core/Src/stm32wlxx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32wlxx.d 

OBJS += \
./Core/Src/Anemometer.o \
./Core/Src/CAda.o \
./Core/Src/MLX90640_API.o \
./Core/Src/MLX90640_I2C_Driver.o \
./Core/Src/RTCLib.o \
./Core/Src/bme680.o \
./Core/Src/bme680Interface.o \
./Core/Src/main.o \
./Core/Src/rn2483.o \
./Core/Src/stm32wlxx_hal_msp.o \
./Core/Src/stm32wlxx_hal_timebase_tim.o \
./Core/Src/stm32wlxx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32wlxx.o 

CPP_DEPS += \
./Core/Src/MLX90640_API.d \
./Core/Src/MLX90640_I2C_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WLE5xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Anemometer.d ./Core/Src/Anemometer.o ./Core/Src/Anemometer.su ./Core/Src/CAda.d ./Core/Src/CAda.o ./Core/Src/CAda.su ./Core/Src/MLX90640_API.d ./Core/Src/MLX90640_API.o ./Core/Src/MLX90640_API.su ./Core/Src/MLX90640_I2C_Driver.d ./Core/Src/MLX90640_I2C_Driver.o ./Core/Src/MLX90640_I2C_Driver.su ./Core/Src/RTCLib.d ./Core/Src/RTCLib.o ./Core/Src/RTCLib.su ./Core/Src/bme680.d ./Core/Src/bme680.o ./Core/Src/bme680.su ./Core/Src/bme680Interface.d ./Core/Src/bme680Interface.o ./Core/Src/bme680Interface.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/rn2483.d ./Core/Src/rn2483.o ./Core/Src/rn2483.su ./Core/Src/stm32wlxx_hal_msp.d ./Core/Src/stm32wlxx_hal_msp.o ./Core/Src/stm32wlxx_hal_msp.su ./Core/Src/stm32wlxx_hal_timebase_tim.d ./Core/Src/stm32wlxx_hal_timebase_tim.o ./Core/Src/stm32wlxx_hal_timebase_tim.su ./Core/Src/stm32wlxx_it.d ./Core/Src/stm32wlxx_it.o ./Core/Src/stm32wlxx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32wlxx.d ./Core/Src/system_stm32wlxx.o ./Core/Src/system_stm32wlxx.su

.PHONY: clean-Core-2f-Src

