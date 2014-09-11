#include <iostream>
#include <queue>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum);
};

bool Solution::hasPathSum(TreeNode *root, int sum) {
    if ( !root )    return false;
    queue<TreeNode*> levelTra;
    levelTra.push(root);
    TreeNode *current;
    while (!levelTra.empty()) {
       current = levelTra.front(); 
       levelTra.pop();
       if ( (!current->left) && (!current->right)) {
           if ( current->val == sum)    return true;
       }
       if (current->left){
           current->left->val += current->val;
           levelTra.push(current->left);
       }
       if (current->right){
           current->right->val += current->val;
           levelTra.push(current->right);
       }
    }
    return false;
}

int main(int argc, char *argv[]) {
    TreeNode node(1);
    TreeNode node1(2);
    node.left = &node1;
    Solution s;
    cout << s.hasPathSum(&node, 0) << endl;
	return 1;
}
