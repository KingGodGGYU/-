## 그래프의 표현 방법 2가지
### 인접 행렬(Adjacency-matrix)
- 정점의 개수를 V개라고 했을 때, V x V 크기의 이차원 배열(행렬모양)에 저장한다.
- A[i][j] = 1 or 0  (i->j 간선이 있을 때는 1, 없을 떄는 0)
- 양방향 그래프의 경우 이차원 배열에 저장했을 때 대각선을 기준으로 대칭을 이룬다는 특징이 있다.
- 인접행렬은 자주 사용하지 않는 방식인데, 그 이유는 존재하지 않는 간선에 대한 정보까지도 저장하기 때문이다.
   정점의 개수가 V개이면 간선의 개수 E는 보통 V^2 >= E 이기 때문에 최대크기인 V x V를 사용하는 이 방식은 비효율적이므로, 이 방식은 주로 쉬운 문제를 풀 때만 사용한다.
- 간선에 가중치가 존재한다면 A[i][j]에 0 또는 1 대신 가중치 값을 넣어주면 된다.
   <이때의 예외상황>
   1) 가중치의 값이 w >=0 이라면, 간선이 없는 곳은 0대신 -1을 넣어 구별해줄 수 있다.
   2) 가중치의 값이 모든 범위의 정수라면, 인정행렬 2개를 만들어 해결해야하는데,
       인접하면 1 아니면 0을 저장한 행렬 1개, 인접한 곳의 가중치를 저장한 행렬 1개 즉, 총 2개의 인접행렬을 만들어 해결할 수 있다
|Labeled Graph|Adjacency Matrix|
|:---:|:---|
|![graph](LabeledGraph.png =250x250)|![Matrix](AdjacencyMatrix.PNG =250x250)|
### 인접 리스트(Adjacency-list)
- A[i] = i와 연결된 정점들을 링크드 리스트로 저장함(__연결된 정점이 저장되어 있지만 이들은 정점 i와 각 정점 간의 간선을 의미한다__)
- 정점에 따라서 연결된 정점의 개수가 다르기 때문에 각기 다른 저장공간의 크기를 효율적으로 관리하기 위해 링크드 리스트를 사용.
- 링크드 리스트를 사용하는 이유는 단지 공간효율때문에 그런 것이므로 Vector로 대체하여 인접리스트를 구현할 수 있다.
- 두 노드간의 간선이 여러개인 경우 인접행렬 보다 인접리스트를 사용하는 것이 좋은데, 그 복잡한 관계는 인접행렬 1개 만으로 나타낼 수 없기 때문이다. 인접리스트는 이것이 가능하다.
- 인접행렬의 경우 공간이 V^2 만큼 필요한데, 인접리스트는 모든 간선을 1번씩 저장하기 때문에 E개 만큼 필요하다.
- - 가중치가 있는 경우 __pair<int, int>__ 형을 가지는 2차원 벡터로 해결할 수 있다.
### 그래프의 구성
```C++
class CGraph {
	int n_vertices; // 정점의 개수
	bool* visited; // 지나간 경로인지 아닌지를 판단하는 bool형 포인터
	int* paths; // 지나온 경로를 포인터로 설정
	int _idx; // 현재 위치
	vector <list<int>> adj; // 정점의 간선을 리스트 벡터로 표현
	vector<int> dist; // 간선의 길이를 벡터로 표현
 ```
 ```
public:
	CGraph(int _n) { // 정점의 개수만 필요하기 때문에 
		this->n_vertices = _n; 
		visited = new bool[_n];
		for (int i = 0; i < _n; i++) {
			visited[i] = false;
		}
		adj.resize(_n); //초기화
		adj.resize(_n);
	}
	~CGraph() {
		delete visited;
	}
	void addUndirectedEdge(int _s, int _d) {
		adj[_s].push_back(_d);
		adj[_d].push_back(_s);
		//방향 없음
	}
	void DFS(int _s, int _d, int _idx) {
		visited[_s] = true;
		paths[_idx]=_s;
		cout << _s << " ";
		list<int>::iterator iter;
		for (iter = adj[_s].begin(); iter != adj[_s].end(); iter++) {
			if (_s == _d) {
				for (int i = 0; i < _idx; +i) {
					cout << paths[i] << ' ';
				}
				cout << endl;
			}
			else {
				for (iter = adj[_s].begin(); iter != adj[_s].end(); iter++) {
					if (!visited[*iter]) {
						DFS(*iter, _d, _idx);
					}
				}
			}
			
	}

};
/*  path 저장 벡터나 포인터로 저장
 도착점이아니었을때  DFS recursion. 도착점일땐 출력
 if문 도착점인지 아닌지
 if(도착점){
	cout<<도착점;
 }
 출력하는 위치까지 왔다갔다 해주는 index 필요
 int idx;

 0: visited[0];  0은 방문했다고 표시
 0
 path 내에 현재 위치는 idx=0;
 0은 도착점? no. 근천의 친구를 보게됨
 if(!도착점){
	adj[0];
 }
 1: visited[1];
 if(!도착점){
	adj[1]
	idx=1
 }
 3: visited[3];
	if(도착점){
		for (path) {
		cout<< path[i];
		}
	}
 idx=2
 출력: 0 1 3
 path에 저장되어있는 0 1 3 을 지워주어야 함, idx값을 이용
 idx-=1;
 path에는 0 1 만 있는 것 처럼 보임(2번째이므로)
 idx-=1; 한번 더함
 2: visited[2];

 0 만 있는 것 처럼 보임, 0과 연결된 곳이 존재 -> idx+=1(2)
 2를 path에 저장
 0 2
 }

 visited[s] = true;
 idx++;
 vector<int> paths;
 paths[idx]=s;
 if(시작점 s== 도착점 d){
	for(i=0; i<idx; i++){
		cout<<paths[i];
	}
if(s!=d){
for(i in adj[s]){
	DFS(s,d);
	idx--;
	visited[s]=false;
	}
}
*/
int main() {
	CGraph OGraph(4);


	return 0;
}
```
## BFS 관련 문제
### 백준 2178번 : 미로 탐색

![2178-1](https://github.com/kb081544/Data-Structure-2022/blob/main/HW09/2178-1.PNG)
![2178-2](https://github.com/kb081544/Data-Structure-2022/blob/main/HW09/2178-2.PNG)
```C++
#include <iostream>
#include <queue>
using namespace std;
 
string map[100]; 
int dis[100][100]; // 방문 기록용
int dx[4] = {1, -1, 0, 0}; // 상하좌우 x축 방향
int dy[4] = {0, 0, 1, -1}; // 상하좌우 y축 방향
int n,m; // 미로 크기 변수
queue<pair<int, int> > q; // 탐색 좌표 저장용 큐

void bfs(int x,int y) {
    q.push(make_pair(x, y)); // 큐에 삽입
	dis[x][y] = 1; // 시작 좌표 방문
	while (!q.empty()) {
		x = q.front().first; //큐의 front 좌표를 현재 좌표로 지정
		y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			// 현재 좌표와 인접한 좌표
			int nx = x + dx[i];
			int ny = y + dy[i];
			if ((0 <= nx && nx < n) && (0 <= ny && ny < m) && dis[nx][ny] == 0 && map[nx][ny] == '1') { 
			// 인접 좌표가 존재하는지, 방문 여부와 이동 여부 확인
				q.push(make_pair(nx, ny)); // 인접 좌표 큐에 삽입
				dis[nx][ny] = dis[x][y] + 1; // 인접 좌표 이동거리 저장
			}
		}
	}
}
int main(void) {
    cin >> n>> m; // 미로 크기
    for (int i = 0; i < n; i++) // 행 입력
		cin >> map[i];
    bfs(0,0); // 미로 탐색 시작
	cout << dis[n - 1][m - 1]; // 도착 좌표까지의 거리 출력
}
```
![result](https://github.com/kb081544/Data-Structure-2022/blob/main/HW09/2178-1.PNG)
