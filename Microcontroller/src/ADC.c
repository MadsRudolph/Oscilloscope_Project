#include <avr/io.h>
#include <avr/interrupt.h> // Include interrupt handling

// Initialize ADC channel 0 (Analog input pin A0 on Arduino)
void init_ADC_kanal0()
{
    ADMUX = (1 << REFS0) | (1 << ADLAR); // AVcc reference + left adjust result
                          // MUX[3:0] = 0000 → ADC0 selected — S.290 Table 26-4

    ADCSRA |= (1 << ADEN); // Enable ADC — S.292
    ADCSRA |= (1 << ADSC); // Start first conversion (warm-up) — S.293

    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler = 128 → 125kHz ADC clock @ 16MHz — S.293

    //ADCSRA |= (1 << ADIE);  // Enable ADC interrupt — S.293
    ADCSRA |= (1 << ADATE); // Enable auto-trigger — S.293

    ADCSRB |= (1 << ADTS2) | (1 << ADTS0); // Trigger source = Timer1 Compare Match B (ADTS[2:0] = 101) — S.295
}

ISR(ADC_vect)
{
    // do nothing, just prevent reset
}


// Initialize Timer1 to trigger ADC at specified rate
void init_timer1(int top_value)
{
    TCCR1A = 0;  // Clear Timer1 control A — avoid PWM
    TCNT1 = 0;   // Reset Timer1 counter

    TCCR1B |= (1 << WGM12); // CTC mode (TOP = OCR1A) — S.148, S.161
    TCCR1B |= (1 << CS11);  // Prescaler = 8 — S.161

    OCR1A = top_value;      // Sets TOP value for sampling frequency
                            // Sampling rate = F_CPU / (8 * top_value)

    TIMSK1 |= (1 << OCIE1B); // Enable Timer1 Compare Match B interrupt — S.166
}
