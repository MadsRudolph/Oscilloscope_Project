// ## Program developed by Mads Rodulph and Sigurd Hestbech Christiansen ##
// ## Last edited: 21-6-2025 ##
// ## This file contains UART initialization and transmission functions ##
// ## References to datasheet pages are marked as S.xxx for Atmega2560 ##

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART.h"

void uart_init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);                  // USART0 Baud rate register high byte (S.412)
    UBRR0L = (unsigned char)ubrr;                         // USART0 Baud rate register low byte (S.412)
    UCSR0A |= (1 << U2X0);                                // Enable double speed (S.223)
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); // Enable RX, TX, and RX interrupt (S.224)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);               // 8-bit data format (S.226)
    // No parity (UPM00 & UUPM01 = 0), 1 stopbit (USBS0 = 0), async mode (UMSEL00 & UMSEL01 = 0) (S.225-226)
    // One complete data cycle is 1 start-bit followed by 8 data-bit's followed by 1 stop-bit.
}

// UART0: Send single byte (used for debug prints)
void uart_send(char data)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = data;
}

// UART0: Send string
void uart_send_string(const char *str)
{
    while (*str)
        uart_send(*str++);
}

// === LabVIEW UART1: Data and command communication ===

void uart1_init(unsigned int ubrr)
{
    UBRR1H = (unsigned char)(ubrr >> 8);
    UBRR1L = (unsigned char)ubrr;
    UCSR1A |= (1 << U2X1); // Double speed mode
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10); // 8-bit
}

// UART1: Send single byte (used for LabVIEW packets)
void uart1_send(char data)
{
    while (!(UCSR1A & (1 << UDRE1)))
        ;
    UDR1 = data;
}