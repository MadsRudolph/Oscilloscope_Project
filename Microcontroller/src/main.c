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
// ISR(TIMER1_COMPB_vect) {}

int main(void)
{
    while (1)
    {
        switch (state)
        {
        case state_init:
            // init_ADC_kanal0(); // Uncomment to initialize ADC0 with auto-trigger via Timer1 ***mayby make it so ADC refrencec is 3.3V this is not the case at the moment
            // init_timer1(200); // Set ADC sample rate using Timer1, see formula: sample_rate = F_CPU / (8 * parameter)
            master_init(); // Initialize SPI master (see SPI.c for details)
            state = state_transmit_SPI;
            break;

        case state_transmit_SPI:
            // Repeated SPI transfers with visible SS activity on oscilloscope
            while (1)
            {
                master_transmit(170); // Send data via SPI (0b10101010 = 0xAA)
                _delay_ms(100);       // Short delay to clearly observe SS/SCK on scope
                master_transmit(85);  // Send data via SPI (0b01010101 = 0x55)
                _delay_ms(100);       // Short delay to clearly observe SS/SCK on scope
            }
            break;

        default:
            break;
        }
    }
}
