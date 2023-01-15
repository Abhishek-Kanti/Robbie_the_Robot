import cv2
import math
import time
import serial
import numpy as np
from cvzone.ClassificationModule import Classifier
from cvzone.HandTrackingModule import HandDetector

ser = serial.Serial(port="COM6", baudrate=9600, timeout=1)

cap = cv2.VideoCapture(0)
cap.set(3,1920)
cap.set(4,1080)
detector = HandDetector(maxHands=1)
classifier = Classifier("ML_Model3/keras_model.h5", "ML_Model3/labels.txt")

offset = 20
imgSize = 300
count = 0

folder = "Data/stop"
labels = ["Forward", "Backward", "Right", "Left", "Stop"]

while True:
    success, img = cap.read()
    ImgOutput = img.copy()
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
            prediction, index = classifier.getPrediction(imgWhite)

            if index == 0:
                ser.write("f".encode())
                print(ser.readline().decode('utf-8'))
                # time.sleep(0.5)
            elif index == 1:
                ser.write("b".encode())
                print(ser.readline().decode('utf-8'))
                #time.sleep(0.5)
            elif index == 2:
                ser.write("l".encode())
                print(ser.readline().decode('utf-8'))
                #time.sleep(0.5)
            elif index == 3:
                ser.write("r".encode())
                print(ser.readline().decode('utf-8'))
                #time.sleep(0.5)
            elif index == 4:
                ser.write("s".encode())
                print(ser.readline().decode('utf-8'))
                #time.sleep(0.5)
            else:
                ser.write("s".encode())
                print(ser.readline().decode('utf-8'))
                #time.sleep(0.5)

        else:
            k = imgSize / w
            heightCal = math.ceil(h * k)
            heightGap = math.ceil((imgSize - heightCal) / 2)
            imgResize = cv2.resize(imgCrop, (imgSize, heightCal))
            imgResizeShape = imgResize.shape
            imgWhite[heightGap:heightCal + heightGap, :] = imgResize
            prediction, index = classifier.getPrediction(imgWhite)

            if index == 0:
                ser.write("f".encode())
                print(ser.readline().decode('utf-8'))
                # time.sleep(0.5)
            elif index == 1:
                ser.write("b".encode())
                print(ser.readline().decode('utf-8'))
                # time.sleep(0.5)
            elif index == 2:
                ser.write("l".encode())
                print(ser.readline().decode('utf-8'))
                # time.sleep(0.5)
            elif index == 3:
                ser.write("r".encode())
                print(ser.readline().decode('utf-8'))
                # time.sleep(0.5)
            elif index == 4:
                ser.write("s".encode())
                print(ser.readline().decode('utf-8'))
                # time.sleep(0.5)
            else:
                ser.write("s".encode())
                print(ser.readline().decode('utf-8'))
                # time.sleep(0.5)

        cv2.putText(ImgOutput, labels[index], (x,y-20), cv2.FONT_HERSHEY_COMPLEX,2,(255,0,255),2)
        cv2.imshow("imgCrop", imgCrop)
        cv2.imshow("imgWhite", imgWhite)

    cv2.imshow("video", ImgOutput)
    cv2.waitKey(1)
ser.close()

