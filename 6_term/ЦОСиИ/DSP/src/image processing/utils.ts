export const getPixelRGB = (list, i) => {
    return {
        red: list[i],
        green: list[i + 1],
        blue: list[i + 2],
        alpha: list[i + 3]
    }
}

export function convertTo2DArray(pixels, width) {
    const height = pixels.length / (width * 4);
    const result = [];

    for (let y = 0; y < height; y++) {
        const row = [];

        for (let x = 0; x < width; x++) {
            const index = (y * width + x) * 4;
            const pixel = getPixelRGB(pixels, index);

            row.push(pixel);
        }

        result.push(row);
    }
    
    return result;
}

export function convertTo1DArray(pixelMatrix) {
    // Инициализируем пустой одномерный массив
    const pixels = [];
    
    // Пробегаем по каждой строке и каждому пикселю в строке
    for (let y = 0; y < pixelMatrix.length; y++) {
        for (let x = 0; x < pixelMatrix[y].length; x++) {
            // Извлекаем текущий пиксель
            const pixel = pixelMatrix[y][x];
            // Добавляем значения R, G, B и A в одномерный массив
            pixels.push(pixel.red, pixel.green, pixel.blue, pixel.alpha);
        }
    }
    
    return pixels;
}