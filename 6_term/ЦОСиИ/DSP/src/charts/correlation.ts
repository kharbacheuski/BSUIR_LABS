import { correlation, FFT_correlation } from "../correlation"
import { getAxis, getPoints } from '../overrides'
import Chart, { ChartItem } from "chart.js/auto";
import {correlation as lib_correlation} from "node-correlation"

const N = 16
const x = (arg: number) => Math.cos(2*arg)
const y = (arg: number) => Math.sin(5*arg)

const axis1 = getAxis(x, N)
const axis2 = getAxis(y, N)

const points = getPoints(N)

const render = () => {
    new Chart(document.getElementById("initial-x") as ChartItem, {
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
    
    new Chart(document.getElementById("initial-y") as ChartItem, {
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
    
    const correlation_res = correlation(structuredClone(axis1.y), structuredClone(axis2.y)) 
    
    new Chart(document.getElementById("correlation") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'Кореляция',
                data: correlation_res,
                borderColor: 'blue',
                borderWidth: 1
            }]
        },
    });

    const lib_correlation_res = lib_correlation(structuredClone(axis1.y), structuredClone(axis2.y)) 
    console.log(lib_correlation_res)
    
    const fft_correlation_res = FFT_correlation(structuredClone(axis1.y), structuredClone(axis2.y))
    
    new Chart(document.getElementById("fft-correlation") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'БПФ Кореляция',
                data: fft_correlation_res,
                borderColor: 'black',
                borderWidth: 1
            }]
        },
    });
}

document.addEventListener('DOMContentLoaded', render)
