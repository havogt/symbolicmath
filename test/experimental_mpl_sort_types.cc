#include "symbolicmath.h"

#include <typeinfo>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/min_element.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/deref.hpp>

namespace bmpl = boost::mpl;

using bmpl::_1;
using bmpl::_2;

namespace symbolicmath
{

}



using namespace symbolicmath;
using namespace std;

int main()
{
//	using list = bmpl::vector<Int<3>,Int<1>,Int<7>>;
	using list = bmpl::vector<bmpl::int_<3>,bmpl::int_<1>,bmpl::int_<7>>;


	cout << typeid(bmpl::int_<3>).name() << endl;

	cout << typeid(bmpl::front<list>::type).name() << endl;
	cout << bmpl::at_c<list,2>::type() << endl;

	using mytype = typename bmpl::min_element<list,
			bmpl::less<
				_1,
				_2>
		>::type;

	cout << bmpl::deref<mytype>::type() << endl;

//	using mytype = typename bmpl::min_element<list,
//			bmpl::less<
//				bmpl::int_<bmpl::_1::value>,
//				bmpl::int_<bmpl::_2::value>
//		>>::type;

//	cout << bmpl::min_element<list, bmpl::less<bmpl::int_<bmpl::_1::value>,bmpl::int_<bmpl::_2::value>>::type() << endl;
}
