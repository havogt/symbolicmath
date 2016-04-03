#ifndef COMPLEX_H_
#define COMPLEX_H_

#include "category_trait.h"

namespace symbolicmath
{

template<typename Real, typename Imag> struct Complex
{
	using real_type = typename Real::type;
	using imag_type = typename Imag::type;
	using type = Complex<real_type, imag_type>;
	using nested_type = Real; // TODO this is not a valid nested_type
};

template<typename T1,typename T2> struct CategoryTrait<Complex<T1,T2>>
{
	static constexpr Category category = Category::COMPLEX;
};

template<typename Real> struct Complex<Real,Zero>
{
	using type = typename Real::type;
};

template<typename T1R, typename T1I, typename T2R, typename T2I> struct Mult<Complex<T1R,T1I>, Complex<T2R,T2I> >
{
	using real_type_temp = typename Sub< typename Mult<T1R,T2R>::type, typename Mult<T1I, T2I>::type>::type;
	using imag_type_temp = typename Add< typename Mult<T1R, T2I>::type, typename Mult<T1I, T2R>::type>::type;
	using type = typename Complex<real_type_temp,imag_type_temp>::type;
};

template<int I, typename T2R, typename T2I> struct Mult<Int<I>, Complex<T2R,T2I>, enable_if_t<I!=0&&I!=1> >
{
	using real_type_temp = typename Mult<Int<I>,typename T2R::type>::type;
	using imag_type_temp = typename Mult<Int<I>,typename T2I::type>::type;
	using type = typename Complex<real_type_temp,imag_type_temp>::type;
};

template<typename T1R, typename T1I, typename T2R, typename T2I> struct Add<Complex<T1R,T1I>, Complex<T2R,T2I>,enable_if_t<!(std::is_same<T1R,T2R>::value&&std::is_same<T1I,T2I>::value)> >
{
	using real_type_temp = typename Add< typename T1R::type, typename T2R::type>::type;
	using imag_type_temp = typename Add< typename T1I::type, typename T2I::type>::type;
	using type = typename Complex<real_type_temp,imag_type_temp>::type;
};

template<typename T1, typename T2> std::ostream& operator<<( std::ostream &out, Complex<T1,T2> )
{
	out << "Complex<" << T1() << "," << T2() << ">";
	return out;
}

template<typename> struct Real;
template<typename R, typename I> struct Real<Complex<R,I>>
{
	using type = typename R::type;
};

template<typename> struct Imag;
template<typename R, typename I> struct Imag<Complex<I,R>>
{
	using type = typename I::type;
};

}

#endif
