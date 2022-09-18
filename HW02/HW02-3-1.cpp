#include <iostream>
#include <queue>
using namespace std;
int main() {
    int cnt;
    int testcase;
    int arr = 0;
    cin >> testcase;
    int* order = new int[testcase];
    int N,M,priority;//문서의 개수, 궁금한 문서 현재 Queue에서 몇 번째에 놓여 있는지를 나타내는 정수, N개 문서의 중요도
    for (int i=0; i<testcase; i++){
        cnt=0;
        cin>>N>>M;
        queue<pair<int, int>> q;
        priority_queue<int> pq; // 우선순위 큐
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