/*
Fast complex math

Copyright 2018 Ahmet Inan <inan@aicodix.de>
*/

#pragma once

template <typename T>
class Complex
{
	T re, im;
public:
	typedef T value_type;
	constexpr Complex() : re(0), im(0) {}
	constexpr Complex(T r) : re(r), im(0) {}
	constexpr Complex(T r, T i) : re(r), im(i) {}
	constexpr T real() const { return re; }
	constexpr T imag() const { return im; }
	inline void real(T r) { re = r; }
	inline void imag(T i) { im = i; }
	template <typename O>
	inline operator Complex<O> ()
	{
		return Complex<O>(re, im);
	}
	inline Complex<T> operator = (T a)
	{
		re = a;
		im = 0;
		return *this;
	}
	inline Complex<T> operator += (Complex<T> a)
	{
		return *this = a + *this;
	}
	inline Complex<T> operator -= (Complex<T> a)
	{
		return *this = *this - a;
	}
	inline Complex<T> operator *= (Complex<T> a)
	{
		return *this = a * *this;
	}
	inline Complex<T> operator *= (T a)
	{
		return *this = a * *this;
	}
};

template <typename T>
static constexpr Complex<T> operator + (Complex<T> a, Complex<T> b)
{
	return Complex<T>(a.real() + b.real(), a.imag() + b.imag());
}

template <typename T>
static constexpr Complex<T> operator + (Complex<T> a)
{
	return a;
}

template <typename T>
static constexpr Complex<T> operator - (Complex<T> a, Complex<T> b)
{
	return Complex<T>(a.real() - b.real(), a.imag() - b.imag());
}

template <typename T>
static constexpr Complex<T> operator - (Complex<T> a)
{
	return Complex<T>(-a.real(), -a.imag());
}

template <typename T>
static constexpr Complex<T> operator * (T a, Complex<T> b)
{
	return Complex<T>(a * b.real(), a * b.imag());
}

template <typename T>
static constexpr Complex<T> operator << (Complex<T> b, int shift)
{
	return Complex<T>(b.real() << shift, b.imag() << shift);
}

template <typename T>
static constexpr Complex<T> operator >> (Complex<T> b, int shift)
{
	return Complex<T>(b.real() >> shift, b.imag() >> shift);
}

template <typename T>
static constexpr Complex<T> operator / (Complex<T> a, T b)
{
	return Complex<T>(a.real() / b, a.imag() / b);
}

template <typename T>
static constexpr Complex<T> operator * (Complex<T> a, Complex<T> b)
{
	return Complex<T>(a.real() * b.real() - a.imag() * b.imag(), a.real() * b.imag() + a.imag() * b.real());
}

template <typename T>
static constexpr Complex<T> conj(Complex<T> a)
{
	return Complex<T>(a.real(), -a.imag());
}

template <typename T>
static constexpr T norm(Complex<T> a)
{
	return a.real() * a.real() + a.imag() * a.imag();
}

