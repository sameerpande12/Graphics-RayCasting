import numpy as np 
import csv 

with open("image.csv",'r') as f:
    data  = list(csv.reader(f,delimiter=','))

data = np.array(data,dtype=np.uint8)
data = data[0]
unique_values = np.unique(data)

data = data.reshape(640,640,3)

# for i in range (320):
#     for j in range (100):
#         data[i][j][0]=255
#         data[i][j][1]=0
#         data[i][j][2]=0

from PIL import Image 
image = Image.fromarray(data,'RGB')
image.save("ok.png")
image.show()