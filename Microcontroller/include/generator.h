// generator.h
#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdint.h>

extern volatile uint8_t run_stop_flag;

void generator_handle_btn(uint8_t btn, uint8_t sw);
void generator_get_state(uint8_t *s, uint8_t *a, uint8_t *f, uint8_t *sel);

#endif
