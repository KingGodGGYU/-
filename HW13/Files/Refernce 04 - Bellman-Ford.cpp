// 수업에서 다룬 문제 풀이 코드로, 일부만 구현되어 있습니다.
// 수업 때 설명을 듣고, 마저 구현하세요.
#include <iostream>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;

struct Edge {
    int src;
    int dst;
    int weight;
};

const int UNKOWN = INT_MAX;

bool ReadTestCase(string filename, int& N, vector<Edge>& edges) {
    ifstream infile(filename);

    if (!infile.is_open()) { // 파일을 읽었는지 확인하는 안전장치
        cout << "error" << endl;
        return false;
    }

    infile >> N; // 셀의 크기: 3개, 3x3

    for (int i = 0; i < N * N - 1; i++) { // 셀의 크기 3x3개를 가져옴(0부터 시작하니 N*N-1)
        string directions; // string으로 방향을 가져옴
        int power; // 소비량, 즉 weight를 가져옴

        infile >> directions >> power; // 방향과 배터리 소모를 받음

        int next = i; // 현재 셀의 위치 index

        for (auto d : directions) {
            switch (d) {
            case 'N': next = i - N; break; // 북쪽으로 가면 N개만큼 줄어들면 됨
            case 'E': next = i + 1; break; // 동쪽으로 가면 한개 늘어나면 됨
            case 'S': next = i + N; break;
            case 'W': next = i - 1; break;
            }
            edges.push_back(Edge{i,next,(-1)*power}); // 시작점, 끝점, 그리고 power에다 음수를 붙여야 최단거리로 바꾸어 풀 수 있음
        }
    }
    return true;
}

vector<int> BellmanFord(vector<Edge> edges, int V, int start) { // 벨만포드 알고리즘
    vector<int> distance(V, UNKOWN);
    distance[start] = 0;
    for (int i = 0; i < V - 1; ++i) {
        for (auto& e : edges) {
            if (distance[e.src] == UNKOWN)
                continue;
            if (distance[e.dst] > distance[e.src] + e.weight)
                distance[e.dst] = distance[e.src] + e.weight;
        }
    }
    // negative cycle을 체크하는 부분이 빠져있음
    // 충분히 돌린 다음, 거리확인 하고 알고리즘을 충분히 돌렸는데 여전히 좋은거리가 있으면
    // 업데이트가 아닌, 알고리즘을 종료시킴. 
    return distance;
}

int main() {
    int N;
    vector<Edge> edges;

    if (ReadTestCase("testcase1.txt", N, edges))
    {
        vector<int> distance = BellmanFord(edges, N * N, 0);

        if (distance.empty() || distance[N * N - 1] == UNKOWN)
            cout << "탐색 중단" << endl;
        else
            cout << -1 * distance[N * N - 1] << endl;
    }
}
