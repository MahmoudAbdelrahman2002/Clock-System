################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/SYSCFG/SYSCFG_Program.c 

OBJS += \
./Src/MCAL/SYSCFG/SYSCFG_Program.o 

C_DEPS += \
./Src/MCAL/SYSCFG/SYSCFG_Program.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/SYSCFG/%.o Src/MCAL/SYSCFG/%.su Src/MCAL/SYSCFG/%.cyclo: ../Src/MCAL/SYSCFG/%.c Src/MCAL/SYSCFG/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-MCAL-2f-SYSCFG

clean-Src-2f-MCAL-2f-SYSCFG:
	-$(RM) ./Src/MCAL/SYSCFG/SYSCFG_Program.cyclo ./Src/MCAL/SYSCFG/SYSCFG_Program.d ./Src/MCAL/SYSCFG/SYSCFG_Program.o ./Src/MCAL/SYSCFG/SYSCFG_Program.su

.PHONY: clean-Src-2f-MCAL-2f-SYSCFG

