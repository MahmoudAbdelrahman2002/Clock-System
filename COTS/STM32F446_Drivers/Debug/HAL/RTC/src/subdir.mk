################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/RTC/src/RTC_DS1307_prog.c 

OBJS += \
./HAL/RTC/src/RTC_DS1307_prog.o 

C_DEPS += \
./HAL/RTC/src/RTC_DS1307_prog.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/RTC/src/%.o HAL/RTC/src/%.su HAL/RTC/src/%.cyclo: ../HAL/RTC/src/%.c HAL/RTC/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-HAL-2f-RTC-2f-src

clean-HAL-2f-RTC-2f-src:
	-$(RM) ./HAL/RTC/src/RTC_DS1307_prog.cyclo ./HAL/RTC/src/RTC_DS1307_prog.d ./HAL/RTC/src/RTC_DS1307_prog.o ./HAL/RTC/src/RTC_DS1307_prog.su

.PHONY: clean-HAL-2f-RTC-2f-src

