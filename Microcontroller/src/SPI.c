// ## Program developed by Mads Rodulph and Sigurd Hestbech Christiansen ##
// ## Last edited: 21-6-2025 ##
// ## This file contains SPI initialization and transmission functions ##
// ## References to datasheet pages are marked as S.xxx for Atmega2560 ##

#include "SPI.h"
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include <util/delay.h>

// Send a byte via SPI as master
void master_transmit(uint8_t data)
{
    PORTB &= ~(1 << PB0); // Set SS low to activate slave
    SPDR = data;          // Load data into SPI Data Register

    while (!(SPSR & (1 << SPIF)))
        ;                // Wait for transmission to complete
    PORTB |= (1 << PB0); // Set SS high to deactivate slave
    // Transmission complete, slave deselected
}

// Initialize SPI in master mode
void master_init()
{
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2); // Set SS, MOSI, and SCK as output, on ArduinoMega2560(MOSI(D51), SCK(52), SS(D53))
    DDRB &= ~(1 << PB3);                          // Set MISO as input, on ArduinoMega2560(MISO(D50))
    PORTB |= (1 << PB0);                          // Set SS high (inactive)

    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << DORD); // Enable SPI in master mode, (DORD = 1) makes so LSB transmits first
    SPCR |= (1 << SPI2X) | (1 << SPR1);             // Set SCK clock rate too fck/32 (S.203), 500kHz with F_CPU = 16 MHz(500 kilo baud)
    SPCR &= ~((1 << CPOL) | (1 << CPHA));           // Sample on rising edge, transmit on falling (S.200–202)
    // SPI mode = 0, LSB first, double speed, clock polarity and phase = 0
}

// Receive a byte via SPI as slave
unsigned char slave_reciver(unsigned char data)
{
    SPDR = data; // Send dummy data to initiate clock

    while (!(SPSR & (1 << SPIF)))
        ; // Wait for transmission to complete

    return SPDR; // Return received data
    // Data received from SPI master
}

// Initialize SPI in slave mode
void slave_init()
{
    DDRB |= (1 << DDB3);              // Set MISO as output
    SPCR |= (1 << SPE) | (1 << DORD); // Enable SPI in slave mode, LSB first
}
