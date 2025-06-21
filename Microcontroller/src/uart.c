// ## This file contains UART initialization and communication functions ##
// ## References to datasheet pages are marked as S.xxx for Atmega2560 ##

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
#include "ADC.h"
#include "SPI.h"

// === Shared variables (declared extern here) ===
#define MAX_RECORD_LENGTH 1000
extern volatile uint16_t record_length;
extern volatile uint16_t current_timer1_top;
static uint8_t selected_param = 0; // 0 = shape, 1 = amplitude, 2 = frequency

// === Generator signal settings ===
volatile uint8_t shape = 0;
volatile uint8_t amplitude = 128;
volatile uint8_t frequency = 100;
volatile uint8_t run_stop_flag = 0;
float sample_rate = 0;

// === UART0: Debug UART ===
void uart_init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0A |= (1 << U2X0); // Double speed mode
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); // RX, TX, and interrupt enable
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data format
}

// UART0: Send single byte (used for debug prints)
void uart_send(char data)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

// UART0: Send string
void uart_send_string(const char *str)
{
    while (*str)
        uart_send(*str++);
}

// === LabVIEW UART1: Data and command communication ===

void uart1_init(unsigned int ubrr)
{
    UBRR1H = (unsigned char)(ubrr >> 8);
    UBRR1L = (unsigned char)ubrr;
    UCSR1A |= (1 << U2X1); // Double speed mode
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10); // 8-bit
}

// UART1: Send single byte (used for LabVIEW packets)
void uart1_send(char data)
{
    while (!(UCSR1A & (1 << UDRE1)));
    UDR1 = data;
}

// UART1 RX buffer
#define UART1_RX_BUFFER_SIZE 128
volatile uint8_t uart1_rx_buffer[UART1_RX_BUFFER_SIZE];
volatile uint8_t uart1_rx_index = 0;
volatile uint8_t uart1_packet_ready = 0;

// UART1 RX interrupt handler — buffers incoming packet from LabVIEW
ISR(USART1_RX_vect)
{
    uint8_t byte = UDR1;

    if (uart1_rx_index < UART1_RX_BUFFER_SIZE) {
        uart1_rx_buffer[uart1_rx_index++] = byte;

        if (uart1_rx_index >= 5) {
            uint16_t length = (uart1_rx_buffer[2] << 8) | uart1_rx_buffer[3];
            if (uart1_rx_index == length)
                uart1_packet_ready = 1;
        }
    } else {
        uart1_rx_index = 0; // Overflow protection
    }
}

// === Main Oscilloscope Data Transmission Function ===
// Sends a full packet to LabVIEW including header, type, data, and dummy checksum
void send_oscilloscope_packet(uint8_t *samples, uint16_t length)
{
    TIMSK1 &= ~(1 << OCIE1B); // Disable ADC interrupts during send

    uart1_send(0x55); // Sync byte 1
    uart1_send(0xAA); // Sync byte 2

    uint16_t payload_length = 2 + 2 + 1 + length + 2;
    uart1_send((payload_length >> 8) & 0xFF); // Length MSB
    uart1_send(payload_length & 0xFF);        // Length LSB
    uart1_send(0x02);                         // Packet type: OSCILLOSCOPE

    for (uint16_t i = 0; i < length; i++)
        uart1_send(samples[i]); // Sample data bytes

    uart1_send(0x00); // Dummy checksum LSB
    uart1_send(0x00); // Dummy checksum MSB

    while (!(UCSR1A & (1 << TXC1))); // Wait until final byte shifts out
    UCSR1A |= (1 << TXC1); // Clear TXC1

    TIMSK1 |= (1 << OCIE1B); // Re-enable ADC
}

// === Send generator config to LabVIEW (shape, freq, amp) ===
void send_generator_packet(uint8_t active, uint8_t shape, uint8_t ampl, uint8_t freq)
{
    uart1_send(0x55);
    uart1_send(0xAA);
    uart1_send(0x00);
    uart1_send(0x0B); // 11 bytes
    uart1_send(0x01); // Type: GENERATOR
    uart1_send(active);
    uart1_send(shape);
    uart1_send(ampl);
    uart1_send(freq);
    uart1_send(0x00); // Dummy checksum
    uart1_send(0x00);
}

// Sends sampling config back to LabVIEW (used after 'SEND' command)
void send_scope_parameters_to_labview(uint16_t record_len, uint16_t s_rate)
{
    uart1_send(0x55);
    uart1_send(0xAA);
    uart1_send(0x00);
    uart1_send(0x09); // 9 bytes total
    uart1_send(0x02); // Type: OSCILLOSCOPE
    uart1_send((s_rate >> 8) & 0xFF);
    uart1_send(s_rate & 0xFF);
    uart1_send((record_len >> 8) & 0xFF);
    uart1_send(record_len & 0xFF);
    uart1_send(0x00);
    uart1_send(0x00);
}

// === Main LabVIEW Packet Parser ===
void parse_uart1_packet()
{
    if (!uart1_packet_ready) return;
    uart1_packet_ready = 0;

    // Validate sync
    if (uart1_rx_buffer[0] != 0x55 || uart1_rx_buffer[1] != 0xAA) {
        uart1_rx_index = 0;
        return;
    }

    uint16_t length = (uart1_rx_buffer[2] << 8) | uart1_rx_buffer[3];
    if (length > UART1_RX_BUFFER_SIZE) {
        uart1_rx_index = 0;
        return;
    }

    uint8_t type = uart1_rx_buffer[4];

    switch (type) {
    case 0x01: { // Generator tab
        uint8_t btn = uart1_rx_buffer[5];
        uint8_t sw = uart1_rx_buffer[6];

        char msg[64];
        sprintf(msg, "BTN: %d, SW: %d\r\n", btn, sw);
        uart_send_string(msg);

        switch (btn) {
        case 0x00: // SEND
            uart_send_string("BTN0 pressed: Send current values\r\n");
            if (selected_param == 0 && sw <= 4) shape = sw;
            else if (selected_param == 1 && sw <= 255) amplitude = sw;
            else if (selected_param == 2 && sw <= 255) frequency = sw;
            else uart_send_string("error: invalid parameter value\r\n");

            transmit_signalgenerator_data(amplitude, frequency, shape);
            uart_send_string("Current values sent to FPGA\r\n");
            break;

        case 0x01:
            selected_param = (selected_param + 1) % 3;
            uart_send_string("BTN1 pressed: Cycle parameter\r\n");
            break;

        case 0x02:
            run_stop_flag = !run_stop_flag;
            uart_send_string(run_stop_flag ? "Paused\r\n" : "Running\r\n");
            break;

        case 0x03:
            uart_send_string("BTN3 pressed: Reset\r\n");
            PORTD |= (1 << PD7); _delay_ms(10); PORTD &= ~(1 << PD7); // Pulse PD7
            selected_param = 0; shape = 0; amplitude = 128; frequency = 1;
            transmit_signalgenerator_data(amplitude, frequency, shape);
            uart_send_string("Reset values sent to FPGA\r\n");
            break;

        default:
            uart_send_string("Unknown BTN value\r\n");
            break;
        }

        send_generator_packet(selected_param, shape, amplitude, frequency);
        break;
    }

    case 0x02: { // SEND in Oscilloscope tab
        uint16_t record_len = (uart1_rx_buffer[7] << 8) | uart1_rx_buffer[8];
        if (record_len > 0 && record_len <= MAX_RECORD_LENGTH) {
            record_length = record_len;

            // === Max sample rate based on UART1 throughput constraint ===
            sample_rate = ((11520.0f * record_length) / (7.0f + record_length)) * 0.95f;
            current_timer1_top = F_CPU / (8.0f * sample_rate);
            init_timer1(current_timer1_top);
        }

        char msg[96];
        snprintf(msg, sizeof(msg),
                 "\r\n=== Oscilloscope Configuration ===\r\n"
                 "Record Length: %u samples\r\n"
                 "Max Sample Rate: %.2f sps\r\n"
                 "Timer1 TOP: %lu\r\n",
                 record_length, sample_rate, (unsigned long)current_timer1_top);
        uart_send_string(msg);
        break;
    }

    case 0x04:
        uart_send_string("START received: triggering SPI stress test\r\n");
        extern volatile uint8_t run_stress_test_flag;
        run_stress_test_flag = 1;
        break;

    default:
        uart_send_string("Unknown type\r\n");
        break;
    }

    uart1_rx_index = 0;
}
