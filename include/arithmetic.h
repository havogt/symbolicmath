#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include "helper/cuda_common.h"
#include "sort.h"


namespace symbolicmath
{

template<typename T> struct Neg
{
	using type = Neg<T>;
	using nested_type = T;
	static constexpr Category category = Category::NEG;
//	static constexpr Category category = T::category; // want to sort Neg<T> and T next to each other

	template<typename... Args> CUDA_HOST_DEVICE static double eval( Args... args )
	{
		return -T::eval( args... );
	}
};

template<typename T> struct Neg<Neg<T>>
{
	using type = typename T::type;
};

template<typename T> std::ostream& operator<<( std::ostream &out, Neg<T> )
{
	out << "Neg<" << T() << ">";
	return out;
}

template<typename T1, typename T2> struct Add
{
	using type = typename SortAndBind<Add,T1,T2>::type;
	using nested_type = T1; // TODO should be both
	static constexpr Category category = Category::ADD;

	template<typename... Args> CUDA_HOST_DEVICE static double eval( Args... args )
	{
		return T1::eval( args... )+T2::eval( args... );
	}
};

template<typename T> struct Add<T,Neg<T> >
{
	using type = Zero::type;
};

template<typename T> struct Add<Neg<T>,T >
{
	using type = Zero::type;
};

// Again, to resolve ambiguity
template<int I> struct Add<Int<I>,Neg<Int<I>> >
{
	using type = Zero::type;
};

// Again, to resolve ambiguity
template<int I> struct Add<Neg<Int<I>>,Int<I> >
{
	using type = Zero::type;
};

template<int I1, int I2> struct Add<Int<I1>, Int<I2> >
{
	using type = typename Int<I1 + I2>::type;
};

template<int I1, int I2> struct Add<Neg<Int<I1>>, Int<I2> >
{
	using type = typename Int<-I1 + I2>::type;
};

template<int I1, int I2> struct Add<Int<I1>, Neg<Int<I2> > >
{
	using type = typename Int<I1 - I2>::type;
};

template<typename T1, typename T2> std::ostream& operator<<( std::ostream &out, Add<T1,T2> )
{
	out << "Add<" << T1() << "," << T2() << ">";
	return out;
}

template<typename T1, typename T2> struct Sub
{
	using type = typename Add<T1,typename Neg<T2>::type>::type;
};

struct MultAble
{
	static constexpr Category category = Category::MULT;
};

template<typename T1, typename T2> struct Mult: MultAble
{
	using type = typename SortAndBind<Mult,T1,T2>::type;
	using nested_type = T1; // TODO should be both
//	static constexpr Category category = Category::MULT;

	template<typename... Args> CUDA_HOST_DEVICE static double eval( Args... args )
	{
		return T1::eval( args... )*T2::eval( args... );
	}
};

template<typename T> struct Mult<Zero::type, T>: MultAble
{
	using type = Zero::type;
};

template<typename T> struct Mult<T, Zero::type>: MultAble
{
	using type = Zero::type;
};

// resolve ambiguity
template<> struct Mult<Zero::type,Zero::type>: MultAble
{
	using type = Zero::type;
};

template<int I1, int I2> struct Mult<Int<I1>, Int<I2> >: MultAble
{
	using type = typename Int<I1 * I2>::type;
};

template<int I> struct Mult<Zero::type, Int<I> >: MultAble
{
	using type = Zero::type;
};
template<int I> struct Mult< Int<I>, Zero::type >: MultAble
{
	using type = Zero::type;
};

template<typename T1, typename T2> std::ostream& operator<<( std::ostream &out, Mult<T1,T2> )
{
	out << "Mult<" << T1() << "," << T2() << ">";
	return out;
}

/*
 * Factor a minus sign
 */
template<typename T1, typename T2> struct Mult<Neg<T1>, T2>
{
	using type = Neg<typename Mult<T1,T2>::type>;
};
template<typename T1, typename T2> struct Mult<T1, Neg<T2>>
{
	using type = Neg<typename Mult<T1,T2>::type>;
};

}

#endif
