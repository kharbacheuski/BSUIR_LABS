function dft(inner) {
    let out = [];
    let iterations = [0, 0];
    let length = inner.length;

    for (let m = 0; m < length; m++) {
        let temp = { re: 0.0, im: 0.0 };
        for (let n = 0; n < length; n++) {
            let arg = -2 * Math.PI * m * n / length;
            let cos = Math.cos(arg);
            let sin = Math.sin(arg);
            temp.re += inner[n] * cos;
            temp.im += inner[n] * sin;
            iterations[0] += 2;
            iterations[1] += 2;
        }
        out.push({ re: temp.re, im: temp.im });
    }
    return [out, iterations];
}

function idft(inner) {
    let out = [];
    let length = inner.length;

    for (let m = 0; m < length; m++) {
        let temp = { re: 0.0, im: 0.0 };
        for (let n = 0; n < length; n++) {
            let arg = 2 * Math.PI * m * n / length;
            let cos = Math.cos(arg);
            let sin = Math.sin(arg);
            temp.re += inner[n].re * cos;
            temp.im += inner[n].im * sin;
        }
        out.push({ re: temp.re / length, im: temp.im / length });
    }
    return out;
}

function fft(inner, iterations=[0, 0]) {
    let out = [];
    let length = inner.length;

    if (length === 2) {
        out.push(inner[0] + inner[1]);
        out.push(inner[0] - inner[1]);
        iterations = [iterations[0] + 2, iterations[1]];
    } else {
        let even = [];
        let odd = [];
        for (let i = 0; i < length; i++) {
            if (i % 2 === 0) {
                even.push(inner[i]);
            } else {
                odd.push(inner[i]);
            }
        }

        let tempEven = fft(even, iterations);
        let tempOdd = fft(odd, iterations);
        console.log(tempEven);
        console.log(tempOdd);
        even = tempEven[0];
        odd = tempOdd[0];
        iterations = [tempEven[1][0], tempEven[1][1]];

        out = new Array(length);
        for (let i = 0; i < length / 2; i++) {
            out[i] = even[i] +  _w(i, length) * odd[i];
            console.log(_w(i, length));
            out[i + length / 2] = even[i] -  _w(i, length) * odd[i];
            iterations = [tempEven[1] + 1, tempOdd[1] + 2];
        }
    }

    return [out, iterations];
}


function ifft(inner) {
    let length = inner.length;
    let out = [];

    if (length === 2) {
        out.push({ re: inner[0].re + inner[1].re, im: inner[0].im + inner[1].im });
        out.push({ re: inner[0].re - inner[1].re, im: inner[0].im - inner[1].im });
    } else {
        let even = [];
        let odd = [];
        for (let i = 0; i < length; i++) {
            if (i % 2 === 0) {
                even.push(inner[i]);
            } else {
                odd.push(inner[i]);
            }
        }

        even = ifft(even);
        odd = ifft(odd);

        for (let i = 0; i < length / 2; i++) {
            let wConj = { re: _w(i, length).re, im: -_w(i, length).im };
            let product = { re: wConj.re * odd[i].re - wConj.im * odd[i].im, im: wConj.re * odd[i].im + wConj.im * odd[i].re };
            out[i] = { re: even[i].re + product.re, im: even[i].im + product.im };
            out[i + length / 2] = { re: even[i].re - product.re, im: even[i].im - product.im };
        }
    }
    return out;
}

function _w(k, n) {
    if (k % n === 0) {
        return [1, 0]; 
    }
    let arg = -2 * Math.PI * k / n;
    let realPart = Math.cos(arg);
    let imaginaryPart = Math.sin(arg);

    return [realPart, imaginaryPart]; 
}

function sampled(func, n, period = (2 * Math.PI)) {
    let out = [];
    for (let i = 0; i < n; i++) {
        out.push(func(period * (i + 1) / n));
    }
    return out;
}

function main() {
    let func = (x) => Math.sin(5 * x) + Math.cos(2 * x);

    let N = 32;
    let inner = sampled(func, N);

    let [spectrumDft, iterationsDft] = dft(inner);
    let [spectrumFft, iterationsFft] = fft(inner);

    console.log(spectrumFft);
    console.log(iterationsFft);

    let x = [];
    for (let i = 0; i < 2 * Math.PI; i += 0.1) {
        x.push(i);
    }
    let y = x.map(val => Math.sin(5 * val) + Math.cos(2 * val));
        
    new Chart(document.getElementById("sourceFunction"), {
        type: 'line',
        data: {
            labels: x,
            datasets: [{
                label: 'Source function: sin(5x) + cos(2x)',
                data: y,
                borderColor: 'blue',
                borderWidth: 1
            }]
        },
    });

    new Chart(document.getElementById("sampledSignal"), {
        type: 'line',
        data: {
            labels: [...Array(N).keys()],
            datasets: [{
                label: 'Sampled signal, N = 32',
                data: inner,
                borderColor: 'blue',
                borderWidth: 1,
                pointStyle: 'circle',
                pointRadius: 5
            }]
        },
    });

    new Chart(document.getElementById("dftPhase"), {
        type: 'line',
        data: {
            labels: [...Array(N).keys()],
            datasets: [{
                label: 'DFT. Phase spectrum',
                data: spectrumDft.map(complexNumber => Math.atan2(complexNumber.im, complexNumber.re)),
                borderColor: 'blue',
                borderWidth: 1,
                pointStyle: 'circle',
                pointRadius: 5
            }]
        },
    });

    new Chart(document.getElementById("dftAmplitude"), {
        type: 'line',
        data: {
            labels: [...Array(N).keys()],
            datasets: [{
                label: 'DFT. Amplitude spectrum',
                data: spectrumDft.map(complexNumber => Math.sqrt(complexNumber.re ** 2 + complexNumber.im ** 2)),
                borderColor: 'blue',
                borderWidth: 1,
                pointStyle: 'circle',
                pointRadius: 5
            }]
        },
    });

    new Chart(document.getElementById("inverseDft"), {
        type: 'line',
        data: {
            labels: [...Array(N).keys()],
            datasets: [{
                label: 'Inverse DFT',
                data: idft(spectrumDft).map(complexNumber => complexNumber.re),
                borderColor: 'red',
                borderWidth: 1,
                pointStyle: 'circle',
                pointRadius: 5
            }]
        },
    });
    

    new Chart(document.getElementById("fftPhase"), {
        type: 'line',
        data: {
            labels: [...Array(N).keys()],
            datasets: [{
                label: 'FFT. Phase spectrum',
                data: spectrumFft.map(complexNumber => Math.atan2(complexNumber.im, complexNumber.re)),
                borderColor: 'blue',
                borderWidth: 1,
                pointStyle: 'circle',
                pointRadius: 5
            }]
        },
    });
    
    new Chart(document.getElementById("fftAmplitude"), {
        type: 'line',
        data: {
            labels: [...Array(N).keys()],
            datasets: [{
                label: 'FFT. Amplitude spectrum',
                data: spectrumFft.map(complexNumber => Math.sqrt(complexNumber.re ** 2 + complexNumber.im ** 2)),
                borderColor: 'blue',
                borderWidth: 1,
                pointStyle: 'circle',
                pointRadius: 5
            }]
        },
    });
    
    new Chart(document.getElementById("inverseFft"), {
        type: 'line',
        data: {
            labels: [...Array(N).keys()],
            datasets: [{
                label: 'Inverse FFT',
                data: ifft(spectrumFft).map(complexNumber => complexNumber.re / N),
                borderColor: 'red',
                borderWidth: 1,
                pointStyle: 'circle',
                pointRadius: 5
            }]
        },
    });
    


    console.log("=== Number of operations using DFT ===");
    console.log("Sum:", iterationsDft[0], ", Mul:", iterationsDft[1]);

    console.log("=== Number of operations using FFT ===");
    console.log("Sum:", iterationsFft[0], ", Mul:", iterationsFft[1]);
}

main()


