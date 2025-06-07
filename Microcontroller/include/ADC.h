#ifndef ADC_H
#define ADC_H

// Initializes ADC on channel 0 (A0) with Timer1 Compare Match B trigger
void init_ADC_kanal0(void);

// Initializes Timer1 to trigger ADC sampling at desired rate
void init_timer1(int top_value);

#endif
