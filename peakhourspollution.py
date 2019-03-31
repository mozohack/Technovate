import matplotlib.pyplot as plt
import pandas as pd
import csv


x = []
y = []
t = []
n=0
with open('peakhourspollutions.csv') as csvfile:
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
    

df1 = pd.DataFrame({ 'high' : m , 'low' : n}, index= t)

lines = df1.plot.line()

lines.set_xlabel("Peak hours pollution visualisation")
lines.set_ylabel("Atmospheric PPM")

fig = lines.get_figure()
fig.savefig("peakhourspollution.jpg")
