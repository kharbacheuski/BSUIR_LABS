import matplotlib.pyplot as plt

from furie_transform import *


x = np.linspace(0, 2 * np.pi, 64)
y = np.sin(5 * x) + np.cos(x)

plt.figure(figsize=(8, 6))

# График исходного сигнала
plt.subplot(3, 2, 1)
plt.plot(x, y)
plt.title('Original Signal')

# БПФ
fft_result = FFT(y)

# Обратное БПФ
inverse_fft_result = IFFT(fft_result)

plt.subplot(3, 2, 3)
plt.plot(np.abs(fft_result))
plt.title('FFT')

# Вывод действительной и мнимой частей БПФ
plt.subplot(3, 2, 4)
plt.plot(np.real(fft_result))
plt.title('Real Part of FFT')

plt.subplot(3, 2, 6)
plt.plot(np.imag(fft_result))
plt.title('Imaginary Part of FFT')

# Вывод реконструированного графика
plt.subplot(3, 2, 2)
plt.plot(x, inverse_fft_result)
plt.title('Reconstruction signal')

plt.tight_layout()
plt.show()

# -------------------------------------------------------------
# С помощью библиотечных функций
x = np.linspace(0, 2 * np.pi, 64)
y = np.sin(5 * x) + np.cos(x)

fft_result = np.fft.fft(y)

inverse_fft_result = np.fft.ifft(fft_result)

plt.figure(figsize=(8, 6))

# График исходного сигнала
plt.subplot(3, 2, 1)
plt.plot(x, y)
plt.title('Original Signal')

plt.subplot(3, 2, 3)
plt.plot(np.abs(fft_result))
plt.title('FFT')

# Вывод целой и мнимой части графика обратного БПФ
plt.subplot(3, 2, 4)
plt.plot(np.real(fft_result))
plt.title('Real Part of FFT')

plt.subplot(3, 2, 6)
plt.plot(np.imag(fft_result))
plt.title('Imaginary Part of FFT')

# Вывод реконструированного графика
plt.subplot(3, 2, 2)
plt.plot(x, inverse_fft_result)
plt.title('Reconstruscted signal')


plt.tight_layout()
plt.show()


