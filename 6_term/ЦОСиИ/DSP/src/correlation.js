import Complex from 'complex.js';
import { FFT, IFFT } from "./furie-transform"

export const correlation = (x, y) => {
    const N = x.length
    const z = []

    for (let m = 0; m < N; m++) {
        let sum = 0
        for (let h = 0; h < N; h++) {
            sum += x[h] * (y[(m + h) % N] || 0)
        }
        z.push(sum)
    }

    return z
}

export const FFT_correlation = (x, y) => {
    const freq_X = FFT(x)
    const freq_Y = FFT(y)

    const z = []

    for (let i = 0; i < x.length; i++) {
        z.push(new Complex(freq_X[i].re, -freq_X[i].im).mul(freq_Y[i]))
    }

    return IFFT(z)
}

// from fft import fft, ifft


// def corr(x: list, y: list) -> list:
//     """Реализация алгоритма корреляции"""
//     N = len(x)
//     z: list = []

//     for m in range(0, N):
//         sum = 0
//         for h in range(0, N):
//             sum += x[h] * (y[(m + h) % N] if m + h >= N else y[m + h])
//         z.append(sum)
//     return z


// def corr_fft(x: list, y: list) -> list:
//     freq_X = fft(x)
//     freq_Y = fft(y)

//     z: list = []

//     for i in range(0, len(x)):
//         z.append(freq_X[i].conjugate() * freq_Y[i])

//     return ifft(z)
