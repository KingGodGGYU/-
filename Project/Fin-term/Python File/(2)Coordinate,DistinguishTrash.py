import pandas as pd
#최북단, 최남단, 최동단, 최서단의 위치를 파악하여 데이타를 얻는다.

df_raw=pd.read_csv("Data.csv", skiprows=None)
df_lat_min=df_raw["Latitude"].min()
df_lat_max=df_raw["Latitude"].max()
df_lon_min=df_raw["Longitude"].min()
df_lon_max=df_raw["Longitude"].max()
print(df_lat_min, df_lat_max)
coordinate_info=[]
coordinate_info.append(df_lat_min)
coordinate_info.append(df_lat_max)
coordinate_info.append(df_lon_min)
coordinate_info.append(df_lon_max)
for i in range(4):
    print(coordinate_info[i])
coordinate_info_df=pd.DataFrame(coordinate_info)
coordinate_info_df.to_csv('coordinate_info.csv', index=False, columns=None)

df=df_raw
select_ind_Rubbish=(df["Rubbish"]==1)
select_ind_Plastics=(df["Plastics"]==1)
select_ind_Cans=(df["Cans"]==1)
select_ind_Glass=(df["Glass"]==1)
select_ind_Papers=(df["Papers"]==1)

df2_Rubbish=df[select_ind_Rubbish]
df2_Plastics=df[select_ind_Plastics]
df2_Cans=df[select_ind_Cans]
df2_Glass=df[select_ind_Glass]
df2_Papers=df[select_ind_Papers]

df2_Rubbish.to_csv("Rubbish_data.csv", index=None)
df2_Plastics.to_csv("Plastics_data.csv", index=None)
df2_Cans.to_csv("Cans_data.csv", index=None)
df2_Glass.to_csv("Glass_data.csv", index=None)
df2_Papers.to_csv("Papers_data.csv", index=None)

