import { FFT, IFFT } from './furie-transform';
import { convolution } from './convolution';

export const reject_filter = (y: number[], filter_window_length: number = 16, signal_length: number = y.length): number[] => {
    const transmission_frequency = 0.5;

    const spectrum = FFT(structuredClone(y)); 

    const filter: number[] = [];

    for (let i = 0; i < signal_length; i++) {
        let temp = i - filter_window_length / 2;

        let coefficient = Math.exp(-2 * Math.PI * transmission_frequency * temp / signal_length);
        let hamming = (0.54 - 0.46 * Math.cos(2 * Math.PI * i / filter_window_length));
        
        filter.push(coefficient * hamming);
    }

    const conv = convolution(spectrum, filter, Math.floor(filter_window_length));

    return IFFT(conv);
}