/*
 * compare.h
 *
 *  Created on: Mar 3, 2016
 *      Author: vogt
 */

#ifndef COMPARE_H_
#define COMPARE_H_

namespace symbolicmath
{

template <typename... Ts> using void_t = void;

template<typename T1, typename T2, typename = void> struct LessType{};
template<typename T1, typename T2, typename = void> struct LessValue{};

template<typename T1, typename T2, typename = void> struct Less
{
	using type = typename LessType<T1,T2>::type;
};

template<typename T1, typename T2> struct Less<T1,T2,void_t<Int<T1:: compare_value>, Int<T2:: compare_value> > >
{
	using type = typename LessValue<T1,T2>::type;
};

template<typename T1, typename T2> struct LessType<T1,T2,typename std::enable_if<(T1::category <= T2::category) && !(T1::category >= T2::category)>::type>
	: std::true_type{};

template<typename T1, typename T2> struct LessType<T1,T2,typename std::enable_if<(T1::category >= T2::category) && !(T1::category <= T2::category)>::type>
	: std::false_type{};

template<typename T1, typename T2> struct LessType<T1,T2,typename std::enable_if<(T1::category >= T2::category) && (T1::category <= T2::category)>::type>
{
	using type = typename Less<typename T1::nested_type, typename T2::nested_type>::type;
};

template<typename T1, typename T2> struct LessValue<T1,T2, typename std::enable_if<(T1::compare_value >= T2::compare_value) && !(T1::compare_value <= T2::compare_value)>::type >
{
	using type = std::false_type;
};

template<typename T1, typename T2> struct LessValue<T1,T2, typename std::enable_if<T1::compare_value <= T2::compare_value>::type >
{
	using type = std::true_type;
};

}




#endif /* INCLUDE_COMPARE_H_ */
