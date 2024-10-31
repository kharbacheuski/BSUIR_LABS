import cv2
import numpy as np
import random
from sklearn.cluster import KMeans

def is_pixel_bright(pixel, accuracy=0.6):
    pixel = pixel.astype(float)
    avg = (pixel[0] + pixel[1] + pixel[2]) / 3

    if avg == 0:
        return False

    if (abs((avg - pixel[0]) / avg) > accuracy or
        abs((avg - pixel[1]) / avg) > accuracy or
        abs((avg - pixel[2]) / avg) > accuracy):
        return True

    return False

def remove_bright_background(image, accuracy=0.6):
    # Get the dimensions of the image
    height, width, _ = image.shape

    # Process each pixel
    for y in range(height):
        for x in range(width):
            pixel = image[y, x]

            # If the pixel is bright, set its alpha to 0 (transparent)
            if not is_pixel_bright(pixel, accuracy):  # Only check RGB channels
                image[y, x] = [0, 0, 0]  # Set to transparent black

    return image

def manual_area_calculation(contour): # contour - Список координат вершин (пикселей) контура. 
    # Сумма площади по формуле
    area = 0
    for i in range(len(contour)):
        x1, y1 = contour[i][0]
        x2, y2 = contour[(i + 1) % len(contour)][0]  # следующая точка
        area += (x1 * y2) - (x2 * y1) # формула Гаусса
    
    return abs(area) / 2  # Возвращаем абсолютное значение площади

# Шаг 1: Загрузка изображения
image = cv2.imread('./images/1.jpg')
remove_bright_background(image)

# Шаг 2: Преобразование изображения в оттенки серого
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Шаг 3: Применение гауссового размытия
blurred = cv2.GaussianBlur(gray, (7, 7), 0)

# Шаг 4: Затем бинаризация
_, binary = cv2.threshold(blurred, 75, 150, cv2.THRESH_BINARY)

# Шаг 5: Применение морфологических операций
kernel = np.ones((15, 15), np.uint8)
eroded = cv2.erode(binary, kernel, iterations=5)   # Сужаем, чтобы уменьшить шум
dilated = cv2.dilate(eroded, kernel, iterations=2)  # Расширяем, чтобы отделить фигуры

# Шаг 6: Обнаружение контуров
contours, _ = cv2.findContours(dilated, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Шаг 7: Создание пустого цветного изображения для рисования раскрашенных фигур
colored_result = np.zeros_like(image)

# Шаг 8: Рисование контуров на новом изображении с случайными цветами
for i, contour in enumerate(contours):
    # Генерация случайного цвета в формате BGR
    color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
    # Рисование фигуры с заполнением
    cv2.drawContours(colored_result, [contour], -1, color, thickness=cv2.FILLED)

    # Вычисление площади и периметра
    area = manual_area_calculation(contour)  # Используем нашу функцию для вычисления площади
    perimeter = cv2.arcLength(contour, True)

    # Вывод площади и периметра в консоль
    print(f'Фигура {i + 1}: площадь = {area:.2f}, периметр = {perimeter:.2f}')

# Изменение размера результата для отображения
resize_width = 1000  # Ширина для изменения размера
aspect_ratio = resize_width / colored_result.shape[1]
new_height = int(colored_result.shape[0] * aspect_ratio)
resized_result = cv2.resize(colored_result, (resize_width, new_height))

# Сохранение результата
cv2.imwrite('colored_figures_with_metrics.jpg', resized_result)

# Отображение результата
cv2.imshow('Colored Figures', resized_result)
cv2.waitKey(0)
cv2.destroyAllWindows()