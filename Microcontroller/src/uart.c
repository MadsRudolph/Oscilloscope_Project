// ## References to datasheet pages are marked as S.xxx for Atmega2560 ##

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "uart.h"
#include <util/delay.h>
extern volatile uint16_t record_length;
extern volatile uint16_t current_timer1_top;

#include "ADC.h" // Needed for init_timer1()
#define MAX_RECORD_LENGTH 1000

// === UART Initialization ===
void uart_init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);    // USART0 Baud rate register high byte (S.412)
    UBRR0L = (unsigned char)ubrr;           // USART0 Baud rate register low byte (S.412)
    UCSR0A |= (1 << U2X0);                  // Enable double speed (S.223)
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // Enable RX and TX (S.224)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data format (S.226)
    // No parity, 1 stop bit, asynchronous mode
}

// === Send one character ===
void uart_send(char data)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;        // Wait until buffer is ready (S.223)
    UDR0 = data; // Send data (S.212)
}

// === Send string ===
void uart_send_string(const char *str)
{
    while (*str)
        uart_send(*str++);
}

// === Send LabVIEW-formatted oscilloscope data packet ===
void send_oscilloscope_packet(uint8_t *samples, uint16_t length)
{
    uart1_send(0x55); // Sync byte 1
    uart1_send(0xAA); // Sync byte 2

    uint16_t payload_length = 1 + length + 2; // Type + Data + Checksum

    uart1_send((payload_length >> 8) & 0xFF); // Length MSB
    uart1_send(payload_length & 0xFF);        // Length LSB

    uart1_send(0x02); // Type: OSCILLOSCOPE

    uint16_t checksum = 0;
    checksum += (payload_length >> 8);        // Length MSB
    checksum += (payload_length & 0xFF);      // Length LSB
    checksum += 0x02;                         // Type byte

    for (uint16_t i = 0; i < length; i++) {
        uart1_send(samples[i]);
        checksum += samples[i];
    }

    checksum = (0x10000 - checksum) & 0xFFFF; // ZERO16 correction

    uart1_send(checksum & 0xFF);              // Checksum LSB
    uart1_send((checksum >> 8) & 0xFF);       // Checksum MSB

    _delay_ms(2); // Ensure data is sent before next packet
}


void uart_send_hex(uint8_t val)
{
    char buf[4];
    sprintf(buf, "%02X", val);
    uart_send_string(buf);
}


// === NEW === Initialize UART1 for LabVIEW communication
void uart1_init(unsigned int ubrr)
{
    UBRR1H = (unsigned char)(ubrr >> 8);
    UBRR1L = (unsigned char)ubrr;
    UCSR1A |= (1 << U2X1);
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1); // Enable RX interrupt
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

// === NEW === Send one character via UART1
void uart1_send(char data)
{
    while (!(UCSR1A & (1 << UDRE1)))
        ;
    UDR1 = data;
}

// === NEW === UART1 receive buffer
#define UART1_RX_BUFFER_SIZE 128
volatile uint8_t uart1_rx_buffer[UART1_RX_BUFFER_SIZE];
volatile uint8_t uart1_rx_index = 0;
volatile uint8_t uart1_packet_ready = 0;

// === NEW === UART1 RX ISR
ISR(USART1_RX_vect)
{
    uint8_t byte = UDR1;

    if (uart1_rx_index < UART1_RX_BUFFER_SIZE)
    {
        uart1_rx_buffer[uart1_rx_index++] = byte;

        // Once we have at least 4 bytes, check for full packet
        if (uart1_rx_index >= 5)
        {
            uint16_t length = (uart1_rx_buffer[2] << 8) | uart1_rx_buffer[3];
            if (uart1_rx_index == length)
            {
                uart1_packet_ready = 1;
            }
        }
    }
    else
    {
        uart1_rx_index = 0; // Overflow protection
    }
}

// === NEW === Packet parser
void parse_uart1_packet()
{
    if (!uart1_packet_ready)
        return;

    uart1_packet_ready = 0;

    // Validate sync
    if (uart1_rx_buffer[0] != 0x55 || uart1_rx_buffer[1] != 0xAA)
    {
        uart1_rx_index = 0;
        return;
    }

    uint16_t length = (uart1_rx_buffer[2] << 8) | uart1_rx_buffer[3];
    if (length > UART1_RX_BUFFER_SIZE)
    {
        uart1_rx_index = 0;
        return;
    }

    uint8_t type = uart1_rx_buffer[4];

    switch (type)
    {
    case 0x01: // BTN
    {
        uint8_t btn = uart1_rx_buffer[5];
        uint8_t sw = uart1_rx_buffer[6];
        uart_send_string("BTN received\r\n");
        // TODO: store btn/sw and forward via SPI if needed
        break;
    }

    case 0x02: // SEND
    {
        uint16_t sample_rate = (uart1_rx_buffer[5] << 8) | uart1_rx_buffer[6];
        uint16_t record_len = (uart1_rx_buffer[7] << 8) | uart1_rx_buffer[8];

        // Bounds checking
        if (record_len > 0 && record_len <= MAX_RECORD_LENGTH)
        {
            record_length = record_len;
        }

        if (sample_rate >= 10 && sample_rate <= 10000)
        {
            current_timer1_top = F_CPU / (8 * sample_rate);
            init_timer1(current_timer1_top); // Update Timer1 on-the-fly
        }

        uart_send_string("SEND parsed: updated record_length and sample_rate\r\n");
        break;
    }

    case 0x03: // START (e.g., for BODE)
        uart_send_string("START received\r\n");
        break;

    default:
        uart_send_string("Unknown type\r\n");
        break;
    }

    uart1_rx_index = 0;
}
