#include <iostream>
#include <assert.h>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
};

class Solution {
private:
    TreeNode* porderTra(TreeNode *current, TreeNode *root);
public:
    void flatten( TreeNode *root);
};
TreeNode* Solution::porderTra(TreeNode *current, TreeNode *root) {
    TreeNode *left = root->left;
    TreeNode *right = root->right;
    if (current) current->right = root;
    else current = root;

    root->left = NULL;
    root->right = NULL;

    TreeNode *last = root;
    if ( left != NULL)
        last = porderTra(last, left);
    if ( right != NULL)
        last = porderTra(last, right);
    return last;
}

void Solution::flatten( TreeNode *root) {
    if (!root)  return;
    porderTra( NULL, root);
}

int main(int argc, char *argv[]) {
    TreeNode node(0);
    Solution s;
    s.flatten(&node);
    TreeNode *current = &node;
    while (current) {
        cout << current->val << " ";
        assert(current->left == NULL);
        current = current->right;
    }
    cout << endl;
	return 1;
}
