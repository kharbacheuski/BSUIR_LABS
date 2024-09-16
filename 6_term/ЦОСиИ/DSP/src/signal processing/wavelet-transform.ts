export function haarWaveletTransform(signal: number[], level: number): number[][] {
    let coeffs: number[][] = [];

    for (let _ = 0; _ < level; _++) {
        const length = signal.length;
        if (length === 1) {
            coeffs.push(signal);
            break;
        }

        const halfLength = Math.floor(length / 2);
        const c = new Array(halfLength).fill(0);
        const d = new Array(halfLength).fill(0);

        for (let i = 0; i < halfLength; i++) { 
            c[i] = (signal[2*i] + signal[2*i + 1]) / Math.sqrt(2);
            d[i] = (signal[2*i] - signal[2*i + 1]) / Math.sqrt(2);
        }

        coeffs.push(d);
        signal = c;
    }

    coeffs.push(signal);
    coeffs.reverse();
    
    console.log("Коэффициенты вейвлет-преобразования:");
    console.log(coeffs);

    return coeffs;
}

export function inverseHaarWaveletTransform(coeffs: number[][]): number[] {
    if (!Array.isArray(coeffs)) {
        throw new Error("Coefficients must be provided as a list");
    }

    const level = coeffs.length - 1;

    let signal = coeffs[0];

    for (let i = 1; i <= level; i++) {
        const length = coeffs[i].length;
        const reconstructedSignal = new Array(length * 2).fill(0);

        for (let j = 0; j < length; j++) {
            reconstructedSignal[2 * j] = (signal[j] + coeffs[i][j]) / Math.sqrt(2);
            reconstructedSignal[2 * j + 1] = (signal[j] - coeffs[i][j]) / Math.sqrt(2);
        }
        signal = reconstructedSignal;
    }

    console.log("Восстановленная функция:");
    console.log(signal);

    return signal;
}
