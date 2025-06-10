#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init(unsigned int ubrr);
void uart_send(char data);
void uart_send_string(const char *str);

void uart1_init(unsigned int ubrr);              
void uart1_send(char data);                      
void send_oscilloscope_packet(uint8_t *samples, uint16_t length);

extern volatile uint8_t uart1_rx_buffer[];
extern volatile uint8_t uart1_rx_index;
extern volatile uint8_t uart1_packet_ready;

#endif
