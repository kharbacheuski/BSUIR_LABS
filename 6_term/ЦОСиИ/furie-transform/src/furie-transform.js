import Complex from 'complex.js';
import "./overrides.js";

const step = 2*Math.PI

export const getAxis = (func, N) => {
	const axis = [];

	for (let i = 1; i <= N; i++) {
		let arg = step*i/N;

		axis.push({
			x: Number(arg.toFixed(2)),
			y: Number(func(arg).toFixed(3))
		})
    }

	const x = axis.map(point => point.x);
	const y = axis.map(point => point.y)
	
	return {
		axis,
		x,
		y 
	}
}

export const FFT = (signal) => {
    let N = signal.length;

	if( N == 1 ) return signal;
	
	let hN = N / 2;
	let a_even = signal.slice(0, hN);
	let a_odd = signal.slice(hN);

	let b_even = FFT(a_even);
	let b_odd = FFT(a_odd);

	const WN = Math.exp(2*Math.PI * new Complex(0, 1)/N)
	let w = 1;

	let y = []

	for(let j = 0; j <= hN; j++) {	
		y[j] = b_even[j] + b_odd[j]*w;
		y[j + hN] = b_even[j] - b_odd[j]*w
		w = w*WN;
	}

	return y
}