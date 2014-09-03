#include <iostream>
#include <vector>
#include <stack>
#define DEBUG
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL){}
};

class Solution {
	public:
		vector<int> preorderTraversal(TreeNode *root);
};
vector<int> Solution::preorderTraversal(TreeNode *root){
	vector<int> res;
	if (!root) return res;
	stack<TreeNode*> s_tree;
	s_tree.push(root);
	TreeNode *current = NULL;
	while (!s_tree.empty()) {
		current = s_tree.top();
		s_tree.pop();
		res.push_back(current->val);
		if (current->right) s_tree.push(current->right);
		if (current->left) s_tree.push(current->left);
	}
	
	return res;
}

int main(int argc, char *argv[]) {
    TreeNode t_3(3);
    TreeNode t_2(2);
    TreeNode t_1(1);
    t_1.right = &t_2;
    t_2.left = &t_3;
	Solution s;
    vector<int> res = s.preorderTraversal(&t_1);
    for (int i = 0; i < res.size(); i ++ ) 
        cout << res[i] << "  ";
    cout << endl;
	return 1;
}
