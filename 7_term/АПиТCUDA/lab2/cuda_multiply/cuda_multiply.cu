#include <iostream>
#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath> // для fabsf

// Функция для создания матрицы с случайными значениями
std::vector<std::vector<float>> create_random_matrix(int rows, int cols) {
    std::vector<std::vector<float>> matrix(rows, std::vector<float>(cols));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            matrix[i][j] = dis(gen);

    return matrix;
}

// Ядро CUDA для отражения по вертикали
__global__ void flip_vertically_gpu(float* matrix, float* result, int rows, int cols) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int total_size = rows * cols;

    if (idx < total_size) {
        int row = idx / cols;
        int col = idx % cols;
        int new_row = rows - 1 - row;
        result[new_row * cols + col] = matrix[row * cols + col];
    }
}

// Ядро CUDA для отражения по горизонтали
__global__ void flip_horizontally_gpu(float* matrix, float* result, int rows, int cols) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int total_size = rows * cols;

    if (idx < total_size) {
        int row = idx / cols;
        int col = idx % cols;
        int new_col = cols - 1 - col;
        result[row * cols + new_col] = matrix[row * cols + col];
    }
}

// Функция для отражения по вертикали на CPU
std::vector<std::vector<float>> flip_vertically(const std::vector<std::vector<float>>& matrix) {
    std::vector<std::vector<float>> flipped(matrix);
    std::reverse(flipped.begin(), flipped.end());
    return flipped;
}

// Функция для отражения по горизонтали на CPU
std::vector<std::vector<float>> flip_horizontally(const std::vector<std::vector<float>>& matrix) {
    std::vector<std::vector<float>> flipped(matrix);
    for (auto& row : flipped)
        std::reverse(row.begin(), row.end());
    return flipped;
}

// Функция для замера времени выполнения на CPU
void measure_cpu(const std::vector<std::vector<float>>& matrix, std::vector<std::vector<float>>& result) {
    auto start = std::chrono::high_resolution_clock::now();

    // Отражение по вертикали
    auto vertically_flipped = flip_vertically(matrix);

    // Отражение по горизонтали
    result = flip_horizontally(vertically_flipped);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    std::cout << "CPU Time: " << duration.count() << " seconds" << std::endl;
}

// Функция для замера времени выполнения на GPU
void measure_gpu(float* d_matrix, float* d_temp_matrix, float* d_result_matrix, int rows, int cols) {
    int total_size = rows * cols;
    int threads_per_block = 256;
    int blocks = (total_size + threads_per_block - 1) / threads_per_block;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    // Отражение по вертикали
    flip_vertically_gpu<<<blocks, threads_per_block>>>(d_matrix, d_temp_matrix, rows, cols);
    cudaDeviceSynchronize();

    // Отражение по горизонтали
    flip_horizontally_gpu<<<blocks, threads_per_block>>>(d_temp_matrix, d_result_matrix, rows, cols);
    cudaDeviceSynchronize();

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
    std::cout << "GPU Time: " << milliseconds / 1000.0 << " seconds" << std::endl;

    cudaEventDestroy(start);
    cudaEventDestroy(stop);
}

// Полное поэлементное сравнение матриц
bool compare_results(const std::vector<std::vector<float>>& cpu_matrix, const std::vector<float>& gpu_matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (fabsf(cpu_matrix[i][j] - gpu_matrix[i * cols + j]) > 1e-5) {
                return false; // Результаты различаются
            }
        }
    }
    return true; // Результаты совпадают
}

int main() {
    int rows = 1000, cols = 1000;
    size_t matrix_size = rows * cols * sizeof(float);

    // Создание матрицы на CPU
    auto cpu_matrix = create_random_matrix(rows, cols);

    // Копирование данных в линейный массив для GPU
    std::vector<float> flat_cpu_matrix(rows * cols);
    for (int i = 0; i < rows; ++i)
        std::copy(cpu_matrix[i].begin(), cpu_matrix[i].end(), flat_cpu_matrix.begin() + i * cols);

    // Выделение памяти на GPU
    float* d_matrix;
    float* d_temp_matrix;
    float* d_result_matrix;
    cudaMalloc(&d_matrix, matrix_size);
    cudaMalloc(&d_temp_matrix, matrix_size);
    cudaMalloc(&d_result_matrix, matrix_size);

    // Копирование данных на GPU
    cudaMemcpy(d_matrix, flat_cpu_matrix.data(), matrix_size, cudaMemcpyHostToDevice);

    // Замер времени на CPU
    std::vector<std::vector<float>> cpu_result(rows, std::vector<float>(cols));
    measure_cpu(cpu_matrix, cpu_result);

    // Замер времени на GPU
    measure_gpu(d_matrix, d_temp_matrix, d_result_matrix, rows, cols);

    // Получение результатов с GPU
    std::vector<float> gpu_result(rows * cols);
    cudaMemcpy(gpu_result.data(), d_result_matrix, matrix_size, cudaMemcpyDeviceToHost);

    // Сравнение результатов
    if (compare_results(cpu_result, gpu_result, rows, cols)) {
        std::cout << "CPU and GPU results match!" << std::endl;
    } else {
        std::cout << "Results differ!" << std::endl;
    }

    // Освобождение памяти
    cudaFree(d_matrix);
    cudaFree(d_temp_matrix);
    cudaFree(d_result_matrix);

    return 0;
}
