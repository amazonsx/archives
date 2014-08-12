#include <iostream>
#include <stack>
#define DEBUG
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left, *right; 
    TreeNode(int x):val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int sumNumbers(TreeNode *root);
};

int Solution::sumNumbers(TreeNode *root){
    if (!root)  return 0;
    int sum = 0;
    stack<TreeNode*> nodeStack;
    stack<int> pathStack;
    nodeStack.push(root);
    pathStack.push(0);

    TreeNode *node = NULL;
    while(!nodeStack.empty()) {
        node = nodeStack.top();
        int path = pathStack.top();
        nodeStack.pop();
        pathStack.pop();
        int currentPath = path*10 + node->val;
        if (!(node->left) && !(node->right)) {
            sum += currentPath;
            continue;
        }
        if (node->left) {
            nodeStack.push(node->left);
            pathStack.push(currentPath);
        }
        if (node->right) {
            nodeStack.push(node->right);
            pathStack.push(currentPath);
        }
    }

    return sum;
}

int main(int argc, char *argv[]) {
    TreeNode n1(1);
    TreeNode n2(2);
    TreeNode n3(3);
    n1.left = &n2;
    n1.right = &n3;
    Solution s;
    cout << s.sumNumbers(&n1) << endl;
	return 1;
}
