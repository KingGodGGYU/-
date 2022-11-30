#include <iostream>
#include <vector>
#include <climits> // clmimts라는 헤더도 MAX값을 넣어줌

using namespace std;

struct Edge {
    int src; // 시작점 
    int dst; // 끝점
    int weight; // 가중치
};

const int UNKOWN = INT_MAX;

vector<int> BellmanFord(vector<Edge> edges, int V, int start) {
    vector<int> distance(V, UNKOWN); // 각각의 거리를 벡터로 둠, 처음 정점들까지의 거리는 전부 INF
    distance[start] = 0; // 정수 타입으로 거리를 둠, 시작점은 내가 있는 곳이니 0
    for (int i = 0; i < V - 1; ++i) { // 정점 개수만큼 for문을 돌려 모든 간선을 뽑음. Relax
        for (auto& e : edges) { // 간선은 구조체이므로 &표시로 참조해서 auto 키워드로 해당 형태를 잡아줌, 간선 e에서 모든 edges
            if (distance[e.src] == UNKOWN) // 시작점이 무한대이면 if문을 빠져나와 for문으로 돌아감
                continue;
            if (distance[e.dst] > distance[e.src] + e.weight) // 기존의 거리보다 새로 찾은 거리가 더 짧으면 
                distance[e.dst] = distance[e.src] + e.weight; // 업데이트 시켜줌->Relax
        }
    }
    return distance;
}
//negative cycle을 체크하는 코드가 필요함, 이것만 추가하면 됨

int main() {
    int V = 5; // 정점의 개수
    vector<Edge> edges; // 간선을 벡터로 둠
    vector<vector<int>> edge_map{
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {3, 2, 5},
        {3, 1, 1},
        {1, 3, 2},
        {1, 4, 2},
        {4, 3, -3}
    };
    for (auto& e : edge_map) // 간선 구조체 하나씩 넣어주면 시작점, 끝점, weight가 삽입
        edges.emplace_back(Edge{ e[0], e[1], e[2] }); // emplace_back: vector에 삽입

    int start = 0;
    vector<int> distance = BellmanFord(edges, V, start);

    cout << "Starting vertex : " << start << endl;
    for (int i = 0; i < distance.size(); ++i) {
        if (distance[i] == UNKOWN)
            cout << "I have not visited the vertex " << i << "." << endl;
        else
            cout << "The vertex " << i << " : " << distance[i] << endl;
    }
    return 0;
}
