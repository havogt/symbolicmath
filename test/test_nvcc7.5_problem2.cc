#include <iostream>


namespace void_details
{
    template <typename... > struct make_void { using type = void; };
}

template<typename... T> using void_t = typename void_details ::make_void<T...>::type;



template<typename... Ts> struct TemporaryBindObject
{
	using type = TemporaryBindObject<Ts...>;
};
//
//
//template<template<typename...> class Dest, typename... Ts, typename = void> struct TryToBind
//{
////	template<typename T = void> struct apply;
////	template<> struct apply<void_t<Dest<Ts...> >
////	{
//		using type = Dest<Ts...>;
////	};
//};


//template<template<typename...> class Dest, typename... Ts> struct TryToBind<Dest, Ts..., Dest<Ts...>>
//{
//	using type = Dest<Ts...>;
//
//	template<typename T> struct apply;
//	template<> struct apply<Dest<Ts...>>
//	{
//		using type = Dest<Ts...>;
//	}
//	template<> struct apply<Dest<Ts...,void>>
//	{
//		using type = Dest<Ts...,void>;
//	}
//};

template<template<typename...> class Dest> struct TestValidBind
{
	template<typename T,  typename = void> struct toTypesOf
	{
		using type = std::false_type;
	};
	template<template<typename...> class Src, typename... NewTs> struct toTypesOf<Src<NewTs...>, void_t<typename Dest<NewTs...>::type>>
	{
		using type = std::true_type;
	};
};

//template<template<typename...> class Dest> struct Bind
//{
//	template<typename T, typename T2=void> struct toTypesOf;
//	template<template<typename...> class Src, typename... NewTs> struct toTypesOf<Src<NewTs...>, typename std::enable_if<TestValidBind<Dest>::toTypesOf<NewTs...>::type::value>::type >
//	{
//		using type = Dest<NewTs...>;
//	};
//	template<template<typename...> class Src, typename... NewTs> struct toTypesOf<Src<NewTs...>, void_t<Dest<NewTs...,void>>>
//	{
//		using type = Dest<NewTs...,void>;
//	};
//};

//template<template<typename...> class Dest> struct BindWithVoid
//{
//	template<typename T> struct toTypesOf;
//	template<template<typename...> class Src, typename... NewTs> struct toTypesOf<Src<NewTs...>>
//	{
//		using type = Dest<NewTs...,void>;
//	};
//};

//template<typename T> struct TypeTraitType
//{
//	using type = int;
//};

template<typename T1, typename = void> struct SomeStruct
{
	using type = int;
	static constexpr int value = 1;
};
template<typename T1> struct SomeStruct2
{
	using type = int;
	static constexpr int value = 1;
};

int main()
{
	using tmp = TemporaryBindObject<int>;

//	using type = Bind<SomeStruct>::toTypesOf<tmp>::type;

	if( TestValidBind<SomeStruct>::toTypesOf<tmp>::type::value )
	{
		std::cout << "is valid" << std::endl;
	}
	else
	{
		std::cout << "NOT valid" << std::endl;
	}
	if( TestValidBind<SomeStruct2>::toTypesOf<tmp>::type::value )
	{
		std::cout << "is valid" << std::endl;
	}
	else
	{
		std::cout << "NOT valid" << std::endl;
	}
}
