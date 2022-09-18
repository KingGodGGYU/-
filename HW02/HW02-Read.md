#Week2
## 1. 우선순위큐와 힙 내용 정리
우선순위큐: 우선 순위가 높은 데이터가 먼저 나가는 형태의 자료구조. 큐가 우선순위에 따라 일차원적으로 정렬이 된 형태이다.    
힙: 루트 노드에 가장 큰 값을 저장하는 최대 힙이거나 가장 작은 값을 저장하는 최소 힙인 "완전이진트리" 형태. 최댓값 또는 최솟값을 찾아내는 연산이 빠르다는 특징을 가진다. 완전이진트리란, 마지막 레벨을 제외 하고 모든 레벨이 완전히 채워져 있으며, 마지막 레벨은 완전 꽉 차 있지 않아도 노드가 왼쪽에서 오른쪽으로 채워져야 하고, 마지막 레벨 h 에서 1~2h-1개의 노드를 가질 수 있다. 또한 배열을 사용하여 효율적으로 표현이 가능하다.

일반적으로 우선순위큐는 힙을 통해 구현한다. 힙은 자식노드와의 비교만으로 노드의 자리를 찾기 때문에 시간복잡도가 O(log2n)으로 낮다. 최악의 경우 힙을 사용하지 않으면 우선순위를 찾기 위해 인덱스의 끝까지 탐색할 수 있다. 이러한 문제를 해결하기 위해 힙을 사용한다. 즉, 우선순위큐가 구현되기 위해 힙이 사용되며 insert와 remove를 보조하는 역할이라 보면 이해하기 쉽다.

## 2. C++를 이용한 우선순위큐 프로그래밍 방법 정리
```C++
#include <queue>: C++에서 제공하는 큐 라이브러리   
queue<int> Q : Q라는 이름의 int 요소들로 구성된 큐 선언   
Q.push: 원소 삽입   
Q.empty: 비었으면 true 반환, 비어있지 않으면 False 반환   
Q.top: 루트 값 반환   
Q.pop: 루트 값 제거   
Q.front(): 큐의 front 를 반환   
Q.back(): 큐의 back를 반환   
```
```C++
//C++에서의 우선순위 큐 사용(STL 이용), "HW02-2.cpp" 파일 업로드 확인
#include <iostream>
#include <queue>
using namespace std;

int main() {
	//최대힙
	priority_queue<int, vector<int>, less<int>> MaxHeap;
	MaxHeap.push(15);
	MaxHeap.push(5);
	MaxHeap.push(10);
	MaxHeap.push(1);
	MaxHeap.push(7);
	MaxHeap.pop();
	MaxHeap.pop();
	cout<<"Max Heap Priority Queue: ";
	while (!MaxHeap.empty()) {
		cout<<MaxHeap.top()<<" ";
		MaxHeap.pop();
	}
	cout<<endl;

	//최소힙
	priority_queue<int, vector<int>, greater<int>> MinHeap;
	MinHeap.push(15);
	MinHeap.push(5);
	MinHeap.push(10);
	MinHeap.push(1);
	MinHeap.push(7);
	MinHeap.pop();
	MinHeap.pop();
	cout<< "Min Heap Priority Queue: ";
	while (!MinHeap.empty()){
		cout<<MinHeap.top()<<" ";
		MinHeap.pop();
	}
	cout<<endl;
	
	return 0;
}
```
## 3-1. 백준 1966
```C++
//"HW02-3-1.cpp" C++ 파일 확인
#include <iostream>
#include <queue>
using namespace std;
int main() {
    int cnt;
    int testcase;
    int arr = 0;
    cin >> testcase;
    int* order = new int[testcase];
    int N,M,priority;
    for (int i=0; i<testcase; i++){
        cnt=0;
        cin>>N>>M;
        queue<pair<int, int>> q;
        priority_queue<int> pq;
        for (int j = 0; j<N; j++) {
            cin >> priority;
            q.push({j, priority});
            pq.push(priority);
        }
        while (!q.empty()) {
            int index = q.front().first;
            int value = q.front().second;
            q.pop();
            if (pq.top()==value) {
                pq.pop();
                ++cnt;
                if (index==M) {
                    order[arr] = cnt;
                    arr++;
                    break;
                }
            }
            else q.push({index,value});
        }
    }
    for (int k = 0; k < testcase; k++) {
        cout << order[k] << endl;
    }
    delete[] order;
    return 0;
}
```
## 3-2. 백준 1655
