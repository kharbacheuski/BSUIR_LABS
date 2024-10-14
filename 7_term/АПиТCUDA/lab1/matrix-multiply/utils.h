#pragma once
#include <iostream>
#include <chrono>
#include <string>

class Timer {
public:
    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }

    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }

    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if (m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }

        return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - m_StartTime).count();
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;
};

bool isMultiplying(int C1, int R2) {
    return C1 == R2;
}

double** convertFloatMatrixToDouble(float** floatMatrix, int R, int C) {
    // Создаем новую матрицу типа float**
    double** doubleMatrix = new double* [R];

    for (int i = 0; i < R; i++) {
        doubleMatrix[i] = new double[C];

        for (int j = 0; j < C; j++) {
            // Преобразуем каждый элемент из double в float
            doubleMatrix[i][j] = static_cast<float>(floatMatrix[i][j]);
        }
    }

    return doubleMatrix;
}

float** convertDoubleMatrixToFloat(double** doubleMatrix, int R, int C) {
    // Создаем новую матрицу типа float**
    float** floatMatrix = new float* [R];

    for (int i = 0; i < R; i++) {
        floatMatrix[i] = new float[C];

        for (int j = 0; j < C; j++) {
            // Преобразуем каждый элемент из double в float
            floatMatrix[i][j] = static_cast<float>(doubleMatrix[i][j]);
        }
    }

    return floatMatrix;
}

template <typename T>
T** createMatrix(int R, int C, bool isEmpty = false) {
    T** matrix = new T * [R];

    for (int i = 0; i < R; i++) {
        matrix[i] = new T[C];

        if (!isEmpty) {
            for (int j = 0; j < C; j++) {
                matrix[i][j] = static_cast<T>(rand() / 10e3);
            }
        }
    }

    return matrix;
}

bool isMatrixCompare(float** A, float** B, int R, int C) {
    for (int row = 0; row < R; row++) {
        for (int col = 0; col < C; col++) {
            if (fabs(A[row][col] - B[row][col]) > 0.01) {
                std::cout << "\nMatrix error: " << A[row][col] << "  " << B[row][col] << "\n\n\n";

                return false;
            }
        }
    }

    return true;
}

template <typename T>
void printMatrix(T** matrix, int R, int C) {
    for (int row = 0; row < R; ++row) {
        for (int col = 0; col < C; ++col) {
            std::cout << matrix[row][col] << " ";
        }
        std::cout << "\n";
    }
}