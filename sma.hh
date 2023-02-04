/*
Simple moving average

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

#include "delay.hh"

template <typename TYPE, int NUM>
class SMA
{
	Delay<TYPE, TYPE, NUM> delay;
	TYPE sum = 0;
public:
	TYPE operator () (TYPE input)
	{
		return sum += input - delay(input);
	}
};

