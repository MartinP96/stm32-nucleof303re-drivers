#include "uart.h"


/*
 * Initialize uart2 in transfer mode.
 */
void uart2_tx_init(void)
{
	/***************Configure uart gpio pin************/

	/*Enable clock access to gpioa */
	RCC->AHBENR |= IOPAEN;

	/*Set PA2 mode to alternate function mode*/
	GPIOA->MODER &= ~(1UL << 4);
	GPIOA->MODER |=  (1UL << 5);

	/*Set PA2 alternate function type to UART_TX (AF07) */
	GPIOA->AFR[0] |= (1 << 8);
	GPIOA->AFR[0] |= (1 << 9);
	GPIOA->AFR[0] |= (1 << 10);
	GPIOA->AFR[0] &= ~(1 << 11);

	/***************Configure usart module************/
	/*Configure clock access to uart2 */
	RCC->APB1ENR |= UART2EM;
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/*Configure the transfer direction */
	USART2->CR1 = CR1_TE;

	/* Enable uart module */
	USART2->CR1 |= CR1_UE;
}

/*
 * Initialize uart2 in transfer and receiver mode.
 */
void uart2_tx_rx_init(void)
{
	/***************Configure uart gpio pin************/
	/*Enable clock access to gpioa */
	RCC->AHBENR |= IOPAEN;

	/*Set PA2 mode to alternate function mode*/
	GPIOA->MODER &= ~(1UL << 4);
	GPIOA->MODER |=  (1UL << 5);
	GPIOA->MODER &= ~(1UL << 6);
	GPIOA->MODER |=  (1UL << 7);

	/*Set PA2 alternate function typte to UART_TX (AF07) */
	GPIOA->AFR[0] |= (1 << 8);
	GPIOA->AFR[0] |= (1 << 9);
	GPIOA->AFR[0] |= (1 << 10);
	GPIOA->AFR[0] &= ~(1 << 11);

	/*Set PA3 alternate function type to UART_RX (AF07) */
	GPIOA->AFR[0] |= (1 << 12);
	GPIOA->AFR[0] |= (1 << 13);
	GPIOA->AFR[0] |= (1 << 14);
	GPIOA->AFR[0] &= ~(1 << 15);

	/***************Configure usart module************/
	/*Configure clock access to uart2 */
	RCC->APB1ENR |= UART2EM;

	/*Configure the transfer direction */
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	/* Enable transmitter/receiver */
	USART2->CR1 = CR1_TE | CR1_RE;

	/* Enable uart module */
	USART2->CR1 |= CR1_UE;
}

/*
 * Function to read from uart2.
 */
char uart2_read(void)
{
	/* Make sure receive data register is not empty */
	while(!(USART2->ISR & ISR_RXNE)) {};

	/* Return data */
	return USART2->RDR;
}

/*
 * Function to write to uart2
 */
void uart2_write(int ch)
{
	/* Make sure transmit data register is empty */
	while(!(USART2->ISR & ISR_TXE)) {};

	/* Write to transmit data  register */
	USART2->TDR = (ch & 0xFF);
}

/*
 * Function to Set baud rate
 */
void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t baudRate)
{
	USARTx->BRR = compute_uart_bd(periphClk, baudRate);
}

/*
 * Function to calculate uart baudrate.
 */
uint16_t compute_uart_bd(uint32_t periphClk, uint32_t baudRate)
{
	return ((periphClk + (baudRate/2U))/baudRate);
}

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}
