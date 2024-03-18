
import { FFT, IFFT } from "./furie-transform"

export const convolution = (x, y) => {
    if (x.length !== y.length) {
        throw new Error("Длины сигналов должны быть одинаковыми.");
    }

    const N = x.length
    const z = []

    for (let m = 0; m < N; m++) {
        let sum = 0

        for (let h = 0; h < N; h++) {
            sum += x[h] * (y[m - h] || 0)
        }

        z.push(sum)
    }

    return z
}

export const FFT_convolution = (x, y) => {
    if (x.length !== y.length) {
        throw new Error("Длины сигналов должны быть одинаковыми.");
    }

    const freq_X = FFT(x)
    const freq_Y = FFT(y)

    const z = []

    for (let i = 0; i < x.length; i++) {
        z.push(freq_X[i].mul(freq_Y[i]))
    }

    return IFFT(z)
}