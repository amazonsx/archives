#include <iostream>
#include <vector>
#include <queue>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x):val(x), left(NULL), right(NULL){}
};

class Solution {
public:
    vector<vector<int> > levelOrderBottom( TreeNode *root);
};

vector<vector<int> > Solution::levelOrderBottom( TreeNode *root) {
    vector<vector<int> > res;
    if (!root)  return res;

    queue<TreeNode*> traversal;    
    traversal.push(root);
    traversal.push(NULL);

    while ( !traversal.empty() ) {
        vector<int> level;
        while ( traversal.front() != NULL) {
            level.push_back(traversal.front()->val);
            if (traversal.front()->left) 
                traversal.push(traversal.front()->left);
            if (traversal.front()->right) 
                traversal.push(traversal.front()->right);
            traversal.pop();
        }
        traversal.pop();
        res.insert(res.begin(), level);
        if (!traversal.empty())  
            traversal.push(NULL);
    }
    return res;
}

int main(int argc, char *argv[]) {
    TreeNode node1(1);
    TreeNode node2(2);
    node1.left = &node2;
    Solution s;
    vector<vector<int> > res = s.levelOrderBottom(&node1);
    for ( int i = 0; i < (signed)res.size(); i ++) {
        for ( int j = 0; j < (signed)res[i].size(); j ++) {
            cout << res[i][j] << "  " ;
        }
        cout << endl;
    }
	return 1;
}
