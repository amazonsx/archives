#include <iostream>
#include <queue>
#define DEBUG
using namespace std;

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    void connect( TreeLinkNode *root);
};

void Solution::connect(TreeLinkNode *root){
    if (!root)  return;
    queue<TreeLinkNode*> traversal;
    traversal.push(root);
    traversal.push(NULL);
    TreeLinkNode *former = NULL, *current = NULL;
    while (!traversal.empty()) {
        former = NULL;
        while (traversal.front()) {
            current = traversal.front();
            traversal.pop();
            if (current->left)  traversal.push(current->left);
            if (current->right)  traversal.push(current->right);
            if (former)
                former->next = current;
            former = current;
        }
        former->next = NULL;
        traversal.pop();
        if (traversal.empty()) break;
        traversal.push(NULL);
    }
}

int main(int argc, char *argv[]) {
	return 1;
}
