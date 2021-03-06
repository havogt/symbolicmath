#include <iostream>

namespace void_details
{
    template <typename... > struct make_void { using type = void; };
}
template<typename... T> using void_t = typename void_details ::make_void<T...>::type;

template<typename T> struct TemporaryBindObject
{
	using type = TemporaryBindObject<T>;
};

template<template<typename...> class Dest> struct TestValidBind
{
	template<typename T, typename = void_t<>> struct toTypesOf
		: std::false_type{};
	template<template<typename...> class Src, typename... Ts> struct toTypesOf<Src<Ts...>, void_t<Dest<Ts...,float>>>
		: std::true_type{};
};

template<typename T> struct OneParamStruct
{
};
template<typename T1, typename T2> struct TwoParamStruct
{
};

int main()
{
	using tmp = TemporaryBindObject<int>;

	std::cout << "Can bind to TwoParamStruct: " << TestValidBind<TwoParamStruct>::toTypesOf<tmp>::value << std::endl;
	std::cout << "Can bind to OneParamStruct: " << TestValidBind<OneParamStruct>::toTypesOf<tmp>::value << std::endl;
}
