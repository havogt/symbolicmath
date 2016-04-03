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
	using type = Matrix<2,Zero::type,One::type,One::type,Zero::type>::type;
};
template<> struct PauliMatrix<2>
{
	using type = Matrix<2,Zero::type,Neg<Complex<Zero::type,One::type>::type>::type,Complex<Zero::type,One::type>::type,Zero::type>::type;
};

}

#endif /* INCLUDE_MATRIX_SPECIAL_H_ */
