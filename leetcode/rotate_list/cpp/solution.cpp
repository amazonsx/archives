#include <iostream>
#include <stdlib.h>
#define DEBUG
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k);
};

ListNode* Solution::rotateRight(ListNode *head, int k) {
    if (k == 0) return head;
    ListNode* cursor = head, *end = NULL;
    int len = 0;
    while (cursor != NULL) {
        end = cursor;
        cursor = cursor->next;
        len ++;
    }
    if (len == 0)   return NULL;
    if (len == 1)   return head;
    k = k % len;
    k = len - k;
    cursor = head;
    while (k != 0) {
        cursor = head;
        head = head->next; 
        end->next = cursor;
        end = end->next;
        k --;
    }
    end->next = NULL;
    return head;
}

int main(int argc, char *argv[]) {
    Solution s;
    int len = rand()%40;
    cout << "List len is ---- " << len << endl;
    ListNode *former = NULL, *head = NULL;
    for (int i = 0; i < len; i ++) {
        int val = rand()%73;
        ListNode *node = new ListNode(val);
        if (former != NULL) 
            former->next = node;
        if (!head)
            head = node;
        former = node;
        cout << val << "   ";
    }
    cout << endl;
    former->next = NULL;

    ListNode *res = NULL;
    res = s.rotateRight(head, 20);
    head =res;
    while (res != NULL) {
        cout << res->val << "   ";
        res = res->next;
    }
    cout << endl;

    res = s.rotateRight(head, 60);
    head =res;
    while (res != NULL) {
        cout << res->val << "   ";
        res = res->next;
    }
    cout << endl;

    res = s.rotateRight(head, 0);
    head =res;
    while (res != NULL) {
        cout << res->val << "   ";
        res = res->next;
    }
    cout << endl;

    ListNode *tmp = new ListNode(1);
    res = s.rotateRight(tmp, 1);
    cout << res->val << endl;

	return 1;
}

