import cv from '@techstark/opencv-js';

const upload = document.getElementById('upload');
const canvas = document.getElementById('canvas') as HTMLCanvasElement;
const ctx = canvas.getContext('2d');

cv.onRuntimeInitialized = () => {
    upload.addEventListener('change', (event: any) => {
        const file = event.target.files[0];

        if (!file) return;

        const reader = new FileReader();
        const img = new Image();

        reader.onload = function(e) {
            img.src = e.target.result as string;
        };

        img.onload = () => {
            // Настройка canvas
            canvas.width = img.width;
            canvas.height = img.height;
            ctx.drawImage(img, 0, 0);

            processImage(img);
        };
        
        reader.readAsDataURL(file);
    });
}

function processImage(img) {
    const src = cv.imread(img);
    const dst = new cv.Mat();

    // Разделите изображение на каналы
    const channels = new cv.MatVector();
    cv.split(src, channels);

    // Настройки цветовых масок
    const r_min = new cv.Mat(src.rows, src.cols, cv.CV_8U, new cv.Scalar(0));
    const r_max = new cv.Mat(src.rows, src.cols, cv.CV_8U, new cv.Scalar(255));
    const g_min = new cv.Mat(src.rows, src.cols, cv.CV_8U, new cv.Scalar(0));
    const g_max = new cv.Mat(src.rows, src.cols, cv.CV_8U, new cv.Scalar(255));
    const b_min = new cv.Mat(src.rows, src.cols, cv.CV_8U, new cv.Scalar(0));
    const b_max = new cv.Mat(src.rows, src.cols, cv.CV_8U, new cv.Scalar(255));

    const r_mask = new cv.Mat();
    const g_mask = new cv.Mat();
    const b_mask = new cv.Mat();

    // Проверка масок
    cv.inRange(channels.get(2), r_min, r_max, r_mask);
    cv.inRange(channels.get(1), g_min, g_max, g_mask);
    cv.inRange(channels.get(0), b_min, b_max, b_mask);

    // Отладка: показ масок
    const debugMask = new cv.Mat();
    cv.bitwise_or(r_mask, g_mask, debugMask);
    cv.bitwise_or(debugMask, b_mask, debugMask);
    cv.imshow(canvas, debugMask); // Показать маски

    // Фильтрация
    const r_filtered = new cv.Mat();
    const g_filtered = new cv.Mat();
    const b_filtered = new cv.Mat();

    cv.bitwise_and(channels.get(2), channels.get(2), r_filtered, r_mask);
    cv.bitwise_and(channels.get(1), channels.get(1), g_filtered, g_mask);
    cv.bitwise_and(channels.get(0), channels.get(0), b_filtered, b_mask);

    // Объединение отфильтрованных каналов
    const newChannels = new cv.MatVector();
    newChannels.push_back(b_filtered);
    newChannels.push_back(g_filtered);
    newChannels.push_back(r_filtered);

    const filtered_image = new cv.Mat();
    cv.merge(newChannels, filtered_image);

    // Преобразование в серый цвет
    const gray = new cv.Mat();
    cv.cvtColor(filtered_image, gray, cv.COLOR_BGR2GRAY);

    // Размытие
    const blur = new cv.Mat();
    cv.GaussianBlur(gray, blur, new cv.Size(9, 9), 0);

    // Поиск контуров
    const contours = new cv.MatVector();
    const hierarchy = new cv.Mat();
    cv.findContours(blur, contours, hierarchy, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE);

    // Фильтрация контуров
    const result = cv.Mat.zeros(src.rows, src.cols, cv.CV_8UC3);
    const filteredContours = [];

    for (let i = 0; i < contours.size(); i++) {
        const contour = contours.get(i);
        const perimeter = cv.arcLength(contour, true);
        if (perimeter > 200) {
            const area = cv.contourArea(contour);
            if (area > 10000 && area < 640000) {
                cv.drawContours(result, contours, i, new cv.Scalar(0, 255, 0), 4);
                filteredContours.push(contour);
            }
        }
    }

    // Отображение результата
    cv.imshow(canvas, result);

    // Освобождение ресурсов
    src.delete();
    dst.delete();
    r_min.delete();
    r_max.delete();
    g_min.delete();
    g_max.delete();
    b_min.delete();
    b_max.delete();
    r_mask.delete();
    g_mask.delete();
    b_mask.delete();
    r_filtered.delete();
    g_filtered.delete();
    b_filtered.delete();
    filtered_image.delete();
    gray.delete();
    blur.delete();
    result.delete();
    for (let i = 0; i < contours.size(); i++) {
        contours.get(i).delete();
    }
    contours.delete();
    hierarchy.delete();
}