#ifndef SCALAR_H_
#define SCALAR_H_

#include "helper/cuda_common.h"

namespace symbolicmath
{

template<int I> struct Int
{
	using type = Int<I>;
	static constexpr int value = I;
	static constexpr int compare_value = value;
	static constexpr Category category = Category::INT;

	template<typename... Args> CUDA_HOST_DEVICE static inline double eval( Args... args )
	{
		return (double)I;
	}
};

template<int I> std::ostream& operator<<( std::ostream &out, Int<I> )
{
	out << "Int<"<< I << ">";
	return out;
}

std::ostream& operator<<( std::ostream &out, Int<0> )
{
	out << "Zero";
	return out;
}

std::ostream& operator<<( std::ostream &out, Int<1> )
{
	out << "One";
	return out;
}

using Zero = Int<0>;
using One = Int<1>;

template<int I> struct RuntimeValue
{
	using type = RuntimeValue<I>;
	using nested_type = Int<I>;
	static constexpr Category category = Category::RUNTIME_VALUE;

	template<int ArgI> CUDA_HOST_DEVICE static inline  double evalHelper()
	{
		return 0;// TODO error
	}

	template<int ArgI, typename First, typename... Args> CUDA_HOST_DEVICE static inline double evalHelper( First first, Args... args )
	{
		if( ArgI==I ) return first;
		else return evalHelper<ArgI+1>( args... );
	}

	template<typename... Args> CUDA_HOST_DEVICE static inline double eval( Args... args )
	{
		return evalHelper<0>( args... );
	}
};

template<int I> std::ostream& operator<<( std::ostream &out, RuntimeValue<I> )
{
	out << "RV" << I;
	return out;
}

}

#endif
