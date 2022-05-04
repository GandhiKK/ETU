import cv2
import numpy as np
import sys

filename = sys.argv[1]
k = int(sys.argv[2])
image = cv2.imread(filename)
cv2.imshow("Original image", image)
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 10, 1.0)
ret, label, center = cv2.kmeans(np.float32(image.reshape((-1, 3))), k, None, criteria, 10, cv2.KMEANS_RANDOM_CENTERS)
center = np.uint8(center)
clusters = center[label.flatten()].reshape((image.shape))
cv2.imshow('Clusters', clusters)
cv2.imwrite('result.bmp', image)
cv2.waitKey(0)