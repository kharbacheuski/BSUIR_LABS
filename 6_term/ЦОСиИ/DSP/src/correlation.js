import Complex from 'complex.js';
import { FFT, IFFT } from "./furie-transform"

export const correlation = (x, y) => {
    if (x.length !== y.length) {
        throw new Error("Длины сигналов должны быть одинаковыми.");
    }

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
    if (x.length !== y.length) {
        throw new Error("Длины сигналов должны быть одинаковыми.");
    }

    const freq_X = FFT(x)
    const freq_Y = FFT(y)

    const z = []

    for (let i = 0; i < x.length; i++) {
        z.push(new Complex(freq_X[i].re, -freq_X[i].im).mul(freq_Y[i]))
    }

    return IFFT(z)
}