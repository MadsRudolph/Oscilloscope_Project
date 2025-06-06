#include <avr/interrupt.h> // Include interrupt handling

// Initialize ADC channel 0 (Analog input pin A0 on Arduino)
void init_ADC_kanal0()
{
    ADMUX = (1 << REFS0); // Set reference voltage to AVcc (5V), see S.289
                          // MUX bits = 0 → selects ADC0 input channel (S.290 Table 26-4)

    ADCSRA |= (1 << ADEN); // Enable ADC (S.292)
    ADCSRA |= (1 << ADSC); // Start initial conversion; first sample takes longer (S.293)

    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set prescaler to 128 → 125kHz ADC clock at 16MHz CPU (S.293)
                                                          // ADC takes 13 cycles to convert → 125kHz / 13 = ~9.6kHz max sample rate

    ADCSRA |= (1 << ADIE);  // Enable ADC interrupt (S.293)
    ADCSRA |= (1 << ADATE); // Enable auto-triggering (S.293)

    ADCSRB |= (1 << ADTS2) | (1 << ADTS0); // Set auto-trigger source to Timer1 Compare Match B (S.295)
}

// Initialize Timer1 for setting ADC sample rate
void init_timer1(int top_value)
{
    TCCR1A = 0; // Clear Timer1A register to avoid conflicts
    TCNT1 = 0;  // Reset Timer1 counter

    TCCR1B |= (1 << WGM12) | (1 << CS11); // Set CTC mode with prescaler 8 (S.148, S.161)
    OCR1A = top_value;                    // Writes to OCR1A to set sample rate, use formula: sample_rate = (F_CPU = 16MHz / 8 / top_value)

    TIMSK1 |= (1 << OCIE1B); // Enable Timer1 Compare Match B interrupt (S.166)
}

// ISR(TIMER1_COMPB_vect) must be added in your main program to prevent crashes
