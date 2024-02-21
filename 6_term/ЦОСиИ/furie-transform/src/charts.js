import { getAxis, FFT, IFFT, complexModule } from "./furie-transform"
import Chart from "chart.js/auto";
import Complex from "complex.js";
import { fft, ifft,  } from "fft-js";

const N = 64
const func = (x) => Math.sin(5*x) + Math.cos(x) 
const axis = getAxis(func, N)

new Chart(document.getElementById("initial"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График исходной функции: sin(5x) + cos(x)',
            data: axis.y,
            borderColor: 'green',
            borderWidth: 1
        }]
    },
});

const fftRes = FFT(structuredClone(axis.y));

console.log(fftRes)

new Chart(document.getElementById("fftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График функции после БПФ',
            data: fftRes.map(point => complexModule(point)),
            borderColor: 'red',
            borderWidth: 1
        }]
    },
});


new Chart(document.getElementById("re-fftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График реальной части после БПФ',
            data: fftRes.map(point => point.re),
            borderColor: 'red',
            borderWidth: 1
        }]
    },
});

new Chart(document.getElementById("im-fftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График воображаемой части после БПФ',
            data: fftRes.map(point => point.im),
            borderColor: 'red',
            borderWidth: 1
        }]
    },
});

const ifftRes = IFFT(fftRes);

const data4 = ifftRes.map(point => point.re);

new Chart(document.getElementById("ifftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График обратной БПФ функции',
            data: data4,
            borderColor: 'red',
            borderWidth: 1
        }]
    },
});

const data5 = fft(structuredClone(axis.y));

const modules = data5.map(point => complexModule(new Complex(point[0], point[1])))

new Chart(document.getElementById("libfftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График библиотечной БПФ функции',
            data: modules,
            borderColor: 'blue',
            borderWidth: 1
        }]
    },
});

new Chart(document.getElementById("re-libfftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График библиотечной реальной части БПФ функции',
            data: data5.map(point => point[0]),
            borderColor: 'blue',
            borderWidth: 1
        }]
    },
});

new Chart(document.getElementById("im-libfftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График библиотечной воображаемой части БПФ функции',
            data: data5.map(point => point[1]),
            borderColor: 'blue',
            borderWidth: 1
        }]
    },
});

const data6 = ifft(data5);

new Chart(document.getElementById("libifftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График библиотечной обратной БПФ функции',
            data: data6.map(point => point[0]),
            borderColor: 'blue',
            borderWidth: 1
        }]
    },
});