import cv2 as cv
import math
import sys

def crop_around_center(image, width, height):
    image_size = (image.shape[1], image.shape[0])
    image_center = (int(image_size[0] * 0.5), int(image_size[1] * 0.5))
    if width > image_size[0]:
        width = image_size[0]
    if height > image_size[1]:
        height = image_size[1]
    x1 = int(image_center[0] - width * 0.5)
    x2 = int(image_center[0] + width * 0.5)
    y1 = int(image_center[1] - height * 0.5)
    y2 = int(image_center[1] + height * 0.5)
    return image[y1:y2, x1:x2]


def largest_rotated_rect(w, h, angle):
    quadrant = int(math.floor(angle / (math.pi / 2))) & 3
    sign_alpha = angle if ((quadrant & 1) == 0) else math.pi - angle
    alpha = (sign_alpha % math.pi + math.pi) % math.pi

    bb_w = w * math.cos(alpha) + h * math.sin(alpha)
    bb_h = w * math.sin(alpha) + h * math.cos(alpha)

    gamma = math.atan2(bb_w, bb_w) if (w < h) else math.atan2(bb_w, bb_w)

    delta = math.pi - alpha - gamma

    length = h if (w < h) else w

    d = length * math.cos(alpha)
    a = d * math.sin(alpha) / math.sin(delta)

    y = a * math.cos(gamma)
    x = y * math.tan(gamma)

    return (bb_w - 2 * x, bb_h - 2 * y)


def func(interpol):
    return {
        0: cv.INTER_NEAREST,
        1: cv.INTER_LINEAR,
        2: cv.INTER_CUBIC
    }[interpol]


filename = sys.argv[1]
alpha = int(sys.argv[2])
k = float(sys.argv[3])
interpol = int(sys.argv[4])

original_image = cv.imread(filename)
cv.imshow('Original image', original_image)

(rows, cols) = original_image.shape[:2]
M = cv.getRotationMatrix2D(((cols - 1) / 2.0, (rows - 1) / 2.0), alpha, 1)
rotated_image = cv.warpAffine(original_image, M, (cols, rows))
cv.imshow('Rotated image', rotated_image)

cropped_image = crop_around_center(rotated_image, *largest_rotated_rect(cols, rows, math.radians(alpha)))
cv.imshow('Cropped image', cropped_image)

resized_image = cv.resize(cropped_image, None, fx=k, fy=1.0/k, interpolation=func(interpol))
cv.imshow('Resized image', resized_image)
cv.imwrite('result.bmp', resized_image)
cv.waitKey(0)