################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../icm20948/icm_20948.c 

OBJS += \
./icm20948/icm_20948.o 

C_DEPS += \
./icm20948/icm_20948.d 


# Each subdirectory must supply rules for building sources it contributes
icm20948/icm_20948.o: ../icm20948/icm_20948.c icm20948/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mokhw/Desktop/GitHub/stm32f4_hal_icm20948/Example_Project/icm20948" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"icm20948/icm_20948.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

