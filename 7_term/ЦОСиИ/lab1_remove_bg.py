import cv2
from utils import remove_bright_background

# Шаг 1: Загрузка изображения
image = cv2.imread('./images/1.jpg')
remove_bright_background(image)

# Изменение размера результата для отображения
resize_width = 1000  # Ширина для изменения размера
aspect_ratio = resize_width / image.shape[1]
new_height = int(image.shape[0] * aspect_ratio)
resized_result = cv2.resize(image, (resize_width, new_height))

# Сохранение результата
cv2.imwrite('image-without-bg.jpg', resized_result)

# Отображение результата
cv2.imshow('Without bg', resized_result)
cv2.waitKey(0)
cv2.destroyAllWindows()