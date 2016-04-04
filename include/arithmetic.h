#ifndef ARITHMETIC_H_
#define ARITHMETIC_H_

#include "category_trait.h"
#include "helper/cuda_common.h"
#include "sort.h"


namespace symbolicmath
{

template<typename T> struct Neg
{
	using type = Neg<T>;
	using nested_type = T;

	template<typename... Args> CUDA_HOST_DEVICE static double eval( Args... args )
	{
		return -T::eval( args... );
	}
};

template<typename T> struct CategoryTrait<Neg<T>>
{
	static constexpr Category category = Category::NEG;
//	static constexpr Category category = T::category; // want to sort Neg<T> and T next to each other
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

template<typename T1, typename T2, typename = void> struct Add
{
	// SortAndBind needs to add a void manually due to a bug in nvcc-7.5
	using type = typename SortAndBindWithVoid<::symbolicmath::Add,T1,T2>::type;
	using nested_type = T1; // TODO should be both

	template<typename... Args> CUDA_HOST_DEVICE static double eval( Args... args )
	{
		return T1::eval( args... )+T2::eval( args... );
	}
};

template<typename T1, typename T2, typename = void> struct Mult
{
	// SortAndBind needs to add a void manually due to a bug in nvcc-7.5
	using type = typename SortAndBindWithVoid<::symbolicmath::Mult,T1,T2>::type;
	using nested_type = T1; // TODO should be both

	template<typename... Args> CUDA_HOST_DEVICE static double eval( Args... args )
	{
		return T1::eval( args... )*T2::eval( args... );
	}
};

template<typename T1,typename T2> struct CategoryTrait<Add<T1,T2>>
{
	static constexpr Category category = Category::ADD;
};

template<typename T> struct Add<Zero::type, T>
{
	using type = typename T::type;
};

template<typename T> struct Add<T,T, enable_if_t<!std::is_same<T,Zero::type>::value>>
{
	using type = typename Mult<Int<2>,typename T::type>::type;
};

template<typename T> struct Add<T,Neg<T> >
{
	using type = Zero::type;
};

template<typename T> struct Add<Neg<T>,T >
{
	using type = Zero::type;
};

template<int I1, int I2> struct Add<Int<I1>, Int<I2>, enable_if_t<I1!=I2&&I1!=0> >
{
	using type = typename Int<I1 + I2>::type;
};

template<int I1, int I2> struct Add<Neg<Int<I1>>, Int<I2>, enable_if_t<I1!=I2&&I1!=0> >
{
	using type = typename Int<-I1 + I2>::type;
};

template<int I1, int I2> struct Add<Int<I1>, Neg<Int<I2> >, enable_if_t<I1!=I2&&I1!=0> >
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

template<typename T1,typename T2> struct CategoryTrait<Mult<T1,T2>>
{
	static constexpr Category category = Category::MULT;
};

// Int<0> is sorted before any other type, therefore no need for the permuated type
template<typename T> struct Mult<Zero::type, T>
{
	using type = Zero::type;
};

template<typename T> struct Mult<One::type, T>
{
	using type = typename T::type;
};

template<int I1, int I2> struct Mult<Int<I1>, Int<I2>, enable_if_t<I1 != 0 && I2 != 0 && I1 != 1> >
{
	using type = typename Int<I1 * I2>::type;
};

template<typename T1, typename T2> std::ostream& operator<<( std::ostream &out, Mult<T1,T2> )
{
	out << "Mult<" << T1() << "," << T2() << ">";
	return out;
}

/*
 * Factor a minus sign
 */
template<typename T1, typename T2> struct Mult<Neg<T1>, T2, enable_if_t<!std::is_same<T1,Zero::type>::value && !std::is_same<T1,One::type>::value>>
{
	using type = typename Neg<typename Mult<T1,T2>::type>::type;
};
template<typename T1, typename T2> struct Mult<T1, Neg<T2>, enable_if_t<!std::is_same<T1,Zero::type>::value && !std::is_same<T1,One::type>::value> >
{
	using type = typename Neg<typename Mult<T1,T2>::type>::type;
};

}

#endif
