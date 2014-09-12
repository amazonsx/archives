#include <iostream>
#include <stack>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool isValidBST( TreeNode *root);
};

bool Solution::isValidBST( TreeNode *root) {
    if (!root)  return true;
    stack<TreeNode*> nodeStack;
    TreeNode *current = root;
    while ( current) {
        nodeStack.push(current);
        current = current->left;
    }
    int last = 0, flag = 0;
    while (!nodeStack.empty()) {
        current = nodeStack.top();
        nodeStack.pop();
        int val = current->val;
        if (current->right) {
            current = current->right;
            while (current) {
                nodeStack.push(current);
                current = current->left;
            }
        }
        if (flag == 1) {
            if (last >= val) return false;
        } else {
            flag = 1;
        }
        last = val;
    }
    return true;
}

int main(int argc, char *argv[]) {
    TreeNode n1(5);
    TreeNode n2(14);
    TreeNode n3(18);
    n1.right = &n2;
    n2.right = &n3;
    Solution s;
    cout << s.isValidBST(&n1) << endl;
	return 1;
}
