#include <iostream>
#include <queue>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

class Solution {
    public:
        void recoverTree(TreeNode *root);
};

void Solution::recoverTree(TreeNode *root){
    if (root == NULL)   return;
    int former = root->val;  
    queue<TreeNode*> traversal;
    if (root->left) traversal.push(root->left);
    if (root->right) traversal.push(root->right);

    TreeNode *tmp = NULL;
    while(!traversal.empty()) {
        tmp = traversal.front();
        traversal.pop();
        if ((tmp->val-former)!= 1)
            tmp->val = former + 1;
        former = tmp->val;
        if (tmp->left)  traversal.push(tmp->left);
        if (tmp->right)  traversal.push(tmp->right);
    }
}

int main(int argc, char *argv[]) {
    TreeNode head(1);
    TreeNode n1(5);
    TreeNode n2(3);
    head.left = &n1;
    head.right = &n2;

    TreeNode n3(4);
    TreeNode n4(2);
    n2.left = &n3;
    n3.right = &n4;
    Solution s;
    s.recoverTree(&head);

    queue<TreeNode*> traversal;
    traversal.push(&head);
    while(!traversal.empty()) {
        if (traversal.front() == NULL) {
            cout << "#" << " " ;
        } else {
            cout << traversal.front()->val << " ";
            traversal.push(traversal.front()->left);
            traversal.push(traversal.front()->right);
        }
        traversal.pop();
    }

    return 1;
}


