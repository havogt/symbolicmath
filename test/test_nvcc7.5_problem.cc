/**
 * Compiling with nvcc (7.5) triggers the error (compilation with nvcc forced):
 * nvcc -x=cu -std=c++11 test_nvcc7.5_problem.cc
 *
 * While compiling with the same host compiler works (file is compiled with host compiler directly):
 * nvcc -std=c++11 test_nvcc7.5_problem.cc
 */

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
	using type = Bind<SomeStruct>::toTypesOf<tmp>::type;
}
