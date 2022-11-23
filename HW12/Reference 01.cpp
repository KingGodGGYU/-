#include <iostream>
#include <fstream>
#include <queue>
#include <list> 
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <limits>
using namespace std;

// STL�� ������� ���� ���� �ڵ� �����Դϴ�.
// �켱 ������ ũ��� ������ ������ ������ �Ӵϴ�.
#define MAX_VTXS 100		// �ִ� 100���� ������ �ٷ�ϴ�.
#define INF 9999            // INF�̸� ������ ���ٰ� ǥ���մϴ�(STL�� ����ϸ� �̷��� �� �ؿ�).

// ����ġ �׷����� ǥ���ϴ� Ŭ������ ADJ MATRIX(���� ���)�� ����մϴ�.
// ��, AdjMatGraph�� ����ġ�� ������� �ʽ��ϴ�.
class AdjMatGraph {
protected:
	int    size;					// ������ �����Դϴ�.
	char   vertices[MAX_VTXS];		// ���� �����Դϴ�.
	int    adj[MAX_VTXS][MAX_VTXS];	// ������ ���� ��ķ� ǥ���մϴ�. ���� ǥ�� ����� ���� ��İ� ���� ����Ʈ, �� ����� �����?
public:
	AdjMatGraph() { reset(); }		// ����ġ �׷��� Ŭ������ �������Դϴ�. reset ��� �Լ��� �����ϼ���.
	char getVertex(int i) { return vertices[i]; }		// ���� ������ ��ȯ�մϴ�.
	int  getEdge(int i, int j) { return adj[i][j]; }	// ���� ������ ��ȯ�մϴ�. 
	void setEdge(int i, int j, int val) { adj[i][j] = val; }	// ������ ����ϴ�. i������ j������ �մ� ���� weight(val)�� ������Ŀ� �Է��մϴ�.
	bool isEmpty() { return size == 0; }		// �׷����� ������ �ϳ��� ���� �������� Ȯ���մϴ�.
	bool isFull() { return size >= MAX_VTXS; }	// �׷����� ������ �� �̻� �߰��� �� ���� �������� Ȯ���մϴ�.

	void reset() {	// �׷����� ó������ �������� �Լ��Դϴ�.  
		size = 0;	// ������ �ϳ��� ����,
		for (int i = 0; i < MAX_VTXS; ++i)
			for (int j = 0; j < MAX_VTXS; ++j)
				setEdge(i, j, 0);	// ����Ǿ� �ִ� ��� ���� 0����(����Ǿ� ���� �ʴٰ�) �����մϴ�.
	}
	void insertVertex(char name) { // ������ �׷����� �־��ִ� �Լ��Դϴ�. 
		if (!isFull()) vertices[size++] = name; // ������ �� ���� �� ������, ������ �����, �׷��� ũ�⵵ �ϳ� ������ŵ�ϴ�(size++).
		else cout << "ERROR : �׷��� ���� ���� �ʰ�" << endl; // ������ �� ���� �� ������ �ܼ�â�� ���� �޼����� ����մϴ�.
	}
	void insertEdge(int u, int v) {	// ���� u�� ���� v�� �մ� ������ ����ϴ�. 
		setEdge(u, v, 1);	// ����ġ�� ������� �ʱ� ������ ����ġ�� 1�Դϴ�. 
		setEdge(v, u, 1);	// ���⼺�� ������� �ʱ� ������ �ݴ�ε� �̾� �ݴϴ�.
	}
	void display() {		// ���� ����� ����� �ܼ�â�� ����ϴ� ����Լ��Դϴ�. 
		cout << size << endl;	// ���� �׷����� ũ��(���� ����)�� ����ϰ�,
		for (int i = 0; i < size; ++i) {		// ������ ������ŭ,
			cout << getVertex(i) << " ";		// ���� ������ ����մϴ�.
			for (int j = 0; j < size; ++j)		// �׸��� �ش� ������ ��� ����Ǿ� �ִ����� ǥ���մϴ�.
				cout << getEdge(i, j) << "\t";
			cout << endl;
		}
	}
};

// ����ġ�� ������� �ʴ� Ŭ������ ��ӹ޾Ƽ� , ����ġ�� ǥ���ϴ� Ŭ������ ����ϴ�.
// ���� ���� �� ����ġ�� ������� �ʴ� Ŭ����, �׸��� �̾ ����ġ�� �ִ� Ŭ������ ������ϴ�.
// ���� ������ ���� ������ �ʾƵ� �˴ϴ�.
class WGraph : public AdjMatGraph {	// ���� ����ġ�� ������� �ʴ� �׷��� Ŭ������ ��ӹ޽��ϴ�.
public:
	void insertEdge(int u, int v, int weight) {	// ����ġ(weight)�� ����Ͽ� ������ ����ϴ�.
		if (weight > INF) weight = INF;			// ���� �̻��� ����ġ(�̻��ϰ� ū ��)�� ������ �߸��� ������ �Ǵ��ϰ�, ������� �ʾҴٰ� ���ϴ�.
		setEdge(u, v, weight);					// ����� �� ����ġ ���� �ִٸ�, ���� u�� v�� �մ� ������ ����ϴ�. 
	}
	bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }	// ������ �̹� �����ϴ��� Ȯ���մϴ�. �ʱⰪ�� INF�̱� ������, ���� ����� ���� i, j�� ���� INF�� �ƴ϶�� ������ �����Ѵٰ� �Ǵ��� �� �ֽ��ϴ�.
	void load(string filename) {		// �ܺ� ���Ͽ��� �׷��� ������ �ҷ��� �� ����մϴ�. �ҷ����� ������ Ȯ���Ͽ� ������ ���� �ٸ��� Ȱ���� �� �־�� �մϴ�.
		ifstream fp(filename);
		if (fp.is_open()) {
			int n, val;
			fp >> n;							// ������ ��ü ������ ���� ��������,
			for (int i = 0; i < n; i++) {
				char str[80];
				int val;
				fp >> str;						// ���� ������ ���� ���� char�̱� ������ char�� ���� ������ �����ɴϴ�.
				insertVertex(str[0]);			// �־��� ������ ���� ������ �����մϴ�. 
				for (int j = 0; j < n; j++) {
					fp >> val;					// ���� ������ �о� �ͼ�,
					insertEdge(i, j, val);		// ������ ����ϴ�.          
				}
			}
		}
		else cout << "File can not be found !" << endl;
		fp.close();
	}
};

// ���ͽ�Ʈ�� �˰����� �ִ� ��� Ž�� ����� �߰��� �׷����Դϴ�.
// ���ͽ�Ʈ�� �˰����� ����ġ�� �ִ� ��� �������? ���� ���� ����� �� ����ġ �׷���(WGraph)�� ��ӹް�, ���ͽ�Ʈ�� �˰����� �۵���ų �� ���� ��ɸ� �߰��� �����մϴ�. 
// ���� ������ ��� Ŭ������ �������� �ʰ�, �ϳ��� Ŭ������ �����ص� �˴ϴ�. 
class WGraphDijkstra : public WGraph {
	int path[MAX_VTXS];		// ����Դϴ�. 
	int dist[MAX_VTXS];		// ���۳��κ����� �ִܰ�� �Ÿ��Դϴ�.
	bool found[MAX_VTXS];	// �湮�� ���� ǥ�� ���� S�Դϴ�. �湮�ϰ� �Ǹ�(���� S�� ���ԵǸ�) true�� ����� �ݴϴ�. 
public:
	int chooseVertex() {	// ��ó�� ���� �߿��� ���� �湮���� �ʾҰ�, ���� ���� ������� �� �� �ִ� ������ �����ϴ� �Լ��Դϴ�.
		int min = INF;		// ���� ���� ����� ã�ƾ� �Ǵ�, �ӽ� ������ ����� ū ���� �־� �ݴϴ�.	
		int minpos = -1;	// ������ ������ ��ȯ�ϱ� ���� �ӽ� �����Դϴ�.
		for (int i = 0; i < size; i++)			// ������ ��� Ȯ���ؼ�,
			if (dist[i] < min && !found[i]) {	// �湮���� ���� �� �� �ּ� ������� �� �� �ִ� ������ ã�Ƴ����ϴ�.
				min = dist[i];
				minpos = i;
			}
		return minpos;
	}
	void printDistance() {		//��� ����������� �ִܰŸ��� �ܼ�â�� ����ϴ� �Լ��Դϴ�.
		for (int i = 0; i < size; i++) { cout << dist[i] << " "; }
		cout << endl;
	}
	void PrintPath(int start, int end) {	// �ش� ���������� ��θ� �ܼ�â�� ����ϴ� �Լ��Դϴ�. 
		cout << "[�ִܰ��: " << getVertex(start) << "<-" << getVertex(end) << "] " << getVertex(end);
		while (path[end] != start) {
			cout << "-" << getVertex(path[end]);
			end = path[end];
		}
		cout << "-" << getVertex(path[end]) << endl;
	}
	// ���ͽ�Ʈ�� �⺻ ��� �˰����Դϴ�. 
	// ���� s ���� �����մϴ�.
	void ShortestPath(int s) {
		for (int i = 0; i < size; i++) {	// ���ͽ�Ʈ�� �˰��� �ʿ��� �������� �ʱ�ȭ�Ͽ� �˰��� �۵��� �غ��մϴ�.
			dist[i] = getEdge(s, i);		// ���� s�� ��� ������ i�� ���� �ϳ� �ϳ� ������ ���� Ȯ���� ���鼭, �ش� ���������� �Ÿ� ������ ������ �Ӵϴ�.
			path[i] = s;					// �� ���������� �ִ� ����Դϴ�. �ش� ������ �����ϱ� ���� �ִ� ����� �ٷ� �� ������ �߰��� �ݴϴ�.
			found[i] = false;				// ó���� S������ �������.
		}
		found[s] = true;	// ���� s�� �湮�Ͽ����Ƿ�, s�� �湮�Ͽ��ٰ�(���� S�� ����) �մϴ�.
		dist[s] = 0;		// ó�� ��ġ�� �Ÿ��� ���� ���� ������ ���̴� 0�Դϴ�. 
		for (int i = 0; i < size; i++) {		// ��� ������ ���� Ȯ���� �� �ݴϴ�. 
			cout << "Step" << i + 1 << ": ";	// �ܼ�â�� ������ ����� �ֱ� ���� �ڵ� �����Դϴ�.
			printDistance();					// ���� ���¿��� �ٸ� ��� ���������� �Ÿ��� �ܼ�â�� ����մϴ�.
			int u = chooseVertex();				// ��ó�� ���� �߿��� ���� �湮���� �ʾҰ�, ���� ���� ������� �� �� �ִ� ������ �����մϴ�.
			found[u] = true;					// �׸��� ������ ������ �湮(���� S�� ����)�մϴ�.
			for (int w = 0; w < size; w++) {	// �ٽ� ��� ������ ���� 
				if (found[w] == false)			// �湮���� ���� ������(���� S�� ������ �ʴ� ��� w)�� �Ÿ� ���� �����մϴ�.
					if (dist[u] + getEdge(u, w) < dist[w]) {	// ���� ����� ���� ������ u ���������� �Ÿ�(dist[u])�� ���� ��ô�� ��� getEdge(u, w)�� ���� ���� ���ο� �Ÿ��� �ǰ�, ������ �˴� ��δ� dist[w]�� �˴ϴ�. ���� ��ô�� ��ΰ� �� ª���� ������Ʈ �� �ݴϴ�.
						dist[w] = dist[u] + getEdge(u, w);		// �� ���� ��θ� ã������ ������Ʈ �� �ְ�, 
						path[w] = u;							//  �ִ� ��ο� �߰��� �ݴϴ�.
					}
			}
		}
	}

};

int main() {

	WGraphDijkstra g;
	string fn = "graph_sp.txt";
	g.load(fn);
	cout << "Dijkstra�� �ִܰ�� Ž���� ���� �׷��� : " << fn << endl << endl;
	g.display();
	g.ShortestPath(0);

	return 0;
}

