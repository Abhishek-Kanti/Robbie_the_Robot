import cv2
import math
import time
import numpy as np
from cvzone.HandTrackingModule import HandDetector

cap = cv2.VideoCapture(0)
cap.set(3,1920)
cap.set(4,1080)

detector = HandDetector(maxHands=1)
offset = 20
imgSize = 300
count = 0

folder = "Data/stop"

while True:
    success, img = cap.read()
    hands, img = detector.findHands(img)
    if hands:
        hand = hands[0]
        x, y, w, h = hand['bbox']

        imgWhite = np.ones((imgSize, imgSize, 3), np.uint8)*255
        imgCrop = img[y-offset:y+h+offset, x-offset:x+w+offset]
        imgCropShape = imgCrop.shape

        aspectRatio = h/w

        if aspectRatio > 1:
            k = imgSize/h
            widthCal = math.ceil(w * k)
            widthGap = math.ceil((imgSize-widthCal)/2)
            imgResize = cv2.resize(imgCrop, (widthCal, imgSize))
            imgResizeShape = imgResize.shape
            imgWhite[:, widthGap:widthCal + widthGap] = imgResize

        else:
            k = imgSize / w
            heightCal = math.ceil(h * k)
            heightGap = math.ceil((imgSize - heightCal) / 2)
            imgResize = cv2.resize(imgCrop, (imgSize, heightCal))
            imgResizeShape = imgResize.shape
            imgWhite[heightGap:heightCal + heightGap, :] = imgResize

        cv2.imshow("imgCrop", imgCrop)
        cv2.imshow("imgWhite", imgWhite)

    cv2.imshow("video",img)
    key = cv2.waitKey(1)

    if key == ord("s"):
        count += 1
        cv2.imwrite(f'{folder}/Image_{time.time()}.jpg', imgWhite)
        print(count)
