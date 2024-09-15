#include "stm32f429xx.h"
#include "delay.h"

int main(void) {
    // Enable clock for GPIOG
    RCC_AHB1ENR |= RCC_AHB1ENR_GPIOGEN;

    // Set PG13 and PG14 as output (mode 01)
   // GPIOG_MODER &= ~((0x3 << (13 * 2)) | (0x3 << (14 * 2)));  // Clear the mode bits for PG13 and PG14
    GPIOG_MODER |= GPIO_MODER_MODER13| GPIO_MODER_MODER14;     // Set PG13 and PG14 to output mode (01)

    while (1) {
        // Toggle LEDs on PG13 and PG14
        GPIOG_ODR ^= GPIO_ODR_ODR_13 | GPIO_ODR_ODR_14;
        
        // Delay
        delay(1);
    }
}