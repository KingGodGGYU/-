# 벨만 포드 알고리즘
## 알고리즘
### 분할/정복
1. Greedy
  - 다익스트라
  - 좋아보이는 알고리즘 사용
2. 영토 확장/visited
  - 근처부터 하나씩 정복해 나가가는 컨셉
3. Relax
  - Bellman-ford
  - 차근차근 알아가며 정보를 알게 되므로 Relax를 시켜줌

### 다익스트라
 > V(Vertex, 정점, <V1, V2,...,Vi>), E(path의 경로, (Vi, Vi+1), W(가중치(Vi, Vi+1, Wi,i+1)), 가중치의 값이 최소가 되도록
 > Shortest Path
 > Longest Path: undefined
 >  > Weight를 음수로 바꾸는 것이 불가
 >  > __Negative Cycle__ : 돌면 돌 수록 최소값이 계속 업데이트됨
 >  > Shortest Path: undefined
 >  > Negative Weight이 있으면 다익스트라, 또는 벨만포드로도 구할 수 없음
### 벨만 포드
 > Relax 사용, 알아나가는 것을 Relax라고 함
 > 그래프를 __충분히 Relax__ 를 해주면(알아나가면) __결과__ 를 알아나갈 수 있음
 > 맞는지 __결과를 확인__ 하는 과정이 필요.

### Shortest Path, Negative Cycle
 > Weight를 음수로 바꾸면 순환할 때 마다 값이 바뀜
 > > __Negative Cycle__ : 돌면 돌 수록 최소값이 계속 업데이트됨
 > > Shortest Path: undefined
 > > Negative Cycle이 있으면 벨만포드로도 구할 수 없음
 > 기본적인 동작 방법
 > > 1. 모든 정점까지의 거리를 INF로 둠, 갈 수 있는 방법도 없음, 시작 정점의 거리는 0
 > > 2. select edge -> Relax
 > > > Dijkstra(greedy): 기존에 알고있던 거리(d[v])>새로 알게 된 거리(d[u]+w(u, v)); d[v]<-d[u]+w(u,v);
 > > > Bellman-Ford: 정점 개수 V에 따라  for 문을 돌림 -> 모든 간선들에 대해 relax 시켜줌. Negatice Cycle 확인 필요.
[알고리즘 공부 책 링크](https://sd.blackball.lv/library/Introduction_to_Algorithms_Third_Edition_(2009).pdf)
