#ifndef SCALAR_H_
#define SCALAR_H_

enum class Category { INT, COMPLEX, SQRT, SIN,  };

struct Zero
{
	using type = Zero;
	static constexpr int value = 0;
	static constexpr Category category = Category::INT;
};

struct One
{
	using type = One;
	static constexpr int value = 1;
	static constexpr Category category = Category::INT;
};

template<int I> struct Int
{
	using type = Int<I>;
	static constexpr int value = I;
	static constexpr Category category = Category::INT;
};

template<> struct Int<0>
{
	using type = Zero;
	static constexpr int value = 0;
	static constexpr Category category = Category::INT;
};

#endif
