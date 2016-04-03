#include "symbolicmath.h"
#include <iostream>

using namespace symbolicmath;
using namespace std;

void CollapseExpressionWithZero()
{
	using type = Mult<Zero::type,Complex<Zero::type,One::type>::type>::type;
	cout << type() << endl;
}
void CollapseExpressionWithZeroAndAddMult()
{
	using type = Add<Mult<Zero::type,Complex<Zero::type,One::type>::type>::type, Mult<Zero::type,Complex<Zero::type,One::type>::type>::type>::type;
	cout << type() << endl;
}

void TestLess()
{
	using type = typename symbolicmath::Less<
			Mult<Int<0>, Int<1> >
			, Int<0>
			>::type;
	using type2 = typename symbolicmath::Less<
			Mult<Int<0>, Complex<Int<0>, Int<1> > >
			, Int<0>
			>::type;

	using type3 = SortAndBind<Mult,Int<0>, Complex<Int<0>, Int<1> > >::type; // should not evaluate

	cout << type() << endl;
	cout << type2() << endl;
	cout << type3() << endl;
}

int main()
{
	CollapseExpressionWithZero();
	CollapseExpressionWithZeroAndAddMult();
	TestLess();
}
