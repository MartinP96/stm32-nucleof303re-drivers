/* UART Driver for NUCLEO F303RE BOARD (STM32F303RE MCU).
 *
 * For communication we are using UART2 which is connected to
 * ST LINK module on NUCLEO BOARD.
 *
 * Author: Martin P.
 * Date: 30.07.2022
 */


#ifndef _UART_H_
#define _UART_H_

#include "uart.h"
#include <stdio.h>
#include <stdint.h>
#include "stm32f3xx.h"

#define SYS_FREQ 8000000// Default system clock for STM32F3
#define APB1_CLK SYS_FREQ
#define UART_BAUDRATE 115200 // Desured BAUDRATE

// Register
#define IOPAEN (1U<<17)
#define UART2EM (1U << 17)
#define CR1_TE (1U << 3)
#define CR1_RE (1U << 2)
#define CR1_UE (1U << 0)
#define ISR_TXE (1U << 7)
#define ISR_RXNE (1U << 5)

// Function definitions
void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphClk, uint32_t baudRate);
uint16_t compute_uart_bd(uint32_t periphClk, uint32_t baudRate);
void uart2_tx_init(void);
void uart2_tx_rx_init(void);
void uart2_write(int ch);
char uart2_read(void);
int __io_putchar(int ch);

#endif
