#######################################
# Project Name (can be passed via command line)
#######################################
TARGET ?= main

#######################################
# Toolchain and Tools
#######################################
CC      = arm-none-eabi-gcc
CP      = arm-none-eabi-objcopy
SZ      = arm-none-eabi-size
OPENOCD = openocd
GDB     = arm-none-eabi-gdb

#######################################
# MCU and Architecture Settings
#######################################
MACH    = cortex-m4
MCU     = -mcpu=$(MACH) -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# Linker script
LD_SCRIPT = linker/STM32F429ZITX_FLASH.ld

#######################################
# Files and Sources
#######################################
C_SOURCES = core/src/$(TARGET).c core/src/delay.c startup/startup_stm32f429zitx.c

# Include paths
INC_DIR = core/inc startup/inc
INCLUDES = $(addprefix -I, $(INC_DIR))

#######################################
# Compilation Flags
#######################################
CFLAGS  = $(MCU) -O2 -g -Wall -std=c99 -ffunction-sections -fdata-sections $(INCLUDES)
CFLAGS += -DSTM32F429xx

LDFLAGS = -T$(LD_SCRIPT) -specs=nosys.specs -lc -lm -lnosys -Wl,--gc-sections -nostdlib

#######################################
# Build Output Paths
#######################################
BUILD_DIR = build
ELF = $(BUILD_DIR)/$(TARGET).elf
BIN = $(BUILD_DIR)/$(TARGET).bin
MAP = $(BUILD_DIR)/$(TARGET).map
HEX = $(BUILD_DIR)/$(TARGET).hex

#######################################
# Rules
#######################################
all: $(BUILD_DIR) $(ELF) $(BIN) $(MAP) $(HEX)

$(BUILD_DIR):
ifeq ($(OS),Windows_NT)
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
	mkdir -p $(BUILD_DIR)
endif

$(ELF): $(C_SOURCES)
	$(CC) $(CFLAGS) $(C_SOURCES) $(LDFLAGS) -o $(ELF)

$(BIN): $(ELF)
	$(CP) -O binary $(ELF) $(BIN)

$(MAP): $(ELF)
	$(SZ) $(ELF) > $(MAP)

$(HEX): $(ELF)
	$(CP) -O ihex $(ELF) $(HEX)

clean:
ifeq ($(OS),Windows_NT)
	del /s /q $(BUILD_DIR)
	rmdir /s /q $(BUILD_DIR)
else
	rm -rf $(BUILD_DIR)
endif

flash: $(ELF)
	$(OPENOCD) -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(ELF) verify reset exit"

debug: $(ELF)
	$(GDB) $(ELF)

# Ensure the TARGET variable is passed down to all relevant targets
.PHONY: all clean flash debug
