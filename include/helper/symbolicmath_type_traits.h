#ifndef SYMBOLICMATH_TYPE_TRAITS_H_
#define SYMBOLICMATH_TYPE_TRAITS_H_

#include <type_traits>
#include "helper/void_t.h"

namespace symbolicmath
{

template<typename T, typename = void> struct HasCompareValue
{
	using type = std::false_type;
};

template<typename T> struct HasCompareValue<T,void_t<decltype(T::compare_value)>>
{
	using type = std::true_type;
};

}



#endif /* SYMBOLICMATH_TYPE_TRAITS_H_ */
