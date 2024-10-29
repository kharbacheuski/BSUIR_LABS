import { isPixelIsBright, removeBackground } from "./outline";
import { getPixelRGB } from "./utils";

const removePixelsInRange = (pixels: ImageData, color1: { red: number; green: number; blue: number }, color2: { red: number; green: number; blue: number }) => {
    const width = pixels.width;
    const height = pixels.height;
    const output = new Uint8ClampedArray(pixels.data.length);

    // Убедимся, что color1 - это меньший цвет, а color2 - больший
    const minColor = {
        red: Math.min(color1.red, color2.red),
        green: Math.min(color1.green, color2.green),
        blue: Math.min(color1.blue, color2.blue)
    };

    const maxColor = {
        red: Math.max(color1.red, color2.red),
        green: Math.max(color1.green, color2.green),
        blue: Math.max(color1.blue, color2.blue)
    };

    // Проходим по всем пикселям изображения
    for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
            const idx = (y * width + x) * 4;
            const currentPixel = {
                red: pixels.data[idx],
                green: pixels.data[idx + 1],
                blue: pixels.data[idx + 2]
            };

            // Проверяем, попадает ли текущий пиксель в диапазон
            const isInRange =
                currentPixel.red >= minColor.red && currentPixel.red <= maxColor.red &&
                currentPixel.green >= minColor.green && currentPixel.green <= maxColor.green &&
                currentPixel.blue >= minColor.blue && currentPixel.blue <= maxColor.blue;

            // Если пиксель в диапазоне, устанавливаем его прозрачным
            if (isInRange) {
                output[idx] = 0;     // Красный
                output[idx + 1] = 0; // Зеленый
                output[idx + 2] = 0; // Синий
                output[idx + 3] = 0; // Альфа (прозрачность)
            } else {
                // Если не попадает, копируем оригинальный пиксель
                output[idx] = pixels.data[idx];
                output[idx + 1] = pixels.data[idx + 1];
                output[idx + 2] = pixels.data[idx + 2];
                output[idx + 3] = pixels.data[idx + 3];
            }
        }
    }

    return new ImageData(output, width, height);
}

document.getElementById('fileInput').addEventListener('change', function(event) {
    const file = (event.target as HTMLInputElement).files[0];
    if (!file) return;

    const reader = new FileReader();

    reader.onload = function(e) {
        const img = new Image();
        img.onload = () => {
            const canvas = document.getElementById("canvas") as HTMLCanvasElement;
            const context = canvas.getContext("2d");

            canvas.width = img.width;
            canvas.height = img.height;

            const newImage = removeBackground(img, context)
            const shapes = removePixelsInRange(newImage, { red: 3, green: 90, blue: 211 }, { red: 54, green: 94, blue: 156 });

            context.putImageData(shapes, 0, 0);
        };

        img.src = e.target.result as string;
    };
    reader.readAsDataURL(file);
});