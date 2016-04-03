#include "symbolicmath.h"
#include "helper/symbolicmath_type_traits.h"
#include <iostream>
using namespace std;
using namespace symbolicmath;

int main()
{

	if( HasCompareValue<Int<4>>::type::value )
	{
		cout << Int<4>() << " has compare value" << endl;
	}
	else
	{
		cout << Int<4>() << " doesn't have compare value" << endl;
	}

	if( HasCompareValue<Sqrt<Int<4>>>::type::value )
	{
		cout << Sqrt<Int<4>>() << " has compare value" << endl;
	}
	else
	{
		cout <<Sqrt<Int<4>>() << " doesn't have compare value" << endl;
	}

	if( Less<Sqrt<Int<4>>,Sin<Int<5>>>::type::value )
	{
		cout << "Less" << endl;
	}
	else
	{
		cout << "not" << endl;
	}
	if( Less<Sin<Int<5>>,Sqrt<Int<4>>>::type::value )
	{
		cout << "Less" << endl;
	}
	else
	{
		cout << "not" << endl;
	}
}
