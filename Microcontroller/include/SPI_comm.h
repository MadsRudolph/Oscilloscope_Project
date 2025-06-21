#ifndef SPI_COMM_H
#define SPI_COMM_H

#include <avr/io.h>

// SPI function declarations
void spi_stress_test_10000_packets(void);
void transmit_signalgenerator_data(uint16_t amp, uint8_t freq, uint8_t shape);

#endif // SPI_H