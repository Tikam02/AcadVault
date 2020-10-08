import matplotlib.pyplot as plt
import cv2

# Read an image
img = cv2.imread('image.jpeg')

# Display an image
plt.imshow(img)

# Write image with another name
cv2.imwrite('image2.jpeg', img)

# Display information of the image
