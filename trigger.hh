/*
Some trigger functions

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

template <typename TYPE, TYPE LOW, TYPE HIGH>
class SchmittTrigger
{
	bool previous;
public:
	constexpr SchmittTrigger(bool previous = false) : previous(previous)
	{
	}
	bool operator() (TYPE input)
	{
		if (previous) {
			if (input < LOW)
				previous = false;
		} else {
			if (input > HIGH)
				previous = true;
		}
		return previous;
	}
};

class FallingEdgeTrigger
{
	bool previous;
public:
	constexpr FallingEdgeTrigger(bool previous = false) : previous(previous)
	{
	}
	bool operator() (bool input)
	{
		bool tmp = previous;
		previous = input;
		return tmp && !input;
	}
};

class RisingEdgeTrigger
{
	bool previous;
public:
	constexpr RisingEdgeTrigger(bool previous = false) : previous(previous)
	{
	}
	bool operator() (bool input)
	{
		bool tmp = previous;
		previous = input;
		return !tmp && input;
	}
};

