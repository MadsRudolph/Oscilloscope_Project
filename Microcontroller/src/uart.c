// ## References to datasheet pages are marked as S.xxx for Atmega2560 ##

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "uart.h"

// UART buffer and flags
volatile char uart_buffer[32];
volatile uint8_t uart_index = 0;
volatile uint8_t uart_rx_flag = 0;

uint8_t temp_min_pwm = 0;
uint8_t temp_max_pwm = 255;
uint8_t new_pwm_values_received = 0;

// Initialize UART with specified baud rate. Look up the table on page 231 of the Atmega2560 datasheet, for selecting your correct parameter.
void uart_init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);                  // USART0 Baud rate register high byte (S.412)
    UBRR0L = (unsigned char)ubrr;                         // USART0 Baud rate register low byte (S.412)
    UCSR0A |= (1 << U2X0);                                 // Enable double speed (S.223)
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); // Enable RX, TX, and RX interrupt (S.224)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);               // 8-bit data format (S.226)
    // No parity ((UPM00 & UUPM01) = 0), 1 stopbit (USBS0 = 0), async mode ((UMSEL00 & UMSEL01 = 0)) (S.225-226)
    // One complete data cycle is 1 start-bit followed by 8 data-bit's followed by 1 stop-bit. 
}

// Send one character via UART. Exsampel from atmega2560 datasheet on page 212
void uart_send(char data)
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait until UDRE0 is high meaning buffer is clear an ready to be written (S.223)
    UDR0 = data; // udates data into buffer and sends data (S.212)
}

// Send string via UART
void uart_send_string(const char *str)
{
    while (*str)
        uart_send(*str++);
}

// ISR for UART RX
ISR(USART0_RX_vect)
{
    char received = UDR0;
    if (received == '\r' || received == '\n')
    {
        uart_buffer[uart_index] = '\0';
        uart_index = 0;
        uart_rx_flag = 1;
    }
    else if (uart_index < sizeof(uart_buffer) - 1)
    {
        uart_buffer[uart_index++] = received;
    }
}

// Handle UART commands for PWM
void process_uart_command(void)
{
    uart_send_string("Got: ");
    uart_send_string((char *)uart_buffer);
    uart_send_string("\r\n");

    if (strncmp((char *)uart_buffer, "MIN:", 4) == 0)
    {
        int value = atoi((char *)&uart_buffer[4]);
        if (value < 0 || value > 255)
        {
            uart_send_string("Error: MIN must be between 0 and 255!\r\n");
        }
        else if (value >= temp_max_pwm)
        {
            uart_send_string("Error: MIN cannot be >= MAX!\r\n");
        }
        else
        {
            temp_min_pwm = value;
            uart_send_string("Temp MIN stored. Press button to apply.\r\n");
            new_pwm_values_received = 1;
        }
    }
    else if (strncmp((char *)uart_buffer, "MAX:", 4) == 0)
    {
        int value = atoi((char *)&uart_buffer[4]);
        if (value < 0 || value > 255)
        {
            uart_send_string("Error: MAX must be between 0 and 255!\r\n");
        }
        else if (value <= temp_min_pwm)
        {
            uart_send_string("Error: MAX cannot be <= MIN!\r\n");
        }
        else
        {
            temp_max_pwm = value;
            uart_send_string("Temp MAX stored. Press button to apply.\r\n");
            new_pwm_values_received = 1;
        }
    }
    else
    {
        uart_send_string("Invalid UART command! Use MIN: or MAX:\r\n");
    }
}
