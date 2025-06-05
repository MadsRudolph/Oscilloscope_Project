#ifndef UART_H
#define UART_H

#include <stdint.h>

// UART buffer and flags
extern volatile char uart_buffer[32];
extern volatile uint8_t uart_index;
extern volatile uint8_t uart_rx_flag;

// Function declarations
void uart_init(unsigned int ubrr);
void uart_send(char data);
void uart_send_string(const char* str);
void process_uart_command(void);

// Temporary PWM values via UART
extern uint8_t temp_min_pwm, temp_max_pwm;
extern uint8_t new_pwm_values_received;

#endif
