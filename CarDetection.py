import libraries of python opencv
from skimage.measure import compare_ssim
import argparse
import imutils
import cv2
import numpy as np
import time

from firebase import firebase

firebase = firebase.FirebaseApplication('https://traffic-managment.firebaseio.com/',None)

#create VideoCapture object and read from video file
cap = cv2.VideoCapture('cars.mp4')
#use trained cars XML classifiers
#car_cascade = cv2.CascadeClassifier('cars.xml')
count = 0
#read until video is completed
t1 = time.time()
while True:
    #capture frame by frame
    ret, frame = cap.read()
    #convert video into gray scale of each frames
#    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
#
#    #detect cars in the video
#    cars = car_cascade.detectMultiScale(gray, 1.1, 3)
#
#    #to draw arectangle in each cars 
#    for (x,y,w,h) in cars:                      
#        cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)      
#        count = count+1
       # print(count)
    #display the resulting frame
    cv2.imshow('video', frame)
   # print(t)
   
    #press Q on keyboard to exit
    
    t = time.time()
    if(t > t1+5):
        print("**************************************")
        cv2.imwrite("card" + ".jpg",frame)
        imageA = cv2.imread("C:\\Users\\Punit\\Downloads\\card2.jpg")
        imageB = cv2.imread("C:\\Users\\Punit\\Downloads\\card.jpg")
         
        # convert the images to grayscale
        grayA = cv2.cvtColor(imageA, cv2.COLOR_BGR2GRAY)
        grayB = cv2.cvtColor(imageB, cv2.COLOR_BGR2GRAY)
        
        
        
        # compute the Structural Similarity Index (SSIM) between the two
        # images, ensuring that the difference image is returned
        (score, diff) = compare_ssim(grayA, grayB, full=True)
        diff = (diff * 255).astype("uint8")
        print("SSIM: {}".format(score))
        data = 100 - score*100
        result = firebase.put('Density','Lane1' , data )
        
        
        
        # threshold the difference image, followed by finding contours to
        # obtain the regions of the two input images that differ
        thresh = cv2.threshold(diff, 0, 255,
        	cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)[1]
        cnts = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
        	cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)
        t1 = time.time()
    # loop over the contours
#    for c in cnts:
#    	# compute the bounding box of the contour and then draw the
#    	# bounding box on both input images to represent where the two
#    	# images differ
#    	(x, y, w, h) = cv2.boundingRect(c)
#    	cv2.rectangle(imageA, (x, y), (x + w, y + h), (0, 0, 255), 2)
#    	cv2.rectangle(imageB, (x, y), (x + w, y + h), (0, 0, 255), 2)
#     
#    # show the output images
#    cv2.imshow("Original", imageA)
#    cv2.imshow("Modified", imageB)
#    cv2.imshow("Diff", diff)
#    cv2.imshow("Thresh", thresh)
    
    if cv2.waitKey(25) & 0xFF == ord('q'):
     break
#release the videocapture object

cap.release()
#close all the frames
cv2.destroyAllWindows()
