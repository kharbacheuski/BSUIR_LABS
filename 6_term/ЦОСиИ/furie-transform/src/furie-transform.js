import Complex from 'complex.js';
import "./overrides.js";

const step = 2*Math.PI

export const getYAxis = (func, N = 64) => {
    const ys = [];

    for (let i = 0; i < N; i++) {
        ys.push(func(step*(i+1)/N));
    }

    return ys;
}

export const getXAxis = (N = 64) => {
	const xes = [];

	for (let i = 0; i < N; i++) {
		xes.push(Number((step*(i+1)/N).toFixed(2)));
	}

	return xes
}

export const FFT = (signal) => {
    const N = signal.length;

	if( N <= 1 ) return signal;
	
	let hN = N / 2;
	let even = signal.slice(0, hN);
	let odd = signal.slice(hN);

	even = FFT(even);
	odd = FFT(odd);

	let a = -step;

	for(let k = 0; k < hN; ++k)
	{
		if(!(even[k] instanceof Complex))
			even[k] = new Complex(even[k], 0);
		if(!(odd[k] instanceof Complex))
			odd[k] = new Complex(odd[k], 0);
		let p = k/N;
		let t = new Complex(0, a * p);
		t.cexp(t).mul(odd[k], t);
		signal[k] = even[k].add(t, odd[k]);
		signal[k + hN] = even[k].sub(t, even[k]);
	}

	return signal;
}

