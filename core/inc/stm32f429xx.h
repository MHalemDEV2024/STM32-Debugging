#ifndef INC_STM32F429XX_H_
#define INC_STM32F429XX_H_

#include <stdint.h>

/**
 * @file stm32f429xx.h
 * @brief Header file for STM32F429 microcontroller peripheral definitions.
 *
 * This header file contains definitions for base addresses, register offsets,
 * and bit masks for the GPIO and RCC peripherals of the STM32F429 microcontroller.
 * It provides a direct and efficient way to access hardware registers and
 * configure peripherals for low-level programming and embedded applications.
 */

/* Base addresses for the GPIO and RCC peripherals */
#define AHB1PERIPH_BASEADDR		0x40020000UL


#define RCC_BASE       (AHB1PERIPH_BASEADDR + 0x3800)  /**< Base address of the RCC (Reset and Clock Control) peripheral */
#define GPIOG_BASE     (AHB1PERIPH_BASEADDR + 0x1800)  /**< Base address of GPIOG (General Purpose Input/Output G) peripheral */

/* Offsets for the relevant registers */
#define RCC_AHB1ENR    (*(volatile uint32_t *)(RCC_BASE + 0x30)) /**< RCC AHB1 peripheral clock enable register */
#define GPIOG_MODER    (*(volatile uint32_t *)(GPIOG_BASE + 0x00)) /**< GPIOG mode register */
#define GPIOG_ODR      (*(volatile uint32_t *)(GPIOG_BASE + 0x14)) /**< GPIOG output data register */

/* Bit positions and masks for the GPIO and RCC peripherals */

/**
 * @brief RCC AHB1 peripheral clock enable register bit mask for GPIOG.
 */
#define RCC_AHB1ENR_GPIOGEN  (1 << 6) /**< Bit 6 in RCC_AHB1ENR to enable the clock for GPIOG */

/**
 * @brief GPIOG mode register bit mask for pin 13.
 */
#define GPIO_MODER_MODER13   (1 << (13 * 2)) /**< Bit field in GPIOG_MODER to set the mode of pin 13 */

/**
 * @brief GPIOG mode register bit mask for pin 14.
 */
#define GPIO_MODER_MODER14   (1 << (14 * 2)) /**< Bit field in GPIOG_MODER to set the mode of pin 14 */

/**
 * @brief GPIOG output data register bit mask for pin 13.
 */
#define GPIO_ODR_ODR_13      (1 << 13) /**< Bit 13 in GPIOG_ODR to control the output data for pin 13 */

/**
 * @brief GPIOG output data register bit mask for pin 14.
 */
#define GPIO_ODR_ODR_14      (1 << 14) /**< Bit 14 in GPIOG_ODR to control the output data for pin 14 */

#endif /* INC_STM32F429XX_H_ */
