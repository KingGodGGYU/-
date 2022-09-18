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
