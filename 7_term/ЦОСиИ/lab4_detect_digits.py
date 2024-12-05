import cv2
import numpy as np
import os

def preprocess_image(image_path):
    image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    _, image = cv2.threshold(image, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

    return image

def generate_template(digit, size):
    # Создаём изображение шаблона с заданной цифрой
    template = np.zeros((size, size), dtype=np.uint8)
    font_scale = size / 25  # Подбор масштаба текста
    thickness = max(1, size // 8)  # Подбор толщины
    text_size = cv2.getTextSize(str(digit), cv2.FONT_HERSHEY_SIMPLEX, font_scale, thickness)[0]
    text_x = (size - text_size[0]) // 2
    text_y = (size + text_size[1]) // 2
    cv2.putText(template, str(digit), (text_x, text_y), cv2.FONT_HERSHEY_SIMPLEX, font_scale, 255, thickness)

    # Обрезаем шаблон по цифре (удаляем фон)
    _, th_template = cv2.threshold(template, 1, 255, cv2.THRESH_BINARY)
    x, y, w, h = cv2.boundingRect(th_template)
    cropped_template = th_template[y:y+h, x:x+w]
    
    # Поиск контуров в cropped_template
    contours, _ = cv2.findContours(cropped_template, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Нарисовать контуры на новом изображении (если нужно)
    contour_image = np.zeros_like(cropped_template)
    cv2.drawContours(contour_image, contours, -1, 255)  # Толщина контуров = 2

    return contour_image

def recognize_digit(cropped_contour, templates):
    # Приведение контура под размер шаблона
    h_c, w_c = cropped_contour.shape

    # Создаем перевернутую версию контура
    flipped_contour = cv2.flip(cropped_contour, 0)
    flipped_contour2 = cv2.flip(cropped_contour, -1)

    # Сравнение с оригиналом и перевернутым контуром
    best_match = None
    best_corr = -1

    for digit, template in templates:
        # Масштабируем шаблон под размеры контура
        template_resized = cv2.resize(template, (w_c, h_c))

        # Сравнение с оригиналом и перевернутым контуром
        correlation_original = cv2.matchTemplate(cropped_contour, template_resized, cv2.TM_CCOEFF_NORMED)
        correlation_flipped = cv2.matchTemplate(flipped_contour, template_resized, cv2.TM_CCOEFF_NORMED)
        correlation_flipped2 = cv2.matchTemplate(flipped_contour2, template_resized, cv2.TM_CCOEFF_NORMED)

        # Ищем наибольшую корреляцию из двух
        best_match_for_digit = None
        best_corr_for_digit = -1

        for corr_value in np.concatenate([correlation_original.flatten(), correlation_flipped.flatten(), correlation_flipped2.flatten()]):
            if corr_value > best_corr_for_digit:
                best_corr_for_digit = corr_value
                best_match_for_digit = digit

        if best_corr_for_digit > best_corr:
            best_corr = best_corr_for_digit
            best_match = best_match_for_digit

    return best_match

def main(image_path):
    # # Проверка и создание папок для шаблонов и контуров
    # if not os.path.exists("digits"):
    #     os.makedirs("digits")
    # if not os.path.exists("contours"):
    #     os.makedirs("contours")

    # Предобработка изображения
    thresh = preprocess_image(image_path)

    contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    recognized_digits = []

    for i, contour in enumerate(contours):
        if cv2.contourArea(contour) < 50:
            continue
        
        # Обрезка фона и сохранение
        contour_image = np.zeros_like(thresh)
        cv2.drawContours(contour_image, [contour], -1, 255)
        _, th_contour = cv2.threshold(contour_image, 1, 255, cv2.THRESH_BINARY)
        x, y, w, h = cv2.boundingRect(th_contour)
        cropped_contour = th_contour[y:y+h, x:x+w]

        # # Сохраняем обрезанный контур
        # cropped_contour_filename = f"contours/cropped_contour_{i}.png"
        # cv2.imwrite(cropped_contour_filename, cropped_contour)

        max_dim = max(w, h)

        templates = [(digit, generate_template(digit, max_dim)) for digit in range(10)]

        # for digit, template in templates:
        #     template_filename = f"digits/template_{digit}.png"
        #     cv2.imwrite(template_filename, template)

        # Распознаём цифру
        digit = recognize_digit(cropped_contour, templates)
        recognized_digits.append(digit)

    print("Распознанные цифры:", " ".join(map(str, recognized_digits)))

if __name__ == "__main__":
    image_path = "output_image_rotated.jpg"  # Укажите путь к изображению
    main(image_path)
