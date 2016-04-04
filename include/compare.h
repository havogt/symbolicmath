/*
 * compare.h
 *
 *  Created on: Mar 3, 2016
 *      Author: vogt
 */

#ifndef COMPARE_H_
#define COMPARE_H_

#include "helper/void_t.h"
#include "helper/symbolicmath_type_traits.h"

namespace symbolicmath
{

template<typename T1, typename T2, typename = void> struct LessType;//{};
template<typename T1, typename T2, typename = void> struct LessValue{};

template<typename T1, typename T2, typename = void> struct Less;

template<typename T1, typename T2> struct Less<T1,T2,enable_if_t<HasCompareValue<T1>::type::value && HasCompareValue<T2>::type::value > >
{
	using type = typename LessValue<T1,T2>::type;
};
template<typename T1, typename T2> struct Less<T1,T2,enable_if_t<!(HasCompareValue<T1>::type::value && HasCompareValue<T2>::type::value) > >
{
	using type = typename LessType<T1,T2>::type;
};


template<typename T1, typename T2> struct LessType<T1,T2,enable_if_t<(CategoryTrait<T1>::category <= CategoryTrait<T2>::category) && !(CategoryTrait<T1>::category >= CategoryTrait<T2>::category)> >
	: std::true_type{};

template<typename T1, typename T2> struct LessType<T1,T2,enable_if_t<(CategoryTrait<T1>::category >= CategoryTrait<T2>::category) && !(CategoryTrait<T1>::category <= CategoryTrait<T2>::category)> >
	: std::false_type{};

template<typename T1, typename T2> struct LessType<T1,T2,enable_if_t<(CategoryTrait<T1>::category >= CategoryTrait<T2>::category) && (CategoryTrait<T1>::category <= CategoryTrait<T2>::category)> >
{
	using type = typename Less<typename T1::nested_type, typename T2::nested_type>::type;
};


template<typename T1, typename T2> struct LessValue<T1,T2, enable_if_t<(T1::compare_value >= T2::compare_value) && !(T1::compare_value <= T2::compare_value)> >
{
	using type = std::false_type;
};

template<typename T1, typename T2> struct LessValue<T1,T2, enable_if_t<T1::compare_value <= T2::compare_value> >
{
	using type = std::true_type;
};

}




#endif /* INCLUDE_COMPARE_H_ */
