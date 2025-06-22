// ## Program developed by Mads Rodulph and Sigurd Hestbech Christiansen ##
// ## Last edited: 20-6-2025 ##
// ## Throughout the code, page references are marked as S.xxx, referring to the Atmega2560 datasheet. ##

#ifndef F_CPU
#define F_CPU 16000000UL // Define CPU frequency
#endif

#include <avr/io.h>        // Include I/O functions
#include <stdio.h>         // Include sprintf
#include <stdbool.h>       // Include boolean support
#include <avr/interrupt.h> // Include interrupt handling
#include <stdint.h>        // Include fixed width integer types
#include <util/delay.h>    // Includes delay function
#include "ADC.h"           // Include ADC initialization functions
#include "SPI.h"           // Include SPI init functions
#include "UART.h"          // Includes uart init functions
#include "UART1_comm.h"    // Includes uart1 communication functions
#include "SPI_comm.h"      // Include SPI communication functions

// Declare parse_uart1_packet prototype
void parse_uart1_packet(void);

// Define maximum buffer size for dynamic record length
#define MAX_RECORD_LENGTH 1000
volatile uint8_t buffer_a[MAX_RECORD_LENGTH]; // triple buffer A
volatile uint8_t buffer_b[MAX_RECORD_LENGTH]; // triple buffer B
volatile uint8_t buffer_c[MAX_RECORD_LENGTH]; // triple buffer C
volatile uint8_t *active_buffer = buffer_a;   // buffer we write into
volatile uint8_t *send_buffer = buffer_b;     // buffer we send from
volatile uint8_t *standby_buffer = buffer_c;  // next available buffer
volatile bool buffer_in_use = false;          // indicates if buffer is locked for transmission
volatile uint16_t current_timer1_top = 200;   // ADC sampling rate control (OCR1A value)
volatile uint16_t record_length = 100;        // number of samples per transmission

// ADC control flags
volatile uint16_t sample_index = 0; // current sample index into active buffer
volatile bool buffer_ready = false; // signals that a full buffer is ready to send

// BTN/SW state
volatile uint8_t btn = 0;
volatile uint8_t sw = 0;
volatile uint8_t run_stress_test_flag = 0; // triggered by LabVIEW START (BTN3)

// Enumeration for program states
enum states
{
    state_init,
    state_Run,
    state_Stop,
    state_SPITest
};
static enum states state = state_init;

// Interrupt Service Routine (ISR) for TIMER1 Compare Match B (see ADC.c for more info)
ISR(TIMER1_COMPB_vect)
{
    if (sample_index < record_length)
    {
        active_buffer[sample_index++] = ADCH;
    }
    else if (!buffer_in_use)
    {
        cli();
        buffer_ready = true;
        buffer_in_use = true;

        // rotate buffers: standby → send → active
        uint8_t *temp = (uint8_t *)standby_buffer;
        standby_buffer = send_buffer;
        send_buffer = active_buffer;
        active_buffer = temp;

        sample_index = 0;
        sei();
    }
    // if buffer is still in use, skip storing until main clears it
}

int main(void)
{
    while (1)
    {
        parse_uart1_packet(); // check for UART1 commands from LabVIEW

        switch (state)
        {
        case state_init:

            init_ADC_kanal0();                           // configure ADC0 with auto-trigger via Timer1
            init_timer1(current_timer1_top);             // configure Timer1 for ADC sampling
            master_init();                               // initialize SPI as master
            uart_init(16);                               // init UART0 (115200 baud)
            uart1_init(16);                              // init UART1 (115200 baud, for LabVIEW)
            uart_send_string("System initialized.\r\n"); // confirm system boot
            DDRD |= (1 << PD7);                          // configure PD7 as output (FPGA reset)
            PORTD &= ~(1 << PD7);                        // ensure reset line is low

            sei();             // enable global interrupts
            state = state_Run; // move to Run state
            break;

        case state_Run:

            if (run_stress_test_flag)
            {
                run_stress_test_flag = 0;
                state = state_SPITest;
            }

            if (buffer_ready)
            {
                // Disable interrupts while accessing shared buffers, to prevent them from being modified during transmission
                // this is necessary to ensure data integrity as the ISR may write to the buffer while we are sending it
                cli();
                buffer_ready = false;
                buffer_in_use = false;
                sei();

                // send data to LabVIEW
                send_oscilloscope_packet((uint8_t *)send_buffer, record_length);
                _delay_ms(9); // wait for UART to complete before sending debug text

                uart_send_string("\rSample: ");
                char buf[16];
                sprintf(buf, "%02X      ", send_buffer[0]);
                uart_send_string(buf);
            }

            if (run_stop_flag)
            {
                state = state_Stop;
            }
            break;

        case state_Stop:
            if (!(run_stop_flag))
            {
                state = state_Run; // resume sampling when unpaused
            }
            break;

        case state_SPITest:
            spi_stress_test_10000_packets(); // run SPI communication stress test
            state = state_Run;
            break;

        default:
            break;
        }
    }
}
