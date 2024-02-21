import { getAxis, FFT, IFFT } from "./furie-transform"
import Chart from "chart.js/auto";
import { fft, ifft } from "fft-js";

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
        x: point.im,
        y: point.re
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


new Chart(document.getElementById("re-fftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График реальной части после БПФ',
            data: data1.map((point, ix) => point.x),
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
            data: data1.map((point, ix) => point.y),
            borderColor: 'red',
            borderWidth: 1
        }]
    },
});

const ifftRes = IFFT(fftRes);

const data4 = ifftRes.map((point, ix) => {
    return {
        x: point.im,
        y: point.re
    }
});

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

const data5 = fft(structuredClone(axis.y)).map((point, ix) => {
    return {
        x: point[1],
        y: point[0]
    }
});

new Chart(document.getElementById("libfftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График библиотечной БПФ функции',
            data: data5,
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
            data: data5.map((point, ix) => point.x),
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
            data: data5.map((point, ix) => point.y),
            borderColor: 'blue',
            borderWidth: 1
        }]
    },
});

const data6 = ifft(fft(structuredClone(axis.y))).map((point, ix) => {
    return {
        x: point[1],
        y: point[0]
    }
});

new Chart(document.getElementById("libifftFunction"), {
    type: 'line',
    data: {
        labels: axis.x,
        datasets: [{
            label: 'График библиотечной обратной БПФ функции',
            data: data6,
            borderColor: 'blue',
            borderWidth: 1
        }]
    },
});