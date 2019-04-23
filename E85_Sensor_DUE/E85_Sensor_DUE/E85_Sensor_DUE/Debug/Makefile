################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../linker_scripts/ \
../linker_scripts/linker_scripts/ \
../linker_scripts/linker_scripts/gcc/


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../Sketch.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
Sketch.o

OBJS_AS_ARGS +=  \
Sketch.o

C_DEPS +=  \
Sketch.d

C_DEPS_AS_ARGS +=  \
Sketch.d

OUTPUT_FILE_PATH +=E85_Sensor_DUE.elf

OUTPUT_FILE_PATH_AS_ARGS +=E85_Sensor_DUE.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+=  \
../linker_scripts/linker_scripts/gcc/flash.ld \
../linker_scripts/linker_scripts/gcc/sram.ld


# AVR32/GNU C Compiler



./%.o: .././%.cpp
	@echo Building file: $<
	@echo Invoking: ARM/GNU C Compiler : 5.3.1
	$(QUOTE)F:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-g++.exe$(QUOTE) -mthumb -D__SAM3X8E__ -DDEBUG -DF_CPU=84000000L -DARDUINO=10804 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSB_PRODUCT="\"Arduino Due\"" -DUSB_MANUFACTURER="\"Arduino LLC\"" -DUSBCON  -I"F:\Atmel Studio\7.0\Packs\arm\cmsis\4.2.0\CMSIS\Include" -I"..\\..\ArduinoCore\include\core" -I"..\\..\ArduinoCore\include\variants" -I"..\\..\ArduinoCore\include\core\avr" -I"..\\..\ArduinoCore\include\core\USB" -I"..\\..\ArduinoCore\include\libraries\due_can-master"  -Os -fno-threadsafe-statics -fno-exceptions -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -g3 -w -mcpu=cortex-m3 -c -std=gnu++11 --param max-inline-insns-single=500 -nostdlib -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: ARM/GNU Linker : 5.3.1
	$(QUOTE)F:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -mthumb -Wl,-Map="E85_Sensor_DUE.map" --specs=nano.specs --specs=nosys.specs -Wl,--start-group -lm -lArduinoCore  -Wl,--end-group -L"..\linker_scripts\linker_scripts\gcc" -L"C:\Users\Alf\Documents\Arduino\E85_Sensor_DUE\E85_Sensor_DUE\E85_Sensor_DUE\ArduinoCore\Debug"  -Wl,--gc-sections -mcpu=cortex-m3 -Tflash_without_bootloader.ld -Wl,--cref -Os -Wl,--check-sections -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align  
	@echo Finished building target: $@
	"F:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O binary "E85_Sensor_DUE.elf" "E85_Sensor_DUE.bin"
	"F:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "E85_Sensor_DUE.elf" "E85_Sensor_DUE.hex"
	"F:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O binary "E85_Sensor_DUE.elf" "E85_Sensor_DUE.eep" || exit 0
	"F:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objdump.exe" -h -S "E85_Sensor_DUE.elf" > "E85_Sensor_DUE.lss"
	"F:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "E85_Sensor_DUE.elf" "E85_Sensor_DUE.srec"
	"F:\Atmel Studio\7.0\toolchain\arm\arm-gnu-toolchain\bin\arm-none-eabi-size.exe" "E85_Sensor_DUE.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "E85_Sensor_DUE.elf" "E85_Sensor_DUE.a" "E85_Sensor_DUE.hex" "E85_Sensor_DUE.bin" "E85_Sensor_DUE.lss" "E85_Sensor_DUE.eep" "E85_Sensor_DUE.map" "E85_Sensor_DUE.srec"
	