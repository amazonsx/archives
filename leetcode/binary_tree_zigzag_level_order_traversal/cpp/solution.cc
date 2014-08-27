#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
        vector<vector<int> > zigzagLevelOrder(TreeNode *head);
};

vector<vector<int> > Solution::zigzagLevelOrder(TreeNode *head) {
    vector<vector<int> > res;
    if (!head)  return res;
    queue<TreeNode*> levelTra;
    levelTra.push(head);
    levelTra.push(NULL);
    int direction = 0;
    TreeNode *current = NULL;
    stack<TreeNode*> levelStack;
    while (!levelTra.empty()) {
        vector<int> level;
        while (levelTra.front()) {
            current = levelTra.front();
            if (direction == 0) {
                if (current->left)
                    levelStack.push(current->left);
            }
            if (current->right)
                levelStack.push(current->right);
            if (direction == 1) {
                if (current->left)
                    levelStack.push(current->left);
            }
            levelTra.pop();
            level.push_back(current->val);
        }
        while ( !levelStack.empty() ) {
            levelTra.push(levelStack.top());
            levelStack.pop();
        }
        direction = 1 - direction;
        levelTra.pop();
        res.push_back(level);
        if (levelTra.empty())   break;
        levelTra.push(NULL);
    }
    return res;
}

int main(int argc, char *argv[]) {
    TreeNode n0(1);
    TreeNode n1(2);
    n0.left = &n1;
    Solution s;
    vector<vector<int> > res = s.zigzagLevelOrder(&n0);
    for ( int i = 0; i < (signed)res.size(); i ++) {
        for ( int j = 0; j < (signed)res[i].size(); j ++) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    return 1;
}
