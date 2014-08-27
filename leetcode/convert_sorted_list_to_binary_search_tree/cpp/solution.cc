#include <iostream>
#include <queue>
#define DEBUG
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    TreeNode *midSearch(ListNode *begin, ListNode *end);
public:
    TreeNode *sortedListToBST(ListNode *head);
};

TreeNode* Solution::midSearch( ListNode *begin, ListNode *end) {
    if (begin == NULL)  return NULL;
    if ( (begin->next == end) || (begin == end) ){
        TreeNode *mid = new TreeNode(begin->val);
        return mid;
    }
    ListNode *first = begin, *second = begin;
    while (first != end) {
        second = second->next;
        if (second != end){
            second = second->next;
        } else {
            break;
        }
        first = first->next;
        if (second == end) break;
    }
    TreeNode *mid = new TreeNode(first->val);
    TreeNode *left = midSearch(begin, first);
    TreeNode *right  = NULL;
    if (first->next != end)
        right = midSearch(first->next, end);
    mid->left = left;
    mid->right = right;
    return mid;
}

TreeNode *Solution::sortedListToBST(ListNode *head) {
    if (!head)  return NULL;
    TreeNode *treeHead = midSearch( head, NULL);
    return treeHead;
}

int main(int argc, char *argv[]) {
    /*
    ListNode node0(0);
    ListNode node1(1);
    ListNode node2(2);
    ListNode node3(3);
    ListNode node4(4);
    ListNode node5(5);
    node0.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    */
    /*
    ListNode node1(3);
    ListNode node2(5);
    ListNode node3(8);
    node1.next = &node2;
    node2.next = &node3;
    */
    ListNode node0(-1);
    ListNode node1(0);
    ListNode node2(1);
    ListNode node3(2);
    node0.next = &node1;
    node1.next = &node2;
    node2.next = &node3;
    Solution s;
    TreeNode *root = s.sortedListToBST(&node0);
    queue<TreeNode*> q;
    q.push(root);
    TreeNode *current = NULL;
    while(!q.empty()) {
        current = q.front();
        q.pop();
        if (!current) {
            cout << "#" << "  ";
            continue;
        }
        cout << current->val << "  ";
        q.push(current->left);
        q.push(current->right);
    }
    return 1;
}
