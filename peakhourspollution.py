# -*- coding: utf-8 -*-
"""
Created on Sun Mar 31 11:18:08 2019

@author: Punit
"""

import matplotlib.pyplot as plt
import pandas as pd
import csv


x = []
y = []
t = []
n=0
with open('C:\\Users\\Punit\\Desktop\\peakhourspollutions.csv') as csvfile:
    plots = csv.reader(csvfile , delimiter=',')
    for row in plots:
        if(n==0):
            n = n+1
            continue
        else :
            x.append(row[7])
            y.append(row[8])
            t.append(row[0])
m = []
n = []
for i in x:
    m.append(int(i))
    
for i in y:
    n.append(int(i))
    
print(m)
print(n)

df1 = pd.DataFrame({ 'high' : m , 'low' : n}, index= t)

lines = df1.plot.line()

    
    