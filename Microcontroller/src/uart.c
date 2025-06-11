// ## This file contains UART initialization and communication functions ##
// ## References to datasheet pages are marked as S.xxx for Atmega2560 ##

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>
#include "uart.h"
#include "ADC.h" // Needed for init_timer1()
#define MAX_RECORD_LENGTH 1000
extern volatile uint16_t record_length;
extern volatile uint16_t current_timer1_top;
static uint8_t selected_param = 0; // 0 = shape, 1 = amplitude, 2 = frequency
volatile uint8_t shape = 0;
volatile uint8_t amplitude = 128;
volatile uint8_t frequency = 100;

void uart_init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);                  // USART0 Baud rate register high byte (S.412)
    UBRR0L = (unsigned char)ubrr;                         // USART0 Baud rate register low byte (S.412)
    UCSR0A |= (1 << U2X0);                                // Enable double speed (S.223)
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); // Enable RX, TX, and RX interrupt (S.224)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);               // 8-bit data format (S.226)
    // No parity (UPM00 & UUPM01 = 0), 1 stopbit (USBS0 = 0), async mode (UMSEL00 & UMSEL01 = 0) (S.225-226)
    // One complete data cycle is 1 start-bit followed by 8 data-bit's followed by 1 stop-bit.
}

// Send one character via UART. Exsampel from atmega2560 datasheet on page 212
void uart_send(char data)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;        // Wait until UDRE0 is high meaning buffer is clear an ready to be written (S.223)
    UDR0 = data; // udates data into buffer and sends data (S.212)
}

// Send string via UART
void uart_send_string(const char *str)
{
    while (*str)
        uart_send(*str++);
}

// Send LabVIEW-formatted oscilloscope data packet
void send_oscilloscope_packet(uint8_t *samples, uint16_t length)
{
    uart1_send(0x55); // Sync byte 1
    uart1_send(0xAA); // Sync byte 2

    uint16_t payload_length = 2 + 2 + 1 + length + 2; // Type + Data + Checksum

    uart1_send((payload_length >> 8) & 0xFF); // Length MSB
    uart1_send(payload_length & 0xFF);        // Length LSB // er det nødvænidgt at & 0xFF?

    uart1_send(0x02); // Type: OSCILLOSCOPE

    for (uint16_t i = 0; i < length; i++)
    {
        uart1_send(samples[i]);
        // checksum += samples[i];
    }
    uart1_send(0x00); // Checksum LSB
    uart1_send(0x00); // Checksum MSB
}

// Initialize UART1 for LabVIEW communication
void uart1_init(unsigned int ubrr)
{
    UBRR1H = (unsigned char)(ubrr >> 8);
    UBRR1L = (unsigned char)ubrr;
    UCSR1A |= (1 << U2X1);
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1); // Enable RX interrupt
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
}

// Send one character via UART1
void uart1_send(char data)
{
    while (!(UCSR1A & (1 << UDRE1)))
        ;
    UDR1 = data;
}

// UART1 receive buffer
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

void send_generator_packet(uint8_t active, uint8_t shape, uint8_t ampl, uint8_t freq)
{
    uart1_send(0x55);
    uart1_send(0xAA);
    uart1_send(0x00);   // Length MSB
    uart1_send(0x0B);   // Length LSB (11 bytes total)
    uart1_send(0x01);   // Type: GENERATOR
    uart1_send(active); // Active indicator
    uart1_send(shape);  // Shape
    uart1_send(ampl);   // Amplitude
    uart1_send(freq);   // Frequency
    uart1_send(0x00);   // Checksum LSB
    uart1_send(0x00);   // Checksum MSB
}

// Packet parser
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

    // Vaildite size of length
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

        char msg[64];
        sprintf(msg, "BTN: %d, SW: %d\r\n", btn, sw);
        uart_send_string(msg);

        switch (btn)
        {
        case 0x00:
            uart_send_string("BTN0 pressed: Send current values\r\n");
            // Possibly send values to FPGA here too
            break;

        case 0x01:
            uart_send_string("BTN1 pressed: Cycle parameter\r\n");
            selected_param = (selected_param + 1) % 3;
            break;

        case 0x02:
            uart_send_string("BTN2 pressed: Increase value\r\n");
            if (selected_param == 0 && shape < 3)
                shape++;
            else if (selected_param == 1 && amplitude < 255)
                amplitude++;
            else if (selected_param == 2 && frequency < 255)
                frequency++;
            break;

        case 0x03:
            uart_send_string("BTN3 pressed: Decrease value\r\n");
            if (selected_param == 0 && shape > 0)
                shape--;
            else if (selected_param == 1 && amplitude > 0)
                amplitude--;
            else if (selected_param == 2 && frequency > 0)
                frequency--;
            break;

        default:
            uart_send_string("Unknown BTN value\r\n");
            break;
        }

        // Always send updated values to LabVIEW
        send_generator_packet(selected_param, shape, amplitude, frequency);
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
