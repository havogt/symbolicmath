#include <iostream>
using namespace std;

template<typename T> struct myprint
{
	static void print()
	{
		cout << "Unknown type" << endl;
	}
};

template<> struct myprint<Zero>
{
	static void print()
	{
		cout << "Zero" << endl;
	}
};

template<int I> struct myprint<Int<I> >
{
	static void print()
	{
		cout << "Int(" << I << ")" << endl;
	}
};

template<typename T1, typename T2> struct myprint<Complex<T1, T2> >
{
	static void print()
	{
		cout << "Complex(";
		myprint<T1>::print();
		cout << ",";
		myprint<T2>::print();
		cout << ")" << endl;
	}
};
