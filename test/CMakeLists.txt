project(symbolicmath_tests)

cmake_minimum_required(VERSION 2.8)

#========================================================

include_directories( ../include )

#set(CMAKE_CXX_STANDARD 11)
add_definitions(-std=c++11) 
add_definitions ("-Wall")

add_executable( test_compiletime_scalar
    test_compiletime_scalar.cc
    )
    
add_executable( test_compiletime_arithmetic
    test_compiletime_arithmetic.cc
    )

add_executable( experimental_mpl_sort_types
    experimental_mpl_sort_types.cc
    )
    
add_executable( experimental_mpl_rebind_from_list
    experimental_mpl_rebind_from_list.cc
    )
    
add_executable( test_compiletime_matrix
    test_compiletime_matrix.cc
    )
    
add_executable( test_eval
    test_eval.cc
    )
    
add_executable( test_gcc4_problem
    test_gcc4_problem.cc
    )
    
    
find_package( CUDA )

set( CUDA_NVCC_FLAGS "-std=c++11" )

cuda_add_executable( test_eval_cuda
	test_eval.cu
	)