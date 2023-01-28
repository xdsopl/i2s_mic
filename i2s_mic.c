/*
Playing with the INMP441 I2S microphone on the Raspberry Pi Pico

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#include <stdio.h>
#include "pico/stdlib.h"

int main()
{
	stdio_init_all();
	while (1)
		for (int i = 0; i < 256; ++i)
			putchar_unlocked(i);
	return 0;
}
