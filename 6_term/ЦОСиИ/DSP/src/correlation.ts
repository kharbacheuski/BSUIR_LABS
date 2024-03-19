import Complex from "complex.js"
import { FFT, IFFT } from "./furie-transform"

export const correlation = (x: number[], y: number[]): number[] => {
    const N = x.length

    const z: number[] = []

    for (let m = 0; m < N; m++) {
        let sum = 0

        for (let h = 0; h < N; h++) {
            sum += x[h] * (y[(m + h) % N] || 0)
        }

        z.push(sum)
    }

    return z
}

export const FFT_correlation = (x: number[], y: number[]): Complex[] => {
    const N = x.length

    const fft_x = FFT(x, 1)
    const fft_y = FFT(y, 1)

    const z: Complex[] = []

    for (let i = 0; i < N; i++) {
        z.push(fft_x[i].conjugate().mul(fft_y[i]))
    }

    return IFFT(z)
}