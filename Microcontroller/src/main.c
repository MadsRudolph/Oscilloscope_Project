// ## Program developed by Mads Rodulph and Sigurd Hestbech Christiansen ##
// ## Last edited: 2025-06-04 ##
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

#include "ADC.h" // Include ADC initialization functions
#include "SPI.h" // Include SPI communication functions

// Enumeration for program states
enum states
{
    state_init,
    state_transmit_SPI
};
enum states state = state_init;

// Interrupt Service Routine (ISR) for TIMER1 Compare Match B (see ADC.c for more info)
ISR(TIMER1_COMPB_vect) {}

int main(void)
{
    while (1)
    {
        switch (state)
        {
        case state_init:
            // init_ADC_kanal0(); // Uncomment to initialize ADC0 with auto-trigger via Timer1
            // init_timer1(200); // Set ADC sample rate using Timer1, see formula: sample_rate = F_CPU / (8 * parameter)
            master_init(); // Initialize SPI master (see SPI.c for details)
            state = state_transmit_SPI;
            break;

        case state_transmit_SPI:
            master_transmit();   // Send data via SPI (add parameter if needed)
            PORTB |= (1 << PB0); // Set SS high to deactivate SPI slave
            break;

        default:
            break;
        }
    }
}
