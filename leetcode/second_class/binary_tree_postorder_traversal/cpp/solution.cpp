#include <iostream>
#include <stack>
#include <vector>
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
		vector<int> postorderTraversal(TreeNode *root);
};
vector<int> Solution::postorderTraversal(TreeNode *root ) {
	vector<int> res;
	if (!root) return res;
	TreeNode *current = root;
	stack<TreeNode*> s_tree;
	while (current) {
		s_tree.push(current);
		current = current->left;
	}
	TreeNode *last_visited = NULL;
	while (!s_tree.empty()) {
		current = s_tree.top();
		if (((!current->left) && (!current->right)) 
				|| ((!current->right) && (current->left) && (last_visited == current->left))
				|| ((current->right) && (last_visited == current->right))) {
			s_tree.pop();
			last_visited = current;
			res.push_back(current->val);
			continue;
		}
		if (current->right) {
			current = current->right;
			while (current) {
				s_tree.push(current);
				current = current->left;
			}
		}
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
    vector<int> res = s.postorderTraversal(&t_1);
    for (unsigned int i = 0; i < res.size(); i ++ ) 
        cout << res[i] << "  ";
    cout << endl;
	return 1;
}
