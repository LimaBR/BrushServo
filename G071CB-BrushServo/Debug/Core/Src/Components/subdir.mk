################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Components/ADC_STM32.cpp \
../Core/Src/Components/BrushServo.cpp \
../Core/Src/Components/INA1X9.cpp \
../Core/Src/Components/Motor_IR4427.cpp \
../Core/Src/Components/PWM_Pin_STM32.cpp \
../Core/Src/Components/Potentiometer.cpp \
../Core/Src/Components/VinMeter.cpp \
../Core/Src/Components/start.cpp 

OBJS += \
./Core/Src/Components/ADC_STM32.o \
./Core/Src/Components/BrushServo.o \
./Core/Src/Components/INA1X9.o \
./Core/Src/Components/Motor_IR4427.o \
./Core/Src/Components/PWM_Pin_STM32.o \
./Core/Src/Components/Potentiometer.o \
./Core/Src/Components/VinMeter.o \
./Core/Src/Components/start.o 

CPP_DEPS += \
./Core/Src/Components/ADC_STM32.d \
./Core/Src/Components/BrushServo.d \
./Core/Src/Components/INA1X9.d \
./Core/Src/Components/Motor_IR4427.d \
./Core/Src/Components/PWM_Pin_STM32.d \
./Core/Src/Components/Potentiometer.d \
./Core/Src/Components/VinMeter.d \
./Core/Src/Components/start.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Components/%.o Core/Src/Components/%.su Core/Src/Components/%.cyclo: ../Core/Src/Components/%.cpp Core/Src/Components/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0plus -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G071xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Components

clean-Core-2f-Src-2f-Components:
	-$(RM) ./Core/Src/Components/ADC_STM32.cyclo ./Core/Src/Components/ADC_STM32.d ./Core/Src/Components/ADC_STM32.o ./Core/Src/Components/ADC_STM32.su ./Core/Src/Components/BrushServo.cyclo ./Core/Src/Components/BrushServo.d ./Core/Src/Components/BrushServo.o ./Core/Src/Components/BrushServo.su ./Core/Src/Components/INA1X9.cyclo ./Core/Src/Components/INA1X9.d ./Core/Src/Components/INA1X9.o ./Core/Src/Components/INA1X9.su ./Core/Src/Components/Motor_IR4427.cyclo ./Core/Src/Components/Motor_IR4427.d ./Core/Src/Components/Motor_IR4427.o ./Core/Src/Components/Motor_IR4427.su ./Core/Src/Components/PWM_Pin_STM32.cyclo ./Core/Src/Components/PWM_Pin_STM32.d ./Core/Src/Components/PWM_Pin_STM32.o ./Core/Src/Components/PWM_Pin_STM32.su ./Core/Src/Components/Potentiometer.cyclo ./Core/Src/Components/Potentiometer.d ./Core/Src/Components/Potentiometer.o ./Core/Src/Components/Potentiometer.su ./Core/Src/Components/VinMeter.cyclo ./Core/Src/Components/VinMeter.d ./Core/Src/Components/VinMeter.o ./Core/Src/Components/VinMeter.su ./Core/Src/Components/start.cyclo ./Core/Src/Components/start.d ./Core/Src/Components/start.o ./Core/Src/Components/start.su

.PHONY: clean-Core-2f-Src-2f-Components

