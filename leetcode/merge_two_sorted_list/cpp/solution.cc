#include <iostream>
#define DEBUG
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x):val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode *l1, ListNode *l2);
    
};
ListNode* Solution::mergeTwoLists(ListNode *l1, ListNode *l2){
    if (!l1)    return l2;
    if (!l2)    return l1;
    ListNode *head = NULL;
    ListNode *cursor1 = l1, *cursor2 = l2;
    if (l1->val > l2->val){
        head = l2;
        cursor2 = l2->next;
    } else {
        head = l1;
        cursor1 = l1->next;
    }
    ListNode *current = head;
    while (cursor1 && cursor2) {
        if (cursor1->val > cursor2->val) {
            current->next = cursor2;
            cursor2 = cursor2->next;
        }else {
            current->next = cursor1;
            cursor1 = cursor1->next;
        }
        current = current->next;
    }
    if (cursor1) {
        current->next = cursor1;
    }
    if (cursor2) {
        current->next = cursor2;
    }
    
    return head;
}

int main(int argc, char *argv[]) {
	return 1;
}
