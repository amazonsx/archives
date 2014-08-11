#include <iostream>
#define DEBUG
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode (int x):val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *swapPairs(ListNode *head);
};

ListNode *Solution::swapPairs(ListNode *head) {
    if (!head)  return NULL;
    ListNode *current = head;
    while (current) {
        if(current->next != NULL) {
            int tmp = current->next->val;
            current->next->val = current->val;
            current->val = tmp;
            current = current->next;
        } 
        current = current->next;
    }

    return head;
}

int main(int argc, char *argv[]) {
	return 1;
}
