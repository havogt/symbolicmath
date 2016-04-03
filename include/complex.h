#ifndef COMPLEX_H_
#define COMPLEX_H_

namespace symbolicmath
{

template<typename Real, typename Imag> struct Complex
{
	using real_type = Real;
	using imag_type = Imag;
	using type = Complex<Real, Imag>;
	using nested_type = Real; // TODO this is not a valid nested_type
	static constexpr Category category = Category::COMPLEX;
};

template<typename Real> struct Complex<Real,Zero>
{
	using type = Real;
};

template<typename T1R, typename T1I, typename T2R, typename T2I> struct Mult<Complex<T1R,T1I>, Complex<T2R,T2I> >
{
	using real_type_temp = typename Sub< typename Mult<T1R,T2R>::type, typename Mult<T1I, T2I>::type>::type;
	using imag_type_temp = typename Add< typename Mult<T1R, T2I>::type, typename Mult<T1I, T2R>::type>::type;
	using type = typename Complex<real_type_temp,imag_type_temp>::type;
};

template<typename T1, typename T2> std::ostream& operator<<( std::ostream &out, Complex<T1,T2> )
{
	out << "Complex<" << T1() << "," << T2() << ">";
	return out;
}

}

#endif
