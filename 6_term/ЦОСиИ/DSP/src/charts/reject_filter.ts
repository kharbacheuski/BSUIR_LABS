import { linear_convolution, curcular_convolution, FFT_convolution } from "../convolution"
import { reject_filter } from "../filter";
import { FFT } from "../furie-transform";
import { getAxis, getPoints } from '../overrides'
import Chart from "chart.js/auto";
import convolve from "convolution"

const filter_window_length = 16
const N = 64

const func = (arg: number) => Math.sin(5*arg) + Math.cos(arg) 
const funcAxis = getAxis(func, N)

const noise = (arg: number) => Math.cos(15*2*Math.PI*arg)
const noiseAxis = getAxis(noise, N)

const noisedfuncY = noiseAxis.y.map((noisePoint, index) => funcAxis.y[index] + noisePoint)


const render = () => {
    new Chart(document.getElementById("initial"), {
        type: 'line',
        data: {
            labels: funcAxis.x,
            datasets: [{
                label: 'Входной сигнал',
                data: funcAxis.y,
                borderColor: 'green',
                borderWidth: 1
            }]
        },
    });

    const fftRes = FFT(structuredClone(funcAxis.y), 1);
    
    new Chart(document.getElementById("initial-ach"), {
        type: 'line',
        data: {
            labels: funcAxis.x,
            datasets: [{
                label: 'АЧХ входного сигнала',
                data: fftRes.map(point => point.abs()),
                borderColor: 'red',
                borderWidth: 1
            }]
        },
    });

    new Chart(document.getElementById("noise"), {
        type: 'line',
        data: {
            labels: noiseAxis.x,
            datasets: [{
                label: 'Шум',
                data: noiseAxis.y,
                borderColor: 'green',
                borderWidth: 1
            }]
        },
    });

    const fftResNoise = FFT(structuredClone(noiseAxis.y), 1);

    new Chart(document.getElementById("noise-ach"), {
        type: 'line',
        data: {
            labels: noiseAxis.x,
            datasets: [{
                label: 'АЧХ шума',
                data: fftResNoise.map(point => point.abs()),
                borderColor: 'red',
                borderWidth: 1
            }]
        },
    });

    new Chart(document.getElementById("noised-signal"), {
        type: 'line',
        data: {
            labels: noiseAxis.x,
            datasets: [{
                label: 'Сигнал с шумом',
                data: noisedfuncY,
                borderColor: 'green',
                borderWidth: 1
            }]
        },
    });

    const fftResNoisedFuncY = FFT(structuredClone(noisedfuncY), 1);

    new Chart(document.getElementById("noised-signal-ach"), {
        type: 'line',
        data: {
            labels: noiseAxis.x,
            datasets: [{
                label: 'АЧХ сигнала с шумом',
                data: fftResNoisedFuncY.map(point => point.abs()),
                borderColor: 'red',
                borderWidth: 1
            }]
        },
    });

    const kih = reject_filter(structuredClone(noisedfuncY), filter_window_length, N)

    new Chart(document.getElementById("kih"), {
        type: 'line',
        data: {
            labels: noiseAxis.x,
            datasets: [{
                label: 'Cигнала с шумом после КИХ фильтра',
                data: kih,
                borderColor: 'green',
                borderWidth: 1
            }]
        },
    });

    const fftReskih = FFT(reject_filter(structuredClone(noisedfuncY), filter_window_length, N), 1)

    new Chart(document.getElementById("kih-ach"), {
        type: 'line',
        data: {
            labels: noiseAxis.x,
            datasets: [{
                label: 'АЧХ cигнала с шумом после КИХ фильтра',
                data: fftReskih.map(point => point.abs()),
                borderColor: 'red',
                borderWidth: 1
            }]
        },
    });
}

document.addEventListener('DOMContentLoaded', render)