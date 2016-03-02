struct Zero
{
	using type = Zero;
	static constexpr int value = 0;
};

struct One
{
	using type = One;
	static constexpr int value = 1;
};

template<int I> struct Int
{
	using type = Int<I>;
	static constexpr int value = I;
};

template<> struct Int<0>
{
	using type = Zero;
	static constexpr int value = 0;
};
