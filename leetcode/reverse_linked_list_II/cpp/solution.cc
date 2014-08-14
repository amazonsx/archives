#include <iostream>
#include <stdlib.h>
#define DEBUG
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x):val(x), next(NULL){}
};

class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n);
};

ListNode *Solution::reverseBetween( ListNode *head, int m, int n) {
    if (!head)  return NULL; 
    if ( m == n)    return head;

    ListNode *nodeM = NULL, *left = NULL, *mid = NULL, *right = NULL;
    ListNode *current = head;
    
    int i = 0;
    for (; i < m; i ++) {
        nodeM = current;
        current = current->next;
    }
    ListNode *former = nodeM, *next = NULL;
    for (; i < ((m+n)>> 1)-1; i ++) {
        next = current->next;
        current->next = former;
        former = current;
        current = next;
    }
    if ((m-n) > 1)  mid = current;
    else mid = nodeM;
    right = mid->next;
    mid->next = former;

    if ((m+n)%2 == 0)  left = mid->next;
    else    left = mid;
    
    ListNode *currentL = left, *currentR = right;
    former = mid;
    for ( int j = 0; j < (n-m+1)/2; j ++) {
        int tmp = currentL->val;
        currentL->val = currentR->val;
        currentR->val = tmp;

        next = currentL->next;
        former = currentL;
        if ( currentL != former) {
            currentL->next = former;
        }
        currentL = next;
        currentR = currentR->next;
    }
    mid->next = right;
    return head;
}

int main(int argc, char *argv[]) {
    ListNode n1(1);
    ListNode n2(2);
    ListNode n3(3);
    ListNode n4(4);
    ListNode n5(5);
    ListNode n6(6);
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    n5.next = &n6;

    Solution s;
    ListNode *head = s.reverseBetween(&n1, 1, 2);
    while (head) {
        cout << head->val << "  " ;
        head = head->next;
    }
    cout << endl;
	return 1;
}
