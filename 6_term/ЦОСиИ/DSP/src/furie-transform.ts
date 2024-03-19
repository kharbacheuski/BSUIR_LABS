import Complex from 'complex.js';
import "./overrides";

const W = (N: number, mode: number = 1) => {
	return new Complex(Math.cos((2 * Math.PI) / N), - mode * Math.sin((2 * Math.PI) / N))
}

function even(_: any, ix: number) {
	return ix % 2 == 0;
}

function odd(_: any, ix: number) {
	return ix % 2 == 1;
}

const getExponent = (k: number, N: number, mode: number = 1) => {
	var x = mode * 2 * Math.PI * ( k / N);

	return new Complex(Math.cos(x), Math.sin(x));
};

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

const swap = (x:  Complex[], i: number, j: number) => {
	const temp = x[i];

	x[i] = x[j];
	x[j] = temp;

	return x
}

const reverse_index = (x: Complex[]) => {
	const N = x.length;

	for(let i = 0; i < N; i++) {
		let j = reverse_binary(i, N);

		if(j > i) {
			x = swap(x, i, j);
		}
	}

	return x
}

// export const FFT_recursive = (signal: number[] | Complex[], mode: number = 1): Complex[] => {
//     const N = signal.length; // Длина вектора сигнала

// 	if( N == 1 ) return signal as Complex[];
	
// 	let hN = N / 2;

// 	let a_even = signal.filter(even) // Делим сигнал на четную часть
// 	let a_odd = signal.filter(odd);  // и на нечетную часть

// 	let b_even = FFT_recursive(a_even as Complex[], mode); // Рекурсивно применяем БПФ к четной части
// 	let b_odd = FFT_recursive(a_odd as Complex[], mode);   // и нечетной части

// 	let y = [] // массив для выходного сигнала

// 	for(let k = 0; k < hN; k++) {	 // массив для выходного сигнала
// 		if(!(b_even[k] instanceof Complex)) // проверка на то, что элемент является комплексным числом
// 			b_even[k] = new Complex(b_even[k], 0);
// 		if(!(b_odd[k] instanceof Complex))
// 			b_odd[k] = new Complex(b_odd[k], 0);

// 		var exponent: Complex = b_odd[k].mul(getExponent(k, N, mode)); // умножаем нечетный элемент на часть с экспонентой

// 		y[k] = b_even[k].add(exponent);
// 		y[k + hN] = b_even[k].sub(exponent);
// 	}

// 	return y
// }

export function FFT_recursive(x: Complex[], mode: number): Complex[] {
    const N: number = x.length;
	const hN = Math.floor(N / 2);

    if (N <= 1) return x as Complex[];

    const b: Complex[] = [];
    const c: Complex[] = [];

    let w = new Complex(1, 0);

    for (let i = 0; i < hN; i++) {
		x = x[i] instanceof Complex ? x as Complex[] : x.map(item => new Complex(item, 0));
		
        b.push(x[i].add(x[i + hN]));
        c.push((x[i].sub(x[i + hN])).mul(w));

        w = w.mul(W(N, mode));
    }

    return [...FFT_recursive(b, mode), ...FFT_recursive(c, mode)];
}


export const FFT = (signal: number[], mode: number = 1): Complex[] => {
	let complex_signal = signal.map(item => new Complex(item, 0));

	complex_signal = FFT_recursive(complex_signal, 1)
    complex_signal = reverse_index(complex_signal)

    return complex_signal
}


export const IFFT = (x: Complex[]): number[] => {
	const N = x.length;

	x = FFT_recursive(x, 1)
	x = reverse_index(x)

	return x.map(item => item.div(N).re)
}