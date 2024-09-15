/*******************************************************************************
**
** @file        : LinkerScript.ld
**
** @brief       : Linker script for STM32F429I-DISC1 Board with STM32F429ZITx Device
**                - FLASH: 2048KBytes
**                - CCMRAM: 64KBytes
**                - RAM: 192KBytes
**
**                Configures memory regions, stack, and heap sizes.
**                Adjust memory regions and sizes based on your application needs.
**
** @attention   : This file is provided "AS-IS". Modify it according to your project needs.
**
*******************************************************************************/

/* Entry Point */
ENTRY(Reset_Handler)

/* Define the end of the stack */
_estack = ORIGIN(RAM) + LENGTH(RAM); /* End of RAM */

/* Define minimum heap and stack sizes */
_Min_Heap_Size = 0x200; /* 512 bytes */
_Min_Stack_Size = 0x400; /* 1024 bytes */

/* Memory regions definition */
MEMORY
{
  CCMRAM (xrw)    : ORIGIN = 0x10000000, LENGTH = 64K
  RAM    (xrw)    : ORIGIN = 0x20000000, LENGTH = 192K
  FLASH  (rx)     : ORIGIN = 0x08000000, LENGTH = 2048K
}

/* Linker Sections */
SECTIONS
{
  /* Interrupt vector table in FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* Program code in FLASH */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* Code sections */
    *(.text*)          /* Additional code sections */
    *(.glue_7)         /* ARM to Thumb glue code */
    *(.glue_7t)        /* Thumb to ARM glue code */
    *(.eh_frame)       /* Exception handling frames */

    KEEP (*(.init))    /* Initialization code */
    KEEP (*(.fini))    /* Finalization code */

    . = ALIGN(4);
    _etext = .;        /* End of code */
  } >FLASH

  /* Constant data in FLASH */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* Read-only data sections */
    *(.rodata*)        /* Additional read-only data sections */
    . = ALIGN(4);
  } >FLASH

  /* ARM Exception Tables */
  .ARM.extab :
  {
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } >FLASH

  /* ARM Exception Index Table */
  .ARM :
  {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } >FLASH

  /* Pre-initialization array in FLASH */
  .preinit_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } >FLASH

  /* Initialization array in FLASH */
  .init_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } >FLASH

  /* Finalization array in FLASH */
  .fini_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } >FLASH

  /* Used by the startup to initialize data */
  _sidata = LOADADDR(.data);


  /* Initialized data sections in RAM */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* Start of data section */
    *(.data)           /* Data sections */
    *(.data*)          /* Additional data sections */
    *(.RamFunc)        /* RAM functions */
    *(.RamFunc*)       /* Additional RAM functions */

    . = ALIGN(4);
    _edata = .;        /* End of data section */
  } >RAM AT> FLASH

  /* CCMRAM section */
  .ccmram :
  {
    . = ALIGN(4);
    _sccmram = .;       /* Start of CCMRAM */
    *(.ccmram)
    *(.ccmram*)

    . = ALIGN(4);
    _eccmram = .;       /* End of CCMRAM */
  } >CCMRAM AT> FLASH

  /* Uninitialized data section in RAM */
  .bss :
  {
    _sbss = .;         /* Start of BSS section */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* End of BSS section */
    __bss_end__ = _ebss;
  } >RAM

  /* Heap and stack allocation */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE (end = .);
    PROVIDE (_end = .);
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM

  /* Discard unused libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  /* ARM attributes */
  .ARM.attributes 0 : { *(.ARM.attributes) }
}
