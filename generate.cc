/*
Generate coefficients for the discrete Hilbert transformation

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#include <cmath>
#include <iostream>
#include "window.hh"
#include "coeffs.hh"
#include "filter.hh"

int main()
{
	const int SHIFT = 9;
	const int TAPS = 21;
	const int FACT = 1 << SHIFT;
	DSP::Kaiser<float> window(2);
	DSP::HilbertTransform<float> filter;
	DSP::Coeffs<TAPS, float> w(&window, &filter);
	for (int i = 0; i < TAPS; ++i)
		std::cout << (int)std::nearbyint(FACT * w(i)) << std::endl;
	return 0;
}

