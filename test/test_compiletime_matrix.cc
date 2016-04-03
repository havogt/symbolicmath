#include "symbolicmath.h"
#include <iostream>

using namespace symbolicmath;
using namespace std;

using matrix = Matrix<Int<4>,Int<3>,Int<2>,Int<1>>;

void MatrixPrints()
{
	cout << matrix() << endl;
}

void GetElementWorks()
{
	using type = matrix::get<1,1>::type;
	static_assert( std::is_same<type,Int<1>::type>::value, "GetElementWorks" );
	cout << type() << endl;
}

void TraceWorks()
{
	using type = Trace<matrix>::type;
	static_assert( std::is_same<Add<Int<4>,Int<1>>::type,type>::value, "TraceWorks" );
	cout << type() << endl;
}

void MatrixMultWorks()
{
	using type = MatrixMult<PauliMatrix<1>::type, PauliMatrix<1>::type>::type;
	cout << type() << endl;
	cout << Trace<type>::type::eval() << endl;
	cout << MatrixMult<PauliMatrix<2>::type, PauliMatrix<2>::type>::type() << endl;
}

void PrintSU2()
{
	cout << SU2::type() << endl;
}

void FaddeevPopovApplication()
{
	cout << Real<Trace<MatrixMult<PauliMatrix<1>::type,MatrixMult<PauliMatrix<2>::type, SU2::type>::type>::type>::type>::type() << endl;
}

void TestAntiCommutator()
{
	cout << AntiCommutator<PauliMatrix<1>::type, PauliMatrix<2>::type>::type() << endl;
}

int main()
{
	MatrixPrints();
	GetElementWorks();
	TraceWorks();
	MatrixMultWorks();
	PrintSU2();
	FaddeevPopovApplication();
	TestAntiCommutator();
}
