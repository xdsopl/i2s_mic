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
	const int TAPS = 21;
	DSP::Kaiser<float> window(2);
	DSP::HilbertTransform<float> filter;
	DSP::Coeffs<TAPS, float> w(&window, &filter);
	for (int i = 0; i < TAPS; ++i)
		std::cout << (int)std::nearbyint(512 * w(i)) << std::endl;
	return 0;
}

