import { getAxis, FFT } from "./furie-transform"
import Chart from "chart.js/auto";
import { dft, fft } from "fft-js";

const N = 64
const func = (x) => Math.sin(5*x) + Math.cos(x) 
const axis = getAxis(func, N)

new Chart(document.getElementById("initial"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График исходной функции: sin(5x) + cos(x)',
            data: structuredClone(axis.y),
            borderColor: 'green',
            borderWidth: 1
        }]
    },
});

new Chart(document.getElementById("fftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График БПФ функции',
            data: FFT(structuredClone(axis.y)),
            borderColor: 'red',
            borderWidth: 1
        }]
    },
});


new Chart(document.getElementById("libfftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График реализованной БПФ функции',
            data: fft(structuredClone(axis.y)),
            borderColor: 'blue',
            borderWidth: 1
        }]
    },
});