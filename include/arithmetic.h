#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include "sort.h"

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

template<typename T1, typename T2> struct Add
{
	using type = typename SortNested<AddImpl<T1,T2>>::type;
	static constexpr Category category = Category::ADD;
};

template<typename T1, typename T2> std::ostream& operator<<( std::ostream &out, AddImpl<T1,T2> )
{
	out << "Add<" << T1() << "," << T2() << ">";
	return out;
}

template<typename T1, typename T2> struct Sub
{
	using type = typename Add<T1,typename Neg<T1>::type>::type;
};

template<typename T1, typename T2> struct MultImpl
{
	using type = MultImpl<T1,T2>;
	using nested_type = T1; // TODO should be both
	static constexpr Category category = Category::MULT;
};

template<int I1, int I2> struct MultImpl<Int<I1>, Int<I2> >
{
	using type = typename Int<I1 * I2>::type;
};

template<typename T1, typename T2> struct Mult
{
	using type = typename SortNested<MultImpl<T1,T2>>::type;
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
template<typename T1, typename T2> struct MultImpl<T1, Neg<T2>>
{
	using type = Neg<typename Mult<T1,T2>::type>;
};

}

#endif
