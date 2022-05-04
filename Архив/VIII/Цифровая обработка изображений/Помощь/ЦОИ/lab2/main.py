import cv2 as cv
import numpy as np
import sys

filename = sys.argv[1]
min_dis = int(sys.argv[2])
min_rad = int(sys.argv[3])
max_rad = int(sys.argv[4])

image = cv.imread(filename)
cv.imshow("Original image", image)
gray = cv.cvtColor(image, cv.COLOR_BGR2GRAY)
cv.imshow("Gray image", gray)
gray = cv.medianBlur(gray, 5)
cv.imshow("Blurred gray image", gray)

circles = cv.HoughCircles(gray, cv.HOUGH_GRADIENT, 1.7,
                           param1=80, param2=57, minDist=min_dis,
                           minRadius=min_rad, maxRadius=max_rad)
if circles is not None:
    circles = np.round(circles[0, :]).astype("int")
    for (x, y, r) in circles:
        cv.circle(image, (x, y), r, (0, 255, 0), 4)
        cv.rectangle(image, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)
cv.imshow("Circles", image)
cv.imwrite('result.bmp', image)
cv.waitKey(0)
