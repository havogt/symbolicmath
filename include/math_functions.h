#ifndef MATH_FUNCTIONS_H_
#define MATH_FUNCTIONS_H_

#include <cmath>

namespace symbolicmath
{

template<typename T> struct Sqrt
{
	using type = Sqrt<T>;
	using nested_type = T;

	template<typename... Args> CUDA_HOST_DEVICE static double eval( Args... args )
	{
		return sqrt(T::eval( args... ));
	}
};

constexpr int ConstexprSqrt( int I, int R = 1 )
{
	return (R*R>I)?(-1):((R*R==I)?(R):(ConstexprSqrt(I,R+1)));
}

template<int I> struct CompileTimeSqrt
{
	static constexpr int value = ConstexprSqrt(I);
//	static_assert( value >= 0, "CompileTimeSqrt called for non-square number" ); // FIXME: Problem in clang++-3.8
};

//template<int I> struct Sqrt<Int<I>>
//{
//	using type = // TODO make this compile time collapsing if square number
//};

template<typename T> struct CategoryTrait<Sqrt<T>>
{
	static constexpr Category category = Category::SQRT;
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

	template<typename... Args> CUDA_HOST_DEVICE static double eval( Args... args )
	{
		return sin(T::eval( args... ));
	}
};

template<typename T> struct CategoryTrait<Sin<T>>
{
	static constexpr Category category = Category::SIN;
};


template<typename T> std::ostream& operator<<( std::ostream &out, Sin<T> )
{
	out << "Sin<" << T() << ">";
	return out;
}




}

#endif
