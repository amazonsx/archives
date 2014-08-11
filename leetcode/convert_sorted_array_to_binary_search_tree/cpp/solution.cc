#include <iostream>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x):val(x), left(NULL), right(NULL){}
};

class Solution {
private:
    TreeNode *convert(vector<int> &num, int start, int end);
public:
    TreeNode *sortedArrayToBST(vector<int> &num);
};

TreeNode* Solution::convert(vector<int> &num, int start, int end) {
    if ( start > end)   return NULL;
    int mid = (start + end) >> 1;
    TreeNode *root = new TreeNode(num[mid]);

    if (start < end) {
        TreeNode *left = convert(num, start, mid-1);
        TreeNode *right = convert(num, mid+1, end);
        root->left = left;
        root->right = right;
    }

    return root;
}

TreeNode* Solution::sortedArrayToBST(vector<int> &num) {
    if (num.empty())    return NULL;
    return convert(num, 0, num.size()-1);
}

int main(int argc, char *argv[]) {
	return 1;
}
