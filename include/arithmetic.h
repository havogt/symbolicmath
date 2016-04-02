#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include "compare.h"

namespace symbolicmath
{

template<typename T> struct Neg
{
	using type = Neg<T>;
	using nested_type = T;
	static constexpr Category category = Category::NEG;
//	static constexpr Category category = T::category; // want to sort Neg<T> and T next to each other
};

template<typename T> std::ostream& operator<<( std::ostream &out, Neg<T> )
{
	out << "Neg<" << T() << ">";
	return out;
}

template<typename T1, typename T2> struct AddImpl
{
	using type = AddImpl<T1, T2>;
};


template<typename T> struct AddImpl<T,Neg<T> >
{
	using type = Zero::type;
};

template<typename T> struct AddImpl<Neg<T>,T >
{
	using type = Zero::type;
};

template<int I1, int I2> struct AddImpl<Int<I1>, Int<I2> >
{
	using type = typename Int<I1 + I2>::type;
};

template<typename T1, typename T2> struct ToDouble<AddImpl<T1,T2> >
{
	static double eval()
	{
		return ToDouble<T1>::eval()+ToDouble<T2>::eval();
	}
};

template<typename T1, typename T2, typename = void> struct Add
{
};

template<typename T1, typename T2> struct Add<T1,T2,typename std::enable_if<Less<T1,T2>::type::value>::type >
{
	using type = typename AddImpl<T2, T1>::type;
	static constexpr Category category = Category::ADD;
};
template<typename T1, typename T2> struct Add<T1,T2,typename std::enable_if<!Less<T1,T2>::type::value>::type>
{
	using type = typename AddImpl<T1, T2>::type;
	static constexpr Category category = Category::ADD;
};

template<typename T1, typename T2> std::ostream& operator<<( std::ostream &out, AddImpl<T1,T2> )
{
	out << "Add<" << T1() << "," << T2() << ">";
	return out;
}

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
	static constexpr Category category = Category::MULT;
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
	static constexpr Category category = Category::MULT;
};
template<typename T1, typename T2> struct Mult<T1,T2,typename std::enable_if<!Less<T1,T2>::type::value>::type>
{
	using type = typename MultImpl<T1, T2>::type;
	static constexpr Category category = Category::MULT;
};

template<typename T1, typename T2> std::ostream& operator<<( std::ostream &out, MultImpl<T1,T2> )
{
	out << "Mult<" << T1() << "," << T2() << ">";
	return out;
}
template<typename T1, typename T2> std::ostream& operator<<( std::ostream &out, Mult<T1,T2> )
{
	out << "Mult<" << T1() << "," << T2() << ">";
	return out;
}

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

}

#endif
