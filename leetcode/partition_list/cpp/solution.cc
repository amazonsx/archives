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
        ListNode *partition(ListNode *head, int x);
};

ListNode *Solution::partition(ListNode *head, int x) {
    if (!head)  return NULL;
    ListNode *current = NULL;
    ListNode *cursor = head, *former = NULL;
    while (cursor) {
        if (cursor->val < x) {
            if (former) {
                if (former != current) {
                    former->next = cursor->next;
                    if ( current) {
                        cursor->next = current->next;
                        current->next = cursor;
                        current = current->next;
                    } else {
                        cursor->next = head;
                        head = cursor;
                        current = head;
                    }
                } else {
                    former = former->next;
                    current = current->next;
                }
            } else {
                current = cursor;
                former = cursor;
            }
        } else {
            former = cursor;
        }
        cursor = former->next;
    }
    return head;
}

int main(int argc, char *argv[]) {
       ListNode node0(1);
       ListNode node1(4);
       ListNode node2(3);
       ListNode node3(2);
       ListNode node4(5);
       ListNode node5(2);
       node0.next = &node1;
       node1.next = &node2;
       node2.next = &node3;
       node3.next = &node4;
       node4.next = &node5;
    /*
    ListNode node0(1);
    ListNode node1(1);
    node0.next = &node1;
    */
    Solution s;
    ListNode *head = s.partition(&node0, 3);
    //ListNode *head = s.partition(&node0, 2);
    while (head) {
        cout << head->val << "  ";
        head = head->next;
    }
    cout << endl;
    return 1;
}
