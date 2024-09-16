import { reject_filter } from "../filter";
import { FFT } from "../furie-transform";
import { getAxis, getPoints } from '../overrides'
import Chart, { ChartItem } from "chart.js/auto";

const N = 64

const func = (arg: number) => Math.sin(5*arg) + Math.cos(arg) 
const funcAxis = getAxis(func, N)

const noise = (arg: number) => Math.cos(90*Math.PI*arg)
const noiseAxis = getAxis(noise, N)

const noisedfuncY = noiseAxis.y.map((noisePoint, index) => funcAxis.y[index] + noisePoint)

const points = getPoints(N)

const render = () => {
    new Chart(document.getElementById("initial") as ChartItem, {
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
    
    new Chart(document.getElementById("initial-ach") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'АЧХ входного сигнала',
                data: fftRes.map(point => point.abs()),
                borderColor: 'red',
                borderWidth: 1
            }]
        },
    });

    new Chart(document.getElementById("noise") as ChartItem, {
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

    new Chart(document.getElementById("noise-ach") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'АЧХ шума',
                data: fftResNoise.map(point => point.abs()),
                borderColor: 'red',
                borderWidth: 1
            }]
        },
    });

    new Chart(document.getElementById("noised-signal") as ChartItem, {
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

    new Chart(document.getElementById("noised-signal-ach") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'АЧХ сигнала с шумом',
                data: fftResNoisedFuncY.map(point => point.abs()),
                borderColor: 'red',
                borderWidth: 1
            }]
        },
    });

    const kih = reject_filter(structuredClone(noisedfuncY))

    new Chart(document.getElementById("kih") as ChartItem, {
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

    const fftReskih = FFT(structuredClone(kih), 1)

    new Chart(document.getElementById("kih-ach") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
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