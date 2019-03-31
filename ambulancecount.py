# -*- coding: utf-8 -*-
"""
Created on Sun Mar 31 12:46:37 2019

@author: Punit
"""

import matplotlib.pyplot as plt
import pandas as pd
import csv

w = []
x = []
y = []
z = []
t = []

n=0
with open('C:\\Users\\Punit\\Desktop\\ambulancecount.csv') as csvfile:
    plots = csv.reader(csvfile , delimiter=',')
    for row in plots:
        if(n==0):
            n = n+1
            continue
        else :
            w.append(row[1])
            x.append(row[2])
            y.append(row[3])
            z.append(row[4])
            t.append(row[0])

print(t)

lenx = len(x)
lenx = len(y)


m = 0
n=0 
p=0
q=0

o =['Lane1','Lane2','Lane3','Lane4']



count = 0
for i in w:
    if(count == lenx-1):
     m = int(i)
     
     break
    else:
        count = count+1
  
count = 0      
for i in x:
    if(count == lenx-1):
     n = int(i)
     
     break
    else:
        count = count+1
    
count = 0
for i in y:
    if(count == lenx-1):
     p =int(i)
     break
    else:
         count = count+1
 
count = 0       
for i in z:
    if(count == lenx-1):
      q= int(i)
      break
    else:
      count = count+1


    
lane = [m,n,p,q]

print(lane)

df1 = pd.DataFrame({'Count':lane,'Lanes':o})

lines = df1.plot.bar()