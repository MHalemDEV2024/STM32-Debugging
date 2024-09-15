#include "delay.h"

/**
 * @brief Generates a delay based on the input time in seconds.
 *
 * This function creates a delay by looping for a calculated number of iterations.
 * The delay time is influenced by the system clock speed and the number of clock cycles
 * each loop iteration takes. The clock speed and cycles per iteration are approximations
 * and may need adjustment based on actual measurements and the specific microcontroller's
 * architecture and optimization settings.
 *
 * Clock Speed: 16 MHz (or actual system clock if known)
 * Cycles Per Iteration: Approximately 13 cycles (depends on architecture and optimization)
 *
 * The formula used to calculate the number of iterations is:
 *     delay_time (in seconds) * (Clock Speed / Cycles Per Iteration)
 *
 * Adjust the `clock_speed` and `cycles_per_iteration` constants if you are using a different
 * clock speed or require precise timing based on empirical measurement.
 *
 * @param seconds The delay time in seconds.
 */

void delay(uint32_t seconds) {
    // Define the system clock speed (16 MHz used here, adjust if necessary)
    uint32_t clock_speed = 16000000; // Replace with actual system clock frequency if known
    
    // Estimate the number of cycles per loop iteration (depends on architecture and compiler optimization)
    uint32_t cycles_per_iteration = 13; // Adjust based on actual measurement if necessary
    
    // Calculate the total number of iterations required to achieve the desired delay
    uint32_t count = (seconds * clock_speed) / cycles_per_iteration;
    
    // Loop for the calculated number of iterations to create the delay
    for (uint32_t i = 0; i < count; i++) {
        __asm("NOP"); // No operation instruction to burn CPU cycles
    }
}
