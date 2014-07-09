#include <iostream>
#define DEBUG
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL){}
};
class Solution {
	public:
        ListNode *reverseKGroup(ListNode *head, int k);
};

ListNode* Solution::reverseKGroup(ListNode *head, int k) {
    ListNode *new_group_head = head, *current = head, 
             *tail_to_head = head, *former_prev = NULL,
             *prev = head, *tmp = NULL;
    int count = 0;
    //while ( (count < k) && (new_group_head != NULL)) {
    while ( new_group_head != NULL) {
        tail_to_head = new_group_head;
        int term_early_flag = 0;
        count = 0;
        while (count < k-1) {
            if (tail_to_head->next == NULL) {
                term_early_flag = 1;
                break;
            }
            tail_to_head = tail_to_head->next;
            count ++;
        }
        if (term_early_flag) break;
#ifdef DEBUG
        cout << "end tail res is " << tail_to_head->val << endl;
        cout << "new group head is " << new_group_head->val << endl;
#endif
        current = new_group_head;
        former_prev = prev;
        prev = current;
        new_group_head = tail_to_head->next;
        while ( current != tail_to_head) {
            tmp = tail_to_head->next;
            tail_to_head->next = current;
            current = current->next;
            tail_to_head->next->next = tmp;
        }
        if (prev == head) {
            head = tail_to_head;
        } else {
            former_prev->next = tail_to_head;
        }
    }
    return head;
}

int main(int argc, char *argv[]) {
    int arr[] = {1, 2, 5, 8, 2, 0, 9, 20, -17, 5};
    ListNode head(arr[0]);
    ListNode *prev_p = &head;
    cout << prev_p->val << "   ";
    for (unsigned int i = 1; i < sizeof(arr)/sizeof(int); i ++) {
        ListNode *current = new ListNode(arr[i]);
        prev_p->next = current;
        prev_p = current;
        cout << current->val << "   " ;
    }
    cout << endl;
    Solution s;
    ListNode *res = s.reverseKGroup(&head, 3);
    ListNode *tmp = res;
    while (tmp != NULL) {
    //for (unsigned int i = 0; i < sizeof(arr)/sizeof(int); i ++ ) {
        cout << tmp->val << "   ";
        tmp = tmp->next;
    }
    cout << endl;
	return 1;
}
