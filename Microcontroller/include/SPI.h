#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

// SPI function declarations
void master_init(void);
void slave_init(void);
void master_transmit(uint8_t data);
unsigned char slave_reciver(unsigned char data);

#endif // SPI_H
