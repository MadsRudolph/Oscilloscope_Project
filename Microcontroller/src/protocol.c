// protocol.c — Parses UART1 LabVIEW packets

#include "protocol.h"
#include "generator.h"
#include "uart.h"
#include "ADC.h"
#include "SPI.h"
#include <stdio.h>

#define MAX_RECORD_LENGTH 1000

extern volatile uint16_t record_length;
extern volatile uint16_t current_timer1_top;
extern volatile uint8_t run_stress_test_flag;
extern volatile uint8_t uart1_rx_buffer[];
extern volatile uint8_t uart1_rx_index;
extern volatile uint8_t uart1_packet_ready;

void parse_uart1_packet()
{
    if (!uart1_packet_ready) return;
    uart1_packet_ready = 0;

    if (uart1_rx_buffer[0] != 0x55 || uart1_rx_buffer[1] != 0xAA)
    {
        uart1_rx_index = 0;
        return;
    }

    uint16_t length = (uart1_rx_buffer[2] << 8) | uart1_rx_buffer[3];
    if (length > MAX_RECORD_LENGTH)
    {
        uart1_rx_index = 0;
        return;
    }

    uint8_t type = uart1_rx_buffer[4];

    switch (type)
    {
    case 0x01:
        generator_handle_btn(uart1_rx_buffer[5], uart1_rx_buffer[6]);
        break;

    case 0x02:
    {
        uint16_t sample_rate = (uart1_rx_buffer[5] << 8) | uart1_rx_buffer[6];
        uint16_t rec_len = (uart1_rx_buffer[7] << 8) | uart1_rx_buffer[8];
        if (rec_len > 0 && rec_len <= MAX_RECORD_LENGTH)
            record_length = rec_len;
        if (sample_rate >= 10 && sample_rate <= 10000)
        {
            current_timer1_top = F_CPU / (8 * sample_rate);
            init_timer1(current_timer1_top);
        }
        break;
    }

    case 0x04:
        run_stress_test_flag = 1;
        break;

    default:
        uart_send_string("Unknown UART1 packet type\r\n");
        break;
    }

    uart1_rx_index = 0;
}
