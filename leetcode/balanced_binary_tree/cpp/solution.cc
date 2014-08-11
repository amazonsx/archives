#include <iostream>
#include <math.h>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x):val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    bool calHeight(TreeNode *root, int &height);
public:
    bool isBalanced(TreeNode *root);
};

bool Solution::calHeight(TreeNode *root, int &height) {
    if ((root->left == NULL) && (root->right == NULL)) {
        height = 1;
        return true;
    }
    int height1 = 0, height2 = 0;
    bool flag1 = true, flag2 = true;
    if (root->left) {
        flag1 = calHeight(root->left, height1);
    }
    if (root->right) {
        flag2 = calHeight(root->right, height2);
    }
    bool flag = flag1 && flag2;
    if (!flag)  return false;

    height = (height1 > height2)? height1 : height2;
    height ++;
    if (abs(height1 - height2) > 1) return false;

    return true;
}


bool Solution::isBalanced(TreeNode *root) {
    if (!root)  return true;
    int height = 0;
    return calHeight(root, height);
}


int main(int argc, char *argv[]) {
    /*
    TreeNode t1(1);
    TreeNode t2(2);
    TreeNode t3(3);
    t1.right = &t2;
    t2.right = &t3;
    */

    TreeNode t1(1);
    TreeNode t2(2);
    t1.right = &t2;

    Solution s;
    cout << s.isBalanced(&t1) << endl;
    
	return 1;
}

