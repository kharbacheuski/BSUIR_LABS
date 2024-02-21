import { getAxis, FFT } from "./furie-transform"
import Chart from "chart.js/auto";
import { fft } from "fft-js";

const N = 64
const func = (x) => Math.sin(5*x) + Math.cos(x) 
const axis = getAxis(func, N)

new Chart(document.getElementById("initial"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График исходной функции: sin(5x) + cos(x)',
            data: axis.coords,
            borderColor: 'green',
            borderWidth: 1
        }]
    },
});

const fftRes = FFT(structuredClone(axis.y));

const data1 = fftRes.map((point, ix) => {
    return {
        x: point.re,
        y: point.im
    }
});

new Chart(document.getElementById("fftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График функции после БПФ',
            data: data1,
            borderColor: 'red',
            borderWidth: 1
        }]
    },
});


const data2 = fftRes.map((point, ix) => {
    return {
        x: axis.x[ix],
        y: point.re
    }
});

new Chart(document.getElementById("re-fftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График реальной части после БПФ',
            data: data2,
            borderColor: 'red',
            borderWidth: 1
        }]
    },
});

const data3 = fftRes.map((point, ix) => {
    return {
        x: axis.x[ix],
        y: point.im
    }
});

new Chart(document.getElementById("im-fftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График воображаемой части после БПФ',
            data: data3,
            borderColor: 'red',
            borderWidth: 1
        }]
    },
});

const data4 = fft(structuredClone(axis.y)).map((point, ix) => {
    return {
        x: axis.x[ix],
        y: point[0]
    }
});

new Chart(document.getElementById("libfftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График библиотечной БПФ функции',
            data: data4,
            borderColor: 'blue',
            borderWidth: 1
        }]
    },
});