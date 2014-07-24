#include <iostream>
#include <stack>
#include <map>
#include <sys/time.h>
#include <limits>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int maxPathSum(TreeNode *root);
};

int Solution::maxPathSum(TreeNode *root) {
    if (root == NULL)   return 0;
    map< TreeNode*, int> branchMax, branchSum;

    TreeNode *current = NULL, *last = NULL;
    stack<TreeNode*> nodeStack; 
    nodeStack.push(root);
    while ( !nodeStack.empty() ) {
        current = nodeStack.top();
        if ((last == current->left)) {
            if (last) {
                branchMax[current] = current->val;
                if (branchMax[last] > 0)
                    branchMax[current] += branchMax[last];
            } else branchMax[current] = current->val;
            if (current->right != NULL) {
                nodeStack.push(current->right);
                last = NULL;
            } else {
                nodeStack.pop();
                branchSum[current] = branchMax[current];
                last = current;
            }
        } else if (last && (last == current->right)) {
            if (branchMax[last] > 0) {
                branchSum[current] = branchMax[current] + branchMax[last];
                branchMax[current] = (branchMax[current] >= (branchMax[last]+current->val))?
                    branchMax[current]:(branchMax[last]+current->val);
            } else {
                branchSum[current] = branchMax[current];
            }
            nodeStack.pop();
            last = current;
        } else {
            while ( current->left != NULL) {
                nodeStack.push(current->left);
                current = current->left;
            }
        }
    }
    int max = numeric_limits<int>::min();
    for ( map<TreeNode*, int>::iterator iter= branchSum.begin();
            iter != branchSum.end();
            iter ++) {
        if (iter->second > max)
            max = iter->second;
    }
    return max;
}

int main(int argc, char *argv[]) {
    Solution s;
    /*
    */
    TreeNode root(2);    
    TreeNode left(-1);
    TreeNode right(-2);
    root.left = &left;
    root.right = &right;
    /*
    TreeNode root(1);    
    TreeNode left(2);
    TreeNode right(3);
    root.left = &left;
    root.right = &right;
    */
    /*
    TreeNode root(1);    
    TreeNode left(-2);
    TreeNode right(3);
    root.left = &left;
    root.right = &right;
    */

    struct timeval first;
    gettimeofday(&first, NULL);
    cout << s.maxPathSum(&root) << endl;
    struct timeval second;
    gettimeofday(&second, NULL);
    cout << "Time cost is ---- " 
        << 1000000 * (second.tv_sec - first.tv_sec) + second.tv_usec - first.tv_usec << endl;
	return 1;
}
