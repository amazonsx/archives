#include <iostream>
#include <queue>
#include <map>
#define DEBUG
using namespace std;

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x): label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode* head);
};

struct NodeFlag {
    int flag;
    RandomListNode *node;
    NodeFlag():flag(0), node(NULL) {}
    NodeFlag(int x):flag(x), node(NULL) {}
    NodeFlag(int x, RandomListNode *ptr):flag(x), node(ptr) {}
};
RandomListNode* Solution::copyRandomList(RandomListNode* head) {
    if (!head)  return NULL;
    map<int, NodeFlag> nodeMap;
    RandomListNode *cpHead = new RandomListNode(head->label);
    NodeFlag nf(1, cpHead);
    nodeMap[cpHead->label] = nf; 
    if (head->next != NULL) {
        RandomListNode *cpNext = new RandomListNode(head->next->label);
        cpHead->next = cpNext;
        NodeFlag nf(0, cpNext);
        nodeMap[cpNext->label] = nf; 
    }
    if (head->random != NULL) {
        RandomListNode *cpRandom = new RandomListNode(head->random->label);
        cpHead->random = cpRandom;
        NodeFlag nf(0, cpRandom);
        nodeMap[cpRandom->label] = nf; 
    }
    RandomListNode* cursor = head->next, *current = NULL;
    while (cursor != NULL) {
        nodeMap[cursor->label].flag = 1;
        current = nodeMap[cursor->label].node;
        if (cursor->next != NULL) {
            RandomListNode *cpNext;
            if (nodeMap.find(cursor->next->label) == nodeMap.end()) {
                cpNext = new RandomListNode(cursor->next->label);
                NodeFlag nf(0, cpNext);
                nodeMap[cpNext->label] = nf; 
            } else {
                cpNext = nodeMap[cursor->next->label].node;
            }
            current->next = cpNext;
        }
        if (cursor->random != NULL) {
            RandomListNode *cpRandom;
            if (nodeMap.find(cursor->random->label) == nodeMap.end()) {
                cpRandom = new RandomListNode(cursor->random->label);
                NodeFlag nf(0, cpRandom);
                nodeMap[cpRandom->label] = nf; 
            } else {
                cpRandom = nodeMap[cursor->random->label].node;
            }
            current->random = cpRandom;
        }
        cursor = cursor->next;
    }

    return cpHead;
}

int main(int argc, char *argv[]) {
    RandomListNode l1(1);
    RandomListNode l2(2);
    l1.next = &l2;
    l1.random = &l2;

    Solution s;
    RandomListNode *res = s.copyRandomList(&l1);
    while (res != NULL) {
        cout << res->label << " -- ";
        if (res->next == NULL)
            cout << "  " << " -- ";
        else 
            cout << res->next->label << " -- ";
        if (res->random == NULL)
            cout << "  " << " -- ";
        else 
            cout << res->random->label << " -- ";
        cout << endl;
        res = res->next;
    }
	return 1;
}
