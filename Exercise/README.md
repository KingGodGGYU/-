### 프로그래머스 
#### 더 맵게
```C++
#include <iostream>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>
using namespace std;

int solution(vector<int> scoville, int K) {
    int count=0;
    priority_queue<int, vector<int>, greater<int>> pq(scoville.begin(), scoville.end());
    while(pq.size()>1&&pq.top()<K){
        int first=pq.top();
        pq.pop();
        int second=pq.top();
        pq.pop();
        pq.push(first+(second*2));
        count++;
    }
    if(pq.top()<K){
        return -1;
    }
    int answer = count;
    return answer;
}
```
```

```
