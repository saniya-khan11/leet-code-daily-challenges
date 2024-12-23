/*
2471. Minimum Number of Operations to Sort a Binary Tree by Level
You are given the root of a binary tree with unique values.

In one operation, you can choose any two nodes at the same level and swap their values.

Return the minimum number of operations needed to make the values at each level sorted in a strictly increasing order.

The level of a node is the number of edges along the path between it and the root node.

 

Example 1:


Input: root = [1,4,3,7,6,8,5,null,null,null,null,9,null,10]
Output: 3
Explanation:
- Swap 4 and 3. The 2nd level becomes [3,4].
- Swap 7 and 5. The 3rd level becomes [5,6,8,7].
- Swap 8 and 7. The 3rd level becomes [5,6,7,8].
We used 3 operations so return 3.
It can be proven that 3 is the minimum number of operations needed.
Example 2:


Input: root = [1,3,2,7,6,5,4]
Output: 3
Explanation:
- Swap 3 and 2. The 2nd level becomes [2,3].
- Swap 7 and 4. The 3rd level becomes [4,6,5,7].
- Swap 6 and 5. The 3rd level becomes [4,5,6,7].
We used 3 operations so return 3.
It can be proven that 3 is the minimum number of operations needed.
Example 3:


Input: root = [1,2,3,4,5,6]
Output: 0
Explanation: Each level is already sorted in increasing order so return 0.
 

Constraints:

The number of nodes in the tree is in the range [1, 105].
1 <= Node.val <= 105
All the values of the tree are unique.
*/
#include<iostream>
#include<vector>
#include <map>
#include <queue>
#include <algorithm> // For sort
using namespace std;

 //Definition for a binary tree node.
 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
 
class Solution {
    int findMinSwaps(vector<int>& values){
        int min_swaps=0;
        //stor k->value....v->Actual_Idx ordered map
        map<int,int> sorted_map;
        int n=values.size();
        for(int j=0;j<n;++j){
            sorted_map[values[j]]=j;
        }
        //sort the array to know the expected index
        sort(values.begin(),values.end());

        vector<bool> visited(n,false);//This marks already processed indices
        int iteration=0;//Row number of Map
        for (auto it = sorted_map.begin(); it != sorted_map.end(); ++it) {
    int val = it->first;
    int idx = it->second;
            if(visited[idx]){
                iteration++;
                continue;
            }
            visited[idx]=true;
            int len =1;//find length of cycle
            while(idx != iteration){
                idx = sorted_map[values[idx]];
                visited[idx]=true;
                len++;
            }
            min_swaps += len-1;//add no of swaps for the current iteration
            iteration++;
        }
        return min_swaps;
    }
    
public:
    int minimumOperations(TreeNode* root) {
        queue<TreeNode*>q;
        q.push(root);

        int min_swaps = 0;
        while(!q.empty()){
            int size=q.size();
            vector<int> values;

            for(int i=0;i<size;++i){
                TreeNode* curr = q.front();
                q.pop();

                values.push_back(curr->val);
                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);
            }
            min_swaps += findMinSwaps(values);

        }   
        return min_swaps;   
    }
    };
    int main(){
        return 0;
    }