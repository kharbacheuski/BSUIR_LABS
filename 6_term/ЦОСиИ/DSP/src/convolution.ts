
import { FFT, IFFT } from "./furie-transform"
import Complex from "complex.js";

export const convolution = (x: number[], y: number[]) => {
    const N = x.length
    const z: number[] = []

    for (let m = 0; m < N; m++) {
        let sum: number = 0

        for (let h = 0; h < N; h++) {
            sum += x[h] * (y[m - h] ?? 0)
        }

        z.push(sum)
    }

    return z
}

export const FFT_convolution = (x: number[], y: number[]) => {
    const N = x.length

    const fft_x: Complex[] = FFT(x, 1)
    const fft_y: Complex[] = FFT(y, 1)

    const z: Complex[] = []

    for (let i = 0; i < N; i++) {
        z.push(fft_x[i].mul(fft_y[i].conjugate()))
    }

    return IFFT(z)
}