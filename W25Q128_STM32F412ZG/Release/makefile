################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
W25Q128_STM32F412ZG.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
W25Q128_STM32F412ZG.list \

OBJCOPY_BIN += \
W25Q128_STM32F412ZG.bin \


# All Target
all: W25Q128_STM32F412ZG.elf secondary-outputs

# Tool invocations
W25Q128_STM32F412ZG.elf: $(OBJS) $(USER_OBJS) D:\ST\TouchGFXDemo\W25Q128_STM32F412ZG\_FLASH.ld
	arm-none-eabi-gcc -o "W25Q128_STM32F412ZG.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\ST\TouchGFXDemo\W25Q128_STM32F412ZG\_FLASH.ld" --specs=nosys.specs -Wl,-Map="W25Q128_STM32F412ZG.map" -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

W25Q128_STM32F412ZG.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "W25Q128_STM32F412ZG.list"
	@echo 'Finished building: $@'
	@echo ' '

W25Q128_STM32F412ZG.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "W25Q128_STM32F412ZG.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
