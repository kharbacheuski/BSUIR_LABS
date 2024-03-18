import { convolution, FFT_convolution } from "../convolution"
import { getAxis, getPoints, complexModule } from '../overrides'
import Chart from "chart.js/auto";

const N = 16
const x = (x) => Math.sin(5*x)
const y = (y) => Math.cos(y) 

const axis1 = getAxis(x, N)
const axis2 = getAxis(y, N)

const points = getPoints(N)

new Chart(document.getElementById("initial-x"), {
    type: 'line',
    data: {
        labels: axis1.x,
        datasets: [{
            label: 'График исходной функции: sin(5x)',
            data: axis1.y,
            borderColor: 'green',
            borderWidth: 1
        }]
    },
});

new Chart(document.getElementById("initial-y"), {
    type: 'line',
    data: {
        labels: axis2.x,
        datasets: [{
            label: 'График исходной функции: cos(x)',
            data: axis2.y,
            borderColor: 'red',
            borderWidth: 1
        }]
    },
});

const convolution_res = convolution(axis1.y, axis2.y) 

new Chart(document.getElementById("convolution"), {
    type: 'line',
    data: {
        labels: points,
        datasets: [{
            label: 'Кореляция',
            data: convolution_res,
            borderColor: 'blue',
            borderWidth: 1
        }]
    },
});

const fft_convolution_res = FFT_convolution(axis1.y, axis2.y)

new Chart(document.getElementById("fft-convolution"), {
    type: 'line',
    data: {
        labels: points,
        datasets: [{
            label: 'БПФ кореляция',
            data: fft_convolution_res.map(point => complexModule(point)),
            borderColor: 'black',
            borderWidth: 1
        }]
    },
});
