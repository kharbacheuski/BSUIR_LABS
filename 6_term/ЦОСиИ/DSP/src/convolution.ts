
import { FFT, IFFT, reverse_index } from "./furie-transform"
import Complex from "complex.js";

export const curcular_convolution = (x: number[], y: number[]) => {
    const N = x.length
    const z: number[] = []

    for (let n = 0; n < N; n++) {
        let sum: number = 0

        for (let m = 0; m < N; m++) {
            sum += x[m] * (y[n - m] || 0)
        }

        z.push(sum)
    }

    return z
}

export const linear_convolution = (x: number[], y: number[]) => {
    const N = x.length
    const M = y.length

    const z: number[] = []

    for (let n = 0; n <= N+M-2; n++) {
        let sum: number = 0

        for (let m = 0; m < N; m++) {
            if(n - m + 1 >= 1 && n - m + 1 <= M) {
                sum += x[m] * y[n - m + 1]
            }
        }

        z.push(sum)
    }

    return z
}

export const FFT_convolution = (x: number[], y: number[]) => {
    const N = x.length

    let fft_x: Complex[] = FFT(x)
    let fft_y: Complex[] = FFT(y)

    const z: Complex[] = []

    for (let i = 0; i < N; i++) {
        z.push(fft_x[i].mul(fft_y[i]))
    }

    return IFFT(z)
}