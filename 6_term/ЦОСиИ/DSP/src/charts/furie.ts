import { FFT, IFFT, FFT_recursive } from "../furie-transform"
import { getAxis, getPoints } from '../overrides'
import Chart, { ChartItem } from "chart.js/auto";
import Complex from "complex.js";
import { fft, ifft } from "fft-js";

type ComplexAsArray = {[0]: number, [1]: number};

const N = 64
const func = (arg: number) => Math.sin(5*arg) + Math.cos(arg) 
const axis = getAxis(func, N)
const points = getPoints(N)

const render = () => {
    new Chart(document.getElementById("initial") as ChartItem, {
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
    
    const fftRes = FFT(structuredClone(axis.y), 1);
    
    new Chart(document.getElementById("fftFunction") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'График функции после БПФ',
                data: fftRes.map(point => point.abs()),
                borderColor: 'red',
                borderWidth: 1
            }]
        },
    });
    
    new Chart(document.getElementById("re-fftFunction") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'График реальной части после БПФ',
                data: fftRes.map(point => point.re),
                borderColor: 'red',
                borderWidth: 1
            }]
        },
    });
    
    new Chart(document.getElementById("im-fftFunction") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'График воображаемой части после БПФ',
                data: fftRes.map(point => point.im),
                borderColor: 'red',
                borderWidth: 1
            }]
        },
    });
    
    const ifftRes = IFFT(structuredClone(fftRes));
    
    new Chart(document.getElementById("ifftFunction") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'График обратной БПФ функции',
                data: ifftRes,
                borderColor: 'red',
                borderWidth: 1
            }]
        },
    });
    
    const data5: ComplexAsArray[] = fft(structuredClone(axis.y));
    
    new Chart(document.getElementById("libfftFunction") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'График библиотечной БПФ функции',
                data: data5.map(point => new Complex(point[0], point[1]).abs()),
                borderColor: 'blue',
                borderWidth: 1
            }]
        },
    });
    
    new Chart(document.getElementById("re-libfftFunction") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'График библиотечной реальной части БПФ функции',
                data: data5.map(point => point[0]),
                borderColor: 'blue',
                borderWidth: 1
            }]
        },
    });
    
    new Chart(document.getElementById("im-libfftFunction") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'График библиотечной воображаемой части БПФ функции',
                data: data5.map(point => point[1]),
                borderColor: 'blue',
                borderWidth: 1
            }]
        },
    });
    
    
    new Chart(document.getElementById("libifftFunction") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'График библиотечной обратной БПФ функции',
                data: (ifft(structuredClone(data5)) as ComplexAsArray[]).map(point => point[0]),
                borderColor: 'blue',
                borderWidth: 1
            }]
        },
    });
}

document.addEventListener('DOMContentLoaded', render)