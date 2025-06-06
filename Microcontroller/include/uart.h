#ifndef UART_H
#define UART_H


#include <stdint.h>

void uart_init(unsigned int ubrr);
void uart_send(char data);
void uart_send_string(const char *str);

void uart1_init(unsigned int ubrr);              // === NEW ===
void uart1_send(char data);                      // === NEW ===
void send_oscilloscope_packet(uint8_t *samples, uint16_t length);

#endif
