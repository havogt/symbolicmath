#include <iostream>

template<typename... T> using void_t = void;

template<typename T> struct TemporaryBindObject
{
	using type = TemporaryBindObject<T>;
};

template<template<typename...> class Dest> struct TestValidBind
{
	template<typename T, typename = void_t<>> struct toTypesOf
	{
		using type = std::false_type;
	};
	template<template<typename...> class Src, typename... Ts> struct toTypesOf<Src<Ts...>, void_t<Dest<Ts...,float>>>
	{
		using type = std::true_type;
	};
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

	std::cout << "Can bind to TwoParamStruct: " << TestValidBind<TwoParamStruct>::toTypesOf<tmp>::type::value << std::endl;
	std::cout << "Can bind to OneParamStruct: " << TestValidBind<OneParamStruct>::toTypesOf<tmp>::type::value << std::endl;
}
