#ifndef SYMBOLICMATH_TYPE_TRAITS_H_
#define SYMBOLICMATH_TYPE_TRAITS_H_

#include <type_traits>

namespace symbolicmath
{

template<int I> struct CaptureInt{};

template<bool B> struct BoolToType
{
	using type = std::true_type;
};

template<> struct BoolToType<false>
{
	using type = std::false_type;
};

template<typename T> struct HasCompareValue
{
	using true_char = char[1];
	using false_char = char[2];

	template<typename C> static true_char& test( CaptureInt<C::compare_value>* );

	template<typename> static false_char& test(...);

	using type = typename BoolToType<sizeof(test<T>(nullptr))==sizeof(true_char)>::type;
};


/*
 * Doesn't work in g++ 4.x.
 * Bug?
 *

template <typename... Ts> using void_t = void;

template<typename T, typename = void> struct HasCompareValue
{
	using type = std::false_type;
};

template<typename T> struct HasCompareValue<T,void_t<CaptureInt<T::compare_value>>>
{
	using type = std::true_type;
};
*/

}



#endif /* SYMBOLICMATH_TYPE_TRAITS_H_ */
