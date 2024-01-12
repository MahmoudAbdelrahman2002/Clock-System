################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/RCC/src/RCC_prog.c 

OBJS += \
./MCAL/RCC/src/RCC_prog.o 

C_DEPS += \
./MCAL/RCC/src/RCC_prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/RCC/src/%.o MCAL/RCC/src/%.su MCAL/RCC/src/%.cyclo: ../MCAL/RCC/src/%.c MCAL/RCC/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCAL-2f-RCC-2f-src

clean-MCAL-2f-RCC-2f-src:
	-$(RM) ./MCAL/RCC/src/RCC_prog.cyclo ./MCAL/RCC/src/RCC_prog.d ./MCAL/RCC/src/RCC_prog.o ./MCAL/RCC/src/RCC_prog.su

.PHONY: clean-MCAL-2f-RCC-2f-src

