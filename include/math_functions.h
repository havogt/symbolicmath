#ifndef MATH_FUNCTIONS_H_
#define MATH_FUNCTIONS_H_

#include <cmath>

template<typename T> struct Sqrt
{
	using type = Sqrt<T>;
};

template<typename T> struct Sin
{
	using type = Sin<T>;
};


template<typename T> struct ToDouble<Sqrt<T> >
{
	static double eval()
	{
		return std::sqrt(ToDouble<T>::eval() );
	}
};

template<typename T> struct ToDouble<Sin<T> >
{
	static double eval()
	{
		return std::sin(T::value);
	}
};

#endif
