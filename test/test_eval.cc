#include "symbolicmath.h"

using namespace symbolicmath;

using V0 = RuntimeValue<0>;
using V1 = RuntimeValue<1>;

int main()
{
	double d = Add<V0,V1>::type::eval(1.,2.);
	std::cout << d << std::endl;
}
