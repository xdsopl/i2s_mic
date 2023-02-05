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
	typedef Complex<int16_t> cmplx16;
	static constexpr int match_len = guard_len | 1;
	static constexpr int match_del = (match_len - 1) / 2;
	SMA<cmplx, cmplx16, symbol_len> cor;
	SMA<value, uint16_t, 2 * symbol_len> pwr;
	SMA<value, uint16_t, match_len> match;
	Delay<cmplx, cmplx8, symbol_len> delay;
	Clipper<cmplx, -128, 127> clip_s8;
	Clipper<cmplx, 0, 255> clip_u8;
	Clipper<cmplx, -32768, 32767> clip_s16;
	Clipper<cmplx, 0, 65536> clip_u16;
public:
	value operator()(cmplx iq) {
		iq = clip_s8(iq);
		cmplx P = cor(clip_s16(delay(iq) * conj(iq)));
		value R = pwr(clip_u16(norm(iq)));
		value timing = match(clip_u16(norm((P << 9) / R))) >> 16;
		return timing;
	}
};

