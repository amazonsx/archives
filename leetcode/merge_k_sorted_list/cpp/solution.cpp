#include <iostream>
#include <vector>
#define DEBUG
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

class Solution {
    public:
        ListNode* mergeKLists(vector<ListNode*> &lists);
};

ListNode* Solution::mergeKLists(vector<ListNode*> &lists) {
    ListNode *head = NULL, *current = NULL;    
    int k = (signed)lists.size();
    if (k == 0) return NULL;
    vector<ListNode*>::iterator iter;
    while (lists.size() > 1) {
        int minIndex = 0, i = 0, min = lists[0]->val;
        iter = lists.begin();
        while (iter != lists.end()) {
            if ( (*iter) == NULL) {
                iter = lists.erase(iter);
                continue;
            }
            if (min > (*iter)->val)  {
                min = (*iter)->val;
                minIndex = i;
            }
            i ++;
            iter ++;
        }
        ListNode *node = new ListNode(min);
        if (!head) {
            head = node;
        } else {
            current->next = node;
        }
        current = node;
        lists[minIndex] = lists[minIndex]->next;
    }
    if (!lists.empty()) {
        while (lists[0] != NULL) {
            if (!current) head = lists[0];
            else current->next = lists[0];
            current = lists[0];
            lists[0] = lists[0]->next;
        }
    }
    return head;
}

int main(int argc, char *argv[]) {
    return 1;
}
