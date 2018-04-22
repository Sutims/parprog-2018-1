import array
import struct
import cv2 as cv
import numpy as np
from config import *

def read_binary(time = False, name = binary_output_default):
    fin = open(name, "rb")
    w = struct.unpack('i', fin.read(4))[0] # read an int width 
    h = struct.unpack('i', fin.read(4))[0] # read an int height
    t = 0.0
    if time:
        t = struct.unpack('<d', fin.read(8))[0] # read time

    values = array.array('d')
    values.read(fin, w * h * 3)

    blank_image = np.zeros((h,w,3), np.uint8)
    for y in range(0, h):
        for x in range(0, w):
            blank_image[y, x, 0] = values[y * w * 3 + x * 3] # read R
            blank_image[y, x, 1] = values[y * w * 3 + x * 3 + 1] # read G
            blank_image[y, x, 2] = values[y * w * 3 + x * 3 + 2] # read B
    return blank_image, t

def main():
    cv.imshow('image', read_binary(True)[0])
    cv.waitKey(0)

if __name__ == "__main__":
    main()
