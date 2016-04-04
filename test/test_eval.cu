#include <iostream>

#include "symbolicmath.h"

using namespace symbolicmath;

using V0 = RuntimeValue<0>;
using V1 = RuntimeValue<1>;

__global__ void test_kernel()
{
	double d = Add<V0,V1>::type::eval(1.,2.);
	printf( "%f\n", d );
	
	using type = Real<Trace<MatrixMult<PauliMatrix<1>::type,MatrixMult<PauliMatrix<2>::type, SU2::type>::type>::type>::type>::type;
	d = type::eval( 1,2,3,4 );
	printf( "trace Matrix (expected: 4) =  %f\n", d );
}

int main()
{
	double d = Add<V0,V1>::type::eval(1.,2.);
	std::cout << d << std::endl;
	
	test_kernel<<<1,1>>>();
	cudaDeviceSynchronize();
}
