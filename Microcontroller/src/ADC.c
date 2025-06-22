// ## Program developed by Mads Rodulph and Sigurd Hestbech Christiansen ##
// ## Last edited: 21-6-2025 ##
// ## This file contains ADC and autotrigger initialization functions ##
// ## References to datasheet pages are marked as S.xxx for Atmega2560 ##

#include "ADC.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Initialize ADC channel 0 (A0) with auto-trigger from Timer1 Compare Match B
void init_ADC_kanal0()
{
    ADMUX = (1 << ADLAR); // Use external voltage reffrence on AREF pin, left-adjust result (8-bit in ADCH) (S.289-290 & S.294)
    // MUX[3:0] = 0000 → ADC0 selected (S.290 Table 26-4)

    // information on ADCSRA at S.292
    ADCSRA = (1 << ADEN) |  // Enable ADC
             (1 << ADATE) | // Auto Trigger Enable
             (1 << ADIE) |  // Enable ADC interrupt (ISR will clear interrupt flag)
             (1 << ADSC) |  // Start first conversion
             (1 << ADPS2);  // Prescaler = 16 (ADC clock = 1MHz @ 16MHz(F_CPU))

    ADCSRB = (1 << ADTS2) | (1 << ADTS0); // Auto Trigger Source = Timer1 Compare Match B (ADTS[2:0] = 101)

    DIDR0 = (1 << ADC0D); // Disable digital input on ADC0 (S.295)
}

// ADC ISR to acknowledge interrupt only
ISR(ADC_vect)
{
    // Empty ISR to clear interrupt flag (sampling is handled in TIMER1_COMPB_vect)
}

// Initialize Timer1 to trigger ADC at given sampling rate
void init_timer1(int top_value)
{
    TCCR1A = 0; // Clear Timer1 control A — avoid PWM
    TCNT1 = 0;  // Reset Timer1 counter

    TCCR1B |= (1 << WGM12); // CTC mode (TOP = OCR1A) — S.148, S.161
    TCCR1B |= (1 << CS11);  // Prescaler = 8 — S.161

    TIMSK1 |= (1 << OCIE1B); // Enable Timer1 Compare Match B interrupt — S.166

    OCR1A = top_value; // Sets TOP value for sampling frequency
                       // Sampling rate = F_CPU / (8 * top_value)
    OCR1B = top_value; // Used to trigger ADC
}
