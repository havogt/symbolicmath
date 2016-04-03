#ifndef TYPE_MANIPULATION_H_
#define TYPE_MANIPULATION_H_

#include "boost/mpl/fold.hpp"
#include "boost/mpl/placeholders.hpp"

namespace symbolicmath
{

template<typename T> struct AddTypeImpl;

template<template <typename...> class OldType, typename... Ts> struct AddTypeImpl<OldType<Ts...>>
{
	template<typename... AddTs> struct apply
	{
		using type = OldType<Ts...,AddTs...>;
	};
};

template<typename T, typename Add> struct AddType
{
	using type = typename AddTypeImpl<T>::template apply<Add>::type;
};

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

template<typename List> struct BindListToTemporary
{
	using type = typename boost::mpl::fold<List,TemporaryBindObject<>,AddType<boost::mpl::_1,boost::mpl::_2>>::type;
};

/**
 * If all template classes would accept any number of template parameters, we could directly fold the list to the
 * template parameters. In general, we need to bind the parameters first to a temporary template class, and then bind all
 * template parameters at once to the destination (i.e. with the correct number of template parameters).
 */
template<typename List, template<typename...> class Template> struct BindList
{
	using type = typename Bind<Template>::template toTypesOf<typename BindListToTemporary<List>::type>::type;
};

}

#endif
