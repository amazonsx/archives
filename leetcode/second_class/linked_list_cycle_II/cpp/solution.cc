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
    ListNode *detectCycle( ListNode *head );
};

ListNode *Solution::detectCycle( ListNode *head ) {
    if (!head)  return NULL;
    ListNode *first = head, *second = head;
    while ( first ) {
        first = first->next;
        second = second->next;
        if ( second )    second = second->next;
        else { return NULL; }
        if ( (!first) || (!second) )    return NULL; 
        if ( first == second)  break; 
    }
    first = head;
    while (first != second) {
        ListNode *cursor = second->next;
        while ( cursor != second) {
            if (first == cursor)    return cursor;
            cursor = cursor->next;
        }
        first = first->next;
    }
    if ( first == second)
        return first;
    return NULL;
}

int main(int argc, char *argv[]) {
    ListNode node(1);
    Solution s;
    ListNode *res = s.detectCycle(&node);
    if (res)    cout << res->val<< endl;
    else cout << "NULL" << endl;
	return 1;
}
