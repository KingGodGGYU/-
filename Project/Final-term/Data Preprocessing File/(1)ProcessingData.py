import pandas as pd
merged_data=pd.read_csv("merge.csv")
#중복값 제거
df_drop=merged_data.drop_duplicates(['Longitude', 'Latitude', 'Rubbish','Plastics','Cans','Glass','Papers'])
#필요없는 정보 제거. 쓰레기 유무와 위도 경도만 필요하므로 나머지 열은 drop 시킨다.
df=df_drop.drop(['Number', 'Name', 'Widths', 'Hights'], axis=1)
df.to_csv("Data.csv")