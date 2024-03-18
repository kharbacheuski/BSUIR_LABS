import { convolution, FFT_convolution } from "../convolution"
import { getAxis, getPoints } from '../overrides'
import Chart from "chart.js/auto";

const N = 66
const x = (arg) => Math.sin(5*arg)
const y = (arg) => Math.cos(arg) 

const axis1 = getAxis(x, N)
const axis2 = getAxis(y, N)

const points = getPoints(N)

const render = () => {
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
    
    const convolution_res = convolution(structuredClone(axis1.y), structuredClone(axis2.y)) 
    
    new Chart(document.getElementById("convolution"), {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'Свертка',
                data: convolution_res,
                borderColor: 'blue',
                borderWidth: 1
            }]
        },
    });
    
    const fft_convolution_res = FFT_convolution(structuredClone(axis1.y), structuredClone(axis2.y))
    
    new Chart(document.getElementById("fft-convolution"), {
        type: 'line',
        data: {
            labels: points,
            datasets: [{
                label: 'БПФ свертка',
                data: fft_convolution_res.map(point => point.re),
                borderColor: 'black',
                borderWidth: 1
            }]
        },
    });
}

document.addEventListener('DOMContentLoaded', render)