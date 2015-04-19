################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../bishop.cpp \
../chesspiece.cpp \
../gameofchess.cpp \
../gamepresenter.cpp \
../king.cpp \
../knight.cpp \
../main.cpp \
../pawn.cpp \
../queen.cpp \
../rook.cpp 

OBJS += \
./bishop.o \
./chesspiece.o \
./gameofchess.o \
./gamepresenter.o \
./king.o \
./knight.o \
./main.o \
./pawn.o \
./queen.o \
./rook.o 

CPP_DEPS += \
./bishop.d \
./chesspiece.d \
./gameofchess.d \
./gamepresenter.d \
./king.d \
./knight.d \
./main.d \
./pawn.d \
./queen.d \
./rook.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


