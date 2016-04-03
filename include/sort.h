#include "compare.h"
#include "helper/type_manipulation.h"

#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/variant/variant.hpp>

namespace symbolicmath
{

template<typename... Ts> struct Sort
{
	using tmpList = boost::mpl::vector<Ts...>;
	using sortedList = typename boost::mpl::sort<tmpList, Less<boost::mpl::_1, boost::mpl::_2>>::type;

	template<int I> struct at
	{
		using type = typename boost::mpl::deref<boost::mpl::at_c<sortedList,I>>::type;
	};
};

template<template<typename...> class Template, typename... Ts> struct SortAndBind
{
	using sortedList = typename Sort<Ts...>::sortedList;
	using type = typename BindList<sortedList,Template>::type;
};

template<typename T> struct SortNested;

template<template<typename...> class Template, typename... Ts> struct SortNested<Template<Ts...>>
{
	using sortedList = typename Sort<Ts...>::sortedList;
	using type = typename BindList<sortedList,Template>::type;
};

}
