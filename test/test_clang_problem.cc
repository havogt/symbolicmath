#include <iostream>
#include <typeinfo>

/**
 * Problem is described here:
 * http://stackoverflow.com/a/3052618/5085250
 */

//template<typename T> struct BindInstantiated;
//template<template<typename...> class Template, typename T> struct BindInstantiated<Template<T>>
//{
//	template<typename NewT> struct apply
//	{
//		using type = Template<NewT>;
//	};
//};
//
//template<typename T> struct Add
//{
//	using type = typename BindInstantiated<Add<void>>::apply<T>::type;
//};
//
//int main()
//{
//	std::cout << typeid( Add<int>::type ).name() << std::endl;
//}



template<template<typename...> class Template> struct Bind
{
	template<typename NewT> struct apply
	{
		using type = Template<NewT>;
	};
};

template<typename T> struct Add
{
	using type = typename Bind<::Add>::apply<T>::type;
};

int main()
{
	std::cout << typeid( Add<int>::type ).name() << std::endl;
}
