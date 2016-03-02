template<typename T> struct ToDouble
{
	static double eval()
	{
		return T::value;
	}
};
