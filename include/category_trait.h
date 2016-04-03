#ifndef CATEGORY_TRAIT_H_
#define CATEGORY_TRAIT_H_

namespace symbolicmath
{

enum class Category { INT, COMPLEX, SQRT, SIN, RUNTIME_VALUE, NEG, ADD, MULT};
template<typename T> struct CategoryTrait;

}
#endif
