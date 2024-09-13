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

bool isMultiplying(int C1, int R2) {
    return C1 == R2;
}

float** fillMatrix(float** matrix, int R, int C) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            matrix[i][j] = (float)(rand() % 10);
        }
    }

    return matrix;
}

float** createMatrix(int R, int C) {
    float** matrix = new float* [R];

    for (int i = 0; i < R; i++) {
        matrix[i] = new float[C];
    }

    return matrix;
}

void variant1(float** A, float** B, int R1, int R2, int C1, int C2, bool writeConsole = false) {
    auto timer = new Timer();

    timer->start();

    float** result = createMatrix(R1, C2);

    for (int row = 0; row < R1; row++) {
        for (int col = 0; col < C2; col++) {
            for (int inner = 0; inner < C1; inner++) {
                result[row][col] += A[row][inner] * B[inner][col];
            }
        }
    }

    timer->stop();

    // Вывод матрицы в консоль
    if(writeConsole)
        for (int row = 0; row < R1; ++row) {
            for (int col = 0; col < C2; ++col) {
                std::cout << result[row][col] << " ";
            }
            std::cout << "\n";
        }

    std::cout << "\nMatrix multiplication time: " << timer->elapsedMilliseconds() << " nanoseconds.\n\n\n";
}

void variant2(float ** A, float** B, int R1, int R2, int C1, int C2, int block_size, bool writeConsole = false) {
    auto timer2 = new Timer();

    timer2->start();

    float** result = createMatrix(R1, C2);

    // Итерируемся по блокам
    for (int block_row = 0; block_row < R1; block_row += block_size) {
        for (int block_col = 0; block_col < C2; block_col += block_size) {
            for (int inner_block = 0; inner_block < C1; inner_block += block_size) {
                // Высчитываем размер текущего блока
                int block_row_end = std::min(block_row + block_size, R1);
                int block_col_end = std::min(block_col + block_size, C2);
                int inner_block_end = std::min(inner_block + block_size, C1);

                // Перемножаем блоки
                for (int i = block_row; i < block_row_end; ++i) {
                    for (int j = block_col; j < block_col_end; ++j) {
                        for (int k = inner_block; k < inner_block_end; ++k) {
                            result[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }

    timer2->stop();

    // Вывод матрицы в консоль
    if (writeConsole)
        for (int row = 0; row < R1; ++row) {
            for (int col = 0; col < C2; ++col) {
                std::cout << result[row][col] << " ";
            }
            std::cout << "\n";
        }

    std::cout << "\nMatrix multiplication time: " << timer2->elapsedMilliseconds() << " nanoseconds.\n\n\n";
}

void MultiplyWithOutAMP() {
    const int R1 = 150; 
    const int C1 = 150;

    const int R2 = 150;
    const int C2 = 150; 

    int L1 = 32; // 32 ячейки - тоесть 32*32*4 байта - 4КБ.  L1 кеш - 64 КБ
    int L2 = 256; // 256 ячеек - тоесть 256*256*4 байта - 256КБ. L2 кеш - 512 КБ
    int L3 = 1024; // 1024 ячеек - тоесть 1024*1024*4 байта - 4МБ.  L3 кеш - 16МБ
    int OUT_OF_CASH = 4096; // 4096 ячеек - тоесть 4096*4096*4 байта - 67МБ

    int block_size = (int)((L3 / 3) * 0.9);

    //std::cout << "\nBlock size " << block_size << std::endl << std::endl;

    float** A = createMatrix(R1, C1);
    A = fillMatrix(A, R1, C1);

    float** B = createMatrix(R2, C2);
    B = fillMatrix(B, R2, C2);

    bool isConsoleOutput = false;

    if (isMultiplying(C1, R2)) {
        variant1(A, B, R1, R2, C1, C2, isConsoleOutput);
        variant2(A, B, R1, R2, C1, C2, L1, isConsoleOutput);
        //variant2(A, B, R1, R2, C1, C2, L2);
        //variant2(A, B, R1, R2, C1, C2, L3);
        //variant2(A, B, R1, R2, C1, C2, OUT_OF_CASH);
    }
    else {
        std::cout << "\nMatrix CAN'T be multiplying" << std::endl;
    }
}

int main() {
    MultiplyWithOutAMP();
}