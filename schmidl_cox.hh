/*
Schmidl & Cox correlator

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

#include "clipper.hh"
#include "trigger.hh"
#include "cordic.hh"
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
	Delay<int8_t, int8_t, match_del> align;
	SchmittTrigger<value, 2 << 18, 3 << 18> threshold;
	FallingEdgeTrigger falling;
	CORDIC<cmplx, int32_t, int8_t> arg;
	Clipper<cmplx, -128, 127> clip_s8;
	Clipper<cmplx, 0, 255> clip_u8;
	Clipper<cmplx, -32768, 32767> clip_s16;
	Clipper<cmplx, 0, 65535> clip_u16;
	value timing_max = 0;
	int index_max = 0;
	int8_t phase_max = 0;
public:
	int8_t frac_cfo = 0;
	int symbol_pos = 0;
	bool operator()(cmplx iq) {
		iq = clip_s8(iq);
		cmplx P = cor(clip_s16(delay(iq) * conj(iq)));
		value R = pwr(clip_u16(norm(iq)));
		value timing = match(clip_u16(norm((P << 9) / R)));
		int8_t phase = align(arg(P));
		bool collect = threshold(timing);
		bool process = falling(collect);

		if (!collect && !process)
			return false;

		if (timing_max < timing) {
			timing_max = timing;
			phase_max = phase;
			index_max = match_del;
		} else if (index_max < symbol_len + guard_len + match_del) {
			++index_max;
		} else if (process) {
			timing_max = 0;
			index_max = 0;
			return false;
		}

		if (!process)
			return false;

		symbol_pos = index_max;
		frac_cfo = phase_max;
		timing_max = 0;
		phase_max = 0;
		index_max = 0;
		return true;
	}
};

