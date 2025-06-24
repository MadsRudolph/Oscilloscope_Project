#ifndef UART1_COMM_H
#define UART1_COMM_H

#include <stdbool.h> // Include boolean support
#include <stdint.h>

void send_oscilloscope_packet(uint8_t *samples, uint16_t length);

extern volatile uint8_t uart1_rx_buffer[];
extern volatile uint8_t uart1_rx_index;
extern volatile uint8_t uart1_packet_ready;
extern volatile uint8_t shape;
extern volatile uint8_t amplitude;
extern volatile uint8_t frequency;
extern volatile uint8_t run_stop_flag;
extern volatile uint8_t uart1_tx_active;

#endif