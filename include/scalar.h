#ifndef SCALAR_H_
#define SCALAR_H_

enum class Category { INT, COMPLEX, SQRT, SIN, RUNTIME_VALUE, NEG};

struct Zero
{
	using type = Zero;
	static constexpr int value = 0;
	static constexpr int compare_value = value;
	static constexpr Category category = Category::INT;
};

struct One
{
	using type = One;
	static constexpr int value = 1;
	static constexpr int compare_value = value;
	static constexpr Category category = Category::INT;
};

template<int I> struct Int
{
	using type = Int<I>;
	static constexpr int value = I;
	static constexpr int compare_value = value;
	static constexpr Category category = Category::INT;
};

template<> struct Int<0>
{
	using type = Zero;
	static constexpr int value = 0;
	static constexpr int compare_value = value;
	static constexpr Category category = Category::INT;
};

template<int I> struct RuntimeValue
{
	using type = RuntimeValue<I>;
	using nested_type = Int<I>;
	static constexpr Category category = Category::RUNTIME_VALUE;
	static double value;
};

template<int I> double RuntimeValue<I>::value;

#endif
