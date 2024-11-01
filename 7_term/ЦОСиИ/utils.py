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