from cv2 import imread, imshow, waitKey

IMG_PATH = "./download.jpeg"

# Reading an image
img = imread(IMG_PATH)

# Displaying an image
imshow('img', img)

waitKey(5)
# Writing an image with another name
with open('img2.jpg', 'w') as f:
    f.write(str(img))

print(img)

