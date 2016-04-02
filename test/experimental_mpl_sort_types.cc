#include "symbolicmath.h"

#include <typeinfo>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/min_element.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/sort.hpp>

namespace mpl = boost::mpl;

using mpl::_1;
using mpl::_2;

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

using namespace symbolicmath;
using namespace std;

int main()
{
	using list = mpl::vector<Int<3>,Int<1>,Int<7>,RuntimeValue<1>, Neg<Int<3>>>;

	PrintList<list>()();

	cout << typeid(mpl::int_<3>).name() << endl;

	cout << typeid(mpl::front<list>::type).name() << endl;
	cout << mpl::at_c<list,2>::type() << endl;

	using minType = typename mpl::min_element<list,
			Less<
				_1,
				_2>
		>::type;

	cout << mpl::deref<minType>::type() << endl;

	using maxType = typename mpl::max_element<list,
			Less<
				_1,
				_2>
		>::type;

	cout << mpl::deref<maxType>::type() << endl;

	using sortedList = typename mpl::sort<list,Less<_1,_2> >::type;

	PrintList<sortedList>()();
}
