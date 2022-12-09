벨만 포드 알고리즘 정리
=======================
## 최단 거리 알고리즘
> 벨만=포드 알고리즘은 한 노드에서 다른 노드까지의 최단 거리를 구하는 알고리즘이다. 
> - 간선의 가중치가 __음수__ 일때도 최단 거리를 구할 수 있다는 점이다. 
> - 모든 간선을 __전부__ 확인 한다는 특징도 있다.
### 다익스트라도 최단거리, 차이점은?
> 1. 다익스트라는 한단계씩, 즉 최단거리가 가장 짧은 노드를 선택하여 한단계씩 최단 거리를 구한다면, __벨만 포드는 매 반복마다 모든 간선을 전부 확인한다!__ 그렇기 때문에 다익스트라 알고리즘에서 도출된 최적의 해가 항상 도출된다.
> 2. 다익스트라는 음수 간선이 있으면 해를 찾을 수 없다. 그러나 벨만-포드 알고리즘은 음수 간선이 있어도 해를 찾을 수 있다. 그 이유는 음수 간선의 순환을 감지하는 단계가 존재하기 때문이다.
>    - 순환을 감지하는 함수를 통해 벨만-포드로 구할 수 있는지의 여부를 확인할 수 있다. 사이클이 생기면 해를 구할 수 없다. 
### 벨만-포드 알고리즘의 과정
1. 출발 노드를 설정한다.
2. 최단 거리 테이블을 초기화한다.
3. 아래 과정을 (정점의 개수)-1 번 반복한다. 
    1. 모든 간선 E개를 하나씩 확인한다.
    2. 각 간선을 거쳐 다른 노드로 가는 비용을 계산하여 최단 거리 테이블을 갱신한다.   
### LeetCode Solution
#### 벨만-포트 알고리즘 사용
```C++
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<pair<int,int>> adj[n+1]; // 노드가 1부터 n까지
        for(int i=0;i<times.size();i++) // 벨만 포드는 노드를 전부 확인하기 때문에 times의 size만큼 돈다. 모든 노드의 정보를 아는 것이 벨만 포트이기 때문이다. 
                adj[times[i][0]].push_back({times[i][1],times[i][2]}); 
		// times[i][1]이 v 즉 종착노드, times[i][2]가 w즉 거리, times[i][0]이 시작 노드이다.
		// adj[시작노드]에 종착 노드와 거리를 push_back 해준다.
        vector<int> dist(n+1,INT_MAX); // 거리 벡터를 만들어주어 모든 거리를 INT_MAX로 둔다.
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq; // 우선순위큐를 사용한다.
        pq.push({0,k}); // k까지의 거리가 0인 pair를 priority_queue에 삽입
        dist[k]=0; // 출발지 k의 거리이므로 0
        while(!pq.empty())
        {
            pair<int,int> t=pq.top(); // 거리와 노드의 정보를 pair로 받아 삽입
            pq.pop();
            for(pair<int,int> it:adj[t.second]) // adj 벡터가 pair로 되어 있으니 끝까지 받아온다
            {
                if(dist[it.first]>t.first+it.second) // it의 first, 즉 출발 노드의 거리 정보가 새로 알게된 거리 정보+원래의 거리 정보의 합 보다 크면(알게된 정보가 작으면)
                {
                    dist[it.first]=t.first+it.second; // 거리를 업데이트 후 
                    pq.push({dist[it.first],it.first}); // pq에 push 해준다.
                }
            }
        }
        int res=0;
        for(int i=1;i<=n;i++)
        {
            if(dist[i]==INT_MAX)
                return -1; // 음수 간선이 있으면 알고리즘을 종료
            res=max(res,dist[i]); // 순환을 계속 하여 음수 간선의 사이클이 있는지를 확인한다. 
        }
		return res;
	}
};
```

#### 다익스트라 알고리즘 사용
```C++
class Solution {
public:
 int networkDelayTime(vector<vector<int>>& times, int n, int k) {
     vector<int> dist(n+1,INT_MAX); // 거리를 벡터로 담아 모든 거리를 INT_MAX로 둔다
     dist[k]=0; // 시작점 k는 k부터의 거리이므로 0
     
     for(int i=0;i<n-1;i++)
     {
         bool flag=false; // 방문했는지의 여부
         for(auto node:times)
         {
             int src=node[0];  // 시작 노드
             int des=node[1]; // 도착 노드
             int time=node[2]; // 걸리는 시간
             if(dist[src]!=INT_MAX&&dist[des]>dist[src]+time)
             {
                 dist[des]=dist[src]+time; // 새로 발견한 거리를 업데이트 해준 후
                 flag=true; // 노드를 방문했다고 표시해준다.
             }
         }
         if(flag==false) // 방문하지 않은 노드를 발견하면 for문을 빠져나온다. 
             break;
     }
     int res=0;
     for(int i=1;i<=n;i++)
     {
         if(dist[i]==INT_MAX)
             return -1;
         res=max(res,dist[i]);
     }
     return res;
 }
};
```
![result](https://github.com/kb081544/Data-Structure-2022/blob/main/HW13/Accepted.png)   

### 백준 1916
#### 다익스트라, 벨만포드 사용
```C++
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define INF 999
int weight[1000];
vector<pair<int, int>>vec[1000];
int dist[1000]; // 거리 즉, weight
int city;
int bus;

void dijkstra(int start) {
	dist[start] = 0; // 처음 위치의 거리는 0
	priority_queue<pair<int, int>> pq; // weight, 현재 위치를 int로 받는다
	pq.push({ dist[start], start }); // weight과 시작점을 pair로 받는다
	while (!pq.empty()) {
		int current = pq.top().second;  // 현재 위치 정점 번호
		int distance = pq.top().first; // start 에서 현재까지의 weight
		pq.pop();
		if (dist[current] < distance) // 저장되어 있는 것보다 업데이트 된 거리가 크면 패스
			continue;
		for (int i = 0; i < vec[current].size(); i++) { // 현재 노드의 인접 노드들을 확인
			int next = vec[current][i].first; // 인접한 정점들을 확인
			int nextDistance = distance + vec[current][i].second; 
			// start부터 현재 정점까지의 최소거리와
			// 현재를 지나 다음 next 정점까지의 distance
			if (nextDistance < dist[next]) { // 현재 정점을 지나가는 것이 더 가까우면
				dist[next] = nextDistance; // 업데이트 후 pq에 push
				pq.push({nextDistance, next}); 
			}
		}
	}
}
int bellmanFord(int start) {
	fill_n(dist, 1000, INF); // 시작점을 제외한 모든 정점까지의 거리를 INF로
	dist[start] = 0; // 시작 정점은 0
	bool visited; // 방문 여부는 bool 형
	for (int i = 0; i < bus; i++) {
		visited = false;
		for (int j = 1; j <= bus; j++) {
			for (int k = 0; k < vec[j].size(); k++) {
				int current = vec[j][k].first;
				int distance = vec[j][k].second;
				if(dist[current] > dist[j] + distance) { // 원래 있던 정보가 업데이트 된 정보보다 크면
					dist[current] = dist[j] + distance; // 업데이트된 정보를 원래 정보로 업데이트
					visited = true; // 방문 여부를 true
				}
			}
		}
		if (!visited)
				break; // 모든 간선에 대해 방문하지 못한 경우 break
	}
	if (visited) {
			cout << "음수 사이클 존재" << endl;
			return 1;
	}
	return 0;
};

int main() {


	int city_src;
	int city_dst;

	int _src, _dst, _weight;
	cin >> city; // 정점 개수
	cin >> bus; // 간선 개수
	for (int i = 0; i < bus; i++) {
		dist[i] = INF;
	}
	for (int i = 0; i < bus; i++) {
		cin >> _src >> _dst >> _weight;
		vec[_src].push_back({ _dst, _weight });
	}
	cin >> city_src;
	cin >> city_dst;
	
	if(!bellmanFord(city_src))
		cout<<dist[city_dst];
	/*
	dijkstra(city_src);
	cout << dist[city_dst];
	*/
	return 0;
}
```   
![1916](https://github.com/kb081544/Data-Structure-2022/blob/main/HW13/result.png)
