import pandas as pd
import numpy as np

#순서: 이름, 위도, 경도, Rubbish,Plastics,Cans,Glass,Papers
trash_df=pd.read_csv("Data.csv")
region_df=pd.read_csv("RegionInfo.csv")

region=[]
trash_df_row=trash_df.shape[0]
cnt=0

coordinate_info=pd.read_csv("coordinate_info.csv")
np_info=coordinate_info.to_numpy()

cols_divide=50
rows_divide=70


trash_np=trash_df.to_numpy()
region_np=region_df.to_numpy()
region_lat=region_np[:,1]
region_lon=region_np[:,2]

def duplicate_drop(arr):
    result=[]
    for value in arr:
        if value not in result:
            result.append(value)
    return result

region_lat=duplicate_drop(region_lat)
region_lon=duplicate_drop(region_lon)

East=np_info[3,0]+region_lat[0]-region_lat[1]
South=np_info[0,0]-(region_lon[1]-region_lon[0])


region_lat_append=np.append(region_lat, South)
region_lon_append=np.append(region_lon, East)


for lat in range(len(region_lat)):
    for lon in range(len(region_lon)):
        temp=[]
        for i in range(trash_df_row):
                if((trash_np[i,1]<=region_lat_append[lat])&(trash_np[i,1]>region_lat_append[lat+1])
                    &((trash_np[i,2])>=region_lon_append[lon])&((trash_np[i,2])<region_lon_append[lon+1])):
                    temp.append(trash_np[i,:])
                else:
                    temp.append([0,0,0,0,0,0,0,0])
        region.append(temp)


region_np=np.array(region)
print(region_np)
region_sum=np.sum(region_np, axis=1)
region_sum_pd=pd.DataFrame(region_sum)

region_sum_pd_drop=region_sum_pd.drop([0,1,2], axis=1)
region_sum_pd_drop.to_csv("SumOfRubbish.csv")
