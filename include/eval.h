#ifndef EVAL_H_
#define EVAL_H_

namespace symbolicmath
{

template<typename T> struct ToDouble
{
	static double eval()
	{
		return T::value;
	}
};

}

#endif
