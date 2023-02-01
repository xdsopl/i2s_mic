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
	uint sd_pin = 2;
	uint sck_ws_pins = 3;
	PIO pio = pio0;
	uint offset = pio_add_program(pio, &i2s_mic_program);
	uint sm = pio_claim_unused_sm(pio, true);
	pio_gpio_init(pio, sd_pin);
	pio_gpio_init(pio, sck_ws_pins);
	pio_gpio_init(pio, sck_ws_pins + 1);
	pio_sm_set_consecutive_pindirs(pio, sm, sd_pin, 1, false);
	pio_sm_set_consecutive_pindirs(pio, sm, sck_ws_pins, 2, true);
	pio_sm_config conf = i2s_mic_program_get_default_config(offset);
	sm_config_set_in_pins(&conf, sd_pin);
	sm_config_set_sideset_pins(&conf, sck_ws_pins);
	sm_config_set_in_shift(&conf, false, true, 32);
	sm_config_set_fifo_join(&conf, PIO_FIFO_JOIN_RX);
	sm_config_set_clkdiv_int_frac(&conf, 122, 18);
	pio_sm_init(pio, sm, offset, &conf);
	pio_sm_set_enabled(pio, sm, true);
	stdio_init_all();
	int shift = 0, count = 0, second = 8000;
	while (1) {
		int32_t left = pio_sm_get_blocking(pio, sm);
		left >>= 8;
		uint32_t mag = left < 0 ? -left : left;
		mag >>= 6;
		int temp = 0;
		while (mag >>= 1)
			++temp;
		if (temp >= shift) {
			shift = temp;
			count = second;
		}
		left >>= shift;
		left += 128;
		left &= 255;
		if (count)
			--count;
		else if (shift) {
			--shift;
			count = second;
		}
		putchar_raw(left);
	}
	return 0;
}
