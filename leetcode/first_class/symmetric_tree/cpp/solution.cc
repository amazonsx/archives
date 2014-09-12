#include <iostream>
#include <queue>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x):val(x), left(NULL), right(NULL){}
};

class Solution {
private:
    bool searchRecursive(TreeNode *t1, TreeNode *t2);
    bool searchIterative(TreeNode *t1, TreeNode *t2);
public:
    bool isSymmetric(TreeNode *root);
};

bool Solution::searchIterative(TreeNode *t1, TreeNode *t2) {
    queue<TreeNode*> q1, q2;
    q1.push(t1);
    q2.push(t2);
    TreeNode *left = NULL, *right = NULL;
    while (! q1.empty()) {
        if (q2.empty()) return false;
        left = q1.front();
        right = q2.front();
        q1.pop();
        q2.pop();
        if (left == NULL) {
            if (right == NULL)  continue;
            else return false;
        } else {
            if (right == NULL)  return false;
        }
        if (left->val != right->val) return false;
        q1.push(left->left);
        q2.push(right->right);
        q1.push(left->right);
        q2.push(right->left);
    }

    if (!q2.empty())    return false;
    return true;
}

bool Solution::searchRecursive(TreeNode *t1, TreeNode *t2) {
    if (t1 == NULL) {
        if (t2 == NULL) return true;
        else return false;
    } else {
        if (t2 == NULL) return false;
    }
    bool flag = true;
    if (t1->val == t2->val) {
        bool flag1 = searchRecursive(t1->left, t2->right);
        bool flag2 = searchRecursive(t1->right, t2->left);
        flag = flag1 && flag2;
    } else return false;
    return flag;
}

bool Solution::isSymmetric(TreeNode *root) {
    if (!root)  return true;
    //return searchRecursive(root->left, root->right);
    return searchIterative(root->left, root->right);
}

int main(int argc, char *argv[]) {
    TreeNode t1(1);
    TreeNode t2(2);
    TreeNode t3(2);
    TreeNode t4(3);
    TreeNode t5(5);
    t1.left = &t2;
    t1.right = &t3;
    t2.right = &t4;
    t3.left = &t5;

    Solution s;
    cout << s.isSymmetric(&t1) << endl;
	return 1;
}
