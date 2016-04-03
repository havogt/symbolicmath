#ifndef CXX14_TYPES_H_
#define CXX14_TYPES_H_

namespace symbolicmath
{

#if __cplusplus < 201402L

template< bool B, class T = void >
using enable_if_t = typename std::enable_if<B,T>::type;

#else

using std::enable_if_t;

#endif

}

#endif
