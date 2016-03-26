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

	using V0 = RuntimeValue<0>;
	using V1 = RuntimeValue<1>;

	using ResultOfRuntimeMult = Mult<Complex<V0,V1>::type,Complex<V0,Neg<V1>::type>::type>::type;

	V0::value = 2;
	V1::value = 4;

	myprint<Complex<V0,V1>::type>::print();
	cout << "\n";

	myprint<ResultOfRuntimeMult>::print();
	cout << "\n";

	using ResultOfRuntimeAdd = Add<V0,V1>::type;
	myprint<ResultOfRuntimeAdd>::print();
	cout << "\n";
	cout << ToDouble<ResultOfRuntimeAdd>::eval();
	cout << "\n";
	cout << ToDouble<ResultOfRuntimeMult>::eval();
	cout << "\n";

}
