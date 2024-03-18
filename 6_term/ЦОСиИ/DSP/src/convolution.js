
import { FFT, IFFT } from "./furie-transform"

export const convolution = (x, y) => {
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
    const freq_X = FFT(x)
    const freq_Y = FFT(y)

    const z = []

    for (let i = 0; i < x.length; i++) {
        z.push(freq_X[i].mul(freq_Y[i]))
    }

    return IFFT(z)
}

// from fft import fft, ifft
// def conv(x: list, y: list) -> list:
//     """Реализация алгоритма свёртки"""
//     N = len(x)
//     z: list = []

//     for m in range(0, N):
//         sum = 0
//         for h in range(0, N):
//             sum += x[h] * (y[m - h])
//         z.append(sum)
//     return z


// def conv_fft(x: list, y: list) -> list:
//     freq_X = fft(x)
//     freq_Y = fft(y)

//     z = []

//     for i in range(0, len(x)):
//         z.append(freq_X[i] * freq_Y[i])

//     return ifft(z)


// def linear_conv(x: list, y: list) -> list:
//     N = len(x)
//     M = len(y)

//     z = []

//     for m in range(0, N + M - 1):
//         sum = 0
//         for h in range(0, N + M - 2):

//             sum += (0 if (0 > h > N) else x[h]) * (0 if (0 > m - h > M) else y[m - h])

//         z.append(sum)
//     return z