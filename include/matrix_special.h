#ifndef MATRIX_SPECIAL_H_
#define MATRIX_SPECIAL_H_

#include "matrix.h"

namespace symbolicmath
{

template<int I> struct PauliMatrix;

template<> struct PauliMatrix<0>
{
	// TODO identity
};

template<> struct PauliMatrix<1>
{
	using type = Matrix<Zero::type,One::type,One::type,Zero::type>::type;
};
template<> struct PauliMatrix<2>
{
	using type = Matrix<Zero::type,Neg<Complex<Zero::type,One::type>::type>::type,Complex<Zero::type,One::type>::type,Zero::type>::type;
};
template<> struct PauliMatrix<3>
{
	using type = Matrix<One::type,One::type,Zero::type,Neg<One::type>::type>::type;
};

struct SU2
{
	using V0 = RuntimeValue<0>::type;
	using V1 = RuntimeValue<1>::type;
	using V2 = RuntimeValue<2>::type;
	using V3 = RuntimeValue<3>::type;
	using type = Matrix<Complex<V0,V1>::type,Complex<V2,V3>::type, Complex<Neg<V2>::type,V3>::type, Complex<V0,Neg<V1>::type>::type >::type;
};

}

#endif /* INCLUDE_MATRIX_SPECIAL_H_ */
