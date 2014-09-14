#include <iostream>
#define DEBUG
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
    ListNode(): val(0), next(NULL) {}
};
class Solution {
	public:
        ListNode *deleteDuplicates(ListNode *head);
};

ListNode* Solution::deleteDuplicates(ListNode *head){
    if (head == NULL) return NULL;
    ListNode *cursor = head, *next = NULL;
    int tmp = 0;
    while (cursor) {
        tmp = cursor->val;
        next = cursor->next;
        while ( next && (tmp == next->val) ) {
            next = next->next;
            cursor->next = next;
        }
        cursor = cursor->next;
    }
    return head;
}
int main(int argc, char *argv[]) {
    Solution s;
    int arr[] = { 0, 1, 2, 3, 4, 4, 4, 5, 5};
    ListNode root[9];
    for ( int i = 0; i < 9; i ++) {
        root[i].val = arr[i];
        if (i != 8) {
            root[i].next = root + i + 1;
        }
    }
    ListNode *tmp = root;
    while (tmp) {
        cout << tmp->val << "   " ;
        tmp = tmp->next;
    }
    cout << endl;
    
    tmp = s.deleteDuplicates(root);

    while (tmp) {
        cout << tmp->val << "   " ;
        tmp = tmp->next;
    }
    cout << endl;
	return 0;
}

