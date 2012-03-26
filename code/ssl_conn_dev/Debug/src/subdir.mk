################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/client.cc \
../src/server.cc \
../src/sim.cc \
../src/ssl_conn.cc 

OBJS += \
./src/client.o \
./src/server.o \
./src/sim.o \
./src/ssl_conn.o 

CC_DEPS += \
./src/client.d \
./src/server.d \
./src/sim.d \
./src/ssl_conn.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


