// ## Program developed by Mads Rodulph and Sigurd Hestbech Christiansen ##
// ## Last edited: 21-6-2025 ##
// ## This file contains UART1 communication functions ##

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART1_comm.h"
#include "UART.h"
#include "ADC.h"
#include "SPI.h"
#include "SPI_comm.h"

#define MAX_RECORD_LENGTH 1000               // max samples allowed per oscilloscope packet
extern volatile uint16_t record_length;      // current active record length
extern volatile uint16_t current_timer1_top; // timer TOP value for sampling rate
static uint8_t selected_param = 0;           // user-selected parameter: 0 = shape, 1 = amplitude, 2 = frequency

volatile uint8_t shape = 0;         // waveform shape: 0-3 (const, square, saw, sine)
volatile uint8_t amplitude = 128;   // waveform amplitude (0-255)
volatile uint8_t frequency = 100;   // waveform frequency (custom encoded)
volatile uint8_t run_stop_flag = 0; // flag toggled by BTN2 (pause/resume)
float sample_rate = 0;              // calculated sample rate in Hz

#define UART1_RX_BUFFER_SIZE 128
volatile uint8_t uart1_rx_buffer[UART1_RX_BUFFER_SIZE]; // circular RX buffer
volatile uint8_t uart1_rx_index = 0;                    // current write index in RX buffer
volatile uint8_t uart1_packet_ready = 0;                // set when complete packet is received

// UART1 RX interrupt — assembles bytes into packet buffer and checks length field
ISR(USART1_RX_vect)
{
    uint8_t byte = UDR1;

    if (uart1_rx_index < UART1_RX_BUFFER_SIZE)
    {
        uart1_rx_buffer[uart1_rx_index++] = byte;

        // once header is complete, check if full packet has arrived
        if (uart1_rx_index >= 5)
        {
            uint16_t length = (uart1_rx_buffer[2] << 8) | uart1_rx_buffer[3];
            if (uart1_rx_index == length)
                uart1_packet_ready = 1; // entire packet received
        }
    }
    else
    {
        uart1_rx_index = 0; // reset buffer if overflow occurs
    }
}

// Send a full oscilloscope data packet to LabVIEW
void send_oscilloscope_packet(uint8_t *samples, uint16_t length)
{
    

    uart1_send(0x55); // sync byte 1
    uart1_send(0xAA); // sync byte 2

    uint16_t payload_length = 2 + 2 + 1 + length + 2; // full packet size including header and checksum
    uart1_send((payload_length >> 8) & 0xFF);         // length high byte
    uart1_send(payload_length & 0xFF);                // length low byte
    uart1_send(0x02);                                 // packet type: OSCILLOSCOPE (0x02)

    for (uint16_t i = 0; i < length; i++)
    {
        while (!(UCSR1A & (1 << UDRE1))) ;
        uart1_send(samples[i]); // send all sample data (1 byte each)
    }

    uart1_send(0x00); // checksum byte 1
    uart1_send(0x00); // checksum byte 2
}

// Send current generator configuration back to LabVIEW
void send_generator_packet(uint8_t active, uint8_t shape, uint8_t ampl, uint8_t freq)
{
    uart1_send(0x55); // sync
    uart1_send(0xAA);
    uart1_send(0x00);
    uart1_send(0x0B);   // total length = 11 bytes
    uart1_send(0x01);   // packet type: GENERATOR (0x01)
    uart1_send(active); // LED select (0 = shape, 1 = amp, 2 = freq)
    uart1_send(shape);  // waveform shape
    uart1_send(ampl);   // amplitude
    uart1_send(freq);   // frequency
    uart1_send(0x00);   // checksum
    uart1_send(0x00);
}

// Parse incoming LabVIEW packet and respond accordingly
void parse_uart1_packet()
{
    if (!uart1_packet_ready)
        return;
    uart1_packet_ready = 0;

    if (uart1_rx_buffer[0] != 0x55 || uart1_rx_buffer[1] != 0xAA)
    {
        uart1_rx_index = 0; // invalid sync header
        return;
    }

    uint16_t length = (uart1_rx_buffer[2] << 8) | uart1_rx_buffer[3];
    if (length > UART1_RX_BUFFER_SIZE)
    {
        uart1_rx_index = 0; // reject oversized packet
        return;
    }

    uint8_t type = uart1_rx_buffer[4];

    switch (type)
    {
    case 0x01:
    {
        uint8_t btn = uart1_rx_buffer[5];
        uint8_t sw = uart1_rx_buffer[6];

        char msg[64];
        sprintf(msg, "BTN: %d, SW: %d\r\n", btn, sw);
        uart_send_string(msg);

        switch (btn)
        {
        case 0x00: // SEND pressed
            uart_send_string("BTN0 pressed: Send current values\r\n");
            if (selected_param == 0 && sw <= 4)
                shape = sw;
            else if (selected_param == 1 && sw <= 255)
                amplitude = sw;
            else if (selected_param == 2 && sw <= 255)
                frequency = sw;
            else
                uart_send_string("error: invalid parameter value\r\n");

            transmit_signalgenerator_data(amplitude, frequency, shape);
            uart_send_string("Current values sent to FPGA\r\n");
            break;

        case 0x01: // PARAM SELECT pressed
            selected_param = (selected_param + 1) % 3;
            uart_send_string("BTN1 pressed: Cycle parameter\r\n");
            break;

        case 0x02: // RUN/PAUSE pressed
            run_stop_flag = !run_stop_flag;
            uart_send_string(run_stop_flag ? "Paused\r\n" : "Running\r\n");
            break;

        case 0x03: // RESET pressed
            uart_send_string("BTN3 pressed: Reset\r\n");
            PORTD |= (1 << PD7);
            _delay_ms(10);
            PORTD &= ~(1 << PD7); // pulse reset to FPGA
            selected_param = 0;
            shape = 0;
            amplitude = 128;
            frequency = 1;
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

    case 0x02:
    {
        uint16_t record_len = (uart1_rx_buffer[7] << 8) | uart1_rx_buffer[8];
        if (record_len > 0 && record_len <= MAX_RECORD_LENGTH)
        {
            record_length = record_len;
            // set optimal sample rate based on record length
            sample_rate = ((11520.0f * record_length) / (7.0f + record_length)) * 0.95f; // calculate sample rate
            current_timer1_top = F_CPU / (8.0f * sample_rate);
            init_timer1(current_timer1_top); // reconfigure Timer1 for new sample rate
        }

        char msg[64];
        uart_send_string("\r\n=== Oscilloscope Configuration ===\r\n");

        snprintf(msg, sizeof(msg), "Record Length: %u samples\r\n", record_length);
        uart_send_string(msg);

        snprintf(msg, sizeof(msg), "Max Sample Rate: %.2f sps\r\n", sample_rate);
        uart_send_string(msg);

        snprintf(msg, sizeof(msg), "Timer1 TOP: %lu\r\n", (unsigned long)current_timer1_top);
        uart_send_string(msg);

        break;
    }

    case 0x04: // START packet received (used for SPI stress test)
        uart_send_string("START received: triggering SPI stress test\r\n");
        extern volatile uint8_t run_stress_test_flag;
        run_stress_test_flag = 1;
        break;

    default:
        uart_send_string("Unknown type\r\n");
        break;
    }

    uart1_rx_index = 0; // reset buffer for next packet
}
