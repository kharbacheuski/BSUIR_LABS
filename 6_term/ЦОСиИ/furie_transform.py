import numpy as np


def FFT(spectrum):
    '''Реализация быстрого преобразования Фурье (БПФ) с прореживанием по частоте'''
    N = len(spectrum)
    if N <= 1:
        return spectrum
    even = FFT(spectrum[::2])
    odd = FFT(spectrum[1::2])
    # Предварительное вычисление фактора
    factor = np.exp(-2j * np.pi * np.arange(N) / N)
    # Комбинирование результатов с применением комплексных экспонент
    combined = np.empty(N, dtype=np.complex128)
    combined[:N // 2] = even + factor[:N // 2] * odd
    combined[N // 2:] = even + factor[N // 2:] * odd  

    return combined


def IFFT(spectrum):
    '''Реализация обратного быстрого преобразования Фурье с прореживанием по частоте'''
    N = len(spectrum)
    if N <= 1:
        return spectrum
    even = IFFT(spectrum[::2])
    odd = IFFT(spectrum[1::2])
    # Предварительное вычисление фактора
    factor = [np.exp(2j * np.pi * k / N) for k in range(N)]
    # Комбинирование результатов с применением комплексных экспонент
    combined = [even[k] + factor[k] * odd[k] for k in range(N // 2)] + \
               [even[k] - factor[k] * odd[k] for k in range(N // 2)]
    # Нормальизуем окончательный сигнал
    return [x / N for x in combined]