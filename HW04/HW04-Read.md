# Week 4
## 1. Data structures augmentation 코딩   
- Rank 구현
- AVL tree 구현 
## 2. AVL tree 정의 등 강의 내용 정리
### AVL Tree 란?
AVL 트리는 스스로 균형을 맞추는 이진탐색트리로, 는 왼쪽과 오른쪽 서브 트리의 높이 차이가 최대 1이다. 트리의 높이가 h 일때 시간복잡도는 O(h)이다. 
* 이진 탐색 트리의 속성을 가짐
* 왼쪽, 오른쪽 서브 트리의 높이 차이가 최대 1
* 높이 차이가 1보다 커지면 회전을 통해 높이 차이를 줄임
* 높이를 log N으로 유지하므로 삽입, 검색, 삭제의 시간 복잡도는 O(log N)
### AVL 트리를 사용하는 이유
대부분의 이진 탐색 트리의 동작들(탐색, 최대, 최소, 삽입, 삭제, 등등)의 시간복잡도는 높이가 h일 때 __O(h)__ 이다. 이진 탐색 트리의 모양이 한쪽으로 비틀어져 있는 skewed Binary Tree가 되면 동작들의 시간복잡도는 최악일 때 __O(n)__ 이 된다. 그러나 어떤 삭제나 삽입 이후 트리의 높이를 __O(log(n))__ 으로 유지하면, 모든 동작의 시간복잡도는 __O(log(n))__ 으로 보장할 수 있다. 이때 n은 트리내의 노드의 개수이다. 
|연산|평균|최악|
|:---:|---|---|
|접근|O(log N)|O(log N)|
|검색|O(log N)|O(log N)|
|삽입|O(log N)|O(log N)|
|삭제|O(log N)|O(log N)|
### 회전
AVL트리는 이진 탐색 트리이기 때문에 삽입과 삭제 연산도 이진 탐색 트리에서 했던 방식 그대로 사용한다. 그러면 AVL의 높이는 어떻게 맞추냐, 바로 __회전__ 이다. 일단 이진 탐색 트리에서 사용하는 삽입 연산을 한 후 균형을 맞춘다. 회전에는 두 방향으로 __Left Rotation__ 과 __Right Rotation__ 이 존재하며 노드의 배열에 따라 4가지 불균형 __(LL, RR, LR, RL)__ 이 발생한다.
> * LL(Left Left) Case
>   * y는 z의 왼쪽 자식 노드이고, x는 y의 왼쪽 자식 노드인 경우 right rotation을 수행한다.
>   * ![LL case](LL.png)
> * RR(Right Right) Case  
>   * y는 z의 오른쪽 자식 노드이고, x는 y의 오른쪽 자식 노드인 경우 left rotation을 수행한다.
>   * ![RR case](RR.png)
> * LR(Left Right) Case
>   * y는 z의 왼쪽 자식 노드이고, x는 y의 오른쪽 자식 노드인 경우 left, right 순으로 총 두 번의 rotation을 수행한다.
>   * ![LR case](LR.png)
> * RL(Right Left) Case
>   * y는 z의 오른쪽 자식 노드이고, x는 y의 왼쪽 자식 노드인 경우, right, left 순으로 총 두번의 rotation을 수행한다.
>   * ![RL case](RL.png)  

## 3. Leet code 문제 풀이
```C++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int check(TreeNode* root){
        if(root == NULL) 
            return 0;
        
        int leftSubtree = check(root->left);
        if(leftSubtree == -1) 
            return -1; //왼쪽 서브트리 체크
        
        int rightSubtree = check(root->right);
        if(rightSubtree == -1) 
            return -1; //오른쪽 서브트리 체크
        
        if(abs(leftSubtree - rightSubtree) > 1) 
            return -1; // 오른쪽 서브트리와 왼쪽 서브트리의 차이가 1보다 크면 -1을 반환

        return 1+max(leftSubtree, rightSubtree);
    }
    bool isBalanced(TreeNode* root) {
        return check(root) == -1 ? false : true;
    }
};
```
![Balanced Binary Tree Problem Result](HW04_3.png)  
