import numpy as np 
import csv 

with open("image.csv",'r') as f:
    data  = list(csv.reader(f,delimiter=','))

data = np.array(data,dtype=np.uint8)
data = data[0]

data = data.reshape(640,640,3)

from PIL import Image 
image = Image.fromarray(data,'RGB')
image.save("ok.png")
image.show()