#include <iostream>
#include <vector>
#include <stack>
#include <math.h>
#define DEBUG
using namespace std;

struct TreeNode {
    int index;
    TreeNode *left, *right;
    TreeNode():index(0), left(NULL), right(NULL) {}
    TreeNode(int x):index(x), left(NULL), right(NULL) {}
};

class Solution {
	public:
        int numDecodings(string s);
        //int numDecodings_in_tree(string s);
        int numDecodings_combination(string s);
};
// It won't work like this
int Solution::numDecodings_combination(string s) {
    int len = s.size();
    if (len == 0) return 0;
    if (len == 1) return 1;
    int count = 0;
    for ( int i = 0; i < s.size(); i ++) {
        if ((s[i] >= '3') && (s[i] <= '9')) continue;
        else if ((s[i] == 1) && (i <= (s.size() - 2))) count ++;
        else if ((s[i] == 2) && (i <= (s.size() - 2)) && (s[i+1]<=6)) count ++;
    }
    return pow(2, count);
}

int Solution::numDecodings(string s) {
    int len = s.size();
    if (len == 0) return 0;
    if (len == 1) return 1;
    int count = 0;
    stack<TreeNode*> furcation_s;
    TreeNode root(0);
    TreeNode *current = &root;
    while (current != NULL) {
#ifdef DEBUG
        cout << current->index << endl;
#endif
        if (current->index == (len - 1)) {
            count ++;
            if (furcation_s.size() == 0) {
                current = NULL;
                continue;
            }
            current = furcation_s.top();
            furcation_s.pop();
            continue;
        }
        for ( int i = current->index + 1; i < len; i++ ) {
            if ( ((i <= (len - 2)) &&  (s[i] == '1')) 
                    || ((i <= (len - 2)) && (s[i] == '2') && (s[i+1] <= '6'))) {
                TreeNode *left = new TreeNode(i);
                TreeNode *right = new TreeNode(i+1);
                current->left = left;
                current->right = right;
                furcation_s.push(current->right);
#ifdef DEBUG
                cout << "push a furcation ------------" << current->right->index << endl;
#endif
                current = left;
            } else {
                TreeNode *left = new TreeNode(i);
                current->left = left;
                current = left;
            }
        }
    }
    return count;
}

int numDecodings_uncomplete(string s) {
    int len = s.size();
    if (len == 0) return 0;
    if (len == 1) return 1;
    int count = 0;
    stack<int> str_s;
    stack<int> fct_s; // the second index of a furcation.
    str_s.push(0);
    int current = 0, pop_flag = 0, furcation = 0, end_reach_flag = 0;
    while (!str_s.empty()) {
        current = str_s.top();
        if (fct_s.size() != 0) {
            furcation = fct_s.top();
        } else if (end_reach_flag){
            break;
        }
        if ( current == len ) {
            str_s.pop();
            pop_flag = 1;
            end_reach_flag = 1;
            if (furcation == current) fct_s.pop();
            count ++;
#ifdef DEBUG
            cout << "pop a end char-------" << current  << endl;
#endif
            continue;
        } else if ((pop_flag == 1) && (current >= furcation)) {
            str_s.pop();
#ifdef DEBUG
            cout << "pop a in path char--------" << current  << endl;
#endif
            if (furcation == current) {
                pop_flag = 0;
                fct_s.pop();
#ifdef DEBUG
                cout << "pop a furcation char---------" << furcation  << endl;
#endif
            }
            continue;
        }
        char first = s[current];          
        if ( first >= '3' && first <= '9') {
#ifdef DEBUG
                cout << "push a single char 1"  << endl;
#endif
            str_s.push(current + 1);
        } else {
            if (current <= (len-2)) {
                char second = s[current+1];
                if ( (first == '1')
                        || ((second >= '1')&&(second <= '6'))) {
                    str_s.push(current + 1);
                    str_s.push(current + 2);
                    fct_s.push(current + 1);
#ifdef DEBUG
                cout << "push furcation char-----------------"  << current+1 << endl;
#endif
                    continue;
            } else {
                str_s.push(current+1);
#ifdef DEBUG
                cout << "push a single char 2"  << endl;
#endif
                continue;
            }
        }
        }
    }
    return count;
}


int main(int argc, char *argv[]) {
    Solution s;
    string str("12332411111126");

    cout << s.numDecodings(str) << endl;
    //cout << s.numDecodings_combination(str) << endl;
	return 0;
}
