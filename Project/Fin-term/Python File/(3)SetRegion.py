import numpy
import pandas as pd
import numpy as np
coordinate_info=pd.read_csv("coordinate_info.csv")
np_info=coordinate_info.to_numpy()

East=np_info[3,0]
West=np_info[2,0]
South=np_info[0,0]
North=np_info[1,0]


#쓰레기의 가장 왼쪽과 오른쪽을 50개로 나누고,
#쓰레기의 가장 북쪽과 남쪽을 70개로 나누어
#총 3500개의 region으로 나눈다.
cols_divide=50
rows_divide=70
cols=np.linspace(West,East,num=cols_divide)
rows=np.linspace(North, South,num=rows_divide)
print(cols)
region_coordinate=[]
trash_inf0=pd.read_csv('Data.csv')
for i in range(rows_divide):
    for j in range(cols_divide):
        region_coordinate.append([rows[i], cols[j]])

region_n=[]
for i in range(rows_divide*cols_divide):
    region_n.append(i)
region_coordinate_df=pd.DataFrame(region_coordinate)
region_n_df=pd.DataFrame(region_n)
print(region_coordinate_df)
print(region_coordinate_df.shape)
region_coordinate_df.to_csv("RegionInfo.csv", index=['Longitude', 'Latitude'])


