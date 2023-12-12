################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/STK/SysTick_program.c 

OBJS += \
./Src/MCAL/STK/SysTick_program.o 

C_DEPS += \
./Src/MCAL/STK/SysTick_program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/STK/%.o Src/MCAL/STK/%.su Src/MCAL/STK/%.cyclo: ../Src/MCAL/STK/%.c Src/MCAL/STK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-STK

clean-Src-2f-MCAL-2f-STK:
	-$(RM) ./Src/MCAL/STK/SysTick_program.cyclo ./Src/MCAL/STK/SysTick_program.d ./Src/MCAL/STK/SysTick_program.o ./Src/MCAL/STK/SysTick_program.su

.PHONY: clean-Src-2f-MCAL-2f-STK

