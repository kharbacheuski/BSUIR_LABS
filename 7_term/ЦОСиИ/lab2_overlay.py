import cv2
import numpy as np
import random
from sklearn.cluster import KMeans
from utils import remove_bright_background

def manual_area_calculation(contour):
    area = 0
    for i in range(len(contour)):
        x1, y1 = contour[i][0]
        x2, y2 = contour[(i + 1) % len(contour)][0]
        area += (x1 * y2) - (x2 * y1)
    return abs(area) / 2

def manual_perimeter_calculation(contour):
    perimeter = 0
    for i in range(len(contour)):
        x1, y1 = contour[i][0]
        x2, y2 = contour[(i + 1) % len(contour)][0]
        perimeter += np.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)  # Расстояние между двумя точками
    return perimeter

# Загрузка изображения
image = cv2.imread('./images/1.jpg')
remove_bright_background(image)

# Преобразование изображения в оттенки серого
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Применение гауссового размытия
blurred = cv2.GaussianBlur(gray, (7, 7), 0)

# Бинаризация
_, binary = cv2.threshold(blurred, 75, 150, cv2.THRESH_BINARY)

# Морфологические операции
kernel = np.ones((15, 15), np.uint8)
eroded = cv2.erode(binary, kernel, iterations=5)
dilated = cv2.dilate(eroded, kernel, iterations=2)

# Обнаружение контуров
contours, _ = cv2.findContours(dilated, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# Вычисление площадей и кластеризация
areas = [manual_area_calculation(contour) for contour in contours]
n_clusters = 3  # Количество кластеров
kmeans = KMeans(n_clusters=n_clusters, random_state=0)
labels = kmeans.fit_predict(np.array(areas).reshape(-1, 1), )

# Генерация случайных цветов для каждого кластера
cluster_colors = {i: (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)) for i in range(n_clusters)}

# Создание пустого изображения для рисования фигур
colored_result = np.zeros_like(image)

# Рисование контуров с цветами на основе кластеров
for i, contour in enumerate(contours):
    color = cluster_colors[labels[i]]
    cv2.drawContours(colored_result, [contour], -1, color, thickness=cv2.FILLED)

    # Вычисление площади и периметра
    area = areas[i]
    perimeter = manual_perimeter_calculation(contour)  # Используем свой алгоритм
    print(f'Фигура {i + 1}: площадь = {area:.2f}, периметр = {perimeter:.2f}')

# Изменение размера результата для отображения
resize_width = 1000
aspect_ratio = resize_width / colored_result.shape[1]
new_height = int(colored_result.shape[0] * aspect_ratio)
resized_result = cv2.resize(colored_result, (resize_width, new_height))

# Сохранение и отображение результата
cv2.imwrite('colored_figures.jpg', resized_result)
cv2.imshow('Colored Figures', resized_result)
cv2.waitKey(0)
cv2.destroyAllWindows()