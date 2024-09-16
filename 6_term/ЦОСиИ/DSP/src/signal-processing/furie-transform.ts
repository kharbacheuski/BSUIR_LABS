import Complex from 'complex.js';
import "./overrides";

const W = (N: number, mode: number = 1) => {
	return new Complex(Math.cos((2 * Math.PI) / N), - mode * Math.sin((2 * Math.PI) / N))
}

const reverse_binary = (k: number, N: number) => {
	const bits = Math.log2(N);
	let j = 0;

	for(let i = bits; i > 0; i--) {
		j = j << 1;
		j = j + (k & 1);
		k = k >> 1;
	}

	return j
}

const swap = (x: Complex[], i: number, j: number) => {
	const temp = x[i];

	x[i] = x[j];
	x[j] = temp;

	return x
}

export const reverse_index = (x: Complex[]) => {
	const N = x.length;

	for(let i = 0; i < N; i++) {
		let j = reverse_binary(i, N);

		if(j > i) {
			x = swap(x, i, j);
		}
	}

	return x
}

export function FFT_recursive(x: Complex[], mode: number): Complex[] {
    const N: number = x.length;
	const hN = Math.floor(N / 2);

    if (N <= 1) return x as Complex[];

    const b: Complex[] = [];
    const c: Complex[] = [];

    let w = new Complex(1, 0);

    for (let i = 0; i < hN; i++) {
		if(!(x[i] instanceof Complex)) {
			x[i] = new Complex(x[i].re, x[i].im);
		}
		
        b.push(x[i].add(x[i + hN]));
        c.push((x[i].sub(x[i + hN])).mul(w));

        w = w.mul(W(N, mode));
    }
	
    return [...FFT_recursive(b, mode), ...FFT_recursive(c, mode)]
}


export const FFT = (signal: number[], mode: number = 1): Complex[] => {
	let complex_signal = signal.map(item => new Complex(item, 0));

	complex_signal = FFT_recursive(complex_signal, 1)
    complex_signal = reverse_index(complex_signal)

    return complex_signal
}


export const IFFT = (x: Complex[]): number[] => {
	const N = x.length;

	x = FFT_recursive(x, -1)
	x = reverse_index(x)

	return x.map(item => item.div(N).re)
}