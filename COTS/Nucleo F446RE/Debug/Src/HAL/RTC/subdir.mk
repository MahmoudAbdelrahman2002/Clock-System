################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/RTC/DS1307_RTC.c 

OBJS += \
./Src/HAL/RTC/DS1307_RTC.o 

C_DEPS += \
./Src/HAL/RTC/DS1307_RTC.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/RTC/%.o Src/HAL/RTC/%.su Src/HAL/RTC/%.cyclo: ../Src/HAL/RTC/%.c Src/HAL/RTC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-HAL-2f-RTC

clean-Src-2f-HAL-2f-RTC:
	-$(RM) ./Src/HAL/RTC/DS1307_RTC.cyclo ./Src/HAL/RTC/DS1307_RTC.d ./Src/HAL/RTC/DS1307_RTC.o ./Src/HAL/RTC/DS1307_RTC.su

.PHONY: clean-Src-2f-HAL-2f-RTC

