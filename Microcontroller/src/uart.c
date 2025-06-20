// uart.c — UART0/UART1 low-level communication only

#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t uart1_rx_buffer[128];
volatile uint8_t uart1_rx_index = 0;
volatile uint8_t uart1_packet_ready = 0;

void uart_init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0A |= (1 << U2X0);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart1_init(unsigned int ubrr)
{
    UBRR1H = (unsigned char)(ubrr >> 8);
    UBRR1L = (unsigned char)ubrr;
    UCSR1A |= (1 << U2X1);
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

void uart_send(char data)
{
    while (!(UCSR0A & (1 << UDRE0))) ;
    UDR0 = data;
}

void uart1_send(char data)
{
    while (!(UCSR1A & (1 << UDRE1))) ;
    UDR1 = data;
}

void uart_send_string(const char *str)
{
    while (*str)
        uart_send(*str++);
}

// Send minimal protocol packet (GENERATOR or OSCILLOSCOPE)
void send_generator_packet(uint8_t active, uint8_t shape, uint8_t ampl, uint8_t freq)
{
    uart1_send(0x55);
    uart1_send(0xAA);
    uart1_send(0x00);
    uart1_send(0x0B);
    uart1_send(0x01);
    uart1_send(active);
    uart1_send(shape);
    uart1_send(ampl);
    uart1_send(freq);
    uart1_send(0x00);
    uart1_send(0x00);
}

void send_oscilloscope_packet(uint8_t *samples, uint16_t length)
{
    uart1_send(0x55);
    uart1_send(0xAA);
    uint16_t total_len = 2 + 2 + 1 + length + 2;
    uart1_send((total_len >> 8) & 0xFF);
    uart1_send(total_len & 0xFF);
    uart1_send(0x02);
    for (uint16_t i = 0; i < length; i++)
        uart1_send(samples[i]);
    uart1_send(0x00);
    uart1_send(0x00);
}

ISR(USART1_RX_vect)
{
    uint8_t byte = UDR1;
    if (uart1_rx_index < sizeof(uart1_rx_buffer))
    {
        uart1_rx_buffer[uart1_rx_index++] = byte;
        if (uart1_rx_index >= 5)
        {
            uint16_t len = (uart1_rx_buffer[2] << 8) | uart1_rx_buffer[3];
            if (uart1_rx_index == len)
                uart1_packet_ready = 1;
        }
    }
    else
    {
        uart1_rx_index = 0;
    }
}
