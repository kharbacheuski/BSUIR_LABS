
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cassert>

#define ARRAY_SIZE 10000000  // Размер массива
#define BIN_COUNT 30000       // Количество корзин для гистограммы

// CUDA kernel для вычисления гистограммы
__global__ void cudaHistogram(const short* data, int* hist, int size) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;

    // Используем атомарные операции для корректного подсчета гистограммы
    if (idx < size) {
        atomicAdd(&hist[data[idx]], 1);
    }
}

// Функция для генерации случайных чисел в массиве
void generateRandomData(short* data, int size) {
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % BIN_COUNT;  // Числа от 0 до BIN_COUNT - 1
    }
}

// CPU версия гистограммы
void cpuHistogram(const short* data, int* hist, int size) {
    for (int i = 0; i < size; ++i) {
        hist[data[i]]++;
    }
}

// Функция для вывода гистограммы
void printHistogram(const int* hist, int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << "Count of " << i << ": " << hist[i] << std::endl;
    }
}

// Функция для вывода части массива
void printArray(const short* data, int size, int limit) {
    std::cout << "Array (first " << limit << " elements): ";
    for (int i = 0; i < limit && i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

// Сравнение двух гистограмм
void compareHistograms(const int* hist1, const int* hist2) {
    for (int i = 0; i < BIN_COUNT; ++i) {
        assert(hist1[i] == hist2[i] && "Histograms do not match!");
    }
    std::cout << "Histograms match!" << std::endl;
}

int main() {
    // Инициализация
    srand(time(0));

    // Создаем массив данных на CPU
    std::vector<short> data(ARRAY_SIZE);
    generateRandomData(data.data(), ARRAY_SIZE);

    // Гистограммы для CPU и CUDA
    std::vector<int> histCpu(BIN_COUNT, 0);
    std::vector<int> histCuda(BIN_COUNT, 0);

    // Вывод части исходного массива
    printArray(data.data(), ARRAY_SIZE, 100);  // Вывод первых 10 элементов массива

    // --- CPU реализация ---
    auto startCpu = std::chrono::high_resolution_clock::now();
    cpuHistogram(data.data(), histCpu.data(), ARRAY_SIZE);
    auto endCpu = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> cpuDuration = endCpu - startCpu;

    std::cout << "CPU histogram completed in: " << cpuDuration.count() << " seconds." << std::endl;

    // --- CUDA реализация ---
    short* d_data;
    int* d_hist;

    // Выделяем память на GPU
    cudaMalloc(&d_data, ARRAY_SIZE * sizeof(short));
    cudaMalloc(&d_hist, BIN_COUNT * sizeof(int));

    // Копируем данные на GPU
    cudaMemcpy(d_data, data.data(), ARRAY_SIZE * sizeof(short), cudaMemcpyHostToDevice);
    cudaMemset(d_hist, 0, BIN_COUNT * sizeof(int));

    // Запуск CUDA Kernel
    int blockSize = 512;
    int numBlocks = (ARRAY_SIZE + blockSize - 1) / blockSize;

    auto startCuda = std::chrono::high_resolution_clock::now();
    cudaHistogram << <numBlocks, blockSize >> > (d_data, d_hist, ARRAY_SIZE);
    cudaDeviceSynchronize();
    auto endCuda = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> cudaDuration = endCuda - startCuda;

    // Копируем результаты с GPU на CPU
    cudaMemcpy(histCuda.data(), d_hist, BIN_COUNT * sizeof(int), cudaMemcpyDeviceToHost);

    std::cout << "CUDA histogram completed in: " << cudaDuration.count() << " seconds." << std::endl;

    // Сравниваем результаты
    compareHistograms(histCpu.data(), histCuda.data());

    // Вывод гистограммы
    std::cout << "\nCPU Histogram:" << std::endl;
    printHistogram(histCpu.data(), 10);

    std::cout << "\nCUDA Histogram:" << std::endl;
    printHistogram(histCuda.data(), 10);

    // Освобождаем память
    cudaFree(d_data);
    cudaFree(d_hist);

    return 0;
}
