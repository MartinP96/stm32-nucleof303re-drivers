#ifndef _GPIOX_H_
#define _GPIOX_H_

#include "stm32f3xx.h"
#include <stdint.h>

/* Register definitions */

// Clock registers bit
#define AHBENR_IOPA (1 << 17)
#define AHBENR_IOPB (1 << 18)
#define AHBENR_IOPC (1 << 19)
#define AHBENR_IOPD (1 << 20)
#define AHBENR_IOPE (1 << 21)
#define AHBENR_IOPF (1 << 22)

//GPIO moder bits
#define INPUT_mode			0
#define OUTPUT_mode			1
#define ALTERNATE_mode		2
#define ANALOG_mode			3

// PIN special modes
#define AF0 0
#define AF1 1
#define AF2 2
#define AF3 3
#define AF4 4
#define AF5 5
#define AF6 6
#define AF7 7
#define AF8 8
#define AF9 9
#define AF10 10
#define AF11 11
#define AF12 12
#define AF13 13
#define AF14 14
#define AF15 15

// Pin states
#define HIGH_state 1
#define LOW_state  0

/* Function definitions */
void gpio_init(void);
void gpio_pin_mode(GPIO_TypeDef* port, uint8_t pin, uint8_t mode);
void gpio_write_pin(GPIO_TypeDef* port, uint8_t pin, uint8_t state);
void gpio_write(GPIO_TypeDef* port, uint32_t value);
uint8_t gpio_read_pin(GPIO_TypeDef* port, uint8_t pin);
void gpio_set_alternate_function(GPIO_TypeDef* port, uint8_t pin, uint32_t AF);

#endif


