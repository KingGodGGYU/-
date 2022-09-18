//C++������ �켱���� ť ���(STL �̿�)
#include <iostream>
#include <queue>
using namespace std;

int main() {
	//�ִ���
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

	//�ּ���
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
