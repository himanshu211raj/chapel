#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include  "cublas_v2.h"

float* cublas_array(size_t size){

    float *ptr;
    cudaError_t err = cudaMallocManaged(&ptr, size*sizeof(float), cudaMemAttachGlobal);
    //printf("CUDA Error: %s\n", cudaGetErrorString(err));
    cudaDeviceSynchronize();
    return ptr;

}

void* to_gpu(float* src_ptr, size_t size){
    float *dst_ptr;
    cudaError_t malloc_err = cudaMalloc(&dst_ptr, size);
    //printf("CUDA malloc error: %s\n", cudaGetErrorString(malloc_err));
    cudaError_t memcpy_err = cudaMemcpy(dst_ptr, src_ptr, size, cudaMemcpyHostToDevice);
    //printf("CUDA memcpy HtoD error: %s\n", cudaGetErrorString(memcpy_err));
    return dst_ptr;

}

void to_cpu(void* dst_ptr, void* src_ptr, size_t size){
    cudaError_t memcpy_err = cudaMemcpy(dst_ptr, src_ptr, size, cudaMemcpyDeviceToHost);
    //printf("CUDA memcpy DtoH error: %s\n", cudaGetErrorString(memcpy_err));
}

void* cublas_create(){

    cublasHandle_t *handle = (cublasHandle_t*)malloc(sizeof(cublasHandle_t));
    cublasStatus_t err = cublasCreate(handle);
    //printf("cublasCreate status: %s\n", cudaGetErrorString(err));
    return handle;

}

void cublas_destroy(cublasHandle_t *handle){

    cublasStatus_t err = cublasDestroy(*handle);
    //printf("cublasDestroy status: %s\n", cudaGetErrorString(err));

}


int cublas_saxpy(cublasHandle_t *handle, int n, float alpha, float *x, int incX, float *y, int incY){

    cublasSaxpy(*handle, n, &alpha, x, 1, y, 1);
    cudaDeviceSynchronize();
    return 0;

}

int cublas_axpy(cublasHandle_t *handle, int n, float alpha, void *x, int incX, void *y, int incY){

    cublasSaxpy(*handle, n, &alpha, x, 1, y, 1);
    cudaDeviceSynchronize();
    return 0;

}


/*
int cublas_daxpy(cublasHandle_t *handle, int n, double alpha, double *x, int incX, double *y, int incy){

    cublasDaxpy(*handle, n, &alpha, x, incX, y, incY);
    cudaDeviceSynchronize();
    return 0;

}
*/

int cublas_sgemm(cublasHandle_t *handle, int transa, int transb, int m, int n, int k, float alpha, float *A, int lda, float *B, int ldb, float beta, float *C, int ldc){

    cublasSgemm(*handle, transa, transb, m, n, k, &alpha, A, lda, B, ldb, &beta, C, ldc);
    cudaDeviceSynchronize();
    return 0;

}
