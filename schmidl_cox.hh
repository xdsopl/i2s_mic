/*
Schmidl & Cox correlator

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

#include "clipper.hh"
#include "sma.hh"

template<typename cmplx, int symbol_len, int guard_len>
class SchmidlCox {
	typedef typename cmplx::value_type value;
	typedef Complex<int8_t> cmplx8;
	static constexpr int match_len = guard_len | 1;
	static constexpr int match_del = (match_len - 1) / 2;
	SMA<cmplx, symbol_len> cor;
	SMA<value, 2 * symbol_len> pwr;
	SMA<value, match_len> match;
	Delay<cmplx, cmplx8, symbol_len> delay;
	Clipper<cmplx, -127, 127> clip;
public:
	value operator()(cmplx iq) {
		iq = clip(iq);
		cmplx P = cor(delay(iq) * conj(iq));
		value R = pwr(norm(iq));
		value timing = match(norm((P << 9) / R)) >> 16;
		return timing;
	}
};

