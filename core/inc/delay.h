#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include <stdint.h>

/**
 * @file delay.h
 * @brief Header file for delay functions.
 *
 * This file provides the function declaration for a delay utility 
 * used to introduce a blocking delay in the program execution. 
 * The delay function is typically used for time-based operations 
 * such as generating timed events or creating time gaps between 
 * actions in embedded systems.
 */

/**
 * @brief Introduces a delay in seconds.
 *
 * This function causes the program to wait for the specified number 
 * of seconds. The delay is implemented using a simple loop and is 
 * dependent on the processor's clock speed and optimization settings.
 *
 * @param seconds The number of seconds to delay.
 * 
 * @note The accuracy of the delay is influenced by compiler optimization 
 *       and clock settings. For precise timing requirements, consider 
 *       using hardware timers or other more accurate timekeeping methods.
 */
void delay(uint32_t seconds);

#endif /* INC_DELAY_H_ */
