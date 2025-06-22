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
    // send message to terminal before reset
    uart_send_string("Resetting FPGA before SPI stress test...\r\n");

    // toggle PD7 high then low to reset FPGA
    PORTD |= (1 << PD7);
    _delay_ms(10);
    PORTD &= ~(1 << PD7);

    // notify that reset is complete
    uart_send_string("FPGA reset complete. Starting SPI stress test (10,827 packets)...\r\n");

    uint16_t packet_count = 0;
    uint8_t val;

    for (uint16_t i = 0; i < 10827; i++)
    {
        val = i % 256;
        transmit_signalgenerator_data(val, val, val); // send packet with repeating value
        packet_count += 1;

        if ((i % 500) == 0)
        {
            // print status update every 500 packets
            char buf[48];
            sprintf(buf, "Packets sent: %u\r\n", packet_count);
            uart_send_string(buf);
        }
    }

    // send final message to terminal
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
            checksum = adress ^ 0x55 ^ amp;

            master_transmit(0x55);     // sync byte
            master_transmit(adress);   // address byte (1 = amplitude)
            master_transmit(amp);      // amplitude value
            master_transmit(checksum); // checksum byte
            break;

        case 2:
            checksum = adress ^ 0x55 ^ freq;

            master_transmit(0x55);     // sync byte
            master_transmit(adress);   // address byte (2 = frequency)
            master_transmit(freq);     // frequency value
            master_transmit(checksum); // checksum byte
            break;

        case 3:
            checksum = adress ^ 0x55 ^ shape;

            master_transmit(0x55);     // sync byte
            master_transmit(adress);   // address byte (3 = shape)
            master_transmit(shape);    // shape value
            master_transmit(checksum); // checksum byte
            break;

        default:
            break;
        }
    }
}
