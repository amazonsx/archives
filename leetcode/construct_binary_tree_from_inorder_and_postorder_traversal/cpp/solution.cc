#include <iostream>
#include <queue>
#include <vector>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
    private:
        bool recTree( vector<int> &inorder, int left, int right, 
                vector<int> &postorder, int &current, TreeNode **root, bool &match);
    public:
        void bfs( TreeNode *root);
        TreeNode *buildTree( vector<int> &inorder, vector<int> &postorder);
};

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

bool Solution::recTree( vector<int> &inorder, int left, int right, 
        vector<int> &postorder, int &current, TreeNode **root, bool &match) {
    if ( left > right) {
        match = false;
        return true;
    }
    if ( left == right ) {
        if (postorder[current] != inorder[left]) {
            current ++;
            return false;
        }
        *root = new TreeNode(postorder[current]);
        return true;
    }
    for ( int i = left; i <= right; i ++) {
        if ( inorder[i] != postorder[current])  continue;
        *root = new TreeNode(postorder[current]);
        TreeNode *rightNode = NULL, *leftNode = NULL;
        bool match = true;
        bool flag = recTree( inorder, i+1, right, 
                postorder, --current, &rightNode, match);
        if (!flag) { 
            delete *root;
            continue; 
        }
        if (!match) {
            current ++;
            match = true;
        }
        flag = recTree(inorder, left, i-1, postorder, --current, &leftNode, match);
        if ( !flag) {
            delete *root;
            if (rightNode) {
                delete rightNode;
                current ++;
            }
            continue;
        }
        if (!match) { 
            current ++;
        }
        (*root)->left = leftNode;
        (*root)->right = rightNode;
        return true;
    }
    current ++;
    return false;
}

TreeNode *Solution::buildTree( vector<int> &inorder, vector<int> &postorder) {
    if (inorder.empty())  return NULL;
    if (postorder.empty())  return NULL;
    TreeNode *head = NULL;
    bool match = true;
    int current = (signed)postorder.size() - 1;
    bool flag = recTree( inorder, 0, (signed)inorder.size()-1, 
            postorder, current, &head, match);
    return head;
}

int main(int argc, char *argv[]) {
    Solution s;
    //int arr1[] = { 2, 6, 1, 4, 3, 3, 5, 6};
    //int arr2[] = { 6, 2, 3, 4, 6, 5, 3, 1};
    
    int arr1[] = { 2, 1};
    int arr2[] = { 2, 1};

    vector<int> inorder(arr1, arr1+sizeof(arr1)/sizeof(int));
    vector<int> postorder(arr2, arr2+sizeof(arr2)/sizeof(int));

    TreeNode *root = s.buildTree(inorder, postorder);
    s.bfs(root);
    return 1;
}

