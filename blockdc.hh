/*
DC Blocker

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

template <typename TYPE, int SHIFT>
class BlockDC
{
	TYPE avg = 0;
public:
	TYPE operator () (TYPE input)
	{
		TYPE tmp = input - (avg >> SHIFT);
		avg += tmp;
		return tmp;
	}
};

