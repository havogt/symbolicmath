#include <iostream>
#include "scalar.h"
#include "arithmetic.h"
#include "complex.h"
#include "eval.h"
#include "math_functions.h"
#include "print.h"


using namespace std;

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

	myprint<Mult<ComplexA, ComplexB>::type >::print();
	cout << "\n";
	myprint<Mult<Two, One>::type>::print();
	cout << "\n";

	myprint<Complex<Two, One>::type >::print();
	cout << "\n";

	myprint<result>::print();
	cout << "\n";
	myprint<result2>::print();
	cout << "\n";
	myprint<result3>::print();
	cout << "\n";
	myprint<result4>::print();
	cout << "\n";

	myprint<Sub<Sqrt<Two>, Sqrt<Two>>::type>::print();
	cout << "\n";

	myprint<Add<Sqrt<Two>, Neg<Sqrt<Two> > >::type>::print();
	cout << "\n";

	std::cout << sqrt(sin(2.)) << std::endl;
	std::cout << ToDouble<Sqrt<Two> >::eval() << std::endl;
	std::cout << ToDouble<Sqrt<Sin<Two> > >::eval() << std::endl;

	myprint<Add<Mult<Two, Sqrt<Two> >, Neg<Mult<Two, Sqrt<Two> > > >::type >::print();
	cout << "\n";
	myprint<Add<Mult<Two, Sqrt<Two> >::type, Neg<Mult<Sqrt<Two>, Two>::type >::type >::type >::print();
	cout << "\n";
	myprint<Add<Mult<Sqrt<One>, Sin<Two> >::type, Neg<Mult<Sin<Two>, Sqrt<One>>::type >::type >::type >::print();
	cout << "\n";

	myprint<Mult<Sqrt<One>, Sin<Two> >::type >::print();
	cout << "\n";
	myprint<Mult<Sin<Two>, Sqrt<One> >::type >::print();
	cout << "\n";
	myprint<Neg<Mult<Sqrt<Two>, Sin<One> >::type >::type>::print();
	cout << "\n";
	myprint<Mult<Sqrt<Two>, Sqrt<One> >::type>::print();
	cout << "\n";
	myprint<Mult<Sqrt<One>, Sqrt<Two> >::type>::print();
	cout << "\n";
	myprint<Mult<One, Sqrt<Two> >::type>::print();
	cout << "\n";
	myprint<Mult<Sqrt<Two>, One>::type>::print();
	cout << "\n";
}
