################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APPLICATION/Door_Locker_Security_System_Control_ECU.c 

OBJS += \
./APPLICATION/Door_Locker_Security_System_Control_ECU.o 

C_DEPS += \
./APPLICATION/Door_Locker_Security_System_Control_ECU.d 


# Each subdirectory must supply rules for building sources it contributes
APPLICATION/%.o: ../APPLICATION/%.c APPLICATION/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


