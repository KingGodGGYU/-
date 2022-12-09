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
        vector<pair<int,int>> adj[n+1];
        for(int i=0;i<times.size();i++)
                adj[times[i][0]].push_back({times[i][1],times[i][2]});
        vector<int> dist(n+1,INT_MAX);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        pq.push({0,k});
        dist[k]=0;
        while(!pq.empty())
        {
            pair<int,int> t=pq.top();
            pq.pop();
            for(pair<int,int> it:adj[t.second])
            {
                if(dist[it.first]>t.first+it.second)
                {
                    dist[it.first]=t.first+it.second;
                    pq.push({dist[it.first],it.first});
                }
            }
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

#### 다익스트라 알고리즘 사용
```C++
class Solution {
public:
 int networkDelayTime(vector<vector<int>>& times, int n, int k) {
     vector<int> dist(n+1,INT_MAX);
     dist[k]=0;
     
     for(int i=0;i<n-1;i++)
     {
         bool flag=false;
         for(auto node:times)
         {
             int src=node[0];
             int des=node[1];
             int time=node[2];
             if(dist[src]!=INT_MAX&&dist[des]>dist[src]+time)
             {
                 dist[des]=dist[src]+time;
                 flag=true;
             }
         }
         if(flag==false)
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

### 백준 1916
#### 다익스트라 사용
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
void dijkstra(int start) {
	dist[start] = 0; // 처음 위치의 거리는 0
	priority_queue<pair<int, int>> pq; // weight, 시작점
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

int main() {
	int city;
	int bus;

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
	dijkstra(city_src);
	cout << dist[city_dst];
	return 0;
}
```
