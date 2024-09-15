
# STM32F429 Development with GDB, OpenOCD, and Makefile

## [Watch the video](https://youtu.be/58DR-Y4ve9s)



This repository contains a complete project setup for developing and debugging applications on the STM32F429 microcontroller. It includes source files, linker script, startup file, and a Makefile to automate building, flashing, and debugging. This guide explains how to use and navigate the project structure.


## Repository Structure

- **core/**
  - **inc/**
    - `delay.h`: Header file for delay functions.
    - `stm32f429xx.h`: Header file defining registers and peripheral functions for STM32F429.
  - **src/**
    - `delay.c`: Source file implementing delay functions.
  
- **linker/**
  - `STM32F429ZITX_FLASH.ld`: Linker script defining memory layout and sections (Flash, RAM, etc.).

- **startup/**
  - `startup_stm32f429zitx.c`: ARM assembly startup file to initialize the microcontroller, set up the stack, and call the main function.

- **.gitignore**: Specifies files to be excluded from version control (e.g., build artifacts, object files).

- **LICENSE**: Contains the licensing information for the project.

- **Makefile**: Automates compilation, flashing the STM32, and debugging with GDB.

- **README.md**: Project setup guide and documentation.

## Key Features

- **GDB Debugging**: Use GDB to set breakpoints, step through code, inspect registers, and debug firmware interactively.
- **OpenOCD Integration**: Interface with STM32 microcontrollers for flashing and debugging.
- **Linker Script**: Defines the memory layout for STM32F429.
- **ARM Startup File**: Initializes hardware and jumps to `main()`.
- **Makefile Automation**: Simplifies the build, flash, and debugging processes.

## How to Use

1. **Build the Project**: Compile the source files using the Makefile.
   ```bash
   make
   ```

2. **Flash the Program**: Use OpenOCD to upload the compiled firmware to the STM32 microcontroller.
   ```bash
   make flash
   ```

3. **Debug the Program**: Launch GDB to debug the firmware interactively.
   ```bash
   make debug
   ```

## Prerequisites

- **ARM Toolchain**:
  - `arm-none-eabi-gcc`: The GCC compiler for ARM.
  - `arm-none-eabi-gdb`: The GDB debugger for ARM.
- **OpenOCD**: Tool to interface with the STM32 microcontroller.
- **STM32 Development Board**: Example used is STM32F429.

## Setup Guide

### Setting Up the Environment

#### On Windows

1. **Install GCC ARM Toolchain**:
   - Download and install the toolchain from the [ARM Developer website](https://developer.arm.com/tools-and-software/embedded/arm-development-tools).
   - Ensure that the toolchain is added to your system's `PATH`.

2. **Install OpenOCD**:
   - Download and install OpenOCD from [OpenOCD's official website](http://openocd.org/).
   - Ensure that OpenOCD is added to your system's `PATH`.

3. **Configure GDB**:
   - Create a `gdbinit` file in your project directory with the following content:
     ```gdb
     target remote :3333
     monitor reset halt
     load
     ```

4. **Run GDB**:
   - Open a Command Prompt in the project directory.
   - Launch GDB:
     ```bash
     arm-none-eabi-gdb
     ```
   - Load the `gdbinit` configuration:
     ```gdb
     source gdbinit
     ```

#### On Linux

1. **Install GCC ARM Toolchain**:
   - For Ubuntu/Debian:
     ```bash
     sudo apt-get update
     sudo apt-get install gcc-arm-none-eabi gdb-arm-none-eabi
     ```
   - For Fedora:
     ```bash
     sudo dnf install arm-none-eabi-gcc arm-none-eabi-gdb
     ```

2. **Install OpenOCD**:
   - For Ubuntu/Debian:
     ```bash
     sudo apt-get install openocd
     ```
   - For Fedora:
     ```bash
     sudo dnf install openocd
     ```

3. **Configure GDB**:
   - Create a `gdbinit` file in the project directory:
     ```gdb
     target remote :3333
     monitor reset halt
     load
     ```

4. **Run GDB**:
   - Open a terminal in the project directory and start GDB:
     ```bash
     arm-none-eabi-gdb
     ```
   - Load the configuration:
     ```gdb
     source gdbinit
     ```

## Debugging Tips

- **OpenOCD Configuration**: Ensure the correct OpenOCD configuration file is used for your STM32 board. OpenOCD configurations are typically stored in the `scripts/` directory.
- **Common GDB Commands**:
   - `break <function>`: Set a breakpoint at a function.
   - `step`: Step into the next line of code.
   - `next`: Step over the current line or function.
   - `print <variable>`: Print the value of a variable.
   - `continue`: Resume program execution.

## Troubleshooting

- **GDB Connection Issues**: Ensure that OpenOCD is running and properly configured for your STM32 board. The default port in `gdbinit` is `:3333`.
- **PATH Configuration**: Ensure `arm-none-eabi-gcc` and `arm-none-eabi-gdb` are accessible from your terminal or command prompt by checking the `PATH` environment variable.


---
