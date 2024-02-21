import Complex from 'complex.js';
import "./overrides.js";

function even(_, ix) {
	return ix % 2 == 0;
}

function odd(_, ix) {
	return ix % 2 == 1;
}

const getExponent = (k, N) => {
	var x = -2 * Math.PI * (k / N);

	return new Complex(Math.cos(x), Math.sin(x));
};

export const getAxis = (func, N) => {
	const axis = [];

	for (let i = 1; i <= N; i++) {
		let arg = 2*Math.PI*i/N;

		axis.push({
			x: Number(arg.toFixed(2)),
			y: Number(func(arg).toFixed(3))
		})
    }

	const x = axis.map(point => point.x);
	const y = axis.map(point => point.y)
	
	return {
		coords: axis,
		x,
		y 
	}
}

export const FFT = (signal) => {
    let N = signal.length; // Длина вектора сигнала

	if( N == 1 ) return signal;
	
	let hN = N / 2;

	let a_even = signal.filter(even) // Делим сигнал на четную часть
	let a_odd = signal.filter(odd);  // и на нечетную часть

	let b_even = FFT(a_even); // Рекурсивно применяем БПФ к четной части
	let b_odd = FFT(a_odd);   // и нечетной части

	let y = [] // массив для выходного сигнала

	for(let k = 0; k < hN; k++) {	 // массив для выходного сигнала
		if(!(b_even[k] instanceof Complex)) // проверка на то, что элемент является комплексным числом
			b_even[k] = new Complex(b_even[k], 0);
		if(!(b_odd[k] instanceof Complex))
			b_odd[k] = new Complex(b_odd[k], 0);

		var exponent = b_odd[k].mul(getExponent(k, N)); // умножаем нечетный элемент на часть с экспонентой

		y[k] = b_even[k].add(exponent);
		y[k + hN] = b_even[k].sub(exponent);
	}

	return y
}

export const IFFT = (signal) => {
	let outputSignal = structuredClone(signal);
    let N = outputSignal.length; // Длина вектора сигнала
	
	let iN = 1 / N;

	for(let i = 0 ; i < N; ++i)
		if(outputSignal[i] instanceof Complex)
		outputSignal[i].im = -outputSignal[i].im;

	outputSignal = FFT(outputSignal);

	for(var i = 0 ; i < N; ++i) {
		outputSignal[i].im = -outputSignal[i].im;
		outputSignal[i].re *= iN;
		outputSignal[i].im *= iN;
	}

	return outputSignal
}