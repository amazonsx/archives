#include <iostream>
#include <sys/time.h>
#define DEBUG
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
    public:
        void reorderList(ListNode *head);
};

void Solution::reorderList(ListNode *head) {
    if (!head)  return;
    int listLen = 0;
    ListNode *cursor = head, *mid = head, *prevMid = head;
    while (cursor != NULL) {
        cursor = cursor->next;
        listLen ++;
        if (cursor != NULL) {
            cursor = cursor->next;
            prevMid = mid;
            mid = mid->next;
            listLen ++;
        }
    }
    if (listLen == 1)   return;
    ListNode *nextHalf = NULL;
    prevMid = mid;
    nextHalf = mid->next;
    prevMid->next = NULL;

    cursor = nextHalf;
    nextHalf = NULL;
    ListNode *next = NULL;
    while(cursor != NULL) {
        next = cursor->next;
        cursor->next = nextHalf;
        nextHalf = cursor;
        cursor = next;
    }
    cursor = head;
    while((cursor != NULL) && (nextHalf != NULL)) {
        next = cursor->next;     
        cursor->next = nextHalf;
        nextHalf = nextHalf->next;
        cursor->next->next = next;
        cursor = next;
    }
}

int main(int argc, char *argv[]) {
    Solution s;

    struct timeval first;
    struct timeval second;
    for (int i = 0; i < 10; i ++) {
        ListNode *head = NULL;
        ListNode *cursor = head, *prev = NULL;
        for (int j = 0; j <= i-1; j ++) {
            if (j == 0) {
                head = new ListNode(j);
                cout << j << "    ";
                prev = head;
                continue;
            }
            ListNode *current = new ListNode(j);
            cout << j << "    ";
            prev->next = current;
            prev = current;
        }
        cout << endl;
        cout << "--------" << endl;
        gettimeofday(&first, NULL);
        s.reorderList(head);
        gettimeofday(&second, NULL);
        prev = head;
        while(prev != NULL) {
            cout << prev->val << "    ";
            cursor = prev->next; 
            delete prev;
            prev = cursor;
        }
        cout << endl;
        cout << "The time cost of this procedure is-" 
            << 1000000*(second.tv_sec - first.tv_sec) + (second.tv_usec - first.tv_usec) << endl;
        cout << "--------------------------------" << endl;
        cout << endl;
    }
    return 1;
}
