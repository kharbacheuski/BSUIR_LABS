#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#define MASK_WIDTH 3
#define MASK_RADIUS (MASK_WIDTH / 2)
#define THREADS_PER_BLOCK 32

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

bool loadImage(const std::string& filename, int& width, int& height, std::vector<unsigned char>& data, bool& isGrayscale) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;

    std::string header;
    file >> header;
    if (header == "P6") {
        isGrayscale = false;
    }
    else if (header == "P5") {
        isGrayscale = true;
    }
    else {
        return false;
    }

    file >> width >> height;
    int maxval;
    file >> maxval;
    file.get();

    int numChannels = isGrayscale ? 1 : 3;
    data.resize(width * height * numChannels);
    file.read(reinterpret_cast<char*>(data.data()), data.size());
    return true;
}

bool saveImage(const std::string& filename, int width, int height, const std::vector<unsigned char>& data, bool isGrayscale) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) return false;

    file << (isGrayscale ? "P5" : "P6") << "\n";
    file << width << " " << height << "\n255\n";
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
    return true;
}

void applyHighPassFilterCPU(const std::vector<unsigned char>& input, std::vector<unsigned char>& output, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x >= MASK_RADIUS && x < width - MASK_RADIUS && y >= MASK_RADIUS && y < height - MASK_RADIUS) {
                for (int c = 0; c < 3; ++c) {
                    int sum = 0;
                    for (int dy = -MASK_RADIUS; dy <= MASK_RADIUS; ++dy) {
                        for (int dx = -MASK_RADIUS; dx <= MASK_RADIUS; ++dx) {
                            int pixel = input[((y + dy) * width + (x + dx)) * 3 + c];
                            sum += pixel * filter_CPU[(dy + MASK_RADIUS) * MASK_WIDTH + (dx + MASK_RADIUS)];
                        }
                    }
                    sum = std::min(255, std::max(0, sum));
                    output[(y * width + x) * 3 + c] = static_cast<unsigned char>(sum);
                }
            }
        }
    }
}

void applyHighPassFilterCPU_Grayscale(const std::vector<unsigned char>& input, std::vector<unsigned char>& output, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x >= MASK_RADIUS && x < width - MASK_RADIUS && y >= MASK_RADIUS && y < height - MASK_RADIUS) {
                int sum = 0;
                for (int dy = -MASK_RADIUS; dy <= MASK_RADIUS; ++dy) {
                    for (int dx = -MASK_RADIUS; dx <= MASK_RADIUS; ++dx) {
                        int pixel = input[(y + dy) * width + (x + dx)];
                        sum += pixel * filter_CPU[(dy + MASK_RADIUS) * MASK_WIDTH + (dx + MASK_RADIUS)];
                    }
                }
                sum = std::min(255, std::max(0, sum));
                output[y * width + x] = static_cast<unsigned char>(sum);
            }
        }
    }
}

__global__ void applyHighPassFilterCUDA(unsigned char* input, unsigned char* output, int width, int height) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    if (x >= MASK_RADIUS && x < width - MASK_RADIUS && y >= MASK_RADIUS && y < height - MASK_RADIUS) {
        for (int c = 0; c < 3; ++c) {
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

__global__ void applyHighPassFilterCUDA_Grayscale(unsigned char* input, unsigned char* output, int width, int height) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    if (x >= MASK_RADIUS && x < width - MASK_RADIUS && y >= MASK_RADIUS && y < height - MASK_RADIUS) {
        int sum = 0;
        for (int dy = -MASK_RADIUS; dy <= MASK_RADIUS; ++dy) {
            for (int dx = -MASK_RADIUS; dx <= MASK_RADIUS; ++dx) {
                int pixel = input[(y + dy) * width + (x + dx)];
                sum += pixel * filter_CUDA[(dy + MASK_RADIUS) * MASK_WIDTH + (dx + MASK_RADIUS)];
            }
        }
        sum = min(255, max(0, sum));
        output[y * width + x] = static_cast<unsigned char>(sum);
    }
}

int main() {
    int width, height;
    bool isGrayscale;
    std::string path = "C:\\Users\\kiryl.harbacheuski\\Desktop\\belka.pgm";
    std::vector<unsigned char> image;

    if (!loadImage(path, width, height, image, isGrayscale)) {
        std::cerr << "Не удалось загрузить изображение!" << std::endl;
        return -1;
    }

    std::vector<unsigned char> outputCPU(image.size());
    std::vector<unsigned char> outputGPU(image.size());

    auto startCPU = std::chrono::high_resolution_clock::now();
    if (isGrayscale) {
        applyHighPassFilterCPU_Grayscale(image, outputCPU, width, height);
    }
    else {
        applyHighPassFilterCPU(image, outputCPU, width, height);
    }
    auto endCPU = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationCPU = endCPU - startCPU;
    std::cout << "Время выполнения на CPU: " << durationCPU.count() << " секунд\n";

    unsigned char* d_input, * d_output;
    cudaMalloc(&d_input, image.size());
    cudaMalloc(&d_output, image.size());
    cudaMemcpy(d_input, image.data(), image.size(), cudaMemcpyHostToDevice);

    dim3 blockSize(THREADS_PER_BLOCK, THREADS_PER_BLOCK);
    dim3 gridSize((width + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK, (height + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK);

    auto startGPU = std::chrono::high_resolution_clock::now();
    if (isGrayscale) {
        applyHighPassFilterCUDA_Grayscale << <gridSize, blockSize >> > (d_input, d_output, width, height);
    }
    else {
        applyHighPassFilterCUDA << <gridSize, blockSize >> > (d_input, d_output, width, height);
    }
    cudaDeviceSynchronize();
    auto endGPU = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationGPU = endGPU - startGPU;
    std::cout << "Время выполнения на GPU: " << durationGPU.count() << " секунд\n";

    cudaMemcpy(outputGPU.data(), d_output, image.size(), cudaMemcpyDeviceToHost);

    // Сравнение результатов CPU и GPU
    bool match = true;
    for (size_t i = 0; i < image.size(); ++i) {
        if (outputCPU[i] != outputGPU[i]) {
            match = false;
            std::cout << "Несоответствие в пикселе " << i << ": CPU = " << static_cast<int>(outputCPU[i]) << ", GPU = " << static_cast<int>(outputGPU[i]) << "\n";
            break;
        }
    }
    if (match) {
        std::cout << "Результаты CPU и GPU совпадают.\n";
    }
    else {
        std::cout << "Результаты CPU и GPU не совпадают.\n";
    }

    saveImage("outputCPU", width, height, outputCPU, isGrayscale);
    saveImage("outputGPU", width, height, outputGPU, isGrayscale);

    cudaFree(d_input);
    cudaFree(d_output);

    return 0;
}
