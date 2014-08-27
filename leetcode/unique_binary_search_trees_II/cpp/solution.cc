#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x):val(x), left(NULL), right(NULL) {}
};

class Solution {
    private:
        vector<TreeNode*> buildBST( int begin, int end);
    public:
        vector<TreeNode *> generateTrees(int n);
};

vector<TreeNode*> Solution::buildBST( int begin, int end) {
    vector<TreeNode*> res;
    if ( begin > end)   return res;
    if ( begin == end ) {
        TreeNode* node = new TreeNode(begin);
        res.push_back(node);
        return res;
    }
    for ( int i = begin; i <= end; i ++) {
        vector<TreeNode*> leftV = buildBST( begin, i-1);
        vector<TreeNode*> rightV = buildBST( i+1, end);
        for ( int j = 0; j < (signed)leftV.size(); j ++) {
            for ( int k = 0; k < (signed)rightV.size(); k ++) {
                TreeNode* node = new TreeNode(i);
                res.push_back(node);
                node->left = leftV[j];
                node->right = rightV[k];
            }
        }
        if ( leftV.empty()) {
            for ( int k = 0; k < (signed)rightV.size(); k ++) {
                TreeNode* node = new TreeNode(i);
                res.push_back(node);
                node->right = rightV[k];
            }
        }
        if ( rightV.empty() ) {
            for ( int j = 0; j < (signed)leftV.size(); j ++) {
                TreeNode* node = new TreeNode(i);
                res.push_back(node);
                node->left = leftV[j];
            }
        }
    }
    return res;
}

vector<TreeNode *> Solution::generateTrees(int n) {
    // this line may not ok for all compilers
    if (n == 0) return vector<TreeNode*>(1, NULL);
    return buildBST(1, n);
}

int main(int argc, char *argv[]) {
    Solution s;
    vector<TreeNode*> res = s.generateTrees(0);
    cout << res.size() << endl;
    return 1;
}
