import { getXAAxis, getYAxis, FFT } from "./furie-transform"
import Chart from "chart.js/auto";

const N = 64

const x = getXAxis(64);
const y = (x) => Math.sin(5*x) + Math.cos(x) 

const signal = getYAxis(y, N)
const fftSignal = FFT(signal)

new Chart(document.getElementById("initial"), {
    type: 'line',
    data: {
        labels: x,
        datasets: [{
            label: 'График исходной функции: sin(5x) + cos(x)',
            data: signal,
            borderColor: 'blue',
            borderWidth: 1
        }]
    },
});

new Chart(document.getElementById("fftFunction"), {
    type: 'line',
    data: {
        labels: x,
        datasets: [{
            label: 'График БПФ функции',
            data: fftSignal.map(point => point.re),
            borderColor: 'red',
            borderWidth: 1
        }]
    },
});

