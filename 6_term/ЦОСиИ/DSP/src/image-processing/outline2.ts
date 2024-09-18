document.getElementById('upload').addEventListener('change', handleImageUpload);

function handleImageUpload(event) {
    const file = event.target.files[0];
    if (!file) return;

    const img = new Image();
    const reader = new FileReader();

    reader.onload = function(e) {
        img.src = e.target.result as string;
    };

    img.onload = function() {
        const canvas = document.getElementById('canvas') as HTMLCanvasElement;
        const ctx = canvas.getContext('2d');
        canvas.width = img.width;
        canvas.height = img.height;
        ctx.drawImage(img, 0, 0);

        const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
        const edges = sobelFilter(imageData);
        ctx.putImageData(edges, 0, 0);
    };

    reader.readAsDataURL(file);
}

function sobelFilter(imageData) {
    const width = imageData.width;
    const height = imageData.height;
    const data = imageData.data;
    const outputData = new Uint8ClampedArray(data.length);
    
    const Gx = [
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1
    ];
    
    const Gy = [
        1, 2, 1,
        0, 0, 0,
        -1, -2, -1
    ];
    
    const threshold = 100; // Порог для выделения контуров

    for (let y = 1; y < height - 1; y++) {
        for (let x = 1; x < width - 1; x++) {
            let pixelX = 0;
            let pixelY = 0;

            for (let j = -1; j <= 1; j++) {
                for (let i = -1; i <= 1; i++) {
                    const idx = ((y + j) * width + (x + i)) * 4;
                    const r = data[idx];
                    const g = data[idx + 1];
                    const b = data[idx + 2];
                    const intensity = (r + g + b) / 3;

                    pixelX += Gx[(j + 1) * 3 + (i + 1)] * intensity;
                    pixelY += Gy[(j + 1) * 3 + (i + 1)] * intensity;
                }
            }

            const magnitude = Math.sqrt(pixelX * pixelX + pixelY * pixelY) | 0;
            const idx = (y * width + x) * 4;

            // Применяем порог для выделения контуров
            if (magnitude > threshold) {
                outputData[idx] = 0; // Черный цвет для контуров
                outputData[idx + 1] = 0; // Черный цвет для контуров
                outputData[idx + 2] = 0; // Черный цвет для контуров
                outputData[idx + 3] = 255; // Альфа-канал
            } else {
                // outputData[idx] = 0; // Черный цвет для фона
                // outputData[idx + 1] = 0; // Черный цвет для фона
                // outputData[idx + 2] = 0; // Черный цвет для фона
                outputData[idx + 3] = 0; // Альфа-канал 100% прозрачность
            }
            
        }
    }

    return new ImageData(outputData, width, height);
}
