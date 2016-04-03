/*
 * cuda_common.h
 *
 *  Created on: Apr 3, 2016
 *      Author: vogt
 */

#ifndef CUDA_COMMON_H_
#define CUDA_COMMON_H_

#ifdef __CUDA_ARCH__
#define CUDA_HOST_DEVICE __device__ __host__
#define CUDA
#else
#define CUDA_HOST_DEVICE
#endif




#endif /* INCLUDE_HELPER_CUDA_COMMON_H_ */
