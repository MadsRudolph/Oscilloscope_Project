// ## This file contains SPI initialization and communication functions ##
// ## References to datasheet pages are marked as S.xxx for Atmega2560 ##

#include "SPI.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "uart.h"

// Send a byte via SPI as master
void master_transmit(uint8_t data)
{
    PORTB &= ~(1 << PB0); // Set SS low to activate slave
    SPDR = data;          // Load data into SPI Data Register

    while (!(SPSR & (1 << SPIF)))
        ;                // Wait for transmission to complete
    PORTB |= (1 << PB0); // Set SS high to deactivate slave
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
}

// Receive a byte via SPI as slave
unsigned char slave_reciver(unsigned char data)
{
    SPDR = data; // Send dummy data to initiate clock

    while (!(SPSR & (1 << SPIF)))
        ; // Wait for transmission to complete

    return SPDR; // Return received data
}

// Initialize SPI in slave mode
void slave_init()
{
    DDRB |= (1 << DDB3);              // Set MISO as output
    SPCR |= (1 << SPE) | (1 << DORD); // Enable SPI in slave mode, LSB first
    // PORTB |= (1 << PB0); // REMOVE this line — SS should not be driven by slave
}

void spi_stress_test_10000_bytes()
{
    uart_send_string("Starting SPI stress test (exactly 10 packets)...\r\n");

    uint16_t bytes_sent = 0;
    uint8_t val;

    // Send 10 packets of data, each packet is 12 bytes
    for (uint16_t i = 0; i < 10; i++)
    {
        val = i % 256;
        transmit_signalgenerator_data(val, val, val); // 3 packets = 12 bytes
        bytes_sent += 12;

        if ((i % 100) == 0)
        {
            char buf[32];
            sprintf(buf, "Bytes sent: %u\r\n", bytes_sent);
            uart_send_string(buf);
        }
    }

    // Manually send 1 more packet = 4 bytes → total = 10000
    val = 0xAA;
    uint8_t addr = 1;
    uint8_t checksum = 0x55 ^ addr ^ val;

    master_transmit(0x55);
    master_transmit(addr);
    master_transmit(val);
    master_transmit(checksum);
    bytes_sent += 4;

    char final_buf[64];
    sprintf(final_buf, "Stress test complete. Sent %u bytes.\r\n", bytes_sent);
    uart_send_string(final_buf);
}

void transmit_signalgenerator_data(uint16_t amp, uint8_t freq, uint8_t shape)
{
    unsigned int checksum = 0;

    for (uint8_t adress = 1; adress < 4; adress++)
    {
        switch (adress)
        {
        case 1:

            checksum = adress ^ 0x55 ^ amp; // calculates checksum with bitwise xor(^)

            master_transmit(0x55);     // transmit bit(0): sync
            master_transmit(adress);   // transmis bit(1): adress
            master_transmit(amp);      // transmit bit(2): data
            master_transmit(checksum); // transmit bit(3): checksum
            break;
        case 2:

            checksum = adress ^ 0x55 ^ freq; // calculates checksum with bitwise xor(^)

            master_transmit(0x55);     // transmit bit(0): sync
            master_transmit(adress);   // transmis bit(1): adress
            master_transmit(freq);     // transmit bit(2): data
            master_transmit(checksum); // transmit bit(3): checksum
            break;
        case 3:

            checksum = adress ^ 0x55 ^ shape; // calculates checksum with bitwise xor(^)

            master_transmit(0x55);     // transmit bit(0): sync
            master_transmit(adress);   // transmis bit(1): adress
            master_transmit(shape);    // transmit bit(2): data
            master_transmit(checksum); // transmit bit(3): checksum
            break;
        default:
            break;
        }
    }
}