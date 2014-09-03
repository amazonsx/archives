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

RandomListNode* Solution::copyRandomList(RandomListNode* head) {
    if (!head)  return NULL;
    map<RandomListNode*, RandomListNode*> nodeMap;
    RandomListNode *current = head;
    RandomListNode *cpHead = new RandomListNode(head->label);
    nodeMap[head] = cpHead;

    while(current != NULL) {
        if (current->next) {
            if (nodeMap.find(current->next) == nodeMap.end()) {
                RandomListNode *nextNode = new RandomListNode(current->next->label);
                nodeMap[current->next] = nextNode;
            }
            nodeMap[current]->next = nodeMap[current->next];
        }
        if (current->random) {
            if (nodeMap.find(current->random) == nodeMap.end()) {
                RandomListNode *randomNode = new RandomListNode(current->random->label);
                nodeMap[current->random] = randomNode;
            }
            nodeMap[current]->random = nodeMap[current->random];
        }
        current = current->next;
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
