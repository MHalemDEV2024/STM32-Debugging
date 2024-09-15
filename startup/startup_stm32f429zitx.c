/*
 * ----------------------------------------------------------------------------
 * STM32F429 Vector Table and Startup Code
 * ----------------------------------------------------------------------------
 *
 * This file sets up the vector table and the initial startup code for the STM32F429
 * microcontroller. It includes initialization routines for the system and defines
 * default interrupt handlers. The startup file is essential for booting the system
 * and setting up the runtime environment for the application.
 *
 * Definitions:
 * - SRAM_START    : Start address of the Static RAM (SRAM) region.
 * - SRAM_SIZE     : Size of SRAM, defined as 128KB.
 * - SRAM_END      : End address of the SRAM region.
 * - STACK_START   : Initial stack pointer value, set to the end of SRAM.
 *
 * External Symbols:
 * - _etext       : End of the text (code) section in Flash.
 * - _sdata       : Start of the initialized data section in SRAM.
 * - _edata       : End of the initialized data section in SRAM.
 * - _sidata     : Start address of the loaded data section in Flash.
 * - _sbss        : Start of the uninitialized data section (BSS) in SRAM.
 * - _ebss        : End of the uninitialized data section (BSS) in SRAM.
 *
 * Function Prototypes:
 * - main()       : Entry point of the application.
 *
 * Interrupt Handlers:
 * This file includes weak default handlers for all system exceptions and IRQs
 * (Interrupt Request). Each handler is associated with a specific interrupt or
 * exception vector. By default, all handlers point to a common "Default_Handler"
 * function, which enters an infinite loop. Specific handlers should be provided
 * by the user application as needed.
 *
 * Vector Table:
 * The vector table is defined in the `.isr_vector` section and includes the initial
 * stack pointer value followed by the addresses of the reset and exception handlers,
 * as well as the addresses for each IRQ handler.
 *
 * Reset Handler:
 * - Copies the initialized data section from Flash to SRAM.
 * - Initializes the BSS section to zero in SRAM.
 * - Calls the `main()` function to start the application.
 *
 * ----------------------------------------------------------------------------
 */

#include <stdint.h>

/* SRAM Memory Addresses and Size Definitions */
#define SRAM_START  0x20000000U
#define SRAM_SIZE   (128U * 1024U)  // 128KB
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))
#define STACK_START SRAM_END

/* External Symbols */
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sidata;
extern uint32_t _sbss;
extern uint32_t _ebss;

/* Function Prototypes */
int main(void);


void Reset_Handler(void);
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

void WWDG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ADC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN1_TX_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN1_RX0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN1_RX1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_FS_WKUP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_BRK_TIM12_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_UP_TIM13_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_TRG_COM_TIM14_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void FMC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SDIO_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ETH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ETH_WKUP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_TX_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_RX0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_RX1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CAN2_SCE_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_HS_EP1_OUT_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_HS_EP1_IN_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_HS_WKUP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_HS_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DCMI_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CRYP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void HASH_RNG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void FPU_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART8_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SAI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void LCD_TFT_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void LCD_TFT_1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2D_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));


/* Vector Table */
uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    STACK_START,                          // Initial stack pointer
    (uint32_t)Reset_Handler,              // Reset Handler
    (uint32_t)NMI_Handler,                // NMI Handler
    (uint32_t)HardFault_Handler,          // HardFault Handler
    (uint32_t)MemManage_Handler,          // MemManage Handler
    (uint32_t)BusFault_Handler,           // BusFault Handler
    (uint32_t)UsageFault_Handler,         // UsageFault Handler
    (uint32_t)0,                          // Reserved
    (uint32_t)0,                          // Reserved
    (uint32_t)0,                          // Reserved
    (uint32_t)0,                          // Reserved
    (uint32_t)SVC_Handler,                // SVCall Handler
    (uint32_t)DebugMon_Handler,           // Debug Monitor Handler
    (uint32_t)0,                          // Reserved
    (uint32_t)PendSV_Handler,             // PendSV Handler
    (uint32_t)SysTick_Handler,            // SysTick Handler

    // External interrupts start here
    (uint32_t)WWDG_IRQHandler,            // Window Watchdog interrupt
    (uint32_t)PVD_IRQHandler,             // PVD through EXTI line detection interrupt
    (uint32_t)TAMP_STAMP_IRQHandler,      // Tamper and TimeStamp interrupts through the EXTI line
    (uint32_t)RTC_WKUP_IRQHandler,        // RTC Wakeup interrupt through the EXTI line
    (uint32_t)FLASH_IRQHandler,           // Flash global interrupt
    (uint32_t)RCC_IRQHandler,             // RCC global interrupt
    (uint32_t)EXTI0_IRQHandler,           // EXTI Line0 interrupt
    (uint32_t)EXTI1_IRQHandler,           // EXTI Line1 interrupt
    (uint32_t)EXTI2_IRQHandler,           // EXTI Line2 interrupt
    (uint32_t)EXTI3_IRQHandler,           // EXTI Line3 interrupt
    (uint32_t)EXTI4_IRQHandler,           // EXTI Line4 interrupt
    (uint32_t)DMA1_Stream0_IRQHandler,    // DMA1 Stream0 global interrupt
    (uint32_t)DMA1_Stream1_IRQHandler,    // DMA1 Stream1 global interrupt
    (uint32_t)DMA1_Stream2_IRQHandler,    // DMA1 Stream2 global interrupt
    (uint32_t)DMA1_Stream3_IRQHandler,    // DMA1 Stream3 global interrupt
    (uint32_t)DMA1_Stream4_IRQHandler,    // DMA1 Stream4 global interrupt
    (uint32_t)DMA1_Stream5_IRQHandler,    // DMA1 Stream5 global interrupt
    (uint32_t)DMA1_Stream6_IRQHandler,    // DMA1 Stream6 global interrupt
    (uint32_t)ADC_IRQHandler,             // ADC global interrupt
    (uint32_t)CAN1_TX_IRQHandler,         // CAN1 TX interrupt
    (uint32_t)CAN1_RX0_IRQHandler,        // CAN1 RX0 interrupt
    (uint32_t)CAN1_RX1_IRQHandler,        // CAN1 RX1 interrupt
    (uint32_t)CAN1_SCE_IRQHandler,        // CAN1 SCE interrupt
    (uint32_t)EXTI9_5_IRQHandler,         // EXTI Line[9:5] interrupts
    (uint32_t)TIM1_BRK_TIM9_IRQHandler,   // TIM1 Break interrupt and TIM9 global interrupt
    (uint32_t)TIM1_UP_TIM10_IRQHandler,   // TIM1 Update interrupt and TIM10 global interrupt
    (uint32_t)TIM1_TRG_COM_TIM11_IRQHandler, // TIM1 Trigger and Commutation interrupts and TIM11 global interrupt
    (uint32_t)TIM1_CC_IRQHandler,         // TIM1 Capture Compare interrupt
    (uint32_t)TIM2_IRQHandler,            // TIM2 global interrupt
    (uint32_t)TIM3_IRQHandler,            // TIM3 global interrupt
    (uint32_t)TIM4_IRQHandler,            // TIM4 global interrupt
    (uint32_t)I2C1_EV_IRQHandler,        // I2C1 event interrupt
    (uint32_t)I2C1_ER_IRQHandler,        // I2C1 error interrupt
    (uint32_t)I2C2_EV_IRQHandler,        // I2C2 event interrupt
    (uint32_t)I2C2_ER_IRQHandler,        // I2C2 error interrupt
    (uint32_t)SPI1_IRQHandler,           // SPI1 global interrupt
    (uint32_t)SPI2_IRQHandler,           // SPI2 global interrupt
    (uint32_t)USART1_IRQHandler,         // USART1 global interrupt
    (uint32_t)USART2_IRQHandler,         // USART2 global interrupt
    (uint32_t)USART3_IRQHandler,         // USART3 global interrupt
    (uint32_t)EXTI15_10_IRQHandler,      // EXTI Line[15:10] interrupts
    (uint32_t)RTC_Alarm_IRQHandler,      // RTC Alarms (A and B) through EXTI line interrupt
    (uint32_t)OTG_FS_WKUP_IRQHandler,    // USB On-The-Go FS Wakeup through EXTI line interrupt
    (uint32_t)TIM8_BRK_TIM12_IRQHandler, // TIM8 Break interrupt and TIM12 global interrupt
    (uint32_t)TIM8_UP_TIM13_IRQHandler,  // TIM8 Update interrupt and TIM13 global interrupt
    (uint32_t)TIM8_TRG_COM_TIM14_IRQHandler, // TIM8 Trigger and Commutation interrupts and TIM14 global interrupt
    (uint32_t)TIM8_CC_IRQHandler,        // TIM8 Capture Compare interrupt
    (uint32_t)DMA1_Stream7_IRQHandler,   // DMA1 Stream7 global interrupt
    (uint32_t)FMC_IRQHandler,            // FMC global interrupt
    (uint32_t)SDIO_IRQHandler,           // SDIO global interrupt
    (uint32_t)TIM5_IRQHandler,           // TIM5 global interrupt
    (uint32_t)SPI3_IRQHandler,           // SPI3 global interrupt
    (uint32_t)UART4_IRQHandler,          // UART4 global interrupt
    (uint32_t)UART5_IRQHandler,          // UART5 global interrupt
    (uint32_t)TIM6_DAC_IRQHandler,       // TIM6 global interrupt, DAC1 and DAC2 underrun error interrupt
    (uint32_t)TIM7_IRQHandler,           // TIM7 global interrupt
    (uint32_t)DMA2_Stream0_IRQHandler,   // DMA2 Stream0 global interrupt
    (uint32_t)DMA2_Stream1_IRQHandler,   // DMA2 Stream1 global interrupt
    (uint32_t)DMA2_Stream2_IRQHandler,   // DMA2 Stream2 global interrupt
    (uint32_t)DMA2_Stream3_IRQHandler,   // DMA2 Stream3 global interrupt
    (uint32_t)DMA2_Stream4_IRQHandler,   // DMA2 Stream4 global interrupt
    (uint32_t)ETH_IRQHandler,            // Ethernet global interrupt
    (uint32_t)ETH_WKUP_IRQHandler,       // Ethernet Wakeup through EXTI line interrupt
    (uint32_t)CAN2_TX_IRQHandler,        // CAN2 TX interrupt
    (uint32_t)CAN2_RX0_IRQHandler,       // CAN2 RX0 interrupt
    (uint32_t)CAN2_RX1_IRQHandler,       // CAN2 RX1 interrupt
    (uint32_t)CAN2_SCE_IRQHandler,       // CAN2 SCE interrupt
    (uint32_t)OTG_FS_IRQHandler,         // USB On-The-Go FS global interrupt
    (uint32_t)DMA2_Stream5_IRQHandler,   // DMA2 Stream5 global interrupt
    (uint32_t)DMA2_Stream6_IRQHandler,   // DMA2 Stream6 global interrupt
    (uint32_t)DMA2_Stream7_IRQHandler,   // DMA2 Stream7 global interrupt
    (uint32_t)USART6_IRQHandler,         // USART6 global interrupt
    (uint32_t)I2C3_EV_IRQHandler,        // I2C3 event interrupt
    (uint32_t)I2C3_ER_IRQHandler,        // I2C3 error interrupt
    (uint32_t)OTG_HS_EP1_OUT_IRQHandler, // USB On-The-Go HS End Point 1 Out global interrupt
    (uint32_t)OTG_HS_EP1_IN_IRQHandler,  // USB On-The-Go HS End Point 1 In global interrupt
    (uint32_t)OTG_HS_WKUP_IRQHandler,    // USB On-The-Go HS Wakeup through EXTI interrupt
    (uint32_t)OTG_HS_IRQHandler,         // USB On-The-Go HS global interrupt
    (uint32_t)DCMI_IRQHandler,           // DCMI global interrupt
    (uint32_t)CRYP_IRQHandler,           // CRYP crypto global interrupt
    (uint32_t)HASH_RNG_IRQHandler,       // Hash and RNG global interrupt
    (uint32_t)FPU_IRQHandler,            // FPU interrupt
    (uint32_t)UART7_IRQHandler,          // UART7 global interrupt
    (uint32_t)UART8_IRQHandler,          // UART8 global interrupt
    (uint32_t)SPI4_IRQHandler,           // SPI4 global interrupt
    (uint32_t)SPI5_IRQHandler,           // SPI5 global interrupt
    (uint32_t)SPI6_IRQHandler,           // SPI6 global interrupt
    (uint32_t)SAI1_IRQHandler,           // SAI1 global interrupt
    (uint32_t)LCD_TFT_IRQHandler,        // LCD_TFT global interrupt
    (uint32_t)LCD_TFT_1_IRQHandler,      // LCD_TFT_1 error interrupt
    (uint32_t)DMA2D_IRQHandler,          // DMA2D global interrupt
    
};

/* Default Handler Function */
void Default_Handler(void)
{
    while (1);
}

/* Reset Handler Function */
void Reset_Handler(void)
{
     // Copy data segment initializers from flash to SRAM
    uint32_t* pSrc  = (uint32_t *)&_sidata;
    uint32_t* pDest = (uint32_t *)&_sdata;
    while (pDest < &_edata) {
        *pDest++ = *pSrc++;
    }

    // Zero fill the bss segment
    pDest = &_sbss;
    while (pDest < &_ebss) {
        *pDest++ = 0;
    }

  
    // Call the main function
    main();

    // Infinite loop if main() returns
    while (1);
}

