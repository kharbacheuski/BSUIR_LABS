import cv from "@techstark/opencv-js"

const uploadInput = document.getElementById('upload');
const canvas = document.getElementById('canvas') as HTMLCanvasElement;
const ctx = canvas.getContext('2d');

// Обработчик для загрузки изображения
uploadInput.addEventListener('change', (event: any) => {
    const file = event.target.files[0] ;
    if (file) {
        const img = new Image();
        img.src = URL.createObjectURL(file);
        img.onload = function() {
            canvas.width = img.width;
            canvas.height = img.height;
            ctx.drawImage(img, 0, 0, img.width, img.height);
            processImage(img);
        };
    }
});

// Функция обработки изображения с использованием OpenCV.js
function processImageStrong(image) {
    // Ждем загрузки OpenCV
 
    let src = cv.imread(canvas);  // Чтение изображения с canvas
    let gray = new cv.Mat();      // Матрица для серого изображения
    let blurred = new cv.Mat();   // Матрица для размытого изображения
    let edges = new cv.Mat();     // Матрица для контуров

    // Преобразование в оттенки серого
    cv.cvtColor(src, gray, cv.COLOR_RGBA2GRAY, 0);

    // Применение размытия для сглаживания изображения (чтобы контуры были мягче)
    cv.GaussianBlur(gray, blurred, new cv.Size(5, 5), 0);

    // Применение оператора Canny для выделения контуров с более мягкими порогами
    const lowThreshold = 100;  // Более низкий порог
    const highThreshold = 200; // Более высокий порог
    cv.Canny(blurred, edges, lowThreshold, highThreshold, 3, false);

    // Вывод контуров на canvas
    cv.imshow('canvas', edges);

    // Освобождение ресурсов
    src.delete();
    gray.delete();
    blurred.delete();
    edges.delete();
}

function processImage(image) {
    let src = cv.imread(canvas);  // Чтение изображения с canvas
    let gray = new cv.Mat();      // Матрица для серого изображения
    let edges = new cv.Mat();     // Матрица для контуров

    // Преобразование в оттенки серого
    cv.cvtColor(src, gray, cv.COLOR_RGBA2GRAY, 0);

    // Применение алгоритма Canny для выделения контуров
    cv.Canny(gray, edges, 150, 250, 3, false);

    // Вывод контуров на canvas
    cv.imshow('canvas', edges);

    // Освобождение ресурсов
    src.delete();
    gray.delete();
    edges.delete();
}