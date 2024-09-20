################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripherals/Src/fonts.c \
../Peripherals/Src/gpio.c \
../Peripherals/Src/rcc.c \
../Peripherals/Src/ssd1306_hardware.c \
../Peripherals/Src/ssd1306_middle.c \
../Peripherals/Src/vl6180x_hardware.c \
../Peripherals/Src/vl6180x_middle.c 

OBJS += \
./Peripherals/Src/fonts.o \
./Peripherals/Src/gpio.o \
./Peripherals/Src/rcc.o \
./Peripherals/Src/ssd1306_hardware.o \
./Peripherals/Src/ssd1306_middle.o \
./Peripherals/Src/vl6180x_hardware.o \
./Peripherals/Src/vl6180x_middle.o 

C_DEPS += \
./Peripherals/Src/fonts.d \
./Peripherals/Src/gpio.d \
./Peripherals/Src/rcc.d \
./Peripherals/Src/ssd1306_hardware.d \
./Peripherals/Src/ssd1306_middle.d \
./Peripherals/Src/vl6180x_hardware.d \
./Peripherals/Src/vl6180x_middle.d 


# Each subdirectory must supply rules for building sources it contributes
Peripherals/Src/%.o Peripherals/Src/%.su: ../Peripherals/Src/%.c Peripherals/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/temporary workspace/STM32CUBEIDE/Summer 2024/vl6180x and ssf1306/Peripherals/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Peripherals-2f-Src

clean-Peripherals-2f-Src:
	-$(RM) ./Peripherals/Src/fonts.d ./Peripherals/Src/fonts.o ./Peripherals/Src/fonts.su ./Peripherals/Src/gpio.d ./Peripherals/Src/gpio.o ./Peripherals/Src/gpio.su ./Peripherals/Src/rcc.d ./Peripherals/Src/rcc.o ./Peripherals/Src/rcc.su ./Peripherals/Src/ssd1306_hardware.d ./Peripherals/Src/ssd1306_hardware.o ./Peripherals/Src/ssd1306_hardware.su ./Peripherals/Src/ssd1306_middle.d ./Peripherals/Src/ssd1306_middle.o ./Peripherals/Src/ssd1306_middle.su ./Peripherals/Src/vl6180x_hardware.d ./Peripherals/Src/vl6180x_hardware.o ./Peripherals/Src/vl6180x_hardware.su ./Peripherals/Src/vl6180x_middle.d ./Peripherals/Src/vl6180x_middle.o ./Peripherals/Src/vl6180x_middle.su

.PHONY: clean-Peripherals-2f-Src

