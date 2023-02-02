/*
Discrete Hilbert transformation

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

template <typename cmplx>
class Hilbert
{
	typedef typename cmplx::value_type value;
	static constexpr int TAPS = 21;
	static constexpr int MID = (TAPS - 1) / 2;
	value real[TAPS] = { 0 };
public:
	cmplx operator()(value input)
	{
		value re = real[MID];
		value im = 317 * (real[MID-1] - real[MID+1])
			+ 83 * (real[MID-3] - real[MID+3]);
			+ 30 * (real[MID-5] - real[MID+5]);
			+ 9 * (real[MID-7] - real[MID+7]);
			+ 2 * (real[MID-9] - real[MID+9]);
		im >>= 9;
		for (int i = 0; i < TAPS-1; ++i)
			real[i] = real[i+1];
		real[TAPS-1] = input;
		return cmplx(re, im);
	}
};

