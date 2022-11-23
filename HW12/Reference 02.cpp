#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <limits>
using namespace std;

template <typename T>
struct Edge {
	unsigned src;
	unsigned dst;
	T weight; // 
};

template <typename T>
struct Label {
	unsigned ID;
	T distance; //템플렛 타입 T
	inline bool operator> (const Label<T>& l) const {
		return this->distance > l.distance; //비교를 통해 최단거리가 계속 바뀜
	}
};

template <typename T>
class Graph {
public:
	Graph(unsigned N) : V(N) {}
	auto vertices() const { return V; } //몇개씩 올지 모르므로 auto
	auto& edges() const { return edge_list; } //복사해서 붙여넣는 것이 너무 번거로우므로 참조형으로 반환을 시켜줌
	auto edges(unsigned v) const {
		vector<Edge<T>> edges_from_v; //임시 선언한 엣지에다 넣어줌
		for (auto& e : edge_list) { //엣지들 하나씩 보면서 엣지들 싹다 돎
			if (e.src == v)
				edges_from_v.emplace_back(e);
		}
		return edges_from_v;
	}
	void add_edge(Edge<T>&& e) { //엣지 자체는 구조체, 템플렛으로 가지고 들어와서 참조표시를 두번 해줌
		if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V) //시작점이 1보다 같거나 크고, 시작점과 도착점을 
			edge_list.emplace_back(e); //edge list라는 간선 구조체 백터에다가 e 간선 구조체를 생성해서 하나씩 넣어줌
		else
			cerr << "errors" << endl;
	}
	template <typename U>
	friend ostream& operator<< (ostream&, const Graph<U>& G);
private:
	unsigned V;//다룰 정점의 개수
	vector<Edge<T>> edge_list; //간선 구조체를 내가 원하는대로 지정할 수있는 간선 구조체를 벡터로 하나씩 쌓아가는 간선 list
};

template<typename U> //템플렛을 바꿔서 선언
ostream& operator<< (ostream& os, const Graph<U>& G) {
	for (unsigned i = 1; i < G.vertices(); ++i) { //편의상 1부터 시작
		os << i << ":\t";
		auto edges = G.edges(i); //i 간선을 가져옴, 특정정점에서 이어지는 outogoing edge
		for (auto& e : edges)
			os << "{" << e.dst << ": " << e.weight << "}, "; //1:{2,2},{5,3} 편의상 출력 하는 부분
		os << endl;
	}
	return os;
}

template <typename T>
auto create_reference_graph() {
	Graph<T> G(9);
	map<unsigned, vector<pair<unsigned, T>>> edge_map; //정점은 unsigned type
	edge_map[1] = { {2, 2}, {5, 3} };
	edge_map[2] = { {1, 2}, {5, 5}, {4, 1} };
	edge_map[3] = { {4, 2}, {7, 3} };
	edge_map[4] = { {2, 1}, {3, 2}, {5, 2}, {6, 4}, {8, 5} };
	edge_map[5] = { {1, 3}, {2, 5}, {4, 2}, {8, 3} };
	edge_map[6] = { {4, 4}, {7, 4}, {8, 1} };
	edge_map[7] = { {3, 3}, {6, 4} };
	edge_map[8] = { {4, 5}, {5, 3}, {6, 1} };
	for (auto& i : edge_map)
		for (auto& j : i.second)
			G.add_edge(Edge<T>{i.first, j.first, j.second}); //key값, j정점의 정점 이름, 연결되어있는 weight
	return G;
}

template <typename T>
auto CDIJKSTRA(const Graph<T>& G, unsigned src, unsigned dst) { //1번에서 6번까지 가는 최단경로
	priority_queue<Label<T>, vector<Label<T>>, greater<Label<T>>> heap; //Label: 특정 정점까지 도착하는 곳을 저장해주는 구조체
	vector<T> distance(G.vertices(), numeric_limits<T>::max()); //Max값으로 선언, 최대값으로 들어감
	set<unsigned> visited; //유니크한 키값을 갖는 애들을 저장하는 컨테이너, 방문했던 정점들을 저장
	vector<unsigned> parent(G.vertices());
	heap.emplace(Label<T>{src, 0}); //최소 힙에 1번에서 6번까지 가는 최단경로 찾기
	parent[src] = src;
	while (!heap.empty()) {
		auto current_vertex = heap.top();//힙에 갈 수 있는 곳 중에 가장 빠른 길을 가게 됨
		heap.pop(); //제거
		if (current_vertex.ID == dst) { //최소값을 갖고 있는 현재 정점이 1이 됨, 1이 목적지이면 끝내기위한 안전장치
			cout << "Arrived at the destination vertex " << current_vertex.ID << endl;
			break;
		}
		if (visited.find(current_vertex.ID) == visited.end()) { //현재 정점이 1이고 visited는 set, setd은 비어있기 때문에 방문 했는지를 찾아봄
			cout << "Arrived at the vertex " << current_vertex.ID << endl;
			for (auto& e : G.edges(current_vertex.ID)) { //전부타 훑지 않고 2개만 보면 됨, 1에서 나가는 것만 뽑아오변 도착지는 2
				auto neighbor = e.dst; //2번 정점이 neighbor가 됨, 그 다음은 5번이 될 터
				auto new_distance = current_vertex.distance + e.weight; //현재 정점은 1이고 1까지의 거리는 0
				if (new_distance < distance[neighbor]) {
					heap.emplace(Label<T>{neighbor, new_distance}); //업데이트 시켜줌
					parent[neighbor] = current_vertex.ID;
					distance[neighbor] = new_distance;
				}
			}
			visited.insert(current_vertex.ID); //정보들을 전부 알았으니 알고 있는 영역으로 넘겨줌
		}
	}
	vector<unsigned> shortest_path; //백트레킹 과정
	auto current_vertex = dst;
	while (current_vertex != src) {
		shortest_path.push_back(current_vertex);
		current_vertex = parent[current_vertex];
	}
	shortest_path.push_back(src);
	reverse(shortest_path.begin(), shortest_path.end());
	return shortest_path;
}

int main() {
	using T = unsigned;
	auto G = create_reference_graph<T>();
	cout << "Reference graph" << endl;
	cout << G << endl;
	auto shortest_path = CDIJKSTRA<T>(G, 1, 6);
	cout << endl << "The shortest path between the vertex 1 and 6" << endl;
	for (auto v : shortest_path)
		cout << v << ' ';
	cout << endl;

	return 0;
}
