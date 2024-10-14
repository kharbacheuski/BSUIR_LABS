#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

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

// Функция для отражения по вертикали
std::vector<std::vector<float>> flip_vertically(const std::vector<std::vector<float>>& matrix) {
    std::vector<std::vector<float>> flipped(matrix);
    std::reverse(flipped.begin(), flipped.end());
    return flipped;
}

// Функция для отражения по горизонтали
std::vector<std::vector<float>> flip_horizontally(const std::vector<std::vector<float>>& matrix) {
    std::vector<std::vector<float>> flipped(matrix);
    for (auto& row : flipped)
        std::reverse(row.begin(), row.end());
    return flipped;
}

// Функция для замера времени
void measure_cpu(const std::vector<std::vector<float>>& matrix) {
    auto start = std::chrono::high_resolution_clock::now();

    // Отражение по вертикали
    auto vertically_flipped = flip_vertically(matrix);

    // Отражение по горизонтали
    auto horizontally_flipped = flip_horizontally(vertically_flipped);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    std::cout << "CPU Time: " << duration.count() << " seconds" << std::endl;
}

int main() {
    int rows = 1000, cols = 1000;

    // Создание матрицы
    auto matrix = create_random_matrix(rows, cols);

    // Замер времени на CPU
    measure_cpu(matrix);

    return 0;
}