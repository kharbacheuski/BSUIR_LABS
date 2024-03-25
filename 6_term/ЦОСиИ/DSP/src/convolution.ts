
import { FFT, IFFT } from "./furie-transform"
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

        for (let m = 0; m < n; m++) {
            sum += ((m < 0 || m > N) ? 0 : x[m]) * ((n-m < 0 || n-m > M)  ? 0 : y[n - m])
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
        z.push(fft_x[i].mul(fft_y[i]))
    }

    return IFFT(z)
}

/*
def reverse_binary(x, N):
    bits = int(math.log2(N))
    j: int = 0
    for i in range(bits, 0, -1):
        j = j << 1
        j = j + (x & 1)
        x = x >> 1

    return j

def swap(x: list, i: int, j: int) -> list:
    temp = x[i]
    x[i] = x[j]
    x[j] = temp
    return x


def reverse_index(x: list) -> list:
    N = len(x)
    for i in range(0, N):
        j = reverse_binary(i, N)
        if j > i:
            x = swap(x, i, j)
    return x
*/

export const reverse_binary = (x: number[], N: number) => {
    let bits = Math.log2(N)

    let j = 0
    for i in range(bits, 0, -1):
        j = j << 1
        j = j + (x & 1)
        x = x >> 1

    return j
}