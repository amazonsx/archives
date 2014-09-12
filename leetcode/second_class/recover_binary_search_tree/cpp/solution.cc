#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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
    vector<TreeNode*> nodes;
    stack<TreeNode*> traversal;

    TreeNode *current = root, *former = NULL;
    while (current) {
        traversal.push(current);
        former = current;
        current = current->left;
    }
    int formerVal, currVal;
    bool flag = false;
    TreeNode *tmp = NULL;
    while( !traversal.empty()) {
        current = traversal.top();
        traversal.pop();
        currVal = current->val;
        if (!flag) {
            flag = true;
        } else {
            if ( currVal < formerVal) {
                nodes.push_back(former);
                nodes.push_back(current);
            }
        }
        tmp = current->right;
        while (tmp) {
            traversal.push(tmp);
            tmp = tmp->left;
        }
        former = current;
        formerVal = currVal;
    }

    if (nodes.size() == 2) {
        int tmp = nodes[0]->val;
        nodes[0]->val = nodes[1]->val;
        nodes[1]->val = tmp;
    } else if (nodes.size() > 0) {
        int tmp = nodes[0]->val;
        nodes[0]->val = nodes[nodes.size()-1]->val;
        nodes[nodes.size()-1]->val = tmp;
    }

}
int main(int argc, char *argv[]) {
    /*
    TreeNode head(2);
    TreeNode n1(4);
    TreeNode n2(1);
    head.left = &n1;
    head.right = &n2;

    TreeNode n3(3);
    TreeNode n4(5);
    n2.left = &n3;
    n3.right = &n4;
    */
    /*
    TreeNode head(0);
    TreeNode n1(1);
    head.left = &n1;
    */
    TreeNode head(2);
    TreeNode n1(3);
    TreeNode n2(1);
    head.left = &n1;
    head.right = &n2;
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
    cout << endl;

    return 1;
}
