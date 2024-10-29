#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cmath>

#define MASK_WIDTH 3
#define MASK_RADIUS (MASK_WIDTH / 2)
#define THREADS_PER_BLOCK 32

// Матрица фильтра высокого разрешения H1 CUDA
__constant__ int filter_CUDA[MASK_WIDTH * MASK_WIDTH] = {
    -1, -1, -1,
    -1, 9, -1,
    -1, -1, -1
};

int filter_CPU[MASK_WIDTH * MASK_WIDTH] = {
    -1, -1, -1,
    -1, 9, -1,
    -1, -1, -1
};

// Функция для загрузки PPM изображения
bool loadPPM(const std::string& filename, int& width, int& height, std::vector<unsigned char>& data) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;

    std::string header;
    file >> header;
    if (header != "P6") return false;

    file >> width >> height;
    int maxval;
    file >> maxval;
    file.get();  // Пропустить один байт

    data.resize(width * height * 3);
    file.read(reinterpret_cast<char*>(data.data()), data.size());
    return true;
}

// Функция для сохранения PPM изображения
bool savePPM(const std::string& filename, int width, int height, const std::vector<unsigned char>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) return false;

    file << "P6\n" << width << " " << height << "\n255\n";
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
    return true;
}


// CPU-реализация фильтра
void applyHighPassFilterCPU(const std::vector<unsigned char>& input, std::vector<unsigned char>& output, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x >= MASK_RADIUS && x < width - MASK_RADIUS && y >= MASK_RADIUS && y < height - MASK_RADIUS) {
                for (int c = 0; c < 3; ++c) {  // Для каждого цветового канала
                    int sum = 0;
                    for (int dy = -MASK_RADIUS; dy <= MASK_RADIUS; ++dy) {
                        for (int dx = -MASK_RADIUS; dx <= MASK_RADIUS; ++dx) {
                            // Получение значения пикселя с учетом краевых условий
                            int pixel = input[((y + dy) * width + (x + dx)) * 3 + c];
                            sum += pixel * filter_CPU[(dy + MASK_RADIUS) * MASK_WIDTH + (dx + MASK_RADIUS)];
                        }
                    }
                    sum = std::min(255, std::max(0, sum)); // Ограничение по диапазону
                    output[(y * width + x) * 3 + c] = static_cast<unsigned char>(sum);
                }
            }
        }
    }
}

// CUDA-ядро для фильтрации
__global__ void applyHighPassFilterCUDA(unsigned char* input, unsigned char* output, int width, int height) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    if (x >= MASK_RADIUS && x < width - MASK_RADIUS && y >= MASK_RADIUS && y < height - MASK_RADIUS) {
        for (int c = 0; c < 3; ++c) {  // Для каждого цветового канала
            int sum = 0;
            for (int dy = -MASK_RADIUS; dy <= MASK_RADIUS; ++dy) {
                for (int dx = -MASK_RADIUS; dx <= MASK_RADIUS; ++dx) {
                    int pixel = input[((y + dy) * width + (x + dx)) * 3 + c];
                    sum += pixel * filter_CUDA[(dy + MASK_RADIUS) * MASK_WIDTH + (dx + MASK_RADIUS)];
                }
            }

            sum = min(255, max(0, sum));
            output[(y * width + x) * 3 + c] = static_cast<unsigned char>(sum);
        }
    }
}

// Сравнение результатов CPU и GPU
bool compareResults(const std::vector<unsigned char>& cpu, const std::vector<unsigned char>& gpu, int width, int height) {
    int nots = 0;
    for (int i = 0; i < width * height * 3; ++i) {
        if (std::abs(cpu[i] - gpu[i]) > 1) {
            nots++;
        }
    }
    if (nots > 1) {
        std::cerr << "Несовпадений найдено " << nots << std::endl;
        return false;
    }
    return true;
}

int main() {
    int width, height;
    char *path = "C:\\Users\\kiryl.harbacheuski\\Desktop\\belka.ppm";
    std::vector<unsigned char> image;
    if (!loadPPM(path, width, height, image)) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return -1;
    }

    std::vector<unsigned char> outputCPU(image.size());
    std::vector<unsigned char> outputGPU(image.size());

    // Применение фильтра на CPU
    auto startCPU = std::chrono::high_resolution_clock::now();
    applyHighPassFilterCPU(image, outputCPU, width, height);
    auto endCPU = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> cpuTime = endCPU - startCPU;
    std::cout << "Время обработки на CPU: " << cpuTime.count() << " секунд" << std::endl;

    // Применение фильтра на GPU
    unsigned char* d_input, * d_output;
    cudaMalloc(&d_input, image.size());
    cudaMalloc(&d_output, image.size());
    cudaMemcpy(d_input, image.data(), image.size(), cudaMemcpyHostToDevice);

    dim3 blockSize(THREADS_PER_BLOCK, THREADS_PER_BLOCK);
    dim3 gridSize((width + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK, (height + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK);

    auto startGPU = std::chrono::high_resolution_clock::now();
    applyHighPassFilterCUDA << <gridSize, blockSize >> > (d_input, d_output, width, height);
    cudaDeviceSynchronize();
    auto endGPU = std::chrono::high_resolution_clock::now();

    cudaMemcpy(outputGPU.data(), d_output, image.size(), cudaMemcpyDeviceToHost);
    std::chrono::duration<double> gpuTime = endGPU - startGPU;
    std::cout << "Время обработки на GPU: " << gpuTime.count() << " секунд" << std::endl;

    // Сравнение результатов
    if (compareResults(outputCPU, outputGPU, width, height)) {
        std::cout << "Результаты CPU и GPU совпадают." << std::endl;
    }
    else {
        std::cout << "Результаты CPU и GPU НЕ совпадают." << std::endl;
    }

    // Сохранение изображения
    if (!savePPM("output-gpu.ppm", width, height, outputGPU)) {
        std::cerr << "Не удалось сохранить изображение!" << std::endl;
        return -1;
    }

    // Сохранение изображения
    if (!savePPM("output-cpu.ppm", width, height, outputCPU)) {
        std::cerr << "Не удалось сохранить изображение!" << std::endl;
        return -1;
    }


    cudaFree(d_input);
    cudaFree(d_output);

    return 0;
}