import cv from "@techstark/opencv-js"

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
        // ctx.drawImage(img, 0, 0);

        const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);

        findContours(canvas);
    };

    reader.readAsDataURL(file);
}

function findContours(canvas) {
    // Читаем изображение в OpenCV
    let src = cv.imread(canvas);
    let gray = new cv.Mat();
    let edges = new cv.Mat();

    // Преобразуем в градации серого
    cv.cvtColor(src, gray, cv.COLOR_RGBA2GRAY);

    // Применяем оператор Собеля
    cv.Sobel(gray, edges, cv.CV_8U, 1, 1, 3, 1, 0, cv.BORDER_DEFAULT);

    // Находим контуры
    let contours = new cv.MatVector();
    let hierarchy = new cv.Mat();
    cv.findContours(edges, contours, hierarchy, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE);

    // Создаем пустую маску для рисования контуров
    let output = cv.Mat.zeros(src.rows, src.cols, cv.CV_8UC3);
    for (let i = 0; i < contours.size(); ++i) {
        cv.drawContours(output, contours, i, new cv.Scalar(255, 255, 255), 1);
    }

    // Отображаем результат
    cv.imshow(canvas, output);

    // Освобождаем память
    src.delete();
    gray.delete();
    edges.delete();
    contours.delete();
    hierarchy.delete();
    output.delete();
}