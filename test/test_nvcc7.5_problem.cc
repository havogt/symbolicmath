#include <iostream>


template<typename... Ts> struct TemporaryBindObject
{
	using type = TemporaryBindObject<Ts...>;
};

template<template<typename...> class Dest> struct Bind
{
	template<typename T> struct toTypesOf;
	template<template<typename...> class Src, typename... NewTs> struct toTypesOf<Src<NewTs...>>
	{
		using type = Dest<NewTs...>;
	};
};

template<typename T1, typename = void> struct SomeStruct
{
};

int main()
{
	using tmp = TemporaryBindObject<int>;
	using type = BindWith<SomeStruct>::toTypesOf<tmp>::type;
}
