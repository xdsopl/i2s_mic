/*
Signal clipper

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

template <typename TYPE, TYPE MIN, TYPE MAX>
struct Clipper
{
	TYPE operator () (TYPE value)
	{
		return value < MIN ? MIN : value > MAX ? MAX : value;
	}
};

