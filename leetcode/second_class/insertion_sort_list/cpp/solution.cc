#include <iostream>
#define DEBUG
using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    struct ListNode(int x):val(x), next(NULL){}
};

class Solution {
public:
    ListNode *insertionSortList(ListNode *head);
};

ListNode* Solution::insertionSortList(ListNode *head) {
    if (!head)  return NULL;
    ListNode *current = head->next, *former = head, *cursor = head;
    while (current != NULL) {
        if (current->val < former->val) {
            cursor = head;
            while (cursor->val < current->val)
                cursor = cursor->next;
            int tmp = cursor->val;
            cursor->val = current->val;
            cursor = cursor->next;
            while (cursor != current) {
                int c_val = cursor->val;
                cursor->val = tmp;
                tmp = c_val;
                cursor = cursor->next;
            }
            cursor->val = tmp;
        }
        former = current;
        current = current->next;
    }
    return head;
}

int main(int argc, char *argv[]) {
	return 1;
}
