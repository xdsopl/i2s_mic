/*
Digital delay line

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

template <typename TYPE, typename BUF, int NUM>
class Delay
{
	BUF buf[NUM] = { 0 };
	int pos = 0;
public:
	TYPE operator () (TYPE input)
	{
		TYPE tmp = buf[pos];
		buf[pos] = input;
		if (++pos >= NUM)
			pos = 0;
		return tmp;
	}
};

