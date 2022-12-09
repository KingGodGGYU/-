### 프로그래머스 
#### 정렬 H-Index
```C++
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
    int answer = 0;
    // 일단 정렬
    sort(citations.begin(), citations.end());
    for(int i=0; i<citations.size(); i++){
        int H_Index=citations.size()-i;
        if(citations[i]>=H_Index)
            return H_Index;
    }
    return answer;
}
```
#### 정렬 K번째 수
```C++
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    for(int i=0; i<commands.size(); i++){
        vector<int>temp;
        for(int j=commands[i][0]-1; j<commands[i][1]; j++){
          temp.push_back({array[j]});  
        }
        sort(temp.begin(), temp.end());
        answer.push_back(temp.at(commands[i][2]-1));
    }

    return answer;
}
```
#### 정렬 가장 큰 수
```C++
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
bool cmp(string a, string b){
    return a+b>b+a;
}
string solution(vector<int> numbers) {
    vector<string>temp; // 임시 벡터 선언
    for(int i=0; i<numbers.size();i++){
        temp.push_back(to_string(numbers[i]));
    }
    string answer = "";
    sort(temp.begin(),temp.end(),cmp);
    if(temp[0].compare("0")==0)
        return "0";
    for(int i=0; i<temp.size(); i++){
        answer+=temp[i];
    }
    return answer;
}
```
#### bfs 가장 먼 노드
```C++
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int solution(int n, vector<vector<int>> edge) {
    // bfs를 사용
    vector<vector<int>> graph(n+1); // 2차원 그래프
    vector<int> counts(n+1,0); // counter 배열
    vector<bool> visited(n+1, false);
    queue<int> q; // bfs queue
    int answer = 0;
    // 인접 리스트 기반 그래프 생성
    for(int i=0; i<edge.size(); i++){
        // 간선 정보
        graph[edge[i][0]].push_back(edge[i][1]);
        graph[edge[i][1]].push_back(edge[i][0]);
    }
    q.push(1);
    visited[1]=true;
    
    //bfs
    while(!q.empty()){
        int node=q.front();
        q.pop();
        for(int i=0; i<graph[node].size(); i++){
            if(!visited[graph[node][i]]){
                int currentCount=counts[node]+1;
                visited[graph[node][i]]=true;
                // 방문 후 count 증가
                counts[graph[node][i]]=currentCount;
                q.push(graph[node][i]);
            }
        }
    }
    
    sort(counts.begin(), counts.end(), greater<int>());
    for(auto cnt:counts){
        if(counts[0]!=cnt)
            break;
        answer++;
    }
   
```
#### 더 맵게
```C++
#include <iostream>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>
using namespace std;

int solution(vector<int> scoville, int K) {
    int count=0;
    priority_queue<int, vector<int>, greater<int>> pq(scoville.begin(), scoville.end());
    while(pq.size()>1&&pq.top()<K){
        int first=pq.top();
        pq.pop();
        int second=pq.top();
        pq.pop();
        pq.push(first+(second*2));
        count++;
    }
    if(pq.top()<K){
        return -1;
    }
    int answer = count;
    return answer;
}
```

### 백준
#### 1238
```C++
#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
#define MAX 1000
#define INF 1000
int dist[MAX];
vector<pair<int, int>> v[MAX];
int N, M, X;

void dijkstra(int start) { // 시작 정점
	priority_queue<pair<int, int>> pq; // weight, 현재 위치
	for (int i = 0; i < MAX; i++) {
		dist[i] = INF;
	}
	dist[start] = 0;
	pq.push({ dist[start], start });
	while (!pq.empty()) {
		int weight = pq.top().first; // distance
		int current = pq.top().second; // 현재 정점
		pq.pop();
		for(int i=0; i<v[current].size(); i++){
			int y = v[current][i].first;
			int wy = v[current][i].second;
			if (dist[y] > dist[current] + wy) {
				dist[y] = dist[current] + wy;
				pq.push({ dist[y], y });
			}
		}
	}
}
// x번마을, m개의 단방향 도로, i번째 길을 지나는데 T시간
int main() {
	int N, M, X;
	cin >> N >> M >> X;
	int src, dst, dist;
	int result;
	int tdist[MAX];
	for (int i = 0; i < M; i++) {
		cin >> src >> dst >> dist;
		v[src].push_back({ dst,dist });
	}
	dijkstra(X);
	for (int i = 1; i <= N; i++) {
		tdist[i] = dist[i];
	}
	for (int i = 1; i <= N; i++) {
		if (i == X)
			continue;
		dijkstra(i);
		result = max(result, tdist[i] + dist[X]);
	}
}
```
#### 1916
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
