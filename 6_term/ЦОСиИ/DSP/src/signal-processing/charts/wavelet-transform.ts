
import { getAxis, getPoints } from '../overrides'
import Chart, { ChartItem } from "chart.js/auto";
import { haarWaveletTransform, inverseHaarWaveletTransform } from "../wavelet-transform";
import wt from "discrete-wavelets"

const colors = [
    "red",
    "blue",
    "orange",
    "black",
    "green",
    "purple",
]

const N = 16

const func = (arg: number) => Math.cos(arg) + Math.sin(5*arg) 
const funcAxis = getAxis(func, N)

const level = Math.log2(N)

const coeffs = haarWaveletTransform(structuredClone(funcAxis.y), level)
const reconstructed_signal = inverseHaarWaveletTransform(coeffs)

const lib_coeffs = wt.wavedec(structuredClone(funcAxis.y), "haar", null, level)
const lib_reconstructed_signal = wt.waverec(lib_coeffs, "haar")

const points = getPoints(N/2)

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
    
    new Chart(document.getElementById("wt") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: coeffs.map((coeffs_level, i) => {
                return {
                    label: `Сигнал после ВП. Level ${i+1}`,
                    data: coeffs_level,
                    borderColor: colors[i],
                    borderWidth: 1
                }
            }),   
        },
    });

    new Chart(document.getElementById("iwt") as ChartItem, {
        type: 'line',
        data: {
            labels: funcAxis.x,
            datasets: [{
                label: 'Восстановленный сигнал',
                data: reconstructed_signal,
                borderColor: 'green',
                borderWidth: 1
            }]
        },
    });

    new Chart(document.getElementById("lib-wt") as ChartItem, {
        type: 'line',
        data: {
            labels: points,
            datasets: lib_coeffs.map((coeffs_level, i) => {
                return {
                    label: `Сигнал после ВП (lib). Level ${i+1}`,
                    data: coeffs_level,
                    borderColor: colors[i],
                    borderWidth: 1
                }
            }),   
        },
    });

    new Chart(document.getElementById("lib-iwt") as ChartItem, {
        type: 'line',
        data: {
            labels: funcAxis.x,
            datasets: [{
                label: 'Восстановленный сигнал (lib)',
                data: lib_reconstructed_signal,
                borderColor: 'red',
                borderWidth: 1
            }]
        },
    });
}

document.addEventListener('DOMContentLoaded', render)