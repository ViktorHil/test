################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/subdir.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
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
Test2.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Test2.list \


# All Target
all: Test2.elf secondary-outputs

# Tool invocations
Test2.elf: $(OBJS) $(USER_OBJS) D:\STM32CubeIDE\workspace_1.0.2\Test2\STM32F072C8TX_FLASH.ld
	arm-none-eabi-gcc -o "Test2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"D:\STM32CubeIDE\workspace_1.0.2\Test2\STM32F072C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Test2.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Test2.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Test2.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
