import { FFT, IFFT } from './furie-transform';
import { convolution } from './convolution';

export const reject_filter = (y: number[], filter_window_length: number, signal_length: number): number[] => {
    const transmission_frequency = 0.5;

    const y_after_fft = FFT(structuredClone(y)); 

    const items: number[] = [];

    for (let i = 0; i < signal_length; i++) {
        const temp = i - filter_window_length / 2;

        items.push(1 - 2 * transmission_frequency * Math.cos(Math.PI * temp * i / signal_length) + transmission_frequency);

        // items[i] = items[i] * (окно хемминга)
        items[i] = items[i] * (0.54 - 0.46 * Math.cos(2 * Math.PI * i / filter_window_length));
    }

    const items_sum = items.reduce((sum, item) => sum + item, 0);
    items.forEach((item) => -(item / items_sum));

    items[Math.floor(signal_length / 2)] += 1;

    const conv = convolution(y_after_fft, items, Math.floor(filter_window_length));

    return IFFT(conv);
}