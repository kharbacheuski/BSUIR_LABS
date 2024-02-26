import Complex from 'complex.js';
import "./overrides.js";

export const complexModule = (x) => {
	return Math.sqrt(x.re*x.re + x.im*x.im);
}

function even(_, ix) {
	return ix % 2 == 0;
}

function odd(_, ix) {
	return ix % 2 == 1;
}

export const eexp = (dir, N) => {
	var x = -2 * dir * Math.PI / N;
	return new Complex(Math.cos(x), Math.sin(x));
}

export const eexp2 = (dir, N, k) => {
	var x = -2 * dir * Math.PI * k/ N;
	return new Complex(Math.cos(x), Math.sin(x));
}


const getExponent = (k, N, sign = -1) => {
	var x = sign*2 * Math.PI * (k / N);

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

// export const FFT = (signal) => {
//     let N = signal.length; // Длина вектора сигнала

// 	if( N == 1 ) return signal;
	
// 	let hN = N / 2;

// 	let a_even = signal.filter(even) // Делим сигнал на четную часть
// 	let a_odd = signal.filter(odd);  // и на нечетную часть

// 	let b_even = FFT(a_even); // Рекурсивно применяем БПФ к четной части
// 	let b_odd = FFT(a_odd);   // и нечетной части

// 	let y = [] // массив для выходного сигнала

// 	for(let k = 0; k < hN; k++) {	 // массив для выходного сигнала
// 		if(!(b_even[k] instanceof Complex)) // проверка на то, что элемент является комплексным числом
// 			b_even[k] = new Complex(b_even[k], 0);
// 		if(!(b_odd[k] instanceof Complex))
// 			b_odd[k] = new Complex(b_odd[k], 0);

// 		var exponent = b_odd[k].mul(getExponent(k, N)); // умножаем нечетный элемент на часть с экспонентой

// 		y[k] = b_even[k].add(exponent);
// 		y[k + hN] = b_even[k].sub(exponent);
// 	}

// 	return y
// }

export const FFT = (signal, dir = 1) => {
    let N = signal.length; // Длина вектора сигнала

	if( N == 1 ) return signal;

	let hN = N / 2;

	let right = []
	let left = []
	left.length = N;

	let wN = eexp(dir, N);
	let w = new Complex(1, 0);

	for(let j = 0; j < hN; j++) {
		if(!(signal[j] instanceof Complex)) // проверка на то, что элемент является комплексным числом
			signal[j] = new Complex(signal[j], 0);
		if(!(signal[j + hN] instanceof Complex)) // проверка на то, что элемент является комплексным числом
			signal[j + hN] = new Complex(signal[j + hN], 0);

		right.push(signal[j].add(signal[j + hN]))
		// right[j] = signal[j].add(signal[j + hN]);
		left.push((signal[j].sub(signal[j + hN])).mul(w))
		// left[j + hN] = ;

		w = w.mul(wN)
	}

	right = FFT(right, dir);
	left = FFT(left, dir);

	return [...left, ...right];
}

export const IFFT = (signal) => {
    let inverse_signal = []; 

	for(let i = 0; i < signal.length; i++){
		inverse_signal[i] = new Complex(signal[i].im, signal[i].re); // Меняем местами мнимую и реальную части
	}

	let ps = FFT(inverse_signal); // Выполняем БПФ на преобразованном сигнале

	let res=[];

	for(let j = 0; j < ps.length; j++){
		res[j] = new Complex(ps[j].im/ps.length, ps[j].re/ps.length)
	}

	return res;
}