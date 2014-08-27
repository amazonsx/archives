#include <iostream>
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
    int minDepth( TreeNode *root);
};

int Solution::minDepth( TreeNode *root) {
    if (!root)  return 0;
    queue<TreeNode*> levelTra;
    levelTra.push(root);
    levelTra.push(NULL);

    int count = 0;
    TreeNode *current = NULL;
    while ( !levelTra.empty() ) {
       count ++;
       while ( levelTra.front()) {
           current = levelTra.front();
           if ( (!current->left) && (!current->right) )
               return count;
           if (current->left)
               levelTra.push(current->left);
           if (current->right)
               levelTra.push(current->right);
           levelTra.pop();
       }
       levelTra.pop();
       if (levelTra.empty())    break;
       levelTra.push(NULL); 
    }
    return count;
}

int main(int argc, char *argv[]) {
	return 1;
}
