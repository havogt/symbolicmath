# symbolicmath
A small compile-time symbolic math library for c++

# Why mathematical calculations at compile-time
In the computation of the ghost propagator (and other applications) in lattice gauge theory some expression appear
which can be simplified easily by hand.
An example is the expression `Re tr S_1 S_2 U`, i.e. the real part of the trace of the product of 3 matrices, where S_i are known at compile-time (here the Pauli-matrices) and U is a general run-time matrix (or here an SU(2) matrix, representable as 2 complex numbers).
Simplified the expression is just one entry of the run-time matrix U. Since these expression have to be evaluated very often they have a significant effect on performance.
Therefore, usually such expressions are evaluated by hand (or a computer algebra software) for all combinations of Pauli matrices.

Instead of doing the calculation by hand the more interesting (though more time consuming, if you start from scratch) solution is to rely on template meta programming to simplify such expressions.
The positive effect is a more readable code, because you just put the mathematical expression instead of a complicated branching code.

The example from above would look like this:
```
Real<Trace<MatrixMult<PauliMatrix<1>::type,MatrixMult<PauliMatrix<2>::type, SU2::type>::type>::type>::type>::type
```
And the resulting type is `Mult<Int<2>,RuntimeValue<2>>`, i.e. 2 times the value of the runtime variable which is part of the 2x2 matrix U from the example.

The runtime values can be passed to the type via an `eval` function:
```
	using type = Real<Trace<MatrixMult<PauliMatrix<1>::type,MatrixMult<PauliMatrix<2>::type, SU2::type>::type>::type>::type>::type;
	double d = type::eval( 1,2,3,4 );
	printf( "trace Matrix (expected: 4) =  %f\n", d );
```
See `test/test_eval.cu` for this example.

# Should I use this library
Probably no, because the code is very incomplete and it does not work for arbitrary complicated expressions. For now it was taylored to support the application discussed above.

# Missing parts:
- Matrix multiplication is hard-coded to 2x2 matrices
- Complicated nessted `Add`s or `Mult`s are not supported because the types are only commuting within one `Add`/`Mult`. 

