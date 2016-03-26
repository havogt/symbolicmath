#ifndef SYMBOLICMATH_H_
#define SYMBOLICMATH_H_

enum class Category { INT, COMPLEX, SQRT, SIN, RUNTIME_VALUE, NEG, ADD, MULT};

#include <type_traits>
#include <ostream>

#include "eval.h"
#include "scalar.h"
#include "arithmetic.h"
#include "complex.h"
#include "math_functions.h"
#include "print.h"

#endif
