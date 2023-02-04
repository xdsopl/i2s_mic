/*
Signal clipper

Copyright 2023 Ahmet Inan <xdsopl@gmail.com>
*/

#pragma once

template <typename CMPLX, typename CMPLX::value_type MIN, typename CMPLX::value_type MAX>
struct Clipper
{
	typename CMPLX::value_type operator () (typename CMPLX::value_type value)
	{
		return value < MIN ? MIN : value > MAX ? MAX : value;
	}
	CMPLX operator () (CMPLX value)
	{
		return CMPLX(operator () (value.real()), operator () (value.imag()));
	}
};

