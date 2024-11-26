import cv2
import numpy as np

def remove_background(image, lower_bound, upper_bound):
    hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv_image, lower_bound, upper_bound)

    # Морфологические преобразования для очистки маски
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))
    morphed_mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
    morphed_mask = cv2.morphologyEx(morphed_mask, cv2.MORPH_CLOSE, kernel)

    # Применение маски для удаления фона
    no_background = cv2.bitwise_and(image, image, mask=morphed_mask)

    return no_background, morphed_mask


def rotate_and_place_numbers(no_background, mask, min_area=15000.0):
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Фильтрация контуров по площади
    filtered_contours = [contour for contour in contours if cv2.contourArea(contour) > min_area]

    if not filtered_contours:
        raise ValueError("No valid contours detected.")

    # Создаем пустое изображение для результата
    rotated_result = np.zeros_like(no_background)

    for contour in filtered_contours:
        min_rect = cv2.minAreaRect(contour)
        angle = min_rect[2]
        size = min_rect[1]

        # Учет ориентации
        if size[0] > size[1]:
            angle += 90
            size = (size[1], size[0])

        # Поворот изображения
        rotation_matrix = cv2.getRotationMatrix2D(min_rect[0], angle, 1.0)
        rotated_image = cv2.warpAffine(no_background, rotation_matrix, (no_background.shape[1], no_background.shape[0]))

        # Обрезка
        center = tuple(map(int, min_rect[0]))
        width, height = map(int, size)
        x, y = center[0] - width // 2, center[1] - height // 2
        bounding_box = (max(0, x), max(0, y), min(rotated_image.shape[1], width), min(rotated_image.shape[0], height))
        digit = rotated_image[bounding_box[1]:bounding_box[1] + bounding_box[3],
                              bounding_box[0]:bounding_box[0] + bounding_box[2]]

        # Добавление цифры на чистое изображение
        if digit.size > 0:
            rotated_result[bounding_box[1]:bounding_box[1] + bounding_box[3],
                           bounding_box[0]:bounding_box[0] + bounding_box[2]] = digit

    return rotated_result


def process_image(image_path, output_path):
    # Загрузка изображения
    src_image = cv2.imread(image_path)
    if src_image is None:
        raise ValueError("Invalid image file.")

    # Диапазон цвета для удаления фона (зеленый)
    lower_green = np.array([40, 140, 140])
    upper_green = np.array([90, 255, 255])

    # Удаление фона
    no_background, mask = remove_background(src_image, lower_green, upper_green)

    # Поворот и размещение цифр
    rotated_result = rotate_and_place_numbers(no_background, mask)

    # Сохранение результата
    cv2.imwrite(output_path, rotated_result)


if __name__ == "__main__":
    # Пример использования
    input_image = "./images/2.jpg"  # Замените на путь к вашему изображению
    output_image = "output_image_rotated.jpg"  # Замените на путь для сохранения результата

    try:
        process_image(input_image, output_image)
        print(f"Processed image saved to {output_image}")
    except ValueError as e:
        print(f"Error: {e}")
