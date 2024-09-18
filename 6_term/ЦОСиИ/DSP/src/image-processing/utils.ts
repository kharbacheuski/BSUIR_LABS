export const colorInRange = (color, basis) => {
    const accurace = {
        red: 10,
        green: 20,
        blue: 35
    };
    
    return (
        (color.red >= basis.red - accurace.red && color.red <= basis.red + accurace.red) &&
        (color.green >= basis.green - accurace.green && color.green <= basis.green + accurace.green) &&
        (color.blue >= basis.blue - accurace.blue && color.blue <= basis.blue + accurace.blue)
    )
};


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

export function hexToRGB(hex: string): { red: number, green: number, blue: number, alpha: number } | null {
    // Убираем # если он есть
    hex = hex.replace(/^#/, '');

    // Проверяем, что длина строки соответствует формату HEX
    if (hex.length !== 3 && hex.length !== 6) {
        return null; // Неверный формат
    }

    // Если формат короткий (например, #FFF), расширяем его до длинного (например, #FFFFFF)
    if (hex.length === 3) {
        hex = hex.split('').map(char => char + char).join('');
    }

    const bigint = parseInt(hex, 16);
    const red = (bigint >> 16) & 255;
    const green = (bigint >> 8) & 255;
    const blue = bigint & 255;

    return { red, green, blue, alpha: 255 };
}

const getDistance = (color1, color2) => {
    return Math.sqrt(
        Math.pow(color1.red - color2.red, 2) +
        Math.pow(color1.green - color2.green, 2) +
        Math.pow(color1.blue - color2.blue, 2)
    );
};

const isDistinctColor = (color, colors, threshold) => {
    for (const c of colors) {
        if (getDistance(color, c) < threshold) {
            return false;
        }
    }
    return true;
};

export const getDistinctColors = (imageData, numColors, threshold = 100) => {
    const colorMap: {[key: string]: {
        count: number,
        rgb: { red: number, green: number, blue: number, alpha: number }
    }} = {};
    
    // Подсчет количества пикселей для каждого цвета
    for (let i = 0; i < imageData.data.length; i += 4) {
        const pixel = getPixelRGB(imageData.data, i);
        const hex = `#${((1 << 24) + (pixel.red << 16) + (pixel.green << 8) + pixel.blue).toString(16).slice(1)}`;

        if (!colorMap[hex]) {
            colorMap[hex] = { count: 0, rgb: pixel }; // Сохраняем цвет и его количество
        }
        colorMap[hex].count++;
    }

    // Сортируем по количеству пикселей
    const sortedColors = Object.values(colorMap)
        .sort((a, b) => b.count - a.count)
        .map(item => item.rgb);

    const distinctColors = [];

    // Выбираем только отличающиеся цвета
    for (const color of sortedColors) {
        if (isDistinctColor(color, distinctColors, threshold)) {
            distinctColors.push(color);
        }
        if (distinctColors.length >= numColors) {
            break;
        }
    }

    return distinctColors; // Возвращаем массив RGB объектов
};