/*
Playing with the INMP441 I2S microphone on the Raspberry Pi Pico

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "i2s_mic.pio.h"
#include "complex.hh"
#include "blockdc.hh"
#include "hilbert.hh"
#include "schmidl_cox.hh"
#include "agc.hh"

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
	typedef int32_t value;
	typedef Complex<value> cmplx;
	BlockDC<value, 4> block_dc;
	AGC<value, 8, 8000> agc;
	static Hilbert<cmplx> hilbert;
	const int symbol_len = 1280;
	const int guard_len = symbol_len / 8;
	static SchmidlCox<cmplx, symbol_len/2, guard_len> correlator;
	while (1) {
		value left = pio_sm_get_blocking(pio, sm);
		cmplx iq = hilbert(agc(block_dc(left >> 8)));
		value val = correlator(iq);
		printf("%ld\n", val);
	}
	return 0;
}
