// ## Dette program er skrevet af Mads Rodulph og Sigurd Hestbech Christiansen ##//
// ## Senest redigeret 04-06-2025 ##//
// ## Gennem programmet er der referet til sidetal på måden S.xxx, dette referer til sider i databladet for Atmege2560 microprocessoren ##//

#define F_CPU 16000000UL // definerer cpu frekvens
#include <avr/io.h>      // inkludere i/o funktioner
#include <stdio.h>       // inkludere sprintf
#include <stdlib.h>
#include <stdbool.h>       // inkludere bool variable
#include <avr/interrupt.h> // inkludere interrupt funktioner
#include <util/delay.h>    // inkluderer delay funktioner
#include <string.h>        // inkludere string copy
#include <stdint.h>        // inkludere uint16_t
#include "ADC.h"           // inkluderer ADC0_init og timer1_init

ISR(TIMER1_COMPB_vect) {}

int main(void)
{
    init_ADC_kanal0(); // initialisere ADC0 til autotrigger via timer1

    init_timer1(104); // indstiller sampleraten på ADC0 via parametren, brug formel: sample_rate = F_CPU / (8 * parametre)
}