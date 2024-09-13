#include <iostream>
#include <chrono>
#include <chrono>

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

template<std::size_t R1, std::size_t C1, std::size_t R2, std::size_t C2>
void variant1(float(&A)[R1][C1], float(&B)[R2][C2]) {
    auto timer = new Timer();

    timer->start();

    float result[R1][C2] {};

    for (int row = 0; row < R1; row++) {
        for (int col = 0; col < C2; col++) {
            for (int inner = 0; inner < C1; inner++) {
                result[row][col] += A[row][inner] * B[inner][col];
            }
            std::cout << result[row][col] << "  ";
        }
        std::cout << "\n";
    }

    timer->stop();
    std::cout << "\nBasic matrix multiplication took: " << timer->elapsedMilliseconds() << " nanoseconds.\n\n\n";
}

template<std::size_t R1, std::size_t C1, std::size_t R2, std::size_t C2>
void variant2(float(&A)[R1][C1], float(&B)[R2][C2], int block_size) {
    auto timer2 = new Timer();

    timer2->start();

    float result[R1][C2] {};

    // Итерируемся по блокам
    for (std::size_t block_row = 0; block_row < R1; block_row += block_size) {
        for (std::size_t block_col = 0; block_col < C2; block_col += block_size) {
            for (std::size_t inner_block = 0; inner_block < C1; inner_block += block_size) {
                // Высчитываем размер текущего блока
                std::size_t block_row_end = std::min(block_row + block_size, R1);
                std::size_t block_col_end = std::min(block_col + block_size, C2);
                std::size_t inner_block_end = std::min(inner_block + block_size, C1);

                // Перемножаем блоки
                for (std::size_t i = block_row; i < block_row_end; ++i) {
                    for (std::size_t j = block_col; j < block_col_end; ++j) {
                        for (std::size_t k = inner_block; k < inner_block_end; ++k) {
                            result[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    timer2->stop();

    // Вывод матрицы в консоль
    for (std::size_t row = 0; row < R1; ++row) {
        for (std::size_t col = 0; col < C2; ++col) {
            std::cout << result[row][col] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nBasic matrix multiplication took: " << timer2->elapsedMilliseconds() << " nanoseconds.\n\n\n";
}

bool isMultiplying(int C1, int R2) {
    return C1 == R2;
}

void MultiplyWithOutAMP() {
    const int R1 = 6;
    const int C1 = 5;

    const int R2 = 5;
    const int C2 = 3;

    // L1 кеш - 64 КБ
    // L2 кеш - 512 КБ
    // L3 кеш - 16МБ

    int L1 = 32; // 32 ячейки - тоесть 32*32*4 байта - 4КБ
    int L2 = 256; // 256 ячеек - тоесть 256*256*4 байта - 256КБ
    int L3 = 1024; // 1024 ячеек - тоесть 1024*1024*4 байта - 4МБ
    int OUT_OF_CASH = 4096; // 4096 ячеек - тоесть 4096*4096*4 байта - 67МБ

    //int block_size = (L3 / 3) * 0.9;
    //std::cout << "\nBlock size " << block_size << std::endl << std::endl;

    float A[R1][C1] = { 
        { 700.2f, 2.5f, 3.0f, 4.57f, 0.12f },
        { 11.89f, 23.345f, 30.13f, 19.0f, 5.9f },
        { 90.0f, 45.0f, 102.0f, 4.114f, 45.8f },
        { 200.78f, 2.5f, 3.89f, 8.4f, 0.0f },
        { 5.012f, 2.1f, 3.6f, 4.0f, 7.78f },
        { 67.04f, 2.2f, 31.5f, 4.0f, 5.111f }
    };

    float B[R2][C2] = {
        {7.012f, 114.11f, 9.0f},
        {12.0f, 2.78f, 3.99f},
        {7.2f, 8.5f, 9.11f},
        {90.3f, 67.5f, 9.5f},
        {7.4f, 80.65f, 92.3f},
    };

    /*float A[R1][C1] = {
        { 700.2f, 2.5f, 3.0f, 4.57f, 0.12f },
        { 11.89f, 23.345f, 30.13f, 19.0f, 5.9f },
        { 90.0f, 45.0f, 102.0f, 4.114f, 45.8f },
        { 200.78f, 2.5f, 3.89f, 8.4f, 0.0f },
        { 5.012f, 2.1f, 3.6f, 4.0f, 7.78f },
        { 67.04f, 2.2f, 31.5f, 4.0f, 5.111f },
        { 700.2f, 2.5f, 3.0f, 4.57f, 0.12f },
        { 11.89f, 23.345f, 30.13f, 19.0f, 5.9f },
        { 90.0f, 45.0f, 102.0f, 4.114f, 45.8f },
        { 200.78f, 2.5f, 3.89f, 8.4f, 0.0f },
        { 5.012f, 2.1f, 3.6f, 4.0f, 7.78f },
        { 67.04f, 2.2f, 31.5f, 4.0f, 5.111f },
        { 700.2f, 2.5f, 3.0f, 4.57f, 0.12f },
        { 11.89f, 23.345f, 30.13f, 19.0f, 5.9f },
        { 90.0f, 45.0f, 102.0f, 4.114f, 45.8f },
        { 200.78f, 2.5f, 3.89f, 8.4f, 0.0f },
        { 5.012f, 2.1f, 3.6f, 4.0f, 7.78f },
        { 67.04f, 2.2f, 31.5f, 4.0f, 5.111f },
        { 700.2f, 2.5f, 3.0f, 4.57f, 0.12f },
        { 11.89f, 23.345f, 30.13f, 19.0f, 5.9f },
        { 90.0f, 45.0f, 102.0f, 4.114f, 45.8f },
        { 200.78f, 2.5f, 3.89f, 8.4f, 0.0f },
        { 5.012f, 2.1f, 3.6f, 4.0f, 7.78f },
        { 67.04f, 2.2f, 31.5f, 4.0f, 5.111f },
        { 700.2f, 2.5f, 3.0f, 4.57f, 0.12f },
        { 11.89f, 23.345f, 30.13f, 19.0f, 5.9f },
        { 90.0f, 45.0f, 102.0f, 4.114f, 45.8f },
        { 200.78f, 2.5f, 3.89f, 8.4f, 0.0f },
        { 5.012f, 2.1f, 3.6f, 4.0f, 7.78f },
        { 67.04f, 2.2f, 31.5f, 4.0f, 5.111f },
        { 700.2f, 2.5f, 3.0f, 4.57f, 0.12f },
        { 11.89f, 23.345f, 30.13f, 19.0f, 5.9f },
        { 90.0f, 45.0f, 102.0f, 4.114f, 45.8f },
        { 200.78f, 2.5f, 3.89f, 8.4f, 0.0f },
        { 5.012f, 2.1f, 3.6f, 4.0f, 7.78f },
        { 67.04f, 2.2f, 31.5f, 4.0f, 5.111f }
    };

    float B[R2][C2] = {
        {7.012f, 114.11f, 9.0f, 7.012f, 114.11f, 9.0f, 7.012f, 114.11f, 9.0f, 7.012f, 114.11f, 9.0f, 7.012f, 114.11f, 9.0f, 7.012f, 114.11f, 9.0f},
        {12.0f, 2.78f, 3.99f, 7.012f, 114.11f, 9.0f, 7.012f, 114.11f, 9.0f, 7.012f, 114.11f, 9.0f, 7.012f, 114.11f, 9.0f, 7.012f, 114.11f, 9.0f},
        {7.2f, 8.5f, 9.11f, 7.4f, 80.65f, 92.3f, 7.4f, 80.65f, 92.3f, 7.4f, 80.65f, 92.3f, 7.4f, 80.65f, 92.3f, 7.4f, 80.65f, 92.3f},
        {90.3f, 67.5f, 9.5f, 7.2f, 8.5f, 9.11f, 7.2f, 8.5f, 9.11f, 7.2f, 8.5f, 9.11f, 7.2f, 8.5f, 9.11f, 7.2f, 8.5f, 9.11f},
        {7.4f, 80.65f, 92.3f, 7.2f, 8.5f, 9.11f, 7.2f, 8.5f, 9.11f, 7.2f, 8.5f, 9.11f, 7.2f, 8.5f, 9.11f, 7.2f, 8.5f, 9.11f}
    };*/

    if (isMultiplying(C1, R2)) {
        variant1(A, B);
        variant2(A, B, L1);
        variant2(A, B, L2);
        variant2(A, B, L3);
        variant2(A, B, OUT_OF_CASH);
    }
    else {
        std::cout << "\nMatrix CAN'T be multiplying" << std::endl;
    }
}

int main() {
    MultiplyWithOutAMP();
}