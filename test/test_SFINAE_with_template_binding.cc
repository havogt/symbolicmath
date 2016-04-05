/**
 * Solution from http://stackoverflow.com/a/36411945/5085250
 *
 * Works with g++-6.0.0, g++-5.3.1, g++-4.9.1, g++-4.8.3, clang++-3.8.0
 */

#include <iostream>

// workaround for g++-4.x
namespace void_details
{
    template <typename... > struct make_void { using type = void; };
}
template<typename... T> using void_t = typename void_details ::make_void<T...>::type;

template<typename... Ts> struct TemporaryBindObject{};

template<template<typename...> class Dest, typename T, typename = void> struct IsValidBindImpl
		: std::false_type{};

template<template<typename...> class Dest, template<typename...> class Src, typename... Ts> struct IsValidBindImpl<Dest, Src<Ts...>, void_t<Dest<Ts...>> >
		: std::true_type{};

template<template<typename...> class Dest, typename... Ts>
using IsValidBind = IsValidBindImpl<Dest,TemporaryBindObject<Ts...>>;

template<template<typename...> class Dest, typename... Ts>
using IsValidBindWithVoid = IsValidBind<Dest, Ts...,void>;

template<typename T> struct OneParamStruct
{
};
template<typename T1, typename T2> struct TwoParamStruct
{
};

int main()
{
	std::cout << "Can bind to TwoParamStruct: " << IsValidBind<TwoParamStruct, int>::value << std::endl;
	std::cout << "Can bind to OneParamStruct: " << IsValidBind<OneParamStruct, int>::value << std::endl;

	std::cout << "Can bind to TwoParamStruct: " << IsValidBindWithVoid<TwoParamStruct, int>::value << std::endl;
	std::cout << "Can bind to OneParamStruct: " << IsValidBindWithVoid<OneParamStruct, int>::value << std::endl;
}
