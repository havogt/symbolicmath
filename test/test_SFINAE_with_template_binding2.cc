/**
 * This solution is from http://stackoverflow.com/a/36412472/5085250
 * as an answer to my question and works with gcc and clang
 */

#include <iostream>

template<typename... T> using void_t = void;

template<typename T> struct TemporaryBindObject
{
	using type = TemporaryBindObject<T>;
};


template<class T>struct tag{using type=T;};
template<template<class...>class Z>struct ztag{
  template<class...Ts>using result=Z<Ts...>;
};

namespace details {
  template<class Src, class Target, class=void>
  struct rebind {};
  template<template<class...>class Src, template<class...>class Target, class...Ts>
  struct rebind<Src<Ts...>, ztag<Target>, void_t<Target<Ts...>>>:
    tag<Target<Ts...>>
  {};
}
template<class Src, class zDest>
using rebind = typename details::rebind<Src,zDest>::type;

namespace details {
  template<template<class...>class Z, class, class...Ts>
  struct can_apply : std::false_type {};
  template<template<class...>class Z, class...Ts>
  struct can_apply<Z, void_t<Z<Ts...>>, Ts...> : std::true_type {};
}
template<template<class...>class Z, class...Ts>
using can_apply = typename details::can_apply<Z, void, Ts...>::type;

template<class...>struct types{using type=types;};

namespace details {
  template<class types, class...Us>
  struct append;
  template<class...Ts, class...Us>
  struct append<types<Ts...>, Us...>:
    types<Ts..., Us...>
  {};
}
template<class types, class...Us>
using append = typename details::append<types, Us...>::type;

template<class Src, template<class...>class Dest>
using can_rebind_with_void =
  can_apply< rebind, append< rebind<Src, ztag<types>>, void >, ztag<Dest> >;



template<typename T> struct OneParamStruct
{
};
template<typename T1, typename T2> struct TwoParamStruct
{
};

int main()
{
	using tmp = TemporaryBindObject<int>;

	std::cout << can_rebind_with_void<tmp,TwoParamStruct>::value << std::endl;
	std::cout << can_rebind_with_void<tmp,OneParamStruct>::value << std::endl;

//	std::cout << "Can bind to TwoParamStruct: " << TestValidBind<TwoParamStruct>::toTypesOf<tmp>::value << std::endl;
//	std::cout << "Can bind to OneParamStruct: " << TestValidBind<OneParamStruct>::toTypesOf<tmp>::value << std::endl;
}
