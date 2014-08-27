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
public:
    vector<vector<int> > levelOrder(TreeNode *root);
};

vector<vector<int> > Solution::levelOrder(TreeNode *root) {
    vector<vector<int> > res;
    if (!root)  return res;
    queue<TreeNode*> levelTra;
    levelTra.push(root);
    levelTra.push(NULL);
    TreeNode *current = NULL;
    while( !levelTra.empty()) {
        vector<int> level;
        while (levelTra.front()) {
            current = levelTra.front();
            level.push_back(current->val);
            levelTra.pop();
            if (current->left)
                levelTra.push(current->left);
            if (current->right)
                levelTra.push(current->right);
        }
        res.push_back(level);
        levelTra.pop();
        if (levelTra.empty())    break;
        levelTra.push(NULL);
    }
    return res;
}

int main(int argc, char *argv[]) {
    TreeNode node1(1);
    TreeNode node2(2);
    TreeNode node3(3);
    node1.left = &node2;
    node1.right = &node3;
    Solution s;
    vector<vector<int> > res = s.levelOrder(&node1);
    for ( int i = 0; i < (signed)res.size(); i ++) {
        for ( int j = 0; j < (signed)res[i].size(); j ++) 
            cout << res[i][j] << "  ";
        cout << endl;
    }

    return 1;
}
