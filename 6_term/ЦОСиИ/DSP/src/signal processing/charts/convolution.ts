import { linear_convolution, curcular_convolution, FFT_convolution } from "../convolution"
import { getAxis, getPoints } from '../overrides'
import Chart, {ChartItem} from "chart.js/auto";
import convolve from "convolution"

const N = 8
const x = (arg: number) => Math.cos(2*arg)
const y = (arg: number) => Math.sin(5*arg)

const axis1 = getAxis(x, N)
const axis2 = getAxis(y, N)

console.log(axis1, axis2)

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
    
    const curcular_convolution_res = curcular_convolution(structuredClone(axis1.y), structuredClone(axis2.y)) 
    
    new Chart(document.getElementById("circular-convolution") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'Циклическая свертка',
                data: curcular_convolution_res,
                borderColor: 'blue',
                borderWidth: 1
            }]
        },
    });

    const linear_convolution_res = linear_convolution(structuredClone(axis1.y), structuredClone(axis2.y)) 
    
    new Chart(document.getElementById("linear-convolution") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'Линейная свертка',
                data: linear_convolution_res,
                borderColor: 'blue',
                borderWidth: 1
            }]
        },
    });

    const lib_convolution_res = convolve(structuredClone(axis1.y), structuredClone(axis2.y)) 
    
    new Chart(document.getElementById("lib-convolution") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'Свертка библиотечная',
                data: lib_convolution_res,
                borderColor: 'blue',
                borderWidth: 1
            }]
        },
    });
    
    const fft_convolution_res = FFT_convolution(structuredClone(axis1.y), structuredClone(axis2.y))
    
    new Chart(document.getElementById("fft-convolution") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'БПФ свертка',
                data: fft_convolution_res,
                borderColor: 'black',
                borderWidth: 1
            }]
        },
    });
}

document.addEventListener('DOMContentLoaded', render)