#### dfs
```C++
void dfs(int x)
{
	visited[x] = true;
	cout << x << " ";
	for (int i = 0; i < graph[x].size(); i++) // 인접한 노드 사이즈만큼 탐색
	{
		int y = graph[x][i];
		if (!visited[y]) // 방문하지 않았으면 즉 visited가 False일 때 not을 해주면 True가 되므로 아래 dfs 실행
            dfs(y); // 재귀적으로 방문
	}
}
```
#### bfs
```C++
void bfs(int start) {
    queue<int> q;
    q.push(start); // 첫 노드를 queue에 삽입
    visited[start] = true; // 첫 노드를 방문 처리

    // 큐가 빌 때까지 반복
    while (!q.empty()) {
        // 큐에서 하나의 원소를 뽑아 출력
        int x = q.front();
        q.pop();
        cout << x << ' ';
        // 해당 원소와 연결된, 아직 방문하지 않은 원소들을 큐에 삽입
        for (int i = 0; i < graph[x].size(); i++) {
            int y = graph[x][i];
            if (!visited[y]) {
                q.push(y);
                visited[y] = true;
            }
        }
    }
}
```
#### 벨만 포드
```C++
void Bellman_Ford()
{
    Dist[1] = 0;
    for (int i = 1; i <= N - 1; i++)
    {
        for (int j = 0; j < Edge.size(); j++)
        {
            int From = Edge[j].first.first;
            int To = Edge[j].first.second;
            int Cost = Edge[j].second;
 
            if (Dist[From] == INF) continue;
            if (Dist[To] > Dist[From] + Cost) Dist[To] = Dist[From] + Cost;
        }
    }
 
    for (int i = 0; i < Edge.size(); i++)
    {
        int From = Edge[i].first.first;
        int To = Edge[i].first.second;
        int Cost = Edge[i].second;
 
        if (Dist[From] == INF) continue;
        if (Dist[To] > Dist[From] + Cost)
        {
            cout << "음의 사이클이 존재하는 그래프입니다." << endl;
            return;
        }
    }
    cout << "음의 사이클이 존재하지 않는, 정상적인 그래프 입니다." << endl;
}
```
#### 다익스트라
##### 우선순위큐 사용
```C++
void Dijkstra_Using_Heap()
{
    priority_queue<pair<int, int>> PQ;
    PQ.push(make_pair(0, Start));
    Dist[Start] = 0;
 
    while (PQ.empty() == 0)
    {
        int Cost = -PQ.top().first;
        int Cur = PQ.top().second;
        PQ.pop();
 
        for (int i = 0; i < Vertex[Cur].size(); i++)
        {
            int Next = Vertex[Cur][i].first;
            int nCost = Vertex[Cur][i].second;
 
            if (Dist[Next] > Cost + nCost)
            {
                Dist[Next] = Cost + nCost;
                PQ.push(make_pair(-Dist[Next], Next));
            }
        }
    }
 
    for (int i = 1; i <= V; i++)
    {
        if (Dist[i] == INF) cout << "INF" << endl;
        else cout << Dist[i] << endl;
    }
}
```
##### 일반적인 코드
```C++
int Find_Shortest_Node()
{
    int Min_Dist, Min_Idx;
    Min_Dist = INF;
    Min_Idx = -1;
 
    for (int i = 1; i <= V; i++)
    {
        if (Select[i] == true) continue;
        if (Dist[i] < Min_Dist)
        {
            Min_Dist = Dist[i];
            Min_Idx = i;
        }
    }
    return Min_Idx;
}
 
void Update_Dist(int NewNode)
{
    for (int i = 1; i <= V; i++)
    {
        if (Select[i] == true) continue;
        if (Dist[i] > Dist[NewNode] + MAP[NewNode][i])
        {
            Dist[i] = Dist[NewNode] + MAP[NewNode][i];
        }
    }
}
 
void Dijkstra()
{
    for (int i = 1; i <= V; i++) Dist[i] = MAP[Start][i];
    Dist[Start] = 0;
    Select[Start] = true;
    
    for (int i = 0; i < V - 1; i++)
    {
        int NewNode = Find_Shortest_Node();
 
        Select[NewNode] = true;
        Update_Dist(NewNode);
    }
}
```
#### 프림 알고리즘
```C++
int N, M, Answer;
int Dist[MAX];
bool Select[MAX];
vector<pair<int, int>> Cost[MAX];
 
void Prim()
{
    Dist[1] = 0;
    Select[1] = true;
    for (int i = 0; i < Cost[1].size(); i++)
    {
        int Next = Cost[1][i].first;
        int Distance = Cost[1][i].second;
        Dist[Next] = Distance;
    }
 
    for (int i = 1; i <= N - 1; i++)
    {
        int Min_Cost = INF;
        int Min_Idx = -1;
        for (int j = 1; j <= N; j++)
        {
            if (Select[j] == true) continue;
            if (Min_Cost > Dist[j])
            {
                Min_Cost = Dist[j];
                Min_Idx = j;
            }
        }
 
        Select[Min_Idx] = true;
        Answer = Answer + Min_Cost;
 
        for (int j = 0; j < Cost[Min_Idx].size(); j++)
        {
            int Next = Cost[Min_Idx][j].first;
            int Distance = Cost[Min_Idx][j].second;
 
            if (Select[Next] == true) continue;
            if (Dist[Next] > Distance) Dist[Next] = Distance;
        }
    }
}
```
