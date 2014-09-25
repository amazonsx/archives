#include <iostream>
#define DEBUG
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2);
};


ListNode* Solution::addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *cursor1 = l1, *cursor2 = l2, *cursor1_former;
    int carryFlag = 0;
    // I cant even remember why would I do this..
    // cursor1 || cursor2 is a good loop condition
    while (cursor2 != NULL) {
        if (cursor1 == NULL) {
            ListNode *node = new ListNode(0);
            cursor1 = node;
            cursor1_former->next = cursor1;
        }
        int num = cursor1->val + cursor2->val + carryFlag;
        cursor1->val = num%10;
        carryFlag = num/10;
        if (cursor1->next == NULL)  cursor1_former = cursor1;
        cursor1 = cursor1->next;
        cursor2 = cursor2->next;
    }
    while (carryFlag != 0) {
        if (cursor1 == NULL) {
            ListNode *node = new ListNode(carryFlag);
            cursor1_former->next = node;
            carryFlag = 0;
        } else {
            int num = cursor1->val + carryFlag;
            carryFlag = num / 10;
            cursor1->val = num%10;
            if (cursor1->next == NULL)  cursor1_former = cursor1;
            cursor1 = cursor1->next;
        }
    }
    return l1;
}

int main(int argc, char *argv[]) {
    ListNode l1(9);
    ListNode l11(8);
    l1.next = &l11;
    ListNode l2(1);
    /*
    ListNode l1(2);
    ListNode l2(0);
    */
    Solution s;
    ListNode *res = s.addTwoNumbers(&l1, &l2);
    while (res != NULL) {
        cout << res->val << "  ";
        res = res->next;
    }
    cout << endl;
	return 1;
}
