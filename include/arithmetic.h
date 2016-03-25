#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include "compare.h"

template<typename T> struct Neg
{
	using type = Neg<T>;
	using nested_type = T;
	static constexpr Category category = Category::NEG;
};



template<typename T1, typename T2> struct Add
{
	using type = Add<T1, T2>;
};

template<typename T1, typename T2> std::ostream& operator<<( std::ostream &out, Add<T1,T2> )
{
	out << "Add<" << T1() << "," << T2() << ">";
	return out;
}

template<typename T> struct Add<T,Neg<T> >
{
	using type = Zero;
};

template<typename T> struct Add<Neg<T>,T >
{
	using type = Zero;
};

template<int I1, int I2> struct Add<Int<I1>, Int<I2> >
{
	using type = typename Int<I1 + I2>::type;
};

template<typename T1, typename T2> struct ToDouble<Add<T1,T2> >
{
	static double eval()
	{
		return ToDouble<T1>::eval()+ToDouble<T2>::eval();
	}
};

template<typename T1, typename T2, typename = void> struct Sub
{
	using type = Sub<T1,T2>;
};

template<typename T> struct Sub<T,T>
{
	using type = Zero;
};

template<typename T1, typename T2> struct Sub<T1,Neg<T2> >
{
	using type = typename Add<T1,T2>::type;
};

/**
 * Enable only if first and second type are different to resolve ambiguity with Sub<T,T>
 */
template<int I1, int I2> struct Sub<Int<I1>, Int<I2>, typename std::enable_if<I1 != I2>::type >
{
	using type = typename Int<I1 - I2>::type;
};

template<typename T1, typename T2> struct MultImpl
{
	using type = MultImpl<T1,T2>;
};

template<typename T1, typename T2> std::ostream& operator<<( std::ostream &out, MultImpl<T1,T2> )
{
	out << "Mult<" << T1() << "," << T2() << ">";
	return out;
}

template<int I1, int I2> struct MultImpl<Int<I1>, Int<I2> >
{
	using type = typename Int<I1 * I2>::type;
};

template<typename T1, typename T2, typename = void> struct Mult
{
};

template<typename T1, typename T2> struct Mult<T1,T2,typename std::enable_if<Less<T1,T2>::type::value>::type >
{
	using type = typename MultImpl<T2, T1>::type;
};
template<typename T1, typename T2> struct Mult<T1,T2,typename std::enable_if<!Less<T1,T2>::type::value>::type>
{
	using type = typename MultImpl<T1, T2>::type;
};

template<typename T1, typename T2> struct ToDouble<MultImpl<T1,T2> >
{
	static double eval()
	{
		return ToDouble<T1>::eval()*ToDouble<T2>::eval();
	}
};

/*
 * Factor a minus sign
 */
template<typename T1, typename T2> struct MultImpl<Neg<T1>, T2>
{
	using type = Neg<typename Mult<T1,T2>::type>;
};



#endif
