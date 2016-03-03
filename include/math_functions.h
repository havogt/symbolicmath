#ifndef MATH_FUNCTIONS_H_
#define MATH_FUNCTIONS_H_

#include <cmath>

template<typename T> struct Sqrt
{
	using type = Sqrt<T>;
	using nested_type = T;
	static constexpr Category category = Category::SQRT;
};

template<typename T> struct Sin
{
	using type = Sin<T>;
	using nested_type = T;
	static constexpr Category category = Category::SIN;
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
		return std::sin(ToDouble<T>::eval());
	}
};

#endif
