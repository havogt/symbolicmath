#include "symbolicmath.h"
#include <iostream>
using namespace std;

using namespace symbolicmath;

using V0 = RuntimeValue<0>;
using V1 = RuntimeValue<1>;

void IntAddDecays()
{
	static_assert( std::is_same<Add<Int<3>::type,Int<5>::type>::type, Int<8>::type>::value, "IntAddDecays" );
	cout << Add<Int<3>::type,Int<5>::type>::type() << endl;
}

void AddCommutationOrder()
{
	static_assert( std::is_same<Add<V0,V1>::type, Add<V1,V0>::type>::value, "AddCommutationOrder" );
}

void IntMultDecays()
{
	static_assert( std::is_same<Mult<Int<3>::type,Int<5>::type>::type, Int<15>::type>::value, "IntMultDecays" );
	cout << Mult<Int<3>::type,Int<5>::type>::type() << endl;
}

void MultCommutationOrder()
{
	static_assert( std::is_same<Mult<V0,V1>::type, Mult<V1,V0>::type>::value, "MultCommutationOrder" );
}

void AddPrints()
{
	cout << Add<V0,V1>::type() << endl; // print non-decayed type
	cout << Add<V1,V0>::type() << endl; // print non-decayed type
}

void MultPrints()
{
	cout << Mult<V0,V1>::type() << endl; // print non-decayed type
	cout << Mult<V1,V0>::type() << endl; // print non-decayed type
}

int main()
{
	IntAddDecays();
	AddCommutationOrder();
	IntMultDecays();
	MultCommutationOrder();
	AddPrints();
	MultPrints();
}
