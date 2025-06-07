// ## Program developed by Mads Rodulph and Sigurd Hestbech Christiansen ##
// ## Last edited: 2025-06-06 ##
// ## Throughout the code, page references are marked as S.xxx, referring to the Atmega2560 datasheet. ##

#define F_CPU 16000000UL // Define CPU frequency

#include <avr/io.h> // Include I/O functions
#include <stdio.h>  // Include sprintf
#include <stdlib.h>
#include <stdbool.h>       // Include boolean support
#include <avr/interrupt.h> // Include interrupt handling
#include <util/delay.h>    // Include delay functions
#include <string.h>        // Include string handling
#include <stdint.h>        // Include fixed width integer types

#include "ADC.h"  // Include ADC initialization functions
#include "SPI.h"  // Include SPI communication functions
#include "uart.h" // Includes uart functions

// === NEW === Define maximum buffer size for dynamic record length
#define MAX_RECORD_LENGTH 1000
volatile uint8_t adc_samples[MAX_RECORD_LENGTH]; // support dynamic size
volatile uint16_t record_length = 100;           // default, can be changed by SEND

// === NEW === ADC control flags
volatile uint16_t sample_index = 0;
volatile bool buffer_ready = false;

// Enumeration for program states
enum states
{
    state_init,
    state_transmit_SPI,
    state_transmit_UART
};
static enum states state = state_init;

// === NEW === Current sample rate control
volatile uint16_t current_timer1_top = 200;

// Interrupt Service Routine (ISR) for TIMER1 Compare Match B (see ADC.c for more info)
ISR(TIMER1_COMPB_vect)
{
    if (sample_index < record_length)
    {
        adc_samples[sample_index++] = ADCH; // 8-bit ADC value from ADC0
    }
    else
    {
        buffer_ready = true;
        sample_index = 0;
    }
    ADCSRA |= (1 << ADSC); // Restart ADC conversion
}

int main(void)
{
    while (1)
    {
        // === NEW === Parse UART1 commands from LabVIEW
        parse_uart1_packet();

        switch (state)
        {
        case state_init:

            init_ADC_kanal0();                           // Uncomment to initialize ADC0 with auto-trigger via Timer1 ***mayby make it so ADC refrencec is 3.3V this is not the case at the moment
            init_timer1(current_timer1_top);             // Set ADC sample rate(10kHz) using Timer1, use formula: sample_rate = F_CPU / (8 * parameter)
            master_init();                               // Initialize SPI master (see SPI.c for details)
            uart_init(16);                               // Set a unsigned integer in the parameter to choose Baud rate (parameter(16) = Baud rate(115200)). Look up uart.c for more info
            uart1_init(16);                              // === NEW === Initialize UART1 for LabVIEW (115200 baud, U2X1 enabled)
            uart_send_string("System initialized.\r\n"); // === NEW === Debug message via UART0

            sei();                       // === NEW === Enable global interrupts
            state = state_transmit_UART; // Changes state

            break;

        case state_transmit_SPI:

            master_transmit(170); // Send data via SPI (0b10101010 = 0xAA)
            _delay_ms(100);       // Short delay to clearly observe SS/SCK on scope
            master_transmit(85);  // Send data via SPI (0b01010101 = 0x55)
            _delay_ms(100);       // Short delay to clearly observe SS/SCK on scope

            break;

        case state_transmit_UART:

            // === NEW === If ADC buffer is ready, send UART packet to LabVIEW
            if (buffer_ready)
            {
                send_oscilloscope_packet((uint8_t *)adc_samples, record_length);
                buffer_ready = false;

                _delay_ms(100); // Short delay to avoid flooding LabVIEW
                uart_send_string("\rSample: ");
                char buf[16];
                sprintf(buf, "%02X      ", adc_samples[0]); // Add extra spaces to clear previous output
                uart_send_string(buf);
            }

            break;

        default:
            break;
        }
    }
}
