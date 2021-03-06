#ifndef MATRIX_H_
#define MATRIX_H_

#include "arithmetic.h"
#include "math_functions.h"

#include <iomanip>

#include "boost/mpl/vector.hpp"
#include "boost/mpl/at.hpp"
#include "boost/mpl/deref.hpp"
#include "boost/mpl/placeholders.hpp"
#include "boost/mpl/transform.hpp"

namespace symbolicmath
{

template<typename... Entries> struct Matrix
{
	using type = Matrix<Entries...>;

	using entries = boost::mpl::vector<Entries...>;
	static constexpr int n = CompileTimeSqrt<sizeof...(Entries)>::value;

	template<int I, int J> struct get
	{
		using type = typename boost::mpl::deref<typename boost::mpl::at_c<entries,I+J*n>::type>::type;
	};
};

template<typename Mat> struct Trace
{
	static_assert( Mat::n == 2, "fix later with mpl::fold and a diagonal view or something" ); // TODO
	using type = typename Add<typename Mat::template get<0,0>::type,typename Mat:: template get<1,1>::type>::type;
};

/**
 * TODO maybe change later to Mult (with enable_if)
 */
template<typename T1, typename T2> struct MatrixMult
{
	static_assert( T1::n == T2::n, "matrix dimensions do not agree" );
	static_assert( T1::n == 2, "fix later" ); // TODO
	static_assert( T2::n == 2, "fix later" ); // TODO

	using T00 = typename Add<typename Mult<typename T1::template get<0,0>::type, typename T2::template get<0,0>::type>::type,typename Mult<typename T1::template get<0,1>::type,typename T2::template get<1,0>::type>::type>::type;
	using T01 = typename Add<typename Mult<typename T1::template get<0,0>::type, typename T2::template get<0,1>::type>::type,typename Mult<typename T1::template get<0,1>::type,typename T2::template get<1,1>::type>::type>::type;
	using T10 = typename Add<typename Mult<typename T1::template get<0,1>::type, typename T2::template get<0,0>::type>::type,typename Mult<typename T1::template get<1,1>::type,typename T2::template get<0,1>::type>::type>::type;
	using T11 = typename Add<typename Mult<typename T1::template get<0,1>::type, typename T2::template get<1,0>::type>::type,typename Mult<typename T1::template get<1,1>::type,typename T2::template get<1,1>::type>::type>::type;
	using type = typename Matrix<typename T00::type, typename T01::type, typename T10::type, typename T11::type >::type; // TODO somewhere is a bug: missing function call, otherwise TXX::type wouldn't be necessary
};

template<typename T1, typename T2> struct MatrixAdd
{
	using newEntries = typename boost::mpl::transform<typename T1::entries, typename T2::entries, Add<boost::mpl::_1,boost::mpl::_2> >::type;
	using type = typename BindList<newEntries,Matrix>::type;
};

template<typename T1, typename T2> struct AntiCommutator
{
	using type = typename MatrixAdd<typename MatrixMult<typename T1::type,typename T2::type>::type, typename MatrixMult<typename T2::type,typename T1::type>::type >::type;
};

template<int N, int CurN> std::ostream& printMatrixHelper(std::ostream &out)
{
	return out;
}

template<int N, int CurN, typename First, typename... Entries> std::ostream& printMatrixHelper(std::ostream &out)
{
	out << First();
	if( CurN > 1 )
		out << ",";
	else if( sizeof...(Entries) > 0 )
		out << "\n" << std::setw( 8 ) << "";
	printMatrixHelper<N,(CurN > 1)?(CurN-1):(N),Entries...>(out);
	return out;
}

template<typename... Entries> std::ostream& operator<<( std::ostream &out, Matrix<Entries...> )
{
	out << std::left << std::setw( 8 ) << "Matrix[" ;
	printMatrixHelper<Matrix<Entries...>::n,Matrix<Entries...>::n,Entries...>(out);
	out << " ]";
	return out;
}

}

#endif
