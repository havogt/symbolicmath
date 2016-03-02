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

	myprint<Mult<Two, Two>::type>::print();

	myprint<Complex<Two, One>::type >::print();

	myprint<result>::print();
	myprint<result2>::print();
	myprint<result3>::print();
	myprint<result4>::print();

	std::cout << sqrt(sin(2.)) << std::endl;
	std::cout << ToDouble<Sqrt<Two> >::eval() << std::endl;
	std::cout << ToDouble<Sqrt<Sin<Two> > >::eval() << std::endl;
}