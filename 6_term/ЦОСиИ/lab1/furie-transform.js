// Условие 


Number.prototype.arrange = function() {
    let arr = [];

    for (let i = 0; i < this; i += 1){
        arr.push(i);
    }

    return arr;
}

const getSignal = (func, N, step = 2*Math.PI) => {
    let points = [];

    for (let i = 0; i < N; i++) {
        points.push(func(step*(i+1)/N));
    }

    return points;
}

const y = (x) => Math.sin(5*x) + Math.cos(x) 

console.log(getSignal(y, 64))

const FFT = (signal) => {
    const length = signal.length;

    if(length <= 1) {
        return signal;
    }
    else {
        const evenSignal = signal.filter((item, index) => index % 2 === 0);
        const oddSignal = signal.filter((item, index) => index % 2 !== 0);

        const evenFFT = FFT(evenSignal);
        const oddFFT = FFT(oddSignal);

        const factor = Math.exp(-2j * Math.PI * length.arrange() / length);
    }
}