#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

// SPI function declarations
void master_init(void);
void slave_init(void);
void master_transmit(uint8_t data);
void transmit_signalgenerator_data(uint16_t amp, uint8_t freq, uint8_t shape);
unsigned char slave_reciver(unsigned char data);
void spi_stress_test_10000_packets(void);


#endif // SPI_H
