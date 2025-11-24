#pragma once

#include <msp430.h>
#include <stdint.h>

#define SMCLK_11500 0
#define SMCLK_9600 1
#define ACLK_9600 2

#define UART_MODE SMCLK_11500

void send_uca0_data(uint8_t data);
void init_uart();
void init_uart_gpio();
