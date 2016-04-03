#ifndef MATRIX_H_
#define MATRIX_H_

#include "arithmetic.h"

#include <iomanip>

#include "boost/mpl/vector.hpp"
#include "boost/mpl/at.hpp"
#include "boost/mpl/deref.hpp"

namespace symbolicmath
{

template<int N, typename... Entries> struct Matrix
{
	using type = Matrix<N, Entries...>;

	using entries = boost::mpl::vector<Entries...>;
	static constexpr int n = N;
	static_assert( N*N == sizeof...(Entries), "size of matrix and number of entries do not match" );

	template<int I, int J> struct get
	{
		using type = typename boost::mpl::deref<typename boost::mpl::at_c<entries,I+J*N>::type>::type;
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
	using type = typename Matrix<T1::n, T00, T01, T10, T11 >::type;
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

template<int N, typename... Entries> std::ostream& operator<<( std::ostream &out, Matrix<N,Entries...> )
{
	out << std::left << std::setw( 8 ) << "Matrix[" ;
	printMatrixHelper<N,N,Entries...>(out);
	out << " ]";
	return out;
}

}

#endif
