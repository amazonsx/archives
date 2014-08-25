#include <iostream>
#include <vector>
#include <queue>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    bool recTree(vector<int> &preorder, int &current,
            vector<int> &inorder, int left, int right,
            bool &match, TreeNode **root);
public:
    TreeNode *buildTree( vector<int> &preorder, vector<int> &inorder);
    void bfs(TreeNode *root);
};

TreeNode* Solution::buildTree( vector<int> &preorder, vector<int> &inorder) {
    if (preorder.empty())   return NULL;
    if (inorder.empty())   return NULL;
    TreeNode *head = NULL;
    bool match = true;
    int current = 0;
    bool flag = recTree( preorder, current, inorder, 0, (signed)inorder.size()-1, match, &head);
    return head;
}

void Solution::bfs( TreeNode *root) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *current = q.front();
        q.pop();
        if (current) {
            cout << current->val << " ";
            q.push(current->left);
            q.push(current->right);
        } else {
            cout << "#" << " ";
        }
    }
    cout << endl;
}

bool Solution::recTree(vector<int> &preorder, int &current, 
        vector<int> &inorder, int left, int right,
        bool &match, TreeNode **root) {
    if ( left > right) {
        match = false;
        return true;
    }
    if (left == right) {
        if ( preorder[current] == inorder[left]){
            *root = new TreeNode(inorder[left]);
            return true;
        }
        else {
            current --;
            return false;
        }
    }
    for ( int i = left; i <= right; i ++) {
        if (inorder[i] != preorder[current])    continue;
        *root = new TreeNode(inorder[i]);
        TreeNode *leftNode = NULL, *rightNode = NULL;
        bool match = true;
        bool flag = recTree( preorder, ++current, inorder, left, i-1, match, &leftNode);
        if (!flag) {
            current ++;
            continue;
        }
        if (!match) {
            current --;
            match = true;
        }
        flag = recTree( preorder, ++current, inorder, i+1, right, match, &rightNode);
        if (!flag) {
            delete *root;
            if ( rightNode) {
                delete rightNode;
                current ++;
            }
            continue;
        }
        if (!match) current --;
        (*root)->left = leftNode;
        (*root)->right = rightNode;
        return true;
    }
    current ++;
    return false;
}

int main(int argc, char *argv[]) {
    Solution s;
    int arr1[] = { 2, 6, 1, 4, 3, 3, 5, 6};
    int arr2[] = { 1, 2, 6, 3, 4, 3, 5, 6};

    vector<int> inorder(arr1, arr1+sizeof(arr1)/sizeof(int));
    vector<int> preorder(arr2, arr2+sizeof(arr2)/sizeof(int));
    TreeNode *root = s.buildTree( preorder, inorder);
    s.bfs(root);
    return 1;
}
