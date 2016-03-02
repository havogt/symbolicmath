template<typename T1, typename T2> struct Sub
{
	using type = Sub<T1,T2>;
};

//template<typename T> struct Sub<T,T>
//{
//	using type = Zero;
//};

template<int I1, int I2> struct Sub<Int<I1>, Int<I2> >
{
	using type = typename Int<I1 - I2>::type;
};



template<typename T1, typename T2> struct Mult
{
	using type = Mult<T1, T2>;
};

template<int I1, int I2> struct Mult<Int<I1>, Int<I2> >
{
	using type = typename Int<I1 * I2>::type;
};

template<typename T1, typename T2> struct Add
{
	using type = Add<T1, T2>;
};

template<int I1, int I2> struct Add<Int<I1>, Int<I2> >
{
	using type = typename Int<I1 + I2>::type;
};
