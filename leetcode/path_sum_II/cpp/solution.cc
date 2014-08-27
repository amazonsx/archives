#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode( int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int> > pathSum( TreeNode *root, int sum);
};

vector<vector<int> > Solution::pathSum(TreeNode *root, int sum) {
    vector<vector<int> > res;
    if (!root)  return res;
    queue<TreeNode*> levTra;
    levTra.push(root);
    TreeNode *current = NULL;

    while (!levTra.empty()) {
        current = levTra.front();
        levTra.pop();
        if (current->left) {
            current->left->val += current->val;
            levTra.push(current->left);
        }
        if (current->right) {
            current->right->val += current->val;
            levTra.push(current->right);
        }
    }
    vector<int> path;
    stack<TreeNode*> depthTra;
    depthTra.push(root);
    stack<int> posStack;
    while ( !depthTra.empty() ) {
        current = depthTra.top();
        path.push_back(current->val);
        depthTra.pop();
        if (!current->right && !current->left) {
            if ( current->val == sum) {
                res.push_back(path);
                for ( int i = (signed)res.back().size()-1; i > 0; i --) {
                   res.back()[i] -= res.back()[i-1];
                }
            }
            if (!posStack.empty()) {
                path.erase( path.begin() + posStack.top(), path.end());
                posStack.pop();
            }
        }

        if ( current->right )
            depthTra.push(current->right);
        if ( current->left )
            depthTra.push(current->left);
        if ( current->right && current->left)
            posStack.push(path.size());
    }
    return res;
}

int main(int argc, char *argv[]) {
    TreeNode node(-2);
    TreeNode node1(-3);
    node.right = &node1;
    Solution s;
    vector<vector<int> > res = s.pathSum(&node, -5);
    for ( int i = 0; i < (signed)res.size(); i ++) {
        for ( int j = 0; j < (signed)res[i].size(); j ++) {
            cout << res[i][j] << "  ";
        }
        cout << endl;
    }
	return 1;
}
