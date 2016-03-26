#ifndef SCALAR_H_
#define SCALAR_H_

namespace symbolicmath
{

template<int I> struct Int
{
	using type = Int<I>;
	static constexpr int value = I;
	static constexpr int compare_value = value;
	static constexpr Category category = Category::INT;
};

template<int I> std::ostream& operator<<( std::ostream &out, Int<I> )
{
	out << "Int<"<< I << ">";
	return out;
}

std::ostream& operator<<( std::ostream &out, Int<0> )
{
	out << "Zero";
	return out;
}

std::ostream& operator<<( std::ostream &out, Int<1> )
{
	out << "One";
	return out;
}

using Zero = Int<0>;
using One = Int<1>;

template<int I> struct RuntimeValue
{
	using type = RuntimeValue<I>;
	using nested_type = Int<I>;
	static constexpr Category category = Category::RUNTIME_VALUE;
	static double value;
};

template<int I> std::ostream& operator<<( std::ostream &out, RuntimeValue<I> )
{
	out << "RV" << I;
	return out;
}

template<int I> double RuntimeValue<I>::value;

}

#endif
