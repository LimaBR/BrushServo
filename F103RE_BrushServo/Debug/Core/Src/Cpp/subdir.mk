################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Cpp/BTS7960B.cpp \
../Core/Src/Cpp/SerialDebug.cpp \
../Core/Src/Cpp/Start.cpp \
../Core/Src/Cpp/StaticFIFO.cpp 

OBJS += \
./Core/Src/Cpp/BTS7960B.o \
./Core/Src/Cpp/SerialDebug.o \
./Core/Src/Cpp/Start.o \
./Core/Src/Cpp/StaticFIFO.o 

CPP_DEPS += \
./Core/Src/Cpp/BTS7960B.d \
./Core/Src/Cpp/SerialDebug.d \
./Core/Src/Cpp/Start.d \
./Core/Src/Cpp/StaticFIFO.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Cpp/%.o Core/Src/Cpp/%.su: ../Core/Src/Cpp/%.cpp Core/Src/Cpp/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Cpp

clean-Core-2f-Src-2f-Cpp:
	-$(RM) ./Core/Src/Cpp/BTS7960B.d ./Core/Src/Cpp/BTS7960B.o ./Core/Src/Cpp/BTS7960B.su ./Core/Src/Cpp/SerialDebug.d ./Core/Src/Cpp/SerialDebug.o ./Core/Src/Cpp/SerialDebug.su ./Core/Src/Cpp/Start.d ./Core/Src/Cpp/Start.o ./Core/Src/Cpp/Start.su ./Core/Src/Cpp/StaticFIFO.d ./Core/Src/Cpp/StaticFIFO.o ./Core/Src/Cpp/StaticFIFO.su

.PHONY: clean-Core-2f-Src-2f-Cpp
