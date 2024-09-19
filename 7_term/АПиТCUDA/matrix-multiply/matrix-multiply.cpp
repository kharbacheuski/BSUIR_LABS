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

float** createMatrix(int R, int C, bool isEmpty = false) {
    float** matrix = new float* [R];

    for (int i = 0; i < R; i++) {
        matrix[i] = new float[C];

        if (!isEmpty) {
            for (int j = 0; j < C; j++) {
                matrix[i][j] = (float)(rand() / 10e3);
            }
        }
    }

    return matrix;
}

float** variant1(float** A, float** B, int R1, int R2, int C1, int C2, bool writeConsole = false) {
    auto timer = new Timer();

    timer->start();

    float** result = createMatrix(R1, C2, true);

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

    std::cout << "\nNon cache matrix multiplication time: " << timer->elapsedMilliseconds() << " nanoseconds.\n\n\n";

    return result;
}

float** variant2(float** A, float** B, int R1, int R2, int C1, int C2, int block_size, bool writeConsole = false) {
    auto timer2 = new Timer();

    timer2->start();

    float** result = createMatrix(R1, C2, true);  // Создаем результирующую матрицу размером R1 x C2 и заполняем её случайными числами

    // Внешний цикл по блокам строк матрицы A
    for (int block_row = 0; block_row < R1; block_row += block_size) {
        // Цикл по блокам столбцов матрицы B (внутренние блоки)
        for (int inner_block = 0; inner_block < C1; inner_block += block_size) {
            // Цикл по блокам столбцов результирующей матрицы (матрицы C)
            for (int block_col = 0; block_col < C2; block_col += block_size) {
                // Вычисляем границы текущего блока строк матрицы A
                int block_row_end = std::min(block_row + block_size, R1);  // Определяем конец блока строк, не выходя за пределы матрицы A
                // Вычисляем границы текущего блока столбцов матрицы B
                int inner_block_end = std::min(inner_block + block_size, C1);  // Определяем конец блока столбцов для A и строк для B
                // Вычисляем границы текущего блока столбцов результирующей матрицы C
                int block_col_end = std::min(block_col + block_size, C2);  // Определяем конец блока столбцов матрицы C

                // Цикл по строкам текущего блока матрицы A
                for (int i = block_row; i < block_row_end; i++) {
                    // Цикл по элементам блока внутренней размерности (по столбцам A и строкам B)
                    for (int k = inner_block; k < inner_block_end; k++) {
                        // Цикл по столбцам текущего блока матрицы B
                        for (int j = block_col; j < block_col_end; j++) {
                            // Умножаем элемент из строки матрицы A и столбца матрицы B и добавляем к результату
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

    std::cout << "\nWith cache matrix multiplication time: " << timer2->elapsedMilliseconds() << " nanoseconds.\n\n\n";

    return result;
}

bool isMatrixCompare(float** A, float** B, int R, int C) {
    for (int row = 0; row < R; row++) {
        for (int col = 0; col < C; col++) {
            if (A[row][col] != B[row][col]) {
                std::cout << "\nMatrix error: " << A[row][col] << "  " << B[row][col] << "\n\n\n";

                return false;
            }
        }
    }

    return true;
}

int getBlockSize(int cache_level) {
    return (int)(cache_level * (0.9 / 3));
}

void MultiplyWithOutAMP() {
    srand(time(0));

    const int R1 = 1000;
    const int C1 = 1500;

    const int R2 = 1500;
    const int C2 = 800;

    int L1 = 32; // 32 ячейки - тоесть 32*32*4 байта - 4КБ.  L1 кеш - 64 КБ
    int L2 = 256; // 256 ячеек - тоесть 256*256*4 байта - 256КБ. L2 кеш - 512 КБ
    int L3 = 1024; // 1024 ячеек - тоесть 1024*1024*4 байта - 4МБ.  L3 кеш - 16МБ
    int OUT_OF_CASH = 4096; // 4096 ячеек - тоесть 4096*4096*4 байта - 67МБ

    float** A = createMatrix(R1, C1);
    float** B = createMatrix(R2, C2);

    bool isConsoleOutput = false;

    if (isMultiplying(C1, R2)) {
        float** one = variant1(A, B, R1, R2, C1, C2, isConsoleOutput);
        float** two = variant2(A, B, R1, R2, C1, C2, L1, isConsoleOutput);

        bool equal = isMatrixCompare(one, two, R1, C2);

        std::cout << "\nIs matrix equal: " << equal << std::endl;
    }
    else {
        std::cout << "\nMatrix CAN'T be multiplying" << std::endl;
    }
}

int main() {
    MultiplyWithOutAMP();
}