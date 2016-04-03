#ifndef MATH_FUNCTIONS_H_
#define MATH_FUNCTIONS_H_

#include <cmath>

namespace symbolicmath
{

template<typename T> struct Sqrt
{
	using type = Sqrt<T>;
	using nested_type = T;
	static constexpr Category category = Category::SQRT;

	template<typename... Args> CUDA_HOST_DEVICE static double eval( Args... args )
	{
		return sqrt(T::eval( args... ));
	}
};

template<typename T> std::ostream& operator<<( std::ostream &out, Sqrt<T> )
{
	out << "Sqrt<" << T() << ">";
	return out;
}


template<typename T> struct Sin
{
	using type = Sin<T>;
	using nested_type = T;
	static constexpr Category category = Category::SIN;

	template<typename... Args> CUDA_HOST_DEVICE static double eval( Args... args )
	{
		return sin(T::eval( args... ));
	}
};

template<typename T> std::ostream& operator<<( std::ostream &out, Sin<T> )
{
	out << "Sin<" << T() << ">";
	return out;
}




}

#endif
