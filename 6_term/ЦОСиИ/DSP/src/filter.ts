import { FFT, IFFT } from './furie-transform';
import { convolution } from './convolution';

export const reject_filter = (y: number[], filter_window_length: number = 9, signal_length: number = y.length): number[] => {
    const cuttoff_frequency = 0.05;

    const spectrum = FFT(structuredClone(y)); 

    const filter: number[] = [];

    for (let i = 0; i < signal_length; i++) {
        let temp = i - filter_window_length / 2;

        let coefficient = 1 - 2*cuttoff_frequency*Math.cos(2 * Math.PI * temp *i / signal_length) + cuttoff_frequency;
        let hamming = (0.54 - 0.46 * Math.cos(2 * Math.PI * i / filter_window_length));
        
        filter.push(coefficient * hamming);
    }

    const conv = convolution(spectrum, filter, filter_window_length);

    return IFFT(conv);
}