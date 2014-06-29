#include <iostream>
#include <queue>
#include <vector>
#define DEBUG
using namespace std;

struct TreeLinkNode {
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};
class Solution {
	private:
		void connect_BFS(TreeLinkNode *root);
	public:
		void connect(TreeLinkNode *root);
};
void Solution::connect(TreeLinkNode *root) {
	if (!root) return;
	TreeLinkNode *left_start = root, *current = root;
	while ( left_start != NULL) {
		current = left_start;
		left_start = current->left;
		while ( current != NULL) {
			if (current->left) {
				current->left->next = current->right;
				if (current->next)
					current->right->next = current->next->left;
			}
			current = current->next;
		}
	}
}
void Solution::connect_BFS(TreeLinkNode *root) {
	if (!root) return;
	queue<TreeLinkNode*> tree_q;
	tree_q.push(root);
	vector<TreeLinkNode*> tree_v;
	TreeLinkNode *tmp;
	while(!tree_q.empty()) {
		tmp = tree_q.front();
		tree_v.push_back(tmp);
		if ( tmp->left != NULL) {
			continue;
		} else {
			int i = 0;
			for (i = 0; i < tree_v.size() - 1; i ++) {
				tree_v[i]->next = tree_v[i+1];
				if (tree_v[i]->left != NULL) {
					tree_q.push(tree_v[i]->left);
					tree_q.push(tree_v[i]->right);
				}
				tree_q.pop();
			}
			tree_v[i]->next = tree_v[i+1];
			if ( tree_v[i]->left != NULL) {
				tree_q.push(tree_v[i]->left);
				tree_q.push(tree_v[i]->right);
			}
			tree_q.pop();
			tree_v.clear();
		}
	}
}


int main(int argc, char *argv[]) {
	Solution s;

	return 1;
}
