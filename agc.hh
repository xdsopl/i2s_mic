/*
Fixed point auto gain control without multipliers

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

template <typename TYPE, int BITS, int HOLD>
class AGC
{
	static constexpr TYPE val_min = -(1 << (BITS - 1));
	static constexpr TYPE val_max = (1 << (BITS - 1)) - 1;
	static constexpr TYPE neg_mid = -(1 << (BITS - 2));
	static constexpr TYPE pos_mid = (1 << (BITS - 2)) - 1;
	int shift = 0;
	int count = 0;
public:
	TYPE operator () (TYPE value)
	{
		value >>= shift;
		if (value < val_min || value > val_max) {
			++shift;
			count = HOLD;
		} else if (value < pos_mid && value > neg_mid) {
			if (count) {
				--count;
			} else if (shift) {
				--shift;
				count = HOLD;
			}
		} else {
			count = HOLD;
		}
		return value;
	}
};

