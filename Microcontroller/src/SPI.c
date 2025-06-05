// ## This file contains SPI initialization and communication functions ##
// ## References to datasheet pages are marked as S.xxx for Atmega2560 ##

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

// Send a byte via SPI as master
uint8_t master_transmit(uint8_t data)
{
    PORTB &= ~(1 << PB0); // Set SS low to activate slave
    _delay_ms(10);        // Delay to ensure slave readiness
    SPDR = data;          // Load data into SPI Data Register

    while (!(SPSR & (1 << SPIF)))
        ; // Wait for transmission to complete

    return SPDR; // Return received data (SPI is full-duplex)
}

// Initialize SPI in master mode
void master_init()
{
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2); // Set SS, MOSI, and SCK as output, on ArduinoMega2560(SS(D3), MOSI(D52), SCK(51))
    DDRB &= ~(1 << PB3);                          // Set MISO as input, on ArduinoMega2560(MISO(D50))

    SPCR |= (1 << SPI2X) | (1 << SPE) | (1 << MSTR) | (1 << DORD); // Enable SPI in master mode, (DORD = 1) makes so LSB transmits first
    SPCR &= ~(1 << SPR0) & ~(1 << SPR1);             // Set SPI clock speed to 8MHz
    SPCR &= ~(1 << CPOL) & ~(1 << CPHA);             // Sample on rising edge, transmit on falling (S.200–202)
}

// Receive a byte via SPI as slave
unsigned char slave_reciver(unsigned char data)
{
    SPDR = data; // Send dummy data to initiate clock

    while (!(SPSR & (SPIF)))
        ; // Wait for transmission to complete

    return SPDR; // Return received data
}

// Initialize SPI in slave mode
void slave_init()
{
    DDRB |= (1 << DDB3); // Set MISO as output
    SPCR |= 0b01001000;  // Enable SPI in slave mode with interrupt
    PORTB |= (1 << PB0); // Set SS high (inactive)
}
