import numpy as np
from PIL import Image
from PIL.ExifTags import TAGS
import pandas as pd
import glob
import numpy as np

image_list=[]
lat_info=[]
lon_info=[]
taglabel={}
file_name=[]
GPS_data=[]
width_data=[]
height_data=[]

for filename in glob.glob('*.jpg'):
    im=Image.open(filename)
    info=im._getexif();
    image_list.append(im)
    #사진의 파일 이름 저장, .jpg 제외하고 저장
    file_name.append(str(filename)[:-4])

    #사진의 크기 정보 저장
    width_data.append(im.size[0])
    height_data.append(im.size[1])

    for tag, value in info.items():
        decoded=TAGS.get(tag,tag)
        taglabel[decoded]=value
    exifGPS=taglabel['GPSInfo']
    latData=exifGPS[2]
    lonData=exifGPS[4]

    #DMS로 표현된 위경도 정보를 Degree로 변환
    latDeg = latData[0]
    latMin = latData[1]/60.0
    latSec = latData[2]/3600.0
    lonDeg = lonData[0]
    lonMin = lonData[1]/60.0
    lonSec = lonData[2]/3600.0

    Lat = (latDeg + (latMin + latSec / 60.0) / 60.0)
    if exifGPS[1] == 'S':
        Lat = Lat * -1
    Lon = (lonDeg + (lonMin + lonSec / 60.0) / 60.0)
    if exifGPS[3] == 'W':
        Lon = Lon * -1
    #위경도 정보 저장
    lat_info.append(Lat)
    lon_info.append(Lon)

GPS_data=np.vstack((file_name,width_data, height_data, lat_info,lon_info))
GPS_data_pd=pd.DataFrame(GPS_data.T)
GPS_data_pd.index+=1
print(GPS_data_pd)
GPS_data_pd.to_csv("GPS.csv", header=['Name','Width', 'Height','Latitude',"Longitude"])