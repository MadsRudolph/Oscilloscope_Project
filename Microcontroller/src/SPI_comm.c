// ## Program developed by Mads Rodulph and Sigurd Hestbech Christiansen ##
// ## Last edited: 21-6-2025 ##
// ## This file contains SPI communication functions ##

#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include <util/delay.h>
#include "SPI_comm.h"
#include "SPI.h"

void spi_stress_test_10000_packets()
{
    // Reset the SPI slave before starting the stress test
    uart_send_string("Resetting FPGA before SPI stress test...\r\n");

    // reset FPGA by toggling PD7 pin
    PORTD |= (1 << PD7);  // Set HIGH (active reset)
    _delay_ms(10);        // Wait
    PORTD &= ~(1 << PD7); // Set LOW (back to normal)

    uart_send_string("FPGA reset complete. Starting SPI stress test (10,827 packets)...\r\n");

    uint16_t packet_count = 0;
    uint8_t val;

    for (uint16_t i = 0; i < 10827; i++)
    {
        val = i % 256;
        transmit_signalgenerator_data(val, val, val); // Sends 1 packet
        packet_count += 1;

        if ((i % 500) == 0) // less frequent UART to reduce lag
        {
            char buf[48];
            sprintf(buf, "Packets sent: %u\r\n", packet_count);
            uart_send_string(buf);
        }
    }

    char final_buf[64];
    sprintf(final_buf, "Stress test complete. Sent %u packets.\r\n", packet_count);
    uart_send_string(final_buf);
}

void transmit_signalgenerator_data(uint8_t amp, uint8_t freq, uint8_t shape)
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