#include <iostream>

#include "symbolicmath.h"
using namespace symbolicmath;

using V0 = RuntimeValue<0>;
using V1 = RuntimeValue<1>;
using V2 = RuntimeValue<2>;
using V3 = RuntimeValue<3>;

int main()
{
	double d = Add<V0,V1>::type::eval(1.,2.);
	assert( d == 3 );
	std::cout << d << std::endl;

	std::cout << "test: ";
	assert( V0::type::eval( 1, 2, 3, 4 ) == 1 );
	std::cout << "ok!" << std::endl;
	std::cout << "test: ";
	assert( V1::type::eval( 1, 2, 3, 4 ) == 2 );
	std::cout << "ok!" << std::endl;
	std::cout << "test: ";
	assert( V2::type::eval( 1, 2, 3, 4 ) == 3 );
	std::cout << "ok!" << std::endl;
	std::cout << "test: ";
	assert( V3::type::eval( 1, 2, 3, 4 ) == 4 );
	std::cout << "ok!" << std::endl;

	std::cout << "should fail at runtime: " << std::endl;
	std::cout << V3::type::eval( 1, 2, 3 ) << std::endl; // runtime assert fails (not enough parameters)
}
