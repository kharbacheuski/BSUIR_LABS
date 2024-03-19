import Complex from 'complex.js';
import "./overrides";

function even(_: any, ix: number) {
	return ix % 2 == 0;
}

function odd(_: any, ix: number) {
	return ix % 2 == 1;
}

const getExponent = (k: number, N: number, mode: number = 1) => {
	var x = mode*2 * Math.PI * (k / N);

	return new Complex(Math.cos(x), Math.sin(x));
};

export const FFT = (signal: number[] | Complex[], mode: number = 1): Complex[] => {
    let N = signal.length; // Длина вектора сигнала

	if( N == 1 ) return signal as Complex[];
	
	let hN = N / 2;

	let a_even = signal.filter(even) // Делим сигнал на четную часть
	let a_odd = signal.filter(odd);  // и на нечетную часть

	let b_even = FFT(a_even as Complex[], mode); // Рекурсивно применяем БПФ к четной части
	let b_odd = FFT(a_odd as Complex[], mode);   // и нечетной части

	let y = [] // массив для выходного сигнала

	for(let k = 0; k < hN; k++) {	 // массив для выходного сигнала
		if(!(b_even[k] instanceof Complex)) // проверка на то, что элемент является комплексным числом
			b_even[k] = new Complex(b_even[k], 0);
		if(!(b_odd[k] instanceof Complex))
			b_odd[k] = new Complex(b_odd[k], 0);

		var exponent: Complex = b_odd[k].mul(getExponent(k, N, mode)); // умножаем нечетный элемент на часть с экспонентой

		y[k] = b_even[k].add(exponent);
		y[k + hN] = b_even[k].sub(exponent);
	}

	return y
}


export const IFFT = (signal: Complex[]): Complex[] => {
	const N = signal.length;
    let inverse_signal: Complex[] = []; 

	for(let i = 0; i < N; i++){
		inverse_signal[i] = new Complex(signal[i].im, signal[i].re); // Меняем местами мнимую и реальную части
	}

	let ps: Complex[] = FFT(inverse_signal, 1); // Выполняем БПФ на преобразованном сигнале

	let res: Complex[] = [];

	for(let j = 0; j < N; j++){
		res[j] = new Complex(ps[j].im/N, ps[j].re/N)
	}

	return res;
}