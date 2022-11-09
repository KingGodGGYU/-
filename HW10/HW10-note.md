## 수업 내용 정리
```C++
#include <iostream>
#include <queue>
#include <list>
#include <vector>
using namespace std;
class CGraph {
	int n_vertices;
	bool* visited;
	int* paths; // 지나온 경로를 포인터로 설정
	int _idx;
	vector <list<int>> adj;
	vector<int> dist;
public:
	CGraph(int _n) {
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
