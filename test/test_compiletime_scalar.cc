#include "symbolicmath.h"

using namespace symbolicmath;

void ZeroDecaysToInt0()
{
	static_assert( std::is_same<Zero::type, Int<0>>::value, "ZeroDecaysToInt0" );
	cout << Int<0>::type() << endl;
}

void OneDecaysToInt1()
{
	static_assert( std::is_same<One::type, Int<1>>::value, "OneDecaysToInt1" );
	cout << Int<1>::type() << endl;
}

void IntPrints()
{
	cout << Int<5>::type() << endl;
	cout << Int<1>::type() << endl;
	cout << Int<0>::type() << endl;
}

int main()
{
	ZeroDecaysToInt0();
	OneDecaysToInt1();
	IntPrints();
}
