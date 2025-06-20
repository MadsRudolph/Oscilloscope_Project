// generator.c — Handles shape, amplitude, frequency, and LabVIEW BTN logic

#include "generator.h"
#include "SPI.h"
#include "uart.h"
#include <util/delay.h>
#include <stdio.h>

static uint8_t selected_param = 0;
static uint8_t shape = 0;
static uint8_t amplitude = 128;
static uint8_t frequency = 100;

volatile uint8_t run_stop_flag = 0;

void generator_handle_btn(uint8_t btn, uint8_t sw)
{
    switch (btn)
    {
    case 0x00:
        if (selected_param == 0 && sw <= 4)
            shape = sw;
        else if (selected_param == 1)
            amplitude = sw;
        else if (selected_param == 2)
            frequency = sw;
        else
            uart_send_string("Invalid SW value\r\n");

        transmit_signalgenerator_data(amplitude, frequency, shape);
        uart_send_string("BTN0: Sent current values to FPGA\r\n");
        break;

    case 0x01:
        selected_param = (selected_param + 1) % 3;
        uart_send_string("BTN1: Cycled parameter\r\n");
        break;

    case 0x02:
        run_stop_flag = !run_stop_flag;
        uart_send_string(run_stop_flag ? "Paused\r\n" : "Running\r\n");
        break;

    case 0x03:
        PORTD |= (1 << PD7);
        _delay_ms(10);
        PORTD &= ~(1 << PD7);
        selected_param = 0;
        shape = 0;
        amplitude = 128;
        frequency = 1;
        transmit_signalgenerator_data(amplitude, frequency, shape);
        uart_send_string("BTN3: Generator reset\r\n");
        break;

    default:
        uart_send_string("Unknown button\r\n");
        break;
    }

    send_generator_packet(selected_param, shape, amplitude, frequency);
}

void generator_get_state(uint8_t *s, uint8_t *a, uint8_t *f, uint8_t *sel)
{
    if (s) *s = shape;
    if (a) *a = amplitude;
    if (f) *f = frequency;
    if (sel) *sel = selected_param;
}
