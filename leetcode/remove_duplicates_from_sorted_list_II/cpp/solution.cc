#include <iostream>
#define DEBUG
using namespace std;

struct ListNode { 
    int val;
    ListNode* next;
    ListNode(int x):val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *deleteDuplicates( ListNode *head);
};

ListNode* Solution::deleteDuplicates( ListNode *head){
    if (!head)  return NULL;
    ListNode *former = NULL, *current = head, *next = NULL;
    while ( current != NULL) {
        next = current->next;
        if (!next)  break;
        if (current->val != next->val) {
            former = current;
            current = next;
            continue;
        }
        while (next) { 
            if (next->val == current->val) {
                next = next->next;
            } else break;
        }
        if (!former) {
            head = next;
            current = head;
        } else {
            former->next = next;
            current = former->next;
        }
    }
    return head;
}

int main(int argc, char *argv[]) {
    ListNode n1(1);
    ListNode n2(1);
    ListNode n3(2);
    ListNode n4(3);
    ListNode n5(3);
    ListNode n6(7);
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    n5.next = &n6;

    Solution s;
    ListNode *res = s.deleteDuplicates(&n1);
    while (res != NULL) {
        cout << res->val << "  " ;
        res = res->next;
    }
    cout << endl;
	return 1;
}

