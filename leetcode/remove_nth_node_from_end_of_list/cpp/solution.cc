#include <iostream>
#include <assert.h>
#define DEBUG
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL){};
};

class Solution {
    public:
        ListNode *removeNthFromEnd( ListNode *head, int n);
};

ListNode* Solution::removeNthFromEnd( ListNode *head, int n) {
    if (!head)  return NULL;
    ListNode *end = head;
    for ( int i = 1; i < n; i ++) {
        end = end->next;
    }
    ListNode *former = NULL;
    assert(end != NULL);
    while ( end->next ) {
        end = end->next;
        if (former == NULL)  former = head;
        else    former = former->next;
    }
    if (former) {
        former->next = former->next->next;
    } else {
        head = head->next;
    }
    return head;
}

int main(int argc, char *argv[]) {
    ListNode node(1);
    ListNode node1(2);
    node.next = &node1;
    Solution s;
    ListNode *head = s.removeNthFromEnd( &node, 1);
    while (head) {
        cout << head->val << "  ";
        head = head->next;
    }
    cout << endl;

    return 1;
}
