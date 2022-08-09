#include "gpiox.h"
#include "stm32f3xx.h"


/*
 * Function: gpio_init
 * Description: Initialize AHBENR BUS clocks
 *
 */
void gpio_init(void)
{
	// Enable GPIO clock bus
	RCC->AHBENR |= AHBENR_IOPA;
	RCC->AHBENR |= AHBENR_IOPB;
	RCC->AHBENR |= AHBENR_IOPC;
	RCC->AHBENR |= AHBENR_IOPD;
	RCC->AHBENR |= AHBENR_IOPE;
	RCC->AHBENR |= AHBENR_IOPF;
}


/*
 * Function: gpio_write_pin
 * Description: Write value to the pin
 * @port : output pin port
 * @pin  : output pin
 * @state : state of the output pin (HIGH_state, LOW_state)
 *
 */
void gpio_write_pin(GPIO_TypeDef* port, uint8_t pin, uint8_t state)
{
	if (state != 0)
	{
		port->BSRR |= (1U << pin);
	}
	else
	{
		port->BSRR |= (1U << pin << 16);
	}
}


/*
 * Function: gpio_write_port
 * Description: Write value to the output port
 * @port : output pin port
 * @value  : value to be written to port
 */
void gpio_write(GPIO_TypeDef* port, uint32_t value)
{
	port->ODR = value;
}


/*
 * Function: gpio_pin_mode
 * Description: Set mode of the selected pin
 * @port :  port
 * @value  : value to be written to port
 */
void gpio_pin_mode(GPIO_TypeDef* port, uint8_t pin, uint8_t mode)
{
	switch(mode)
	{
		case INPUT_mode:
			port->MODER &= ~(1U << (pin*2));
			port->MODER &= ~(1U << (pin*2 + 1));
			break;

		case OUTPUT_mode:
			port->MODER |=  (1U << (pin*2));
			port->MODER &= ~(1U << (pin*2 + 1));
			break;

		case ALTERNATE_mode:
			port->MODER &= ~(1U << (pin*2));
			port->MODER |=  (1U << (pin*2 + 1));
			break;

		case ANALOG_mode:
			port->MODER |=  (1U << (pin*2));
			port->MODER |=  (1U << (pin*2 + 1));
			break;
	}
}


/*
 * Function: gpio_pin_mode
 * Description: Set mode of the selected pin
 * @port :  port
 * @value  : value to be written to port
 */
uint8_t gpio_read_pin(GPIO_TypeDef* port, uint8_t pin)
{
	if (port->IDR & (1U << pin))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 * Function: gpio_set alternate_function
 * Description: Set alternate function mode of gpio pin
 * @port :  port
 * @value  : value to be written to port
 */
void gpio_set_alternate_function(GPIO_TypeDef* port, uint8_t pin, uint32_t AF)
{
	if (pin <= 7)
	{
		// Test
		uint32_t state = port->AFR[0];
		uint32_t state_new = state | (AF << pin*4);
		port->AFR[0] = state_new;
	}
	else
	{
		uint32_t state = port->AFR[0];
		uint32_t state_new = state | (AF << pin*4);
		port->AFR[1] |= (AF << pin*4);
	}
}
