#include <iostream>
#include "symbolicmath.h"


using namespace std;

using namespace symbolicmath;

int main()
{
	using One = Int<1>;
	using Two = Int<2>;
	using MinusTwo = Int<-2>;
	using result = Sub<One, One>::type;
	using result2 = Sub<One, Two>::type;
	using result3 = Add<One, Two>::type;
	using result4 = Add<MinusTwo, Two>::type;

	using ComplexA = Complex<One, Two>;
	using ComplexB = Complex<One, MinusTwo>;

	cout << Mult<ComplexA, ComplexB>::type() << endl;
	cout << Mult<Two, One>::type() << endl;

	cout << Complex<Two, One>::type() << endl;

	cout << result() << endl;
	cout << result2() << endl;
	cout << result3() << endl;
	cout << result4() << endl;

	cout << Sub<Sqrt<Two>, Sqrt<Two>>::type() << endl;
	cout << Sub<Sqrt<Two>, Sqrt<One>>::type() << endl;

	cout << Add<Sqrt<Two>, Neg<Sqrt<Two> > >::type() << endl;

	cout << sqrt(sin(2.)) << endl;
	cout << Sqrt<Two>::eval() << endl;
	cout << Sqrt<Sin<Two> >::eval() << endl;

	cout << Add<Mult<Two, Sqrt<Two> >, Neg<Mult<Two, Sqrt<Two> > > >::type() << endl;
	cout << Add<Mult<Two, Sqrt<Two> >::type, Neg<Mult<Sqrt<Two>, Two>::type >::type >::type() << endl;
	cout << Add<Mult<Sqrt<One>, Sin<Two> >::type, Neg<Mult<Sin<Two>, Sqrt<One>>::type >::type >::type() << endl;

	cout << Mult<Sqrt<One>, Sin<Two> >::type() << endl;
	cout << Mult<Sin<Two>, Sqrt<One> >::type() << endl;
	cout << Neg<Mult<Sqrt<Two>, Sin<One> >::type >::type() << endl;
	cout << Mult<Sqrt<Two>, Sqrt<One> >::type() << endl;
	cout << Mult<Sqrt<One>, Sqrt<Two> >::type() << endl;
	cout << Mult<One, Sqrt<Two> >::type() << endl;
	cout << Mult<Sqrt<Two>, One>::type() << endl;

	using V0 = RuntimeValue<0>;
	using V1 = RuntimeValue<1>;

	using ResultOfRuntimeMult = Mult<Complex<V0,V1>::type,Complex<V0,Neg<V1>::type>::type>::type;

	cout << Complex<V0,V1>::type() << endl;

	cout << ResultOfRuntimeMult() << endl;

	using ResultOfRuntimeAdd = Add<V0,V1>::type;
	cout << ResultOfRuntimeAdd() << endl;

	cout << ResultOfRuntimeAdd::eval( 4., 1. ) << endl;
	cout << ResultOfRuntimeMult::eval( 5., 3.) << endl;
}
