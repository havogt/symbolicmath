#ifndef PRINT_H_
#define PRINT_H_


#include <iostream>
using namespace std;

template<typename T> struct myprint
{
	static void print()
	{
		cout << "Unknown type";
	}
};

template<> struct myprint<Zero>
{
	static void print()
	{
		cout << "Zero";
	}
};

template<int I> struct myprint<Int<I> >
{
	static void print()
	{
		cout << "Int(" << I << ")";
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
		cout << ")";
	}
};

template<typename T1, typename T2> struct myprint<MultImpl<T1, T2> >
{
	static void print()
	{
		cout << "Mult(";
		myprint<T1>::print();
		cout << ",";
		myprint<T2>::print();
		cout << ")";
	}
};

template<typename T1, typename T2> struct myprint<Add<T1, T2> >
{
	static void print()
	{
		cout << "Add(";
		myprint<T1>::print();
		cout << ",";
		myprint<T2>::print();
		cout << ")";
	}
};

template<typename T1, typename T2> struct myprint<Sub<T1, T2> >
{
	static void print()
	{
		cout << "Sub(";
		myprint<T1>::print();
		cout << ",";
		myprint<T2>::print();
		cout << ")";
	}
};

template<typename T> struct myprint<Sqrt<T> >
{
	static void print()
	{
		cout << "Sqrt(";
		myprint<T>::print();
		cout << ")";
	}
};
template<typename T> struct myprint<Sin<T> >
{
	static void print()
	{
		cout << "Sin(";
		myprint<T>::print();
		cout << ")";
	}
};
template<typename T> struct myprint<Neg<T> >
{
	static void print()
	{
		cout << "Neg(";
		myprint<T>::print();
		cout << ")";
	}
};

#endif
