import numpy as np
import cv2
from firebase import firebase
import time

firebase = firebase.FirebaseApplication('https://traffic-managment.firebaseio.com/',None)

car_cascade = cv2.CascadeClassifier(*****)
cap = cv2.VideoCapture(******)

t1 = time.time()
while True:
    #capture frame by frame
    ret, frame = cap.read()
    
    cv2.imshow('video', frame)
  
    
    t = time.time()
    if(t > t1+5):
      
        cv2.imwrite("card" + ".jpg",frame)
        img = cv2.imread('C:\\Users\\Punit\\Desktop\\card.jpg')
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
       
        faces = car_cascade.detectMultiScale(gray, 1.3, 5)
    
        count = 0
        for (x,y,w,h) in faces:
            
            img = cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
            count = count+1
            roi_gray = gray[y:y+h, x:x+w]
            roi_color = img[y:y+h, x:x+w]
            result = firebase.put('Density','Lane1' , count )
        
        t1 = time.time()
    
    
    if cv2.waitKey(25) & 0xFF == ord('q'):
     break




cv2.waitKey(0)
cv2.destroyAllWindows()
