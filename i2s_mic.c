/*
Playing with the INMP441 I2S microphone on the Raspberry Pi Pico

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "i2s_mic.pio.h"

int main()
{
	uint clk_pin = 0;
	PIO pio = pio0;
	uint offset = pio_add_program(pio, &i2s_mic_program);
	uint sm = pio_claim_unused_sm(pio, true);
	pio_gpio_init(pio, clk_pin);
	pio_sm_set_consecutive_pindirs(pio, sm, clk_pin, 1, true);
	pio_sm_config c = i2s_mic_program_get_default_config(offset);
	sm_config_set_sideset_pins(&c, clk_pin);
	sm_config_set_clkdiv_int_frac(&c, 122, 18);
	pio_sm_init(pio, sm, offset, &c);
	pio_sm_set_enabled(pio, sm, true);
	stdio_init_all();
	while (1)
		for (int i = 0; i < 256; ++i)
			putchar_unlocked(i);
	return 0;
}
