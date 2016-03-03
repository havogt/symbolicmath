#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include "compare.h"

template<typename T> struct Neg
{
	using type = Neg<T>;
};

template<typename T1, typename T2, typename = void> struct Sub
{
	using type = Sub<T1,T2>;
};

template<typename T> struct Sub<T,T>
{
	using type = Zero;
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


template<typename T1, typename T2> struct Add
{
	using type = Add<T1, T2>;
};

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


#endif
