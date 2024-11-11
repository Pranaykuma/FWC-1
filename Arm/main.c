/*==========================================================
Code by G V V Sharma
March 7, 2021,
Released under GNU/GPL
https://www.gnu.org/licenses/gpl-3.0.en.html
/
 *==========================================================
 *
 *    File   : main.c
 *    Purpose: main for Pygmy blink onboard led
 *                                                          
 *=========================================================*/
#include <stdint.h>
#include <stdbool.h>

// Define the GPIO direction and data registers based on your platform
// These should be part of your microcontroller's memory-mapped I/O
#define GPIO_DIRECTION_REG     (*((volatile uint32_t *) 0x400FF014))  // Example address
#define GPIO_OUTPUT_REG        (*((volatile uint32_t *) 0x400FF004))  // Example address
#define GPIO_INPUT_REG         (*((volatile uint32_t *) 0x400FF000))  // Example address

// GPIO mode definitions
#define GPIO_OUTPUT_MODE       1
#define GPIO_INPUT_MODE        0

// Function to set GPIO direction
void PyHal_GPIO_SetDir(uint32_t gpionum, uint32_t dir) {
    uint32_t tempscratch32;
    tempscratch32 = GPIO_DIRECTION_REG;
    if (dir == GPIO_OUTPUT_MODE) {
        tempscratch32 |= (1 << gpionum);  // Set as output
    } else {
        tempscratch32 &= ~(1 << gpionum); // Set as input
    }
    GPIO_DIRECTION_REG = tempscratch32;
}

// Function to get GPIO direction
uint32_t PyHal_GPIO_GetDir(uint32_t gpionum) {
    uint32_t tempscratch32;
    tempscratch32 = GPIO_DIRECTION_REG;
    return ((tempscratch32 & (1 << gpionum)) ? GPIO_OUTPUT_MODE : GPIO_INPUT_MODE);
}

// Function to set GPIO output value
void PyHal_GPIO_Set(uint32_t gpionum, uint32_t value) {
    uint32_t tempscratch32;
    tempscratch32 = GPIO_OUTPUT_REG;
    if (value == 1) {
        tempscratch32 |= (1 << gpionum);  // Set pin high
    } else {
        tempscratch32 &= ~(1 << gpionum); // Set pin low
    }
    GPIO_OUTPUT_REG = tempscratch32;
}

// Function to get GPIO input value
uint32_t PyHal_GPIO_Get(uint32_t gpionum) {
    uint32_t tempscratch32;
    tempscratch32 = GPIO_INPUT_REG;
    return ((tempscratch32 & (1 << gpionum)) ? 1 : 0);  // Return pin state (1 or 0)
}

int main(void) {
    // Example: Set GPIO 0 as output
    PyHal_GPIO_SetDir(0, GPIO_OUTPUT_MODE);

    // Example: Toggle GPIO 0
    while (1) {
        PyHal_GPIO_Set(0, 1);  // Set GPIO 0 high
        for (volatile int i = 0; i < 1000000; i++);  // Delay
        PyHal_GPIO_Set(0, 0);  // Set GPIO 0 low
        for (volatile int i = 0; i < 1000000; i++);  // Delay
    }

    return 0;
}

