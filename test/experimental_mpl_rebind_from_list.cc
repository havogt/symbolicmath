#include "symbolicmath.h"

#include <iostream>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/placeholders.hpp>

using namespace std;
using namespace symbolicmath;


namespace mpl = boost::mpl;

using mpl::_1;
using mpl::_2;
void printAll()
{
}

template<typename First> void printAll( First first )
{
	cout << first;
}

template<typename First, typename... Rest> void printAll( First first, Rest... rest )
{
	cout << first << ",";
	printAll( rest... );
}

template<typename... Ts> struct SomeStruct
{
	using type = SomeStruct<Ts...>;
};

template<typename... Ts> std::ostream& operator<<( std::ostream &out, SomeStruct<Ts...> )
{
	cout << "SomeStruct<";
	printAll( Ts()... );
	cout << ">";
	return out;
}


struct PrintElem
{
	template<typename T> void operator()( T )
	{
		std::cout << T() << ", ";
	}
};

template<typename list> struct PrintList
{
	void operator()()
	{
		std::cout << "[";
		mpl::for_each<list>( PrintElem() );
		std::cout << "]" << std::endl;
	}
};

int main()
{
	using list = mpl::vector<Int<3>,Int<5>>;

	PrintList<list>()();

	using someStruct1 = SomeStruct<>;
	using someStruct2 = AddTypeImpl<someStruct1>::apply<Int<7>,Int<8>>::type;
	using someStruct3 = AddType<someStruct2,Int<13>>::type;
	cout << someStruct1() << endl;
	cout << someStruct2() << endl;
	cout << someStruct3() << endl;

	using type = BindList<list,SomeStruct>::type;
	cout << type() << endl;
}
