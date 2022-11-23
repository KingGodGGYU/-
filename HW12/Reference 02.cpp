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
			G.add_edge(Edge<T>{i.first, j.first, j.second});
	return G;
}

template <typename T>
auto CDIJKSTRA(const Graph<T>& G, unsigned src, unsigned dst) {
	priority_queue<Label<T>, vector<Label<T>>, greater<Label<T>>> heap;
	vector<T> distance(G.vertices(), numeric_limits<T>::max());
	set<unsigned> visited;
	vector<unsigned> parent(G.vertices());
	heap.emplace(Label<T>{src, 0});
	parent[src] = src;
	while (!heap.empty()) {
		auto current_vertex = heap.top();
		heap.pop();
		if (current_vertex.ID == dst) {
			cout << "Arrived at the destination vertex " << current_vertex.ID << endl;
			break;
		}
		if (visited.find(current_vertex.ID) == visited.end()) {
			cout << "Arrived at the vertex " << current_vertex.ID << endl;
			for (auto& e : G.edges(current_vertex.ID)) {
				auto neighbor = e.dst;
				auto new_distance = current_vertex.distance + e.weight;
				if (new_distance < distance[neighbor]) {
					heap.emplace(Label<T>{neighbor, new_distance});
					parent[neighbor] = current_vertex.ID;
					distance[neighbor] = new_distance;
				}
			}
			visited.insert(current_vertex.ID);
		}
	}
	vector<unsigned> shortest_path;
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
