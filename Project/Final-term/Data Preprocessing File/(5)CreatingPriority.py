import pandas as pd
# ['Rubbish','Plastics','Cans','Glass','Papers'],
# 분해 속도 느린순 : 플라스틱 500년이상 > 유리 100~200만년 > 알루미늄 캔 500년년, 금속캔 100년 > 종이는 이에 비하면 새발의 피

# 플라스틱은 미세플라스틱으로 인해 해양오염이 심하고 분해되는대도 오래걸려 1위, 10점
# 일반쓰레기는 범위가 너무 넓어 2위, 7점
# 알루미늄캔은 분해되는데 500년 이사이 걸리므로 3위, 5점
# 유리는 썪는데 정말 오래걸리지만  다른 쓰레기에 비하면 재사용이 용이하기 때문에 4위, 3점
# 종이는 금방 분해되기 때문에 5위, 점수 1점

df=pd.read_csv("SumOfRubbish.csv")
df.columns=['region', 'Rubbish', 'Plastics', 'Cans','Glass', 'Papers']
df['Plastics']=df['Plastics']*10.0
df['Rubbish']=df['Rubbish']*7.0
df['Cans']=df['Cans']*5.0
df['Glass']=df['Glass']*3.0
df['Papers']=df['Papers']*1.0

df['Points']=df['Plastics']+df['Rubbish']+df['Cans']+df['Glass']+df['Papers']

point_idx=(df['Points']!=0)
point_region=df['Points'][point_idx]
df_region=df[point_idx]
df_csv=df_region.drop(['Rubbish','Plastics','Cans','Glass','Papers'], axis=1)

print(point_region)
print(point_region.shape)
print(df_region)
df_csv.to_csv("PointsData.csv", index=False, header=None)
